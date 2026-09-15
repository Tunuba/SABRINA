"""Saca los sonidos de los bancos VAB de la PS1 (SOUND\\*\\*.VHD + .VBD) a WAV.

VHD (cabecera, formato estandar de Sony): "pBAV", version, id, tamano, 2 reservados, cantidad de programas,
de tonos y de muestras VAG, volumen, paneo y atributos; luego 128 programas de 16 bytes, 16 tonos de 32
bytes por programa, y una tabla de 256 uint16 con el tamano de cada muestra dividido por 8 (la entrada 0
no se usa). VBD: las muestras VAG seguidas, en ADPCM de la SPU: bloques de 16 bytes (filtro y
desplazamiento, banderas, 28 muestras de 4 bits).

Uso: python vab.py H1W          sonidos de un nivel en notas\\sonidos\\<nivel>\\
     python vab.py todos
La frecuencia real depende de la nota con que el juego toque cada muestra; se guardan a 22050 Hz.
"""
import glob
import os
import struct
import sys
import wave

RAIZ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FILTROS = [(0, 0), (60, 0), (115, -52), (98, -55), (122, -60)]


def adpcm(datos):
    """Decodifica ADPCM de la SPU a muestras de 16 bits."""
    out = []
    s1 = s2 = 0
    for b in range(0, len(datos) - 15, 16):
        cab, banderas = datos[b], datos[b + 1]
        desp, filtro = cab & 0x0F, min(cab >> 4, 4)
        f0, f1 = FILTROS[filtro]
        for k in range(28):
            byte = datos[b + 2 + k // 2]
            n = (byte >> ((k & 1) * 4)) & 0x0F
            if n >= 8:
                n -= 16
            v = (n << 12) >> desp
            v += (s1 * f0 + s2 * f1 + 32) >> 6
            v = max(-32768, min(32767, v))
            out.append(v)
            s2, s1 = s1, v
        if banderas & 1 and b + 16 >= len(datos):
            break
    return out


def leer_vab(vhd, vbd):
    h = open(vhd, "rb").read()
    if h[:4] != b"pBAV":
        raise ValueError(f"{vhd} no empieza con pBAV")
    progs, tonos, vags = struct.unpack_from("<HHH", h, 0x12)
    tabla = 0x20 + 128 * 16 + progs * 16 * 32
    tam = struct.unpack_from("<256H", h, tabla)
    b = open(vbd, "rb").read()
    muestras, p = [], 0
    for k in range(1, vags + 1):
        n = tam[k] * 8
        muestras.append(b[p:p + n])
        p += n
    return dict(programas=progs, tonos=tonos, vags=vags, muestras=muestras, sobra=len(b) - p)


def guardar(nivel):
    carpeta = {"FR": "FRONT", "H1": "HUB", "C1": "CHAOS", "S": "STONE", "E": "EGYPT", "J": "JAPAN", "W": "WEST"}
    c = carpeta.get(nivel[:2]) or carpeta[nivel[0]]
    base = os.path.join(RAIZ, "extraido", "SOUND", c, nivel)
    v = leer_vab(base + ".VHD", base + ".VBD")
    sal = os.path.join(RAIZ, "notas", "sonidos", nivel)
    os.makedirs(sal, exist_ok=True)
    for k, m in enumerate(v["muestras"]):
        pcm = adpcm(m)
        with wave.open(os.path.join(sal, f"{nivel}_{k:03d}.wav"), "wb") as w:
            w.setnchannels(1)
            w.setsampwidth(2)
            w.setframerate(22050)
            w.writeframes(struct.pack(f"<{len(pcm)}h", *pcm))
    print(f"{nivel}: {v['programas']} programas, {v['tonos']} tonos, {v['vags']} muestras, sobran {v['sobra']} bytes"
          f" del VBD -> {sal}")


if __name__ == "__main__":
    if sys.argv[1] == "todos":
        for vhd in sorted(glob.glob(os.path.join(RAIZ, "extraido", "SOUND", "*", "*.VHD"))):
            guardar(os.path.splitext(os.path.basename(vhd))[0])
    else:
        guardar(sys.argv[1])
