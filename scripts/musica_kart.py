"""La musica de SABRINA KART: una cancion nueva hecha solo con los sonidos del propio juego, en el lugar de la musica
del pueblo (la pista 3 del CD, MUSHUBLV), con el mismo tamano exacto.

Como en los juegos de PS1 (un banco VAB y una secuencia), cada instrumento es una muestra de los bancos de sonido del
juego (SOUND\\*\\*.VBD, sacadas con vab.py) tocada a otra altura cambiando su velocidad. Casi todas las muestras son
efectos que deslizan el tono; se usan las dos que se quedan quietas (medidas con un analisis de picos por ventana):
  E1W_043 (Egipto, 361.6 Hz, sin los primeros 0.06 s que suben)   bajo (dos octavas abajo) y arpegio
  C1W_015 (Caos, 493 Hz, sin los primeros 0.48 s que suben)        melodia y colchon
(los tonos medidos con un pico parabolico sobre toda la parte quieta de cada muestra)
y para la bateria, golpes cortos: S1W_043 muy grave como bombo, W1W_042 de caja, W1W_045 agudo de platillo cerrado y
J1W_046 de platillo. Reverberacion simple (como la de la SPU) y un limitador al final.

La cancion: La menor, 142 BPM, 64 compases que llenan justo los 108 s de musica de la pista (despues de los 2 s de
silencio del principio), asi que al repetirse no se nota el corte. Intro, tema A (Am F C G), puente B (F G Em Am),
pausa de colchon y arpegio, tema A mas fuerte, puente C (Dm Em F G) y vuelta.

Uso: python musica_kart.py      escribe disco\\sabrina_kart (Track 03).bin y notas\\sonidos\\kart_musica.wav (para oirla)
"""
import math
import os
import wave

import numpy as np

import disco

SR = 44100
PISTA_ORIGINAL = os.path.join(disco.DISCO, f"{disco.NOMBRE} (Track 03).bin")
PISTA = os.path.join(disco.DISCO, "sabrina_kart (Track 03).bin")
OIR = os.path.join(disco.RAIZ, "notas", "sonidos", "kart_musica.wav")
SONIDOS = os.path.join(disco.RAIZ, "notas", "sonidos")
SILENCIO = 150 * 588                 # los 2 s de pausa (INDEX 00 a 01) del principio de la pista, se dejan iguales
COMPASES = 64


def muestra(nombre, desde=0.0):
    ruta = os.path.join(SONIDOS, nombre[:3], nombre + ".wav")
    if not os.path.exists(ruta):
        import vab
        vab.guardar(nombre[:3])
    w = wave.open(ruta)
    x = np.frombuffer(w.readframes(w.getnframes()), np.int16).astype(np.float64) / 32768
    x = x[int(desde * w.getframerate()):]
    x = x - x.mean()
    return x / (np.abs(x).max() + 1e-9), w.getframerate()


class Instrumento:
    def __init__(self, nombre, f0, desde=0.0, ataque=0.004, suelta=0.06, filtro=None):
        self.x, self.sr = muestra(nombre, desde)
        self.f0, self.ataque, self.suelta = f0, ataque, suelta
        if filtro:                   # paso bajo de un polo (para el bajo y el bombo)
            a = math.exp(-2 * math.pi * filtro / self.sr)
            y = np.zeros_like(self.x)
            acc = 0.0
            for i, v in enumerate(self.x):
                acc = (1 - a) * v + a * acc
                y[i] = acc
            self.x = y / (np.abs(y).max() + 1e-9)

    def nota(self, frec, dur):
        """La muestra tocada a frec durante dur segundos (o hasta que se acabe), con su envolvente."""
        paso = frec / self.f0 * self.sr / SR
        n = min(int(dur * SR), int((len(self.x) - 1) / paso))
        if n <= 0:
            return np.zeros(0)
        y = np.interp(np.arange(n) * paso, np.arange(len(self.x)), self.x)
        env = np.ones(n)
        a = min(n, int(self.ataque * SR))
        env[:a] = np.linspace(0, 1, a, endpoint=False)
        s = min(n, int(self.suelta * SR))
        env[n - s:] *= np.linspace(1, 0, s)
        return y * env


def hz(midi):
    return 440.0 * 2 ** ((midi - 69) / 12)


class Mezcla:
    def __init__(self, segundos):
        self.l = np.zeros(int(segundos * SR) + SR * 4)
        self.r = np.zeros_like(self.l)
        self.rev = np.zeros_like(self.l)

    def poner(self, y, t, vol, pan=0.0, rev=0.15):
        i = int(t * SR)
        y = y * vol
        self.l[i:i + len(y)] += y * math.sqrt((1 - pan) / 2)
        self.r[i:i + len(y)] += y * math.sqrt((1 + pan) / 2)
        self.rev[i:i + len(y)] += y * rev


def reverberacion(x):
    """Schroeder: cuatro peines en paralelo y dos pasa todo (lo que hace la reverb de la SPU, a grandes rasgos)."""
    def peine(x, d, g):
        y = x.copy()
        for i in range(d, len(y), d):
            y[i:i + d] += g * y[i - d:i][: len(y[i:i + d])]
        return y

    def pasatodo(x, d, g):
        y = np.zeros_like(x)
        buf = np.zeros_like(x)
        for i in range(0, len(x), d):
            fin = min(len(x), i + d)
            ant = buf[i - d:fin - d] if i >= d else np.zeros(fin - i)
            buf[i:fin] = x[i:fin] + g * ant
            y[i:fin] = -g * buf[i:fin] + ant
        return y
    s = sum(peine(x, d, 0.80) for d in (1557, 1617, 1491, 1422)) / 4
    return pasatodo(pasatodo(s, 225, 0.5), 556, 0.5)


def componer():
    total = (os.path.getsize(PISTA_ORIGINAL) // 4) - SILENCIO
    largo = total / SR
    negra = largo / (COMPASES * 4)
    print(f"{largo:.3f} s de musica, {60 / negra:.2f} BPM")
    m = Mezcla(largo)

    arpa = Instrumento("E1W_043", 361.6, desde=0.06, ataque=0.002, suelta=0.05)
    bajo = Instrumento("E1W_043", 361.6, desde=0.06, ataque=0.003, suelta=0.04, filtro=900)
    voz = Instrumento("C1W_015", 493.0, desde=0.48, ataque=0.012, suelta=0.08)
    colchon = Instrumento("C1W_015", 493.0, desde=0.48, ataque=0.25, suelta=0.3)
    bombo = Instrumento("S1W_043", 1000.0, ataque=0.001, suelta=0.03, filtro=500)
    caja = Instrumento("W1W_042", 1000.0, ataque=0.001, suelta=0.04)
    hat = Instrumento("W1W_045", 1000.0, ataque=0.001, suelta=0.02)
    plato = Instrumento("J1W_046", 1000.0, ataque=0.001, suelta=0.2)

    acordes = {"Am": (57, 60, 64), "F": (53, 57, 60), "C": (48, 52, 55), "G": (55, 59, 62), "Em": (52, 55, 59),
               "E": (52, 56, 59), "Dm": (50, 53, 57)}
    # (compases, acordes de a uno por compas, que suena)
    secciones = [("intro", ["Am", "F", "C", "G"]),
                 ("A", ["Am", "F", "C", "G", "Am", "F", "C", "E"] * 2),
                 ("B", ["F", "G", "Em", "Am", "F", "G", "Em", "E"]),
                 ("pausa", ["Am", "F", "C", "G"]),
                 ("A2", ["Am", "F", "C", "G", "Am", "F", "C", "E"] * 2),
                 ("C", ["Dm", "Em", "F", "G", "Dm", "Em", "F", "E"]),
                 ("vuelta", ["Am", "F", "C", "G", "Am", "F", "G", "E"])]
    tema = [[(69, 2), (72, 1), (76, 1), (74, 2), (72, 2)], [(72, 2), (69, 1), (72, 1), (77, 2), (76, 2)],
            [(76, 2), (79, 2), (76, 1), (74, 1), (72, 2)], [(74, 3), (71, 1), (67, 2), (71, 2)],
            [(69, 2), (72, 1), (76, 1), (81, 2), (79, 1), (76, 1)], [(77, 2), (76, 1), (74, 1), (72, 2), (69, 2)],
            [(72, 1), (74, 1), (76, 2), (79, 2), (76, 2)], [(76, 2), (74, 1), (71, 1), (68, 2), (71, 2)]]
    puente = [[(81, 4), (79, 2), (77, 2)], [(79, 4), (77, 2), (76, 2)], [(76, 2), (74, 2), (71, 2), (76, 2)],
              [(81, 6), (None, 2)], [(77, 2), (81, 2), (84, 2), (81, 2)], [(79, 2), (83, 2), (86, 2), (83, 2)],
              [(79, 2), (76, 2), (71, 2), (74, 2)], [(76, 4), (80, 4)]]
    puente_c = [[(74, 8)], [(76, 8)], [(77, 6), (79, 2)], [(79, 4), (83, 4)],
                [(81, 4), (77, 4)], [(79, 4), (76, 4)], [(77, 2), (79, 2), (81, 2), (84, 2)], [(83, 4), (80, 4)]]
    corchea = negra / 2
    semi = negra / 4

    compas = 0
    for nombre, acs in secciones:
        for k, ac in enumerate(acs):
            t0 = compas * 4 * negra
            raiz, tercera, quinta = acordes[ac]
            fuerte = nombre in ("A2", "C")
            # bateria
            if nombre != "pausa":
                for b in range(4):
                    if nombre != "intro" or k >= 2:
                        m.poner(bombo.nota(110, 0.25), t0 + b * negra, 0.95, 0, 0.02)
                    if b in (1, 3) and nombre != "intro":
                        m.poner(caja.nota(800, 0.3), t0 + b * negra, 0.55, 0.1, 0.25)
                for c in range(8):
                    m.poner(hat.nota(1500 if c % 2 else 1300, 0.08), t0 + c * corchea, 0.22 if c % 2 else 0.3, 0.45, 0.05)
                if nombre == "A2" or (nombre == "C" and k % 2):
                    for c in range(8):
                        m.poner(hat.nota(1700, 0.05), t0 + c * corchea + semi, 0.14, -0.4, 0.05)
            if k == 0 and nombre in ("A", "B", "A2", "C"):
                m.poner(plato.nota(1000, 1.5), t0, 0.5, -0.2, 0.3)
            # bajo: corcheas, raiz y octava
            if nombre not in ("intro", "pausa"):
                for c in range(8):
                    nota = raiz - 12 + (12 if c in (3, 7) else 0)
                    m.poner(bajo.nota(hz(nota - 12), corchea * 0.9), t0 + c * corchea, 0.7, 0, 0.03)
            # arpegio en semicorcheas
            arp = [raiz + 12, tercera + 12, quinta + 12, raiz + 24]
            arp = arp + arp[::-1][1:3] + [quinta + 12, tercera + 12]
            arp = arp * 2
            for c in range(16):
                vol = 0.16 if nombre in ("A", "A2", "B", "C") else 0.24
                m.poner(arpa.nota(hz(arp[c]), semi * 0.8), t0 + c * semi, vol, -0.5 if c % 2 else 0.5, 0.3)
            # colchon: el acorde entero, largo
            if nombre in ("pausa", "B", "C", "intro"):
                for nn in (raiz + 12, tercera + 12, quinta + 12):
                    m.poner(colchon.nota(hz(nn), 4 * negra), t0, 0.12, (nn - tercera) / 30, 0.5)
            # melodia
            frases = {"A": tema, "A2": tema, "B": puente, "C": puente_c, "vuelta": tema}.get(nombre)
            if frases:
                t = t0
                for nota, d in frases[k % len(frases)]:
                    if nota is not None:
                        alto = 12 if nombre == "A2" and (k // 8) == 1 else 0
                        m.poner(voz.nota(hz(nota + alto), d * corchea * 0.95), t, 0.42 if fuerte else 0.36, 0.05, 0.3)
                        if fuerte:
                            m.poner(voz.nota(hz(nota - 12), d * corchea * 0.95), t, 0.18, -0.1, 0.3)
                    t += d * corchea
            compas += 1
    assert compas == COMPASES, compas

    # reverberacion y vuelta en circulo (la cola del final suena al principio: el lazo no se corta)
    rv = reverberacion(m.rev)
    l, r = m.l + rv, m.r + rv * 0.97
    n = total
    for c in (l, r):
        c[:len(c) - n] += c[n:]
    l, r = l[:n], r[:n]
    # limitador suave y volumen parecido al de la musica original
    estereo = np.stack([l, r], 1)
    estereo -= estereo.mean(0)
    estereo /= np.sqrt((estereo ** 2).mean()) / 0.22
    estereo = np.tanh(estereo * 1.1) / np.tanh(1.1)
    estereo *= 0.97 / np.abs(estereo).max()
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
