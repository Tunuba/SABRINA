"""Capturas de las funciones que dibujan el escenario (func_8001FD50 y su gemela func_800204F0) con el nivel ya en
marcha. Las capturas viejas de func_8001FD50 eran de los primeros cuadros, con la camara sin poner: en las 8 un solo
triangulo pasaba los descartes y caia fuera de pantalla, y el dibujo (texturas, partidores, recorte, AddPrim) no se
probaba (05-10, 6 de 12 mutantes vivos). Aqui se entra al nivel, se espera a que corra y se captura en dos puntos.
Un solo emulador, sin ventana.
Uso: py capt_dibujo.py [niveles separados por comas] [funciones separadas por comas]
"""
import os, sys, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from emu import RAIZ, Emu
from explorar import CUE, estado

niveles = [int(x) for x in sys.argv[1].split(",")] if len(sys.argv) > 1 else [1, 3, 5, 7, 9, 11, 13]
nombres = sys.argv[2].split(",") if len(sys.argv) > 2 else ["func_8001FD50", "func_800204F0"]
CAPT = os.path.join(RAIZ, "decomp", "capturas")
funcs = {nom: int(d, 16) for d, tam, nom in (l.split() for l in open(os.path.join(RAIZ, "decomp", "funciones_juego.tsv")))
         if nom in nombres}


def esperar(e, n, tope=60):
    """Como e.esperar, pero si el emulador deja de avanzar (el juego se colgo) sigue a los tope segundos."""
    meta = e.frames() + n
    limite = time.time() + tope
    while e.frames() < meta and time.time() < limite:
        time.sleep(0.01)


def cuantas(nom):
    c = os.path.join(CAPT, nom)
    return len([f for f in os.listdir(c) if f.endswith(".regs")]) if os.path.isdir(c) else 0


t0 = time.time()
antes = {nom: cuantas(nom) for nom in funcs}
with Emu(iso=CUE, log="capt_dibujo.log", extra=("-fastboot",), depurar=True) as e:
    e.cargar(estado("saltar"))
    e.esperar(2)
    for nivel in niveles:
        e.eval(f"wr8(0x8007CA00, {nivel}); wr16(0x8007C9FC, 0); return 'ok'")
        esperar(e, 1300)
        # dos puntos del nivel: donde aparece Sabrina y un cuarto de la cuadricula mas alla
        for punto in (None, (16, 16)):
            if punto:
                x = ((punto[0] * 4) - 0x80 + 2) << 16
                z = (0x7F - (punto[1] * 4) - 0x80 + 2) << 16
                e.eval(f"local s = rd32(0x8007CAF8); if s ~= 0 then wr32(s + 0x24, {x & 0xFFFFFFFF}); "
                       f"wr32(s + 0x2C, {z & 0xFFFFFFFF}) end; return 'ok'")
                esperar(e, 60)
            for nom, d in funcs.items():
                os.makedirs(os.path.join(CAPT, nom), exist_ok=True)
                e.lua("capturar", a=d, n=1, dir=os.path.join(CAPT, nom), inicio=cuantas(nom))
            esperar(e, 10)
        print(f"nivel {nivel} listo, {time.time() - t0:.0f} s", flush=True)
print({nom: cuantas(nom) - antes[nom] for nom in funcs}, f"capturas nuevas ({time.time() - t0:.0f} s)")
