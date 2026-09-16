"""Resumen de la descompilacion: cuanto codigo esta verificado, por estado y por modulo.

Junta progreso.tsv con notas/modulos.tsv (que trozo del ejecutable es cada archivo fuente original) y,
si existen, cobertura.tsv y mutantes.tsv.

Uso: python3 reporte.py
"""
import os

AQUI = os.path.dirname(os.path.abspath(__file__))
RAIZ = os.path.dirname(AQUI)


def main():
    filas = []
    for l in list(open(os.path.join(AQUI, "progreso.tsv")))[1:]:
        p = l.rstrip("\n").split("\t")
        filas.append((p[0], int(p[1]), p[2]))
    dirs = {}
    for l in open(os.path.join(AQUI, "funciones_juego.tsv")):
        d, tam, nom = l.split()
        dirs[nom] = int(d, 16)
    modulos = []
    for l in list(open(os.path.join(RAIZ, "notas", "modulos.tsv")))[1:]:
        p = l.split("\t")
        modulos.append((int(p[0], 16), int(p[1], 16), p[2]))

    def modulo(nom):
        d = dirs.get(nom, 0)
        for ini, fin, m in modulos:
            if ini <= d < fin:
                return m
        return "?"

    from collections import Counter, defaultdict
    estados = Counter(f[2] for f in filas)
    bytes_estado = defaultdict(int)
    for _, tam, est in filas:
        bytes_estado[est] += tam
    total = sum(f[1] for f in filas)
    hechas = sum(b for e, b in bytes_estado.items() if e in ("IGUAL", "YA_HECHA"))
    print(f"{sum(estados[e] for e in ('IGUAL', 'YA_HECHA'))} funciones verificadas de {len(filas)}; "
          f"{hechas} de {total} bytes ({100 * hechas / max(total, 1):.1f} %)")
    for e, n in estados.most_common():
        print(f"  {e:13s} {n:4d} funciones {bytes_estado[e]:7d} bytes")
    print("\npor modulo (verificado / total de bytes):")
    por_mod = defaultdict(lambda: [0, 0])
    for nom, tam, est in filas:
        m = por_mod[modulo(nom)]
        m[1] += tam
        if est in ("IGUAL", "YA_HECHA"):
            m[0] += tam
    for m, (ok, tot) in sorted(por_mod.items(), key=lambda x: -x[1][1]):
        print(f"  {m:18s} {ok:6d} / {tot:6d}  {100 * ok / max(tot, 1):5.1f} %")
    for nombre, archivo, columna in (("cobertura", "cobertura.tsv", 3), ("mutantes muertos", "mutantes.tsv", 2)):
        ruta = os.path.join(AQUI, archivo)
        if not os.path.exists(ruta):
            continue
        lineas = [l.rstrip("\n").split("\t") for l in list(open(ruta))[1:]]
        if not lineas:
            continue
        if nombre == "cobertura":
            flojas = [(l[0], int(l[3])) for l in lineas if int(l[3]) < 100]
            print(f"\ncobertura: {len(lineas) - len(flojas)} de {len(lineas)} funciones se recorren enteras")
            for nom, pc in sorted(flojas, key=lambda x: x[1])[:15]:
                print(f"  {nom:28s} {pc:3d} %")
        else:
            vivos = [(l[0], int(l[2]), int(l[3])) for l in lineas if int(l[2]) < int(l[3])]
            print(f"\nmutantes: {len(lineas) - len(vivos)} de {len(lineas)} funciones matan todos los suyos")
            for nom, m, t in vivos[:15]:
                print(f"  {nom:28s} {m} de {t}")


if __name__ == "__main__":
    main()
