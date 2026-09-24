"""Recolorea el traje default de Sabrina (el del HUB) a un estilo de bruja de comic: camisa
roja, piel clara (color piel, no blanco), pelo blanco y pantalon y zapatos negros.

mod_rosa.py encontraba sus cuatro paletas buscando en la RAM en vivo (gpu_paquetes.py); esta
version en cambio lee los nodos del .INO (ino.py) para saber, hueso por hueso, que indice de
textura usa cada parte del cuerpo, y el registro de esa textura (h6 TPAGE, h7 CLUT) para ubicar
su paleta en la VRAM. Asi salio que en el HUB hay ocho paletas de 16 colores seguidas en la fila
472 -no tres como se pensaba- y que las etiquetas de mod_rosa.py estaban mezcladas: lo que
llamaba "cadera" era en realidad un borde fino de la cintura, y "brazo" era la paleta de las
manos. La paleta de pelo/cabeza (512,473, 256 colores) es la misma que mod_rosa.py ya usaba, y
ademas resulta compartida por las cabezas de los otros trajes (japan, stone, west) y por las
manos del traje stone: cambiarla los deja a todos con el pelo/piel parejos de paso.

Esa paleta trae la cara Y el pelo mezclados en el mismo rango de indices (son la misma rampa de
marrones), asi que no alcanza con un solo tono para toda la paleta si se quiere pelo blanco pero
cara color piel: hay que mirar cada color por separado. Los tonos de pelo son bien amarillos (el
azul mucho mas bajo que el rojo y el verde); los de piel/sombra son mas parejos entre los tres
canales. Separarlos asi y pintar cada grupo aparte se probo contra el modelo 3D (ino_obj.py con
una paleta de prueba en rojo/azul) y calzo perfecto: el pelo entero salio de un color y la cara
del otro, sin mezcla.

Mapa comprobado (SABdefaultHips, SABdefaultChest y sus hijos en H1W.INO; ver
scripts\\ino_obj.py Texturas):
  zapatos (envion -32), piernas (ancla), borde de cintura (+32), cadera (+64): pantalon y calzado
  manos (+96), brazos (+128): piel
  camisa_detalle (+160), camisa (+192): tela de la camisa (exclusivas del torso)
El borde de cintura y la cadera los usan tanto las piernas como la camisa (es la costura donde se
unen): pintarlos de negro los deja de cinto, separando la camisa roja de la pollera negro en vez
de chocar contra el rojo. Comprobado en HUB, Stone 1, Egypt 2 y West 3 que piernas/borde/cadera/
manos/brazos/camisa_detalle son identicos byte a byte; zapatos y camisa solo se comprobaron en el
HUB (el traje default no se dibuja en los otros niveles, esas filas pueden traer otra cosa) -por
eso conviene mirar la captura de `probar` antes de creer del todo en el resultado fuera del HUB.

Dos formas de probarlo, igual que mod_rosa.py:
  python mod_bruja.py probar    cambia las paletas en vivo en el HUB (necesita el estado 'saltar',
                                 se crea con explorar.py/ir_a_nivel.py) y deja una captura en
                                 notas\\capturas\\mod_bruja_vivo.png. No toca ningun archivo del disco.
  python mod_bruja.py disco     arma disco\\sabrina_bruja (Track 01).bin y mods\\sabrina_bruja.ppf,
                                 recoloreando los 14 .TEX (necesita extraido\\, que deja -Taller)
"""
import glob
import os
import struct
import sys

from mod_rosa import PIERNAS, FILA_DESDE

# desplazamiento en bytes desde el ancla de piernas, medido en H1W.TEX (ver el docstring)
OFFSETS = {
    "zapatos": -32,
    "piernas": 0,
    "borde_cintura": 32,
    "cadera": 64,
    "manos": 96,
    "brazos": 128,
    "camisa_detalle": 160,
    "camisa": 192,
}


def _tono(v, r, g, b):
    if v & 0x7FFF == 0:
        return v
    return (v & 0x8000) | r | (g << 5) | (b << 10)


def a_negro(v):
    """Un color de 15 bits a un negro con algo de relieve (la GPU igual lo multiplica por la luz
    del vertice, no hace falta guardar el negro puro)."""
    r, g, b = v & 31, (v >> 5) & 31, (v >> 10) & 31
    n = max(r, g, b) // 4
    return _tono(v, n, n, n)


def a_rojo(v):
    """Un color de 15 bits a un rojo saturado con el mismo brillo."""
    r, g, b = v & 31, (v >> 5) & 31, (v >> 10) & 31
    brillo = max(r, g, b)
    return _tono(v, brillo, brillo // 5, brillo // 8)


def a_blanco(v):
    """Un color de 15 bits a un blanco platino: hasta las sombras quedan claras. Para el pelo."""
    r, g, b = v & 31, (v >> 5) & 31, (v >> 10) & 31
    n = min(31, 16 + max(r, g, b))
    return _tono(v, n, n, n)


def a_piel(v):
    """Un color de 15 bits a un tono piel claro (calido, no gris), con el mismo brillo. Para la
    piel (cara, manos, brazos)."""
    r, g, b = v & 31, (v >> 5) & 31, (v >> 10) & 31
    brillo = max(r, g, b)
    return _tono(v, min(31, 20 + brillo // 3), min(31, 15 + brillo // 3), min(31, 11 + brillo // 3))


def es_pelo(v):
    """True si este color de la paleta de cabeza es del pelo (dorado, el azul bien por debajo del
    rojo y el verde) y no de la piel/sombra (los tres canales mas parejos)."""
    r, g, b = v & 31, (v >> 5) & 31, (v >> 10) & 31
    return max(r, g, b) > 3 and b < r * 0.65 and b < g * 0.65


TRANSFORMA = {
    "zapatos": a_negro, "piernas": a_negro, "borde_cintura": a_negro, "cadera": a_negro,
    "manos": a_piel, "brazos": a_piel,
    "camisa_detalle": a_rojo, "camisa": a_rojo,
}


def recolorear_tex(datos):
    """Devuelve (datos nuevos, encontrado). datos: un .TEX entero (512x512 de 16 bits, la mitad
    derecha de la VRAM)."""
    d = bytearray(datos)
    off = d.find(PIERNAS, FILA_DESDE * 1024)
    if off < 0:
        return bytes(d), False
    for nombre, delta in OFFSETS.items():
        base = off + delta
        pal = struct.unpack_from("<16H", d, base)
        struct.pack_into("<16H", d, base, *[TRANSFORMA[nombre](v) for v in pal])
    # pelo y cabeza: 256 colores (512 bytes), al principio de la fila de abajo (mismo calculo que mod_rosa.py)
    fila_inicio = off - (off % 1024)
    inicio_pelo = fila_inicio + 1024
    pal = struct.unpack_from("<256H", d, inicio_pelo)
    struct.pack_into("<256H", d, inicio_pelo, *[a_blanco(v) if es_pelo(v) else a_piel(v) for v in pal])
    return bytes(d), True


def cambios_disco(raiz):
    """{ruta en el disco: bytes} de todos los .TEX recoloreados."""
    res = {}
    for ruta in sorted(glob.glob(os.path.join(raiz, "extraido", "GRAPHICS", "*", "*.TEX"))):
        nuevo, hecho = recolorear_tex(open(ruta, "rb").read())
        if hecho:
            res[os.path.relpath(ruta, os.path.join(raiz, "extraido"))] = nuevo
            print(f"  {os.path.basename(ruta)}: look de bruja")
    return res


if __name__ == "__main__" and sys.argv[1:] == ["probar"]:
    from emu import RAIZ, Emu
    from explorar import CUE, estado
    with Emu(iso=CUE, log="mod_bruja.log", extra=("-fastboot",)) as e:
        e.cargar(estado("saltar"))
        e.esperar(4)
        e.eval("PCSX.pauseEmulator(); return 'ok'")
        vram = e.vram()
        e.eval("PCSX.resumeEmulator(); return 'ok'")
        mitad = b"".join(vram[(y * 1024 + 512) * 2:(y * 1024 + 1024) * 2] for y in range(512))
        nuevo, hecho = recolorear_tex(mitad)
        print("look de bruja" if hecho else "no se encontro la paleta de piernas")
        for y in range(FILA_DESDE, 512):
            e.escribir_vram(512, y, 512, 1, nuevo[y * 1024:(y + 1) * 1024])
        e.esperar(2)
        print(e.captura(os.path.join(RAIZ, r"notas\capturas\mod_bruja_vivo.png")))
elif __name__ == "__main__" and sys.argv[1:] == ["disco"]:
    import disco
    import ppf
    cambios = cambios_disco(disco.RAIZ)
    if not cambios:
        sys.exit("no se encontro la paleta de piernas en ningun .TEX; hace falta extraido\\ (-Taller)")
    pista = os.path.join(disco.DISCO, "sabrina_bruja (Track 01).bin")
    disco.parchar(cambios, pista)
    disco.cue_mod(os.path.join(disco.DISCO, "sabrina_bruja.cue"), pista)
    salida = os.path.join(disco.RAIZ, "mods", "sabrina_bruja.ppf")
    c, t = ppf.crear(disco.PISTA1, pista, salida, "Sabrina bruja (prueba)")
    print(f"disco {pista}")
    print(f"parche {salida}: {t} bytes, {c} bytes cambiados")
