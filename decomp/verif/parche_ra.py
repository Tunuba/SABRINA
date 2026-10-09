import sys
src, dst = sys.argv[1], sys.argv[2]
t = open(src, encoding="utf-8", newline="").read()


def cambiar(viejo, nuevo):
    global t
    assert t.count(viejo) == 1, viejo
    t = t.replace(viejo, nuevo)


cambiar("""funcion, sin los argumentos): 05-10, un C sin el FlushCache() despues de parchear codigo pasaba la prueba de
mutantes, porque el modelo no hace nada en FlushCache y no queda rastro en la RAM.""",
"""funcion, sin los argumentos): 05-10, un C sin el FlushCache() despues de parchear codigo pasaba la prueba de
mutantes, porque el modelo no hace nada en FlushCache y no queda rastro en la RAM.

Direcciones de vuelta como reubicacion (05-10): el C vive en BASE_C, asi que una funcion llamada que guarda en
memoria su direccion de vuelta (__builtin_return_address, setjmp) deja ahi una direccion dentro del C, y la
original una dentro de la original. Se anotan las llamadas que la funcion hace hacia afuera de su propio codigo
(destino, ra y sp en el momento del jal/jalr) y una palabra de RAM distinta vale si en la original es el ra (o el
sp) de la llamada k y en el C el de la llamada k, con el mismo destino. Es lo que pasaria en un ejecutable
rearmado con el C en la direccion de la original. Si las llamadas no coinciden en destino, no se reubica nada.""")

cambiar("""    uc.hook_add(UC_HOOK_CODE, codigo, begin=0xA0, end=0xC4)
""", """    uc.hook_add(UC_HOOK_CODE, codigo, begin=0xA0, end=0xC4)

    # las llamadas hacia afuera del codigo propio (ver "Direcciones de vuelta como reubicacion" arriba): un gancho
    # solo en cada jal/jalr del codigo propio, buscados en los bytes (un dato que parezca jal nunca se ejecuta)
    llamadas = []
    if codigo_c:
        ini_p, cod_p = BASE_C, codigo_c
    else:
        ini_p = pc
        fin_p = min((d for d in simbolos().values() if d > pc), default=pc + 0x400)
        cod_p = bytes(ram[(pc & 0x1FFFFF):(fin_p & 0x1FFFFF)])
    fin_p = ini_p + len(cod_p)

    def llamada(u, dirc, tam, _):
        ins = struct.unpack("<I", bytes(u.mem_read(dirc & 0x1FFFFFFF, 4)))[0]
        if ins >> 26 in (2, 3):
            dest = ((dirc + 4) & 0xF0000000) | ((ins & 0x3FFFFFF) << 2)
            if ins >> 26 == 2:
                # un j hacia afuera es una llamada de cola (GCC la usa para la ultima llamada; la original hace jal
                # y vuelve): se anota sin direccion de vuelta. Un j dentro del codigo propio es un salto comun.
                if not (ini_p <= dest < fin_p):
                    llamadas.append((dest, None, None))
                return
        else:
            dest = u.reg_read(UC_MIPS_REG_ZERO + ((ins >> 21) & 31))
        if ini_p <= dest < fin_p:
            # dentro del C: si es la copia en C de una funcion del juego, cuenta como llamada a la original; si es
            # algo solo del C (el cuerpo de un stub, una static), no se anota
            dest = MAPA_C.get(dest) if codigo_c else None
            if dest is None:
                return
        llamadas.append((dest, (dirc + 8) & 0xFFFFFFFF, u.reg_read(UC_MIPS_REG_SP)))

    for i in range(0, len(cod_p) - 3, 4):
        ins = struct.unpack_from("<I", cod_p, i)[0]
        if ins >> 26 in (2, 3) or (ins >> 26 == 0 and (ins & 0x3F) == 9 and (ins & 0x1F0000) == 0):
            uc.hook_add(UC_HOOK_CODE, llamada, begin=ini_p + i, end=ini_p + i)
""")

cambiar("""                criticas=criticas, bios=bios,
""", """                criticas=criticas, bios=bios, llamadas=llamadas,
""")

cambiar("""        malos = [i for i in range(0, 0x200000, 4) if ra[i:i + 4] != rb[i:i + 4] and not (ini_pila <= i < fin_pila)]
""", """        malos = [i for i in range(0, 0x200000, 4) if ra[i:i + 4] != rb[i:i + 4] and not (ini_pila <= i < fin_pila)]
        la, lb = a.get("llamadas", []), b.get("llamadas", [])
        if malos and la and [x[0] for x in la] == [x[0] for x in lb]:
            pares = {(x[k], y[k]) for x, y in zip(la, lb) for k in (1, 2) if x[k] is not None and y[k] is not None}
            malos = [i for i in malos if (struct.unpack_from("<I", ra, i)[0], struct.unpack_from("<I", rb, i)[0])
                     not in pares]
""")

cambiar("""    gte.poner_ganchos(uc, direcciones_cop2() | cop2_en_binario(codigo_c or b""))
""", """    est_gte = gte.poner_ganchos(uc, direcciones_cop2() | cop2_en_binario(codigo_c or b""))
    # las escrituras al cop0 (mtc0), en orden, en el ejecutable y en el C
    cop0 = []

    def escribe_cop0(u, dirc, tam, _):
        ins = struct.unpack("<I", bytes(u.mem_read(dirc & 0x1FFFFFFF, 4)))[0]
        cop0.append(((ins >> 11) & 31, u.reg_read(UC_MIPS_REG_ZERO + ((ins >> 16) & 31))))

    sitios = {d for d, (mn, _) in desensamblado()[0].items() if mn == "mtc0"}
    for i in range(0, len(codigo_c or b"") - 3, 4):
        if struct.unpack_from("<I", codigo_c, i)[0] >> 21 == 0x10 << 5 | 4:
            sitios.add(BASE_C + i)
    for d in sitios:
        uc.hook_add(UC_HOOK_CODE, escribe_cop0, begin=d, end=d)
""")

cambiar("""                criticas=criticas, bios=bios, llamadas=llamadas,
""", """                criticas=criticas, bios=bios, llamadas=llamadas,
                gte=(tuple(est_gte.datos), tuple(est_gte.ctrl)), cop0=cop0,
""")

cambiar("""    if a.get("criticas", []) != b.get("criticas", []):
""", """    if a.get("gte") != b.get("gte"):
        dif.append("coprocesador geometrico distinto")
    if a.get("cop0", []) != b.get("cop0", []):
        dif.append("escrituras al cop0 distintas")
    if a.get("criticas", []) != b.get("criticas", []):
""")

cambiar("""Direcciones de vuelta como reubicacion (05-10):""",
"""Se compara tambien como quedan el coprocesador geometrico (sus registros de datos y de control, en gte.py) y el
secuencia de escrituras al cop0 (mtc0: registro y valor). 05-10: InitGeom solo escribe ahi, y sus 8 mutantes
pasaban todos. El registro de estado de Unicorn no sirve para eso: no deja poner el bit 30 (CU2).

Direcciones de vuelta como reubicacion (05-10):""")

cambiar("UC_HOOK_INTR\n", "UC_HOOK_INTR\nfrom unicorn.mips_const import UC_MIPS_REG_CP0_STATUS\n")

cambiar("""        uc.hook_add(UC_HOOK_CODE, vsync, begin=espera, end=espera)
""", """        # salvo si la funcion bajo prueba es la propia espera (05-10): el gancho esta en la entrada de la original,
        # asi que la original salia enseguida y el C (en BASE_C, sin gancho) esperaba hasta el limite y avisaba
        if EN_PRUEBA["f"] != "func_800161D4":
            uc.hook_add(UC_HOOK_CODE, vsync, begin=espera, end=espera)
""")

cambiar("""    for f in funciones:
        PILA_LOCAL["bytes"] =""", """    MAPA_C.clear()
    MAPA_C.update({dirs[n]: sim[n] for n in dirs if n in sim})
    for f in funciones:
        EN_PRUEBA["f"] = f
        PILA_LOCAL["bytes"] =""")

cambiar("""PILA_LOCAL = {"bytes": 0x4000}
""", """PILA_LOCAL = {"bytes": 0x4000}
# la funcion que se esta verificando (la pone verificar(); el modelo de VSync la mira)
EN_PRUEBA = {"f": None}
# direccion en el C -> direccion de la original, para las funciones del C que tienen nombre del juego (verificar())
MAPA_C = {}
""")

cambiar("""            bios.append((dirc, u.reg_read(UC_MIPS_REG_ZERO + 9)))
""", """            n_bios = u.reg_read(UC_MIPS_REG_ZERO + 9)
            bios.append((dirc, n_bios) + tuple(u.reg_read(UC_MIPS_REG_A0 + i)
                                               for i in range(ARGS_BIOS.get((dirc, n_bios), 0))))
""")

cambiar("""    if a.get("bios", []) != b.get("bios", []):
        dif.append("llamadas a la BIOS distintas")
""", """    if not bios_iguales(a.get("bios", []), b.get("bios", []), ini_pila, fin_pila):
        dif.append("llamadas a la BIOS distintas")
""")

cambiar("""def comparar(a, b, sp, con_v0=True):
""", """# cuantos argumentos se comparan en cada llamada a la BIOS (tabla, funcion); las que no estan, ninguno. 05-10: los
# borradores de m2c llamaban a open, TestEvent, DeliverEvent... sin argumentos (prototipos.h las declara void) y
# pasaban, porque el modelo de la BIOS no hace nada con ellos.
ARGS_BIOS = {
    (0xA0, 0x39): 2, (0xA0, 0x49): 1, (0xA0, 0xAB): 1, (0xA0, 0xAC): 1,          # InitHeap, GPU_cw, _card_info/load
    (0xB0, 0x07): 2, (0xB0, 0x08): 4, (0xB0, 0x09): 1, (0xB0, 0x0A): 1,          # Deliver/Open/Close/WaitEvent
    (0xB0, 0x0B): 1, (0xB0, 0x0C): 1, (0xB0, 0x12): 4, (0xB0, 0x19): 1,          # Test/EnableEvent, InitPAD2, HookEntryInt
    (0xB0, 0x32): 2, (0xB0, 0x33): 3, (0xB0, 0x34): 3, (0xB0, 0x35): 3,          # open, lseek, read, write
    (0xB0, 0x36): 1, (0xB0, 0x42): 2, (0xB0, 0x43): 1, (0xB0, 0x45): 1,          # close, firstfile, nextfile, erase
    (0xB0, 0x4A): 1, (0xB0, 0x4E): 3, (0xB0, 0x4F): 3, (0xB0, 0x5B): 1,          # InitCARD2, _card_write/read, ChangeClearPad
    (0xB0, 0x5C): 1,                                                             # _card_status
    (0xC0, 0x02): 2, (0xC0, 0x03): 2, (0xC0, 0x0A): 2,                           # SysEnq/DeqIntRP, ChangeClearRCnt
}


def bios_iguales(la, lb, ini_pila, fin_pila):
    \"\"\"Las llamadas a la BIOS, con sus argumentos; un argumento que en las dos apunta a la pila local vale igual (un
    nombre de archivo armado en la pila queda en otro lugar del marco en el C).\"\"\"
    if len(la) != len(lb):
        return False
    for x, y in zip(la, lb):
        if x[:2] != y[:2]:
            return False
        for p, q in zip(x[2:], y[2:]):
            if p != q and not (p >> 29 == 4 and q >> 29 == 4 and ini_pila <= p & 0x1FFFFF < fin_pila
                               and ini_pila <= q & 0x1FFFFF < fin_pila):
                return False
    return True


def comparar(a, b, sp, con_v0=True):
""")

cambiar("""funcion, sin los argumentos): 05-10,""", """funcion, y los argumentos que dice ARGS_BIOS): 05-10,""")

open(dst, "w", encoding="utf-8", newline="").write(t)
print("ok")
