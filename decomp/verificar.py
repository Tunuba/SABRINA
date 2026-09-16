"""Verifica que una funcion descompilada a C hace exactamente lo mismo que la original.

Para cada captura (capturas/<funcion>/NN.ram, .spad, .regs: memoria y registros reales al entrar a la
funcion, tomados del juego corriendo) ejecuta en Unicorn la funcion original y la version en C, cada una
desde la misma memoria, y compara el valor devuelto (v0, v1), la RAM entera, el scratchpad y lo escrito en
los registros de hardware. Se excluye la pila por debajo del sp de entrada (variables locales) y los 16
bytes de sp a sp+16, donde la funcion puede guardar a0-a3. Si el C declara la funcion void y ningun
llamador lee v0 al volver, v0 no se compara. Si el C define un dato del juego (una copia nueva en vez de la
memoria del juego), no se acepta.

La version en C se compila con el GCC moderno para MIPS I (mipsel-linux-gnu-gcc -march=r3000) y se enlaza
en 0x80400000, fuera de los 2 MB de RAM de la PS1 pero en la misma region de 256 MB, asi un jal a las
funciones originales funciona. Todos los simbolos externos se resuelven a sus direcciones reales (los del
ELF que arma armar.sh).

Las llamadas a la BIOS (0xA0, 0xB0, 0xC0) vuelven enseguida. Las instrucciones del coprocesador geometrico
(cop2) no las ejecuta Unicorn: se emulan en Python (gte.py) con un gancho en la direccion de cada una.

Uso: python3 verificar.py src/Archivo.c Funcion [Funcion...]
"""
import functools
import glob
import os
import struct
import subprocess
import sys
import tempfile

import gte
from unicorn import Uc, UcError, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_LITTLE_ENDIAN, UC_HOOK_CODE, UC_HOOK_MEM_WRITE, UC_HOOK_MEM_READ
from unicorn.mips_const import UC_MIPS_REG_PC, UC_MIPS_REG_RA, UC_MIPS_REG_V0, UC_MIPS_REG_V1, UC_MIPS_REG_SP, \
    UC_MIPS_REG_HI, UC_MIPS_REG_LO, UC_MIPS_REG_ZERO

AQUI = os.path.dirname(os.path.abspath(__file__))
BASE_C = 0x80400000
FIN = 0x80FFFFF0            # direccion de retorno centinela
LIMITE = 20_000_000         # instrucciones como maximo por ejecucion

_simbolos = None


def simbolos():
    global _simbolos
    if _simbolos is None:
        _simbolos = {}
        salida = subprocess.run(["mipsel-linux-gnu-nm", os.path.join(AQUI, "build/slus_012.08.elf")],
                                capture_output=True, text=True).stdout
        for l in salida.splitlines():
            p = l.split()
            if len(p) == 3:
                _simbolos[p[2]] = int(p[0], 16)
    return _simbolos


def compilar(c, excluir):
    """Compila y enlaza el .c en BASE_C. Devuelve (binario, {nombre: direccion})."""
    tmp = tempfile.mkdtemp()
    obj = os.path.join(tmp, "f.o")
    # gnu89 y -w: el C de m2c llama funciones sin prototipo y mezcla enteros y punteros, como el original
    r = subprocess.run(["mipsel-linux-gnu-gcc", "-c", "-O2", "-march=r3000", "-mabi=32", "-mno-abicalls", "-fno-pic",
                        "-G0", "-fno-builtin", "-ffreestanding", "-fno-strict-aliasing", "-msoft-float",
                        "-std=gnu89", "-w", "-fcommon", "-ffunction-sections",
                        # el div del juego no revisa el cero (el de GCC pone un teq); asi divide igual que la
                        # original tambien con divisor 0
                        "-mno-check-zero-division",
                        "-I", os.path.join(AQUI, "include"), "-o", obj, c], capture_output=True, text=True)
    if r.returncode:
        raise SystemExit("no compila:\n" + r.stderr)
    und = subprocess.run(["mipsel-linux-gnu-nm", "-u", obj], capture_output=True, text=True).stdout.split()
    und = [u for u in und if u != "U"]
    sim = simbolos()
    # un dato del juego definido en el C seria una copia nueva, no la memoria del juego: la funcion leeria y
    # escribiria esa copia y podria pasar la verificacion sin tocar lo que toca la original
    for l in subprocess.run(["mipsel-linux-gnu-nm", obj], capture_output=True, text=True).stdout.splitlines():
        p = l.split()
        if len(p) == 3 and p[1] in "dDbBgGsSCrR" and p[2] in sim:
            raise SystemExit(f"no compila: error: el C define el dato del juego {p[2]}; tiene que ser extern")
    # las funciones del juego que el C define: el nombre sigue apuntando a la original (asi un puntero a
    # funcion o una llamada desde el C van a la del juego, como en el original) y la version en C queda
    # con el nombre c__Nombre, que es la que se ejecuta
    definidas = []
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-t", obj], capture_output=True, text=True).stdout.splitlines():
        p = l.split()
        if len(p) >= 6 and p[1] == "g" and p[2] == "F" and p[3].startswith(".text") and p[-1] in sim:
            definidas.append((p[-1], p[3], int(p[0], 16)))
    if definidas:
        extra = []
        for nom, sec, off in definidas:
            extra += ["--add-symbol", f"c__{nom}={sec}:0x{off:x},global,function"]
        subprocess.run(["mipsel-linux-gnu-objcopy", *extra, obj], check=True)
    ld = os.path.join(tmp, "f.ld")
    with open(ld, "w") as f:
        for u in und + [d[0] for d in definidas]:
            if u not in sim:
                raise SystemExit(f"simbolo desconocido: {u}")
            f.write(f"{u} = 0x{sim[u]:08X};\n")
        f.write(f"SECTIONS {{ . = 0x{BASE_C:08X}; .text : {{ *(.text*) }} .rodata : {{ *(.rodata*) }} "
                f".data : {{ *(.data*) *(.sdata*) }} .bss : {{ *(.bss*) *(.sbss*) *(COMMON) }} }}\n")
    elf = os.path.join(tmp, "f.elf")
    r = subprocess.run(["mipsel-linux-gnu-ld", "-EL", "-T", ld, "-o", elf, obj], capture_output=True, text=True)
    if r.returncode:
        raise SystemExit("no enlaza:\n" + r.stderr)
    binario = os.path.join(tmp, "f.bin")
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", elf, binario], check=True)
    dirs = {}
    for l in subprocess.run(["mipsel-linux-gnu-nm", elf], capture_output=True, text=True).stdout.splitlines():
        p = l.split()
        if len(p) == 3 and p[1] in "Tt":
            dirs[p[2]] = int(p[0], 16)
    for nom, _, _ in definidas:
        dirs[nom] = dirs["c__" + nom]
    return open(binario, "rb").read(), dirs


_dis = None
ALMACENA = {"sb", "sh", "sw", "swl", "swr", "swc2"}
SALTO_COND = {"beq", "bne", "beqz", "bnez", "bgez", "bgtz", "blez", "bltz", "bgezal", "bltzal", "beql", "bnel"}
SOLO_FUENTES = {"mult", "multu", "div", "divu", "mthi", "mtlo", "jr", "jalr", "teq", "break", "syscall"}


def desensamblado():
    """{direccion: (instruccion, operandos)}, {destino: [direcciones de los jal]} y las funciones ordenadas."""
    global _dis
    if _dis is None:
        ins, llamadas = {}, {}
        sal = subprocess.run(["mipsel-linux-gnu-objdump", "-d", os.path.join(AQUI, "build/slus_012.08.elf")],
                             capture_output=True, text=True).stdout
        for l in sal.splitlines():
            p = l.split("\t")
            if len(p) >= 3 and p[0].endswith(":"):
                try:
                    d = int(p[0][:-1].strip(), 16)
                except ValueError:
                    continue
                mn = p[2].strip()
                ops = p[3].split(" <")[0].strip() if len(p) > 3 else ""
                ins[d] = (mn, [o.strip() for o in ops.split(",")] if ops else [])
                if mn == "jal":
                    llamadas.setdefault(int(ops, 16), []).append(d)
        funcs = sorted(v for v in simbolos().values() if v in ins)
        _dis = (ins, llamadas, funcs)
    return _dis


def _regs(op):
    return set(t for t in op.replace("(", " ").replace(")", " ").split() if not t.lstrip("-").isdigit()
               and not t.startswith("0x"))


def lee_escribe(mn, ops):
    """Registros que lee una instruccion y el que escribe (o None)."""
    todos = set().union(*map(_regs, ops)) if ops else set()
    if mn in ALMACENA or mn in SALTO_COND or mn in SOLO_FUENTES:
        return todos, None
    if mn in ("j", "b", "jal", "nop") or not ops:
        return set(), None
    if mn == "lui":
        return set(), ops[0]
    return (set().union(*map(_regs, ops[1:])) if len(ops) > 1 else set()), ops[0]


def _juntar(resultados):
    """True si alguno lee v0, None si alguno no se sabe, False si ninguno lo lee."""
    resultados = list(resultados)
    return True if True in resultados else None if None in resultados else False


def v0_se_usa(dirc, prof=0, vistos=None):
    """Despues de volver de una llamada en dirc, ¿el codigo lee v0 antes de pisarlo? True, False o None
    (no se sabe). Sigue los saltos incondicionales y, si llega a `jr ra` sin tocar v0, mira a quienes llaman
    a la funcion que lo contiene."""
    import bisect
    ins, llamadas, funcs = desensamblado()
    vistos = vistos if vistos is not None else set()
    pc = dirc + 8                                      # despues del jal y su hueco de retardo
    for _ in range(80):
        if pc not in ins:
            return None
        mn, ops = ins[pc]
        lee, escribe = lee_escribe(mn, ops)
        if "v0" in lee:
            return True
        if mn in ("j", "b", "jr", "jal", "jalr"):
            lee_h, escribe_h = lee_escribe(*ins.get(pc + 4, ("nop", [])))   # el hueco corre antes del salto
            if "v0" in lee_h:
                return True
            if escribe_h == "v0" or mn in ("jal", "jalr"):
                return False                           # pisado, o lo pisa la funcion llamada
            if mn in ("j", "b"):
                pc = int(ops[0], 16)
                continue
            if ops != ["ra"]:
                return None                            # jr por una tabla de saltos
            # v0 sale tal cual de esta funcion: depende de si la usan sus llamadores
            i = bisect.bisect_right(funcs, pc) - 1
            f = funcs[i] if i >= 0 else None
            if f in vistos:
                return False                           # ya se esta mirando por otro camino
            if f is None or prof >= 4 or not llamadas.get(f):
                return None                            # sin llamadas directas (solo por punteros)
            vistos.add(f)
            return _juntar(v0_se_usa(s, prof + 1, vistos) for s in llamadas[f])
        if escribe == "v0":
            return False
        pc += 4
    return None


def es_void(c, funcion):
    import re
    m = re.search(r"^\s*(static\s+)?(\w[\w\s\*]*?)\s*\b" + funcion + r"\s*\(", open(c).read(), re.M)
    return bool(m) and m.group(2).strip() == "void"


def v0_de_void(funcion):
    """Para una funcion que el C declara void: ¿algun llamador lee v0 al volver? (el compilador del juego
    deja en v0 lo ultimo que calculo). True, False o None si solo se llega por punteros o no se sabe."""
    sitios = desensamblado()[1].get(simbolos()[funcion], [])
    return _juntar(v0_se_usa(s) for s in sitios) if sitios else None


def fin_de(funcion):
    sim = simbolos()
    ini = sim[funcion]
    return min((d for d in sim.values() if d > ini), default=ini + 0x400)


def constantes_de(funcion):
    """Valores interesantes para los argumentos: las constantes de la funcion original y sus vecinos,
    potencias de dos y sus vecinos."""
    sim = simbolos()
    ini = sim[funcion]
    fin = min((d for d in sim.values() if d > ini), default=ini + 0x400)
    dis = subprocess.run(["mipsel-linux-gnu-objdump", "-d", f"--start-address=0x{ini:x}", f"--stop-address=0x{fin:x}",
                          os.path.join(AQUI, "build/slus_012.08.elf")], capture_output=True, text=True).stdout
    base = set()
    for tok in dis.replace(",", " ").split():
        if tok.startswith("0x") or tok.lstrip("-").isdigit():
            try:
                v = int(tok, 0)
            except ValueError:
                continue
            base |= {v, v << 16}
    global _propias, _propias_base
    _propias = sorted({(v + d) & 0xFFFFFFFF for v in base for d in (-1, 0, 1)})
    _propias_base = sorted({v & 0xFFFFFFFF for v in base if -0x10000 < v < 0x10000})
    for k in range(32):
        base.add(1 << k)
    pool = set()
    for v in base:
        for d in (-1, 0, 1):
            pool.add((v + d) & 0xFFFFFFFF)
            pool.add((-v + d) & 0xFFFFFFFF)
    return sorted(pool)


_propias = []
_propias_base = []


def variantes(regs, pool, n, rnd):
    """n juegos de registros con a0-a3 cambiados por las constantes de la propia funcion (las que compara,
    como -1 o -2, y sus vecinas), valores de pool, sumas y restas de ellos o al azar."""
    res = []
    propias = _propias or pool
    # primero, sistematico: cada constante de la funcion en cada argumento (asi se toman las ramas de
    # `if (i == -1)`, que al azar casi nunca salen), hasta 16
    pares = [(i, c) for i in (4, 5, 6, 7) for c in _propias_base]
    rnd.shuffle(pares)
    for i, c in pares[:16]:
        r = list(regs)
        r[i] = c
        res.append(r)
    for _ in range(n):
        r = list(regs)
        for i in (4, 5, 6, 7):
            if rnd.random() < 0.6:
                t = rnd.random()
                if t < 0.2:
                    v = rnd.randrange(0, 0x2000)        # indices chicos (celdas, objetos, tablas)
                elif t < 0.4:
                    v = rnd.choice(propias)
                elif t < 0.5:
                    v = rnd.choice(pool)
                elif t < 0.8:
                    v = rnd.choice(pool) + rnd.choice((1, -1)) * rnd.choice(pool)
                else:
                    v = rnd.getrandbits(32)
                r[i] = v & 0xFFFFFFFF
        res.append(r)
    return res


def cop2_en_binario(binario):
    """Direcciones de instrucciones cop2 dentro del C ya compilado, que se carga en BASE_C."""
    res = set()
    for i in range(0, len(binario) - 3, 4):
        w = struct.unpack_from("<I", binario, i)[0]
        if (w >> 26) & 0x3F in (0x12, 0x32, 0x3A):
            res.add(BASE_C + i)
    return res


@functools.lru_cache(maxsize=1)
def direcciones_cop2():
    return gte.instrucciones_cop2(desensamblado()[0])


@functools.lru_cache(maxsize=16)
def _memoria(captura):
    """La RAM y el scratchpad de una captura, guardados en memoria: son 2 MB por captura y cada variante
    arranca de ahi; leerlos del disco de Windows en cada corrida era lo que hacia lento el lote."""
    return open(captura + ".ram", "rb").read(), open(captura + ".spad", "rb").read()


def ejecutar(captura, pc, codigo_c, regs=None, parche=None, trazar=False, propia=None):
    """Corre desde la captura. parche: {direccion fisica: bytes} que se escriben encima de la RAM.
    trazar: devuelve tambien en "lecturas" lo que la funcion lee de la RAM antes de escribirlo (sus
    entradas en memoria), como {direccion fisica: tamano}; y en "propias" las que lee el codigo de la propia
    funcion (propia = (inicio, fin)), no las funciones a las que llama."""
    ram, spad = _memoria(captura)
    if regs is None:
        regs = [int(x, 16) for x in open(captura + ".regs").read().split()]
    uc = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 + UC_MODE_LITTLE_ENDIAN)
    # Unicorn traduce kseg0 (0x80xxxxxx) y kseg1 (0xA0xxxxxx) a la direccion fisica 0x0xxxxxxx, igual que
    # la PS1: se mapea la memoria fisica, no las direcciones virtuales.
    uc.mem_map(0x00000000, 0x01000000)            # RAM de 2 MB y, en 0x00400000, el codigo en C
    uc.mem_map(0x1F800000, 0x00010000)            # scratchpad y registros de hardware
    uc.mem_map(0x1FC00000, 0x00080000)            # BIOS (0xBFC00000)
    uc.mem_write(0x00000000, ram)
    uc.mem_write(0x1F800000, spad)
    if codigo_c:
        uc.mem_write(BASE_C & 0x1FFFFFFF, codigo_c)
    for d, b in (parche or {}).items():
        uc.mem_write(d, b)
    for i in range(1, 32):
        uc.reg_write(UC_MIPS_REG_ZERO + i, regs[i])
    uc.reg_write(UC_MIPS_REG_HI, regs[33])
    uc.reg_write(UC_MIPS_REG_LO, regs[34])
    uc.reg_write(UC_MIPS_REG_RA, FIN)
    sp = regs[29]
    hw = []

    def codigo(u, dirc, tam, _):
        if dirc in (0xA0, 0xB0, 0xC0):                 # llamada a la BIOS: volver sin hacer nada
            u.reg_write(UC_MIPS_REG_PC, u.reg_read(UC_MIPS_REG_RA))

    def escritura(u, acceso, dirc, tam, valor, _):
        if 0x1F801000 <= dirc < 0x1F803000:
            hw.append((dirc, tam, valor))

    uc.hook_add(UC_HOOK_CODE, codigo, begin=0xA0, end=0xC4)
    uc.hook_add(UC_HOOK_MEM_WRITE, escritura, begin=0x1F801000, end=0x1F803000)
    # el coprocesador geometrico, emulado en Python: en el codigo del juego y en el C compilado
    gte.poner_ganchos(uc, direcciones_cop2() | cop2_en_binario(codigo_c or b""))
    lecturas, escritas, propias = {}, set(), set()
    if trazar:
        pila = ((sp & 0x1FFFFF) - 0x4000, sp & 0x1FFFFF)

        def lee(u, acceso, dirc, tam, valor, _):
            d = dirc & 0x1FFFFFFF
            if d < 0x200000 and not (pila[0] <= d < pila[1]) and d not in escritas and d not in lecturas:
                lecturas[d] = tam
                if propia and propia[0] <= u.reg_read(UC_MIPS_REG_PC) < propia[1]:
                    propias.add(d)

        def escribe(u, acceso, dirc, tam, valor, _):
            d = dirc & 0x1FFFFFFF
            if d < 0x200000:
                escritas.update(range(d, d + tam))

        uc.hook_add(UC_HOOK_MEM_READ, lee)
        uc.hook_add(UC_HOOK_MEM_WRITE, escribe)
    error = None
    try:
        uc.emu_start(pc, FIN, count=LIMITE)
    except UcError as ex:
        error = f"{ex} en {uc.reg_read(UC_MIPS_REG_PC):08x}"
    if error is None and uc.reg_read(UC_MIPS_REG_PC) != FIN:
        error = f"no termino en {LIMITE} instrucciones (pc {uc.reg_read(UC_MIPS_REG_PC):08x})"
    return dict(v0=uc.reg_read(UC_MIPS_REG_V0), v1=uc.reg_read(UC_MIPS_REG_V1),
                ram=bytes(uc.mem_read(0x00000000, 0x200000)), spad=bytes(uc.mem_read(0x1F800000, 0x400)),
                hw=hw, sp=sp, error=error, lecturas=lecturas, propias=propias)


def comparar(a, b, sp, con_v0=True):
    dif = []
    if a["error"] or b["error"]:
        return [f"error original: {a['error']} / C: {b['error']}"] if a["error"] != b["error"] else []
    if con_v0 and a["v0"] != b["v0"]:
        dif.append(f"v0 {a['v0']:08x} contra {b['v0']:08x}")
    # la pila local y los 16 bytes de sp a sp+16, que la convencion de llamada le da a la funcion llamada
    # para guardar a0-a3 (una llamada al final, compilada como salto, los usa para la que sigue)
    ini_pila = (sp & 0x1FFFFF) - 0x4000
    fin_pila = (sp & 0x1FFFFF) + 16
    ra, rb = a["ram"], b["ram"]
    if ra != rb:
        malos = [i for i in range(0, 0x200000, 4) if ra[i:i + 4] != rb[i:i + 4] and not (ini_pila <= i < fin_pila)]
        if malos:
            dif.append(f"{len(malos)} palabras de RAM distintas, la primera en {0x80000000 + malos[0]:08x}")
    if a["spad"] != b["spad"]:
        dif.append("scratchpad distinto")
    if a["hw"] != b["hw"]:
        dif.append("escrituras de hardware distintas")
    return dif


def verificar(c, funciones, n_variantes=60):
    import random
    sim = simbolos()
    codigo_c, dirs = compilar(c, funciones)
    total_ok = True
    for f in funciones:
        caps = sorted(glob.glob(os.path.join(AQUI, "capturas", f, "*.regs")))
        if not caps:
            print(f"{f}: sin capturas")
            total_ok = False
            continue
        if f not in dirs:
            print(f"{f}: no esta en {c}")
            total_ok = False
            continue
        void = es_void(c, f)
        lee_v0 = v0_de_void(f) if void else True
        con_v0 = lee_v0 is not False
        if void and lee_v0 is False:
            print(f"  {f}: void y ningun llamador lee v0 al volver; v0 no se compara")
        solo_v0 = 0                  # ejecuciones que solo difieren en v0 (para una void sin probar)
        ok = 0
        entradas = {}                # por captura: lo que la original lee de la RAM antes de escribirlo
        for cap in caps:
            base = cap[:-5]
            # el rastreo va en una corrida aparte: con los ganchos de memoria puestos Unicorn a veces corre
            # distinto (func_80044C40 salta a 0 solo con ellos), asi que no se compara esa corrida
            t = ejecutar(base, sim[f], None, trazar=True, propia=(sim[f], fin_de(f)))
            entradas[base] = (t["lecturas"], t["propias"])
            a = ejecutar(base, sim[f], None)
            b = ejecutar(base, dirs[f], codigo_c)
            d = comparar(a, b, a["sp"], con_v0)
            if d and void and not comparar(a, b, a["sp"], False):
                solo_v0 += 1
            if d:
                print(f"  {f} {os.path.basename(base)}: " + "; ".join(d))
            else:
                ok += 1
        # variantes de los argumentos sobre la memoria de cada captura
        rnd = random.Random(1234)
        pool = constantes_de(f)
        v_ok = v_tot = v_mal = 0
        for cap in caps:
            base = cap[:-5]
            regs = [int(x, 16) for x in open(base + ".regs").read().split()]
            for r in variantes(regs, pool, n_variantes, rnd):
                a = ejecutar(base, sim[f], None, r)
                if a["error"]:
                    continue                 # con esos argumentos la original tampoco funciona
                v_tot += 1
                b = ejecutar(base, dirs[f], codigo_c, r)
                d = comparar(a, b, a["sp"], con_v0)
                if d and void and not comparar(a, b, a["sp"], False):
                    solo_v0 += 1
                if d:
                    v_mal += 1
                    if v_mal <= 3:
                        args = " ".join(f"{x:08x}" for x in r[4:8])
                        print(f"  {f} {os.path.basename(base)} con a0-a3 {args}: " + "; ".join(d))
                else:
                    v_ok += 1
        # variantes de la memoria: se cambian uno a tres de los valores que la original lee (contadores,
        # indices, banderas, otros datos del juego), asi tambien se prueban las ramas que dependen de la
        # memoria y no de los argumentos
        for cap in caps:
            base = cap[:-5]
            ram = open(base + ".ram", "rb").read()
            lecturas, propias = entradas[base]
            lista = sorted(lecturas.items())
            suyas = [x for x in lista if x[0] in propias]
            if not lista:
                continue
            for _ in range(n_variantes):
                parche = {}
                # casi siempre algo que lee la propia funcion; a veces algo que leen las que llama
                de = suyas if suyas and rnd.random() < 0.75 else lista
                for d, tam in rnd.sample(de, min(len(de), rnd.choice((1, 1, 2, 3)))):
                    tam = tam if tam in (1, 2, 4) else 4
                    v = int.from_bytes(ram[d:d + tam], "little")
                    x = rnd.random()
                    if x < 0.3:
                        n = v + rnd.choice((1, -1, 2, -2))
                    elif x < 0.5:
                        n = rnd.choice((0, 1, -1, v ^ 1, v << 1, v >> 1))
                    elif x < 0.75:
                        n = rnd.randrange(0, 0x40)
                    elif x < 0.9:
                        n = rnd.choice(pool)
                    else:
                        n = rnd.getrandbits(32)
                    parche[d] = (n & ((1 << (8 * tam)) - 1)).to_bytes(tam, "little")
                a = ejecutar(base, sim[f], None, None, parche)
                if a["error"]:
                    continue
                v_tot += 1
                b = ejecutar(base, dirs[f], codigo_c, None, parche)
                d = comparar(a, b, a["sp"], con_v0)
                if d and void and not comparar(a, b, a["sp"], False):
                    solo_v0 += 1
                if d:
                    v_mal += 1
                    if v_mal <= 6:
                        cambios = " ".join(f"{0x80000000 + k:08x}={w.hex()}" for k, w in parche.items())
                        print(f"  {f} {os.path.basename(base)} con memoria {cambios}: " + "; ".join(d))
                else:
                    v_ok += 1
        bien = ok == len(caps) and v_ok == v_tot
        # void a la que solo se llega por punteros: todo igual menos v0, y no se puede saber si alguien lo lee
        estado = "IGUAL" if bien else "IGUAL_V0" if lee_v0 is None and \
            solo_v0 == (len(caps) - ok) + (v_tot - v_ok) else "DISTINTO"
        total_ok &= bien
        print(f"{f}: {ok} de {len(caps)} capturas y {v_ok} de {v_tot} variantes iguales -> {estado}")
    return total_ok


if __name__ == "__main__":
    sys.exit(0 if verificar(sys.argv[1], sys.argv[2:]) else 1)
