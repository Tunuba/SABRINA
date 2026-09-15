"""Mod de invencibilidad: Sabrina no pierde vida. Parche de 5 instrucciones del ejecutable.

El juego trae un truco de depuracion ("SABRINA IS INVINCIBLE", palabra en 0x8007CB74) que ningun codigo
enciende, y que ademas solo cubre dos de los cuatro danos. En vez de encenderlo:
  0x80031300  lw v0,-0x7be0(gp) -> li v0,1        dano de enemigos (FUN_800310b4), usa la rama del truco
  0x8003431C  addi v0,v0,-1     -> addi v0,v0,0   suelo peligroso tipo 4 (FUN_80033fc8)
  0x80034600  addi v0,v0,-1     -> addi v0,v0,0   suelo peligroso tipo 2
  0x8005A014  addi v0,v0,-4     -> addi v0,v0,0   golpe de 4
  0x8005A168  addi v0,v0,-4     -> addi v0,v0,0   golpe de 4
El suelo de tipo 8 (caida, muerte inmediata) se deja igual a proposito: con el truco original Sabrina
caeria para siempre.

Uso: python mod_invencible.py probar    laboratorio en el emulador, con y sin parche
"""
import os
import struct
import sys

PARCHES = [
    (0x80031300, 0x8F828420, 0x24020001),
    (0x8003431C, 0x2042FFFF, 0x20420000),
    (0x80034600, 0x2042FFFF, 0x20420000),
    (0x8005A014, 0x2042FFFC, 0x20420000),
    (0x8005A168, 0x2042FFFC, 0x20420000),
]


def _off(direccion):
    return direccion - 0x80010000 + 0x800


def parchar_exe(datos):
    d = bytearray(datos)
    for dirc, viejo, nuevo in PARCHES:
        actual = struct.unpack_from("<I", d, _off(dirc))[0]
        if actual != viejo:
            raise ValueError(f"en {dirc:08x} esperaba {viejo:08x} y hay {actual:08x}")
        struct.pack_into("<I", d, _off(dirc), nuevo)
    return bytes(d)


def probar():
    from emu import RAIZ, Emu
    cue = os.path.join(RAIZ, r"disco\Sabrina the Teenage Witch - A Twitch in Time! (USA).cue")
    vida = "return rd8(rd32(0x8007CAF8) + 0x118) .. ' barra ' .. rd8(0x8007CB1D)"
    for con_parche in (False, True):
        with Emu(iso=cue, log="invencible_lab.log", extra=("-fastboot",), depurar=True) as e:
            e.cargar(os.path.join(RAIZ, r"estados\saltar.estado"))
            e.esperar(5)
            if con_parche:          # el parche se aplica en la RAM, sobre el ejecutable ya cargado
                for dirc, _, nuevo in PARCHES:
                    e.eval(f"wr32({dirc}, {nuevo}); return 'ok'")
                e.eval("PCSX.invalidateCache(); return 'ok'")
            antes = e.eval(vida)
            e.lua("suelo", t=4, n=3)
            e.esperar(120)
            despues = e.eval(vida)
            print(f"{'con parche' if con_parche else 'original  '}: vida {antes} -> {despues}")


if __name__ == "__main__" and sys.argv[1:] == ["probar"]:
    probar()
