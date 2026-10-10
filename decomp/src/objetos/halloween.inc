/* MOD: SABRINA, NOCHE DE BRUJAS EN EL CASTILLO. Se incluye en camara_g08.c solo con -DSABRINA_HALLOWEEN.
 *
 * Un especial de Halloween sobre el juego tal cual: Sabrina camina, corre y salta con su propio codigo y la camara
 * es la del juego. Desde la camara (corre en cada paso) se lleva todo lo demas: las cuatro zonas del castillo
 * (mapa_halloween.py, halloween_mapa.h), las calabazas que se juntan y el portal que se abre al tenerlas todas, las
 * manzanas encantadas que curan, los monstruos (fantasmas que persiguen, murcielagos que bajan en picada, calabazas
 * saltarinas y el Rey Calabaza con sus bolas de fuego), el cristal magico que lanza Sabrina con cuadrado, los golpes
 * (como los de un enemigo del juego: empujon, quejido, animacion de dolor y un rato sin que vuelva a doler), la luna,
 * el texto y la fiesta del final. Los monstruos y objetos son nodos de modelo (halloween_modelos.py) colgados de los
 * de los objetos y puestos cada paso con MatrizDesdeAngulos, como el rival del kart. */

#include "halloween_mapa.h"

extern s16 D_8007CB70;               /* la animacion que debe tener el companero */
extern Objeto *D_8007CB8C;           /* el companero: la mitad de arriba de Sabrina */
extern void ImprimirDepuracion(const char *formato, ...);
extern s32 rsin(s32 angulo);
extern s32 rcos(s32 angulo);
extern volatile s32 D_800649EC;      /* cuantas vueltas de la pantalla van (VSync) */
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern s8 vida_barra;
extern void ActualizarBarraVida(void);
extern void func_800300C4(s32 mucho);    /* cura 4 puntos (20 con mucho) y redibuja la barra */
extern s32 func_80031000(void);          /* la animacion de dolor y el rato sin que vuelva a doler */

#define H_CUADRADO 0x80
#define H_X 0x40
#define H_SELECT 0x100
#define H_SEG 28                     /* pasos del juego por segundo (medido en el kart) */
#define H_VBL 60
#define H_LEJOS 6000                 /* altura (hacia abajo) donde se esconde un nodo que no se usa */
#define H_VIDA 20                    /* la vida llena del juego (func_800300C4 no pasa de 20) */

/* modelos_cargados va uno corrido: el modelo n de la lista del .INO es el n + 1 */
#define H_M_FANTASMA 14
#define H_M_MURCIELAGO 15
#define H_M_CALABAZA 16
#define H_M_MANZANA 17
#define H_M_REY 18
#define H_M_PORTAL 19
#define H_M_CRISTAL 21
#define H_M_FUEGO 22
#define H_M_LUNA 23

#define H_POSE_SALUDA 0x0C
#define H_POSE_MAGIA 0x0E
#define H_POSE_ARRIBA 0x16

enum { H_EMPEZAR, H_TITULO, H_JUEGO, H_FIN };

/* un monstruo: donde esta (y hacia abajo), su casa, si vive, su reloj (para volver a salir o para sus ataques) y la
 * pausa despues de pegar (se aparta un rato en vez de quedarse encima de Sabrina) */
typedef struct {
    s32 x, y, z, cx, cy, cz, t, vivo;
    void *nodo;
    s32 pausa;
} HBicho;

static s32 h_fase, h_zona, h_pasos, h_tiempo, h_vbl, h_avisos_t, h_juntadas, h_derrotados, h_portal;
static const char *h_aviso;
static HBicho h_fan[HW_MAX_FANTASMAS], h_mur[HW_MAX_MURCIELAGOS], h_sal[HW_MAX_SALTARINAS], h_rey, h_fuego[3];
static void *h_cal_nodo[HW_MAX_CALABAZAS], *h_man_nodo[HW_MAX_MANZANAS], *h_portal_nodo, *h_luna_nodo;
static void *h_cristal_nodo, *h_chispa_nodo[3];
static u8 h_tomada[HW_MAX_CALABAZAS];
static s16 h_man_t[HW_MAX_MANZANAS];            /* pasos para que vuelva a salir una manzana comida */
static s32 h_zap_t, h_zap_x, h_zap_y, h_zap_z, h_zap_dir, h_boom_t, h_boom_x, h_boom_y, h_boom_z, h_rey_vida;

static const char *const h_nombre_zona[HW_ZONAS] = {
    "EL CEMENTERIO DE GREENDALE", "EL GRAN SALON DEL CASTILLO", "LA TORRE EMBRUJADA", "LA MAZMORRA DEL REY CALABAZA"};

static void h_avisar(const char *texto, s32 pasos) {
    h_aviso = texto;
    h_avisos_t = pasos;
}

/* Un nodo nuevo del modelo m (NULL si el nivel no lo cargo). */
static void *h_nodo(s32 m) {
    return modelos_cargados[m] != NULL ? func_8001E06C(modelos_cargados[m], D_8007C9F0) : NULL;
}

/* Pone un nodo en (x, y, z) del mundo (y hacia abajo) girado ry, con escala ex a lo ancho, ey a lo alto y ez a lo
 * largo (0x1000 = 1). */
static void __attribute__((noinline)) h_colocar(void *nodo, s32 x, s32 y, s32 z, s32 ry, s32 ex, s32 ey, s32 ez) {
    s32 e[3], p[3], g[3];

    if (nodo == NULL) {
        return;
    }
    e[0] = ex;
    e[1] = ey;
    e[2] = ez;
    p[0] = x << 8;
    p[1] = y << 8;
    p[2] = z << 8;
    g[0] = 0;
    g[1] = ry & 0xFFF;
    g[2] = 0;
    MatrizDesdeAngulos(nodo, e, p, g);
}

static void h_esconder(void *nodo) {
    h_colocar(nodo, 0, H_LEJOS, 0, 0, 0x1000, 0x1000, 0x1000);
}

/* Si (x, y, z) esta cerca de Sabrina: a menos de r en el plano y de 400 en altura. */
static s32 __attribute__((noinline)) h_toca(Objeto *s, s32 x, s32 y, s32 z, s32 r) {
    s32 dx = (s->x >> 8) - x, dz = (s->z >> 8) - z, dy = (s->y >> 8) - y;

    return dx < r && -dx < r && dz < r && -dz < r && dy < 400 && -dy < 400;
}

/* La pose de la mitad de arriba de Sabrina, como hace el juego al cambiarse de ropa. */
static void h_pose(s32 k) {
    EstadoAnim *a = D_8007CB8C->anim;

    a->animacion = D_8007CB8C->animaciones[k];
    a->_50 = 0;
    a->_4E = 0x800;
    D_8007CB70 = k;
}

/* Lleva a Sabrina (y la camara) a la salida de la zona z y deja la zona como nueva. */
static void __attribute__((noinline)) h_entrar(Objeto *o, Objeto *s, s32 z) {
    s32 i;
    const s16 *q;

    h_zona = z;
    s->x = hw_salida[z][0] << 8;
    s->z = hw_salida[z][1] << 8;
    s->y = -64 << 8;
    s->empuje_x = 0;
    s->empuje_z = 0;
    s->vel_y = 0;
    s->rot[1] = hw_salida[z][2];
    h_juntadas = 0;
    h_portal = hw_n_calabazas[z] == 0 ? -1 : 0;   /* la mazmorra no tiene portal: tiene jefe */
    for (i = 0; i < HW_MAX_CALABAZAS; i++) {
        h_tomada[i] = i >= hw_n_calabazas[z];
    }
    for (i = 0; i < HW_MAX_MANZANAS; i++) {
        h_man_t[i] = i < hw_n_manzanas[z] ? 0 : 0x7FFF;
    }
    for (i = 0; i < HW_MAX_FANTASMAS; i++) {
        q = hw_fantasmas[z][i];
        h_fan[i].x = h_fan[i].cx = q[0];
        h_fan[i].y = h_fan[i].cy = q[1];
        h_fan[i].z = h_fan[i].cz = q[2];
        h_fan[i].vivo = i < hw_n_fantasmas[z];
        h_fan[i].t = i * 40;
    }
    for (i = 0; i < HW_MAX_MURCIELAGOS; i++) {
        q = hw_murcielagos[z][i];
        h_mur[i].x = h_mur[i].cx = q[0];
        h_mur[i].y = h_mur[i].cy = q[1];
        h_mur[i].z = h_mur[i].cz = q[2];
        h_mur[i].vivo = i < hw_n_murcielagos[z];
        h_mur[i].t = i * 300;
    }
    for (i = 0; i < HW_MAX_SALTARINAS; i++) {
        q = hw_saltarinas[z][i];
        h_sal[i].x = h_sal[i].cx = q[0];
        h_sal[i].y = h_sal[i].cy = q[1];
        h_sal[i].z = h_sal[i].cz = q[2];
        h_sal[i].vivo = i < hw_n_saltarinas[z];
        h_sal[i].t = i * 17;
    }
    h_rey.vivo = z == HW_ZONAS - 1;
    h_rey.x = h_rey.cx = HW_JEFE_X;
    h_rey.z = h_rey.cz = HW_JEFE_Z;
    h_rey.y = h_rey.cy = 0;
    h_rey.t = 0;
    h_rey_vida = 8;
    for (i = 0; i < 3; i++) {
        h_fuego[i].vivo = 0;
    }
    h_zap_t = 0;
    s->vida = H_VIDA;
    s->extra.espera_golpe = 2 * H_SEG;   /* recien llegada, dos segundos sin que le duela nada */
    vida_barra = H_VIDA;
    ActualizarBarraVida();
    o->estado = 0;
    func_80037278(o, s);             /* la camara, ya asentada detras de Sabrina */
    h_avisar(h_nombre_zona[z], 3 * H_SEG);
    TocarSonido(1, 0, 0x30, 0x7F);
}

/* Un golpe de un monstruo que esta en (x, z): como DanoPorEnemigo (empujon hacia atras, quejido, 4 de vida y un rato
 * sin que vuelva a doler). Sin vida, Sabrina vuelve a empezar la zona. */
static void __attribute__((noinline)) h_golpe(Objeto *o, Objeto *s, s32 x, s32 z) {
    if (s->extra.espera_golpe > 0 || h_fase != H_JUEGO) {
        return;
    }
    s->empuje_x += ((s->x >> 8) - x) << 6;
    s->empuje_z += ((s->z >> 8) - z) << 6;
    s->vel_y = -0x1000;
    TocarSonido((h_pasos & 1) ? 7 : 8, 0, 0x2A, 0x7F);
    s->vida -= 4;
    if (s->vida <= 0) {
        h_entrar(o, s, h_zona);
        h_avisar("LOS MONSTRUOS TE ATRAPARON... OTRA VEZ!", 3 * H_SEG);
        return;
    }
    vida_barra = s->vida;
    ActualizarBarraVida();
    func_80031000();
}

/* El cristal de Sabrina le pega a algo en (x, y, z) si esta a menos de r. */
static s32 h_pega(s32 x, s32 y, s32 z, s32 r) {
    s32 dx = h_zap_x - x, dz = h_zap_z - z, dy = h_zap_y - y;

    return h_zap_t > 0 && dx < r && -dx < r && dz < r && -dz < r && dy < r + 200 && -dy < r + 200;
}

static void h_explotar(s32 x, s32 y, s32 z) {
    h_boom_t = 12;
    h_boom_x = x;
    h_boom_y = y;
    h_boom_z = z;
    h_zap_t = 0;
    TocarSonido(1, 0, 0x24, 0x7F);
}

/* Un monstruo que el cristal acaba de deshacer: explota y vuelve a salir de su casa a los 12 segundos. */
static s32 h_deshacer(HBicho *b) {
    if (!b->vivo || !h_pega(b->x, b->y - 150, b->z, 260)) {
        return 0;
    }
    h_explotar(b->x, b->y - 150, b->z);
    b->vivo = 0;
    b->t = 12 * H_SEG;
    h_derrotados++;
    return 1;
}

static void h_revivir(HBicho *b) {
    if (!b->vivo && b->t > 0 && --b->t == 0) {
        b->vivo = 1;
        b->x = b->cx;
        b->y = b->cy;
        b->z = b->cz;
    }
}

/* Si el monstruo puede ir a por Sabrina este paso: solo jugando y fuera de la pausa que se toma despues de pegar. */
static s32 h_caza(HBicho *b) {
    if (b->pausa > 0) {
        b->pausa--;
        return 0;
    }
    return h_fase == H_JUEGO;
}

/* Mueve b hacia (x, z) a lo sumo v por paso y devuelve hacia donde mira. */
static s32 __attribute__((noinline)) h_ir(HBicho *b, s32 x, s32 z, s32 v) {
    s32 dx = x - b->x, dz = z - b->z, d = (dx < 0 ? -dx : dx) + (dz < 0 ? -dz : dz);

    if (d > v) {
        b->x += dx * v / d;
        b->z += dz * v / d;
    }
    return func_8001BE8C(0, 0, dx, dz);
}

/* Los monstruos de la zona: los fantasmas flotan y persiguen a Sabrina si esta cerca (si no, vuelven a su tumba); los
 * murcielagos dan vueltas y bajan en picada; las calabazas saltarinas saltan hacia ella. */
static void __attribute__((noinline)) h_fantasmas(Objeto *o, Objeto *s) {
    s32 i, a, sx = s->x >> 8, sz = s->z >> 8;
    HBicho *b;

    for (i = 0; i < HW_MAX_FANTASMAS; i++) {
        b = &h_fan[i];
        if (b->nodo == NULL) {
            b->nodo = h_nodo(H_M_FANTASMA);
        }
        h_revivir(b);
        if (!b->vivo || h_deshacer(b)) {
            h_esconder(b->nodo);
            continue;
        }
        b->t++;
        if (h_caza(b) && h_toca(s, b->cx, s->y >> 8, b->cz, 2200)) {
            a = h_ir(b, sx, sz, 13);
        } else {
            a = h_ir(b, b->cx, b->cz, 12);
        }
        b->y = b->cy - 40 - ((rsin(b->t * 90) * 60) >> 12);
        h_colocar(b->nodo, b->x, b->y, b->z, a, 0x1000, 0x1000, 0x1000);
        if (h_toca(s, b->x, b->y, b->z, 190) && b->pausa == 0) {
            h_golpe(o, s, b->x, b->z);
            b->pausa = 2 * H_SEG;
        }
    }
}

static void __attribute__((noinline)) h_murcielagos(Objeto *o, Objeto *s) {
    s32 i, a, sx = s->x >> 8, sy = s->y >> 8, sz = s->z >> 8;
    HBicho *b;

    for (i = 0; i < HW_MAX_MURCIELAGOS; i++) {
        b = &h_mur[i];
        if (b->nodo == NULL) {
            b->nodo = h_nodo(H_M_MURCIELAGO);
        }
        h_revivir(b);
        if (!b->vivo || h_deshacer(b)) {
            h_esconder(b->nodo);
            continue;
        }
        b->t++;
        if (h_caza(b) && h_toca(s, b->cx, sy, b->cz, 1500) && (b->t & 127) < 64) {
            a = h_ir(b, sx, sz, 34);                     /* en picada, a la cabeza */
            b->y += ((sy - 260) - b->y) / 6;
        } else {
            a = b->t * 50;
            h_ir(b, b->cx + ((rsin(a) * 450) >> 12), b->cz + ((rcos(a) * 450) >> 12), 30);
            a += 0x400;
            b->y += (b->cy - b->y) / 8;
        }
        h_colocar(b->nodo, b->x, b->y, b->z, a, 0x1000 + ((rsin(b->t * 600) * 0x700) >> 12), 0x1000, 0x1000);
        if (h_toca(s, b->x, b->y + 250, b->z, 170) && b->pausa == 0) {
            h_golpe(o, s, b->x, b->z);
            b->pausa = 3 * H_SEG;
        }
    }
}

static void __attribute__((noinline)) h_saltarinas(Objeto *o, Objeto *s) {
    s32 i, a, c, sx = s->x >> 8, sy = s->y >> 8, sz = s->z >> 8;
    HBicho *b;

    for (i = 0; i < HW_MAX_SALTARINAS; i++) {
        b = &h_sal[i];
        if (b->nodo == NULL) {
            b->nodo = h_nodo(H_M_CALABAZA);
        }
        h_revivir(b);
        if (!b->vivo || h_deshacer(b)) {
            h_esconder(b->nodo);
            continue;
        }
        b->t++;
        c = h_caza(b) && h_toca(s, b->cx, sy, b->cz, 2600);
        h_ir(b, c ? sx : b->cx, c ? sz : b->cz, 18);
        a = (rsin(b->t * 130) * 230) >> 12;
        b->y = b->cy - (a < 0 ? -a : a);
        h_colocar(b->nodo, b->x, b->y, b->z, func_8001BE8C(b->x, b->z, sx, sz), 0x1800, 0x1800, 0x1800);
        if (h_toca(s, b->x, b->y, b->z, 220) && b->pausa == 0) {
            h_golpe(o, s, b->x, b->z);
            b->pausa = 2 * H_SEG;
        }
    }
}

/* El Rey Calabaza: da vueltas por la mazmorra mirando a Sabrina, cada 2.5 segundos le tira una bola de fuego que la
 * persigue (con la mitad de la vida, dos y mas rapido). Ocho cristales lo deshacen. */
static void __attribute__((noinline)) h_jefe(Objeto *o, Objeto *s) {
    s32 i, a, v, sx = s->x >> 8, sy = s->y >> 8, sz = s->z >> 8;
    HBicho *f;

    if (h_rey.nodo == NULL) {
        h_rey.nodo = h_nodo(H_M_REY);
        for (i = 0; i < 3; i++) {
            h_fuego[i].nodo = h_nodo(H_M_FUEGO);
        }
    }
    if (h_rey.vivo && h_fase == H_JUEGO) {
        h_rey.t++;
        v = h_rey_vida <= 4 ? 14 : 9;
        a = h_rey.t * v;
        h_ir(&h_rey, h_rey.cx + ((rsin(a) * 1250) >> 12), h_rey.cz + ((rcos(a * 2) * 900) >> 12), 40);
        h_rey.y = -180 - ((rsin(h_rey.t * 70) * 90) >> 12);
        if (h_pega(h_rey.x, h_rey.y - 350, h_rey.z, 420)) {
            h_explotar(h_zap_x, h_zap_y, h_zap_z);
            h_avisar(--h_rey_vida > 4 ? "  JA JA JA! ESO NO DUELE!" : "    GRRR! ME LAS PAGARAS!", H_SEG);
            if (h_rey_vida <= 0) {
                h_rey.vivo = 0;
                h_derrotados++;
                h_fase = H_FIN;
                h_pasos = 0;
                h_explotar(h_rey.x, h_rey.y - 350, h_rey.z);
            }
        }
        i = (h_rey.t % (H_SEG * 5 / 2) == 0) ? 0 : 3;
        for (; i < (h_rey_vida <= 4 ? 2 : 1); i++) {
            h_fuego[i].vivo = 5 * H_SEG;
            h_fuego[i].x = h_rey.x;
            h_fuego[i].z = h_rey.z;
            h_fuego[i].y = h_rey.y - 300;
        }
        /* chocarse con el */
        if (h_toca(s, h_rey.x, h_rey.y, h_rey.z, 380)) {
            h_golpe(o, s, h_rey.x, h_rey.z);
        }
    }
    a = h_rey_vida <= 4 && (h_pasos & 2) ? 0x1300 : 0x1000;     /* con poca vida palpita */
    if (h_rey.vivo) {
        h_colocar(h_rey.nodo, h_rey.x, h_rey.y, h_rey.z, func_8001BE8C(h_rey.x, h_rey.z, sx, sz), a, a, a);
    } else {
        h_esconder(h_rey.nodo);
    }
    for (i = 0; i < 3; i++) {
        f = &h_fuego[i];
        if (f->vivo > 0 && h_fase == H_JUEGO) {
            f->vivo--;
            h_ir(f, sx, sz, h_rey_vida <= 4 ? 44 : 34);
            f->y += ((sy - 200) - f->y) / 10;
            if (h_toca(s, f->x, f->y + 200, f->z, 200)) {
                f->vivo = 0;
                h_golpe(o, s, f->x, f->z);
            }
            h_colocar(f->nodo, f->x, f->y, f->z, h_pasos * 200, 0x1000, 0x1000, 0x1000);
        } else {
            h_esconder(f->nodo);
        }
    }
}

/* Las calabazas (que dan vueltas y flotan; al juntarlas todas se abre el portal), las manzanas encantadas (curan;
 * salen otra vez a los 20 segundos) y el portal con la luna. */
static void __attribute__((noinline)) h_calabazas(Objeto *s) {
    s32 i, a, n = hw_n_calabazas[h_zona];
    const s16 *q;

    for (i = 0; i < HW_MAX_CALABAZAS; i++) {
        if (h_cal_nodo[i] == NULL) {
            h_cal_nodo[i] = h_nodo(H_M_CALABAZA);
        }
        q = hw_calabazas[h_zona][i];
        if (h_tomada[i]) {
            /* en la fiesta del final llueven calabazas alrededor de Sabrina */
            if (h_fase == H_FIN) {
                a = i * 683 + h_pasos * 30;
                h_colocar(h_cal_nodo[i], (s->x >> 8) + ((rsin(a) * 700) >> 12),
                          -1200 + ((h_pasos * 45 + i * 300) % 1200), (s->z >> 8) + ((rcos(a) * 700) >> 12), a,
                          0x1000, 0x1000, 0x1000);
            } else {
                h_esconder(h_cal_nodo[i]);
            }
            continue;
        }
        h_colocar(h_cal_nodo[i], q[0], q[1] - 30 - ((rsin(h_pasos * 80 + i * 500) * 30) >> 12), q[2],
                  h_pasos * 40 + i * 300, 0x1000, 0x1000, 0x1000);
        if (h_toca(s, q[0], q[1], q[2], 230)) {
            h_tomada[i] = 1;
            h_juntadas++;
            h_explotar(q[0], q[1] - 120, q[2]);
            TocarSonido(1, 0, 0x3C, 0x7F);
            if (h_juntadas == n) {
                h_portal = 1;
                h_avisar("TODAS! EL PORTAL SE ABRIO!", 3 * H_SEG);
            } else {
                h_avisar("     UNA CALABAZA!", H_SEG);
            }
        }
    }
}

static void __attribute__((noinline)) h_manzanas(Objeto *s) {
    s32 i;
    const s16 *q;

    for (i = 0; i < HW_MAX_MANZANAS; i++) {
        if (h_man_nodo[i] == NULL) {
            h_man_nodo[i] = h_nodo(H_M_MANZANA);
        }
        q = hw_manzanas[h_zona][i];
        if (h_man_t[i] > 0) {
            if (h_man_t[i] != 0x7FFF) {
                h_man_t[i]--;
            }
            h_esconder(h_man_nodo[i]);
            continue;
        }
        h_colocar(h_man_nodo[i], q[0], q[1] - 20 - ((rsin(h_pasos * 70 + i * 900) * 25) >> 12), q[2],
                  h_pasos * 30, 0x1000, 0x1000, 0x1000);
        if (s->vida < H_VIDA && h_toca(s, q[0], q[1], q[2], 220)) {
            func_800300C4(0);
            h_man_t[i] = 20 * H_SEG;
            h_avisar("MANZANA ENCANTADA: +VIDA", H_SEG);
            TocarSonido(1, 0, 0x48, 0x7F);
        }
    }
}

static void __attribute__((noinline)) h_portal_luna(Objeto *o, Objeto *s) {
    s32 a;
    const s16 *q;

    if (h_portal_nodo == NULL) {
        h_portal_nodo = h_nodo(H_M_PORTAL);
        h_luna_nodo = h_nodo(H_M_LUNA);
    }
    q = hw_portal[h_zona];
    if (h_portal > 0) {
        a = 0x1000 + ((rsin(h_pasos * 120) * 0x200) >> 12);
        h_colocar(h_portal_nodo, q[0], q[1], q[2], h_pasos * 60, a, a, a);
        if (h_toca(s, q[0], q[1], q[2], 300)) {
            h_entrar(o, s, h_zona + 1);
        }
    } else {
        h_esconder(h_portal_nodo);
    }
    /* la luna llena, siempre al norte, dentro de la cupula del cielo (que va con Sabrina) */
    h_colocar(h_luna_nodo, (s->x >> 8) + 1800, -3300, (s->z >> 8) - 5400, func_8001BE8C(1800, -5400, 0, 0), 0x1000,
              0x1000, 0x1000);
}

/* El cristal magico: sale de Sabrina hacia donde mira, vuela un segundo y, al pegar, salta en chispas. */
static void __attribute__((noinline)) h_cristales(Objeto *s, u32 nuevo) {
    s32 i, a, d;

    if (h_cristal_nodo == NULL) {
        h_cristal_nodo = h_nodo(H_M_CRISTAL);
        for (i = 0; i < 3; i++) {
            h_chispa_nodo[i] = h_nodo(H_M_CRISTAL);
        }
    }
    if ((nuevo & H_CUADRADO) && h_zap_t <= 4 && h_fase == H_JUEGO) {
        h_zap_t = H_SEG;
        h_zap_dir = s->rot[1];
        h_zap_x = (s->x >> 8) + ((rsin(h_zap_dir) * 150) >> 12);
        h_zap_z = (s->z >> 8) + ((rcos(h_zap_dir) * 150) >> 12);
        h_zap_y = (s->y >> 8) - 30;
        h_pose(H_POSE_MAGIA);
        TocarSonido(1, 0, 0x4C, 0x7F);
    }
    if (h_zap_t > 0) {
        h_zap_t--;
        h_zap_x += (rsin(h_zap_dir) * 120) >> 12;
        h_zap_z += (rcos(h_zap_dir) * 120) >> 12;
        h_colocar(h_cristal_nodo, h_zap_x, h_zap_y, h_zap_z, h_pasos * 300, 0x1000, 0x1000, 0x1000);
    } else {
        h_esconder(h_cristal_nodo);
    }
    for (i = 0; i < 3; i++) {
        a = i * 1365 + h_pasos * 90;
        if (h_boom_t > 0) {
            d = (13 - h_boom_t) * 60;
            h_colocar(h_chispa_nodo[i], h_boom_x + ((rsin(a) * d) >> 12), h_boom_y - d / 2,
                      h_boom_z + ((rcos(a) * d) >> 12), a * 3, 0x1000, 0x1000, 0x1000);
        } else {
            h_esconder(h_chispa_nodo[i]);
        }
    }
    if (h_boom_t > 0) {
        h_boom_t--;
    }
}

static void h_imprimir_tiempo(const char *texto, s32 f) {
    s32 m = f / (60 * H_VBL), sg = (f / H_VBL) % 60;

    ImprimirDepuracion("%s%d:%d%d", texto, m, sg / 10, sg % 10);
}

/* El texto de arriba: la zona, las calabazas, los monstruos deshechos y el tiempo; la vida del jefe; los avisos. */
static void __attribute__((noinline)) h_pantalla(void) {
    s32 i;

    if (h_fase == H_TITULO) {
        ImprimirDepuracion("\n\n\n\n          * * *  SABRINA  * * *\n\n          NOCHE DE BRUJAS EN EL CASTILLO\n\n\n"
                           "   JUNTA LAS CALABAZAS DE CADA ZONA PARA ABRIR EL PORTAL\n   CUADRADO: CRISTAL MAGICO CONTRA LOS MONSTRUOS\n"
                           "   LAS MANZANAS ENCANTADAS CURAN\n\n%s", (h_pasos & 16) ? "             PULSA X PARA EMPEZAR\n" : "\n");
        return;
    }
    if (h_fase == H_FIN) {
        ImprimirDepuracion("\n   * * *  FELIZ HALLOWEEN, SABRINA!  * * *\n\n   DESHICISTE AL REY CALABAZA Y A %d MONSTRUOS\n",
                           h_derrotados);
        h_imprimir_tiempo("   EN ", h_tiempo);
        if (h_pasos > 3 * H_SEG) {
            ImprimirDepuracion("\n\n\n\n\n\n\n\n\n\n          X O SELECT: OTRA NOCHE DE BRUJAS\n");
        }
        return;
    }
    ImprimirDepuracion("\n  NOCHE DE BRUJAS  %d. %s\n", h_zona + 1, h_nombre_zona[h_zona]);
    if (hw_n_calabazas[h_zona] > 0) {
        ImprimirDepuracion("  CALABAZAS %d/%d", h_juntadas, hw_n_calabazas[h_zona]);
    } else if (h_rey.vivo) {
        ImprimirDepuracion("  REY CALABAZA ");
        for (i = 0; i < 8; i++) {
            ImprimirDepuracion(i < h_rey_vida ? "#" : "-");
        }
    }
    ImprimirDepuracion("   MONSTRUOS %d", h_derrotados);
    h_imprimir_tiempo("   ", h_tiempo);
    ImprimirDepuracion("\n  CUADRADO: CRISTAL MAGICO\n");
    if (h_avisos_t > 0) {
        ImprimirDepuracion("\n\n\n          %s\n", h_aviso);
    }
}

/* La fiesta del final: Sabrina saluda, levanta los brazos y lanza magia mientras llueven calabazas. */
static void __attribute__((noinline)) h_fiesta(void) {
    static const u8 poses[4] = {H_POSE_ARRIBA, H_POSE_SALUDA, H_POSE_ARRIBA, H_POSE_MAGIA};

    if (h_pasos % (H_SEG + H_SEG / 3) == 1) {
        h_pose(poses[(h_pasos / (H_SEG + H_SEG / 3)) & 3]);
        TocarSonido(1, 0, 0x3C + ((h_pasos / H_SEG) & 3) * 4, 0x7F);
    }
    for (h_juntadas = 0; h_juntadas < HW_MAX_CALABAZAS; h_juntadas++) {
        h_tomada[h_juntadas] = 1;
    }
}

static void __attribute__((noinline)) hw_paso(Objeto *o) {
    Objeto *s = p_sabrina;
    u32 nuevo = D_8007CA58;
    s32 dv;

    if (s == NULL) {
        return;
    }
    /* el cuadrado es del cristal magico y SELECT empieza otra noche (en este C SELECT prende la camara libre): a
     * Sabrina y a la camara no les llegan */
    D_8007CA50 &= ~(H_CUADRADO | H_SELECT);
    D_8007CA54 &= ~(H_CUADRADO | H_SELECT);
    D_8007CA58 &= ~(H_CUADRADO | H_SELECT);
    if (h_fase == H_EMPEZAR) {
        /* la portada: Sabrina en el cementerio, los monstruos quietos, hasta que se pulse X */
        h_fase = H_TITULO;
        h_tiempo = 0;
        h_derrotados = 0;
        h_entrar(o, s, 0);
    }
    if ((h_fase == H_TITULO && (nuevo & H_X)) || (nuevo & H_SELECT) ||
        (h_fase == H_FIN && h_pasos > 3 * H_SEG && (nuevo & H_X))) {
        if (h_fase != H_TITULO) {
            h_entrar(o, s, 0);
        }
        h_fase = H_JUEGO;
        h_tiempo = 0;
        h_derrotados = 0;
        h_pasos = 0;
        h_avisar("JUNTA LAS CALABAZAS Y CUIDADO CON LOS FANTASMAS!", 3 * H_SEG);
        D_8007CA50 &= ~H_X;
        D_8007CA58 &= ~H_X;
    }
    h_pasos++;
    if (h_avisos_t > 0) {
        h_avisos_t--;
    }
    if (h_fase == H_JUEGO) {
        dv = D_800649EC - h_vbl;
        h_tiempo += dv > 0 && dv <= 6 ? dv : 2;
    }
    h_vbl = D_800649EC;
    h_cristales(s, nuevo);
    h_fantasmas(o, s);
    h_murcielagos(o, s);
    h_saltarinas(o, s);
    h_jefe(o, s);
    h_calabazas(s);
    h_manzanas(s);
    h_portal_luna(o, s);
    if (h_fase == H_FIN) {
        h_fiesta();
    }
    h_pantalla();
}
