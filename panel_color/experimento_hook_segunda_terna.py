"""Mismo experimento que experimento_hook_camara.py (gancho por GPU::Vsync, ya probado que
aguanta jugando de verdad), pero esta vez clavando la SEGUNDA terna sin confirmar (p - 0x78), no
el look-at (p - 0x84). Congelamos el look-at y no cambio nada en pantalla -la camara siguio a
Sabrina normal-, asi que probamos con la otra: si esta es el ojo de la camara, con esta clavada
la vista no deberia acompañarla al moverse.

Uso: python experimento_hook_segunda_terna.py
"""
import sys

sys.path.insert(0, r"D:\proyectos personales\Sabrina decomp\SABRINA\scripts")
from emu import Emu
from explorar import CUE, estado

P_SABRINA = 0x8007CAF8
TERNA_X, TERNA_Y, TERNA_Z = -0x78, -0x74, -0x70


def s32(v):
    v = int(v)
    return v - 0x100000000 if v >= 0x80000000 else v


def rd(e, addr):
    return s32(e.eval(f"return rd32({addr})"))


with Emu(iso=CUE, log="experimento_hook_segunda_terna.log", extra=("-fastboot",), depurar=True, ui=True) as e:
    e.cargar(estado("saltar"))
    e.esperar(4)
    p = int(e.eval(f"return rd32({P_SABRINA})"))
    sx, sy, sz = rd(e, p + 0x24), rd(e, p + 0x28), rd(e, p + 0x2C)
    print(f"Sabrina en x={sx} y={sy} z={sz}")

    vx, vy, vz = sx + 2_000_000, sy - 100_000, sz + 1_500_000
    print(f"clavando la segunda terna (p-0x78) en x={vx} y={vy} z={vz}")

    px, py, pz = p + TERNA_X, p + TERNA_Y, p + TERNA_Z
    vx_, vy_, vz_ = vx & 0xFFFFFFFF, vy & 0xFFFFFFFF, vz & 0xFFFFFFFF
    codigo = (
        f"CAMHOOK2=PCSX.Events.createEventListener('GPU::Vsync',function() "
        f"wr32({px},{vx_}) wr32({py},{vy_}) wr32({pz},{vz_}) end) return 'ok'"
    )
    print(f"  [vsync] {len(codigo)} caracteres -> {e.eval(codigo)}")
    e.esperar(10)
    mx, my, mz = rd(e, px), rd(e, py), rd(e, pz)
    print(f"segunda terna clavada en x={mx} y={my} z={mz}")

    print()
    print("Listo. Movete y mira si la camara te sigue o no esta vez.")
    print("Cerra la ventana de PCSX-Redux cuando termines.")
    e.p.wait()
    print("ventana cerrada, listo")
