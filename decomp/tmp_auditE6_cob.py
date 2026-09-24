import sys, cobertura
for f in sys.argv[1:]:
    t, c = cobertura.cobertura_de(f, 30)
    print(f, c, "de", t, flush=True)
