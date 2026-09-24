"""El panel de textura de Sabrina (antes todo panel_color.py): un swatch por cada color de las
paletas que ino_obj.py identifico para el traje default -zapatos, piernas, borde de cintura,
cadera, manos, brazos y las dos de la camisa (16 colores cada una), mas la de pelo/cara (256
colores, compartida con las cabezas de los otros trajes)-. Pasar el mouse por un swatch dice a que
direccion de la VRAM corresponde y que color tiene ahora; clic abre un selector de color y lo
escribe ahi mismo con escribir_vram(), asi se ve el cambio al toque en la ventana del juego.

Ctrl+clic en vez de clic normal va marcando varios swatches (quedan con un borde violeta) sin
abrirles el selector; con uno o mas marcados, "Aplicar color a la seleccion" abre un solo selector
y les pone ese mismo color a todos juntos, cada uno preservando su propio bit de transparencia.

No toca ningun archivo del disco: vive en la VRAM del emulador mientras esta abierto. El boton
"Exportar cambios" si deja algo en el disco: un .json en esta carpeta (cambios_AAAAMMDD_HHMMSS.json)
con que colores se tocaron, como desplazamiento en bytes desde el ancla de "piernas" (asi sirve en
los 14 niveles, no solo el HUB). aplicar_cambios.py lee ese .json y arma el disco + el .ppf.
"""
import json
import os
import struct
import time
import tkinter as tk
from tkinter import colorchooser, messagebox

import estilo
from mod_rosa import PIERNAS, FILA_DESDE

# desplazamiento en bytes desde el ancla de "piernas" (mismo mapa que mod_bruja.py)
BLOQUES = [
    ("zapatos", -32),
    ("piernas", 0),
    ("borde_cintura", 32),
    ("cadera", 64),
    ("manos", 96),
    ("brazos", 128),
    ("camisa_detalle", 160),
    ("camisa", 192),
]


def r5_a_r8(v):
    return (v << 3) | (v >> 2)


def r8_a_r5(v):
    return max(0, min(31, round(v / 255 * 31)))


def color_de(v):
    r, g, b = v & 31, (v >> 5) & 31, (v >> 10) & 31
    return f"#{r5_a_r8(r):02x}{r5_a_r8(g):02x}{r5_a_r8(b):02x}"


class Swatch:
    """Un color de la paleta: donde vive en la VRAM (x, y), su valor de 15 bits actual y el
    original (para saber si se toco y para exportar). delta: desplazamiento en bytes desde el
    ancla de "piernas" -sirve en cualquier nivel, la posicion (x, y) solo vale para este .TEX-."""

    def __init__(self, grupo, indice, x, y, valor, delta):
        self.grupo = grupo
        self.indice = indice
        self.x = x
        self.y = y
        self.valor = valor
        self.original = valor
        self.delta = delta


def leer_mitad_derecha(e):
    vram = e.vram()
    return b"".join(vram[(y * 1024 + 512) * 2:(y * 1024 + 1024) * 2] for y in range(512))


def armar_swatches(mitad):
    off = mitad.find(PIERNAS, FILA_DESDE * 1024)
    if off < 0:
        return None
    swatches = []
    for nombre, delta_bloque in BLOQUES:
        base = off + delta_bloque
        x0 = 512 + (base % 1024) // 2
        y0 = base // 1024
        vals = struct.unpack_from("<16H", mitad, base)
        for i, v in enumerate(vals):
            swatches.append(Swatch(nombre, i, x0 + i, y0, v, delta_bloque + i * 2))
    fila_inicio = off - (off % 1024)
    inicio_pelo = fila_inicio + 1024
    delta_pelo = inicio_pelo - off
    xp = 512 + (inicio_pelo % 1024) // 2
    yp = inicio_pelo // 1024
    vals = struct.unpack_from("<256H", mitad, inicio_pelo)
    for i, v in enumerate(vals):
        swatches.append(Swatch("pelo_cara", i, xp + i, yp, v, delta_pelo + i * 2))
    return swatches


def construir_export(tocados, nivel="H1W"):
    return {
        "generado": time.strftime("%Y-%m-%d %H:%M:%S"),
        "nivel_donde_se_probo": nivel,
        "cambios": [
            {"grupo": s.grupo, "indice": s.indice, "delta": s.delta,
             "original": f"0x{s.original:04X}", "nuevo": f"0x{s.valor:04X}"}
            for s in tocados
        ],
    }


def guardar_export(ruta, tocados, nivel="H1W"):
    with open(ruta, "w", encoding="utf-8") as f:
        json.dump(construir_export(tocados, nivel), f, indent=2, ensure_ascii=False)


class FrameTextura(tk.Frame):
    def __init__(self, padre, e, volver):
        super().__init__(padre, bg=estilo.BG)
        self.e = e
        self.swatches = None
        self.seleccionados = set()
        estilo.encabezado(
            self, "Textura Sabrina",
            "Pasa el mouse por un color para identificarlo. Clic para cambiarlo; Ctrl+clic para "
            "marcar varios y cambiarlos todos juntos. Se ve al toque en el juego.",
            volver=volver)
        self.estado_lbl = tk.Label(self, text="cargando...", fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO)
        self.estado_lbl.pack(anchor="w", padx=14)
        self.cuerpo = tk.Frame(self, bg=estilo.BG)
        self.cuerpo.pack(padx=14, pady=4, fill="both", expand=True)
        botones = tk.Frame(self, bg=estilo.BG)
        botones.pack(anchor="w", padx=14, pady=(4, 2))
        estilo.boton(botones, "Releer de la VRAM", self.releer).pack(side="left")
        estilo.boton(botones, "Exportar cambios", self.exportar).pack(side="left", padx=(6, 0))
        seleccion = tk.Frame(self, bg=estilo.BG)
        seleccion.pack(anchor="w", padx=14, pady=(0, 12))
        estilo.boton(seleccion, "Aplicar color a la seleccion", self.aplicar_a_seleccion).pack(side="left")
        estilo.boton(seleccion, "Aplicar tono (conserva sombras)", self.aplicar_tono_a_seleccion).pack(
            side="left", padx=(6, 0))
        estilo.boton(seleccion, "Limpiar seleccion", self.limpiar_seleccion).pack(side="left", padx=(6, 0))
        self.seleccion_lbl = tk.Label(seleccion, text="0 marcados", fg=estilo.FG_MUTED, bg=estilo.BG,
                                       font=estilo.TEXTO_CHICO)
        self.seleccion_lbl.pack(side="left", padx=(10, 0))
        self.cargar()

    def cargar(self):
        mitad = leer_mitad_derecha(self.e)
        self.swatches = armar_swatches(mitad)
        self.seleccionados = set()
        for w in self.cuerpo.winfo_children():
            w.destroy()
        if self.swatches is None:
            self.estado_lbl.configure(text="no se encontro la paleta de piernas en la VRAM (el HUB no cargo bien?)")
            return
        for nombre in [b[0] for b in BLOQUES]:
            self._fila(self.cuerpo, nombre, [s for s in self.swatches if s.grupo == nombre])
        tk.Label(self.cuerpo, text="pelo_cara (256, compartida con japan/stone/west)", fg=estilo.FG,
                 bg=estilo.BG, font=estilo.TEXTO, anchor="w").pack(fill="x", pady=(10, 2))
        grilla = tk.Frame(self.cuerpo, bg=estilo.BG)
        grilla.pack(anchor="w")
        pelo = [s for s in self.swatches if s.grupo == "pelo_cara"]
        for i, s in enumerate(pelo):
            self._swatch(grilla, s, fila=i // 32, col=i % 32, chico=True)
        self.estado_lbl.configure(text="Pasa el mouse por un color para identificarlo. Clic para cambiarlo.")

    def _fila(self, padre, nombre, lista):
        f = tk.Frame(padre, bg=estilo.BG)
        f.pack(fill="x", pady=2)
        tk.Label(f, text=f"{nombre:15s}", fg=estilo.FG, bg=estilo.BG, font=estilo.TEXTO,
                 width=15, anchor="w").pack(side="left")
        for s in lista:
            self._swatch(f, s)

    def _swatch(self, padre, s, fila=None, col=None, chico=False):
        lbl = tk.Label(padre, width=2 if chico else 3, height=1, bg=color_de(s.valor), relief="raised", bd=1,
                        highlightthickness=2, highlightbackground=estilo.BG, highlightcolor=estilo.BG)
        if fila is None:
            lbl.pack(side="left", padx=1)
        else:
            lbl.grid(row=fila, column=col, padx=1, pady=1)
        lbl.bind("<Enter>", lambda ev, s=s: self._mostrar(s))
        lbl.bind("<Button-1>", lambda ev, s=s, w=lbl: self._elegir(s, w))
        lbl.bind("<Control-Button-1>", lambda ev, s=s, w=lbl: self._toggle_seleccion(s, w))
        s.widget = lbl

    def _mostrar(self, s):
        r, g, b = s.valor & 31, (s.valor >> 5) & 31, (s.valor >> 10) & 31
        marca = "  [marcado]" if s in self.seleccionados else ""
        self.estado_lbl.configure(
            text=f"{s.grupo}[{s.indice}]  VRAM ({s.x},{s.y})  15 bits 0x{s.valor:04X}  "
                 f"5 bits r={r} g={g} b={b}  {color_de(s.valor)}{marca}")

    def _aplicar_valor(self, s, widget, nuevo):
        """Escribe un color de 15 bits ya armado en un swatch y en la VRAM."""
        s.valor = nuevo
        widget.configure(bg=color_de(nuevo))
        self.e.escribir_vram(s.x, s.y, 1, 1, struct.pack("<H", nuevo))

    def _elegir(self, s, widget):
        elegido = colorchooser.askcolor(color=color_de(s.valor), title=f"{s.grupo}[{s.indice}] - VRAM ({s.x},{s.y})")
        if not elegido or not elegido[0]:
            return
        r8, g8, b8 = (int(round(c)) for c in elegido[0])
        r5, g5, b5 = r8_a_r5(r8), r8_a_r5(g8), r8_a_r5(b8)
        nuevo = (s.valor & 0x8000) | r5 | (g5 << 5) | (b5 << 10)
        self._aplicar_valor(s, widget, nuevo)
        self._mostrar(s)

    def _toggle_seleccion(self, s, widget):
        if s in self.seleccionados:
            self.seleccionados.discard(s)
            widget.configure(highlightbackground=estilo.BG, highlightcolor=estilo.BG)
        else:
            self.seleccionados.add(s)
            widget.configure(highlightbackground=estilo.ACENTO, highlightcolor=estilo.ACENTO)
        self.seleccion_lbl.configure(text=f"{len(self.seleccionados)} marcados")
        self._mostrar(s)

    def limpiar_seleccion(self):
        for s in self.seleccionados:
            s.widget.configure(highlightbackground=estilo.BG, highlightcolor=estilo.BG)
        self.seleccionados.clear()
        self.seleccion_lbl.configure(text="0 marcados")

    def aplicar_a_seleccion(self):
        if not self.seleccionados:
            messagebox.showinfo("Aplicar color a la seleccion",
                                 "Todavia no marcaste ningun swatch (Ctrl+clic para marcar).")
            return
        primero = next(iter(self.seleccionados))
        elegido = colorchooser.askcolor(color=color_de(primero.valor),
                                         title=f"Color para {len(self.seleccionados)} swatches marcados")
        if not elegido or not elegido[0]:
            return
        r8, g8, b8 = (int(round(c)) for c in elegido[0])
        r5, g5, b5 = r8_a_r5(r8), r8_a_r5(g8), r8_a_r5(b8)
        for s in self.seleccionados:
            nuevo = (s.valor & 0x8000) | r5 | (g5 << 5) | (b5 << 10)
            self._aplicar_valor(s, s.widget, nuevo)
        self.estado_lbl.configure(text=f"color aplicado a {len(self.seleccionados)} swatches marcados")

    def aplicar_tono_a_seleccion(self):
        """Como aplicar_a_seleccion, pero en vez de dejarlos todos en el mismo color exacto,
        conserva el brillo propio de cada swatch y solo le cambia el matiz -asi una camisa con
        sombras sigue teniendo sombras, solo que del color nuevo. Misma idea que a_rojo/a_piel en
        mod_bruja.py."""
        if not self.seleccionados:
            messagebox.showinfo("Aplicar tono", "Todavia no marcaste ningun swatch (Ctrl+clic para marcar).")
            return
        primero = next(iter(self.seleccionados))
        elegido = colorchooser.askcolor(
            color=color_de(primero.valor),
            title=f"Tono para {len(self.seleccionados)} swatches (conserva el brillo de cada uno)")
        if not elegido or not elegido[0]:
            return
        r8, g8, b8 = (int(round(c)) for c in elegido[0])
        rt, gt, bt = r8_a_r5(r8), r8_a_r5(g8), r8_a_r5(b8)
        brillo_t = max(rt, gt, bt)
        for s in self.seleccionados:
            r, g, b = s.valor & 31, (s.valor >> 5) & 31, (s.valor >> 10) & 31
            brillo_s = max(r, g, b)
            if brillo_t == 0 or brillo_s == 0:
                nr, ng, nb = 0, 0, 0
            else:
                nr = min(31, round(rt * brillo_s / brillo_t))
                ng = min(31, round(gt * brillo_s / brillo_t))
                nb = min(31, round(bt * brillo_s / brillo_t))
            nuevo = (s.valor & 0x8000) | nr | (ng << 5) | (nb << 10)
            self._aplicar_valor(s, s.widget, nuevo)
        self.estado_lbl.configure(
            text=f"tono aplicado a {len(self.seleccionados)} swatches marcados, conservando el brillo de cada uno")

    def releer(self):
        self.cargar()
        self.estado_lbl.configure(text="releido de la VRAM")

    def exportar(self):
        tocados = [s for s in self.swatches if s.valor != s.original] if self.swatches else []
        if not tocados:
            messagebox.showinfo("Exportar cambios", "Todavia no cambiaste ningun color.")
            return
        nombre = f"cambios_{time.strftime('%Y%m%d_%H%M%S')}.json"
        ruta = os.path.join(os.path.dirname(os.path.abspath(__file__)), nombre)
        guardar_export(ruta, tocados)
        self.estado_lbl.configure(text=f"exportado {nombre} ({len(tocados)} colores cambiados)")
        messagebox.showinfo("Exportar cambios",
                             f"{len(tocados)} colores cambiados guardados en:\n{ruta}\n\n"
                             "Para armar el disco: python aplicar_cambios.py " + nombre)
