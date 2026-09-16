"""El coprocesador geometrico de la PlayStation (GTE), lo justo para lo que usa este juego.

Unicorn no ejecuta las instrucciones del coprocesador 2: da excepcion. Aqui se emulan a mano: se pone un
gancho en la direccion de cada una, se hace la cuenta en Python y se deja que Unicorn ejecute un nop, que
se escribe encima de la instruccion al arrancar la corrida. Antes el gancho adelantaba el contador en vez
de poner el nop, y eso se comia los saltos: el compilador puede poner un swc2 en el hueco de retardo de una
llamada (en el juego no pasa, en el C que genera GCC si), y al adelantar el contador se perdia el salto.

El juego usa mover registros (mtc2, mfc2, ctc2, cfc2, lwc2, swc2) y cinco ordenes: mvmva (multiplicar por
una matriz y sumar un vector), op (producto vectorial con la diagonal de la matriz de giro), rtps y rtpt
(pasar uno o tres vectores a coordenadas de pantalla) y nclip (el area con signo del triangulo en
pantalla, para saber si se ve de frente). Una orden que no este aqui para la corrida: dejarla pasar en
silencio haria que las dos versiones se equivocaran igual y el verificador aprobaria sin mirar nada.

Ojo con lo que esto demuestra: las dos versiones, la original y la de C, ven el mismo GTE, asi que la
comparacion vale aunque la cuenta no fuera exacta; lo que cambiaria es que los caminos que toma el codigo
no serian los del juego de verdad. Por eso mvmva y op estan hechos como manda el manual, con sus recortes.
"""
import struct

from unicorn import UC_HOOK_CODE
from unicorn.mips_const import UC_MIPS_REG_ZERO


def s16(v):
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def s32(v):
    v &= 0xFFFFFFFF
    return v - 0x100000000 if v & 0x80000000 else v


def recortar(v, bajo, alto):
    return bajo if v < bajo else alto if v > alto else v


# Tabla de la division del GTE: el hardware saca 1/z con esta tabla y dos pasadas de Newton, no dividiendo.
UNR = [max(0, (0x40000 // (i + 0x100) + 1) // 2 - 0x101) for i in range(257)]


class Gte:
    def __init__(self):
        self.datos = [0] * 32
        self.ctrl = [0] * 32
        self.sin_emular = set()      # ordenes que aparecieron y no estan hechas; paran la corrida

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

    # --- banderas ---
    # El GTE deja en el control 31 lo que se salio de rango en la ultima orden. El juego lo lee (cfc2 $31)
    # para saber si un triangulo se le fue de la pantalla y hay que recortarlo, asi que hay que llevarlo.
    def bandera_ini(self):
        self.ctrl[31] = 0

    def bandera_fin(self):
        f = self.ctrl[31]
        if f & 0x7F87E000:               # los bits que encienden el resumen de error
            f |= 0x80000000
        self.ctrl[31] = f & 0xFFFFFFFF

    def marcar(self, bit):
        self.ctrl[31] |= 1 << bit

    def guardar_mac0(self, v):
        if v > 0x7FFFFFFF:
            self.marcar(16)
        elif v < -0x80000000:
            self.marcar(15)
        self.datos[24] = v & 0xFFFFFFFF

    def guardar_mac_ir(self, mac, sf, lm):
        bajo = 0 if lm else -0x8000
        for k in range(3):
            if mac[k] > 0x7FFFFFFFFF:
                self.marcar(30 - k)
            elif mac[k] < -0x8000000000:
                self.marcar(27 - k)
            v = mac[k] >> (12 if sf else 0)
            self.datos[25 + k] = v & 0xFFFFFFFF
            r = recortar(v, bajo, 0x7FFF)
            if r != v:
                self.marcar(24 - k)
            self.datos[9 + k] = r & 0xFFFFFFFF

    # --- ordenes ---
    def mvmva(self, op):
        sf = (op >> 19) & 1
        mx = (op >> 17) & 3
        vx = (op >> 15) & 3
        cv = (op >> 13) & 3
        lm = (op >> 10) & 1
        self.bandera_ini()
        m = self.matriz(mx)
        v = self.vector(vx)
        t = self.traslacion(cv)
        mac = [(t[k] << 12) + m[k][0] * v[0] + m[k][1] * v[1] + m[k][2] * v[2] for k in range(3)]
        self.guardar_mac_ir(mac, sf, lm)
        self.bandera_fin()

    def op(self, orden):
        sf = (orden >> 19) & 1
        lm = (orden >> 10) & 1
        self.bandera_ini()
        c = self.ctrl
        d1, d2, d3 = s16(c[0]), s16(c[2]), s16(c[4])
        ir1, ir2, ir3 = s16(self.datos[9]), s16(self.datos[10]), s16(self.datos[11])
        mac = [d2 * ir3 - d3 * ir2,
               d3 * ir1 - d1 * ir3,
               d1 * ir2 - d2 * ir1]
        self.guardar_mac_ir(mac, sf, lm)
        self.bandera_fin()

    def dividir(self, h, sz3):
        """h*0x20000/sz3 redondeado, como lo hace el hardware. Si la z es muy chica se sale de rango y el
        GTE devuelve el tope; ahi es donde el juego decide que algo esta demasiado cerca."""
        if sz3 == 0 or h >= sz3 * 2:
            self.marcar(17)
            return 0x1FFFF
        z = 16 - sz3.bit_length()
        n = h << z
        d = sz3 << z
        u = UNR[(d - 0x7FC0) >> 7] + 0x101
        d = (0x2000080 - d * u) >> 8
        d = (0x80 + d * u) >> 8
        r = ((n * d) + 0x8000) >> 16
        if r > 0x1FFFF:
            self.marcar(17)
            return 0x1FFFF
        return r

    def rtps(self, orden, cual=0):
        """Pasa el vector a coordenadas de pantalla: lo gira y lo traslada con la matriz 0, empuja la z en
        su cola, y divide x e y entre esa z. Deja el punto en la cola SXY y la niebla en IR0."""
        sf = (orden >> 19) & 1
        lm = (orden >> 10) & 1
        m = self.matriz(0)
        v = self.vector(cual)
        t = self.traslacion(0)
        mac = [(t[k] << 12) + m[k][0] * v[0] + m[k][1] * v[1] + m[k][2] * v[2] for k in range(3)]
        self.guardar_mac_ir(mac, sf, lm)
        z = mac[2] >> 12
        sz = recortar(z, 0, 0xFFFF)
        if sz != z:
            self.marcar(18)
        d = self.datos
        d[16], d[17], d[18], d[19] = d[17], d[18], d[19], sz
        div = self.dividir(self.ctrl[26] & 0xFFFF, sz)
        mac0 = div * s16(d[9]) + s32(self.ctrl[24])
        self.guardar_mac0(mac0)
        sx = recortar(mac0 >> 16, -0x400, 0x3FF)
        if sx != mac0 >> 16:
            self.marcar(14)
        mac0 = div * s16(d[10]) + s32(self.ctrl[25])
        self.guardar_mac0(mac0)
        sy = recortar(mac0 >> 16, -0x400, 0x3FF)
        if sy != mac0 >> 16:
            self.marcar(13)
        d[12], d[13] = d[13], d[14]
        d[14] = (sx & 0xFFFF) | ((sy & 0xFFFF) << 16)
        mac0 = div * s16(self.ctrl[27]) + s32(self.ctrl[28])
        self.guardar_mac0(mac0)
        ir0 = recortar(mac0 >> 12, 0, 0x1000)
        if ir0 != mac0 >> 12:
            self.marcar(12)
        d[8] = ir0 & 0xFFFFFFFF

    def rtp(self, orden, cuantos):
        """rtps (un vector) o rtpt (los tres del triangulo). Las banderas salen juntas de los tres."""
        self.bandera_ini()
        for k in range(cuantos):
            self.rtps(orden, k)
        self.bandera_fin()

    def nclip(self):
        """El doble del area con signo del triangulo que hay en la cola de pantalla: negativa si se ve por
        detras. El juego lo usa para no dibujar las caras de atras."""
        self.bandera_ini()
        d = self.datos
        x = [s16(d[12 + k]) for k in range(3)]
        y = [s16(d[12 + k] >> 16) for k in range(3)]
        self.guardar_mac0(x[0] * y[1] + x[1] * y[2] + x[2] * y[0]
                          - x[0] * y[2] - x[1] * y[0] - x[2] * y[1])
        self.bandera_fin()


def instrucciones_cop2(ins):
    """Las direcciones con una instruccion del coprocesador 2, de un desensamblado {direccion: (mn, ops)}."""
    return {d for d, (mn, _) in ins.items()
            # objdump escribe las ordenes del GTE como `c2 0x...`, no con su nombre
            if mn in ("mtc2", "mfc2", "ctc2", "cfc2", "lwc2", "swc2", "c2", "cop2")}


NOP = b"\x00\x00\x00\x00"


def poner_ganchos(uc, direcciones):
    """Pone un gancho en cada direccion con una instruccion cop2 y deja un nop en su lugar. Devuelve el
    GTE, por si hace falta verlo."""
    gte = Gte()
    palabras = {}

    def paso(u, dirc, tam, _):
        palabra = palabras[dirc]
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
                elif cual == 0x01:
                    gte.rtp(palabra, 1)
                elif cual == 0x30:                   # rtpt: los tres vertices del triangulo
                    gte.rtp(palabra, 3)
                elif cual == 0x06:
                    gte.nclip()
                else:
                    # no emularla y seguir seria aprobar sin mirar: se para la corrida
                    gte.sin_emular.add(cual)
                    u.emu_stop()
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

    for d in direcciones:
        palabras[d] = struct.unpack("<I", uc.mem_read(d & 0x1FFFFFFF, 4))[0]
        uc.mem_write(d & 0x1FFFFFFF, NOP)
        uc.hook_add(UC_HOOK_CODE, paso, begin=d, end=d + 3)
    return gte
