"""La musica de SABRINA, NOCHE DE BRUJAS: una cancion de terror nueva hecha solo con los sonidos del juego, en el
lugar de la musica del pueblo (la pista 3 del CD, MUSHUBLV), con su mismo tamano.

Los instrumentos son los de musica_kart.py (las dos muestras de tono quieto de los bancos VAB y los golpes cortos),
con otro caracter: Re menor, lenta (40 compases que llenan justo los 108 s de la pista, ~89 BPM, asi el lazo no se
nota), un arpegio obsesivo de piano en corcheas (Re-La-La, como en las peliculas de terror), una caja de musica que
toca una cancion de cuna tenebrosa en lo agudo, un bajo que baja de semitono en semitono (Re, Do#, Do, Si, Sib, La),
colchon de coro largo, un bombo como un corazon y alguna campanada grave.

  intro (4)  caja de musica sola sobre el colchon
  A (8)      el arpegio y el bajo; el corazon
  B (8)      la melodia de la campana
  C (8)      el bajo cromatico, todo mas oscuro
  D (8)      todo junto, la caja de musica en contracanto
  final (4)  la caja de musica sola: vuelve a la intro

Uso: python musica_halloween.py   escribe disco\\sabrina_halloween (Track 03).bin y notas\\sonidos\\halloween_musica.wav
"""
import math
import os
import wave

import numpy as np

import disco
from musica_kart import (PISTA_ORIGINAL, SILENCIO, SR, Instrumento, Mezcla, hz, reverberacion)

PISTA = os.path.join(disco.DISCO, "sabrina_halloween (Track 03).bin")
OIR = os.path.join(disco.RAIZ, "notas", "sonidos", "halloween_musica.wav")
COMPASES = 40


def componer():
    total = (os.path.getsize(PISTA_ORIGINAL) // 4) - SILENCIO
    largo = total / SR
    negra = largo / (COMPASES * 4)
    corchea = negra / 2
    print(f"{largo:.3f} s de musica, {60 / negra:.2f} BPM")
    m = Mezcla(largo)

    piano = Instrumento("E1W_043", 361.6, desde=0.06, ataque=0.002, suelta=0.12)
    bajo = Instrumento("E1W_043", 361.6, desde=0.06, ataque=0.004, suelta=0.08, filtro=600)
    campana = Instrumento("C1W_015", 493.0, desde=0.48, ataque=0.006, suelta=0.25)
    coro = Instrumento("C1W_015", 493.0, desde=0.48, ataque=0.5, suelta=0.5)
    corazon = Instrumento("S1W_043", 1000.0, ataque=0.001, suelta=0.05, filtro=300)
    golpe = Instrumento("W1W_042", 1000.0, ataque=0.001, suelta=0.08)

    # acordes (raiz, tercera, quinta) y el bajo de cada compas
    ACORDES = {"Dm": (50, 53, 57), "Bb": (46, 50, 53), "A": (45, 49, 52), "Gm": (43, 46, 50), "C#d": (49, 52, 55),
               "F": (41, 45, 48)}
    A = ["Dm", "Dm", "Bb", "A"] * 2
    C_BAJO = [50, 49, 48, 47, 46, 45, 44, 45]          # Re Do# Do Si Sib La Sol# La
    C_ACORDES = ["Dm", "A", "F", "Gm", "Bb", "A", "C#d", "A"]
    secciones = [("intro", ["Dm", "Dm", "Bb", "A"]), ("A", A), ("B", ["Dm", "Gm", "Bb", "A", "Dm", "Gm", "C#d", "A"]),
                 ("C", C_ACORDES), ("D", ["Dm", "Gm", "Bb", "A", "Dm", "Gm", "A", "A"]), ("final", ["Dm", "Dm", "Bb", "A"])]
    # la cancion de cuna de la caja de musica (corcheas; None = silencio), dos octavas arriba
    cuna = [[(74, 2), (77, 1), (76, 1), (74, 2), (69, 2)], [(70, 2), (69, 1), (67, 1), (69, 4)],
            [(74, 2), (77, 1), (79, 1), (81, 2), (77, 2)], [(76, 3), (73, 1), (76, 4)]]
    # la melodia de la campana (seccion B y D)
    tema = [[(62, 3), (65, 1), (64, 2), (57, 2)], [(58, 2), (57, 2), (55, 2), (57, 2)],
            [(62, 2), (65, 2), (69, 3), (67, 1)], [(65, 2), (64, 2), (61, 4)],
            [(62, 3), (65, 1), (64, 2), (57, 2)], [(58, 2), (62, 2), (67, 2), (65, 2)],
            [(64, 2), (61, 2), (64, 2), (67, 2)], [(69, 6), (None, 2)]]

    compas = 0
    for nombre, acs in secciones:
        for k, ac in enumerate(acs):
            t0 = compas * 4 * negra
            raiz, ter, qui = ACORDES[ac]
            # colchon de coro: el acorde entero, largo y bajo de volumen
            for nn in (raiz + 12, ter + 12, qui + 12):
                m.poner(coro.nota(hz(nn), 4 * negra), t0, 0.10 if nombre != "D" else 0.13, (nn - ter) / 30, 0.6)
            # el arpegio de piano: Re-La-La, Re-La-La, Re-La (en el acorde de turno)
            if nombre in ("A", "B", "C", "D"):
                patron = [raiz + 24, qui + 12, qui + 12, raiz + 24, qui + 12, qui + 12, raiz + 24, qui + 12]
                for c, nn in enumerate(patron):
                    m.poner(piano.nota(hz(nn), corchea * 0.9), t0 + c * corchea, 0.20 if c % 3 else 0.26,
                            -0.35 if c % 2 else 0.35, 0.35)
            # el bajo: una redonda (cromatico en la C)
            if nombre in ("A", "B", "C", "D"):
                nb = C_BAJO[k] if nombre == "C" else raiz
                m.poner(bajo.nota(hz(nb - 12), 4 * negra * 0.95), t0, 0.55, 0, 0.05)
                m.poner(bajo.nota(hz(nb - 12), negra), t0 + 2.5 * negra, 0.35, 0, 0.05)
            # el corazon: dos latidos por compas (pum-pum ... pum-pum)
            if nombre in ("A", "C", "D") or (nombre == "B" and k >= 4):
                for tb in (0, 0.45 * negra / 0.5 * 0.5, 2 * negra, 2 * negra + 0.45 * negra):
                    m.poner(corazon.nota(90, 0.3), t0 + tb, 0.85, 0, 0.05)
            # una campanada grave al empezar cada seccion
            if k == 0:
                m.poner(campana.nota(hz(50), 3.0), t0, 0.32, 0, 0.7)
                m.poner(golpe.nota(400, 0.4), t0, 0.25, -0.2, 0.5)
            # la caja de musica (intro, final y contracanto en D)
            if nombre in ("intro", "final", "D"):
                t = t0
                for nn, d in cuna[k % 4]:
                    if nn is not None:
                        m.poner(campana.nota(hz(nn + 12), d * corchea * 0.9), t, 0.20 if nombre == "D" else 0.30, 0.4,
                                0.6)
                    t += d * corchea
            # la melodia de la campana
            if nombre in ("B", "D"):
                t = t0
                for nn, d in tema[k % 8]:
                    if nn is not None:
                        m.poner(campana.nota(hz(nn + 12), d * corchea * 0.95), t, 0.36, -0.1, 0.45)
                        m.poner(campana.nota(hz(nn), d * corchea * 0.95), t, 0.14, 0.1, 0.45)
                    t += d * corchea
            compas += 1
    assert compas == COMPASES, compas

    rv = reverberacion(m.rev)
    l, r = m.l + rv * 1.2, m.r + rv * 1.15
    for c in (l, r):
        c[:len(c) - total] += c[total:]
    l, r = l[:total], r[:total]
    estereo = np.stack([l, r], 1)
    estereo -= estereo.mean(0)
    estereo /= np.sqrt((estereo ** 2).mean()) / 0.20
    estereo = np.tanh(estereo * 1.1) / np.tanh(1.1)
    estereo *= 0.95 / np.abs(estereo).max()
    print(f"rms {np.sqrt((estereo ** 2).mean()):.3f}, pico {np.abs(estereo).max():.3f}")
    return (estereo * 32767).astype("<i2")


def escribir(datos):
    original = open(PISTA_ORIGINAL, "rb").read()
    crudo = original[:SILENCIO * 4] + datos.tobytes()
    assert len(crudo) == len(original)
    open(PISTA, "wb").write(crudo)
    with wave.open(OIR, "wb") as w:
        w.setnchannels(2)
        w.setsampwidth(2)
        w.setframerate(SR)
        w.writeframes(datos.tobytes())
    print("escrito", PISTA, "y", OIR)


if __name__ == "__main__":
    escribir(componer())
