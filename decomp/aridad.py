"""Cuantos argumentos recibe cada funcion del ejecutable, para darselo a m2c.

Sin prototipos m2c no sabe cuantos argumentos pasar en una llamada y se come los que la funcion solo deja
pasar (en `strncmp(a, b, 12)` escribe `strncmp(12)`). Aqui se mira el ensamblador: a0-a3 es argumento si
la funcion lo lee antes de escribirlo, recorriendo en orden de direcciones; una llamada lee los argumentos
de la llamada (se repite hasta que no cambia nada, porque una funcion que solo pasa a0 a otra tambien lo
recibe). Se equivoca hacia el lado de sobrar: un argumento de mas no cambia lo que hace el C.

Deja include/prototipos.h con `s32 nombre(s32, ...);` para cada funcion.
Uso: python3 aridad.py
"""
import os
import re
import subprocess

AQUI = os.path.dirname(os.path.abspath(__file__))
ARGS = ["a0", "a1", "a2", "a3"]
VARIADICAS = {"printf": 1, "sprintf": 2, "FntPrint": 1}   # argumentos fijos; el resto va con ...


# Cuantos argumentos recibe cada rutina de la BIOS (los stubs `li t2,0xB0; jr t2; li t1,N` no leen a0-a3, asi que
# el recorrido de arriba cree que no reciben nada y m2c se come los argumentos de la llamada: 05-10,
# DeliverEvent(0xF0000009, 0x20) salia como DeliverEvent() y el juego se colgaba)
ARIDAD_NOMBRE = {"TestEvent": 1, "OpenEvent": 3, "EnableEvent": 1, "CloseEvent": 1, "DeliverEvent": 2,
                 "WaitEvent": 1, "DisableEvent": 1, "ChangeClearRCnt": 2, "ChangeClearPAD": 1,
                 "_card_info": 1, "_card_load": 1, "GPU_cw": 1, "firstfile2": 2, "nextfile": 1, "exit": 1}


def main():
    import verificar
    ins, llamadas, funcs = verificar.desensamblado()
    sim = verificar.simbolos()
    marcadas = set(re.findall(r"^(\w+) = 0x[0-9A-Fa-f]+; // type:func",
                              open(os.path.join(AQUI, "symbol_addrs.txt")).read(), re.M))
    # las que ya tienen prototipo escrito a mano en tipos_conocidos.h no se tocan
    a_mano = set(re.findall(r"^[\w\s\*]+?\b(\w+)\s*\([^;]*\);",
                            open(os.path.join(AQUI, "include", "tipos_conocidos.h")).read(), re.M))
    nombres = {}
    for n, d in sim.items():
        if (n in marcadas or re.fullmatch(r"func_[0-9A-F]{8}", n)) and d in ins and "." not in n                 and n not in a_mano:
            nombres.setdefault(d, n)
    inicios = sorted(nombres)
    rango = {d: (d, inicios[i + 1] if i + 1 < len(inicios) else d + 0x1000) for i, d in enumerate(inicios)}
    aridad = {d: 0 for d in inicios}
    fijas = {d: VARIADICAS[n] for d, n in nombres.items() if n in VARIADICAS}
    # lo que escriben los llamadores en a0-a3 justo antes de cada jal (en el mismo bloque, con el hueco de
    # retardo): un trampolin que pasa sus argumentos sin tocarlos a un puntero a funcion no los lee, y solo
    # asi se sabe cuantos recibe
    de_llamadores = {}
    for pc, (mn, ops) in ins.items():
        if mn != "jal" or not ops or not re.fullmatch(r"[0-9a-f]+", ops[0]):
            continue
        destino = int(ops[0], 16)
        escritos = set()
        for q in [pc + 4] + [pc - 4 * k for k in range(1, 9)]:
            if q not in ins:
                break
            m, o = ins[q]
            if q != pc + 4 and (m in ("jal", "j", "jalr", "jr", "b") or m in verificar.SALTO_COND):
                break
            _, escribe = verificar.lee_escribe(m, o)
            if escribe in ARGS:
                escritos.add(escribe)
        n = max((ARGS.index(r) + 1 for r in escritos), default=0)
        de_llamadores[destino] = max(de_llamadores.get(destino, 0), n)
    trampolin = set()
    for _ in range(6):
        cambio = False
        for d in inicios:
            ini, fin = rango[d]
            params = set()
            # recorrido por caminos: (pc, argumentos ya escritos en ese camino)
            pila, vistos = [(ini, frozenset())], set()
            while pila:
                pc, escritos = pila.pop()
                if (pc, escritos) in vistos or not (ini <= pc < fin) or pc not in ins:
                    continue
                vistos.add((pc, escritos))
                mn, ops = ins[pc]
                es_salto = mn in ("jal", "j", "jalr", "jr", "b") or mn in verificar.SALTO_COND
                orden = [ins.get(pc + 4, ("nop", [])), (mn, ops)] if es_salto else [(mn, ops)]
                w = set(escritos)
                for m, o in orden:        # el hueco de retardo corre antes del salto
                    lee, escribe = verificar.lee_escribe(m, o)
                    if m in ("jal", "j") and o:
                        destino = int(o[0], 16) if re.fullmatch(r"[0-9a-f]+", o[0]) else None
                        if destino in aridad and not (ini <= destino < fin):
                            lee = lee | set(ARGS[:aridad[destino]])
                    params |= {r for r in ARGS if r in lee and r not in w}
                    if escribe in ARGS:
                        w.add(escribe)
                w = frozenset(w)
                if not es_salto:
                    pila.append((pc + 4, w))
                elif mn == "jal" or mn == "jalr":
                    if mn == "jalr" and not w:
                        trampolin.add(d)                       # llama sin haber tocado a0-a3
                    pila.append((pc + 8, frozenset(ARGS)))     # despues de una llamada a0-a3 no valen nada
                elif mn in ("j", "b"):
                    destino = int(ops[0], 16) if re.fullmatch(r"[0-9a-f]+", ops[0]) else None
                    if destino is not None and ini <= destino < fin:
                        pila.append((destino, w))            # si sale de la funcion es una llamada final
                elif mn == "jr":
                    pass
                else:                                          # condicional: los dos caminos
                    pila.append((pc + 8, w))
                    destino = ops[-1]
                    if re.fullmatch(r"[0-9a-f]+", destino):
                        pila.append((int(destino, 16), w))
            n = fijas.get(d, max((ARGS.index(r) + 1 for r in params), default=0))
            n = ARIDAD_NOMBRE.get(nombres[d], n)
            if d in trampolin and d not in fijas:
                n = max(n, de_llamadores.get(d, 0))
            if n != aridad[d]:
                aridad[d], cambio = n, True
        if not cambio:
            break
    with open(os.path.join(AQUI, "include", "prototipos.h"), "w") as f:
        f.write("/* Hecho por aridad.py: cuantos argumentos recibe cada funcion, para m2c. No editar.\n"
                " * Devuelve s32 si algun llamador lee v0 al volver y void si ninguno; las marcadas con ? solo\n"
                " * se llaman por punteros y no se sabe. */\n")
        for d in inicios:
            args = ", ".join(["s32"] * aridad[d]) + (", ..." if d in fijas else "") or "void"
            lee = verificar.v0_de_void(nombres[d])
            tipo = "void" if lee is False else "s32"
            f.write(f"{tipo} {nombres[d]}({args});{' /* ? */' if lee is None else ''}\n")
    from collections import Counter
    print(Counter(aridad.values()))


if __name__ == "__main__":
    main()
