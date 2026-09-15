"""Prueba de laboratorio de la vida y del truco de invencibilidad, en el emulador.

Lo que se sabe por Ghidra (FUN_80033fc8, el manejador de golpes de Sabrina):
  objeto de Sabrina: puntero en 0x8007CAF8 (gp - 0x7C5C, con gp = 0x80084754)
  vida: byte en objeto + 0x118; la barra de la pantalla copia el valor en 0x8007CB1D
  golpe: bit 0x10 en el halfword objeto + 0x8C y el tipo de golpe en objeto + 0x80 (4 o 2 restan 1)
  invencible: si la palabra en 0x8007CB74 (gp - 0x7BE0) no es 0, no hay dano

Uso: python prueba_vida.py
"""
import os

from emu import RAIZ, Emu

CUE = os.path.join(RAIZ, r"disco\Sabrina the Teenage Witch - A Twitch in Time! (USA).cue")
CAP = os.path.join(RAIZ, r"notas\capturas")
PTR_SABRINA, HUD_VIDA, INVENCIBLE = 0x8007CAF8, 0x8007CB1D, 0x8007CB74



def estado(e):
    return e.eval(f"local p = rd32({PTR_SABRINA}); return string.format('objeto %08x vida %d barra %d invencible %d', "
                  f"p, rd8(p + 0x118), rd8({HUD_VIDA}), rd32({INVENCIBLE}))")


def golpe(e, tipo=4):
    e.eval(f"local p = rd32({PTR_SABRINA}); wr16(p + 0x80, {tipo}); "
           f"wr16(p + 0x8c, bit.bor(rd16(p + 0x8c), 0x10)); return 'ok'")
    e.esperar(30)


with Emu(iso=CUE, log="prueba_vida.log", extra=("-fastboot",)) as e:
    e.cargar(os.path.join(RAIZ, r"estados\saltar.estado"))
    e.esperar(5)
    print("inicio      ", estado(e))
    e.captura(os.path.join(CAP, "vida_0_inicio.png"))
    golpe(e)
    print("tras golpe  ", estado(e))
    e.captura(os.path.join(CAP, "vida_1_golpe.png"))
    golpe(e)
    print("otro golpe  ", estado(e))
    e.eval(f"wr32({INVENCIBLE}, 1); return 'ok'")
    golpe(e)
    print("invencible  ", estado(e))
    golpe(e)
    print("invencible  ", estado(e))
    e.captura(os.path.join(CAP, "vida_2_invencible.png"))
log = open(os.path.join(RAIZ, r"notas\logs\prueba_vida.log"), encoding="utf-8", errors="replace").read()
print("mensajes del juego con INVINCIBLE:", log.count("INVINCIBLE"))
