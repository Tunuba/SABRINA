"""El coprocesador geometrico de la PlayStation (GTE), lo justo para lo que usa este juego.

Unicorn no ejecuta las instrucciones del coprocesador 2: da excepcion. Aqui se emulan a mano. Como ninguna
de las 261 instrucciones cop2 del juego cae en un hueco de retardo, se puede poner un gancho en la
direccion exacta de cada una, hacer la cuenta en Python y saltarla.

El juego solo usa mover registros (mtc2, mfc2, ctc2, cfc2, lwc2, swc2), mvmva (multiplicar por una matriz
y sumar un vector) y op (producto vectorial con la diagonal de la matriz de giro).

Ojo con lo que esto demuestra: las dos versiones, la original y la de C, ven el mismo GTE, asi que la
comparacion vale aunque la cuenta no fuera exacta; lo que cambiaria es que los caminos que toma el codigo
no serian los del juego de verdad. Por eso mvmva y op estan hechos como manda el manual, con sus recortes.
"""
import struct

from unicorn import UC_HOOK_CODE
from unicorn.mips_const import UC_MIPS_REG_PC, UC_MIPS_REG_ZERO


def s16(v):
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def s32(v):
    v &= 0xFFFFFFFF
    return v - 0x100000000 if v & 0x80000000 else v


def recortar(v, bajo, alto):
    return bajo if v < bajo else alto if v > alto else v


class Gte:
    def __init__(self):
        self.datos = [0] * 32
        self.ctrl = [0] * 32

    # --- registros ---
    def leer_dato(self, i):
        if i == 15:                                  # SXYP: el ultimo de la cola de pantalla
            return self.datos[14]
        if i == 28 or i == 29:                       # IRGB / ORGB: el color a 5 bits por canal
            r = recortar(s32(self.datos[9]) >> 7, 0, 0x1F)
            g = recortar(s32(self.datos[10]) >> 7, 0, 0x1F)
            b = recortar(s32(self.datos[11]) >> 7, 0, 0x1F)
            return r | (g << 5) | (b << 10)
        return self.datos[i] & 0xFFFFFFFF

    def escribir_dato(self, i, v):
        v &= 0xFFFFFFFF
        if i == 15:                                  # empuja la cola de coordenadas de pantalla
            self.datos[12], self.datos[13], self.datos[14] = self.datos[13], self.datos[14], v
            return
        if i == 28:                                  # IRGB: desarma el color a IR1, IR2, IR3
            self.datos[28] = v & 0x7FFF
            self.datos[9] = (v & 0x1F) << 7
            self.datos[10] = ((v >> 5) & 0x1F) << 7
            self.datos[11] = ((v >> 10) & 0x1F) << 7
            return
        if i == 29:                                  # ORGB es de solo lectura
            return
        if i == 30:                                  # LZCS: cuantos bits de arriba son iguales al primero
            self.datos[30] = v
            n = v if not (v & 0x80000000) else (~v & 0xFFFFFFFF)
            self.datos[31] = 32 - n.bit_length() if n else 32
            return
        self.datos[i] = v

    # --- matrices y vectores ---
    def matriz(self, cual):
        b = {0: 0, 1: 8, 2: 16}.get(cual)
        if b is None:                                # la cuarta matriz es basura; el juego no la usa
            return [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
        c = self.ctrl
        return [[s16(c[b]), s16(c[b] >> 16), s16(c[b + 1])],
                [s16(c[b + 1] >> 16), s16(c[b + 2]), s16(c[b + 2] >> 16)],
                [s16(c[b + 3]), s16(c[b + 3] >> 16), s16(c[b + 4])]]

    def vector(self, cual):
        d = self.datos
        if cual == 0:
            return [s16(d[0]), s16(d[0] >> 16), s16(d[1])]
        if cual == 1:
            return [s16(d[2]), s16(d[2] >> 16), s16(d[3])]
        if cual == 2:
            return [s16(d[4]), s16(d[4] >> 16), s16(d[5])]
        return [s16(d[9]), s16(d[10]), s16(d[11])]   # el vector IR

    def traslacion(self, cual):
        c = self.ctrl
        if cual == 0:
            return [s32(c[5]), s32(c[6]), s32(c[7])]
        if cual == 1:
            return [s32(c[13]), s32(c[14]), s32(c[15])]
        if cual == 2:
            return [s32(c[21]), s32(c[22]), s32(c[23])]
        return [0, 0, 0]

    def guardar_mac_ir(self, mac, sf, lm):
        bajo = 0 if lm else -0x8000
        for k in range(3):
            v = mac[k] >> (12 if sf else 0)
            self.datos[25 + k] = v & 0xFFFFFFFF
            self.datos[9 + k] = recortar(v, bajo, 0x7FFF) & 0xFFFFFFFF

    # --- ordenes ---
    def mvmva(self, op):
        sf = (op >> 19) & 1
        mx = (op >> 17) & 3
        vx = (op >> 15) & 3
        cv = (op >> 13) & 3
        lm = (op >> 10) & 1
        m = self.matriz(mx)
        v = self.vector(vx)
        t = self.traslacion(cv)
        mac = [(t[k] << 12) + m[k][0] * v[0] + m[k][1] * v[1] + m[k][2] * v[2] for k in range(3)]
        self.guardar_mac_ir(mac, sf, lm)

    def op(self, orden):
        sf = (orden >> 19) & 1
        lm = (orden >> 10) & 1
        c = self.ctrl
        d1, d2, d3 = s16(c[0]), s16(c[2]), s16(c[4])
        ir1, ir2, ir3 = s16(self.datos[9]), s16(self.datos[10]), s16(self.datos[11])
        mac = [d2 * ir3 - d3 * ir2,
               d3 * ir1 - d1 * ir3,
               d1 * ir2 - d2 * ir1]
        self.guardar_mac_ir(mac, sf, lm)


def instrucciones_cop2(ins):
    """Las direcciones con una instruccion del coprocesador 2, de un desensamblado {direccion: (mn, ops)}."""
    return {d for d, (mn, _) in ins.items()
            # objdump escribe las ordenes del GTE como `c2 0x...`, no con su nombre
            if mn in ("mtc2", "mfc2", "ctc2", "cfc2", "lwc2", "swc2", "c2", "cop2")}


def poner_ganchos(uc, direcciones):
    """Pone un gancho en cada direccion con una instruccion cop2. Devuelve el GTE, por si hace falta verlo."""
    gte = Gte()

    def paso(u, dirc, tam, _):
        palabra = struct.unpack("<I", u.mem_read(dirc & 0x1FFFFFFF, 4))[0]
        rt = (palabra >> 16) & 0x1F
        rd = (palabra >> 11) & 0x1F
        base = (palabra >> 21) & 0x1F
        desp = palabra & 0xFFFF
        desp = desp - 0x10000 if desp & 0x8000 else desp
        orden = (palabra >> 26) & 0x3F
        if orden == 0x12:                            # COP2
            sub = (palabra >> 21) & 0x1F
            if palabra & 0x02000000:                 # una orden del GTE
                cual = palabra & 0x3F
                if cual == 0x12:
                    gte.mvmva(palabra)
                elif cual == 0x0C:
                    gte.op(palabra)
            elif sub == 0:                           # mfc2
                u.reg_write(UC_MIPS_REG_ZERO + rt, gte.leer_dato(rd))
            elif sub == 2:                           # cfc2
                u.reg_write(UC_MIPS_REG_ZERO + rt, gte.ctrl[rd] & 0xFFFFFFFF)
            elif sub == 4:                           # mtc2
                gte.escribir_dato(rd, u.reg_read(UC_MIPS_REG_ZERO + rt))
            elif sub == 6:                           # ctc2
                gte.ctrl[rd] = u.reg_read(UC_MIPS_REG_ZERO + rt) & 0xFFFFFFFF
        elif orden == 0x32:                          # lwc2
            dir_dato = (u.reg_read(UC_MIPS_REG_ZERO + base) + desp) & 0xFFFFFFFF
            gte.escribir_dato(rt, struct.unpack("<I", u.mem_read(dir_dato & 0x1FFFFFFF, 4))[0])
        elif orden == 0x3A:                          # swc2
            dir_dato = (u.reg_read(UC_MIPS_REG_ZERO + base) + desp) & 0xFFFFFFFF
            u.mem_write(dir_dato & 0x1FFFFFFF, struct.pack("<I", gte.leer_dato(rt)))
        u.reg_write(UC_MIPS_REG_PC, dirc + 4)

    for d in direcciones:
        uc.hook_add(UC_HOOK_CODE, paso, begin=d, end=d + 3)
    return gte
