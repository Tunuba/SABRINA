"""Auditoria del C escrito a mano: verifica TODAS las funciones de src/<modulo>/*.c (no src/auto) y deja el
resultado real de cada una, sin creerle a ningun reporte anterior.

Salida: ../notas/fases/auditoria.tsv (funcion, bytes, estado, archivo, detalle) y un resumen con el porcentaje
del codigo del juego que queda verificado sumando el lote automatico (progreso.tsv) y lo escrito a mano.

Uso: python3 auditar.py [--procesos N] [--tope segundos por archivo]
"""
import argparse
import glob
import os
import re
import subprocess
from concurrent.futures import ThreadPoolExecutor, as_completed

AQUI = os.path.dirname(os.path.abspath(__file__))
SALIDA = os.path.join(AQUI, "..", "notas", "fases", "auditoria.tsv")
TOTAL = 293812                                  # bytes de codigo del juego (funciones_juego.tsv)
DEF = re.compile(r"^(?!extern\b)\w[\w\s\*]*?\b(\w+)\([^;]*$", re.M)   # la misma que usa auto.py
FIN = re.compile(r"^(\w+): (.*?)(?: -> (\w+))?$")

tam = {l.split()[2]: int(l.split()[1]) for l in open(os.path.join(AQUI, "funciones_juego.tsv"))}


def funciones_de(c):
    return [f for f in dict.fromkeys(DEF.findall(open(c).read())) if f in tam]


def verificar(c, funcs, tope):
    try:
        r = subprocess.run(["python3", "verificar.py", c, *funcs], cwd=AQUI, capture_output=True, text=True,
                           timeout=tope)
        texto = r.stdout + r.stderr
    except subprocess.TimeoutExpired as e:
        texto = (e.stdout or b"").decode("utf-8", "replace") if isinstance(e.stdout, bytes) else (e.stdout or "")
        texto += "\nTOPE_DE_TIEMPO"
    res = {}
    for l in texto.splitlines():
        m = FIN.match(l)
        if m and m.group(1) in funcs:
            f, det, est = m.groups()
            if est is None:
                est = "SIN_CAPTURAS" if "sin capturas" in det else "NO_ESTA" if "no esta" in det else None
            if est:
                res[f] = (est, det)
    for f in funcs:
        if f not in res:
            if "TOPE_DE_TIEMPO" in texto:
                res[f] = ("TOPE_DE_TIEMPO", "la verificacion no termino a tiempo")
            elif "error" in texto.lower():
                err = next((l for l in texto.splitlines() if "error" in l.lower()), "")
                res[f] = ("NO_COMPILA", err.strip()[:200])
            else:
                res[f] = ("SIN_RESULTADO", texto.strip().splitlines()[-1][:200] if texto.strip() else "")
    return c, res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--procesos", type=int, default=8)
    ap.add_argument("--tope", type=int, default=1200)
    a = ap.parse_args()
    trabajos = []
    for c in sorted(glob.glob(os.path.join("src", "*", "*.c"), root_dir=AQUI)):
        if os.sep + "auto" + os.sep in os.sep + c:
            continue
        fs = funciones_de(os.path.join(AQUI, c))
        if fs:
            trabajos.append((c, fs))
    print(f"{sum(len(f) for _, f in trabajos)} funciones en {len(trabajos)} archivos", flush=True)
    filas = []
    with ThreadPoolExecutor(a.procesos) as ex:
        for fut in as_completed([ex.submit(verificar, c, fs, a.tope) for c, fs in trabajos]):
            c, res = fut.result()
            for f, (est, det) in res.items():
                filas.append((f, tam[f], est, c, det))
                print(f"{est:14s} {f} ({c})", flush=True)
    filas.sort(key=lambda r: (r[2], r[0]))
    os.makedirs(os.path.dirname(SALIDA), exist_ok=True)
    with open(SALIDA, "w") as s:
        s.write("funcion\tbytes\testado\tarchivo\tdetalle\n")
        for r in filas:
            s.write("\t".join(str(x) for x in r) + "\n")
    # porcentaje: lo IGUAL a mano mas lo IGUAL del lote que no este tambien a mano
    mano_ok = {f for f, _, e, _, _ in filas if e in ("IGUAL", "IGUAL_V0")}
    lote_ok = set()
    for l in list(open(os.path.join(AQUI, "progreso.tsv")))[1:]:
        p = l.rstrip("\n").split("\t")
        if p[2] in ("IGUAL", "IGUAL_V0"):
            lote_ok.add(p[0])
    todo = mano_ok | lote_ok
    b = sum(tam[f] for f in todo)
    cuenta = {}
    for r in filas:
        cuenta[r[2]] = cuenta.get(r[2], 0) + 1
    print("a mano: " + ", ".join(f"{k} {v}" for k, v in sorted(cuenta.items())))
    print(f"VERIFICADO EN TOTAL: {len(todo)} funciones, {b} de {TOTAL} bytes = {100 * b / TOTAL:.1f} %")


if __name__ == "__main__":
    main()
