"""Leer y parchar la imagen de disco de Sabrina sin rearmarla.

- archivos(): lee el XML de dumpsxiso (hecho con -l) y devuelve cada archivo con su sector (LBA),
  su tamano y su tipo.
- parchar(): copia la pista de datos y escribe encima los archivos cambiados, sector por sector,
  recalculando el EDC y el ECC de cada sector. Solo acepta archivos del MISMO tamano que el original,
  asi nada se mueve de sitio y el juego, que busca sus archivos por posicion, sigue encontrandolos.

Un sector de datos (modo 2 forma 1) mide 2352 bytes: 12 de sincronia, 4 de cabecera (MSF y modo),
8 de subcabecera, 2048 de datos, 4 de EDC (un CRC) y 276 de ECC (paridades P y Q).

Uso de prueba: python disco.py verificar   (recalcula EDC y ECC de sectores intactos y compara)
"""
import os
import shutil
import sys
import xml.etree.ElementTree as ET

RAIZ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DISCO = os.path.join(RAIZ, "disco")
NOMBRE = "Sabrina the Teenage Witch - A Twitch in Time! (USA)"
PISTA1 = os.path.join(DISCO, NOMBRE + " (Track 01).bin")
CUE = os.path.join(DISCO, NOMBRE + ".cue")
XML = os.path.join(RAIZ, "extraido", "sabrina.xml")
SECTOR = 2352
DATOS = 2048

# Tablas del EDC y el ECC de los CD-ROM (las mismas que usan ECM y los emuladores)
_F = [0] * 256
_B = [0] * 256
_EDC = [0] * 256
for _i in range(256):
    _j = ((_i << 1) ^ (0x11D if _i & 0x80 else 0)) & 0xFF
    _F[_i] = _j
    _B[_i ^ _j] = _i
    _e = _i
    for _ in range(8):
        _e = (_e >> 1) ^ (0xD8018001 if _e & 1 else 0)
    _EDC[_i] = _e


def edc(datos):
    e = 0
    for b in datos:
        e = (e >> 8) ^ _EDC[(e ^ b) & 0xFF]
    return e


def _ecc_bloque(s, mayor_n, menor_n, mayor_mult, menor_inc, destino):
    """Calcula una paridad (P o Q) sobre s[12:] y la escribe en s[destino:]."""
    tam = mayor_n * menor_n
    base = 12
    for mayor in range(mayor_n):
        idx = (mayor >> 1) * mayor_mult + (mayor & 1)
        a = b = 0
        for _ in range(menor_n):
            t = s[base + idx]
            idx += menor_inc
            if idx >= tam:
                idx -= tam
            a ^= t
            b ^= t
            a = _F[a]
        a = _B[_F[a] ^ b]
        s[destino + mayor] = a
        s[destino + mayor + mayor_n] = a ^ b


def sellar_forma1(s):
    """Recalcula EDC y ECC de un sector modo 2 forma 1 (bytearray de 2352)."""
    e = edc(s[16:2072])
    s[2072:2076] = e.to_bytes(4, "little")
    cab = bytes(s[12:16])
    s[12:16] = b"\0\0\0\0"          # en modo 2 la cabecera cuenta como ceros para el ECC
    _ecc_bloque(s, 86, 24, 2, 86, 2076)    # paridad P
    _ecc_bloque(s, 52, 43, 86, 88, 2248)   # paridad Q
    s[12:16] = cab


def archivos(xml=XML):
    """Devuelve {ruta: (lba, tamano, tipo)} leyendo el XML de dumpsxiso y los archivos extraidos."""
    res = {}

    def recorrer(nodo, carpeta):
        for h in nodo:
            if h.tag == "dir":
                recorrer(h, carpeta + h.get("name") + "\\")
            elif h.tag == "file" and h.get("type") != "da":
                ruta = carpeta + h.get("name")
                res[ruta] = (int(h.get("offs")), os.path.getsize(h.get("source")), h.get("type", "data"))

    arbol = ET.parse(xml).getroot()
    for pista in arbol.iter("track"):
        for dt in pista.iter("directory_tree"):
            recorrer(dt, "")
    return res


def parchar(cambios, salida_pista, pista=PISTA1):
    """Copia la pista de datos a salida_pista y reemplaza los archivos de cambios {ruta: bytes}."""
    tabla = archivos()
    for ruta, datos in cambios.items():
        lba, tam, tipo = tabla[ruta]
        if tipo != "data":
            raise ValueError(f"{ruta} es de tipo {tipo}, solo se parchan archivos de datos")
        if len(datos) != tam:
            raise ValueError(f"{ruta} mide {tam} bytes y el nuevo {len(datos)}; tiene que medir lo mismo")
    shutil.copyfile(pista, salida_pista)
    with open(salida_pista, "r+b") as f:
        for ruta, datos in cambios.items():
            lba, tam, _ = tabla[ruta]
            for i in range(0, tam, DATOS):
                f.seek((lba + i // DATOS) * SECTOR)
                s = bytearray(f.read(SECTOR))
                if s[18] & 0x20:
                    raise ValueError(f"el sector {lba + i // DATOS} de {ruta} es forma 2")
                trozo = datos[i:i + DATOS]
                s[24:24 + len(trozo)] = trozo
                sellar_forma1(s)
                f.seek((lba + i // DATOS) * SECTOR)
                f.write(s)


def cue_mod(salida_cue, pista1_mod):
    """Escribe un .cue que usa la pista de datos parchada y las pistas de audio originales.
    Tiene que quedar en la carpeta disco, junto a las pistas de audio."""
    texto = open(CUE, encoding="utf-8").read()
    texto = texto.replace(f'"{NOMBRE} (Track 01).bin"', f'"{os.path.basename(pista1_mod)}"', 1)
    open(salida_cue, "w", encoding="utf-8").write(texto)


def verificar(n=40):
    """Recalcula EDC y ECC de sectores de datos intactos y comprueba que salen iguales."""
    buenos = malos = 0
    tam = os.path.getsize(PISTA1) // SECTOR
    with open(PISTA1, "rb") as f:
        for lba in list(range(16, 16 + n // 2)) + list(range(tam // 2, tam // 2 + n // 2)):
            f.seek(lba * SECTOR)
            s = bytearray(f.read(SECTOR))
            if s[15] != 2 or s[18] & 0x20:
                continue            # solo forma 1
            original = bytes(s)
            sellar_forma1(s)
            if bytes(s) == original:
                buenos += 1
            else:
                malos += 1
    print(f"sectores forma 1 recalculados: {buenos} iguales, {malos} distintos")
    return malos == 0


if __name__ == "__main__" and sys.argv[1:] == ["verificar"]:
    verificar()
    t = archivos()
    print(len(t), "archivos de datos en el XML, por ejemplo", list(t.items())[:3])
