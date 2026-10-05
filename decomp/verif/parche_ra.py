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
        if ins >> 26 == 3:
            dest = ((dirc + 4) & 0xF0000000) | ((ins & 0x3FFFFFF) << 2)
        else:
            dest = u.reg_read(UC_MIPS_REG_ZERO + ((ins >> 21) & 31))
        if not (ini_p <= dest < fin_p):
            llamadas.append((dest, (dirc + 8) & 0xFFFFFFFF, u.reg_read(UC_MIPS_REG_SP)))

    for i in range(0, len(cod_p) - 3, 4):
        ins = struct.unpack_from("<I", cod_p, i)[0]
        if ins >> 26 == 3 or (ins >> 26 == 0 and (ins & 0x3F) == 9 and (ins & 0x1F0000) == 0):
            uc.hook_add(UC_HOOK_CODE, llamada, begin=ini_p + i, end=ini_p + i)
""")

cambiar("""                criticas=criticas, bios=bios,
""", """                criticas=criticas, bios=bios, llamadas=llamadas,
""")

cambiar("""        malos = [i for i in range(0, 0x200000, 4) if ra[i:i + 4] != rb[i:i + 4] and not (ini_pila <= i < fin_pila)]
""", """        malos = [i for i in range(0, 0x200000, 4) if ra[i:i + 4] != rb[i:i + 4] and not (ini_pila <= i < fin_pila)]
        la, lb = a.get("llamadas", []), b.get("llamadas", [])
        if malos and la and [x[0] for x in la] == [x[0] for x in lb]:
            pares = {(x[1], y[1]) for x, y in zip(la, lb)} | {(x[2], y[2]) for x, y in zip(la, lb)}
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
        PILA_LOCAL["bytes"] =""", """    for f in funciones:
        EN_PRUEBA["f"] = f
        PILA_LOCAL["bytes"] =""")

cambiar("""PILA_LOCAL = {"bytes": 0x4000}
""", """PILA_LOCAL = {"bytes": 0x4000}
# la funcion que se esta verificando (la pone verificar(); el modelo de VSync la mira)
EN_PRUEBA = {"f": None}
""")

open(dst, "w", encoding="utf-8", newline="").write(t)
print("ok")
