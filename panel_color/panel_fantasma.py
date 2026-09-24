"""Panel para abrir el 'nivel fantasma' (scripts\\nivel_fantasma.py): un HUB alternativo con el
piso reemplazado por una malla de triangulos chicos y todo lo demas vaciado, en una ventana aparte
-no toca la sesion principal del panel_color, que sigue en el disco normal-.

Ojo, esto abre un SEGUNDO PCSX-Redux (puerto aparte, 8092) ademas del que ya usa panel_color.py:
arrancar de cero tarda cerca de un minuto (titulo, nuevo juego, saltar el video), por eso corre en
un hilo aparte para no congelar la ventana. El piso se ve (gris solido); el skybox real (SkyDome1,
sin tocar) todavia no -mismo problema de triangulos grandes, ver el docstring de nivel_fantasma.py-.

El hilo de fondo NO llama a widgets de Tkinter directo (ademas de no ser seguro entre hilos, una
prueba automatizada lo tiro con 'main thread is not in main loop'): deja mensajes en una queue.Queue
y el hilo principal la revisa solo, con self.after() programado desde si mismo -el patron que
Tkinter espera-.
"""
import os
import queue
import sys
import threading
import tkinter as tk

import estilo

RAIZ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(RAIZ, "scripts"))
import nivel_fantasma  # noqa: E402
from emu import Emu  # noqa: E402
from explorar import recorrer  # noqa: E402

PUERTO_FANTASMA = 8092
REVISAR_MS = 150


class FrameFantasma(tk.Frame):
    def __init__(self, padre, e, volver):
        super().__init__(padre, bg=estilo.BG)
        estilo.encabezado(
            self, "Nivel fantasma",
            "Un HUB alternativo: el piso pasa de 349 triangulos originales a una malla chica propia, "
            "y todo lo que no sea Sabrina/su sombra/el skybox real queda vacio. Abre en una ventana "
            "aparte, no toca esta sesion.",
            volver=volver)

        tk.Label(self, text="El piso se ve (gris solido) y la colision funciona -Sabrina camina "
                             "encima sin caerse-. El skybox original (sin tocar) todavia no se ve "
                             "-mismo problema de triangulos grandes, ver el docstring de "
                             "nivel_fantasma.py-. Arrancar de cero tarda cerca de un minuto.",
                  fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO, anchor="w",
                  wraplength=760, justify="left").pack(anchor="w", padx=14, pady=(0, 10))

        fila = tk.Frame(self, bg=estilo.BG)
        fila.pack(anchor="w", padx=14)
        self.boton_abrir = estilo.boton(fila, "Abrir el nivel fantasma", self._abrir)
        self.boton_abrir.pack(side="left")
        self.boton_cerrar = estilo.boton(fila, "Cerrar el nivel fantasma", self._cerrar)
        self.boton_cerrar.pack(side="left", padx=(6, 0))
        self.boton_cerrar.configure(state="disabled")

        self.estado_lbl = tk.Label(self, text="", fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO,
                                    anchor="w", wraplength=760, justify="left")
        self.estado_lbl.pack(anchor="w", padx=14, pady=(10, 0))

        self.e_fantasma = None  # Emu de la ventana aparte, si esta abierta
        self._cola = queue.Queue()  # (tipo, dato) que deja el hilo de fondo, para que el principal la lea
        self._revisando = False

    def _decir(self, texto):
        self.estado_lbl.configure(text=texto)

    def _abrir(self):
        if self.e_fantasma is not None:
            self._decir("ya esta abierto")
            return
        self.boton_abrir.configure(state="disabled")
        self._decir("armando el disco (si no existe todavia) y arrancando de cero, esto tarda...")
        threading.Thread(target=self._abrir_en_hilo, daemon=True).start()
        if not self._revisando:
            self._revisando = True
            self.after(REVISAR_MS, self._revisar_cola)

    def _abrir_en_hilo(self):
        try:
            ruta = nivel_fantasma.armar_disco()
            self._cola.put(("estado", f"disco listo ({os.path.basename(ruta)}); arrancando el emulador..."))
            e = Emu(iso=ruta, log="nivel_fantasma_panel.log", extra=("-fastboot",), ui=True, puerto=PUERTO_FANTASMA)
            self._cola.put(("estado", "arrancando: titulo, nuevo juego, saltando el video de entrada..."))
            recorrer(e, "fantasma_panel_arranque", "w2160 c CROSS w300 START w60 CROSS w240 c w1300 c")
            self._cola.put(("listo", e))
        except Exception as ex:
            self._cola.put(("error", str(ex)))

    def _revisar_cola(self):
        try:
            while True:
                tipo, dato = self._cola.get_nowait()
                if tipo == "estado":
                    self._decir(dato)
                elif tipo == "listo":
                    self.e_fantasma = dato
                    self._decir("listo: Sabrina esta parada en el plano invisible, jugable en la otra ventana")
                    self.boton_cerrar.configure(state="normal")
                elif tipo == "error":
                    self._decir(f"fallo: {dato}")
                    self.boton_abrir.configure(state="normal")
        except queue.Empty:
            pass
        if not self.winfo_exists():
            self._revisando = False
            return
        self.after(REVISAR_MS, self._revisar_cola)

    def _cerrar(self):
        if self.e_fantasma is not None:
            self.e_fantasma.cerrar()
            self.e_fantasma = None
        self.boton_cerrar.configure(state="disabled")
        self.boton_abrir.configure(state="normal")
        self._decir("cerrado")

    def al_salir(self):
        """Para que panel_color.py lo llame al cerrar la ventana principal y no deje el proceso huerfano."""
        if self.e_fantasma is not None:
            self.e_fantasma.cerrar()
            self.e_fantasma = None
