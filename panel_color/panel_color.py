"""Parque de juegos en vivo: arranca PCSX-Redux con ventana (a diferencia del resto de los scripts,
que lo usan oculto), carga el estado 'saltar' (HUB jugando) y abre al lado un menu con los paneles
de lo que ya esta identificado en memoria -textura de Sabrina (panel_textura.py) y valores numericos
del objeto de Sabrina y unos contadores globales (panel_memoria.py)-. Entrar y salir de cada panel
no reinicia el emulador, todos comparten la misma conexion.

Nada de esto toca el disco salvo el boton "Exportar cambios" del panel de textura (deja un .json
en esta carpeta) y aplicar_cambios.py, que lo lee y arma el disco + el .ppf.

Uso: python panel_color.py
"""
import os
import sys
import tkinter as tk

RAIZ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(RAIZ, "scripts"))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from emu import Emu  # noqa: E402
from explorar import CUE, estado  # noqa: E402

import estilo  # noqa: E402
from panel_textura import FrameTextura  # noqa: E402
from panel_memoria import FrameMovimiento, FrameVidaObjetos  # noqa: E402
from panel_camara import FrameCamara  # noqa: E402
from panel_modelos import FrameModelos  # noqa: E402
from panel_fantasma import FrameFantasma  # noqa: E402

PANELES = [
    ("Textura Sabrina", "Los colores del traje default (piernas, camisa, manos, pelo/cara...). "
                         "Clic en un swatch para cambiarlo y verlo al toque en el juego.", FrameTextura),
    ("Saltos y movimiento", "Posicion (x, y, z), empuje y velocidad vertical del objeto de Sabrina "
                             "-la gravedad le suma 0x51E cada paso-.", FrameMovimiento),
    ("Vida y objetos", "Vidas, gemas, huevos, hechizos, objetos anacronicos, y el truco escondido de "
                        "invencibilidad.", FrameVidaObjetos),
    ("Camara", "El punto al que mira la camara (confirmado) y una segunda terna sin confirmar, "
               "encontrados comparando fotos de RAM.", FrameCamara),
    ("Modelos 3D", "Escala por eje a cualquier modelo del nivel -Sabrina, el ropero, el escenario, "
                    "FashionDiva-, con vista previa en Python antes de aplicarlo de verdad.", FrameModelos),
    ("Nivel fantasma", "Abre en una ventana aparte un HUB alternativo con el piso reemplazado por "
                        "un plano de 4 triangulos y todo lo demas vaciado. El piso queda invisible "
                        "(problema sin resolver), pero la colision funciona.", FrameFantasma),
]


class App(tk.Tk):
    def __init__(self, e):
        super().__init__()
        self.e = e
        estilo.ventana_base(self, "Sabrina - parque de juegos en vivo")
        self.geometry("980x640")
        self.protocol("WM_DELETE_WINDOW", self.cerrar)
        self.actual = None
        self._paneles_fantasma = []  # instancias vivas de FrameFantasma, para poder cerrar su Emu aparte
        self.menu_principal()

    def _limpiar(self):
        if self.actual is not None:
            self.actual.destroy()
            self.actual = None

    def menu_principal(self):
        self._limpiar()
        f = tk.Frame(self, bg=estilo.BG)
        f.pack(fill="both", expand=True)
        self.actual = f
        estilo.encabezado(f, "Sabrina - parque de juegos en vivo",
                           "Elegi que parte de la memoria queres tocar mientras el HUB corre al lado. "
                           "Todo es en vivo; nada queda guardado salvo que uses 'Exportar cambios'.")
        cuerpo = tk.Frame(f, bg=estilo.BG)
        cuerpo.pack(fill="both", expand=True, padx=14, pady=6)
        for titulo, descripcion, clase in PANELES:
            estilo.boton_menu(cuerpo, titulo, descripcion, lambda c=clase: self.abrir(c))

    def abrir(self, clase):
        self._limpiar()
        self.actual = clase(self, self.e, volver=self.menu_principal)
        self.actual.pack(fill="both", expand=True)
        if clase is FrameFantasma:
            self._paneles_fantasma.append(self.actual)

    def cerrar(self):
        for f in self._paneles_fantasma:
            f.al_salir()
        self.e.cerrar()
        self.destroy()


if __name__ == "__main__":
    e = Emu(iso=CUE, log="panel_color.log", extra=("-fastboot",), ui=True)
    try:
        e.cargar(estado("saltar"))
        e.esperar(30)  # le da tiempo al juego de calcular la camara al menos una vez antes de leerla
        App(e).mainloop()
    except Exception:
        e.cerrar()
        raise
