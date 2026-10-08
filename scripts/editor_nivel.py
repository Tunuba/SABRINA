"""Editor de niveles de plataformas para Sabrina: dibujas rectangulos (plataformas con las que se puede chocar) en
una vista desde arriba, les pones altura y color, y con "Probar" arma el disco, abre el juego y deja a Sabrina en
la salida. Los niveles se guardan en niveles\\*.json. La logica (validar, armar el disco) vive en nivel_plataformas.py.

Uso: python editor_nivel.py [nivel.json]        (o doble clic en EDITOR_NIVEL.bat)

Ratón (vista desde arriba: derecha = +X, abajo = +Z; en el juego UP avanza hacia +X +Z, o sea abajo a la derecha):
  arrastrar en vacio       crea una plataforma (se ajusta a la cuadricula de 128)
  clic / arrastrar         selecciona / mueve la plataforma
  arrastrar una esquina    cambia su tamano
  rueda                    zoom
  boton derecho o central  desplaza la vista
Teclado: Supr borra, Ctrl+D duplica, Ctrl+S guarda, flechas mueven la seleccionada 128.
La cruz amarilla es la salida: ahi aparece Sabrina (y reaparece si cae), asi que tiene que haber una plataforma
a altura 0 debajo. Las plataformas rojas no son alcanzables saltando (hueco > 256 o subida > 250).
Probar cierra el juego anterior; "Ir a la seleccionada" teletransporta a Sabrina en el juego abierto.
"""
import os
import sys
import threading
import tkinter as tk
from tkinter import colorchooser, filedialog, messagebox, simpledialog

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "panel_color"))
import estilo  # noqa: E402
import nivel_plataformas as np_  # noqa: E402

GRID = 128
PASOS_HASTA_EL_HUB = "w2160 CROSS w300 START w60 CROSS w240 w1300"
PUERTO = 8094


def hex_color(c):
    return "#%02x%02x%02x" % tuple(min(255, int(v)) for v in c)


class Editor(tk.Tk):
    def __init__(self, ruta=None):
        super().__init__()
        estilo.ventana_base(self, "Editor de niveles - Sabrina")
        self.geometry("1280x780")
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
        self._armar_ui()
        self.protocol("WM_DELETE_WINDOW", self.salir)
        self.cargar_archivo(ruta or np_.NIVEL_POR_DEFECTO)

    # ------------------------------------------------------------ interfaz
    def _armar_ui(self):
        self.columnconfigure(0, weight=1)
        self.rowconfigure(0, weight=1)
        self.canvas = tk.Canvas(self, bg="#0c0c10", highlightthickness=0, cursor="crosshair")
        self.canvas.grid(row=0, column=0, sticky="nsew")
        lado = tk.Frame(self, bg=estilo.BG, width=330)
        lado.grid(row=0, column=1, sticky="ns", padx=8, pady=8)
        lado.grid_propagate(False)

        tk.Label(lado, text="Plataformas", font=estilo.ENCABEZADO, bg=estilo.BG, fg=estilo.FG).pack(anchor="w")
        self.lista = tk.Listbox(lado, height=9, bg=estilo.BG_TARJETA, fg=estilo.FG, font=estilo.TEXTO_CHICO,
                                selectbackground=estilo.ACENTO, selectforeground=estilo.ACENTO_TEXTO,
                                exportselection=False, highlightthickness=0, borderwidth=0)
        self.lista.pack(fill="x", pady=(4, 8))
        self.lista.bind("<<ListboxSelect>>", self._lista_elegida)

        fila = tk.Frame(lado, bg=estilo.BG)
        fila.pack(fill="x")
        self.campos = {}
        for i, (clave, texto) in enumerate([("nombre", "Nombre"), ("x0", "X desde"), ("z0", "Z desde"),
                                            ("x1", "X hasta"), ("z1", "Z hasta"), ("alto", "Altura (+ = arriba)")]):
            tk.Label(fila, text=texto, bg=estilo.BG, fg=estilo.FG_MUTED, font=estilo.TEXTO_CHICO).grid(
                row=i, column=0, sticky="w", pady=2)
            e = tk.Entry(fila, width=14, bg=estilo.BG_TARJETA, fg=estilo.FG, insertbackground=estilo.FG,
                         relief="flat", font=estilo.TEXTO)
            e.grid(row=i, column=1, sticky="e", padx=(8, 0), pady=2)
            e.bind("<Return>", lambda _e: self.aplicar_campos())
            e.bind("<FocusOut>", lambda _e: self.aplicar_campos())
            self.campos[clave] = e
        fila.columnconfigure(1, weight=1)
        self.boton_color = self._boton(lado, "Color...", self.elegir_color)

        botones = tk.Frame(lado, bg=estilo.BG)
        botones.pack(fill="x", pady=(10, 0))
        for i, (t, f) in enumerate([("Duplicar", self.duplicar), ("Borrar", self.borrar),
                                    ("Nuevo nivel", self.nuevo_nivel), ("Abrir...", self.abrir),
                                    ("Guardar", self.guardar), ("Guardar como...", self.guardar_como)]):
            b = self._boton(botones, t, f, pack=False)
            b.grid(row=i // 2, column=i % 2, sticky="ew", padx=2, pady=2)
        botones.columnconfigure((0, 1), weight=1)

        self.btn_probar = self._boton(lado, "▶ Probar en el juego", self.probar, acento=True)
        self.btn_ir = self._boton(lado, "Ir a la seleccionada (juego abierto)", self.ir_a_seleccionada)
        self.btn_cerrar = self._boton(lado, "Cerrar el juego", self.cerrar_juego)

        self.estado = tk.Label(lado, text="", bg=estilo.BG, fg=estilo.FG_MUTED, font=estilo.TEXTO_CHICO,
                               justify="left", anchor="nw", wraplength=310)
        self.estado.pack(fill="both", expand=True, pady=(10, 0), anchor="w")

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
            c.create_text((ax + bx) / 2, (az + bz) / 2, text=f"{p['nombre']}\n↑{-p['h']}", fill="#101010",
                          font=("Segoe UI", 9, "bold"))
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

    def hit_plataforma(self, px, py):
        x, z = self.a_mundo(px, py)
        dentro = [i for i, p in enumerate(self.plats) if p["x0"] <= x <= p["x1"] and p["z0"] <= z <= p["z1"]]
        return min(dentro, key=lambda i: self.plats[i]["h"]) if dentro else None   # la mas alta (h mas negativo)

    # ------------------------------------------------------------ raton
    def _clic(self, ev):
        self.canvas.focus_set()
        esq = self.hit_esquina(ev.x, ev.y)
        if esq:
            self.arrastre = ("tamano", esq)
            return
        i = self.hit_plataforma(ev.x, ev.y)
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
                n = 1 + max([int(p["nombre"][1:]) for p in self.plats
                             if p["nombre"][:1] == "p" and p["nombre"][1:].isdigit()] or [0])
                alt = self.plats[self.sel]["h"] if self.sel is not None and self.sel < len(self.plats) else 0
                self.plats.append(np_.nueva(f"p{n}", ax, az, bx, bz, alt, (128, 128, 128)))
                self.seleccionar(len(self.plats) - 1)
                self.cambio()
        elif a and a[0] == "tamano":
            p = self.plats[self.sel]
            p.update(np_.nueva(p["nombre"], p["x0"], p["z0"], p["x1"], p["z1"], p["h"], p["color"]))
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
            self.lista.insert("end", f"{p['nombre']:8s} ↑{-p['h']:<6d} {p['x1'] - p['x0']}x{p['z1'] - p['z0']}")
        if self.sel is not None and self.sel < len(self.plats):
            self.lista.selection_set(self.sel)

    def _llenar_campos(self):
        for k, e in self.campos.items():
            e.delete(0, "end")
        if self.sel is None or self.sel >= len(self.plats):
            return
        p = self.plats[self.sel]
        valores = dict(p, alto=-p["h"])
        for k, e in self.campos.items():
            e.insert(0, str(valores[k]))
        self.boton_color.config(bg=hex_color(p["color"]), fg="#000000" if sum(p["color"]) > 300 else "#ffffff")

    def aplicar_campos(self):
        if self.sel is None or self.sel >= len(self.plats):
            return
        p = self.plats[self.sel]
        try:
            nuevo = np_.nueva(self.campos["nombre"].get().strip() or p["nombre"],
                              int(self.campos["x0"].get()), int(self.campos["z0"].get()),
                              int(self.campos["x1"].get()), int(self.campos["z1"].get()),
                              -int(self.campos["alto"].get()), p["color"])
        except ValueError:
            self._llenar_campos()
            return
        if nuevo != p:
            p.update(nuevo)
            self.cambio()
            self._llenar_lista()
            self.dibujar()

    def elegir_color(self):
        if self.sel is None:
            return
        p = self.plats[self.sel]
        rgb, _ = colorchooser.askcolor(color=hex_color(p["color"]), title="Color de la plataforma")
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
        texto = f"{len(self.plats)} plataformas" + ("  (sin guardar)" if self.sucio else "")
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
        self.plats = np_.cargar(ruta)
        self.ruta, self.sel, self.sucio = ruta, None, False
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
        self.plats = [np_.nueva("salida", -512, -1536, 1024, 0, 0, (70, 150, 70))]
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
        np_.guardar(self.plats, self.ruta)
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
    def _msg(self, texto, malo=False):
        self.after(0, lambda: self.estado.config(text=texto, fg=estilo.MALO if malo else estilo.BUENO))

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
        threading.Thread(target=self._jugar, args=(plats,), daemon=True).start()

    def _jugar(self, plats):
        from emu import Emu
        from explorar import recorrer
        try:
            self._cerrar_emu()
            cue = np_.armar_disco(plats, "editor")
            self._msg("Abriendo el juego; unos 40 segundos hasta poder jugar...")
            e = Emu(iso=cue, log="editor.log", extra=("-fastboot",), puerto=PUERTO, ui=True)
            self.emu = e
            recorrer(e, "editor_arranque", PASOS_HASTA_EL_HUB)
            e.eval("PCSX.settings.spu.Mute = false; return 'ok'")     # Emu lo deja mudo para las rondas automaticas
            self._msg("Listo, a jugar. Cierra la ventana del juego (o el boton) para volver a probar.")
            self.after(0, self.btn_probar.config, {"state": "normal"})
            self.ocupado = False
            e.p.wait()
        except Exception as ex:           # noqa: BLE001 - se muestra al usuario
            self._msg(f"No se pudo probar: {ex}", malo=True)
        finally:
            self.ocupado = False
            self.after(0, self.btn_probar.config, {"state": "normal"})
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
        e, p = self.emu, dict(self.plats[self.sel])
        threading.Thread(target=lambda: np_.teletransportar(e, p), daemon=True).start()

    def salir(self):
        if not self.confirmar_perdida():
            return
        self._cerrar_emu()
        self.destroy()


if __name__ == "__main__":
    Editor(sys.argv[1] if len(sys.argv) > 1 else None).mainloop()
