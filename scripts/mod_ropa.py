"""Mod visual: el pantalon naranja de Sabrina pasa a azul, en todos los niveles.

Como se encontro: gpu_paquetes.py lee los poligonos que el juego manda a la GPU y dice que paleta usa
cada uno; probar_paletas.py las cambia en vivo. En el HUB el pantalon es la paleta (832,472) y la cadera
(864,472). La de las piernas esta igual en los 14 .TEX, en otra posicion en cada uno.

El mod busca, en la zona de paletas de cada .TEX (filas 448 a 511), las paletas de 16 colores que tienen
al menos 3 de los naranjas exactos del pantalon, y solo ahi cambia esos naranjas (rojo por azul). La piel
que comparte paleta con la cadera no se toca.

Uso: python mod_ropa.py probar     cambia las paletas en vivo en el HUB y captura
"""
import glob
import os
import struct
import sys

NARANJAS = {0x04AD, 0x048C, 0x08CF, 0x08AE, 0x048B, 0x048A, 0x0CCF, 0x0CEF, 0x10EF, 0x08AD}
FILA_DESDE = 448
# La paleta de las piernas tal cual esta en los 14 niveles. Un .TEX sin ella no tiene el modelo de
# Sabrina (FR.TEX, el del menu, trae en esas filas pixeles de imagenes con los mismos naranjas).
PIERNAS = struct.pack("<16H", 0x04AD, 0x048C, 0x08CF, 0x08AE, 0x048B, 0x048A, 0x0CCF, 0x2990,
                      0x2570, 0x256F, 0x214E, 0x0CEF, 0x10EF, 0, 0, 0)


def a_azul(v):
    return (v & 0x83E0) | ((v & 31) << 10) | ((v >> 10) & 31)


def recolorear_tex(datos):
    """Devuelve (datos nuevos, paletas cambiadas). datos: un .TEX (512x512 de 16 bits)."""
    d = bytearray(datos)
    cambiadas = 0
    if d.find(PIERNAS, FILA_DESDE * 1024) < 0:
        return bytes(d), 0
    for y in range(FILA_DESDE, 512):
        for x in range(0, 512, 16):
            off = (y * 512 + x) * 2
            pal = list(struct.unpack_from("<16H", d, off))
            if sum(1 for v in pal if v in NARANJAS) < 3:
                continue
            struct.pack_into("<16H", d, off, *[a_azul(v) if v in NARANJAS else v for v in pal])
            cambiadas += 1
    return bytes(d), cambiadas


def cambios_disco(raiz):
    """{ruta en el disco: bytes} de todos los .TEX recoloreados."""
    res = {}
    for ruta in sorted(glob.glob(os.path.join(raiz, "extraido", "GRAPHICS", "*", "*.TEX"))):
        nuevo, n = recolorear_tex(open(ruta, "rb").read())
        if n:
            res[os.path.relpath(ruta, os.path.join(raiz, "extraido"))] = nuevo
            print(f"  {os.path.basename(ruta)}: {n} paletas")
    return res


if __name__ == "__main__" and sys.argv[1:] == ["probar"]:
    from emu import RAIZ, Emu
    from explorar import CUE, estado
    with Emu(iso=CUE, log="mod_ropa.log", extra=("-fastboot",)) as e:
        e.cargar(estado("saltar"))
        e.esperar(4)
        e.eval("PCSX.pauseEmulator(); return 'ok'")
        vram = e.vram()
        e.eval("PCSX.resumeEmulator(); return 'ok'")
        # la mitad derecha de la VRAM es el .TEX del nivel: se recolorea y se sube de nuevo
        mitad = b"".join(vram[(y * 1024 + 512) * 2:(y * 1024 + 1024) * 2] for y in range(512))
        nuevo, n = recolorear_tex(mitad)
        print(n, "paletas cambiadas en la VRAM del HUB")
        for y in range(FILA_DESDE, 512):
            e.escribir_vram(512, y, 512, 1, nuevo[y * 1024:(y + 1) * 1024])
        e.esperar(2)
        print(e.captura(os.path.join(RAIZ, r"notas\capturas\mod_ropa_vivo.png")))
