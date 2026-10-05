# Casos que ninguna captura de func_80017D80 recorre, sobre la captura real 00:
# - un archivo de un solo sector (WRLDDATA\FRONT\FRW.BIN, 368 bytes), donde primero == ultimo;
# - CdControl (func_80029D28) o CdRead que fallan siempre: en la RAM de la captura se cambia su primera
#   instruccion por `jr ra; move v0, zero`, para la original y para el C por igual (el modelo del CD nunca falla).
# Corre la original, el C y los mutantes del cuerpo que pasaron la prueba de mutantes (05-10).
# uso (desde decomp, en WSL con el venv): python3 verif/caso17d80.py
import os
import sys
import tempfile

sys.path.insert(0, os.getcwd())
import mutantes as M
import verificar as V

F = "func_80017D80"
C = "src/File/archivo_entero_g14.c"
VIVOS = ("< por <= (linea 60)", "sin la linea `Liberar(datos);` (linea 73)", "sin la linea `Liberar(datos);` (linea 86)",
         "0 por 1 (linea 76)", "0 por 1 (linea 87)")
base = f"capturas/{F}/00"
regs = [int(x, 16) for x in open(base + ".regs").read().split()]
nombre = regs[4] & 0x1FFFFF
sim = V.simbolos()
V.PILA_LOCAL["bytes"] = 0x4000
FALLA = bytes.fromhex("0800e003" "21100000")      # jr ra; addu v0, zero, zero

texto = open(C).read()
fuentes = [("C", C)]
for t, que in M.mutantes(texto, "cargar_entero"):
    if que in VIVOS:
        p = os.path.join(tempfile.mkdtemp(), "mutante.c")
        open(p, "w").write(t)
        fuentes.append(("mutante " + que, p))
compilados = [(e, V.compilar(f, [F])) for e, f in fuentes]

casos = [
    ("un sector", {nombre: b"WRLDDATA\\FRONT\\FRW.BIN\0"}),
    ("CdControl falla", {sim["func_80029D28"] & 0x1FFFFF: FALLA}),
    ("CdRead falla", {sim["CdRead"] & 0x1FFFFF: FALLA}),
    ("captura tal cual", {}),
]
for caso, parche in casos:
    a = V.ejecutar(base, sim[F], None, None, parche)
    print(f"== {caso}: original error={a['error']} v0={a.get('v0', 0):08x}")
    for etiqueta, (codigo, dirs) in compilados:
        b = V.ejecutar(base, dirs[F], codigo, None, parche)
        d = V.comparar(a, b, a["sp"])
        print(f"   {etiqueta}: {'IGUAL' if not d else 'DISTINTO ' + '; '.join(d)}")
