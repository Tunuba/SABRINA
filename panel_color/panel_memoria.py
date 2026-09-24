"""Paneles de valores numericos de la RAM (no colores): lo que ya esta identificado del objeto de
Sabrina y de unos contadores globales, en decomp\\include\\objeto.h y notas\\FORMATOS.md. Usa los
mismos rd8/rd16/rd32/wr8/wr16/wr32 que ya expone control.lua (ir_a_nivel.py los usa igual para
saltar de nivel).

Todo esto es en vivo, como panel_textura.py: los cambios vuelven al original si recargas el
estado o cerras el emulador. Volverlo permanente (por ejemplo el salto mas alto) es otra cosa: hay
que encontrar la instruccion del ejecutable que fija el impulso inicial y parcharla, como hace
mod_invencible.py con la vida -esto todavia no lo tenemos identificado-.
"""
import tkinter as tk
from tkinter import messagebox

import estilo

P_SABRINA = 0x8007CAF8  # puntero al objeto de Sabrina (decomp/include/objeto.h)

# offset, tipo, ayuda -- del objeto de Sabrina (decomp/include/objeto.h)
CAMPOS_SABRINA = [
    ("vida", 0x118, "s8", "0 a 20 mas o menos. Este mismo campo es la vida de CUALQUIER objeto (enemigos incluidos)."),
    ("estado", 0x70, "s16", "2 = muerta."),
    ("x", 0x24, "s32", "Posicion. 0x1000 = 1.0 unidad del mundo."),
    ("y", 0x28, "s32", "Altura."),
    ("z", 0x2C, "s32", "Posicion."),
    ("velocidad_vertical", 0x3C, "s32",
     "vel_y: la gravedad le suma 0x51E cada paso (30/s). Negativo = subiendo, positivo = cayendo."),
    ("empuje_x", 0x38, "s32", "Empuje externo en x (golpes, fisica)."),
    ("empuje_z", 0x40, "s32", "Empuje externo en z."),
]

IMPULSOS = [("chico", -0x1800), ("mediano", -0x3000), ("grande", -0x6000)]

# nombre, offset, valor de arranque -- un eje cada uno, para que se puedan activar por separado
EJES_BRISA = [
    ("arriba/abajo (el salto, vel_y)", 0x3C, "-1200"),
    ("empuje x", 0x38, "800"),
    ("empuje z", 0x40, "800"),
]
BRISA_MS = 50  # cada cuanto revisa la tecla y reescribe el campo (unos 3 pasos de juego)
# de sobra por si falla la consulta en vivo (PCSX.CONSTS.PAD.BUTTON); nombres_botones() la reemplaza
BOTONES_RESPALDO = ["CROSS", "SQUARE", "TRIANGLE", "CIRCLE", "L1", "R1", "L2", "R2",
                     "UP", "DOWN", "LEFT", "RIGHT", "START", "SELECT"]

# direccion absoluta, tipo, ayuda -- de notas/FORMATOS.md (direcciones de GameShark)
GLOBALES = [
    ("vidas", 0x800C8518, "s8", "Vidas de repuesto."),
    ("gemas", 0x800C8556, "s8", "Gemas recogidas."),
    ("huevos", 0x800C857A, "s8", "Huevos recogidos."),
    ("hechizo 1", 0x8007C8B0, "s8", "De los 6 hechizos, 0x8007C8B0 a 0x8007C8B5."),
    ("hechizo 2", 0x8007C8B1, "s8", ""),
    ("hechizo 3", 0x8007C8B2, "s8", ""),
    ("hechizo 4", 0x8007C8B3, "s8", ""),
    ("hechizo 5", 0x8007C8B4, "s8", ""),
    ("hechizo 6", 0x8007C8B5, "s8", ""),
    ("objeto anacronico 1", 0x8007C88C, "s8", "De los 4, 0x8007C88C a 0x8007C88F."),
    ("objeto anacronico 2", 0x8007C88D, "s8", ""),
    ("objeto anacronico 3", 0x8007C88E, "s8", ""),
    ("objeto anacronico 4", 0x8007C88F, "s8", ""),
]
TRUCO_INVENCIBLE = (0x8007CB74, "s32")  # si no es 0, no recibe dano; el juego nunca la prende sola


def leer(e, addr, tipo):
    if tipo in ("s8", "u8"):
        v = int(e.eval(f"return rd8({addr})"))
        return v & 0xFF if tipo == "u8" else v
    if tipo in ("s16", "u16"):
        v = int(e.eval(f"return rd16({addr})")) & 0xFFFF
        return v - 0x10000 if tipo == "s16" and v >= 0x8000 else v
    if tipo in ("s32", "u32"):
        v = int(e.eval(f"return rd32({addr})")) & 0xFFFFFFFF
        return v - 0x100000000 if tipo == "s32" and v >= 0x80000000 else v
    raise ValueError(tipo)


def escribir(e, addr, tipo, valor):
    fn = {"s8": "wr8", "u8": "wr8", "s16": "wr16", "u16": "wr16", "s32": "wr32", "u32": "wr32"}[tipo]
    mask = {"s8": 0xFF, "u8": 0xFF, "s16": 0xFFFF, "u16": 0xFFFF, "s32": 0xFFFFFFFF, "u32": 0xFFFFFFFF}[tipo]
    e.eval(f"{fn}({addr}, {valor & mask}); return 'ok'")


def nombres_botones(e):
    """Los nombres reales de PCSX.CONSTS.PAD.BUTTON, preguntados en vivo (mejor que copiarlos a
    mano y que se desactualicen). Si la consulta falla, BOTONES_RESPALDO."""
    try:
        r = e.eval(
            "local t = {} for k in pairs(PCSX.CONSTS.PAD.BUTTON) do t[#t+1] = k end "
            "table.sort(t) return table.concat(t, ',')"
        )
        nombres = [n for n in r.strip().split(",") if n]
        return nombres or BOTONES_RESPALDO
    except OSError:
        return BOTONES_RESPALDO


def boton_presionado(e, nombre):
    """True si ese boton esta apretado de verdad en el juego (teclado o control mapeado a ese
    pad) ahora mismo -PCSX.SIO0.slots[1].pads[1].getButton(), no lo que nosotros simulamos-."""
    r = e.eval(f"return tostring(PCSX.SIO0.slots[1].pads[1].getButton(PCSX.CONSTS.PAD.BUTTON.{nombre}))")
    return r.strip() == "true"


class Fila:
    """Una fila: nombre + valor actual + campo para escribir uno nuevo + boton aplicar."""

    def __init__(self, padre, nombre, ayuda, leer_cb, escribir_cb):
        self.leer_cb = leer_cb
        self.escribir_cb = escribir_cb
        f = tk.Frame(padre, bg=estilo.BG)
        f.pack(fill="x", pady=2)
        tk.Label(f, text=nombre, fg=estilo.FG, bg=estilo.BG, font=estilo.TEXTO, width=20,
                 anchor="w").pack(side="left")
        self.valor_lbl = tk.Label(f, text="?", fg=estilo.ACENTO, bg=estilo.BG, font=estilo.TEXTO,
                                   width=10, anchor="w")
        self.valor_lbl.pack(side="left")
        self.entrada = tk.Entry(f, width=10, bg=estilo.BG_TARJETA, fg=estilo.FG, insertbackground=estilo.FG,
                                  relief="flat")
        self.entrada.pack(side="left", padx=(4, 4))
        self.entrada.bind("<Return>", lambda ev: self.aplicar())
        estilo.boton(f, "Aplicar", self.aplicar).pack(side="left")
        if ayuda:
            tk.Label(f, text=ayuda, fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO,
                      anchor="w", wraplength=380, justify="left").pack(side="left", padx=(10, 0))

    def releer(self):
        try:
            v = self.leer_cb()
        except Exception:
            self.valor_lbl.configure(text="error")
            return
        self.valor_lbl.configure(text=str(v))
        self.entrada.delete(0, "end")
        self.entrada.insert(0, str(v))

    def aplicar(self):
        texto = self.entrada.get().strip()
        try:
            valor = int(texto, 0)  # acepta 0x... y negativos
        except ValueError:
            messagebox.showerror("Valor invalido", f"'{texto}' no es un numero (probá 123, -50 o 0x1F).")
            return
        self.escribir_cb(valor)
        self.releer()


class FilaBrisa:
    """Una brisa de un solo eje: un valor a mantener, una tecla, y un check "activar al mantener
    la tecla presionada". Mientras esta tildado, cada BRISA_MS pregunta si esa tecla esta apretada
    de verdad en el juego (boton_presionado) y solo si lo esta reescribe el campo; si no, no toca
    nada ese instante (el juego sigue con su fisica normal, por eso se siente soltar y agarrar)."""

    def __init__(self, padre, nombre, offset, valor_inicial, botones, base_cb, e):
        self.offset = offset
        self.base_cb = base_cb
        self.e = e
        f = tk.Frame(padre, bg=estilo.BG)
        f.pack(fill="x", pady=3)
        self.widget = f
        tk.Label(f, text=nombre, fg=estilo.FG, bg=estilo.BG, font=estilo.TEXTO, width=26,
                 anchor="w").pack(side="left")
        tk.Label(f, text="valor:", fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO).pack(side="left")
        self.valor = tk.Entry(f, width=8, bg=estilo.BG_TARJETA, fg=estilo.FG, insertbackground=estilo.FG,
                               relief="flat")
        self.valor.insert(0, valor_inicial)
        self.valor.pack(side="left", padx=(2, 12))
        tk.Label(f, text="tecla:", fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO).pack(side="left")
        self.tecla = tk.StringVar(value=botones[0])
        tk.OptionMenu(f, self.tecla, *botones).pack(side="left", padx=(2, 12))
        self.activa = tk.BooleanVar()
        tk.Checkbutton(f, text="Activar al mantener la tecla", variable=self.activa, command=self._toggle,
                       fg=estilo.FG, bg=estilo.BG, selectcolor=estilo.BG_TARJETA, activebackground=estilo.BG,
                       activeforeground=estilo.FG, font=estilo.TEXTO_CHICO).pack(side="left")
        self.estado_lbl = tk.Label(f, text="", fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO, width=12)
        self.estado_lbl.pack(side="left", padx=(8, 0))

    def _toggle(self):
        self.estado_lbl.configure(text="")
        if self.activa.get():
            self._tick()

    def _tick(self):
        if not self.widget.winfo_exists() or not self.activa.get():
            return
        try:
            apretada = boton_presionado(self.e, self.tecla.get())
            if apretada:
                valor = int(self.valor.get().strip(), 0)
                escribir(self.e, self.base_cb() + self.offset, "s32", valor)
        except (ValueError, OSError):
            apretada = False
        self.estado_lbl.configure(text="empujando" if apretada else "(soltada)")
        self.widget.after(BRISA_MS, self._tick)


class FrameMovimiento(tk.Frame):
    def __init__(self, padre, e, volver):
        super().__init__(padre, bg=estilo.BG)
        self.e = e
        estilo.encabezado(
            self, "Saltos y movimiento",
            "Posicion, empuje y velocidad vertical del objeto de Sabrina. En vivo: se pierde al recargar el estado.",
            volver=volver)

        estilo.separador(self, "Impulso rapido (prueba la sensacion de un salto)")
        impulsos = tk.Frame(self, bg=estilo.BG)
        impulsos.pack(fill="x", padx=14)
        tk.Label(impulsos, text="empuja vel_y para arriba:", fg=estilo.FG_MUTED, bg=estilo.BG,
                 font=estilo.TEXTO).pack(side="left")
        for nombre, valor in IMPULSOS:
            estilo.boton(impulsos, f"{nombre} ({valor:#x})",
                         lambda v=valor: self._impulso(v)).pack(side="left", padx=4)

        estilo.separador(self, "Brisas (una por eje, se mantiene mientras aguantes la tecla)")
        tk.Label(self, text="Cada una es independiente: podes tener la de arriba/abajo activada y las de "
                             "empuje x/z apagadas, o las tres juntas. Tildala, elegi la tecla, y mientras la "
                             "tengas apretada de verdad en el juego reescribe ese campo -no lo que hace clic "
                             "en esta ventana, sino la tecla real del control/teclado del juego-.",
                  fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO, anchor="w",
                  wraplength=760, justify="left").pack(anchor="w", padx=14, pady=(0, 4))
        brisas = tk.Frame(self, bg=estilo.BG)
        brisas.pack(fill="x", padx=14)
        botones = nombres_botones(e)
        self.brisas = [FilaBrisa(brisas, nombre, offset, valor, botones, self._base, self.e)
                       for nombre, offset, valor in EJES_BRISA]

        estilo.separador(self, "Campos del objeto")
        cuerpo = tk.Frame(self, bg=estilo.BG)
        cuerpo.pack(fill="both", expand=True, padx=14)
        self.filas = []
        for nombre, offset, tipo, ayuda in CAMPOS_SABRINA:
            fila = Fila(cuerpo, nombre, ayuda,
                        leer_cb=lambda o=offset, t=tipo: leer(self.e, self._base() + o, t),
                        escribir_cb=lambda v, o=offset, t=tipo: escribir(self.e, self._base() + o, t, v))
            self.filas.append(fila)

        estilo.boton(self, "Releer todo", self.releer).pack(anchor="w", padx=14, pady=12)
        self.releer()

    def _base(self):
        return leer(self.e, P_SABRINA, "u32")

    def _impulso(self, valor):
        escribir(self.e, self._base() + 0x3C, "s32", valor)
        self.releer()

    def releer(self):
        for f in self.filas:
            f.releer()


class FrameVidaObjetos(tk.Frame):
    def __init__(self, padre, e, volver):
        super().__init__(padre, bg=estilo.BG)
        self.e = e
        estilo.encabezado(
            self, "Vida y objetos",
            "Vidas, gemas, huevos, hechizos y objetos anacronicos recogidos, mas el truco de invencibilidad "
            "escondido en el ejecutable (nunca se prende solo).",
            volver=volver)

        estilo.separador(self, "Contadores")
        cuerpo = tk.Frame(self, bg=estilo.BG)
        cuerpo.pack(fill="both", expand=True, padx=14)
        self.filas = []
        for nombre, addr, tipo, ayuda in GLOBALES:
            fila = Fila(cuerpo, nombre, ayuda,
                        leer_cb=lambda a=addr, t=tipo: leer(self.e, a, t),
                        escribir_cb=lambda v, a=addr, t=tipo: escribir(self.e, a, t, v))
            self.filas.append(fila)

        estilo.separador(self, "Trucos")
        trucos = tk.Frame(self, bg=estilo.BG)
        trucos.pack(fill="x", padx=14)
        self.invencible = tk.BooleanVar()
        tk.Checkbutton(trucos, text="Invencible (no recibe dano de enemigos ni de suelo)",
                       variable=self.invencible, command=self._toggle_invencible,
                       fg=estilo.FG, bg=estilo.BG, selectcolor=estilo.BG_TARJETA, activebackground=estilo.BG,
                       activeforeground=estilo.FG, font=estilo.TEXTO).pack(anchor="w")

        estilo.boton(self, "Releer todo", self.releer).pack(anchor="w", padx=14, pady=12)
        self.releer()

    def _toggle_invencible(self):
        addr, tipo = TRUCO_INVENCIBLE
        escribir(self.e, addr, tipo, 1 if self.invencible.get() else 0)

    def releer(self):
        for f in self.filas:
            f.releer()
        addr, tipo = TRUCO_INVENCIBLE
        self.invencible.set(leer(self.e, addr, tipo) != 0)
