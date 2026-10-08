"""Modelo del lector de CD de la PS1 para verificar.py (aprobado por Meme el 2026-10-04).

Imita lo que ve el juego del controlador del CD (registros 0x1F801800-0x1F801803): las ordenes y sus
respuestas (acuse INT3 y, en las de dos pasos, la respuesta completa INT2), los sectores que llegan al leer
(INT1) con sus datos sacados del .bin del disco, y la copia por DMA (canal 3) del sector a la RAM.

Las interrupciones del CD no llegan en cualquier momento: el acuse de una orden queda pendiente apenas se da
la orden (el juego puede leerlo sondeando), y lo demas (la respuesta completa, el sector siguiente) se
entrega en la proxima llamada a VSync, corriendo la rutina de interrupcion del CD de libcd (func_8002A5F8).
La original y el C llaman a la misma VSync, asi que ven lo mismo en el mismo orden.
Lo que no se modela: el audio (Play suena "en silencio"), los errores de lectura y la tapa abierta. Los sectores
de audio XA (con el modo 0x40) se saltan sin interrupcion, como en la consola, donde van al sonido (07-10).
"""
import mmap
import struct
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


# Archivos de la PC de desarrollo (04-10): las herramientas del juego leen .TGA de carpetas que no se grabaron
# en el disco (GRAPHICS\TARGA, SPRITE, PICTURES, FONT). archivo_virtual(nombre) arma uno chico y fijo (16x16,
# 16 bits, pocos colores, sacados del nombre; las fuentes 24x32 con 4 letras) y lo pone despues del final del disco; verificar.py hace que
# CdSearchFile lo encuentre. sector() lo sirve como un sector de datos (modo 2, forma 1).
# Tambien los .TNF y .bud de cualquier carpeta de GRAPHICS que lee HerramientaArmarModelos y el .XDX de
# HerramientaArmarCuadricula (ver _modelo_virtual).
VIRTUAL_LBA = 400000
_virtuales = {}      # nombre -> (lba, tam)
_sectores_virtuales = {}


def archivo_virtual(nombre):
    if nombre not in _virtuales:
        h = sum(nombre) & 0xFF
        if nombre.endswith((b".TNF;1", b".BUD;1", b".XDX;1")):
            return _guardar_virtual(nombre, _modelo_virtual(nombre, h))
        colores = [((h * 7 + k * 37) & 0x7FFF) | (0x8000 if k & 1 else 0) for k in range(5)]
        if b"FONT" in nombre:
            # una fuente: 24x32 con 4 letras separadas por columnas de 0x7BC0 (0x1F0 despues de convertir,
            # el separador que busca func_8001ADD8)
            ancho, alto, sep = 24, 32, (5, 11, 17, 23)
        else:
            ancho, alto, sep = 16, 16, ()
        cab = bytes([0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, ancho, 0, alto, 0, 0x10, 0x20])
        pix = b"".join((0x7BC0 if x in sep else colores[(x * 3 + y * 5 + h) % 5]).to_bytes(2, "little")
                       for y in range(alto) for x in range(ancho))
        _guardar_virtual(nombre, cab + pix)
    return _virtuales[nombre]


def _guardar_virtual(nombre, datos):
    lba = VIRTUAL_LBA + 4 * len(_virtuales)
    for k in range(0, len(datos), 0x800):
        _sectores_virtuales[lba + k // 0x800] = datos[k:k + 0x800]
    _virtuales[nombre] = (lba, len(datos))
    return _virtuales[nombre]


def _modelo_virtual(nombre, h):
    """Los archivos de HerramientaArmarModelos (el .TNF y el .bud de cada modelo en GRAPHICS) y el .XDX. El .TNF: cuantos nombres (2
    bytes), cuantos bytes siguen (2) y cada nombre de textura con su largo delante (incluye el 0 del final).
    El .bud, como lo lee func_8001CB4C: un objeto raiz con un hijo y despues -1. Cada objeto: vertices,
    poligonos e hijos (2 bytes cada uno), 32 bytes, el largo del nombre (2) y el nombre, los hijos, los
    poligonos (0x1C bytes) y los vertices (0xC)."""
    s16 = lambda *v: b"".join(struct.pack("<h", x) for x in v)
    relleno = lambda n, k: bytes((h * 13 + k * 7 + i) & 0xFF for i in range(n))
    if nombre.endswith(b".XDX;1"):
        # la cuadricula de HerramientaArmarCuadricula: cuantos elementos de 12 bytes (2), de 8 (2), 4 bytes
        # que no lee y cuantos de 2 (4); despues los tres bloques
        return s16(2, 1) + relleno(4, 7) + struct.pack("<i", 3) + relleno(24, 8) + relleno(8, 9) + relleno(6, 10)
    if nombre.endswith(b".TNF;1"):
        nombres = [b"T%02X%d.TGA" % (h, k) + bytes(1) for k in range(2)]
        cuerpo = b"".join(bytes([len(n)]) + n for n in nombres)
        return s16(len(nombres), len(cuerpo)) + cuerpo
    hijo = s16(1, 1, 0) + relleno(0x20, 1) + s16(0) + relleno(0x1C, 2) + relleno(0xC, 3)
    return s16(2, 1, 1) + relleno(0x20, 4) + s16(4) + b"RAIZ" + hijo + relleno(0x1C, 5) + relleno(0x18, 6) + \
        s16(-1)


def sector(lba):
    """Los 2352 bytes del sector (ceros fuera del disco o en pistas de audio sin datos). Despues de los archivos
    virtuales, un sector de datos vacio con su cabecera: el lector sigue leyendo el sector que viene detras del
    ultimo pedido antes de que llegue el Pause, y libcd revisa la cabecera de cada uno ("CdRead: sector
    error" y vuelta a empezar si no coincide, como pasaba con todos los archivos virtuales: 600 vueltas)."""
    if lba in _sectores_virtuales or _sectores_virtuales and lba >= VIRTUAL_LBA:
        d = _sectores_virtuales.get(lba, b"")
        fin = 0x89 if lba + 1 not in _sectores_virtuales else 0x08     # datos (y fin de archivo en el ultimo)
        sub = bytes([1, 0, fin, 0]) * 2
        return bytes([0]) + bytes([0xFF]) * 10 + bytes([0]) + bytes(_msf(lba)) + bytes([2]) + sub + d + \
            bytes(RAW - 24 - len(d))
    for inicio, archivo, base in reversed(pistas()):
        if lba >= base:
            m = _archivos.get(archivo)
            if m is None:
                # mmap: el disco esta en /mnt/c (lento por archivo), asi lo cachea el sistema
                with open(archivo, "rb") as f:
                    m = _archivos[archivo] = mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ)
            b = m[(lba - base) * RAW:(lba - base + 1) * RAW]
            return b + bytes(RAW - len(b))
    return bytes(RAW)


ESPERA_DIRECTA = 64

# ordenes de dos pasos (acuse y despues respuesta completa)
DOS_PASOS = {0x07, 0x08, 0x09, 0x0A, 0x15, 0x16, 0x1A, 0x1E}


class Cd:
    def __init__(self):
        # los archivos virtuales son de cada corrida: se reparten en el orden en que se buscan y el lector lee
        # por delante del ultimo sector pedido; si quedaran de la corrida anterior (la de la original), la del
        # C encontraria con datos sectores que la original leyo vacios (func_80024450 daba DISTINTO por eso)
        _virtuales.clear()
        _sectores_virtuales.clear()
        self.indice = 0
        self.param = []
        self.respuesta = []          # la respuesta de la interrupcion pendiente
        self.ie = 0x1F
        self.tipo = 0                # la interrupcion pendiente (0 ninguna)
        self.consultas = 0           # consultas seguidas del tipo sin nada pendiente (ver lee)
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

    def posicion(self, msf):
        """La posicion de la ultima Setloc (la copia de libcd, 3 bytes en BCD)."""
        if _de_bcd(msf[0]) < 80:
            self.destino = self.lba = (_de_bcd(msf[0]) * 60 + _de_bcd(msf[1])) * 75 + _de_bcd(msf[2]) - 150

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
            # el juego consulta el lector sin VSync (una orden que espera su fin desde dentro de una
            # interrupcion, como el Pause al terminar CdRead): en la consola la respuesta llega sola al rato,
            # aca despues de ESPERA_DIRECTA consultas sin nada pendiente (04-10)
            if self.tipo == 0 and self.cola:
                self.consultas += 1
                if self.consultas >= ESPERA_DIRECTA:
                    self.consultas = 0
                    self.tipo, self.respuesta = self.cola.pop(0)
                    self.log.append("J%d" % self.tipo)
            else:
                self.consultas = 0
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
                    if not self.sector:
                        # piden un sector sin haber leido: el que estaba listo al capturar, el de la posicion
                        self.sector = self._datos_del_sector(sector(self.lba))
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
                if self.modo & 0x40 and raw[15] == 2 and raw[18] & 0x04:
                    # audio XA con el modo XA-ADPCM puesto (07-10): en la consola el sector va al sonido y no
                    # llega como datos (sin INT1). Los .STR traen uno de audio cada 8 de video; entregados como
                    # datos, la biblioteca de video no armaba ningun cuadro y el video no terminaba nunca
                    self.lba += 1
                    self.sectores += 1
                    self.log.append("A%d" % (self.lba - 1))
                    self.log.append("v0%s" % ("" if self.tipo & self.ie else "x"))
                    return False

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
