"""Ensaya con un disco propio todo lo que despues se hara con el de Sabrina.

1. Arma un disco de PS1 con mkpsxiso (el ejemplo padtest, una textura TIM y un archivo de datos).
2. Lo arranca en el emulador con OpenBIOS y guarda una captura.
3. Lo desarma con dumpsxiso y lo vuelve a armar desde el XML que genera.
4. Compara el disco rearmado con el original, byte a byte.

Uso: python prueba_disco.py        (todo queda en C:\\Proyectos\\SABRINA\\prueba_disco)
"""
import hashlib
import os
import re
import shutil
import struct
import subprocess

from emu import RAIZ, Emu

MK = os.path.join(RAIZ, r"herramientas\mkpsxiso\mkpsxiso-2.30-win64")
DIR = os.path.join(RAIZ, "prueba_disco")
FUENTE = os.path.join(DIR, "fuente")
EXE = os.path.join(RAIZ, r"herramientas\nugget\psyqo\examples\padtest\padtest.ps-exe")


def tim16(ancho, alto):
    """Textura TIM de 16 bits con un degradado, para tener un TIM de verdad en el disco."""
    pix = bytearray()
    for y in range(alto):
        for x in range(ancho):
            r, g, b = x * 31 // (ancho - 1), y * 31 // (alto - 1), 16
            pix += struct.pack("<H", r | (g << 5) | (b << 10))
    bloque = struct.pack("<IHHHH", 12 + len(pix), 640, 0, ancho, alto) + pix
    return struct.pack("<II", 0x10, 0x02) + bloque


def sha(ruta):
    return hashlib.sha256(open(ruta, "rb").read()).hexdigest()


def correr(*args):
    r = subprocess.run(args, capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"{args[0]} salio con {r.returncode}\n{r.stdout}\n{r.stderr}")
    return r.stdout


shutil.rmtree(DIR, ignore_errors=True)
os.makedirs(os.path.join(FUENTE, "DATOS"))
shutil.copy(EXE, os.path.join(FUENTE, "PADTEST.EXE"))
with open(os.path.join(FUENTE, "SYSTEM.CNF"), "w", newline="\r\n") as f:
    f.write("BOOT = cdrom:\\PADTEST.EXE;1\nTCB = 4\nEVENT = 10\nSTACK = 801FFFF0\n")
with open(os.path.join(FUENTE, "DATOS", "PRUEBA.TIM"), "wb") as f:
    f.write(tim16(64, 64))
with open(os.path.join(FUENTE, "DATOS", "GRANDE.BIN"), "wb") as f:
    f.write(bytes((i * 7 + (i >> 8)) & 0xFF for i in range(200_000)))

xml = f"""<?xml version="1.0" encoding="UTF-8"?>
<iso_project image_name="{DIR}\\prueba.bin" cue_sheet="{DIR}\\prueba.cue">
  <track type="data">
    <identifiers system="PLAYSTATION" application="PLAYSTATION" volume="PRUEBA" publisher="SABRINA"/>
    <directory_tree source="{FUENTE}">
      <file name="SYSTEM.CNF"/>
      <file name="PADTEST.EXE"/>
      <dir name="DATOS" source="{FUENTE}\\DATOS">
        <file name="PRUEBA.TIM"/>
        <file name="GRANDE.BIN"/>
      </dir>
      <dummy sectors="1024"/>
    </directory_tree>
  </track>
</iso_project>
"""
with open(os.path.join(DIR, "prueba.xml"), "w") as f:
    f.write(xml)
correr(os.path.join(MK, "mkpsxiso.exe"), "-y", os.path.join(DIR, "prueba.xml"))
print("1. disco armado", os.path.getsize(os.path.join(DIR, "prueba.bin")), "bytes")

with Emu(iso=os.path.join(DIR, "prueba.cue"), log="prueba_disco.log") as e:
    e.esperar(240)
    e.captura(os.path.join(DIR, "arranque.png"))
print("2. arrancado, captura en arranque.png")

sal = os.path.join(DIR, "desarmado")
# -l deja escrito en el XML el sector (LBA) de cada archivo, asi al rearmar cada uno cae donde estaba
correr(os.path.join(MK, "dumpsxiso.exe"), "-l", "-x", sal, "-s", os.path.join(DIR, "desarmado.xml"),
       os.path.join(DIR, "prueba.bin"))
for raiz, _, archivos in os.walk(sal):
    for a in archivos:
        print("   ", os.path.relpath(os.path.join(raiz, a), sal), os.path.getsize(os.path.join(raiz, a)))
iguales = all(sha(os.path.join(FUENTE, r)) == sha(os.path.join(sal, r))
              for r in ("SYSTEM.CNF", "PADTEST.EXE", r"DATOS\PRUEBA.TIM", r"DATOS\GRANDE.BIN"))
print("3. desarmado, archivos identicos a la fuente:", iguales)

# rearmar desde el xml de dumpsxiso, cambiando el nombre de salida
x = open(os.path.join(DIR, "desarmado.xml"), encoding="utf-8").read()
x = re.sub(r'image_name="[^"]*"', lambda m: f'image_name="{DIR}\\rearmado.bin"', x)
x = re.sub(r'cue_sheet="[^"]*"', lambda m: f'cue_sheet="{DIR}\\rearmado.cue"', x)
with open(os.path.join(DIR, "rearmado.xml"), "w", encoding="utf-8") as f:
    f.write(x)
correr(os.path.join(MK, "mkpsxiso.exe"), "-y", os.path.join(DIR, "rearmado.xml"))
rearmado = [os.path.join(DIR, n) for n in os.listdir(DIR) if n.startswith("rearmado") and n.endswith(".bin")]
print("4. rearmado", rearmado)
for r in rearmado:
    print("   identico al original:", sha(r) == sha(os.path.join(DIR, "prueba.bin")))
