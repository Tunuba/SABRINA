"""SABRINA, NOCHE DE BRUJAS EN EL CASTILLO: arma el disco del especial de Halloween y lo abre o lo prueba.

El especial es C del juego descompilado (decomp/src/objetos/halloween.inc, compilado dentro de la camara con
-DSABRINA_HALLOWEEN), el castillo de mapa_halloween.py, los monstruos de halloween_modelos.py y la musica de
musica_halloween.py (en la pista 3 del CD, la del pueblo). Va en su propio disco: disco\\sabrina_halloween.cue.

Uso: python halloween.py              abre el juego (arma el disco si falta)
     python halloween.py armar        vuelve a armar todo: castillo, musica, ejecutable (WSL) y disco
     python halloween.py probar       sin ventana: juega una partida entera (calabazas, portales, jefe) y saca capturas
"""
import os
import subprocess
import sys

import disco
import kart
import traducir
from emu import RAIZ, Emu
from explorar import CAP, recorrer

CUE = os.path.join(disco.DISCO, "sabrina_halloween.cue")
PISTA = os.path.join(disco.DISCO, "sabrina_halloween (Track 01).bin")
EXE = os.path.join(RAIZ, "decomp", "build", "SLUS_halloween.exe")
NIVEL = os.path.join(RAIZ, "niveles", "halloween.json")
PISTA_MUSICA = os.path.join(disco.DISCO, "sabrina_halloween (Track 03).bin")


def armar_exe():
    d = os.path.join(RAIZ, "decomp").replace("\\", "/")
    r = subprocess.run(["wsl.exe", "-d", kart.wsl(), "--cd", "/mnt/" + d[0].lower() + d[2:], "--", "python3",
                        "armar_c.py", "--solo", kart.CAMARA, "--D", "SABRINA_HALLOWEEN", "--O", "Os", "--huecos",
                        "src/mods/kart_huecos.c", "--salida", "build/SLUS_halloween.exe"], capture_output=True, text=True)
    print(r.stdout.strip(), r.stderr.strip())
    if r.returncode or "funciones en C" not in r.stdout or "otros: 0" not in r.stdout:
        sys.exit("no se pudo armar el ejecutable de Halloween (ver decomp/build/armado_c.txt)")


def armar_disco():
    import halloween_modelos as hm
    import nivel_plataformas as n
    plats, cielo = n.cargar_nivel(NIVEL)
    errores, _ = n.validar(plats)
    if errores:
        sys.exit("castillo invalido: " + "; ".join(errores))
    ino = n.nf.construir_bytes(n.nodo_de(plats), n.CONSERVAR_PLAT, sin_objetos=True, paredes=True,
                               reemplazos=hm.reemplazos(dict(n.CIELO_DEFECTO, **(cielo or {}))))
    disco.parchar({traducir.EXE: open(EXE, "rb").read(), "GRAPHICS\\HUB\\H1W.INO": ino}, PISTA)
    disco.cue_mod(CUE, PISTA)
    if os.path.exists(PISTA_MUSICA):           # la musica de terror (musica_halloween.py) en la pista del pueblo
        texto = open(CUE, encoding="utf-8").read()
        original = f'"{disco.NOMBRE} (Track 03).bin"'
        open(CUE, "w", encoding="utf-8").write(texto.replace(original, f'"{os.path.basename(PISTA_MUSICA)}"', 1))
    print("disco", CUE)


def armar():
    subprocess.run([sys.executable, os.path.join(RAIZ, "scripts", "mapa_halloween.py")], check=True)
    musica = os.path.join(RAIZ, "scripts", "musica_halloween.py")
    if os.path.exists(musica):
        subprocess.run([sys.executable, musica], check=True)
    armar_exe()
    armar_disco()


def probar():
    """Una partida entera sin ventana: X en la portada; en cada zona lleva a Sabrina a cada calabaza (escribiendo su
    posicion) y comprueba que se cuentan y que se abre el portal; lanza un cristal y saca capturas; entra por el portal.
    En la mazmorra le acierta al Rey Calabaza (pone el cristal sobre el) hasta deshacerlo y saca la fiesta del final.
    Dice que fallo, si algo fallo, y deja notas/capturas/hw_hoja.png."""
    import mapa_halloween as m
    from hoja import hoja
    from nivel_plataformas import P_SABRINA
    sim = kart.simbolos("h_")
    a = lambda nombre: sim[nombre] & 0xFFFFFFFF
    capturas, fallos = [], []
    with Emu(iso=CUE, log="halloween.log", extra=("-fastboot",), puerto=8096) as e:
        recorrer(e, "hw_arranque", kart.PASOS_HASTA_EL_HUB)
        e.esperar(20)
        s = kart.leer(e, P_SABRINA) & 0xFFFFFFFF
        leer = lambda nombre: kart.leer(e, a(nombre))

        def foto(nombre):
            r = os.path.join(CAP, f"hw_{nombre}.png")
            e.captura(r)
            capturas.append(r)

        def llevar(x, y, z):
            e.eval(f"wr32({s + 0x24},{(x << 8) & 0xFFFFFFFF}) wr32({s + 0x28},{((y - 40) << 8) & 0xFFFFFFFF}) "
                   f"wr32({s + 0x2C},{(z << 8) & 0xFFFFFFFF}) return 1")

        foto("0_portada")
        e.pulsar("CROSS", 4, 20)
        if leer("h_fase") != 2:
            fallos.append(f"la X no empezo el juego (h_fase {leer('h_fase')})")
        for z, zona in enumerate(m.zonas):
            if leer("h_zona") != z:
                fallos.append(f"zona {z + 1}: h_zona = {leer('h_zona')}")
            e.esperar(30)
            foto(f"z{z + 1}_a_entrada")
            e.lua("boton", b="UP", f=40)
            e.esperar(30)
            e.pulsar("SQUARE", 4, 6)
            foto(f"z{z + 1}_b_cristal")
            for k, (x, y, zz) in enumerate(zona["calabazas"]):
                llevar(x + 37, y, zz + 53)
                e.esperar(12)
                if k == len(zona["calabazas"]) // 2:
                    foto(f"z{z + 1}_c_calabazas")
            if zona["calabazas"]:
                if leer("h_juntadas") != len(zona["calabazas"]) or leer("h_portal") != 1:
                    fallos.append(f"zona {z + 1}: juntadas {leer('h_juntadas')} de {len(zona['calabazas'])}, "
                                  f"portal {leer('h_portal')}")
                px, py, pz = zona["portal"]
                llevar(px + 300, py, pz + 300)
                e.esperar(15)
                foto(f"z{z + 1}_d_portal")
                llevar(px, py, pz)
                e.esperar(30)
        # el jefe: cristales que le pegan hasta deshacerlo (con la segunda fase alguno se lo lleva un fantasma)
        for golpe in range(16):
            if leer("h_fase") == 3:
                break
            e.esperar(20)
            x, y, z = (leer("h_rey") + 0, kart.leer(e, a("h_rey") + 4), kart.leer(e, a("h_rey") + 8))
            e.eval(f"wr32({a('h_zap_t')},10) wr32({a('h_zap_x')},{x & 0xFFFFFFFF}) "
                   f"wr32({a('h_zap_y')},{(y - 350) & 0xFFFFFFFF}) wr32({a('h_zap_z')},{z & 0xFFFFFFFF}) return 1")
            if golpe in (0, 5):
                e.esperar(4)
                foto(f"z4_jefe{golpe}")
        e.esperar(20)
        if leer("h_fase") != 3:
            fallos.append(f"el Rey Calabaza no se deshizo (h_fase {leer('h_fase')}, vida {leer('h_rey_vida')})")
        for k in range(3):
            e.esperar(45)
            foto(f"fin{k}")
        print("vida", kart.leer(e, s + 0x118, 1), "monstruos deshechos", leer("h_derrotados"))
    hoja(os.path.join(CAP, "hw_hoja.png"), 4, capturas)
    print("FALLOS:" if fallos else "todo bien", *fallos, sep="\n  ")
    print("capturas en notas/capturas/hw_hoja.png")


if __name__ == "__main__":
    modo = sys.argv[1] if len(sys.argv) > 1 else "jugar"
    if modo == "armar":
        armar()
    elif modo == "probar":
        if not os.path.exists(CUE):
            armar()
        probar()
    elif modo == "jugar":
        if not os.path.exists(CUE):
            armar()
        print("abriendo SABRINA, NOCHE DE BRUJAS; espera unos 40 segundos a que pase la intro...", flush=True)
        with Emu(iso=CUE, log="halloween_jugar.log", extra=("-fastboot",), puerto=8095, ui=True) as e:
            recorrer(e, "hw_jugar", kart.PASOS_HASTA_EL_HUB)
            e.eval("PCSX.settings.spu.Mute = false; return 'ok'")
            print("listo: junta las calabazas; cuadrado lanza el cristal magico (cierra la ventana para terminar)",
                  flush=True)
            e.p.wait()
    else:
        print(__doc__)
