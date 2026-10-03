"""Capturas SINTETICAS: para funciones que no se ejecutaron en ninguna ronda de capturas.

Una captura sintetica es la RAM, el scratchpad y los registros de una captura REAL de otra funcion (la
"donante": la mas cercana en direccion que tenga capturas), con el pc puesto en la funcion a probar. El
verificador corre igual el original y el C sobre esa memoria y sobre sus variantes (argumentos y memoria al
azar), asi que compara lo mismo; lo que cambia es que la funcion no se llamo de verdad en ese momento del
juego. Por eso lo que se verifica asi se anota APARTE: progreso_sint.tsv (lote) y estado IGUAL_SINT /
IGUAL_V0_SINT en notas/fases/auditoria.tsv (a mano). Las capturas van en capturas_sint/ (fuera de git).

Uso (en WSL, con el venv):
  python3 sint.py candidatas [--tope bytes]          lista de funciones simples sin capturas
  python3 sint.py crear F1,F2,...                     crea capturas_sint/F/00 desde su donante
  python3 sint.py lote F1,F2,...                      m2c + verificar con las sinteticas -> progreso_sint.tsv
  python3 sint.py verificar src/X.c F                 verifica C escrito a mano con las sinteticas
  python3 sint.py mutantes src/X.c F [--max n]        mutantes.py con las sinteticas
"""
import contextlib
import glob as _glob
import io
import os
import re
import shutil
import sys

AQUI = os.path.dirname(os.path.abspath(__file__))
REALES = os.path.join(AQUI, "capturas")
SINT = os.path.join(AQUI, "capturas_sint")
TSV = os.path.join(AQUI, "progreso_sint.tsv")


def funciones():
    res = []
    for l in open(os.path.join(AQUI, "funciones_juego.tsv")):
        d, tam, nom = l.split()
        res.append((int(d, 16), int(tam), nom))
    return res


def con_capturas(nom):
    return bool(_glob.glob(os.path.join(REALES, nom, "*.regs")))


def asm_de(nom):
    for f in _glob.glob(os.path.join(AQUI, "asm", "*.s")):
        t = open(f).read()
        i = t.find(f"glabel {nom}\n")
        if i >= 0:
            return t[i:t.find(f"endlabel {nom}", i)]
    return ""


def candidatas(tope, max_llamadas=2, max_globales=6, hechas=(), con_gte=False):
    progreso = {}
    for l in list(open(os.path.join(AQUI, "progreso.tsv")))[1:]:
        p = l.rstrip("\n").split("\t")
        progreso[p[0]] = p[2]
    res = []
    for d, tam, nom in funciones():
        if progreso.get(nom) != "SIN_CAPTURAS" or tam > tope or con_capturas(nom):
            continue
        a = asm_de(nom)
        llamadas = len(re.findall(r"\bjal\b|\bjalr\b", a))
        globales = len(re.findall(r"%hi\(|%gp_rel\(", a))
        # el GTE (cop2, lwc2, swc2, mtc2, mfc2, ctc2, cfc2) lo emula gte.py; con_gte lo deja pasar
        hw = bool(re.search(r"mtc0|mfc0|syscall|break", a)) or (not con_gte and bool(re.search(r"cop2|lwc2|swc2|mtc2|mfc2|ctc2|cfc2", a)))
        if llamadas <= max_llamadas and globales <= max_globales and not hw and nom not in hechas:
            res.append((tam, nom, llamadas, globales))
    return sorted(res)


def donante(nom):
    fs = funciones()
    d = {n: a for a, _, n in fs}[nom]
    mejor = None
    for a, _, n in fs:
        if n != nom and con_capturas(n):
            if mejor is None or abs(a - d) < abs(mejor[0] - d):
                mejor = (a, n)
    return mejor[1]


def crear(nom):
    dst = os.path.join(SINT, nom)
    if os.path.exists(os.path.join(dst, "00.regs")):
        return
    don = donante(nom)
    src = sorted(_glob.glob(os.path.join(REALES, don, "*.regs")))[0][:-5]
    os.makedirs(dst, exist_ok=True)
    shutil.copyfile(src + ".ram", os.path.join(dst, "00.ram"))
    shutil.copyfile(src + ".spad", os.path.join(dst, "00.spad"))
    regs = open(src + ".regs").read().split()
    regs[32] = "%08x" % {n: a for a, _, n in funciones()}[nom]
    open(os.path.join(dst, "00.regs"), "w").write(" ".join(regs))
    open(os.path.join(dst, "DONANTE"), "w").write(don + "\n")


def usar_sinteticas():
    """Hace que verificar (y mutantes) busquen las capturas en capturas_sint/."""
    import verificar

    class G:
        @staticmethod
        def glob(patron):
            return _glob.glob(patron.replace(os.sep + "capturas" + os.sep, os.sep + "capturas_sint" + os.sep))
    verificar.glob = G
    return verificar


def lote(noms):
    import auto
    auto.armar_datos_m2c()
    auto.armar_tipos()                 # que tipos_conocidos.h recien editado llegue a m2c
    V = usar_sinteticas()
    antes = {}
    if os.path.exists(TSV):
        for l in list(open(TSV))[1:]:
            p = l.rstrip("\n").split("\t")
            antes[p[0]] = p
    tam = {n: t for _, t, n in funciones()}
    for nom in noms:
        crear(nom)
        c = os.path.join(AQUI, "src", "auto", nom + ".c")
        estado, detalle = "M2C_FALLA", ""
        for extra in ((), ("--no-switches",)):
            borrador, externas = auto.m2c_dos_pasadas(nom, extra)
            if "Decompilation failure" in borrador or not borrador.strip():
                continue
            open(c, "w").write(auto.limpiar(borrador, externas))
            try:
                salida = io.StringIO()
                with contextlib.redirect_stdout(salida):
                    V.verificar(c, [nom], n_variantes=30)
                ultima = salida.getvalue().strip().split("\n")[-1]
                estado = ultima.rsplit("-> ", 1)[-1] if "-> " in ultima else "DISTINTO"
                detalle = ultima[:120]
                break
            except SystemExit as ex:
                estado, detalle = "NO_COMPILA", str(ex).strip().split("\n")[-1][:120]
        if estado in ("IGUAL", "IGUAL_V0"):
            estado += "_SINT"
        antes[nom] = [nom, str(tam[nom]), estado, detalle]
        print(nom, estado, flush=True)
        with open(TSV, "w") as f:
            f.write("funcion\ttamano\testado\tdetalle\n")
            for p in sorted(antes.values()):
                f.write("\t".join(p) + "\n")


def main():
    a = sys.argv[1:]
    if a[0] == "candidatas":
        tope = int(a[a.index("--tope") + 1], 0) if "--tope" in a else 0x200
        ll = int(a[a.index("--llamadas") + 1]) if "--llamadas" in a else 2
        gl = int(a[a.index("--globales") + 1]) if "--globales" in a else 6
        # --nuevas: salta las que ya estan en progreso_sint.tsv
        hechas = {l.split("\t")[0] for l in open(TSV)} if "--nuevas" in a and os.path.exists(TSV) else set()
        for t, n, ll, g in candidatas(tope, ll, gl, hechas, "--gte" in a):
            print(f"{t}\t{n}\t{ll}\t{g}")
    elif a[0] == "crear":
        for n in a[1].split(","):
            crear(n)
    elif a[0] == "lote":
        lote(a[1].split(","))
    elif a[0] == "verificar":
        crear(a[2])
        V = usar_sinteticas()
        V.verificar(a[1], [a[2]])
    elif a[0] == "mutantes":
        crear(a[2])
        usar_sinteticas()
        import mutantes
        sys.argv = ["mutantes.py"] + a[1:]
        mutantes.main()


if __name__ == "__main__":
    main()
