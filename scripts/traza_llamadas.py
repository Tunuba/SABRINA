"""Registra la secuencia de entradas a las funciones reemplazadas (en el disco original y en el armado con C) y
las compara: la primera diferencia es donde el C empieza a hacer otra cosa.
Uso: python traza_llamadas.py [max_entradas]"""
import os, sys, time, subprocess
import disco
from emu import Emu

MAX = int(sys.argv[1]) if len(sys.argv) > 1 else 3000
tam = {}
for l in open(os.path.join(disco.RAIZ, "decomp", "funciones_juego.tsv"), encoding="utf-8"):
    p = l.rstrip("\n").split("\t")
    tam[p[2]] = (int(p[0], 16), int(p[1]))
fs = [l.split("\t")[1] for l in open(os.path.join(disco.RAIZ, "decomp", "build", "armado_c_completo.txt"), encoding="utf-8") if l.startswith("OK")]
dirs = {tam[f][0]: f for f in fs if f in tam}


def trazar(cue, nombre, hasta_frame=600):
    with Emu(iso=cue, log=f"traza_{nombre}.log", extra=("-fastboot",), depurar=True) as e:
        def run_lua(code):
            e.eval("CODE=''; return 'ok'")
            for i in range(0, len(code), 80):
                e.eval("CODE=CODE..[==[%s]==]; return 'ok'" % code[i:i + 80])
            return e.eval("local f,err=loadstring(CODE); if not f then return err end; return tostring(f())")
        run_lua("LOG={} N=0 BP={} function hook(d) return function() N=N+1 if N<=%d then local g=PCSX.getRegisters().GPR.n; LOG[N]=string.format('%%x:%%x,%%x,%%x,%%x',d,g.a0,g.a1,g.a2,g.a3) end end end return 'ok'" % MAX)
        for d in dirs:
            run_lua("BP[#BP+1]=PCSX.addBreakpoint(0x%08x,'Exec',4,'x',hook(0x%08x)) return 'bp'" % (d, d))
        t = time.time(); ult = -1; desde = time.time()
        while time.time() - t < 240:
            f = e.frames()
            if f >= hasta_frame or int(e.eval("return N")) >= MAX:
                break
            if f != ult:
                ult, desde = f, time.time()
            elif time.time() - desde > 10:
                break
            time.sleep(1)
        n = min(int(e.eval("return N")), MAX)
        out = []
        for i in range(1, n + 1, 200):
            out += e.eval("local t={} for i=%d,%d do t[#t+1]=LOG[i] or '' end return table.concat(t,' ')" % (i, min(i + 199, n))).split()
        return out, f


if __name__ == "__main__":
    a, fa = trazar(disco.CUE, "orig")
    b, fb = trazar(os.path.join(disco.DISCO, "bis.cue"), "c")
    print("original:", len(a), "entradas, frame", fa, "| C:", len(b), "entradas, frame", fb)
    nom = lambda z: dirs.get(int(z.split(":")[0], 16), "?")
    for i, (x, y) in enumerate(zip(a, b)):
        if x.split(":")[0] != y.split(":")[0]:
            print("primera diferencia de FUNCION en la entrada", i)
            print("  original:", nom(x), x)
            print("  C:       ", nom(y), y)
            print("  antes:", [nom(z) + " " + z.split(":")[1] for z in a[max(0, i - 6):i]])
            break
    else:
        print("misma secuencia de funciones en las", min(len(a), len(b)), "entradas comparadas")
    for i, (x, y) in enumerate(zip(a, b)):
        if x.split(":")[0] == y.split(":")[0] and x.split(":")[1].split(",")[0] != y.split(":")[1].split(",")[0]:
            print("primera diferencia de a0 en la entrada", i, nom(x), x, "contra", y)
            break
