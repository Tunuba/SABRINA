"""Colores y widgets compartidos por los paneles, para que todos se vean parte de la misma
aplicacion (tema oscuro, acento violeta a tono con el mod de bruja)."""
import tkinter as tk

BG = "#1b1b23"
BG_TARJETA = "#26262f"
BG_TARJETA_HOVER = "#302f3d"
FG = "#eceaf4"
FG_MUTED = "#9d9aad"
ACENTO = "#b98cff"
ACENTO_TEXTO = "#1b1b23"
BUENO = "#7cd992"
MALO = "#ff8080"

TITULO = ("Segoe UI", 16, "bold")
SUBTITULO = ("Segoe UI", 10)
ENCABEZADO = ("Segoe UI", 12, "bold")
TEXTO = ("Consolas", 10)
TEXTO_CHICO = ("Consolas", 9)


def ventana_base(win, titulo):
    win.configure(bg=BG)
    win.title(titulo)
    try:
        win.tk.call("tk", "scaling", 1.15)
    except tk.TclError:
        pass


def encabezado(padre, texto, subtexto=None, volver=None):
    """Franja de arriba: titulo del panel y, si se pasa volver, un boton para ir al menu."""
    f = tk.Frame(padre, bg=BG)
    f.pack(fill="x", padx=14, pady=(12, 6))
    if volver:
        tk.Button(f, text="< Menu", command=volver, bg=BG_TARJETA, fg=FG, activebackground=ACENTO,
                  activeforeground=ACENTO_TEXTO, relief="flat", padx=10, cursor="hand2").pack(side="left", padx=(0, 12))
    caja = tk.Frame(f, bg=BG)
    caja.pack(side="left", fill="x", expand=True)
    tk.Label(caja, text=texto, bg=BG, fg=FG, font=TITULO, anchor="w").pack(anchor="w")
    if subtexto:
        tk.Label(caja, text=subtexto, bg=BG, fg=FG_MUTED, font=SUBTITULO, anchor="w",
                  wraplength=760, justify="left").pack(anchor="w")
    return f


def separador(padre, texto):
    f = tk.Frame(padre, bg=BG)
    f.pack(fill="x", padx=14, pady=(14, 4))
    tk.Label(f, text=texto, bg=BG, fg=ACENTO, font=ENCABEZADO, anchor="w").pack(anchor="w")
    tk.Frame(f, bg=BG_TARJETA, height=1).pack(fill="x", pady=(4, 0))
    return f


def boton_menu(padre, titulo, descripcion, comando):
    """Una tarjeta grande y clickeable para el menu principal."""
    marco = tk.Frame(padre, bg=BG_TARJETA, cursor="hand2", highlightthickness=1,
                      highlightbackground=BG_TARJETA, highlightcolor=ACENTO)
    tk.Label(marco, text=titulo, bg=BG_TARJETA, fg=FG, font=ENCABEZADO, anchor="w").pack(
        anchor="w", padx=16, pady=(12, 2))
    tk.Label(marco, text=descripcion, bg=BG_TARJETA, fg=FG_MUTED, font=SUBTITULO, anchor="w",
              wraplength=520, justify="left").pack(anchor="w", padx=16, pady=(0, 12))

    def entrar(_ev=None):
        marco.configure(highlightbackground=BG_TARJETA)
        comando()

    def hover_on(_ev=None):
        marco.configure(bg=BG_TARJETA_HOVER, highlightbackground=ACENTO)
        for w in marco.winfo_children():
            w.configure(bg=BG_TARJETA_HOVER)

    def hover_off(_ev=None):
        marco.configure(bg=BG_TARJETA, highlightbackground=BG_TARJETA)
        for w in marco.winfo_children():
            w.configure(bg=BG_TARJETA)

    for w in (marco, *marco.winfo_children()):
        w.bind("<Button-1>", entrar)
        w.bind("<Enter>", hover_on)
        w.bind("<Leave>", hover_off)
    marco.pack(fill="x", pady=7)
    return marco


def boton(padre, texto, comando, **kw):
    return tk.Button(padre, text=texto, command=comando, bg=BG_TARJETA, fg=FG, activebackground=ACENTO,
                      activeforeground=ACENTO_TEXTO, relief="flat", padx=10, pady=4, cursor="hand2", **kw)
