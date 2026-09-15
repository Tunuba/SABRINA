"""Arma un disco con los mods elegidos y su parche PPF para compartir.

Uso: python armar.py nombre [--es] [--invencible]
  --es          menus del ejecutable y pantalla de carga en espanol
  --invencible  Sabrina no pierde vida (ver mod_invencible.py)
Deja
  disco\\<nombre> (Track 01).bin y disco\\<nombre>.cue   para jugar en el emulador
  mods\\<nombre>.ppf                                    parche sobre la pista 1 original
"""
import os
import sys

import disco
import mod_invencible
import ppf
import traducir
from mod_carga import pantalla_carga

nombre = sys.argv[1]
exe = open(os.path.join(disco.RAIZ, "extraido", traducir.EXE), "rb").read()
cambios = {}
descripcion = []
if "--es" in sys.argv:
    exe, n = traducir.traducir_exe(exe)
    cambios[r"GRAPHICS\FRONT\FR.PIC"] = pantalla_carga()
    descripcion.append("espanol")
    print(f"espanol: {n} textos y la pantalla de carga")
if "--invencible" in sys.argv:
    exe = mod_invencible.parchar_exe(exe)
    descripcion.append("invencible")
    print(f"invencible: {len(mod_invencible.PARCHES)} instrucciones")
if not descripcion:
    sys.exit("no elegiste ningun mod")
cambios[traducir.EXE] = exe

pista = os.path.join(disco.DISCO, f"{nombre} (Track 01).bin")
disco.parchar(cambios, pista)
disco.cue_mod(os.path.join(disco.DISCO, nombre + ".cue"), pista)
salida = os.path.join(disco.RAIZ, "mods", nombre + ".ppf")
c, t = ppf.crear(disco.PISTA1, pista, salida, "Sabrina " + " + ".join(descripcion))
print(f"disco {pista}")
print(f"parche {salida}: {t} bytes, {c} bytes cambiados")
