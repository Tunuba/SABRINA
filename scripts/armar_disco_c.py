"""Arma un disco con el ejecutable hecho por decomp/armar_c.py.

Uso: python armar_disco_c.py [ejecutable] [nombre]
  por defecto decomp\build\SLUS_C.exe y el nombre sabrina_c: deja disco\sabrina_c.cue
"""
import os
import sys

import disco
import traducir

exe_ruta = sys.argv[1] if len(sys.argv) > 1 else os.path.join(disco.RAIZ, "decomp", "build", "SLUS_C.exe")
nombre = sys.argv[2] if len(sys.argv) > 2 else "sabrina_c"
exe = open(exe_ruta, "rb").read()
pista = os.path.join(disco.DISCO, f"{nombre} (Track 01).bin")
disco.parchar({traducir.EXE: exe}, pista)
disco.cue_mod(os.path.join(disco.DISCO, nombre + ".cue"), pista)
print(f"disco {nombre}.cue con {exe_ruta} ({len(exe)} bytes)")
