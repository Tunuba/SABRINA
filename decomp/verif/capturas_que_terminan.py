# Para cada funcion dada: en cuantas de sus capturas la ORIGINAL termina (tope de 20 s por corrida).
# uso (WSL, venv, desde decomp): python3 verif/capturas_que_terminan.py f1 f2 ...
import glob, os, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import verificar as V

sim = V.simbolos()
for f in sys.argv[1:]:
    caps = sorted(glob.glob(os.path.join("capturas", f, "*.regs")))
    bien = []
    for c in caps:
        r = V.ejecutar(c[:-5], sim[f], None, tope_seg=20)
        if not r["error"]:
            bien.append(os.path.basename(c)[:-5])
    print(f"{f}\t{len(bien)} de {len(caps)}\t{' '.join(bien)}", flush=True)
