"""Descompilacion automatica en lote: borrador de m2c, arreglos mecanicos, compilacion y verificacion.

Para cada funcion del juego con capturas:
  1. m2c genera C con un contexto donde cada dato del juego es `extern u8 NOMBRE[];` (asi m2c escribe los
     accesos con el ancho exacto de cada lectura) y juego.h.
  2. Se arreglan cosas mecanicas: tipos desconocidos `?` pasan a s32.
  3. Se compila y se verifica con verificar.py (capturas reales y variantes de argumentos).
Resultado en progreso.tsv: funcion, tamano, estado, detalle. Estados: IGUAL, DISTINTO, NO_COMPILA,
M2C_FALLA, SIN_CAPTURAS, GTE (usa el coprocesador geometrico, Unicorn no lo emula), YA_HECHA (ya hay C
escrito a mano en src/ y no se toca).
Los borradores quedan en src/auto/<funcion>.c; los que dan IGUAL se pueden pasar al modulo que toque.

Uso: python3 auto.py [--solo Funcion,...] [--max-tam bytes] [--procesos n]
"""
import argparse
import glob
import os
import re
import subprocess
import sys
from concurrent.futures import ProcessPoolExecutor, as_completed

AQUI = os.path.dirname(os.path.abspath(__file__))
M2C = os.path.expanduser("~/decomp-herramientas/m2c/m2c.py")
CONTEXTO = os.path.join(AQUI, "build", "contexto_auto.h")


def armar_contexto():
    """Contexto para m2c: tipos de juego.h y cada dato del ELF como arreglo de bytes."""
    sal = subprocess.run(["mipsel-linux-gnu-nm", os.path.join(AQUI, "build/slus_012.08.elf")],
                         capture_output=True, text=True).stdout
    datos = set()
    for l in sal.splitlines():
        p = l.split()
        if len(p) == 3 and p[1] in "dDbBrRsSgGvVAa" and re.fullmatch(r"[A-Za-z_]\w*", p[2]) and "." not in p[2]:
            datos.add(p[2])
    tipos = subprocess.run(["mipsel-linux-gnu-cpp", "-P", "-I", os.path.join(AQUI, "include"),
                            os.path.join(AQUI, "include", "juego.h")], capture_output=True, text=True).stdout
    with open(CONTEXTO, "w") as f:
        f.write(tipos)
        for d in sorted(datos):
            f.write(f"extern u8 {d}[];\n")


DATOS_M2C = os.path.join(AQUI, "build", "datos_m2c.s")


CODIGO_M2C = os.path.join(AQUI, "build", "codigo_m2c.s")


def armar_datos_m2c():
    """Copias para m2c: en los datos, las entradas de las tablas de saltos pasan a ser etiquetas de codigo
    (.L800...); en el codigo, se agrega esa etiqueta delante de cada instruccion destino. splat deja las
    entradas como numeros y no pone las etiquetas porque los datos estan en otro segmento."""
    salida, en_tabla, destinos = [], False, set()
    for l in open(os.path.join(AQUI, "asm/data/51280.data.s")):
        if l.startswith("dlabel jtbl_"):
            en_tabla = True
        elif l.startswith("enddlabel"):
            en_tabla = False
        elif en_tabla:
            m = re.search(r"\.word 0x(800[0-9A-F]{5})", l)
            if m:
                destinos.add(m.group(1))
                l = l.replace(m.group(0), f".word .L{m.group(1)}")
        salida.append(l)
    open(DATOS_M2C, "w").writelines(salida)
    codigo, puestas, final = [], set(), False
    for l in open(os.path.join(AQUI, "asm/800.s")):
        m = re.match(r"\s*\.L([0-9A-F]{8}):", l)
        if m:
            puestas.add(m.group(1))
        m = re.match(r"\s*/\* [0-9A-F]+ ([0-9A-F]{8}) ", l)
        if m and m.group(1) in destinos and m.group(1) not in puestas:
            codigo.append(f"  .L{m.group(1)}:\n")
            puestas.add(m.group(1))
        # llamada al final (`j Funcion` y su hueco): m2c no ve lo que escribe el hueco y se come argumentos;
        # se le da como `jal Funcion`, el hueco y `jr $ra`, que para el C es lo mismo (return Funcion(...))
        if re.match(r"\s*/\*.*\*/\s+j\s+[A-Za-z_]\w*\s*$", l):
            l = re.sub(r"(\*/\s+)j(\s+)", r"\1jal\2", l)
            final = True
            codigo.append(l)
            continue
        codigo.append(l)
        if final and m:
            codigo.append("    jr         $ra\n    nop\n")
            final = False
    open(CODIGO_M2C, "w").writelines(codigo)


SOLO_TIPOS = os.path.join(AQUI, "build", "solo_tipos.h")
# `static s8 D_8006553C[0xE0] = {` con el inicializador en las lineas siguientes tambien cuenta
DECL = re.compile(r"^(extern|static)\s+([\w\s\*]+?)\s*\b(\w+)\s*(\[[^\]]*\])?\s*(=.*)?(;.*|=\s*\{\s*)$")


def m2c(funcion, contexto, extra=()):
    r = subprocess.run([sys.executable, M2C, "--target", "mips-gcc-c", "--valid-syntax", "--context", contexto,
                        *extra, CODIGO_M2C, DATOS_M2C, "-f", funcion], capture_output=True, text=True)
    return r.stdout + r.stderr


def declaraciones(texto):
    """Datos que declara m2c: {nombre: (tipo, es_arreglo)}. Las variables del juego nunca son static ni
    llevan valor inicial en el C: son la memoria que ya existe."""
    res = {}
    for l in texto.splitlines():
        m = DECL.match(l.strip())
        if m and "(" not in l.split("=")[0]:
            tipo = m.group(2).strip()
            res[m.group(3)] = (tipo, bool(m.group(4)) or tipo.endswith("*") is False and "{" in (m.group(5) or ""))
    return res


PROTOTIPOS = os.path.join(AQUI, "include", "prototipos.h")


def base_contexto(funcion):
    """Tipos de juego.h y los prototipos de aridad.py (cuantos argumentos pasar en cada llamada y si lo que
    devuelven se usa). El de la propia funcion va solo si se sabe si devuelve algo (sin la marca ?); si no,
    m2c lo deduce."""
    protos = [l for l in open(PROTOTIPOS) if not (re.match(r"\w+ " + funcion + r"\(", l) and "/* ? */" in l)] \
        if os.path.exists(PROTOTIPOS) else []
    nombres = {m.group(1) for l in protos for m in [re.match(r"(?:s32|void) (\w+)\(", l)] if m}
    return open(SOLO_TIPOS).read() + "\n" + "".join(protos), nombres


def m2c_dos_pasadas(funcion, extra=()):
    """1) sin tipos de datos, para que m2c infiera el ancho de cada acceso; 2) con esos tipos y los
    desconocidos como arreglos de bytes. Devuelve (texto, declaraciones para el encabezado)."""
    base, funciones = base_contexto(funcion)
    ctx1 = os.path.join(AQUI, "build", "ctx", funcion + "_1.h")
    os.makedirs(os.path.dirname(ctx1), exist_ok=True)
    open(ctx1, "w").write(base)
    t1 = m2c(funcion, ctx1, extra)
    decl = declaraciones(t1)
    lineas = []
    for nom, (tipo, arr) in decl.items():
        if nom in funciones:
            continue                                   # es una funcion; ya tiene su prototipo
        if "M2C_UNK" in tipo or tipo in ("?", ""):
            lineas.append(f"extern u8 {nom}[];")
        else:
            lineas.append(f"extern {tipo} {nom}{'[]' if arr else ''};")
    ctx = os.path.join(AQUI, "build", "ctx", funcion + ".h")
    with open(ctx, "w") as f:
        f.write(base + "\n" + "\n".join(lineas) + "\n")
    t2 = m2c(funcion, ctx, extra)
    return t2, lineas


_funciones = None


def funciones_elf():
    global _funciones
    if _funciones is None:
        sal = subprocess.run(["mipsel-linux-gnu-nm", os.path.join(AQUI, "build/slus_012.08.elf")],
                             capture_output=True, text=True).stdout
        # en el ELF de splat los datos tambien quedan como T: las funciones son las marcadas type:func en
        # symbol_addrs.txt y las func_ que puso splat
        marcadas = set(re.findall(r"^(\w+) = 0x[0-9A-Fa-f]+; // type:func", open(os.path.join(AQUI, "symbol_addrs.txt")).read(), re.M))
        _funciones = {p[2] for p in (l.split() for l in sal.splitlines()) if len(p) == 3 and p[1] in "Tt"
                      and (p[2] in marcadas or re.fullmatch(r"func_[0-9A-F]{8}", p[2]))}
    return _funciones


DEFINICION = re.compile(r"^(static\s+)?[\w\s\*]+?\b\w+\s*(\[[^\]]*\])?\s*(=.*)?;?$")


def ensanchar_parametros(t):
    """Un parametro s8/u8/s16/u16 llega en un registro entero. GCC da por hecho que quien llama ya lo
    recorto; el codigo del juego lo recorta el mismo. Para hacer lo mismo con cualquier valor del registro,
    el parametro entra como s32 y se recorta al empezar la funcion."""
    m = re.search(r"^(\w[\w\s\*]*?\b\w+)\(([^)]*)\)\s*\{\n", t, re.M)
    if not m or m.group(2).strip() in ("", "void"):
        return t
    params, recortes = [], []
    for p in m.group(2).split(","):
        q = re.fullmatch(r"\s*(s8|u8|s16|u16)\s+(\w+)\s*", p)
        if q:
            params.append(f"s32 {q.group(2)}_reg")
            recortes.append(f"    {q.group(1)} {q.group(2)} = ({q.group(1)}) {q.group(2)}_reg;\n")
        else:
            params.append(p.strip())
    if not recortes:
        return t
    return t[:m.start()] + f"{m.group(1)}({', '.join(params)}) {{\n" + "".join(recortes) + t[m.end():]


def limpiar(texto, externas):
    lineas = []
    profundidad, en_dato = 0, False
    for l in texto.splitlines():
        s = l.strip()
        if en_dato:                                    # sigue el inicializador de un dato de varias lineas
            en_dato = not s.endswith(";")
            continue
        if profundidad == 0 and s and not s.startswith(("#", "/*", "//")) and "(" not in s.split("=")[0] \
                and DEFINICION.match(s):
            # dato del juego que m2c define con su valor inicial (`s32 D_8007CA88 = 0;`): compilado asi seria
            # una copia nueva y no la memoria del juego; va en el encabezado como extern
            en_dato = not s.endswith(";")
            continue
        afuera = profundidad == 0
        profundidad += l.count("{") - l.count("}")
        if afuera and DECL.match(s) and "(" not in s.split("=")[0]:
            continue                                   # datos: van en el encabezado como extern
        if afuera and re.match(r"^[\w\s\*]+\b\w+\s*\([^;{]*\)\s*;\s*(/\*.*\*/)?$", s):
            continue                                   # prototipos que inventa m2c (dentro de una funcion
                                                       # la misma forma es `return f(x);`)
        lineas.append(l)
    t = "\n".join(lineas)
    t = re.sub(r"(?<![\w?])\?(?![\w?])", "s32", t)             # tipos desconocidos
    t = ensanchar_parametros(t)
    cab = "\n".join(e.replace("M2C_UNK", "u8") for e in externas)
    # funciones que se usan como valor (punteros a funcion): sin declaracion no compila; se declaran sin
    # prototipo, igual que la declaracion implicita de una llamada
    definidas = set(re.findall(r"^\w[\w\s\*]*?\b(\w+)\s*\([^;]*$", t, re.M))
    como_valor = {n for n in re.findall(r"\b([A-Za-z_]\w*)\b(?!\s*\()", t) if n in funciones_elf()}
    cab += "".join(f"\nextern s32 {n}();" for n in sorted(como_valor - definidas))
    return ('#include "juego.h"\n#include "m2c_macros.h"\n#include "m2c_ajustes.h"\n\n' + cab + "\n\n" + t + "\n")


def procesar(funcion, tam):
    import verificar
    caps = glob.glob(os.path.join(AQUI, "capturas", funcion, "*.regs"))
    if not caps:
        return funcion, tam, "SIN_CAPTURAS", ""
    import io
    import contextlib
    c = os.path.join(AQUI, "src", "auto", funcion + ".c")
    os.makedirs(os.path.dirname(c), exist_ok=True)
    resultado = None
    # primero normal; si m2c falla o no compila, otra vez sin detectar switch irregulares
    for extra in ((), ("--no-switches",)):
        borrador, externas = m2c_dos_pasadas(funcion, extra)
        if "Decompilation failure" in borrador or "Internal error" in borrador or not borrador.strip():
            motivo = borrador.strip().split("\n")[-2 if borrador.strip().endswith("*/") else -1][:80]
            resultado = (funcion, tam, "M2C_FALLA", motivo)
            continue
        if re.search(r"M2C_ERROR\(/\* unknown instruction: (mtc2|mfc2|ctc2|cfc2|lwc2|swc2|cop2)", borrador) or \
                "gte_" in borrador:
            with open(c, "w") as f:
                f.write(limpiar(borrador, externas))
            return funcion, tam, "GTE", ""
        with open(c, "w") as f:
            f.write(limpiar(borrador, externas))
        try:
            salida = io.StringIO()
            with contextlib.redirect_stdout(salida):
                ok = verificar.verificar(c, [funcion], n_variantes=30)
            ultima = salida.getvalue().strip().split("\n")[-1]
            estado = ultima.rsplit("-> ", 1)[-1] if "-> " in ultima else ("IGUAL" if ok else "DISTINTO")
            return funcion, tam, estado, ultima[:120]
        except SystemExit as ex:
            msg = str(ex).strip().split("\n")
            err = next((m for m in msg if "error" in m), msg[-1] if msg else "")
            resultado = (funcion, tam, "NO_COMPILA", err.replace(AQUI + "/", "")[:120])
    return resultado


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--solo", default="")
    ap.add_argument("--max-tam", type=int, default=100000)
    ap.add_argument("--procesos", type=int, default=10)
    a = ap.parse_args()
    armar_datos_m2c()
    os.makedirs(os.path.join(AQUI, "build"), exist_ok=True)
    # los tipos que ya se entienden (objeto.h) y los prototipos escritos a mano van al contexto de m2c
    tipos = subprocess.run(["mipsel-linux-gnu-cpp", "-P", "-DSIN_COMPROBACIONES", "-I", os.path.join(AQUI, "include"),
                            os.path.join(AQUI, "include", "tipos_conocidos.h")], capture_output=True, text=True).stdout
    open(SOLO_TIPOS, "w").write(tipos)
    hechas = set()
    for c in glob.glob(os.path.join(AQUI, "src", "*", "*.c")):
        if os.sep + "auto" + os.sep not in c:
            # definiciones, no las declaraciones extern de lo que se llama
            hechas |= set(re.findall(r"^(?!extern\b)\w[\w\s\*]*?\b(\w+)\([^;]*$", open(c).read(), re.M))
    funcs = []
    for l in open(os.path.join(AQUI, "funciones_juego.tsv")):
        d, tam, nom = l.split()
        if nom.startswith(("caseD_", "switchD_", "LAB_")):
            continue                  # etiquetas de un switch que Ghidra tomo por funciones
        if (not a.solo or nom in a.solo.split(",")) and int(tam) <= a.max_tam:
            funcs.append((nom, int(tam)))
    res = []
    with ProcessPoolExecutor(a.procesos) as ex:
        futs = {}
        for nom, tam in funcs:
            if nom in hechas:
                res.append((nom, tam, "YA_HECHA", ""))
            else:
                futs[ex.submit(procesar, nom, tam)] = nom
        for i, fu in enumerate(as_completed(futs)):
            try:
                res.append(fu.result())
            except Exception as e:
                res.append((futs[fu], 0, "ERROR", str(e)[:120]))
            if (i + 1) % 50 == 0:
                print(f"  {i + 1} de {len(futs)}", flush=True)
    tsv = os.path.join(AQUI, "progreso.tsv")
    if a.solo and os.path.exists(tsv):
        # con --solo se actualizan esas filas y el resto queda como estaba
        nuevas = {r[0] for r in res}
        for l in list(open(tsv))[1:]:
            p = l.rstrip("\n").split("\t")
            if p[0] not in nuevas:
                res.append((p[0], int(p[1]), p[2], p[3] if len(p) > 3 else ""))
    res.sort()
    with open(tsv, "w") as f:
        f.write("funcion\ttamano\testado\tdetalle\n")
        for r in res:
            f.write("\t".join(str(x) for x in r) + "\n")
    from collections import Counter
    c = Counter(r[2] for r in res)
    bytes_ok = sum(r[1] for r in res if r[2] in ("IGUAL", "YA_HECHA"))
    total = sum(r[1] for r in res)
    print(dict(c))
    print(f"verificadas {c['IGUAL'] + c['YA_HECHA']} funciones, {bytes_ok} de {total} bytes de codigo "
          f"({100 * bytes_ok / max(total, 1):.1f} %)")


if __name__ == "__main__":
    main()
