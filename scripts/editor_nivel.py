"""Editor de niveles de plataformas para Sabrina: dibujas rectangulos (plataformas con las que se puede chocar) en
una vista desde arriba, les pones altura y color, y con "Probar" arma el disco, abre el juego y deja a Sabrina en
la salida. Los niveles se guardan en niveles\\*.json. La logica (validar, armar el disco) vive en nivel_plataformas.py.

Uso: python editor_nivel.py [nivel.json]        (o doble clic en EDITOR_NIVEL.bat)

Ratón (vista desde arriba: derecha = +X, abajo = +Z; en el juego UP avanza hacia +X +Z, o sea abajo a la derecha):
  arrastrar en vacio       crea un bloque del tipo elegido en "Al crear" (se ajusta a la cuadricula de 128)
  Mayus + arrastrar        lo mismo pero sobre otro bloque (paredes encima de un suelo, rampas sobre un piso...)
  clic / arrastrar         selecciona / mueve la plataforma
  arrastrar una esquina    cambia su tamano
  rueda                    zoom
  boton derecho o central  desplaza la vista
Tipos de bloque (arriba del panel, "Al crear"): plataforma, pared (alta y maciza, para salas y pasillos) y rampa.
Cada bloque tiene su grosor (cuanto baja desde la tapa), su textura de tapa y de lado (galeria de texturas) y, si es
rampa, la altura final y el eje. El cielo (cenit, horizonte, nadir) es del nivel y se ve de fondo en la vista 3D.
Teclado: Supr borra, Ctrl+D duplica, Ctrl+S guarda, flechas mueven la seleccionada 128.
Vista 3D (abajo): arrastrar gira y inclina, rueda hace zoom, doble clic la reinicia, clic selecciona. Arranca con la
vista del juego (la camara mira hacia +X +Z). Dos plataformas pueden estar una sobre otra (ver nivel_plataformas.py);
Ctrl+clic en la planta elige la plataforma de debajo cuando hay varias apiladas.
La cruz amarilla es la salida: ahi aparece Sabrina (y reaparece si cae), asi que tiene que haber una plataforma
a altura 0 debajo. Las plataformas rojas no son alcanzables saltando (hueco > 256 o subida > 250).
Probar cierra el juego anterior; "Ir a la seleccionada" teletransporta a Sabrina en el juego abierto.
"""
import math
import os
import queue
import sys
import threading
import tkinter as tk
from tkinter import colorchooser, filedialog, messagebox, ttk

from PIL import ImageTk

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "panel_color"))
import estilo  # noqa: E402
import nivel_plataformas as np_  # noqa: E402

GRID = 128
PASOS_HASTA_EL_HUB = "w2160 CROSS w300 START w60 CROSS w240 w1300"
PUERTO = 8094


def hex_color(c):
    return "#%02x%02x%02x" % tuple(min(255, int(v)) for v in c)


SOMBRA_LADO = {"+x": 0.62, "-x": 0.62, "+z": 0.78, "-z": 0.78}   # los lados, mas oscuros que la tapa


def color_bloque(p, lado):
    """El color con que se ve un bloque en las vistas del editor: el medio de su textura por el color del bloque (como
    el juego: textura * color / 128), aclarado para que se distinga sobre el fondo oscuro."""
    tex = p.get("tex_lado" if lado else "tex_tapa", np_.TEX_DEFECTO)
    medio = np_.color_medio(tex)
    return [min(255, m * c / 128 * 1.7) for m, c in zip(medio, p["color"])]


def proyectar_caras(plats, profs, yaw, pitch, ancho, alto, zoom=1.0, sel=None, inalcanzables=()):
    """Proyeccion ortogonal de los bloques (la tapa, plana o rampa, y los lados que miran a la camara), de lo mas
    lejano a lo mas cercano (algoritmo del pintor). Devuelve (caras, (escala, mu, mv)) con caras = lista de
    dict(poly, relleno, borde, grosor, idx). Arriba = -h. Va aparte del Canvas para poder probarla sin ventana."""
    cy_, sy_ = math.cos(yaw), math.sin(yaw)
    cp, sp = math.cos(pitch), math.sin(pitch)

    def punto(x, h, z):
        arriba = -h
        u = x * cy_ + z * sy_
        w = -x * sy_ + z * cy_                       # w crece hacia donde mira la camara (horizontalmente)
        return u, arriba * cp + w * sp, w * cp - arriba * sp          # (u, v) de pantalla y profundidad

    crudas = []                                                         # (4 esquinas 3D, color, sombra, idx)
    for i, (p, prof) in enumerate(zip(plats, profs)):
        x0, z0, x1, z1 = p["x0"], p["z0"], p["x1"], p["z1"]
        yt = lambda x, z, p=p: np_.y_tapa(p, x, z)
        yb = np_.h_max(p) + prof
        ct, cl = color_bloque(p, False), color_bloque(p, True)
        crudas.append(([(x0, yt(x0, z0), z0), (x1, yt(x1, z0), z0), (x1, yt(x1, z1), z1), (x0, yt(x0, z1), z1)],
                       ct, 1.0, i))
        lados = {"+x": (1, 0, [(x1, yt(x1, z0), z0), (x1, yt(x1, z1), z1), (x1, yb, z1), (x1, yb, z0)]),
                 "-x": (-1, 0, [(x0, yt(x0, z0), z0), (x0, yt(x0, z1), z1), (x0, yb, z1), (x0, yb, z0)]),
                 "+z": (0, 1, [(x0, yt(x0, z1), z1), (x1, yt(x1, z1), z1), (x1, yb, z1), (x0, yb, z1)]),
                 "-z": (0, -1, [(x0, yt(x0, z0), z0), (x1, yt(x1, z0), z0), (x1, yb, z0), (x0, yb, z0)])}
        for k, (nx, nz, esq) in lados.items():
            if nx * sy_ - nz * cy_ > 0:                                 # la normal mira hacia la camara
                crudas.append((esq, cl, SOMBRA_LADO[k], i))
    caras = []
    for esq, col, sombra, i in crudas:
        pts = [punto(*q) for q in esq]
        caras.append((sum(q[2] for q in pts) / 4, [(q[0], q[1]) for q in pts], col, sombra, i))
    if not caras:
        return [], (1.0, 0.0, 0.0)
    us = [q[0] for c in caras for q in c[1]]
    vs = [q[1] for c in caras for q in c[1]]
    bw, bh = (max(us) - min(us)) or 1, (max(vs) - min(vs)) or 1
    escala = min((ancho - 40) / bw, (alto - 40) / bh) * zoom
    mu, mv = (max(us) + min(us)) / 2, (max(vs) + min(vs)) / 2
    salida = []
    for _prof, poly, col, sombra, i in sorted(caras, key=lambda c: -c[0]):
        pantalla = [(ancho / 2 + (u - mu) * escala, alto / 2 - (v - mv) * escala) for u, v in poly]
        mal = i in inalcanzables
        salida.append(dict(poly=pantalla, relleno=hex_color([c * sombra for c in col]), idx=i,
                           borde="#ffffff" if i == sel else "#ff5a5a" if mal else "#101014",
                           grosor=2 if i == sel or mal else 1))
    return salida, (escala, mu, mv)


def punto_en_poligono(x, y, poly):
    dentro = False
    for (ax, ay), (bx, by) in zip(poly, poly[1:] + poly[:1]):
        if (ay > y) != (by > y) and x < (bx - ax) * (y - ay) / (by - ay) + ax:
            dentro = not dentro
    return dentro


class Editor(tk.Tk):
    def __init__(self, ruta=None):
        super().__init__()
        estilo.ventana_base(self, "Editor de niveles - Sabrina")
        self.geometry("1420x860")
        self.plats = []
        self.sel = None
        self.ruta = None
        self.sucio = False
        self.zoom = 0.12                  # pixeles por unidad del modelo
        self.ox, self.oy = 420, 330       # pixel donde cae el (0, 0) del modelo
        self.arrastre = None
        self.emu = None
        self.ocupado = False
        self.alcanzables = set()
        self.cola = queue.Queue()         # lo que los hilos del juego piden hacer en la ventana
        self.yaw3d, self.pitch3d, self.zoom3d = -math.pi / 4, 0.6, 1.0   # vista 3D: como mira la camara del juego
        self.caras3d, self._arr3d = [], None
        self.cielo = dict(np_.CIELO_DEFECTO)
        self.tipo = tk.StringVar(value="plataforma")       # que se crea al arrastrar en vacio
        self._miniaturas = []                              # las PhotoImage de la galeria (si no, Tk las borra)
        self._armar_ui()
        self.after(100, self._vaciar_cola)
        self.protocol("WM_DELETE_WINDOW", self.salir)
        self.cargar_archivo(ruta or np_.NIVEL_POR_DEFECTO)

    # ------------------------------------------------------------ interfaz
    def _armar_ui(self):
        self.columnconfigure(0, weight=1)
        self.rowconfigure(0, weight=1)
        centro = tk.Frame(self, bg=estilo.BG)
        centro.grid(row=0, column=0, sticky="nsew")
        centro.columnconfigure(0, weight=1)
        centro.rowconfigure(0, weight=3)
        centro.rowconfigure(1, weight=2)
        self.canvas = tk.Canvas(centro, bg="#0c0c10", highlightthickness=0, cursor="crosshair")
        self.canvas.grid(row=0, column=0, sticky="nsew")
        self.canvas3d = tk.Canvas(centro, bg="#14141c", highlightthickness=0, cursor="fleur")
        self.canvas3d.grid(row=1, column=0, sticky="nsew", pady=(4, 0))
        c3 = self.canvas3d
        c3.bind("<ButtonPress-1>", self._ini3d)
        c3.bind("<B1-Motion>", self._giro3d)
        c3.bind("<ButtonRelease-1>", self._fin3d)
        c3.bind("<MouseWheel>", self._rueda3d)
        c3.bind("<Double-Button-1>", self._reiniciar3d)
        c3.bind("<Configure>", lambda _e: self.dibujar3d())
        lado = tk.Frame(self, bg=estilo.BG, width=360)
        lado.grid(row=0, column=1, sticky="ns", padx=8, pady=8)
        lado.grid_propagate(False)

        tk.Label(lado, text="Bloques", font=estilo.ENCABEZADO, bg=estilo.BG, fg=estilo.FG).pack(anchor="w")
        crear = tk.Frame(lado, bg=estilo.BG)
        crear.pack(fill="x")
        tk.Label(crear, text="Al crear:", bg=estilo.BG, fg=estilo.FG_MUTED, font=estilo.TEXTO_CHICO).pack(side="left")
        for valor, texto in (("plataforma", "Plataforma"), ("pared", "Pared"), ("rampa", "Rampa")):
            tk.Radiobutton(crear, text=texto, value=valor, variable=self.tipo, bg=estilo.BG, fg=estilo.FG,
                           selectcolor=estilo.BG_TARJETA, activebackground=estilo.BG, activeforeground=estilo.FG,
                           font=estilo.TEXTO_CHICO).pack(side="left", padx=4)
        self.lista = tk.Listbox(lado, height=6, bg=estilo.BG_TARJETA, fg=estilo.FG, font=estilo.TEXTO_CHICO,
                                selectbackground=estilo.ACENTO, selectforeground=estilo.ACENTO_TEXTO,
                                exportselection=False, highlightthickness=0, borderwidth=0)
        self.lista.pack(fill="x", pady=(4, 6))
        self.lista.bind("<<ListboxSelect>>", self._lista_elegida)

        fila = tk.Frame(lado, bg=estilo.BG)
        fila.pack(fill="x")
        self.campos = {}
        campos = [("nombre", "Nombre"), ("x0", "X desde"), ("z0", "Z desde"), ("x1", "X hasta"), ("z1", "Z hasta"),
                  ("alto", "Altura (+ = arriba)"), ("grosor", "Grosor (vacio = auto)"),
                  ("alto2", "Rampa: altura final"), ("eje", "Rampa: eje (x o z)"),
                  ("paso", "Cuadro tapa (256 o 512)"), ("paso_lado", "Cuadro lados (vacio = 512)")]
        for i, (clave, texto) in enumerate(campos):
            tk.Label(fila, text=texto, bg=estilo.BG, fg=estilo.FG_MUTED, font=estilo.TEXTO_CHICO).grid(
                row=i, column=0, sticky="w", pady=1)
            e = tk.Entry(fila, width=12, bg=estilo.BG_TARJETA, fg=estilo.FG, insertbackground=estilo.FG,
                         relief="flat", font=estilo.TEXTO)
            e.grid(row=i, column=1, sticky="e", padx=(8, 0), pady=1)
            e.bind("<Return>", lambda _e: self.aplicar_campos())
            e.bind("<FocusOut>", lambda _e: self.aplicar_campos())
            self.campos[clave] = e
        fila.columnconfigure(1, weight=1)
        flags = tk.Frame(lado, bg=estilo.BG)
        flags.pack(fill="x", pady=(4, 0))
        self.var_techo, self.var_pared = tk.BooleanVar(), tk.BooleanVar()
        for var, texto in ((self.var_techo, "Con techo (cara inferior)"), (self.var_pared, "Es pared (sin aviso)")):
            tk.Checkbutton(flags, text=texto, variable=var, command=self.aplicar_flags, bg=estilo.BG, fg=estilo.FG,
                           selectcolor=estilo.BG_TARJETA, activebackground=estilo.BG, activeforeground=estilo.FG,
                           font=estilo.TEXTO_CHICO).pack(side="left", padx=2)
        mats = tk.Frame(lado, bg=estilo.BG)
        mats.pack(fill="x", pady=(6, 0))
        self.boton_color = self._boton(mats, "Color", self.elegir_color, pack=False)
        self.boton_tapa = self._boton(mats, "Tapa: ...", lambda: self.elegir_textura("tex_tapa"), pack=False)
        self.boton_lado = self._boton(mats, "Lado: ...", lambda: self.elegir_textura("tex_lado"), pack=False)
        for i, b in enumerate((self.boton_color, self.boton_tapa, self.boton_lado)):
            b.grid(row=0, column=i, sticky="ew", padx=2)
        mats.columnconfigure((0, 1, 2), weight=1)

        cielo = tk.Frame(lado, bg=estilo.BG)
        cielo.pack(fill="x", pady=(8, 0))
        tk.Label(cielo, text="Cielo:", bg=estilo.BG, fg=estilo.FG_MUTED, font=estilo.TEXTO_CHICO).grid(row=0, column=0)
        self.botones_cielo = {}
        for i, (k, t) in enumerate((("cenit", "Cenit"), ("horizonte", "Horizonte"), ("nadir", "Nadir"))):
            self.botones_cielo[k] = self._boton(cielo, t, lambda k=k: self.elegir_cielo(k), pack=False)
            self.botones_cielo[k].grid(row=0, column=i + 1, sticky="ew", padx=2)
        cielo.columnconfigure((1, 2, 3), weight=1)

        botones = tk.Frame(lado, bg=estilo.BG)
        botones.pack(fill="x", pady=(8, 0))
        for i, (t, fn) in enumerate([("Duplicar", self.duplicar), ("Borrar", self.borrar),
                                     ("Nuevo nivel", self.nuevo_nivel), ("Abrir...", self.abrir),
                                     ("Guardar", self.guardar), ("Guardar como...", self.guardar_como)]):
            b = self._boton(botones, t, fn, pack=False)
            b.grid(row=i // 3, column=i % 3, sticky="ew", padx=2, pady=2)
        botones.columnconfigure((0, 1, 2), weight=1)

        self.var_libre = tk.BooleanVar()
        tk.Checkbutton(lado, text="Probar con camara libre (SELECT)", variable=self.var_libre, bg=estilo.BG, fg=estilo.FG,
                       selectcolor=estilo.BG_TARJETA, activebackground=estilo.BG, activeforeground=estilo.FG,
                       font=estilo.TEXTO_CHICO).pack(anchor="w", pady=(6, 0))
        self.btn_probar = self._boton(lado, "▶ Probar en el juego", self.probar, acento=True)
        self.btn_tam = self._boton(lado, "Medir el tamano del nivel (.INO)", self.medir_tamano)
        self.btn_ir = self._boton(lado, "Ir a la seleccionada (juego abierto)", self.ir_a_seleccionada)
        self.btn_cerrar = self._boton(lado, "Cerrar el juego", self.cerrar_juego)

        self.estado = tk.Label(lado, text="", bg=estilo.BG, fg=estilo.FG_MUTED, font=estilo.TEXTO_CHICO,
                               justify="left", anchor="nw", wraplength=340)
        self.estado.pack(fill="both", expand=True, pady=(8, 0), anchor="w")

        c = self.canvas
        c.bind("<ButtonPress-1>", self._clic)
        c.bind("<B1-Motion>", self._arrastrar)
        c.bind("<ButtonRelease-1>", self._soltar)
        for b in (2, 3):
            c.bind(f"<ButtonPress-{b}>", self._pan_ini)
            c.bind(f"<B{b}-Motion>", self._pan)
        c.bind("<MouseWheel>", self._rueda)
        c.bind("<Configure>", lambda _e: self.dibujar())
        c.bind("<Delete>", lambda _e: self.borrar())
        self.bind("<Control-s>", lambda _e: self.guardar())
        self.bind("<Control-d>", lambda _e: self.duplicar())
        for tecla, d in (("Left", (-GRID, 0)), ("Right", (GRID, 0)), ("Up", (0, -GRID)), ("Down", (0, GRID))):
            c.bind(f"<{tecla}>", lambda _e, d=d: self.mover(*d))
        c.bind("<Enter>", lambda _e: c.focus_set())

    def _boton(self, padre, texto, comando, acento=False, pack=True):
        b = tk.Button(padre, text=texto, command=comando, relief="flat", cursor="hand2", font=estilo.TEXTO,
                      bg=estilo.ACENTO if acento else estilo.BG_TARJETA,
                      fg=estilo.ACENTO_TEXTO if acento else estilo.FG,
                      activebackground=estilo.BG_TARJETA_HOVER, activeforeground=estilo.FG, pady=5)
        if pack:
            b.pack(fill="x", pady=(8 if acento else 4, 0))
        return b

    # ------------------------------------------------------------ coordenadas
    def a_pantalla(self, x, z):
        return self.ox + x * self.zoom, self.oy + z * self.zoom

    def a_mundo(self, px, py):
        return (px - self.ox) / self.zoom, (py - self.oy) / self.zoom

    @staticmethod
    def ajustar(v):
        return int(round(v / GRID)) * GRID

    # ------------------------------------------------------------ dibujo
    def dibujar(self):
        c = self.canvas
        c.delete("all")
        w, h = c.winfo_width(), c.winfo_height()
        # cuadricula de colision (1024) y ejes
        paso = 1024 * self.zoom
        if paso > 14:
            x0, z0 = self.a_mundo(0, 0)
            x1, z1 = self.a_mundo(w, h)
            for gx in range(int(x0 // 1024) * 1024, int(x1) + 1024, 1024):
                px = self.a_pantalla(gx, 0)[0]
                c.create_line(px, 0, px, h, fill="#2a2a38" if gx else "#44445a")
            for gz in range(int(z0 // 1024) * 1024, int(z1) + 1024, 1024):
                py = self.a_pantalla(0, gz)[1]
                c.create_line(0, py, w, py, fill="#2a2a38" if gz else "#44445a")
        # plataformas: las mas bajas primero
        orden = sorted(range(len(self.plats)), key=lambda i: -self.plats[i]["h"])
        for i in orden:
            p = self.plats[i]
            ax, az = self.a_pantalla(p["x0"], p["z0"])
            bx, bz = self.a_pantalla(p["x1"], p["z1"])
            inalcanzable = i not in self.alcanzables
            borde = "#ff5a5a" if inalcanzable else "#f2f2f2" if i == self.sel else "#000000"
            c.create_rectangle(ax, az, bx, bz, fill=hex_color(p["color"]), outline=borde,
                               width=3 if i == self.sel or inalcanzable else 1, stipple="" if i != self.sel else "")
            etiqueta = f"{p['nombre']}\n↑{-p['h']}" + (f" → ↑{-p['h2']} (eje {p.get('eje', 'x')})"
                                                          if p.get("h2") is not None else "")
            c.create_text((ax + bx) / 2, (az + bz) / 2, text=etiqueta, fill="#101010", font=("Segoe UI", 9, "bold"))
            if p.get("h2") is not None:                  # una flecha hacia donde sube la rampa
                sube_x = p.get("eje", "x") == "x"
                alto_, bajo_ = (p["h2"] < p["h"]), None
                if sube_x:
                    a_, b_ = ((ax, (az + bz) / 2), (bx, (az + bz) / 2)) if alto_ else ((bx, (az + bz) / 2), (ax, (az + bz) / 2))
                else:
                    a_, b_ = (((ax + bx) / 2, az), ((ax + bx) / 2, bz)) if alto_ else (((ax + bx) / 2, bz), ((ax + bx) / 2, az))
                c.create_line(*a_, *b_, fill="#101010", width=2, arrow="last")
        if self.sel is not None and self.sel < len(self.plats):
            p = self.plats[self.sel]
            for x, z in ((p["x0"], p["z0"]), (p["x1"], p["z0"]), (p["x0"], p["z1"]), (p["x1"], p["z1"])):
                px, pz = self.a_pantalla(x, z)
                c.create_rectangle(px - 5, pz - 5, px + 5, pz + 5, fill="#ffffff", outline="#000000")
        sx, sz = self.a_pantalla(*np_.SALIDA)
        c.create_line(sx - 9, sz, sx + 9, sz, fill="#ffe14d", width=2)
        c.create_line(sx, sz - 9, sx, sz + 9, fill="#ffe14d", width=2)
        c.create_text(sx + 12, sz - 10, text="salida", fill="#ffe14d", anchor="w", font=("Segoe UI", 8))
        if self.arrastre and self.arrastre[0] == "crear":
            _, (ax, az), (bx, bz) = self.arrastre
            pa, pb = self.a_pantalla(ax, az), self.a_pantalla(bx, bz)
            c.create_rectangle(*pa, *pb, outline="#ffffff", dash=(4, 3))
        self.dibujar3d()

    # ------------------------------------------------------------ vista 3D
    def dibujar3d(self):
        c = self.canvas3d
        c.delete("all")
        w, h = c.winfo_width(), c.winfo_height()
        if w < 50 or h < 50:
            return
        franjas = 24                      # el cielo del nivel de fondo: cenit arriba, horizonte al medio, nadir abajo
        mezcla = lambda a, b, t: [a[k] + (b[k] - a[k]) * t for k in range(3)]
        for i in range(franjas):
            t = (i + 0.5) / franjas
            col = mezcla(self.cielo["cenit"], self.cielo["horizonte"], t * 2) if t < 0.5 else \
                mezcla(self.cielo["horizonte"], self.cielo["nadir"], (t - 0.5) * 2)
            c.create_rectangle(0, h * i / franjas, w, h * (i + 1) / franjas + 1, fill=hex_color(col), outline="")
        c.create_text(8, 6, anchor="nw", fill="#ffffff", font=("Segoe UI", 8),
                      text="3D: arrastra para girar, rueda = zoom, doble clic = reiniciar, clic = seleccionar")
        if not self.plats:
            self.caras3d = []
            return
        inalc = set(range(len(self.plats))) - self.alcanzables
        self.caras3d, (escala, mu, mv) = proyectar_caras(
            self.plats, np_.profundidades(self.plats), self.yaw3d, self.pitch3d, w, h, self.zoom3d, self.sel, inalc)
        for cara in self.caras3d:
            flat = [v for q in cara["poly"] for v in q]
            c.create_polygon(*flat, fill=cara["relleno"], outline=cara["borde"], width=cara["grosor"])
        # la salida: un poste amarillo de 500 de alto sobre (128, 0, -896)
        cy_, sy_ = math.cos(self.yaw3d), math.sin(self.yaw3d)
        cp, sp = math.cos(self.pitch3d), math.sin(self.pitch3d)
        sx, sz = np_.SALIDA
        u, wd = sx * cy_ + sz * sy_, -sx * sy_ + sz * cy_
        puntos = [(w / 2 + (u - mu) * escala, h / 2 - ((arriba * cp + wd * sp) - mv) * escala) for arriba in (0, 500)]
        c.create_line(*puntos[0], *puntos[1], fill="#ffe14d", width=2)
        c.create_text(puntos[1][0] + 6, puntos[1][1], text="salida", fill="#ffe14d", anchor="w",
                      font=("Segoe UI", 8))

    def _ini3d(self, ev):
        self._arr3d = (ev.x, ev.y, False)

    def _giro3d(self, ev):
        if not self._arr3d:
            return
        x, y, giro = self._arr3d
        if giro or abs(ev.x - x) + abs(ev.y - y) > 3:
            self.yaw3d -= (ev.x - x) * 0.01
            self.pitch3d = max(0.15, min(1.45, self.pitch3d + (ev.y - y) * 0.01))
            self._arr3d = (ev.x, ev.y, True)
            self.dibujar3d()

    def _fin3d(self, ev):
        a, self._arr3d = self._arr3d, None
        if a and not a[2]:                       # clic sin arrastrar: elige la plataforma bajo el puntero
            for cara in reversed(self.caras3d):
                if punto_en_poligono(ev.x, ev.y, cara["poly"]):
                    self.seleccionar(cara["idx"])
                    self.dibujar()
                    return

    def _rueda3d(self, ev):
        self.zoom3d = max(0.3, min(5.0, self.zoom3d * (1.15 if ev.delta > 0 else 1 / 1.15)))
        self.dibujar3d()

    def _reiniciar3d(self, _ev):
        self.yaw3d, self.pitch3d, self.zoom3d = -math.pi / 4, 0.6, 1.0
        self.dibujar3d()

    # ------------------------------------------------------------ eleccion
    def hit_esquina(self, px, py):
        if self.sel is None or self.sel >= len(self.plats):
            return None
        p = self.plats[self.sel]
        for nx, nz in (("x0", "z0"), ("x1", "z0"), ("x0", "z1"), ("x1", "z1")):
            ex, ez = self.a_pantalla(p[nx], p[nz])
            if abs(ex - px) <= 8 and abs(ez - py) <= 8:
                return nx, nz
        return None

    def hit_plataforma(self, px, py, debajo=False):
        """La plataforma bajo el puntero: la mas alta (h mas negativo); con 'debajo' (Ctrl+clic), la siguiente mas
        baja que la seleccionada, para llegar a las que quedan tapadas por otra apilada encima."""
        x, z = self.a_mundo(px, py)
        dentro = sorted((i for i, p in enumerate(self.plats) if p["x0"] <= x <= p["x1"] and p["z0"] <= z <= p["z1"]),
                        key=lambda i: self.plats[i]["h"])
        if not dentro:
            return None
        if debajo and self.sel in dentro:
            return dentro[(dentro.index(self.sel) + 1) % len(dentro)]
        return dentro[0]

    # ------------------------------------------------------------ raton
    def _clic(self, ev):
        self.canvas.focus_set()
        if ev.state & 0x1:                       # Mayus + arrastrar: crea un bloque nuevo aunque haya otro debajo
            x, z = (self.ajustar(v) for v in self.a_mundo(ev.x, ev.y))
            self.arrastre = ("crear", (x, z), (x, z))
            return
        esq = self.hit_esquina(ev.x, ev.y)
        if esq:
            self.arrastre = ("tamano", esq)
            return
        i = self.hit_plataforma(ev.x, ev.y, debajo=bool(ev.state & 0x4))
        if i is not None:
            self.seleccionar(i)
            x, z = self.a_mundo(ev.x, ev.y)
            self.arrastre = ("mover", x, z, dict(self.plats[i]))
            return
        x, z = (self.ajustar(v) for v in self.a_mundo(ev.x, ev.y))
        self.arrastre = ("crear", (x, z), (x, z))

    def _arrastrar(self, ev):
        a = self.arrastre
        if not a:
            return
        x, z = self.a_mundo(ev.x, ev.y)
        if a[0] == "crear":
            self.arrastre = ("crear", a[1], (self.ajustar(x), self.ajustar(z)))
        elif a[0] == "mover":
            p, orig = self.plats[self.sel], a[3]
            dx, dz = self.ajustar(x - a[1]), self.ajustar(z - a[2])
            p["x0"], p["x1"] = orig["x0"] + dx, orig["x1"] + dx
            p["z0"], p["z1"] = orig["z0"] + dz, orig["z1"] + dz
            self.cambio()
        elif a[0] == "tamano":
            p = self.plats[self.sel]
            nx, nz = a[1]
            p[nx], p[nz] = self.ajustar(x), self.ajustar(z)
            self.cambio()
        self.dibujar()

    def _soltar(self, _ev):
        a, self.arrastre = self.arrastre, None
        if a and a[0] == "crear":
            (ax, az), (bx, bz) = a[1], a[2]
            if abs(bx - ax) >= 256 and abs(bz - az) >= 256:
                n = 1 + max([int("".join(ch for ch in p["nombre"] if ch.isdigit()) or 0) for p in self.plats] or [0])
                base = self.plats[self.sel]["h"] if self.sel is not None and self.sel < len(self.plats) else 0
                tipo = self.tipo.get()
                if tipo == "pared":      # alta y maciza (baja hasta el suelo de abajo): para salas y pasillos
                    self.plats.append(np_.nueva(f"pared{n}", ax, az, bx, bz, base - 600, (150, 140, 130),
                                                prof=600, tex_tapa=16, tex_lado=1, pared=True))
                elif tipo == "rampa":
                    self.plats.append(np_.nueva(f"rampa{n}", ax, az, bx, bz, base, (150, 140, 130), h2=base - 256,
                                                eje="x" if abs(bx - ax) >= abs(bz - az) else "z", prof=300,
                                                tex_tapa=97, tex_lado=16))
                else:
                    self.plats.append(np_.nueva(f"p{n}", ax, az, bx, bz, base, (128, 128, 128)))
                self.seleccionar(len(self.plats) - 1)
                self.cambio()
        elif a and a[0] == "tamano":
            p = self.plats[self.sel]
            p.update(np_.nueva(p["nombre"], p["x0"], p["z0"], p["x1"], p["z1"], p["h"], p["color"]))   # reordena x0 < x1
            self.cambio()
        self.dibujar()

    def _pan_ini(self, ev):
        self._pan_prev = (ev.x, ev.y)

    def _pan(self, ev):
        self.ox += ev.x - self._pan_prev[0]
        self.oy += ev.y - self._pan_prev[1]
        self._pan_prev = (ev.x, ev.y)
        self.dibujar()

    def _rueda(self, ev):
        antes = self.a_mundo(ev.x, ev.y)
        self.zoom = max(0.02, min(0.6, self.zoom * (1.15 if ev.delta > 0 else 1 / 1.15)))
        self.ox = ev.x - antes[0] * self.zoom
        self.oy = ev.y - antes[1] * self.zoom
        self.dibujar()

    # ------------------------------------------------------------ edicion
    def seleccionar(self, i):
        self.sel = i
        self._llenar_campos()
        self._llenar_lista()

    def _lista_elegida(self, _ev):
        s = self.lista.curselection()
        if s:
            self.sel = s[0]
            self._llenar_campos()
            self.dibujar()

    def _llenar_lista(self):
        self.lista.delete(0, "end")
        for i, p in enumerate(self.plats):
            self.lista.insert("end", f"{p['nombre'][:10]:10s} ↑{-p['h']:<6d} {p['x1'] - p['x0']}x{p['z1'] - p['z0']}"
                                     + ("  rampa" if p.get("h2") is not None else ""))
        if self.sel is not None and self.sel < len(self.plats):
            self.lista.selection_set(self.sel)

    def _llenar_campos(self):
        for k, e in self.campos.items():
            e.delete(0, "end")
        for b, t in ((self.boton_tapa, "Tapa: ..."), (self.boton_lado, "Lado: ...")):
            b.config(text=t)
        self.var_techo.set(False)
        self.var_pared.set(False)
        if self.sel is None or self.sel >= len(self.plats):
            return
        p = self.plats[self.sel]
        valores = dict(p, alto=-p["h"], grosor=p.get("prof", ""), alto2="" if p.get("h2") is None else -p["h2"],
                       eje=p.get("eje", "x") if p.get("h2") is not None else "", paso=p.get("paso", ""),
                       paso_lado=p.get("paso_lado", ""))
        self.var_techo.set(bool(p.get("techo")))
        self.var_pared.set(bool(p.get("pared")))
        for k, e in self.campos.items():
            e.insert(0, str(valores[k]))
        self.boton_color.config(text="Color", bg=hex_color(p["color"]), fg="#000000" if sum(p["color"]) > 300 else "#ffffff")
        nombres = dict(np_.PALETA)
        for b, clave, rotulo in ((self.boton_tapa, "tex_tapa", "Tapa"), (self.boton_lado, "tex_lado", "Lado")):
            k = p.get(clave, np_.TEX_DEFECTO)
            b.config(text=f"{rotulo}: #{k} {nombres.get(k, '')}"[:22])

    def aplicar_campos(self):
        if self.sel is None or self.sel >= len(self.plats):
            return
        p = self.plats[self.sel]
        try:
            nuevo = dict(p)
            nuevo.update(np_.nueva(self.campos["nombre"].get().strip() or p["nombre"],
                                   int(self.campos["x0"].get()), int(self.campos["z0"].get()),
                                   int(self.campos["x1"].get()), int(self.campos["z1"].get()),
                                   -int(self.campos["alto"].get()), p["color"]))
            for clave, campo, signo in (("prof", "grosor", 1), ("h2", "alto2", -1), ("paso", "paso", 1),
                                        ("paso_lado", "paso_lado", 1)):
                txt = self.campos[campo].get().strip()
                if txt:
                    nuevo[clave] = signo * int(txt)
                else:
                    nuevo.pop(clave, None)
            eje = self.campos["eje"].get().strip().lower()
            if nuevo.get("h2") is None or eje not in ("x", "z"):
                nuevo.pop("eje", None)
            if nuevo.get("h2") is not None:
                nuevo["eje"] = eje if eje in ("x", "z") else "x"
        except ValueError:
            self._llenar_campos()
            return
        if nuevo != p:
            p.clear()
            p.update(nuevo)
            self.cambio()
            self._llenar_lista()
            self._llenar_campos()
            self.dibujar()

    def aplicar_flags(self):
        if self.sel is None or self.sel >= len(self.plats):
            return
        p = self.plats[self.sel]
        for clave, var in (("techo", self.var_techo), ("pared", self.var_pared)):
            if var.get():
                p[clave] = True
            else:
                p.pop(clave, None)
        self.cambio()
        self.dibujar()

    def medir_tamano(self):
        """El .INO del disco tiene un tamano fijo; dice cuanto de el usa este nivel (tarda un par de segundos)."""
        self.estado.config(text="Midiendo...", fg=estilo.FG_MUTED)
        self.update_idletasks()
        errores, _ = np_.validar(self.plats)
        if errores:
            self.estado.config(text="Hay errores; corrigelos antes de medir.", fg=estilo.MALO)
            return
        usado, maximo = np_.tamano_ino(self.plats, self.cielo)
        pct = 100 * usado / maximo
        self.estado.config(text=f"Tamano del nivel: {usado:,} de {maximo:,} bytes ({pct:.0f}%)."
                                + ("" if usado <= maximo else "\nNO CABE: usa cuadros mas grandes (paso_lado 512), "
                                                           "menos bloques o quita techos."),
                           fg=estilo.BUENO if usado <= maximo else estilo.MALO)

    def elegir_textura(self, clave):
        """Galeria con las texturas de arquitectura (PALETA): un clic en una la pone en la tapa o en los lados."""
        if self.sel is None or self.sel >= len(self.plats):
            return
        p = self.plats[self.sel]
        ventana = tk.Toplevel(self)
        ventana.title("Textura de la " + ("tapa" if clave == "tex_tapa" else "pared") + f" de {p['nombre']}")
        ventana.configure(bg=estilo.BG)
        ventana.transient(self)
        self._miniaturas = []
        columnas = 7
        for n, (k, nombre) in enumerate(np_.PALETA):
            im = np_.imagen_textura(k)
            marco = tk.Frame(ventana, bg=estilo.BG_TARJETA, padx=3, pady=3)
            marco.grid(row=n // columnas, column=n % columnas, padx=3, pady=3)
            if im is not None:
                escala = min(80 / im.width, 80 / im.height)
                foto = ImageTk.PhotoImage(im.resize((max(1, int(im.width * escala)), max(1, int(im.height * escala)))))
                self._miniaturas.append(foto)
                boton = tk.Button(marco, image=foto, relief="flat", bg=estilo.BG_TARJETA, cursor="hand2",
                                  command=lambda k=k: (p.__setitem__(clave, k), self.cambio(), self._llenar_campos(),
                                                       self.dibujar(), ventana.destroy()))
                boton.pack()
            tk.Label(marco, text=f"#{k} {nombre}", bg=estilo.BG_TARJETA, fg=estilo.FG, font=("Segoe UI", 8)).pack()

    def elegir_cielo(self, cual):
        rgb, _ = colorchooser.askcolor(color=hex_color(self.cielo[cual]), title=f"Cielo: {cual}")
        if rgb:
            self.cielo[cual] = [int(v) for v in rgb]
            self._color_botones_cielo()
            self.sucio = True
            self.cambio()
            self.dibujar3d()

    def _color_botones_cielo(self):
        for k, b in self.botones_cielo.items():
            b.config(bg=hex_color(self.cielo[k]), fg="#000000" if sum(self.cielo[k]) > 330 else "#ffffff")

    def elegir_color(self):
        if self.sel is None:
            return
        p = self.plats[self.sel]
        rgb, _ = colorchooser.askcolor(color=hex_color(p["color"]), title="Color del bloque (128 = el de la textura)")
        if rgb:
            p["color"] = [int(v) for v in rgb]
            self._llenar_campos()
            self.cambio()
            self.dibujar()

    def mover(self, dx, dz):
        if self.sel is not None and self.sel < len(self.plats):
            p = self.plats[self.sel]
            p["x0"] += dx
            p["x1"] += dx
            p["z0"] += dz
            p["z1"] += dz
            self.cambio()
            self._llenar_campos()
            self.dibujar()

    def duplicar(self):
        if self.sel is None or self.sel >= len(self.plats):
            return
        p = dict(self.plats[self.sel])
        p["color"] = list(p["color"])
        p["nombre"] += "b"
        w = p["x1"] - p["x0"]
        p["x0"] += w + 256
        p["x1"] += w + 256
        self.plats.append(p)
        self.seleccionar(len(self.plats) - 1)
        self.cambio()
        self.dibujar()

    def borrar(self):
        if self.sel is None or self.sel >= len(self.plats):
            return
        del self.plats[self.sel]
        self.sel = None
        self.cambio()
        self._llenar_campos()
        self._llenar_lista()
        self.dibujar()

    def cambio(self, sucio=True):
        """Algo cambio: se vuelve a validar (barato) y se marca como sin guardar."""
        if sucio:
            self.sucio = True
        errores, avisos = np_.validar(self.plats)
        self.errores = errores
        self.alcanzables = set(range(len(self.plats)))
        if not errores:
            nombres_mal = {a.split(":")[0] for a in avisos}
            self.alcanzables = {i for i, p in enumerate(self.plats) if p["nombre"] not in nombres_mal}
        texto = f"{len(self.plats)} bloques" + ("  (sin guardar)" if self.sucio else "")
        if errores:
            texto += "\n\nERRORES (no se puede probar):\n- " + "\n- ".join(errores)
        if avisos:
            texto += "\n\nAvisos:\n- " + "\n- ".join(avisos)
        if not errores and not avisos:
            texto += "\n\nTodo en orden."
        self.estado.config(text=texto, fg=estilo.MALO if errores else estilo.FG_MUTED)
        self.title(f"Editor de niveles - {os.path.basename(self.ruta) if self.ruta else 'sin nombre'}"
                   f"{' *' if self.sucio else ''}")

    # ------------------------------------------------------------ archivos
    def cargar_archivo(self, ruta):
        self.plats, self.cielo = np_.cargar_nivel(ruta)
        self.ruta, self.sel, self.sucio = ruta, None, False
        self._color_botones_cielo()
        self.cambio(False)
        self._llenar_campos()
        self._llenar_lista()
        self.dibujar()

    def confirmar_perdida(self):
        if not self.sucio:
            return True
        r = messagebox.askyesnocancel("Editor", "Hay cambios sin guardar. ¿Guardarlos?")
        if r is None:
            return False
        return self.guardar() if r else True

    def nuevo_nivel(self):
        if not self.confirmar_perdida():
            return
        self.plats = [np_.nueva("salida", -512, -1536, 1024, 0, 0, (128, 128, 128))]
        self.cielo = dict(np_.CIELO_DEFECTO)
        self._color_botones_cielo()
        self.ruta, self.sel = None, None
        self.cambio()
        self._llenar_campos()
        self._llenar_lista()
        self.dibujar()

    def abrir(self):
        if not self.confirmar_perdida():
            return
        ruta = filedialog.askopenfilename(initialdir=np_.NIVELES, filetypes=[("Niveles", "*.json")])
        if ruta:
            self.cargar_archivo(ruta)

    def guardar(self):
        if not self.ruta:
            return self.guardar_como()
        np_.guardar(self.plats, self.ruta, self.cielo)
        self.sucio = False
        self.cambio(False)
        return True

    def guardar_como(self):
        os.makedirs(np_.NIVELES, exist_ok=True)
        ruta = filedialog.asksaveasfilename(initialdir=np_.NIVELES, defaultextension=".json",
                                            filetypes=[("Niveles", "*.json")])
        if not ruta:
            return False
        self.ruta = ruta
        return self.guardar()

    # ------------------------------------------------------------ juego
    def _vaciar_cola(self):
        """Tk solo se toca desde el hilo principal: los hilos del juego dejan aqui lo que quieren mostrar."""
        try:
            while True:
                self.cola.get_nowait()()
        except queue.Empty:
            pass
        self.after(100, self._vaciar_cola)

    def _msg(self, texto, malo=False):
        self.cola.put(lambda: self.estado.config(text=texto, fg=estilo.MALO if malo else estilo.BUENO))

    def _probar_libre(self):
        self.cola.put(lambda: self.btn_probar.config(state="normal"))

    def probar(self):
        if self.ocupado:
            return
        errores, _ = np_.validar(self.plats)
        if errores:
            messagebox.showerror("Editor", "No se puede probar:\n- " + "\n- ".join(errores))
            return
        plats = [dict(p, color=list(p["color"])) for p in self.plats]
        self.ocupado = True
        self.btn_probar.config(state="disabled")
        self._msg("Armando el disco...")
        threading.Thread(target=self._jugar, args=(plats, dict(self.cielo), self.var_libre.get()), daemon=True).start()

    def _jugar(self, plats, cielo, libre=False):
        from emu import Emu
        from explorar import recorrer
        try:
            self._cerrar_emu()
            cue = np_.armar_disco(plats, "editor", cielo, camara_libre=libre)
            self._msg("Abriendo el juego; unos 40 segundos hasta poder jugar...")
            e = Emu(iso=cue, log="editor.log", extra=("-fastboot",), puerto=PUERTO, ui=True)
            self.emu = e
            recorrer(e, "editor_arranque", PASOS_HASTA_EL_HUB)
            e.eval("PCSX.settings.spu.Mute = false; return 'ok'")     # Emu lo deja mudo para las rondas automaticas
            self._msg("Listo, a jugar. Cierra la ventana del juego (o el boton) para volver a probar.")
            self._probar_libre()
            self.ocupado = False
            e.p.wait()
        except Exception as ex:           # noqa: BLE001 - se muestra al usuario
            self._msg(f"No se pudo probar: {ex}", malo=True)
        finally:
            self.ocupado = False
            self._probar_libre()
            self._cerrar_emu()

    def _cerrar_emu(self):
        e, self.emu = self.emu, None
        if e is not None:
            try:
                e.cerrar()
            except Exception:            # noqa: BLE001
                pass

    def cerrar_juego(self):
        threading.Thread(target=self._cerrar_emu, daemon=True).start()

    def ir_a_seleccionada(self):
        if self.emu is None or self.sel is None or self.sel >= len(self.plats):
            self._msg("Hace falta el juego abierto (Probar) y una plataforma seleccionada.", malo=True)
            return
        e, i = self.emu, self.sel
        todas = [dict(q) for q in self.plats]
        threading.Thread(target=lambda: np_.teletransportar(e, todas[i], todas), daemon=True).start()

    def salir(self):
        if not self.confirmar_perdida():
            return
        self._cerrar_emu()
        self.destroy()


if __name__ == "__main__":
    Editor(sys.argv[1] if len(sys.argv) > 1 else None).mainloop()
