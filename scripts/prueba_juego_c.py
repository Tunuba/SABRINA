"""Juega el disco armado con C: titulo, nuevo juego, HUB, y despues salta por varios niveles y mueve a Sabrina.

Uso: python prueba_juego_c.py <disco.cue> [nombre] [niveles separados por coma]
Cada etapa espera unos segundos y comprueba que los cuadros avanzan y que el procesador no cayo en la BIOS.
Capturas en notas\capturas\jc_<nombre>_NN.png y una hoja con todas.
"""
import os
import sys
import time

from emu import RAIZ, Emu
from hoja import hoja
from ir_a_nivel import ir, NIVEL, JUGANDO, NOMBRES

cue = sys.argv[1]
nombre = sys.argv[2] if len(sys.argv) > 2 else "c"
niveles = [int(x) for x in sys.argv[3].split(",")] if len(sys.argv) > 3 else [3, 4, 7, 10, 14, 13]
CAP = os.path.join(RAIZ, "notas", "capturas")


def pc(e):
    return int(e.eval("return PCSX.getRegisters().pc"))


def vivo(e, etapa, seg=3):
    f0 = e.frames()
    time.sleep(seg)
    f1 = e.frames()
    p = pc(e)
    ok = f1 > f0 + 30 and not (0xBFC00000 <= p or 0x80000080 <= p < 0x80000100)
    print(f"  {etapa}: frames {f0}->{f1} pc {p:08x} {'VIVO' if ok else 'CAIDO'}", flush=True)
    return ok


caps = []
with Emu(iso=os.path.join(RAIZ, "disco", cue), log=f"jc_{nombre}.log", extra=("-fastboot",), depurar=True) as e:
    def cap(tag):
        r = os.path.join(CAP, f"jc_{nombre}_{len(caps):02d}.png")
        e.captura(r)
        caps.append(r)
        print(f"  captura {tag}", flush=True)

    e.esperar(2160)
    cap("titulo")
    for p in "CROSS w300 START w60 CROSS w240".split():
        if p[0] == "w":
            e.esperar(int(p[1:]))
        else:
            e.pulsar(p)
    e.esperar(1300)
    cap("hub")
    todo = vivo(e, "HUB")
    for dirn in ("RIGHT", "UP", "LEFT", "DOWN"):
        e.pulsar(dirn, f=40)
    e.pulsar("CROSS", f=10)
    e.esperar(60)
    todo &= vivo(e, "HUB tras moverse")
    cap("hub movido")
    for n in niveles:
        ir(e, n)
        e.esperar(600)
        cap(f"nivel {NOMBRES[n]}")
        ok = vivo(e, f"nivel {NOMBRES[n]} (byte {e.eval(f'return rd8({NIVEL})')} jugando {e.eval(f'return rd16({JUGANDO})')})")
        todo &= ok
        if not ok:
            break
        for dirn in ("UP", "RIGHT"):
            e.pulsar(dirn, f=60)
        e.pulsar("CROSS", f=10)
        e.esperar(60)
        todo &= vivo(e, f"nivel {NOMBRES[n]} tras moverse")
        if not todo:
            break
hoja(os.path.join(CAP, f"jc_{nombre}_hoja.png"), 4, caps)
print("RESULTADO:", "TODO VIVO" if todo else "SE CAYO")
