"""La camara real: siete valores en `p - 0xfc` a `p - 0xe0` (p = puntero al objeto de Sabrina,
0x8007CAF8), encontrados girando la camara con L2 (Sabrina QUIETA, para no mezclar rotacion con
posicion) y comparando fotos de RAM. Congelandolos con un gancho de GPU::Vsync: la camara dejo de
girar con L2 y dejo de seguir a Sabrina al teletransportarla lejos -se quedo mirando el mismo lugar
vacio-. Dos candidatos anteriores (un punto que solo copiaba su x/z, y una segunda terna que
orbitaba pero sin efecto real) se descartaron: se podian congelar pero la camara seguia igual.

Cada uno de los siete se traba por separado -no es todo o nada-: el que no tildes, el juego lo
sigue recalculando solo como si nada. Probados uno por uno (notas\\capturas\\explorar_7_valores):
el valor 0 rota la vista con claridad, el 2 la mueve fuerte (casi de encima de otro personaje), el
3 es de una escala enorme (millones; empujarlo mucho manda la camara a un lugar vacio, pantalla
negra), y el 1/4/5 no se notaron mucho con los empujones que se probaron. Sin confirmar del todo
que es cada uno -no llegamos a leer camara.c, el codigo real, en esta copia-.

El gancho se instala UNA vez por sesion del emulador (siete globales CAM_ON0..CAM_ON6 de Lua) y
cada checkbox solo prende/apaga el suyo; entrar y salir del panel no los duplica.

Camara cinematica: probando a mano, empujar solo el valor 0 un poquito cada cuadro (sin tocar los
otros 6, que el juego los sigue calculando solo) da una camara que orbita despacio alrededor de
Sabrina mientras la sigue -a diferencia de tratar de calcular los siete a mano con una formula
(se probo, dio pantallas negras y angulos rotos: la relacion no es lineal en coordenadas del
mundo). Ojo: esto y trabar el valor 0 a mano compiten por la misma direccion: si tildas los dos a
la vez, gana el que se instalo despues.

Uso: entra desde el menu de panel_color.py, no se corre solo.
"""
import tkinter as tk
from tkinter import messagebox

import estilo
from panel_memoria import P_SABRINA, leer, escribir

# offset desde el puntero de Sabrina -confirmado girando la camara con Sabrina quieta
CAMPOS_TRABA = [-0xFC, -0xF8, -0xF4, -0xF0, -0xE8, -0xE4, -0xE0]


class FilaCamara:
    """Un valor de la camara: su numero actual, un campo para escribir uno nuevo, y un check para
    trabarlo -mientras esta trabado, el gancho de Vsync lo sostiene en lo ultimo que se aplico acá;
    destrabado, el juego lo recalcula solo otra vez-."""

    def __init__(self, padre, i, offset, e, base_cb):
        self.i = i
        self.offset = offset
        self.e = e
        self.base_cb = base_cb
        f = tk.Frame(padre, bg=estilo.BG)
        f.pack(fill="x", pady=2)
        tk.Label(f, text=f"valor {i} (p{offset:+#x})", fg=estilo.FG, bg=estilo.BG, font=estilo.TEXTO,
                 width=16, anchor="w").pack(side="left")
        self.valor_lbl = tk.Label(f, text="?", fg=estilo.ACENTO, bg=estilo.BG, font=estilo.TEXTO,
                                   width=12, anchor="w")
        self.valor_lbl.pack(side="left")
        self.entrada = tk.Entry(f, width=10, bg=estilo.BG_TARJETA, fg=estilo.FG, insertbackground=estilo.FG,
                                  relief="flat")
        self.entrada.pack(side="left", padx=(4, 4))
        self.entrada.bind("<Return>", lambda ev: self.aplicar())
        estilo.boton(f, "Aplicar", self.aplicar).pack(side="left")
        self.trabada = tk.BooleanVar()
        tk.Checkbutton(f, text="Trabar", variable=self.trabada, command=self.toggle,
                       fg=estilo.FG, bg=estilo.BG, selectcolor=estilo.BG_TARJETA, activebackground=estilo.BG,
                       activeforeground=estilo.FG, font=estilo.TEXTO).pack(side="left", padx=(10, 0))

    def toggle(self):
        if self.trabada.get():
            v = leer(self.e, self.base_cb() + self.offset, "s32")
            self.e.eval(f"CV{self.i}={v & 0xFFFFFFFF}")
            self.e.eval(f"CAM_ON{self.i}=true")
        else:
            self.e.eval(f"CAM_ON{self.i}=false")
        self.releer()

    def aplicar(self):
        texto = self.entrada.get().strip()
        try:
            valor = int(texto, 0)  # acepta 0x... y negativos
        except ValueError:
            messagebox.showerror("Valor invalido", f"'{texto}' no es un numero (probá 123, -50 o 0x1F).")
            return
        self.e.eval(f"CV{self.i}={valor & 0xFFFFFFFF}")
        if not self.trabada.get():
            # sin trabar esto se puede perder al toque (el juego lo recalcula), pero se intenta igual
            escribir(self.e, self.base_cb() + self.offset, "s32", valor)
        self.releer()

    def releer(self):
        v = leer(self.e, self.base_cb() + self.offset, "s32")
        self.valor_lbl.configure(text=str(v))
        self.entrada.delete(0, "end")
        self.entrada.insert(0, str(v))


class FrameCamara(tk.Frame):
    def __init__(self, padre, e, volver):
        super().__init__(padre, bg=estilo.BG)
        self.e = e
        estilo.encabezado(
            self, "Camara",
            "El bloque real que usa el juego para la camara, encontrado girandola con L2 con Sabrina "
            "quieta. Traba los valores que quieras y dejá los demas libres.",
            volver=volver)

        estilo.separador(self, "Los siete valores (p - 0xfc a p - 0xe0)")
        tk.Label(self, text="Cada uno se traba por separado: el que tildes queda clavado (editable "
                             "mientras lo esta); los que no, el juego los sigue calculando solo.",
                  fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO, anchor="w",
                  wraplength=760, justify="left").pack(anchor="w", padx=14, pady=(0, 4))
        cuerpo = tk.Frame(self, bg=estilo.BG)
        cuerpo.pack(fill="x", padx=14)
        self.filas = [
            FilaCamara(cuerpo, i, o, self.e, self._base)
            for i, o in enumerate(CAMPOS_TRABA)
        ]
        self._instalar_gancho()

        estilo.boton(self, "Releer todo", self.releer).pack(anchor="w", padx=14, pady=12)

        estilo.separador(self, "Camara cinematica (orbita sola alrededor de Sabrina)")
        tk.Label(self, text="Empuja solo el valor 0 un poquito cada cuadro; el juego sigue calculando "
                             "los otros 6 solo, por eso no se rompe el encuadre. Probado caminando: la "
                             "sigue mientras gira.",
                  fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO_CHICO, anchor="w",
                  wraplength=760, justify="left").pack(anchor="w", padx=14, pady=(0, 4))
        orbital = tk.Frame(self, bg=estilo.BG)
        orbital.pack(fill="x", padx=14, pady=(0, 12))
        self.orbital_activa = tk.BooleanVar()
        tk.Checkbutton(orbital, text="Activa", variable=self.orbital_activa, command=self._toggle_orbital,
                       fg=estilo.FG, bg=estilo.BG, selectcolor=estilo.BG_TARJETA, activebackground=estilo.BG,
                       activeforeground=estilo.FG, font=estilo.TEXTO).pack(side="left")
        tk.Label(orbital, text="velocidad:", fg=estilo.FG_MUTED, bg=estilo.BG, font=estilo.TEXTO).pack(
            side="left", padx=(10, 4))
        self.orbital_vel = tk.Entry(orbital, width=8, bg=estilo.BG_TARJETA, fg=estilo.FG,
                                     insertbackground=estilo.FG, relief="flat")
        self.orbital_vel.insert(0, "900")
        self.orbital_vel.pack(side="left")
        self.orbital_vel.bind("<Return>", lambda ev: self._aplicar_velocidad_orbital())
        estilo.boton(orbital, "Aplicar velocidad", self._aplicar_velocidad_orbital).pack(side="left", padx=(6, 0))
        tk.Label(orbital, text="(negativo = al reves)", fg=estilo.FG_MUTED, bg=estilo.BG,
                  font=estilo.TEXTO_CHICO).pack(side="left", padx=(10, 0))
        self._instalar_orbital()

        self.releer()

    def _base(self):
        return leer(self.e, P_SABRINA, "u32")

    def _instalar_gancho(self):
        """Un gancho de Vsync por direccion, cada uno con su propia bandera CAM_ONi -asi cada check
        prende/apaga solo el suyo-. Se fija primero si ya estaba instalado (CAM_ON0 existe) para no
        duplicarlo si entras y salis del panel varias veces en la misma sesion del emulador."""
        ya_instalado = self.e.eval("return CAM_ON0~=nil") == "true"
        if ya_instalado:
            for i, fila in enumerate(self.filas):
                fila.trabada.set(self.e.eval(f"return CAM_ON{i}") == "true")
            return
        p = self._base()
        for i, o in enumerate(CAMPOS_TRABA):
            addr = p + o
            self.e.eval(f"CV{i}=0")
            self.e.eval(f"CAM_ON{i}=false")
            codigo = (
                f"CAMROT{i}=PCSX.Events.createEventListener('GPU::Vsync',"
                f"function() if CAM_ON{i} then wr32({addr},CV{i}) end end) return 'ok'"
            )
            self.e.eval(codigo)

    def _instalar_orbital(self):
        """Gancho de Vsync aparte, sobre la misma direccion que el valor 0, gateado por CAM_ORB.
        Misma idea que _instalar_gancho: se instala una sola vez por sesion."""
        ya_instalado = self.e.eval("return CAM_ORB~=nil") == "true"
        if ya_instalado:
            self.orbital_activa.set(self.e.eval("return CAM_ORB") == "true")
            vel = self.e.eval("return CAM_ORB_VEL")
            self.orbital_vel.delete(0, "end")
            self.orbital_vel.insert(0, vel)
            return
        addr0 = self._base() + CAMPOS_TRABA[0]
        self.e.eval("CAM_ORB=false")
        self.e.eval("CAM_ORB_VEL=900")
        codigo = (
            f"CAMORB=PCSX.Events.createEventListener('GPU::Vsync',"
            f"function() if CAM_ORB then wr32({addr0},rd32({addr0})+CAM_ORB_VEL) end end) return 'ok'"
        )
        self.e.eval(codigo)

    def _toggle_orbital(self):
        self.e.eval("CAM_ORB=true" if self.orbital_activa.get() else "CAM_ORB=false")

    def _aplicar_velocidad_orbital(self):
        texto = self.orbital_vel.get().strip()
        try:
            v = int(texto, 0)
        except ValueError:
            messagebox.showerror("Valor invalido", f"'{texto}' no es un numero (probá 900, -900 o 0x100).")
            return
        self.e.eval(f"CAM_ORB_VEL={v}")

    def releer(self):
        for f in self.filas:
            f.releer()
