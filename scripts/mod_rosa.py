"""Prueba: pinta de rosa las cuatro paletas conocidas de Sabrina (piernas, cadera, brazo y
pelo/cabeza), para ver si es posible recolorear todo el personaje. Mismo metodo que mod_ropa.py
(pantalon azul), pero cambiando toda la paleta en vez de solo los naranjas.

Como se ubican: gpu_paquetes.py y probar_paletas.py ya identificaron, en el HUB, piernas (832,472),
cadera (864,472) y brazo (896,472) -tres paletas de 16 colores seguidas en la misma fila de la VRAM,
32 bytes cada una- y pelo/cabeza (512,473), de 256 colores, al principio de la fila siguiente.
mod_ropa.py ya probo que la paleta de las piernas es identica, byte a byte, en los 14 .TEX del juego
(solo cambia de posicion); como las otras tres paletas estan pegadas a ella en el mismo bloque, se
ubican en relacion a esa ancla en vez de buscarlas cada una por separado. Lo de piernas/cadera/brazo
esta comprobado (son ese mismo bloque que ya uso mod_ropa.py); lo de pelo/cabeza, al depender de que
la fila de abajo empiece siempre en la columna 0, es una suposicion: conviene mirar la captura de
`probar` antes de creerselo del todo.

Dos formas de probarlo, de menos a mas permanente:
  python mod_rosa.py probar     cambia las paletas en vivo en el HUB (necesita el estado 'saltar',
                                 se crea con explorar.py/ir_a_nivel.py) y deja una captura en
                                 notas\\capturas\\mod_rosa_vivo.png. No toca ningun archivo del disco.
  python mod_rosa.py disco      arma disco\\sabrina_rosa (Track 01).bin y mods\\sabrina_rosa.ppf,
                                 recoloreando los 14 .TEX (necesita extraido\\, que deja -Taller)
"""
import glob
import os
import struct
import sys

# Los 16 colores de la paleta de las piernas, iguales en los 14 niveles (de mod_ropa.py).
PIERNAS = struct.pack("<16H", 0x04AD, 0x048C, 0x08CF, 0x08AE, 0x048B, 0x048A, 0x0CCF, 0x2990,
                      0x2570, 0x256F, 0x214E, 0x0CEF, 0x10EF, 0, 0, 0)
FILA_DESDE = 448


def a_rosa(v):
    """Un color de 15 bits de la PS1 a un tono rosado con el mismo brillo. 0 y la semitransparencia
    quedan igual."""
    if v & 0x7FFF == 0:
        return v
    r, g, b = v & 31, (v >> 5) & 31, (v >> 10) & 31
    brillo = max(r, g, b)
    nr, ng, nb = brillo, (brillo * 3) // 10, (brillo * 7) // 10
    return (v & 0x8000) | nr | (ng << 5) | (nb << 10)


def recolorear_tex(datos):
    """Devuelve (datos nuevos, encontrado). datos: un .TEX entero (512x512 de 16 bits, la mitad
    derecha de la VRAM)."""
    d = bytearray(datos)
    off = d.find(PIERNAS, FILA_DESDE * 1024)
    if off < 0:
        return bytes(d), False
    # piernas, cadera y brazo: tres paletas de 16 colores (32 bytes) seguidas en la misma fila.
    for base in (off, off + 32, off + 64):
        pal = struct.unpack_from("<16H", d, base)
        struct.pack_into("<16H", d, base, *[a_rosa(v) for v in pal])
    # pelo y cabeza: 256 colores (512 bytes), al principio de la fila de abajo.
    fila_inicio = off - (off % 1024)
    inicio_pelo = fila_inicio + 1024
    pal = struct.unpack_from("<256H", d, inicio_pelo)
    struct.pack_into("<256H", d, inicio_pelo, *[a_rosa(v) for v in pal])
    return bytes(d), True


def cambios_disco(raiz):
    """{ruta en el disco: bytes} de todos los .TEX recoloreados."""
    res = {}
    for ruta in sorted(glob.glob(os.path.join(raiz, "extraido", "GRAPHICS", "*", "*.TEX"))):
        nuevo, hecho = recolorear_tex(open(ruta, "rb").read())
        if hecho:
            res[os.path.relpath(ruta, os.path.join(raiz, "extraido"))] = nuevo
            print(f"  {os.path.basename(ruta)}: piernas, cadera, brazo y pelo a rosa")
    return res


if __name__ == "__main__" and sys.argv[1:] == ["probar"]:
    from emu import RAIZ, Emu
    from explorar import CUE, estado
    with Emu(iso=CUE, log="mod_rosa.log", extra=("-fastboot",)) as e:
        e.cargar(estado("saltar"))
        e.esperar(4)
        e.eval("PCSX.pauseEmulator(); return 'ok'")
        vram = e.vram()
        e.eval("PCSX.resumeEmulator(); return 'ok'")
        mitad = b"".join(vram[(y * 1024 + 512) * 2:(y * 1024 + 1024) * 2] for y in range(512))
        nuevo, hecho = recolorear_tex(mitad)
        print("piernas, cadera, brazo y pelo a rosa" if hecho else "no se encontro la paleta de piernas")
        for y in range(FILA_DESDE, 512):
            e.escribir_vram(512, y, 512, 1, nuevo[y * 1024:(y + 1) * 1024])
        e.esperar(2)
        print(e.captura(os.path.join(RAIZ, r"notas\capturas\mod_rosa_vivo.png")))
elif __name__ == "__main__" and sys.argv[1:] == ["disco"]:
    import disco
    import ppf
    cambios = cambios_disco(disco.RAIZ)
    if not cambios:
        sys.exit("no se encontro la paleta de piernas en ningun .TEX; hace falta extraido\\ (-Taller)")
    pista = os.path.join(disco.DISCO, "sabrina_rosa (Track 01).bin")
    disco.parchar(cambios, pista)
    disco.cue_mod(os.path.join(disco.DISCO, "sabrina_rosa.cue"), pista)
    salida = os.path.join(disco.RAIZ, "mods", "sabrina_rosa.ppf")
    c, t = ppf.crear(disco.PISTA1, pista, salida, "Sabrina rosa (prueba)")
    print(f"disco {pista}")
    print(f"parche {salida}: {t} bytes, {c} bytes cambiados")
