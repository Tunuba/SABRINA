"""Capturas en cascada: corre la ORIGINAL de una funcion (el padre) desde una de sus capturas y, cuando entra a
otra (la hija) por n-esima vez, guarda la RAM, el scratchpad y los registros como captura sintetica de la hija.

Sirve para las funciones que solo se llaman desde herramientas o desde el arranque (sin capturas reales): el
padre ya prepara sus argumentos de verdad (un archivo abierto, un bufer lleno). Lo que no esta en la RAM (el
estado del hardware, del CD y de los archivos virtuales del modelo) no viaja: sirve si la hija trabaja con lo
que ya esta en memoria (por ejemplo un archivo chico que ArchivoAbrir ya leyo a su bufer).

Uso: python3 verif/cascada.py padre captura_del_padre hija [n] [--real]
  captura_del_padre: ruta sin extension (p. ej. capturas_sint/HerramientaArmarModelos/00)
  queda en capturas_sint/hija/NN.* con NN.MANO diciendo de donde salio.
"""
import os
import sys

AQUI = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(AQUI)
sys.path.insert(0, AQUI)
import verificar as V
from unicorn import UC_HOOK_CODE
from unicorn.mips_const import UC_MIPS_REG_ZERO, UC_MIPS_REG_HI, UC_MIPS_REG_LO

padre, cap, hija = sys.argv[1:4]
n = int(sys.argv[4]) if len(sys.argv) > 4 and sys.argv[4].isdigit() else 1
sim = V.simbolos()
destino = os.path.join(AQUI, "capturas_sint", hija)
os.makedirs(destino, exist_ok=True)
nn = len([x for x in os.listdir(destino) if x.endswith(".regs")])
hecho = {"veces": 0, "guardada": False}
orig_uc = V.Uc


def Uc2(*a):
    u = orig_uc(*a)
    es = u.emu_start

    def emu_start(*x, **k):
        def entrada(uu, d, t, _):
            hecho["veces"] += 1
            if hecho["veces"] != n or hecho["guardada"]:
                return
            regs = [uu.reg_read(UC_MIPS_REG_ZERO + i) for i in range(32)]
            regs[0] = 0
            regs += [d, uu.reg_read(UC_MIPS_REG_HI), uu.reg_read(UC_MIPS_REG_LO)]
            base = os.path.join(destino, "%02d" % nn)
            open(base + ".ram", "wb").write(bytes(uu.mem_read(0, 0x200000)))
            open(base + ".spad", "wb").write(bytes(uu.mem_read(0x1F800000, 0x400)))
            open(base + ".regs", "w", newline="").write(" ".join("%08x" % r for r in regs))
            open(base + ".MANO", "w", newline="").write(
                f"en cascada: la entrada numero {n} a {hija} corriendo la original de {padre} desde {cap}\n")
            if not os.path.exists(os.path.join(destino, "DONANTE")):
                open(os.path.join(destino, "DONANTE"), "w", newline="").write(padre + "\n")
            hecho["guardada"] = True
            uu.emu_stop()
        u.hook_add(UC_HOOK_CODE, entrada, begin=sim[hija], end=sim[hija])
        return es(*x, **k)
    u.emu_start = emu_start
    return u


V.Uc = Uc2
V.ejecutar(cap, sim[padre], None)
print(f"{hija}: {'captura %02d guardada' % nn if hecho['guardada'] else 'no se llego'} "
      f"(entro {hecho['veces']} veces)")
