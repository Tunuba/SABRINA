"""Compara dos imagenes de disco de 2352 bytes por sector y dice que sectores cambian y donde.

Uso: python comparar_discos.py a.bin b.bin
En cada sector distinto indica si la diferencia cae en la cabecera (0-23), en los datos de usuario
(24-2071, modo 2 forma 1) o en el codigo de correccion EDC/ECC (2072-2351).
"""
import sys


def comparar(ra, rb, mostrar=20):
    a, b = open(ra, "rb").read(), open(rb, "rb").read()
    print(f"tamanos {len(a)} y {len(b)}, sectores {len(a) // 2352} y {len(b) // 2352}")
    distintos = []
    for s in range(min(len(a), len(b)) // 2352):
        x, y = a[s * 2352:(s + 1) * 2352], b[s * 2352:(s + 1) * 2352]
        if x != y:
            pos = [i for i in range(2352) if x[i] != y[i]]
            zonas = sorted({"cabecera" if i < 24 else "datos" if i < 2072 else "edc/ecc" for i in pos})
            distintos.append((s, len(pos), zonas, pos[:6]))
    print(f"{len(distintos)} sectores distintos")
    for s, n, zonas, pos in distintos[:mostrar]:
        print(f"  lba {s:6d}  {n:4d} bytes  {','.join(zonas):22s} primeros {pos}")
    return distintos


if __name__ == "__main__":
    comparar(sys.argv[1], sys.argv[2])
