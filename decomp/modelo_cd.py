"""Modelo del lector de CD de la PS1 para verificar.py (aprobado por Meme el 2026-10-04).

Imita lo que ve el juego del controlador del CD (registros 0x1F801800-0x1F801803): las ordenes y sus
respuestas (acuse INT3 y, en las de dos pasos, la respuesta completa INT2), los sectores que llegan al leer
(INT1) con sus datos sacados del .bin del disco, y la copia por DMA (canal 3) del sector a la RAM.

Las interrupciones del CD no llegan en cualquier momento: el acuse de una orden queda pendiente apenas se da
la orden (el juego puede leerlo sondeando), y lo demas (la respuesta completa, el sector siguiente) se
entrega en la proxima llamada a VSync, corriendo la rutina de interrupcion del CD de libcd (func_8002A5F8).
La original y el C llaman a la misma VSync, asi que ven lo mismo en el mismo orden.
Lo que no se modela: el audio (Play suena "en silencio"), los errores de lectura y la tapa abierta.
"""
import os

DISCO = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "disco")
CUE = "Sabrina the Teenage Witch - A Twitch in Time! (USA).cue"
RAW = 2352

_pistas = None      # [(lba de inicio, archivo, lba del principio del archivo)]
_archivos = {}


def _bcd(n):
    return (n // 10) * 16 + n % 10


def _de_bcd(b):
    return (b >> 4) * 10 + (b & 15)


def _msf(lba):
    lba += 150
    return _bcd(lba // 4500), _bcd(lba // 75 % 60), _bcd(lba % 75)


def pistas():
    global _pistas
    if _pistas is None:
        _pistas = []
        base = 0
        archivo = None
        for l in open(os.path.join(DISCO, CUE), encoding="utf-8"):
            l = l.strip()
            if l.startswith("FILE"):
                archivo = os.path.join(DISCO, l.split('"')[1])
                inicio_archivo = base
                base += os.path.getsize(archivo) // RAW
            elif l.startswith("INDEX 01"):
                m, s, f = (int(x) for x in l.split()[2].split(":"))
                _pistas.append((inicio_archivo + (m * 60 + s) * 75 + f, archivo, inicio_archivo))
    return _pistas


def sector(lba):
    """Los 2352 bytes del sector (ceros fuera del disco o en pistas de audio sin datos)."""
    for inicio, archivo, base in reversed(pistas()):
        if lba >= base:
            f = _archivos.get(archivo)
            if f is None:
                f = _archivos[archivo] = open(archivo, "rb")
            f.seek((lba - base) * RAW)
            b = f.read(RAW)
            return b + bytes(RAW - len(b))
    return bytes(RAW)


# ordenes de dos pasos (acuse y despues respuesta completa)
DOS_PASOS = {0x07, 0x08, 0x09, 0x0A, 0x15, 0x16, 0x1A, 0x1E}


class Cd:
    def __init__(self):
        self.indice = 0
        self.param = []
        self.respuesta = []          # la respuesta de la interrupcion pendiente
        self.ie = 0x1F
        self.tipo = 0                # la interrupcion pendiente (0 ninguna)
        self.cola = []               # interrupciones que esperan a la proxima VSync: (tipo, bytes)
        self.lba = 0                 # donde esta la cabeza
        self.destino = 0             # lo que pidio Setloc
        self.modo = 0
        self.leyendo = False
        self.tocando = False
        self.sector = b""            # los datos del ultimo sector leido
        self.fifo = b""              # lo que queda por sacar del sector pedido (request)
        self.pos = 0
        self.sectores = 0            # sectores entregados (tope para no leer para siempre)
        self.log = []                # para depurar (verif/traza_cd.sh)

    def estado(self):
        return 0x02 | (0x20 if self.leyendo else 0) | (0x80 if self.tocando else 0)

    # registros ------------------------------------------------------------------------------------------
    def lee(self, off):
        if off == 0:
            return (self.indice | (0x08 if not self.param else 0) | (0x10 if len(self.param) < 16 else 0) |
                    (0x20 if self.respuesta else 0) | (0x40 if self.pos < len(self.fifo) else 0))
        if off == 1:
            return self.respuesta.pop(0) if self.respuesta else 0
        if off == 2:
            if self.pos < len(self.fifo):
                self.pos += 1
                return self.fifo[self.pos - 1]
            return 0
        if self.indice & 1:
            return self.tipo | 0xE0
        return self.ie | 0xE0

    def escribe(self, off, v):
        v &= 0xFF
        if off == 0:
            self.indice = v & 3
        elif off == 1:
            if self.indice == 0:
                self.orden(v)
        elif off == 2:
            if self.indice == 0:
                self.param.append(v)
            elif self.indice == 1:
                self.ie = v & 0x1F
        elif off == 3:
            if self.indice == 0:
                if v & 0x80:
                    if self.pos >= len(self.fifo):
                        self.fifo, self.pos = self.sector, 0
                else:
                    self.fifo, self.pos = b"", 0
            elif self.indice == 1:
                if v & 7:
                    self.tipo &= ~(v & 7)
                    if self.tipo == 0:
                        self.respuesta = []
                if v & 0x40:
                    self.param = []

    # ordenes --------------------------------------------------------------------------------------------
    def _dar(self, tipo, datos):
        """Interrupcion inmediata si no hay otra pendiente; si no, a la cola."""
        if self.tipo == 0 and not self.cola:
            self.tipo, self.respuesta = tipo, list(datos)
        else:
            self.cola.append((tipo, list(datos)))

    def orden(self, c):
        p, self.param = self.param, []
        self.log.append("o%x%s" % (c, p))
        st = self.estado()
        r = [st]
        if c == 0x02 and len(p) >= 3:
            self.destino = (_de_bcd(p[0]) * 60 + _de_bcd(p[1])) * 75 + _de_bcd(p[2]) - 150
        elif c == 0x03:
            if p and p[0]:
                self.destino = pistas()[min(_de_bcd(p[0]), len(pistas())) - 1][0]
            self.lba, self.tocando, self.leyendo = self.destino, True, False
            r = [self.estado()]
        elif c in (0x06, 0x1B):
            self.lba, self.leyendo, self.tocando = self.destino, True, False
            r = [self.estado()]
        elif c in (0x08, 0x09):
            self.leyendo = self.tocando = False
        elif c == 0x0A:
            self.leyendo = self.tocando = False
            self.modo = 0
        elif c == 0x0E and p:
            self.modo = p[0]
        elif c == 0x0F:
            r = [st, self.modo, 0, 0, 0]
        elif c == 0x10:
            r = list(self.sector[0:8]) if len(self.sector) >= 8 else [0] * 8
        elif c == 0x11:
            m, s, f = _msf(self.lba)
            t = max(i for i, (ini, _, _) in enumerate(pistas()) if ini <= max(self.lba, 0)) + 1
            tm, ts, tf = _msf(self.lba - pistas()[t - 1][0] - 150)
            r = [_bcd(t), 1, tm, ts, tf, m, s, f]
        elif c == 0x13:
            r = [st, 1, _bcd(len(pistas()))]
        elif c == 0x14:
            t = _de_bcd(p[0]) if p else 0
            lba = pistas()[t - 1][0] if 1 <= t <= len(pistas()) else (pistas()[-1][0] + 1000)
            m, s, _ = _msf(lba)
            r = [st, m, s]
        elif c in (0x15, 0x16):
            self.lba = self.destino
            self.leyendo = self.tocando = False
        elif c == 0x19:
            r = [0x94, 0x09, 0x19, 0xC0]
        self._dar(3, r)
        if c in DOS_PASOS:
            fin = [self.estado()]
            if c == 0x1A:
                fin = [0x02, 0x00, 0x20, 0x00, 0x53, 0x43, 0x45, 0x41]
            self.cola.append((2, fin))

    def _datos_del_sector(self, raw):
        if self.modo & 0x20:
            return raw[12:12 + 0x924]
        return raw[24:24 + 0x800]

    def cuadro(self):
        """En cada VSync: si no hay interrupcion pendiente, pasa a la siguiente de la cola o, leyendo, llega
        el sector siguiente. Devuelve si hay una interrupcion que el juego tiene habilitada."""
        if self.tipo == 0:
            if self.cola:
                self.tipo, r = self.cola.pop(0)
                self.respuesta = r
                self.log.append("I%d" % self.tipo)
            elif self.leyendo and self.sectores < 20000:
                raw = sector(self.lba)
                self.sector = self._datos_del_sector(raw)
                self.lba += 1
                self.sectores += 1
                self.tipo, self.respuesta = 1, [self.estado()]
                self.log.append("S%d" % (self.lba - 1))
        self.log.append("v%d%s" % (self.tipo, "" if self.tipo & self.ie else "x"))
        return bool(self.tipo & self.ie)

    def dma(self, n):
        """El DMA del canal 3 lleva n bytes de lo pedido del sector."""
        b = self.fifo[self.pos:self.pos + n]
        self.pos += len(b)
        return b + bytes(n - len(b))
