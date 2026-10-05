# Caso que ninguna captura de func_80017D80 recorre: un archivo de un solo sector (WRLDDATA\FRONT\FRW.BIN, 368
# bytes), donde primero == ultimo. Corre la captura real 00 con ese nombre en la original, en el C y en el mutante
# `<` por `<=` de la linea del `if ((u32) ultimo < (u32) primero)`, que paso la prueba de mutantes (05-10).
# uso (desde decomp, en WSL con el venv): python3 verif/caso17d80.py
import os
import sys
import tempfile

sys.path.insert(0, os.getcwd())
import verificar as V

F = "func_80017D80"
C = "src/File/archivo_entero_g14.c"
base = f"capturas/{F}/00"
regs = [int(x, 16) for x in open(base + ".regs").read().split()]
nombre = regs[4] & 0x1FFFFF
sim = V.simbolos()
V.PILA_LOCAL["bytes"] = 0x4000

texto = open(C).read()
viejo = "if ((u32) ultimo < (u32) primero) {"
assert texto.count(viejo) == 1
mutante = os.path.join(tempfile.mkdtemp(), "mutante.c")
open(mutante, "w").write(texto.replace(viejo, "if ((u32) ultimo <= (u32) primero) {"))

for archivo in (b"WRLDDATA\\FRONT\\FRW.BIN", b"GRAPHICS\\Stone\\S3.pic"):
    parche = {nombre: archivo + b"\0"}
    a = V.ejecutar(base, sim[F], None, None, parche)
    print(f"== {archivo.decode()}: original error={a['error']} v0={a.get('v0', 0):08x}")
    for etiqueta, fuente in (("C", C), ("mutante", mutante)):
        codigo, dirs = V.compilar(fuente, [F])
        b = V.ejecutar(base, dirs[F], codigo, None, parche)
        d = V.comparar(a, b, a["sp"])
        print(f"   {etiqueta}: {'IGUAL' if not d else 'DISTINTO ' + '; '.join(d)}")
