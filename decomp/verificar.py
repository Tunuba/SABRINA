"""Verifica que una funcion descompilada a C hace exactamente lo mismo que la original.

Para cada captura (capturas/<funcion>/NN.ram, .spad, .regs: memoria y registros reales al entrar a la
funcion, tomados del juego corriendo) ejecuta en Unicorn la funcion original y la version en C, cada una
desde la misma memoria, y compara el valor devuelto (v0, v1), la RAM entera, el scratchpad y lo escrito en
los registros de hardware. Se excluye la pila por debajo del sp de entrada (variables locales).

La version en C se compila con el GCC moderno para MIPS I (mipsel-linux-gnu-gcc -march=r3000) y se enlaza
en 0x80400000, fuera de los 2 MB de RAM de la PS1 pero en la misma region de 256 MB, asi un jal a las
funciones originales funciona. Todos los simbolos externos se resuelven a sus direcciones reales (los del
ELF que arma armar.sh).

Las llamadas a la BIOS (0xA0, 0xB0, 0xC0) vuelven enseguida. Las instrucciones del GTE (cop2) no las
emula Unicorn: una funcion que las use no se puede verificar asi.

Uso: python3 verificar.py src/Archivo.c Funcion [Funcion...]
"""
import glob
import os
import struct
import subprocess
import sys
import tempfile

from unicorn import Uc, UcError, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_LITTLE_ENDIAN, UC_HOOK_CODE, UC_HOOK_MEM_WRITE
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
                        "-std=gnu89", "-w", "-fcommon",
                        "-I", os.path.join(AQUI, "include"), "-o", obj, c], capture_output=True, text=True)
    if r.returncode:
        raise SystemExit("no compila:\n" + r.stderr)
    und = subprocess.run(["mipsel-linux-gnu-nm", "-u", obj], capture_output=True, text=True).stdout.split()
    und = [u for u in und if u != "U"]
    sim = simbolos()
    ld = os.path.join(tmp, "f.ld")
    with open(ld, "w") as f:
        for u in und:
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
    return open(binario, "rb").read(), dirs


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
    for k in range(32):
        base.add(1 << k)
    pool = set()
    for v in base:
        for d in (-1, 0, 1):
            pool.add((v + d) & 0xFFFFFFFF)
            pool.add((-v + d) & 0xFFFFFFFF)
    return sorted(pool)


def variantes(regs, pool, n, rnd):
    """n juegos de registros con a0-a3 cambiados por valores de pool, sumas y restas de ellos o al azar."""
    res = []
    for _ in range(n):
        r = list(regs)
        for i in (4, 5, 6, 7):
            if rnd.random() < 0.6:
                t = rnd.random()
                if t < 0.4:
                    v = rnd.choice(pool)
                elif t < 0.8:
                    v = rnd.choice(pool) + rnd.choice((1, -1)) * rnd.choice(pool)
                else:
                    v = rnd.getrandbits(32)
                r[i] = v & 0xFFFFFFFF
        res.append(r)
    return res


def ejecutar(captura, pc, codigo_c, regs=None):
    ram = open(captura + ".ram", "rb").read()
    spad = open(captura + ".spad", "rb").read()
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
    error = None
    try:
        uc.emu_start(pc, FIN, count=LIMITE)
    except UcError as ex:
        error = f"{ex} en {uc.reg_read(UC_MIPS_REG_PC):08x}"
    if error is None and uc.reg_read(UC_MIPS_REG_PC) != FIN:
        error = f"no termino en {LIMITE} instrucciones (pc {uc.reg_read(UC_MIPS_REG_PC):08x})"
    return dict(v0=uc.reg_read(UC_MIPS_REG_V0), v1=uc.reg_read(UC_MIPS_REG_V1),
                ram=bytes(uc.mem_read(0x00000000, 0x200000)), spad=bytes(uc.mem_read(0x1F800000, 0x400)),
                hw=hw, sp=sp, error=error)


def comparar(a, b, sp):
    dif = []
    if a["error"] or b["error"]:
        return [f"error original: {a['error']} / C: {b['error']}"] if a["error"] != b["error"] else []
    if a["v0"] != b["v0"]:
        dif.append(f"v0 {a['v0']:08x} contra {b['v0']:08x}")
    ini_pila = (sp & 0x1FFFFF) - 0x4000
    fin_pila = sp & 0x1FFFFF
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
        ok = 0
        for cap in caps:
            base = cap[:-5]
            a = ejecutar(base, sim[f], None)
            b = ejecutar(base, dirs[f], codigo_c)
            d = comparar(a, b, a["sp"])
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
                d = comparar(a, b, a["sp"])
                if d:
                    v_mal += 1
                    if v_mal <= 3:
                        args = " ".join(f"{x:08x}" for x in r[4:8])
                        print(f"  {f} {os.path.basename(base)} con a0-a3 {args}: " + "; ".join(d))
                else:
                    v_ok += 1
        bien = ok == len(caps) and v_ok == v_tot
        total_ok &= bien
        print(f"{f}: {ok} de {len(caps)} capturas y {v_ok} de {v_tot} variantes iguales -> "
              f"{'IGUAL' if bien else 'DISTINTO'}")
    return total_ok


if __name__ == "__main__":
    sys.exit(0 if verificar(sys.argv[1], sys.argv[2:]) else 1)
