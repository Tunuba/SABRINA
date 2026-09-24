"""Experimento: mover el look-at de la camara independiente de Sabrina. panel_camara.py ya probo
que escribir el valor una vez no sirve -el juego lo recalcula cada frame desde la posicion de
Sabrina y lo pisa al instante-.

Tres intentos, los dos primeros documentados en el codigo de abajo porque no sirvieron:
1. Punto de interrupcion de ESCRITURA sobre esa direccion, escribiendo nuestro valor ahi mismo:
   el juego termina su propia escritura despues de la nuestra y nos pisa.
2. Lo mismo pero agendando la escritura con PCSX.nextTick (para despues de terminar el paso
   actual): a veces gana el nuestro, a veces el del juego -depende de la carrera exacta ese
   frame, probado en dos maquinas y dio resultados distintos cada vez. No sirve.
3. El que funciona: engancharse al evento GPU::Vsync (lo mismo que usa control.lua para contar
   frames) y escribir ahi, una vez por cuadro. Eso corre garantizado *despues* de toda la logica
   del juego de ese frame -no hay carrera que perder, siempre va al final-. Probado dos veces
   seguidas, las tres coordenadas quedaron clavadas las dos veces.

Instalado con eval() nomas, sin tocar control.lua ni ningun panel existente -es un experimento
aparte para ver si la idea funciona antes de meterla en panel_camara.py-.

Ojo: los puntos de interrupcion y ganchos de eventos con efecto real solo andan con el emulador en
modo interprete (-debugger -interpreter, Emu(depurar=True)), que es mas lento que el modo normal.

Esta version abre la ventana del juego y se queda esperando a que la cierres, para poder jugar y
ver el efecto -no hace la verificacion automatica por texto que hacian las versiones anteriores-.

Uso: python experimento_hook_camara.py
"""
import sys

sys.path.insert(0, r"D:\proyectos personales\Sabrina decomp\SABRINA\scripts")
from emu import RAIZ, Emu
from explorar import CUE, estado

P_SABRINA = 0x8007CAF8
OJO_MIRA_X, OJO_MIRA_Y, OJO_MIRA_Z = -0x84, -0x80, -0x7C


def s32(v):
    v = int(v)
    return v - 0x100000000 if v >= 0x80000000 else v


def rd(e, addr):
    return s32(e.eval(f"return rd32({addr})"))


with Emu(iso=CUE, log="experimento_hook_camara.log", extra=("-fastboot",), depurar=True, ui=True) as e:
    e.cargar(estado("saltar"))
    e.esperar(4)
    p = int(e.eval(f"return rd32({P_SABRINA})"))
    sx, sy, sz = rd(e, p + 0x24), rd(e, p + 0x28), rd(e, p + 0x2C)
    print(f"Sabrina en x={sx} y={sy} z={sz}")

    # punto fijo bien distinto al de Sabrina, para notar claro si el hook gana la carrera
    vx, vy, vz = sx + 2_000_000, sy - 100_000, sz + 1_500_000
    print(f"apuntando el look-at a un punto fijo x={vx} y={vy} z={vz} (independiente de Sabrina)")

    # una URL de eval larga hace que el servidor conteste 404 (ya anotado en control.lua): en vez
    # de un eval() con las tres, van tres cortitos, una por eje
    px, py, pz = p + OJO_MIRA_X, p + OJO_MIRA_Y, p + OJO_MIRA_Z
    vx_, vy_, vz_ = vx & 0xFFFFFFFF, vy & 0xFFFFFFFF, vz & 0xFFFFFFFF
    # intento 1 (no funciono): escribir DENTRO del punto de interrupcion de escritura -el juego
    # termina su propia escritura despues de la nuestra, nos pisa.
    # intento 2 (funciono, pero al azar): agendar con PCSX.nextTick -a veces gana el nuestro, a
    # veces el del juego, depende de la carrera exacta ese frame. No sirve para algo confiable.
    # intento 3: engancharse a GPU::Vsync (lo mismo que usa control.lua para contar frames) y
    # escribir ahi, una vez por cuadro, garantizado despues de toda la logica del juego de ese
    # frame -no hay carrera, va siempre al final-.
    codigo = (
        f"CAMHOOK=PCSX.Events.createEventListener('GPU::Vsync',function() "
        f"wr32({px},{vx_}) wr32({py},{vy_}) wr32({pz},{vz_}) end) return 'ok'"
    )
    print(f"  [vsync] {len(codigo)} caracteres -> {e.eval(codigo)}")
    e.esperar(10)
    mx, my, mz = rd(e, p + OJO_MIRA_X), rd(e, p + OJO_MIRA_Y), rd(e, p + OJO_MIRA_Z)
    print(f"look-at clavado en x={mx} y={my} z={mz}")

    print()
    print("Listo. La camara deberia estar mirando fijo a ese punto en el aire, lejos de Sabrina.")
    print("Movete con el control/teclado en la ventana del juego y mira que pasa.")
    print("Cerra la ventana de PCSX-Redux cuando termines (este script va a salir solo).")
    e.p.wait()
    print("ventana cerrada, listo")
