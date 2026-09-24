"""Editor simple de los modelos 3D del nivel: elegis cualquiera de la lista del .INO -no solo
Sabrina, tambien el ropero, el escenario, FashionDiva, lo que sea que tenga vertices-, le aplicas
un factor de escala por eje desde su propio centro, y lo ves primero en una vista previa
renderizada en Python (ino_obj.py, sin tocar el juego) y despues, si te convence, de verdad en la
VRAM. La tecnica para encontrarlo en RAM: buscar los 12 bytes crudos de cada vertice tal cual
estan en el .INO -la misma que ya funciono con el ropero y con la cadera de Sabrina-.

Ojo, un limite comprobado: la vista previa escala en el espacio ya transformado (lo que devuelve
aplanar()), no vertice por vertice local como la escritura real a la RAM -para un modelo de un
solo nodo (el ropero, el escenario) da lo mismo; para un modelo con huesos como Sabrina puede no
coincidir exacto, es una aproximacion para mirar antes de aplicar, no una simulacion perfecta.

Piso bajo Sabrina (colision real): al principio pareci que la colision NO seguia a los vertices en
vivo -se probo levantando un pedazo cualquiera del piso y Sabrina se quedaba flotando a la altura
vieja-. Resulto ser que se estaba tocando el pedazo equivocado. La colision de a donde puede
caminar usa una cuadricula de 64x64 celdas (seccion 1 del .INO, formula de fila/columna en
notas/FORMATOS.md): cada celda tiene una lista de triangulos del modelo del mundo. Encontrando esa
lista para la celda donde esta parada Sabrina AHORA, y los vertices de esos triangulos exactos (no
cualquiera cercano), levantarlos si mueve donde puede pisar -probado subiendola de verdad, se
paraba mas arriba y no se caia-. Con un salto muy grande (probado con 500 unidades locales) el
juego lo tomo como una caida larga y la mato (GAME OVER); con algo mas chico (80) subio bien y
sin problema. Por eso el campo de "elevar" tiene un valor chico por defecto.

El nivel ya no esta fijo al HUB: se lee en vivo el byte que dice que nivel esta cargado
(0x8007CA00, el mismo que usa ir_a_nivel.py) y se busca su .INO correspondiente. Si cambias de
nivel en el juego, apretar "Buscar en la RAM" (o cambiar de modelo) vuelve a leer todo para el
nivel nuevo.

Uso: entra desde el menu de panel_color.py, no se corre solo.
"""
import os
import struct
import sys
import tkinter as tk
from tkinter import messagebox

import numpy as np
from PIL import ImageTk

import estilo

RAIZ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(RAIZ, "scripts"))
import ino  # noqa: E402
from ino_obj import aplanar, dibujar  # noqa: E402
from panel_memoria import P_SABRINA, leer  # noqa: E402

DIR_NIVEL = 0x8007CA00  # que nivel esta cargado (0 menu, 1-3 Stone, 4-6 Egypt, 7-9 Japan,
                        # 10-12 West, 13 HUB, 14 Chaos) -mismo byte que usa ir_a_nivel.py


def nivel_actual(e):
    """Codigo de 3 letras del .INO (H1W, S1W...) del nivel que esta cargado ahora mismo."""
    i = leer(e, DIR_NIVEL, "u8")
    if i < 0 or i >= len(ino.NIVELES):
        return "H1W"
    return ino.NIVELES[i]


def _todos(nodos, campo):
    out = []
    for n in nodos:
        out.extend(n[campo])
        out.extend(_todos(n["hijos"], campo))
    return out


def celda_de(x, z, g):
    fila = (~((z >> 16) + 0x80) & 0xFF) >> 2
    columna = ((x >> 16) + 0x80) >> 2
    return fila, columna, fila * g["ancho"] + columna


def modelo_del_mundo(s, nivel):
    """(nombre, nodos) del modelo de escenario/piso del nivel -el que usa la colision-, el que
    termina en <nivel>.bud (comprobado con H1W en el HUB; se asume el mismo patron en los demas)."""
    return next(((n, nd) for n, nd in s["modelos"] if n.upper().endswith(nivel.upper() + ".BUD")), (None, None))


def vertices_bajo(s, g, x, z, nivel):
    """(indices de vertice del modelo del mundo, tris_mundo, verts_mundo) para la celda de (x, z):
    todos los vertices de todos los triangulos que esa celda de colision realmente usa. Se probo
    tratando de descartar los triangulos "grandes" como si fueran fondo (con un umbral de tamano)
    y salio mal -algunos triangulos grandes resultaron ser piso real, no fondo-, asi que van todos,
    sin filtrar por tamano."""
    nom_mundo, nodos_mundo = modelo_del_mundo(s, nivel)
    if nodos_mundo is None:
        return set(), [], []
    tris_mundo = _todos(nodos_mundo, "tris")
    verts_mundo = _todos(nodos_mundo, "verts")
    _fila, _col, orden = celda_de(x, z, g)
    cantidad, _pad, inicio = struct.unpack_from("<hHi", g["listas"], orden * 8)
    if cantidad <= 0:
        return set(), tris_mundo, verts_mundo
    idx_tris = struct.unpack_from(f"<{cantidad}h", g["indices"], inicio * 2)
    idx_verts = set()
    for it in idx_tris:
        idx_verts.update(tris_mundo[it][:3])
    return idx_verts, tris_mundo, verts_mundo


def listar_modelos(nivel):
    """[(nombre corto, nodos)] de todos los modelos del nivel que tengan algun vertice."""
    s = ino.leer_ino(nivel)
    vistos = set()
    salida = []
    for nombre, nodos in s["modelos"]:
        base = os.path.splitext(os.path.basename(nombre.replace("\\", "/")))[0]
        if not nodos or base in vistos:
            continue
        vistos.add(base)
        salida.append((base, nodos))
    return salida


def vertices_planos(nodos):
    """[(bytes crudos de 12, (x,y,z) local)] de todo el arbol, mismo orden que recorre aplanar()."""
    out = []

    def recorrer(ns):
        for n in ns:
            for v in n["verts"]:
                out.append((v, struct.unpack_from("<3h", v, 0)))
            recorrer(n["hijos"])

    recorrer(nodos)
    return out


class FrameModelos(tk.Frame):
    def __init__(self, padre, e, volver):
        super().__init__(padre, bg=estilo.BG)
        self.e = e
        estilo.encabezado(
            self, "Modelos 3D",
            "Elegi cualquier modelo del nivel que este cargado ahora (se detecta solo, no hace "
            "falta que sea el HUB) y aplicale una escala por eje.",
            volver=volver)

        self.nivel = nivel_actual(e)
        self.modelos = listar_modelos(self.nivel)
        self.nodos_actual = None
        self.direcciones = None  # [(addr o None, (x,y,z) original local)]
        self._imagen_actual = None  # referencia viva, si no Tkinter la tira

        estilo.separador(self, "Nivel")
        fila_nivel = tk.Frame(self, bg=estilo.BG)
        fila_nivel.pack(fill="x", padx=14)
        self.nivel_lbl = tk.Label(fila_nivel, text=f"nivel detectado: {self.nivel}", fg=estilo.FG,
                                   bg=estilo.BG, font=estilo.TEXTO)
        self.nivel_lbl.pack(side="left")
        estilo.boton(fila_nivel, "Detectar nivel de nuevo", self._detectar_nivel).pack(side="left", padx=(6, 0))

        estilo.separador(self, "Modelo")
        self.fila_modelo = tk.Frame(self, bg=estilo.BG)
        self.fila_modelo.pack(fill="x", padx=14)
        self.menu_modelo = None
        self.modelo_var = tk.StringVar()
        self._armar_menu_modelo()
        estilo.boton(self.fila_modelo, "Buscar en la RAM", self._cambiar_modelo).pack(side="left", padx=(6, 0))
        self.info_lbl = tk.Label(self.fila_modelo, text="", fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO)
        self.info_lbl.pack(side="left", padx=(10, 0))

        estilo.separador(self, "Escala (desde el centro del modelo)")
        escala = tk.Frame(self, bg=estilo.BG)
        escala.pack(fill="x", padx=14)
        self.escala_x = self._campo_escala(escala, "x")
        self.escala_y = self._campo_escala(escala, "y")
        self.escala_z = self._campo_escala(escala, "z")
        estilo.boton(escala, "Vista previa", self._previsualizar).pack(side="left", padx=(10, 4))
        estilo.boton(escala, "Aplicar en el juego", self._aplicar).pack(side="left")
        estilo.boton(escala, "Restaurar original", self._restaurar).pack(side="left", padx=(4, 0))

        estilo.separador(self, "Vista previa (renderizada en Python, no toca el juego)")
        self.preview_lbl = tk.Label(self, bg=estilo.BG_TARJETA)
        self.preview_lbl.pack(padx=14, pady=(0, 12))

        estilo.separador(self, "Piso bajo Sabrina (colision real)")
        tk.Label(self, text="Levanta o baja el piso de la celda donde esta parada AHORA -los "
                             "vertices que la colision realmente consulta, comprobado subiendola de "
                             "verdad-. Un salto grande la mata (lo toma como una caida); mejor de a poco.",
                  fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO, anchor="w",
                  wraplength=760, justify="left").pack(anchor="w", padx=14, pady=(0, 4))
        piso = tk.Frame(self, bg=estilo.BG)
        piso.pack(fill="x", padx=14, pady=(0, 12))
        tk.Label(piso, text="elevar:", fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO).pack(side="left")
        self.elevar_entry = tk.Entry(piso, width=6, bg=estilo.BG_TARJETA, fg=estilo.FG,
                                      insertbackground=estilo.FG, relief="flat")
        self.elevar_entry.insert(0, "80")
        self.elevar_entry.pack(side="left", padx=(2, 8))
        estilo.boton(piso, "Subir piso bajo Sabrina", lambda: self._tocar_piso(1)).pack(side="left")
        estilo.boton(piso, "Bajar piso bajo Sabrina", lambda: self._tocar_piso(-1)).pack(side="left", padx=(4, 0))
        estilo.boton(piso, "Restaurar piso original", self._restaurar_piso).pack(side="left", padx=(4, 0))
        self.piso_lbl = tk.Label(piso, text="", fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO)
        self.piso_lbl.pack(side="left", padx=(10, 0))
        self._piso_original = {}  # {addr: (x,y,z) original}, para poder restaurar

        self._cambiar_modelo()

    def _campo_escala(self, padre, letra):
        tk.Label(padre, text=f"{letra}:", fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO).pack(side="left")
        entrada = tk.Entry(padre, width=5, bg=estilo.BG_TARJETA, fg=estilo.FG, insertbackground=estilo.FG,
                            relief="flat")
        entrada.insert(0, "1.0")
        entrada.pack(side="left", padx=(2, 8))
        entrada.bind("<Return>", lambda ev: self._previsualizar())
        return entrada

    def _factores(self):
        try:
            return (float(self.escala_x.get()), float(self.escala_y.get()), float(self.escala_z.get()))
        except ValueError:
            messagebox.showerror("Factor invalido",
                                  "Los tres factores de escala tienen que ser numeros (1.0, 1.5, 0.5...).")
            return None

    def _armar_menu_modelo(self):
        if self.menu_modelo is not None:
            self.menu_modelo.destroy()
        nombres = [m[0] for m in self.modelos]
        self.modelo_var.set(nombres[0] if nombres else "")
        if nombres:
            self.menu_modelo = tk.OptionMenu(self.fila_modelo, self.modelo_var, *nombres,
                                              command=lambda _v: self._cambiar_modelo())
            self.menu_modelo.pack(side="left")
        else:
            self.menu_modelo = None

    def _detectar_nivel(self):
        nuevo = nivel_actual(self.e)
        cambio = nuevo != self.nivel
        self.nivel = nuevo
        self.nivel_lbl.configure(text=f"nivel detectado: {self.nivel}" + (" (cambio)" if cambio else ""))
        if cambio:
            self.modelos = listar_modelos(self.nivel)
            self._armar_menu_modelo()
        self._cambiar_modelo()

    def _modelo_elegido(self):
        nombre = self.modelo_var.get()
        return next((nodos for n, nodos in self.modelos if n == nombre), None)

    def _cambiar_modelo(self, *_a):
        self.nodos_actual = self._modelo_elegido()
        if self.nodos_actual is None:
            self.info_lbl.configure(text="no hay modelos en este nivel")
            return
        planos = vertices_planos(self.nodos_actual)
        ram = self.e.ram()
        self.direcciones = []
        encontrados = 0
        for crudo, pos in planos:
            off = ram.find(crudo)
            addr = 0x80000000 + off if off >= 0 else None
            if addr is not None:
                encontrados += 1
            self.direcciones.append((addr, pos))
        self.info_lbl.configure(text=f"{encontrados} de {len(planos)} vertices encontrados en la RAM")
        # encuadre fijo para la vista previa, calculado UNA vez con el modelo sin escalar -si no,
        # dibujar() encuadra cada imagen por separado y una escala pareja se ve siempre igual de
        # grande (le hace zoom para compensar). Mismo criterio que ya usa animar.py.
        V0, _C0, _T0, _D0 = aplanar(self.nodos_actual)
        if len(V0):
            volteado = V0 * np.array([1, -1, 1])
            self._render_centro = (volteado.max(0) + volteado.min(0)) / 2
            self._render_esc = 0.7 * 280 / max(np.ptp(volteado[:, 0]), np.ptp(volteado[:, 1]), 1)
        else:
            self._render_centro = self._render_esc = None
        self.escala_x.delete(0, "end")
        self.escala_x.insert(0, "1.0")
        self.escala_y.delete(0, "end")
        self.escala_y.insert(0, "1.0")
        self.escala_z.delete(0, "end")
        self.escala_z.insert(0, "1.0")
        self._previsualizar()

    def _centro_local(self):
        xs = [p[0] for _, p in self.direcciones]
        ys = [p[1] for _, p in self.direcciones]
        zs = [p[2] for _, p in self.direcciones]
        return sum(xs) / len(xs), sum(ys) / len(ys), sum(zs) / len(zs)

    def _posiciones_escaladas(self, factores):
        fx, fy, fz = factores
        cx, cy, cz = self._centro_local()

        def escalar(p):
            x, y, z = p
            nx = cx + (x - cx) * fx
            ny = cy + (y - cy) * fy
            nz = cz + (z - cz) * fz
            clamp = lambda v: max(-32768, min(32767, round(v)))
            return clamp(nx), clamp(ny), clamp(nz)

        return [escalar(p) for _, p in self.direcciones]

    def _previsualizar(self):
        if self.nodos_actual is None:
            return
        factores = self._factores()
        if factores is None:
            return
        fx, fy, fz = factores
        V, C, T, D = aplanar(self.nodos_actual)
        if len(V) == 0:
            self.info_lbl.configure(text="este modelo no tiene vertices para mostrar")
            return
        centro = V.mean(axis=0)
        Ve = V.copy()
        Ve[:, 0] = centro[0] + (V[:, 0] - centro[0]) * fx
        Ve[:, 1] = centro[1] + (V[:, 1] - centro[1]) * fy
        Ve[:, 2] = centro[2] + (V[:, 2] - centro[2]) * fz
        img = dibujar(Ve, C, T, ancho=360, alto=280, centro=self._render_centro, esc=self._render_esc)
        self._imagen_actual = ImageTk.PhotoImage(img)
        self.preview_lbl.configure(image=self._imagen_actual)

    def _aplicar(self):
        factores = self._factores()
        if factores is None:
            return
        nuevas = self._posiciones_escaladas(factores)
        aplicados = 0
        for (addr, _orig), (nx, ny, nz) in zip(self.direcciones, nuevas):
            if addr is None:
                continue
            self.e.eval(f"wr16({addr},{nx & 0xFFFF}); wr16({addr + 2},{ny & 0xFFFF}); "
                        f"wr16({addr + 4},{nz & 0xFFFF}); return 'ok'")
            aplicados += 1
        self.info_lbl.configure(text=f"aplicado de verdad a {aplicados} vertices en el juego")

    def _restaurar(self):
        aplicados = 0
        for addr, (x, y, z) in self.direcciones:
            if addr is None:
                continue
            self.e.eval(f"wr16({addr},{x & 0xFFFF}); wr16({addr + 2},{y & 0xFFFF}); "
                        f"wr16({addr + 4},{z & 0xFFFF}); return 'ok'")
            aplicados += 1
        self.info_lbl.configure(text=f"restaurado el original en {aplicados} vertices")
        for entrada in (self.escala_x, self.escala_y, self.escala_z):
            entrada.delete(0, "end")
            entrada.insert(0, "1.0")
        self._previsualizar()

    def _tocar_piso(self, signo):
        try:
            elevar = int(self.elevar_entry.get().strip())
        except ValueError:
            messagebox.showerror("Valor invalido", "El campo 'elevar' tiene que ser un numero entero (80, 200...).")
            return
        s = ino.leer_ino(self.nivel)
        g = s["cuadricula"]
        p = leer(self.e, P_SABRINA, "u32")
        x = leer(self.e, p + 0x24, "s32")
        z = leer(self.e, p + 0x2C, "s32")
        idx_verts, _tris, verts_mundo = vertices_bajo(s, g, x, z, self.nivel)
        if not idx_verts:
            self.piso_lbl.configure(
                text="la celda de Sabrina esta vacia, o no se encontro el modelo del mundo de este nivel")
            return
        ram = self.e.ram()
        tocados = 0
        for iv in idx_verts:
            crudo = verts_mundo[iv]
            off = ram.find(crudo)
            if off < 0:
                continue
            addr = 0x80000000 + off
            ox, oy, oz = struct.unpack_from("<3h", crudo, 0)
            if addr not in self._piso_original:
                self._piso_original[addr] = (ox, oy, oz)
            _ax, ay_actual, _az = struct.unpack_from("<3h", ram, off)
            ny = max(-32768, min(32767, ay_actual - signo * elevar))
            self.e.eval(f"wr16({addr + 2},{ny & 0xFFFF}); return 'ok'")
            tocados += 1
        fila, columna, _o = celda_de(x, z, g)
        self.piso_lbl.configure(
            text=f"{'subido' if signo > 0 else 'bajado'} el piso de la celda ({fila},{columna}), {tocados} vertices")

    def _restaurar_piso(self):
        for addr, (x, y, z) in self._piso_original.items():
            self.e.eval(f"wr16({addr},{x & 0xFFFF}); wr16({addr + 2},{y & 0xFFFF}); "
                        f"wr16({addr + 4},{z & 0xFFFF}); return 'ok'")
        self.piso_lbl.configure(text=f"restaurado el piso original en {len(self._piso_original)} vertices")
        self._piso_original = {}
