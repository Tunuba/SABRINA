"""Genera niveles\\greendale.json: Greendale entero, el pueblo de Sabrina, bajo la niebla de Silent Hill.

Un pueblo abandonado y gris hecho con los bloques del motor (nivel_plataformas.py): la casa Spellman con su
torreon, su porche y el cementerio de atras (ahi aparece Sabrina); Main Street con faroles, la libreria
Cerberus, el diner del doctor Cerberus, el cine Paramount con marquesina, la farmacia y el ayuntamiento con la
torre del reloj; Baxter High con su portico de columnas y su segundo piso; la calle Kinkle que cruza el pueblo;
la Academia de Artes Ocultas con sus dos torres; la Iglesia de la Noche con un campanario que se sube por
escalones hasta la campana (la meta); el bosque de Greendale con arboles muertos; el rio Sweetwater con su
puente de tablones y, al otro lado, la boca de las minas Kinkle con la colina detras. El cielo es niebla: los
tres colores casi iguales, grises, y la isla cae a la niebla por los cuatro lados.

Uso: python mapa_greendale.py        (escribe niveles\\greendale.json y dice cuanto ocupa)

Medidas: unidades del modelo, todo en multiplos de 256 (Sabrina mide ~250, salta 380 y sube sola escalones de
hasta ~360). Las alturas aqui son positivas hacia arriba y se pasan a h = -alto. El .INO tiene tamano fijo
(313.628 bytes): los suelos llevan cuadros de 512 y lados de 1024, los edificios cuadros de 512; con eso el
pueblo entero cabe con margen (tamano_ino lo mide al final).
"""
import os

import nivel_plataformas as n

ISLA = 600                                   # cuanto baja la isla hasta la niebla
# texturas (indices de la galeria del editor, PALETA en nivel_plataformas)
ASFALTO, ACERA, HIERBA, PIEDRA, VETEADA, LISA = 13, 67, 81, 16, 1, 13
LADRILLO, TEJAS, TABLONES, PUERTA, PANELES, ARCO = 88, 96, 97, 108, 110, 109
VALLA, AGUA, MARMOL, AZULEJO, LETRERO, LETRERO2 = 100, 66, 69, 78, 94, 95
OXIDO, TELA_ROJA, ORO, GLIFO = 89, 106, 77, 79
# colores (128 = la textura tal cual; menos = mas oscuro: todo el pueblo va apagado por la niebla)
GRIS_CALLE, GRIS_ACERA, VERDE_MUERTO = (80, 82, 88), (105, 105, 108), (70, 82, 62)
MADERA_VIEJA, LADRILLO_SUCIO, PIEDRA_FRIA = (100, 88, 78), (118, 88, 80), (92, 94, 104)
TEJA_OSCURA, AGUA_TURBIA, MARMOL_SUCIO = (110, 80, 72), (58, 78, 88), (96, 100, 125)
TURQUESA_APAGADO, HUESO, HOLLIN, ROJO_OXIDO = (90, 118, 118), (130, 128, 120), (60, 60, 64), (120, 70, 60)
bloques = []


def suelo(nombre, x0, z0, x1, z1, h=0, **kw):
    """Un trozo de suelo de la isla: baja ISLA hasta la niebla, cuadros de 512 y lados de 1024 (no se ven)."""
    kw.setdefault("prof", ISLA)
    kw.setdefault("paso", 512)
    kw.setdefault("paso_lado", 1024)
    kw.setdefault("tex_lado", PIEDRA)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -h, **kw))


def edificio(nombre, x0, z0, x1, z1, alto, base=0, **kw):
    """Un bloque macizo (casa, tienda, torre, columna, lapida) de 'alto' sobre la altura 'base'. Baja hasta la base
    (con 'extra' sigue mas abajo, para lo que se apoya en la isla)."""
    extra = kw.pop("extra", 0)
    kw.setdefault("color", LADRILLO_SUCIO)
    kw.setdefault("tex_tapa", PIEDRA)
    kw.setdefault("tex_lado", LADRILLO)
    kw.setdefault("paso", 512)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -(base + alto), pared=True, prof=alto + extra, **kw))


def tejado(nombre, x0, z0, x1, z1, base, alto=200, **kw):
    """Una losa con cara inferior (se ve desde abajo): tejados que sobresalen, marquesinas, dinteles."""
    kw.setdefault("color", TEJA_OSCURA)
    kw.setdefault("tex_tapa", TEJAS)
    kw.setdefault("tex_lado", TEJAS)
    kw.setdefault("paso", 512)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -(base + alto), pared=True, prof=alto, techo=True, **kw))


def escalon(nombre, x0, z0, x1, z1, alto, **kw):
    """Un peldano plano (se sube solo, hasta 360): no es pared, asi validar avisa si no se alcanza. Por defecto
    baja hasta el suelo; con prof corto y techo es una losa que flota (la escalera del campanario)."""
    kw.setdefault("color", PIEDRA_FRIA)
    kw.setdefault("tex_tapa", PIEDRA)
    kw.setdefault("tex_lado", PIEDRA)
    kw.setdefault("paso", 512)
    kw.setdefault("prof", alto)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -alto, **kw))


def rampa(nombre, x0, z0, x1, z1, h_ini, h_fin, eje, **kw):
    kw.setdefault("prof", 300)
    kw.setdefault("tex_tapa", TABLONES)
    kw.setdefault("tex_lado", PIEDRA)
    kw.setdefault("color", MADERA_VIEJA)
    bloques.append(n.nueva(nombre, x0, z0, x1, z1, -h_ini, h2=-h_fin, eje=eje, **kw))


def arbol(nombre, x, z, alto=1100, copa=False):
    """Un tronco de 256 (arbol muerto); con copa, una losa verde oscura encima que se ve desde abajo."""
    edificio(f"{nombre}", x, z, x + 256, z + 256, alto, color=MADERA_VIEJA, tex_tapa=PUERTA, tex_lado=PUERTA,
             paso_lado=1024)
    if copa:
        tejado(f"{nombre}_copa", x - 256, z - 256, x + 512, z + 512, alto, 300, color=VERDE_MUERTO, tex_tapa=VALLA,
               tex_lado=VALLA)


def farol(nombre, x, z):
    edificio(nombre, x, z, x + 256, z + 256, 700, color=HOLLIN, tex_tapa=ORO, tex_lado=LISA, paso_lado=1024)


# ================================================================== la isla (suelos), 13824 x 10752
# calles: Main Street (a lo largo de X) y la calle Kinkle (a lo largo de Z) se cruzan
suelo("main_street_o", -4096, -512, 5120, 1024, color=GRIS_CALLE, tex_tapa=ASFALTO)
suelo("main_street_e", 6656, -512, 9728, 1024, color=GRIS_CALLE, tex_tapa=ASFALTO)
suelo("calle_kinkle", 5120, -5120, 6656, 5632, color=GRIS_CALLE, tex_tapa=ASFALTO)
# lotes del norte: jardin y cementerio Spellman, patio de Baxter High, explanada de la Academia
suelo("jardin_spellman", -4096, -5120, 1024, -512, color=VERDE_MUERTO, tex_tapa=HIERBA)     # contiene la salida; el
suelo("patio_baxter", 1024, -5120, 5120, -512, color=GRIS_ACERA, tex_tapa=ACERA)                # cementerio es su mitad norte
suelo("explanada_academia", 6656, -5120, 9728, -512, color=GRIS_ACERA, tex_tapa=LISA)
# lotes del sur: acera de las tiendas, atrio de la iglesia, bosque, rio y la otra orilla con la mina
suelo("acera_tiendas", -4096, 1024, 5120, 2816, color=GRIS_ACERA, tex_tapa=ACERA)
suelo("atrio_iglesia", 6656, 1024, 9728, 5632, color=GRIS_ACERA, tex_tapa=LISA)
suelo("bosque", -4096, 2816, 5120, 4096, color=VERDE_MUERTO, tex_tapa=HIERBA)
suelo("rio_sweetwater", -4096, 4096, 5120, 4608, h=-400, color=AGUA_TURBIA, tex_tapa=AGUA, prof=200)
suelo("orilla_mina", -4096, 4608, 5120, 5632, color=VERDE_MUERTO, tex_tapa=HIERBA)

# ================================================================== la casa Spellman (funeraria) y el cementerio
# Sabrina aparece en (128, -896): en el jardin, frente al porche
edificio("casa_spellman", -3072, -3328, -1024, -1280, 1100, color=MADERA_VIEJA, tex_tapa=TEJAS, tex_lado=PANELES)
edificio("torreon_spellman", -1536, -3328, -1024, -2816, 1900, color=MADERA_VIEJA, tex_tapa=TEJAS,
         tex_lado=PANELES)
escalon("porche_spellman", -1024, -2304, -512, -1536, 250, color=MADERA_VIEJA, tex_tapa=TABLONES, tex_lado=TABLONES)
tejado("techo_porche", -1024, -2304, -256, -1536, 1100, 150, color=MADERA_VIEJA, tex_tapa=TABLONES,
       tex_lado=TABLONES)
for i, (x, z) in enumerate(((-3584, -4864), (-2816, -4608), (-2048, -4864), (-1280, -4608), (-512, -4864),
                            (-3328, -4096), (-2048, -4096))):
    edificio(f"lapida{i + 1}", x, z, x + 256, z + 256, 300 if i % 2 else 400, color=HUESO, tex_tapa=VETEADA,
             tex_lado=VETEADA, paso_lado=1024)
edificio("cripta", 256, -4864, 1024, -4096, 700, color=PIEDRA_FRIA, tex_tapa=PIEDRA, tex_lado=VETEADA)
tejado("cripta_tejado", 128, -4992, 1024, -3968, 700, 150, color=PIEDRA_FRIA, tex_tapa=PIEDRA, tex_lado=PIEDRA)
# seto bajo entre el jardin y Main Street, con la verja abierta frente a la casa
edificio("seto_o", -4096, -768, -1536, -512, 250, color=VERDE_MUERTO, tex_tapa=VALLA, tex_lado=VALLA, paso_lado=1024)
edificio("seto_e", -256, -768, 1024, -512, 250, color=VERDE_MUERTO, tex_tapa=VALLA, tex_lado=VALLA, paso_lado=1024)
edificio("seto_n", -4096, -5120, 1024, -4864, 250, color=VERDE_MUERTO, tex_tapa=VALLA, tex_lado=VALLA, paso_lado=1024)
edificio("seto_cementerio", -4096, -3584, -3328, -3328, 250, color=VERDE_MUERTO, tex_tapa=VALLA, tex_lado=VALLA,
         paso_lado=1024)

# ================================================================== Baxter High (norte de Main Street)
edificio("baxter_high", 1536, -4608, 4608, -2048, 1000, color=LADRILLO_SUCIO, tex_tapa=PIEDRA, tex_lado=LADRILLO)
edificio("baxter_piso2", 2048, -4352, 4096, -2304, 600, base=1000, color=LADRILLO_SUCIO, tex_tapa=PIEDRA,
         tex_lado=LADRILLO, paso_lado=1024)
for i, x in enumerate((2304, 3072, 3840)):
    edificio(f"columna_baxter{i + 1}", x, -1536, x + 256, -1280, 1000, color=HUESO, tex_tapa=MARMOL, tex_lado=VETEADA,
             paso_lado=1024)
tejado("portico_baxter", 2048, -1792, 4096, -1024, 1000, 200, color=PIEDRA_FRIA, tex_tapa=PIEDRA, tex_lado=PIEDRA,
       paso_lado=1024)
escalon("escalera_baxter1", 2304, -1280, 3840, -1024, 125, color=HUESO, tex_tapa=VETEADA, tex_lado=VETEADA)
escalon("escalera_baxter2", 2304, -2048, 3840, -1280, 250, color=HUESO, tex_tapa=VETEADA, tex_lado=VETEADA)
edificio("asta_bandera", 1280, -1536, 1536, -1280, 1600, color=HOLLIN, tex_tapa=ORO, tex_lado=LISA, paso_lado=1024)

# ================================================================== Main Street: faroles y tiendas (lado sur)
for i, x in enumerate((-3328, 768, 7424)):
    farol(f"farol_n{i + 1}", x, -768)
for i, x in enumerate((-1280, 3840, 8448)):
    farol(f"farol_s{i + 1}", x, 1024)
edificio("cerberus_books", -3840, 1280, -2560, 2304, 800, color=MADERA_VIEJA, tex_tapa=PIEDRA, tex_lado=PANELES)
tejado("cerberus_letrero", -3840, 1024, -2560, 1280, 650, 150, color=MADERA_VIEJA, tex_tapa=LETRERO, tex_lado=LETRERO)
edificio("diner_cerberus", -2304, 1280, -1024, 2304, 700, color=TURQUESA_APAGADO, tex_tapa=PIEDRA, tex_lado=AZULEJO)
edificio("cine_paramount", -768, 1280, 1024, 2304, 1200, color=MARMOL_SUCIO, tex_tapa=PIEDRA, tex_lado=MARMOL)
tejado("marquesina", -768, 1024, 1024, 1280, 700, 250, color=HUESO, tex_tapa=LETRERO2, tex_lado=LETRERO2)
edificio("farmacia", 1280, 1280, 2304, 2304, 700, color=LADRILLO_SUCIO, tex_tapa=PIEDRA, tex_lado=LADRILLO)
edificio("ayuntamiento", 2560, 1280, 4864, 2560, 1000, color=PIEDRA_FRIA, tex_tapa=PIEDRA, tex_lado=VETEADA,
         paso_lado=1024)
edificio("torre_reloj", 3328, 1536, 4096, 2304, 1000, base=1000, color=PIEDRA_FRIA, tex_tapa=PIEDRA,
         tex_lado=VETEADA)
edificio("reloj", 3584, 1280, 3840, 1536, 300, base=1500, color=HUESO, tex_tapa=GLIFO, tex_lado=GLIFO, paso_lado=1024)

# ================================================================== la Academia de Artes Ocultas (noreste)
edificio("academia", 7168, -4608, 9472, -1536, 1400, color=PIEDRA_FRIA, tex_tapa=PIEDRA, tex_lado=VETEADA,
         paso_lado=1024)
edificio("torre_academia_o", 7168, -1536, 7680, -1024, 2400, color=PIEDRA_FRIA, tex_tapa=PIEDRA, tex_lado=VETEADA,
         paso_lado=1024)
edificio("torre_academia_e", 8960, -1536, 9472, -1024, 2400, color=PIEDRA_FRIA, tex_tapa=PIEDRA, tex_lado=VETEADA,
         paso_lado=1024)
tejado("portal_academia", 7936, -1536, 8704, -1024, 900, 200, color=HOLLIN, tex_tapa=ARCO, tex_lado=ARCO)
escalon("escalera_academia", 7680, -1280, 8960, -1024, 200, color=PIEDRA_FRIA)

# ================================================================== la Iglesia de la Noche y el campanario (sureste)
edificio("iglesia", 7168, 1280, 9472, 3328, 1200, color=HOLLIN, tex_tapa=TEJAS, tex_lado=VETEADA, paso_lado=1024)
edificio("campanario", 7936, 3584, 8704, 4352, 2500, color=HOLLIN, tex_tapa=OXIDO, tex_lado=VETEADA)
# la escalera que rodea el campanario: 10 peldanos de 250 hasta la campana (la meta)
peldanos = ((7168, 3584, 7680, 4096), (7168, 4096, 7680, 4608), (7168, 4608, 7680, 5120), (7680, 4608, 8192, 5120),
            (8192, 4608, 8704, 5120), (8704, 4608, 9216, 5120), (8704, 4096, 9216, 4608), (8704, 3584, 9216, 4096),
            (8704, 3072, 9216, 3584), (8192, 3072, 8704, 3584))
for i, (x0, z0, x1, z1) in enumerate(peldanos):
    escalon(f"peldano{i + 1}", x0, z0, x1, z1, 250 * (i + 1), color=HOLLIN, tex_tapa=LISA, tex_lado=VETEADA,
            prof=250, techo=i > 0)
escalon("campana", 8192, 3584, 8448, 3840, 2750, color=(140, 120, 70), tex_tapa=ORO, tex_lado=ORO, paso_lado=1024,
        prof=250)

# ================================================================== el bosque de Greendale, el rio y la mina
for i, (x, z, copa) in enumerate(((-3584, 3072, True), (-2560, 3584, False), (-1536, 3072, True), (-512, 3584, False),
                                  (512, 3072, False), (1536, 3584, True), (2560, 3072, False), (3584, 3584, True),
                                  (4352, 3072, False), (-3584, 5120, False), (-1536, 5376, False), (3584, 5120, False))):
    arbol(f"arbol{i + 1}", x, z, 1100 if copa else 900 + 200 * (i % 3), copa)
bloques.append(n.nueva("puente", 256, 4096, 1280, 4608, 0, color=MADERA_VIEJA, tex_tapa=TABLONES, tex_lado=TABLONES,
                       prof=100, paso=512, pared=True))
edificio("colina_mina", -1024, 5376, 3072, 5632, 1500, color=HOLLIN, tex_tapa=PIEDRA, tex_lado=PIEDRA, extra=ISLA,
         paso_lado=1024)
edificio("mina_pilar_o", 512, 4864, 768, 5376, 700, color=ROJO_OXIDO, tex_tapa=OXIDO, tex_lado=TELA_ROJA, paso_lado=256)
edificio("mina_pilar_e", 1792, 4864, 2048, 5376, 700, color=ROJO_OXIDO, tex_tapa=OXIDO, tex_lado=TELA_ROJA, paso_lado=256)
tejado("mina_dintel", 512, 4864, 2048, 5376, 700, 250, color=ROJO_OXIDO, tex_tapa=OXIDO, tex_lado=TELA_ROJA)

cielo = dict(cenit=[78, 82, 92], horizonte=[138, 138, 142], nadir=[62, 64, 70])     # niebla cerrada

if __name__ == "__main__":
    errores, avisos = n.validar(bloques)
    print(len(bloques), "bloques; errores:", errores)
    for a in avisos:
        print("aviso:", a)
    tam, maximo = n.tamano_ino(bloques, cielo)
    print(f"tamano del .INO: {tam} de {maximo} bytes ({100 * tam / maximo:.1f} %)")
    if not errores and tam <= maximo:
        ruta = os.path.join(n.NIVELES, "greendale.json")
        n.guardar(bloques, ruta, cielo)
        print("escrito", ruta)
