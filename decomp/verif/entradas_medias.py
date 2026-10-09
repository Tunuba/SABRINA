"""Busca saltos o punteros que caen en medio de una funcion reemplazada desde fuera de ella.
Una funcion reemplazada solo conserva su entrada (j al C); si algo salta a otra direccion de su cuerpo,
el armado con C la rompe. Uso: python verif/entradas_medias.py [build/armado_c.txt]"""
import os, struct, sys
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
exe = open("SLUS_012.08", "rb").read()
inst = [l.split("\t")[1] for l in open(sys.argv[1] if len(sys.argv) > 1 else "build/armado_c.txt", encoding="utf-8") if l.startswith("OK")]
tam = {}
for l in open("funciones_juego.tsv", encoding="utf-8"):
    p = l.rstrip("\n").split("\t")
    if len(p) == 3: tam[p[2]] = (int(p[0], 16), int(p[1]))
rangos = sorted((tam[f][0], tam[f][0] + tam[f][1], f) for f in inst)
import bisect
ini = [r[0] for r in rangos]
def donde(a):
    i = bisect.bisect_right(ini, a) - 1
    if i >= 0 and rangos[i][0] <= a < rangos[i][1]: return rangos[i]
base, off = 0x80010000, 0x800
n = (len(exe) - off) // 4
malos = []
for k in range(n):
    a = base + 4 * k
    w = struct.unpack_from("<I", exe, off + 4 * k)[0]
    op = w >> 26
    t = None
    if op in (2, 3): t = (a & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
    elif op in (1, 4, 5, 6, 7): t = a + 4 + (((w & 0xFFFF) ^ 0x8000) - 0x8000) * 4
    elif 0x80010000 <= w < 0x80060000 and (w & 3) == 0: t = w; op = "dato"
    else: continue
    if op == "dato": continue
    r = donde(t)
    if r and t != r[0]:
        o = donde(a)
        if not o or o[2] != r[2]:
            malos.append((hex(a), o[2] if o else "(fuera de funciones)", hex(t), r[2], op))
print(len(malos), "entradas en medio")
for m in malos[:40]: print(*m)
