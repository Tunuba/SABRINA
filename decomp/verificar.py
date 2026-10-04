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
import re
import struct
import subprocess
import sys
import tempfile
import time

import gte
import modelo_cd
from unicorn import Uc, UcError, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_LITTLE_ENDIAN, UC_HOOK_CODE, UC_HOOK_MEM_WRITE, UC_HOOK_MEM_READ, UC_HOOK_INTR
from unicorn.mips_const import UC_MIPS_REG_PC, UC_MIPS_REG_RA, UC_MIPS_REG_V0, UC_MIPS_REG_V1, UC_MIPS_REG_SP, \
    UC_MIPS_REG_HI, UC_MIPS_REG_LO, UC_MIPS_REG_ZERO, UC_MIPS_REG_A0

AQUI = os.path.dirname(os.path.abspath(__file__))
BASE_C = 0x80400000
# Modelos del hardware que espera el juego (aprobados por Meme el 2026-10-03). Original y C ven lo mismo, asi
# que la comparacion sigue siendo justa; solo dejan terminar a las funciones que esperaban para siempre.
# - GPU desocupado: el estado del GPU (GPUSTAT, 0x1F801814) dice siempre listo para comandos, VRAM y DMA.
# - VSync: cada llamada a VSync (func_8001626C) hace pasar un cuadro (sube D_800649EC, que en la consola
#   sube la interrupcion de VBlank), y la espera de cuadros (func_800161D4) encuentra el contador ya en el
#   cuadro que espera, como si hubieran pasado.
# Con SABRINA_SIN_MODELOS=1 se apagan (para comparar con como era antes).
MODELOS = os.environ.get("SABRINA_SIN_MODELOS") != "1"
GPU_LISTA = MODELOS
# Modelos agregados el 2026-10-04 (Meme aprobo todo). SABRINA_SIN_VBLANK=1 / SABRINA_SIN_CD=1 apagan cada uno.
# - VBlank: en cada llamada a VSync corre la rutina de VBlank del juego (func_80016A2C: sube D_800649EC y
#   llama a las funciones de VSyncCallback, como la barra de carga func_800211D4), en la pila de las
#   interrupciones (D_80063954 + 0xFDC) y guardando todos los registros, como una interrupcion. Reemplaza al
#   "cuadro" de VSync de arriba (el contador lo sube la rutina misma).
# - CD: modelo_cd.py imita el controlador del CD (ordenes, respuestas, sectores del .bin, DMA del canal 3).
#   Sus interrupciones (salvo el acuse de una orden, que queda pendiente al darla) se entregan en cada
#   llamada a VSync corriendo la rutina del CD de libcd (func_8002A5F8), antes de la de VBlank, si el juego
#   no esta ya dentro de una interrupcion (D_8006391A).
VBLANK = MODELOS and os.environ.get("SABRINA_SIN_VBLANK") != "1"
CD = MODELOS and os.environ.get("SABRINA_SIN_CD") != "1"
VUELTA_INT = 0x80FFFFE0     # direccion de retorno centinela de las rutinas de interrupcion
# - BIOS, GetC0Table (B0 0x56): las capturas se hicieron con una BIOS sin el kernel de Sony en la RAM, asi que
#   la tabla C0 no esta. El modelo pone una en una pagina aparte (0x01000000, fuera de la RAM que se compara)
#   con la entrada 6 (el manejador de excepciones) apuntando a las 6 instrucciones que trae la BIOS real en
#   +0x28; func_80017BC0 (libapi) las encuentra y las parchea, como en la consola.
TABLA_C0 = 0x81000000
# - BIOS, malloc (A0 0x33) y free (A0 0x34) (04-10): al arrancar, Reservar usa el malloc de la BIOS
#   (D_8007C8E0 != 0), que en el emulador volvia sin hacer nada y dejaba en v0 lo que traia; memset escribia
#   entonces en la direccion 0 y la funcion no terminaba. El modelo da bloques seguidos (alineados a 8) en
#   una zona aparte (MONTON_BIOS, fuera de la RAM de la PS1) y free no hace nada. Lo escrito en esa zona
#   tambien se compara. SABRINA_SIN_MALLOC=1 lo apaga.
# - Tarjeta de memoria (04-10): libcard avisa que termino (D_800D52C8) desde la rutina de VBlank (func_80050828
#   como VSyncCallback). Las esperas que giran leyendo ese aviso sin llamar a VSync (func_80051298) no
#   terminaban: cuando la misma instruccion lo lee en 0 dos veces seguidas, pasa un cuadro (corre la rutina
#   de VBlank como una interrupcion, ver VBLANK) antes de la instruccion siguiente. Y la tarjeta esta puesta y
#   contesta bien: la BIOS de la tarjeta se modela (bios_tarjeta) con una tarjeta en blanco por ejecucion,
#   _card_write guarda el sector de 128 bytes, _card_read lo devuelve, _card_status dice lista, y cada
#   operacion (write, read, _card_info, _card_load) termina enseguida con los eventos IOE de software y de
#   hardware (lo que hacen sus manejadores func_800519E4 y func_80051A34: D_800D5390 y D_800D53A0 en 1). Lo
#   escrito en la tarjeta tambien se compara. SABRINA_SIN_TARJETA=1 apaga todo esto.
# - PCdrv (04-10): las herramientas de desarrollo escriben a la PC con "break" (0x102 PCcreat, 0x104 PCclose,
#   0x106 PCwrite, en func_800294F0/80029518/80029530; un gancho en cada break). El modelo contesta que salio bien y anota cada
#   creacion, cierre y escritura (con los datos); eso tambien se compara. SABRINA_SIN_PCDRV=1 lo apaga.
PCDRV = MODELOS and os.environ.get("SABRINA_SIN_PCDRV") != "1"
TARJETA = MODELOS and os.environ.get("SABRINA_SIN_TARJETA") != "1"
MALLOC = MODELOS and os.environ.get("SABRINA_SIN_MALLOC") != "1"
MONTON_BIOS = 0x81100000
MONTON_TAM = 0x00400000
C0_VIEJO = (0xAF410004, 0xAF420008, 0xAF43000C, 0xAF5F007C, 0x40037000, 0x00000000)
FIN = 0x80FFFFF0            # direccion de retorno centinela
LIMITE = int(os.environ.get("SABRINA_LIMITE", 20_000_000))   # instrucciones como maximo por ejecucion (SABRINA_LIMITE para una tanda larga)
ESCALONES = (250_000, 1_250_000, 5_000_000, LIMITE)   # para medir cuanto corre la original en una captura

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
    # las ayudas de 64 bits que pide GCC son las mismas rutinas que ya trae el juego
    sim = dict(sim, __muldi3=sim["func_80029214"])
    # un dato del juego definido en el C seria una copia nueva, no la memoria del juego: la funcion leeria y
    # escribiria esa copia y podria pasar la verificacion sin tocar lo que toca la original
    for l in subprocess.run(["mipsel-linux-gnu-nm", obj], capture_output=True, text=True).stdout.splitlines():
        p = l.split()
        if len(p) == 3 and p[1] in "dDbBgGsSCrR" and (p[2] in sim or re.fullmatch(r"D_[0-9A-F]{8}", p[2])):
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
    # el tipo puede venir precedido de una macro de atributo (TOCA_NULL, etc.): importa la ultima palabra
    return bool(m) and m.group(2).split()[-1:] == ["void"]


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


_inicios = None


def inicios_de_funcion():
    """Direcciones donde empieza cada funcion del juego (funciones_juego.tsv)."""
    global _inicios
    if _inicios is None:
        _inicios = set()
        for l in open(os.path.join(AQUI, "funciones_juego.tsv")):
            p = l.split("	")
            if len(p) >= 3:
                _inicios.add(int(p[0], 16))
    return _inicios


def _puntero_a_funcion(v, n):
    """Si v (lo que habia en la RAM) es un puntero a una funcion del juego, la variante n solo puede ser otra
    funcion del juego o 0: un valor al azar haria saltar a la mitad de otro codigo, que depende de cada
    registro y de la pila del que llama, y ningun C puede imitar eso (no es un error de la funcion)."""
    ini = inicios_de_funcion()
    if v in ini and n not in ini:
        return 0
    return n


def _evitar_base_c(v):
    """Un argumento al azar que caiga justo en la zona fisica donde vive el C compilado (BASE_C) hace que la
    version en C, al usarlo como puntero, lea su propio codigo maquina en vez de la RAM en cero que ve la
    original ahi: no es un bug de la funcion, es un choque con el arnes de pruebas. Se aleja el valor de esa
    ventana (64 KB, mas que de sobra para una sola funcion) conservando el resto de sus bits."""
    fis = v & 0x1FFFFFFF
    if (BASE_C & 0x1FFFFFFF) <= fis < (BASE_C & 0x1FFFFFFF) + 0x10000:
        v ^= 0x00800000
    return v & 0xFFFFFFFF


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
                r[i] = _evitar_base_c(v)
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
def tablas_de_saltos():
    """Rangos fisicos [desde, hasta) de las tablas de saltos (jtbl_). Son direcciones de codigo fijas: el
    C tiene su propia tabla, asi que cambiarlas en una variante solo rompe el original."""
    rangos, ini = [], None
    for ruta in glob.glob(os.path.join(AQUI, "asm", "data", "*.s")):
        for l in open(ruta, errors="replace"):
            m = re.match(r"dlabel (jtbl_[0-9A-F]{8})", l)
            if m:
                ini = int(m.group(1)[5:], 16) & 0x1FFFFFFF
            elif l.startswith("enddlabel jtbl_") and ini is not None:
                rangos.append((ini, ultimo + 4))
                ini = None
            elif ini is not None:
                m = re.search(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ", l)
                if m:
                    ultimo = int(m.group(1), 16) & 0x1FFFFFFF
    return rangos


def en_tabla_de_saltos(d):
    return any(a <= d < b for a, b in tablas_de_saltos())


@functools.lru_cache(maxsize=1)
def direcciones_cop2():
    return gte.instrucciones_cop2(desensamblado()[0])


@functools.lru_cache(maxsize=16)
def _memoria(captura):
    """La RAM y el scratchpad de una captura, guardados en memoria: son 2 MB por captura y cada variante
    arranca de ahi; leerlos del disco de Windows en cada corrida era lo que hacia lento el lote."""
    return open(captura + ".ram", "rb").read(), open(captura + ".spad", "rb").read()


def ejecutar(captura, pc, codigo_c, regs=None, parche=None, trazar=False, propia=None, tope_seg=None,
             cuenta=None):
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
    uc.mem_map(0x1F800000, 0x00001000)            # scratchpad
    # los registros de hardware (0x1F801000-0x1F803000) van como MMIO: lo que se escribe se anota en hw y se
    # puede volver a leer. Antes era memoria comun con un gancho de escritura, y Unicorn tiene un fallo con
    # ese gancho: un sw/sh al hardware en el hueco de retardo de un salto hacia saltar a 0 (func_8003E914 y
    # func_8003E0C4 daban error en la original y no en el C). Con MMIO no pasa.
    hw = []
    io = bytearray(0x2000)
    cd = modelo_cd.Cd() if CD else None
    # DICR (0x1F8010F4) como en la consola (04-10): las banderas de fin de DMA (bits 24-30) se borran
    # escribiendo 1; el bit 31 es el resumen. Al arrancar un DMA con su interrupcion habilitada (bit 16+n y el
    # 23) queda su bandera y la interrupcion pendiente, que se entrega en el proximo punto (ver VSync)
    dicr = {"bajo": 0, "banderas": 0}

    def io_lee(u, off, tam, _):
        if cd and 0x800 <= off < 0x804:
            return cd.lee(off - 0x800)
        if MODELOS and off == 0x0F4 and tam == 4:
            b = dicr["banderas"]
            resumen = 0x80000000 if (dicr["bajo"] & 0x8000) or (dicr["bajo"] & 0x800000 and
                                                                b & (dicr["bajo"] >> 16) & 0x7F) else 0
            return dicr["bajo"] | (b << 24) | resumen
        v = int.from_bytes(io[off:off + tam], "little")
        if GPU_LISTA and off == 0x814:
            v |= 0x1C000000          # GPUSTAT: listo para comandos, para mandar VRAM y para DMA
        if MODELOS and off in (0x088, 0x098, 0x0A8, 0x0B8, 0x0C8, 0x0D8, 0x0E8) and tam == 4:
            v &= ~0x11000000         # control de cada canal de DMA: la transferencia ya termino
        if MODELOS and off == 0x070:
            v |= 0x80                # I_STAT: el mando respondio (ACK, interrupcion 7) (04-10)
        if MODELOS and off == 0x120:
            # el contador 2 avanza 0x40 en cada lectura (04-10): las esperas con tiempo de libpad
            # (func_800290AC) terminan. Lo escrito lo pone en ese valor, como en la consola. Los contadores
            # 0 y 1 no: VSync lee el 1 hasta que dos lecturas seguidas coincidan
            v = (int.from_bytes(io[off:off + 2], "little") + 0x40) & 0xFFFF
            io[off:off + 2] = v.to_bytes(2, "little")
        if MODELOS and off == 0x824 and tam == 4:
            v = 0x80040000           # estado del MDEC: desocupado y sin datos de salida (04-10; no decodifica)
        if MODELOS and off == 0x044:
            v |= 0x7                 # estado del puerto del mando: listo para mandar, dato recibido, enviado
        return v

    def io_escribe(u, off, tam, valor, _):
        hw.append((0x1F801000 + off, tam, valor))
        io[off:off + tam] = (valor & ((1 << (8 * tam)) - 1)).to_bytes(tam, "little")
        if MODELOS and off == 0x0F4 and tam == 4:
            dicr["bajo"] = valor & 0xFFFFFF
            dicr["banderas"] &= ~(valor >> 24) & 0x7F
        elif MODELOS and off in (0x088, 0x098, 0x0A8, 0x0B8, 0x0C8, 0x0D8, 0x0E8) and tam == 4 and \
                valor & 0x01000000:
            n = (off - 0x088) >> 4
            if dicr["bajo"] & (1 << (16 + n)) and dicr["bajo"] & 0x800000:
                dicr["banderas"] |= 1 << n
        if cd and 0x800 <= off < 0x804:
            cd.escribe(off - 0x800, valor)
        elif cd and off == 0x0B8 and tam == 4 and valor & 0x01000000:
            # DMA del CD (canal 3): del sector pedido a la RAM, MADR 0x0B0 y BCR 0x0B4
            madr = int.from_bytes(io[0x0B0:0x0B4], "little") & 0x1FFFFC
            bcr = int.from_bytes(io[0x0B4:0x0B8], "little")
            n = (bcr & 0xFFFF) * max(bcr >> 16, 1) * 4
            if madr + n <= 0x200000:
                u.mem_write(madr, cd.dma(n))

    uc.mmio_map(0x1F801000, 0x2000, io_lee, None, io_escribe, None)
    uc.mem_map(0x1F803000, 0x0000D000)            # resto (expansion 2 y demas)
    uc.mem_map(0x1FC00000, 0x00080000)            # BIOS (0xBFC00000)
    if MALLOC:
        uc.mem_map(MONTON_BIOS & 0x1FFFFFFF, MONTON_TAM)
    monton = {"usado": 0}
    if MODELOS:
        uc.mem_map(TABLA_C0 & 0x1FFFFFFF, 0x1000)     # la tabla C0 del modelo y el codigo al que apunta
        uc.mem_write((TABLA_C0 & 0x1FFFFFFF) + 0x18, struct.pack("<I", TABLA_C0 + 0x100))
        uc.mem_write((TABLA_C0 & 0x1FFFFFFF) + 0x128, struct.pack("<6I", *C0_VIEJO))
    uc.mem_write(0x00000000, ram)
    uc.mem_write(0x1F800000, spad)
    if cd:
        # el modo que el juego le puso al CD antes de la captura: libcd guarda una copia (Setmode)
        cd.modo = ram[simbolos()["D_8006D320"] & 0x1FFFFF]
        loc = simbolos()["D_8006D31C"] & 0x1FFFFF
        cd.posicion(ram[loc:loc + 3])
        # si la ultima orden de libcd fue leer (ReadN/ReadS), el lector estaba leyendo al capturar
        if ram[simbolos()["D_8006D321"] & 0x1FFFFF] in (0x06, 0x1B):
            cd.leyendo = True
            # y el sector que ya habia llegado estaba pedido (request 0x80): los datos esperan en el FIFO
            cd.sector = cd._datos_del_sector(modelo_cd.sector(cd.lba))
            cd.fifo, cd.pos = cd.sector, 0
    if MODELOS:
        # el DICR de antes de la captura: habilitados los canales que tienen funcion de DMA (DMACallback)
        f = simbolos()["D_800649F4"] & 0x1FFFFF
        for n in range(7):
            if struct.unpack_from("<I", ram, f + 4 * n)[0]:
                dicr["bajo"] |= (1 << (16 + n)) | 0x800000
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

    tarjeta = {}                                      # (puerto, sector) -> 128 bytes (ver TARJETA)
    if TARJETA:
        ev_sw, ev_hw = simbolos()["D_800D5390"] & 0x1FFFFFFF, simbolos()["D_800D53A0"] & 0x1FFFFFFF

    def bios_tarjeta(u, dirc, f):
        a0, a1, a2 = (u.reg_read(UC_MIPS_REG_ZERO + r) for r in (4, 5, 6))
        if (dirc, f) == (0xB0, 0x4E):                  # _card_write(puerto, sector, bufer)
            tarjeta[(a0, a1)] = bytes(u.mem_read(a2 & 0x1FFFFFFF, 128))
        elif (dirc, f) == (0xB0, 0x4F):                # _card_read(puerto, sector, bufer)
            u.mem_write(a2 & 0x1FFFFFFF, tarjeta.get((a0, a1), bytes(128)))
        elif (dirc, f) not in ((0xA0, 0xAB), (0xA0, 0xAC)):   # _card_info, _card_load
            return (dirc, f) in ((0xB0, 0x5C), (0xB0, 0x50))  # _card_status: lista; _new_card: nada
        # termino bien: los manejadores de los eventos IOE (func_800519E4 y func_80051A34) ponen su aviso
        u.mem_write(ev_sw, struct.pack("<I", 1))
        u.mem_write(ev_hw, struct.pack("<I", 1))
        return True

    def codigo(u, dirc, tam, _):
        if dirc in (0xA0, 0xB0, 0xC0):                 # llamada a la BIOS: volver sin hacer nada
            if TARJETA and bios_tarjeta(u, dirc, u.reg_read(UC_MIPS_REG_ZERO + 9)):
                u.reg_write(UC_MIPS_REG_V0, 1)
                u.reg_write(UC_MIPS_REG_PC, u.reg_read(UC_MIPS_REG_RA))
                return
            if MODELOS and dirc == 0xB0 and u.reg_read(UC_MIPS_REG_ZERO + 9) == 0x56:
                u.reg_write(UC_MIPS_REG_V0, TABLA_C0)    # GetC0Table: la tabla del modelo (ver TABLA_C0)
            if MALLOC and dirc == 0xA0 and u.reg_read(UC_MIPS_REG_ZERO + 9) == 0x33:
                tam = (u.reg_read(UC_MIPS_REG_A0) + 7) & ~7          # malloc (ver MONTON_BIOS)
                if monton["usado"] + tam <= MONTON_TAM:
                    u.reg_write(UC_MIPS_REG_V0, MONTON_BIOS + monton["usado"])
                    monton["usado"] += tam
                else:
                    u.reg_write(UC_MIPS_REG_V0, 0)
            u.reg_write(UC_MIPS_REG_PC, u.reg_read(UC_MIPS_REG_RA))

    interrupcion_mala = []

    pc_escrito = []                                   # lo que se mando a la PC de desarrollo (ver PCDRV)
    pc_abiertos = {"n": 0}

    def pcdrv(codigo_break, u):
        a1, a2, a3 = (u.reg_read(UC_MIPS_REG_ZERO + r) for r in (5, 6, 7))
        if codigo_break == 0x102:                      # PCcreat(nombre): manejador en v1
            nombre = bytes(u.mem_read(a1 & 0x1FFFFFFF, 64)).split(bytes(1))[0]
            pc_abiertos["n"] += 1
            pc_escrito.append(("crear", nombre, pc_abiertos["n"]))
            u.reg_write(UC_MIPS_REG_V0, 0)
            u.reg_write(UC_MIPS_REG_V1, pc_abiertos["n"])
        elif codigo_break == 0x104:                    # PCclose(manejador)
            pc_escrito.append(("cerrar", a1))
            u.reg_write(UC_MIPS_REG_V0, 0)
            u.reg_write(UC_MIPS_REG_V1, 0)
        elif codigo_break == 0x106:                    # PCwrite(manejador, largo, datos): v1 lo escrito
            datos = bytes(u.mem_read(a3 & 0x1FFFFFFF, a2)) if 0 < a2 <= 0x200000 else b""
            pc_escrito.append(("escribir", a1, datos))
            u.reg_write(UC_MIPS_REG_V0, 0)
            u.reg_write(UC_MIPS_REG_V1, len(datos))
        else:
            interrupcion_mala.append(f"PCdrv {codigo_break:x} sin modelo")
            u.emu_stop()

    def interrupcion(u, intno, _):
        # unico uso de "syscall" en el juego: EnterCriticalSection/ExitCriticalSection (psyq_g01.c), que
        # apagan/prenden las interrupciones de la CPU real; Unicorn no modela eso. Al llegar aca el pc ya
        # quedo apuntando a la instruccion siguiente al syscall (no hace falta avanzarlo), asi que solo se
        # deja v0 en 1 (exito, como devuelve la BIOS real) para que ambas versiones sigan igual
        d = u.reg_read(UC_MIPS_REG_PC)
        previa = struct.unpack_from("<I", u.mem_read((d - 4) & 0x1FFFFFFF, 4))[0]
        if (previa >> 26) == 0 and (previa & 0x3F) == 0x0C:
            u.reg_write(UC_MIPS_REG_V0, 1)
        else:
            interrupcion_mala.append(f"interrupcion no manejada en {d:08x}")
            u.emu_stop()

    uc.hook_add(UC_HOOK_CODE, codigo, begin=0xA0, end=0xC4)
    if PCDRV:
        # Unicorn no avisa el break como interrupcion (salta al vector de excepciones): un gancho en cada uno
        def break_pcdrv(u, dirc, tam, _):
            ins = struct.unpack("<I", bytes(u.mem_read(dirc & 0x1FFFFFFF, 4)))[0]
            pcdrv((ins >> 6) & 0xFFFFF, u)
            u.reg_write(UC_MIPS_REG_PC, dirc + 4)

        for f, off in (("func_800294F0", 0xC), ("func_80029518", 0x8), ("func_80029530", 0xC)):
            d = simbolos()[f] + off
            uc.hook_add(UC_HOOK_CODE, break_pcdrv, begin=d, end=d)
    if MODELOS:
        espera, contador = simbolos()["func_800161D4"], simbolos()["D_800649EC"] & 0x1FFFFFFF

        def vsync(u, dirc, tam, _):
            objetivo = u.reg_read(UC_MIPS_REG_A0)
            ahora = struct.unpack("<i", bytes(u.mem_read(contador, 4)))[0]
            if ahora < (objetivo if objetivo < 0x80000000 else objetivo - 0x100000000):
                u.mem_write(contador, struct.pack("<I", objetivo & 0xFFFFFFFF))

        uc.hook_add(UC_HOOK_CODE, vsync, begin=espera, end=espera)
        # y cada llamada a VSync hace pasar un cuadro: los que preguntan VSync(-1) esperando que avance
        # (las cargas, las pantallas legales) si no, giran para siempre
        entrada = simbolos()["func_8001626C"]

        def cuadro(u, dirc, tam, _):
            ahora = struct.unpack("<I", bytes(u.mem_read(contador, 4)))[0]
            u.mem_write(contador, struct.pack("<I", (ahora + 1) & 0xFFFFFFFF))

        if not (VBLANK or CD):
            uc.hook_add(UC_HOOK_CODE, cuadro, begin=entrada, end=entrada)
        else:
            # en la entrada de VSync, como interrupciones: la del CD (si tiene algo) y la de VBlank. Se guardan
            # todos los registros, cada rutina corre en la pila de las interrupciones y vuelve a VUELTA_INT;
            # al terminar la ultima se restauran y se entra de nuevo a VSync, que esta vez sigue de largo.
            s = simbolos()
            pila_int = s["D_80063954"] + 0xFDC
            pila_ini = s["D_80063954"] & 0x1FFFFFFF
            pila_int_f = pila_int & 0x1FFFFFFF
            en_int = s["D_8006391A"] & 0x1FFFFFFF
            estado = {"pendientes": [], "guardado": None, "seguir": False}

            def correr_siguiente(u):
                rutina = estado["pendientes"].pop(0)
                u.reg_write(UC_MIPS_REG_SP, pila_int)
                u.reg_write(UC_MIPS_REG_RA, VUELTA_INT)
                u.reg_write(UC_MIPS_REG_PC, rutina)

            def entrada_vsync(u, dirc, tam, _):
                if estado["seguir"]:
                    estado["seguir"] = False
                    return
                es_vsync = dirc == entrada
                if estado["guardado"] is not None:
                    # VSync llamada desde una rutina de interrupcion: un cuadro mas, sin anidar interrupciones
                    if es_vsync and not VBLANK:
                        cuadro(u, dirc, tam, _)
                    return
                pend = []
                dentro = struct.unpack("<H", bytes(u.mem_read(en_int, 2)))[0]
                if cd and cd.cuadro() and not dentro:
                    pend.append(s["func_8002A5F8"])
                elif cd and cd.tipo:
                    cd.log.append("D" if dentro else "-")
                if dicr["banderas"] & (dicr["bajo"] >> 16) & 0x7F and dicr["bajo"] & 0x800000 and not dentro:
                    pend.append(s["func_80016B4C"])      # fin de DMA (libetc)
                if not es_vsync:
                    pass
                elif VBLANK:
                    pend.append(s["func_80016A2C"])
                else:
                    cuadro(u, dirc, tam, _)
                if not pend:
                    return
                estado["volver"] = dirc
                estado["pendientes"] = pend
                estado["guardado"] = [u.reg_read(UC_MIPS_REG_ZERO + i) for i in range(32)] + \
                    [u.reg_read(UC_MIPS_REG_HI), u.reg_read(UC_MIPS_REG_LO)]
                estado["dentro"] = dentro
                # la pila de las interrupciones se deja como estaba al volver: guarda registros del codigo
                # interrumpido, que son distintos en la original y en el C (ruido del modelo, no del juego)
                estado["pila"] = bytes(u.mem_read(pila_ini, pila_int_f - pila_ini))
                u.mem_write(en_int, struct.pack("<H", 1))    # dentro de una interrupcion, como en libetc
                correr_siguiente(u)

            def vuelta(u, dirc, tam, _):
                if estado["pendientes"]:
                    correr_siguiente(u)
                    return
                r = estado["guardado"]
                for i in range(1, 32):
                    u.reg_write(UC_MIPS_REG_ZERO + i, r[i])
                u.reg_write(UC_MIPS_REG_HI, r[32])
                u.reg_write(UC_MIPS_REG_LO, r[33])
                u.mem_write(en_int, struct.pack("<H", estado["dentro"]))
                u.mem_write(pila_ini, estado["pila"])
                estado["guardado"] = None
                estado["seguir"] = not estado.pop("sin_seguir", False)
                u.reg_write(UC_MIPS_REG_PC, estado["volver"])

            uc.hook_add(UC_HOOK_CODE, entrada_vsync, begin=entrada, end=entrada)
            if cd:
                # StGetNext no espera (devuelve 1 si no hay cuadro) y el juego la llama en un bucle sin VSync:
                # al entrar tambien llegan las interrupciones del CD (solo las del CD)
                g = s["StGetNext"]
                uc.hook_add(UC_HOOK_CODE, entrada_vsync, begin=g, end=g)
            uc.hook_add(UC_HOOK_CODE, vuelta, begin=VUELTA_INT, end=VUELTA_INT)
            if cd and PCDRV:
                # CdSearchFile de un .TGA de las carpetas de la PC de desarrollo: el archivo virtual de modelo_cd
                carpetas = (b"\\GRAPHICS\\TARGA\\", b"\\GRAPHICS\\SPRITE\\", b"\\GRAPHICS\\PICTURES\\",
                            b"\\GRAPHICS\\FONT\\")

                def buscar_virtual(u, dirc, tam, _):
                    f, nom = u.reg_read(UC_MIPS_REG_ZERO + 4), u.reg_read(UC_MIPS_REG_ZERO + 5)
                    n = bytes(u.mem_read(nom & 0x1FFFFFFF, 80)).split(bytes(1))[0].upper()
                    if not (n.startswith(carpetas) and n.endswith(b".TGA;1")):
                        return
                    lba, largo = modelo_cd.archivo_virtual(n)
                    corto = n.split(b"\\")[-1][:15]
                    u.mem_write(f & 0x1FFFFFFF, bytes(modelo_cd._msf(lba)) + bytes([0]) + struct.pack("<I", largo) +
                                corto + bytes(16 - len(corto)))
                    u.reg_write(UC_MIPS_REG_V0, f)
                    u.reg_write(UC_MIPS_REG_PC, u.reg_read(UC_MIPS_REG_RA))

                uc.hook_add(UC_HOOK_CODE, buscar_virtual, begin=s["func_8002BE88"], end=s["func_8002BE88"])
            if VBLANK and TARJETA:
                # espera de la tarjeta (ver TARJETA): la misma instruccion lee el aviso en 0 dos veces seguidas
                aviso = s["D_800D52C0"] + 8
                espera_t = {"pc": None, "gancho": None}

                def dar_cuadro(u, dirc, tam, _):
                    u.hook_del(espera_t["gancho"])
                    espera_t["gancho"] = None
                    if estado["guardado"] is not None:
                        return
                    estado["volver"] = dirc
                    estado["pendientes"] = [s["func_80016A2C"]]
                    estado["guardado"] = [u.reg_read(UC_MIPS_REG_ZERO + i) for i in range(32)] +                         [u.reg_read(UC_MIPS_REG_HI), u.reg_read(UC_MIPS_REG_LO)]
                    estado["dentro"] = struct.unpack("<H", bytes(u.mem_read(en_int, 2)))[0]
                    estado["pila"] = bytes(u.mem_read(pila_ini, pila_int_f - pila_ini))
                    estado["sin_seguir"] = True
                    u.mem_write(en_int, struct.pack("<H", 1))
                    correr_siguiente(u)

                def lee_aviso(u, acceso, dirc, tam, valor, _):
                    pc = u.reg_read(UC_MIPS_REG_PC)
                    v = struct.unpack("<I", bytes(u.mem_read(aviso & 0x1FFFFFFF, 4)))[0]
                    if v != 0 or estado["guardado"] is not None:
                        espera_t["pc"] = None
                        return
                    if espera_t["pc"] == pc and espera_t["gancho"] is None:
                        espera_t["gancho"] = u.hook_add(UC_HOOK_CODE, dar_cuadro)
                        espera_t["pc"] = None
                    else:
                        espera_t["pc"] = pc

                uc.hook_add(UC_HOOK_MEM_READ, lee_aviso, begin=aviso, end=aviso + 3)
                uc.hook_add(UC_HOOK_MEM_READ, lee_aviso, begin=aviso & 0x1FFFFFFF, end=(aviso & 0x1FFFFFFF) + 3)
    uc.hook_add(UC_HOOK_INTR, interrupcion)
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
        # tope_seg: tope de tiempo (solo para la original en las variantes, ver verificar)
        uc.emu_start(pc, FIN, timeout=int(tope_seg * 1e6) if tope_seg else 0, count=cuenta or LIMITE)
    except UcError as ex:
        error = f"{ex} en {uc.reg_read(UC_MIPS_REG_PC):08x}"
    if error is None and interrupcion_mala:
        error = interrupcion_mala[0]
    if error is None and uc.reg_read(UC_MIPS_REG_PC) != FIN:
        error = f"no termino en {cuenta or LIMITE} instrucciones (pc {uc.reg_read(UC_MIPS_REG_PC):08x})"
    return dict(v0=uc.reg_read(UC_MIPS_REG_V0), v1=uc.reg_read(UC_MIPS_REG_V1),
                ram=bytes(uc.mem_read(0x00000000, 0x200000)), spad=bytes(uc.mem_read(0x1F800000, 0x400)),
                monton=bytes(uc.mem_read(MONTON_BIOS & 0x1FFFFFFF, monton["usado"])) if monton["usado"] else b"",
                tarjeta=sorted(tarjeta.items()),
                pc=pc_escrito,
                hw=hw, sp=sp, error=error, lecturas=lecturas, propias=propias, cd=cd.log if cd else [])


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
    if a.get("monton", b"") != b.get("monton", b""):
        dif.append("monton de la BIOS distinto")
    if a.get("tarjeta", []) != b.get("tarjeta", []):
        dif.append("tarjeta de memoria distinta")
    if a.get("pc", []) != b.get("pc", []):
        dif.append("lo escrito a la PC de desarrollo es distinto")
    if a["hw"] != b["hw"]:
        dif.append("escrituras de hardware distintas")
    return dif


def verificar(c, funciones, n_variantes=int(os.environ.get("SABRINA_VARIANTES", "60"))):
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
        reloj = time.time()
        escalon_max = 0              # el escalon de instrucciones mas alto en que termino la original
        # una funcion que espera al hardware (el CD, el sonido, el GPU) nunca termina en el emulador: da
        # vueltas hasta el tope de instrucciones en cada corrida. Una captura en la que la original no termina
        # no se puede comparar (las dos quedan esperando), asi que se descarta, como las variantes que dan
        # error; la funcion es NO_TERMINA solo si no termina en ninguna. Antes bastaba con la primera
        # (func_80022E58 terminaba en 5 de 8 y quedaba DISTINTO por las 3 que esperan al GPU).
        giran = set()
        for cap in caps:
            primera = ejecutar(cap[:-5], sim[f], None)
            if not (primera["error"] and "no termino" in primera["error"]):
                break
            giran.add(cap)
        if len(giran) == len(caps):
            print(f"{f}: la original no termina en el emulador (espera al hardware) -> NO_TERMINA")
            total_ok = False
            continue
        for cap in caps:
            base = cap[:-5]
            if cap in giran:
                continue
            for escalon in ESCALONES:
                a = ejecutar(base, sim[f], None, cuenta=escalon)
                if not (a["error"] and "no termino" in a["error"]):
                    break
            if a["error"] and "no termino" in a["error"]:
                giran.add(cap)
                continue
            escalon_max = max(escalon_max, escalon)
            # el rastreo va en una corrida aparte: con los ganchos de memoria puestos Unicorn a veces corre
            # distinto (func_80044C40 salta a 0 solo con ellos), asi que no se compara esa corrida
            t = ejecutar(base, sim[f], None, trazar=True, propia=(sim[f], fin_de(f)))
            entradas[base] = (t["lecturas"], t["propias"])
            b = ejecutar(base, dirs[f], codigo_c)
            d = comparar(a, b, a["sp"], con_v0)
            if d and void and not comparar(a, b, a["sp"], False):
                solo_v0 += 1
            if d:
                print(f"  {f} {os.path.basename(base)}: " + "; ".join(d))
            else:
                ok += 1
        # una funcion lenta de simular (las de biblioteca, con sus bucles largos) se prueba con menos
        # variantes: si no, una sola funcion se lleva media hora
        comparables = [c for c in caps if c not in giran]
        # (por el escalon de instrucciones y no por el tiempo: asi no prueba menos cuando la PC esta cargada)
        if escalon_max > ESCALONES[0]:
            n_variantes = max(6, n_variantes * ESCALONES[0] // escalon_max * 4)
            print(f"  {f}: la original corre hasta {escalon_max} instrucciones, se prueban {n_variantes} variantes")
        # una variante que hace girar a la original (un contador o un tamano al azar) gastaria LIMITE
        # instrucciones en cada corrida: la original de las variantes tiene de tope 16 veces el escalon de
        # instrucciones en que termino en las capturas. Si lo pasa, la variante se descarta como las que dan
        # error: solo baja la cobertura, nunca hace pasar un C distinto. Es por instrucciones y no por tiempo
        # para que el resultado no dependa de lo cargada que este la PC.
        cuenta_var = min(LIMITE, 16 * escalon_max)
        # variantes de los argumentos sobre la memoria de cada captura
        rnd = random.Random(1234)
        pool = constantes_de(f)
        v_ok = v_tot = v_mal = 0
        for cap in comparables:
            base = cap[:-5]
            regs = [int(x, 16) for x in open(base + ".regs").read().split()]
            for r in variantes(regs, pool, n_variantes, rnd):
                a = ejecutar(base, sim[f], None, r, cuenta=cuenta_var)
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
        for cap in comparables:
            base = cap[:-5]
            ram = open(base + ".ram", "rb").read()
            lecturas, propias = entradas[base]
            lista = sorted((d, t) for d, t in lecturas.items() if not en_tabla_de_saltos(d))
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
                    n &= (1 << (8 * tam)) - 1
                    if tam == 4:
                        # un puntero del juego movido justo a BASE_C tendria el mismo choque que en variantes()
                        n = _evitar_base_c(n)
                        n = _puntero_a_funcion(v, n)
                    parche[d] = n.to_bytes(tam, "little")
                a = ejecutar(base, sim[f], None, None, parche, cuenta=cuenta_var)
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
        bien = ok == len(comparables) and v_ok == v_tot
        # void a la que solo se llega por punteros: todo igual menos v0, y no se puede saber si alguien lo lee
        estado = "IGUAL" if bien else "IGUAL_V0" if lee_v0 is None and \
            solo_v0 == (len(comparables) - ok) + (v_tot - v_ok) else "DISTINTO"
        total_ok &= bien
        nota = f" ({len(giran)} capturas donde la original no termina, sin comparar)" if giran else ""
        print(f"{f}: {ok} de {len(comparables)} capturas y {v_ok} de {v_tot} variantes iguales{nota} -> {estado}")
    return total_ok


if __name__ == "__main__":
    sys.exit(0 if verificar(sys.argv[1], sys.argv[2:]) else 1)
