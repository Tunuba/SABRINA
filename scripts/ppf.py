"""Parches PPF 3.0, el formato clasico de la escena de PS1, para compartir un mod sin compartir el juego.

Uso
  python ppf.py crear  original.bin modificado.bin salida.ppf "descripcion"
  python ppf.py aplicar original.bin parche.ppf salida.bin
  python ppf.py probar  original.bin modificado.bin   (crea, aplica y compara byte a byte)

Se aplica sobre la pista 1 (la de datos) de la imagen Redump. Tambien lo abren PPF-O-Matic y
los emuladores que cargan .ppf junto al .cue.

Formato: cabecera "PPF30", metodo 2, descripcion de 50 bytes, tipo de imagen (0 = BIN), bloque de
validacion (1 = se incluyen 1024 bytes del disco original en 0x9320 para comprobar que el parche
va sobre el disco correcto), undo 0, relleno 0; luego registros de desplazamiento de 8 bytes, largo
de 1 byte y los datos.
"""
import sys

VALIDACION = 0x9320


def crear(original, modificado, salida, descripcion="Mod de Sabrina"):
    a, b = open(original, "rb").read(), open(modificado, "rb").read()
    if len(a) != len(b):
        raise ValueError("las dos imagenes deben medir lo mismo")
    cab = bytearray(b"PPF30")
    cab.append(2)
    cab += descripcion.encode("ascii", "replace")[:50].ljust(50, b" ")
    cab += bytes((0, 1, 0, 0))
    cab += a[VALIDACION:VALIDACION + 1024]
    registros = bytearray()
    i, n, cambios = 0, len(a), 0
    # Se compara por bloques grandes con memoria compartida para no ir byte a byte en todo el disco
    paso = 1 << 16
    for base in range(0, n, paso):
        if a[base:base + paso] == b[base:base + paso]:
            continue
        i = base
        fin = min(base + paso, n)
        while i < fin:
            if a[i] == b[i]:
                i += 1
                continue
            j = i
            while j < fin and j - i < 255 and a[j] != b[j]:
                j += 1
            registros += i.to_bytes(8, "little") + bytes((j - i,)) + b[i:j]
            cambios += j - i
            i = j
    with open(salida, "wb") as f:
        f.write(cab + registros)
    return cambios, len(cab) + len(registros)


def aplicar(original, parche, salida):
    p = open(parche, "rb").read()
    if p[:5] != b"PPF30":
        raise ValueError("no es un PPF 3.0")
    datos = bytearray(open(original, "rb").read())
    pos = 60
    if p[57] == 1:
        if bytes(datos[VALIDACION:VALIDACION + 1024]) != p[60:1084]:
            raise ValueError("el parche no corresponde a este disco (fallo el bloque de validacion)")
        pos = 1084
    while pos < len(p):
        if p[pos:pos + 4] == b"@BEG":       # descripcion larga opcional al final
            break
        off = int.from_bytes(p[pos:pos + 8], "little")
        largo = p[pos + 8]
        datos[off:off + largo] = p[pos + 9:pos + 9 + largo]
        pos += 9 + largo
    open(salida, "wb").write(datos)


if __name__ == "__main__":
    modo = sys.argv[1]
    if modo == "crear":
        c, t = crear(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5] if len(sys.argv) > 5 else "Mod de Sabrina")
        print(f"{c} bytes cambiados, parche de {t} bytes")
    elif modo == "aplicar":
        aplicar(sys.argv[2], sys.argv[3], sys.argv[4])
    elif modo == "probar":
        import os
        import tempfile
        tmp = tempfile.mkdtemp()
        c, t = crear(sys.argv[2], sys.argv[3], os.path.join(tmp, "p.ppf"))
        aplicar(sys.argv[2], os.path.join(tmp, "p.ppf"), os.path.join(tmp, "r.bin"))
        igual = open(os.path.join(tmp, "r.bin"), "rb").read() == open(sys.argv[3], "rb").read()
        print(f"{c} bytes cambiados, parche de {t} bytes, aplicado igual al modificado: {igual}")
