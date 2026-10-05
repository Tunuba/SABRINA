"""Busca que funciones en C rompen el arranque: arma con un subconjunto y comprueba que el juego avance.

Uso: python biseccion_c.py            bisecta la lista de decomp/build/armado_c.txt
     python biseccion_c.py A,B,C      prueba solo ese subconjunto
"""
import os
import subprocess
import sys
import time

import disco
import traducir
from emu import RAIZ, Emu

DECOMP = os.path.join(RAIZ, "decomp")
WSLDIR = "/mnt/" + DECOMP[0].lower() + DECOMP[2:].replace("\\", "/")


def armar(funs, salida="build/SLUS_bis.exe"):
    r = subprocess.run(["wsl", "-d", "Ubuntu", "--", "bash", "-lc",
                        f"cd '{WSLDIR}' && python3 armar_c.py --solo {','.join(funs)} --salida {salida}"],
                       capture_output=True, text=True)
    if r.returncode:
        raise SystemExit(r.stdout + r.stderr)
    return os.path.join(DECOMP, salida)


def prueba(funs, frames=2400, espera=170):
    """True si el juego llega a 'frames' cuadros sin caer en el manejador de excepciones."""
    exe = open(armar(funs), "rb").read()
    pista = os.path.join(disco.DISCO, "bis (Track 01).bin")
    disco.parchar({traducir.EXE: exe}, pista)
    disco.cue_mod(os.path.join(disco.DISCO, "bis.cue"), pista)
    with Emu(iso=os.path.join(disco.DISCO, "bis.cue"), log="bis.log", extra=("-fastboot",), depurar=True) as e:
        t = time.time()
        ultimo, desde = -1, time.time()
        f, pc = -1, 0
        while time.time() - t < espera:
            try:
                f = e.frames()
                pc = int(e.eval("return PCSX.getRegisters().pc"))
            except Exception:
                pass
            if 0x80000080 <= pc < 0x80000100:
                return False, f"excepcion en frame {f}"
            if f != ultimo:
                ultimo, desde = f, time.time()
            elif time.time() - desde > 12:
                return False, f"congelado en frame {f} (pc {pc:08x})"
            if f >= frames:
                return True, f"{f} frames"
            time.sleep(1)
        return False, f"lento: frame {f}"


def lista():
    return [l.split("\t")[1] for l in open(os.path.join(DECOMP, "build", "armado_c_completo.txt"), encoding="utf-8")
            if l.startswith("OK")]


if __name__ == "__main__":
    if len(sys.argv) > 1:
        print(prueba(sys.argv[1].split(",")))
        sys.exit()
    fs = lista()
    # por quitar: "todas menos fs[:r]" pasa solo cuando r deja fuera a la ultima de las que rompen
    lo, hi = 0, len(fs)         # lo: falla (probado); hi: sin ninguna, pasa
    while hi - lo > 1:
        mid = (lo + hi) // 2
        ok, m = prueba(fs[mid:])
        print(f"sin las primeras {mid}:", ok, m, flush=True)
        if ok:
            hi = mid
        else:
            lo = mid
    print("rompe:", fs[hi - 1], flush=True)
