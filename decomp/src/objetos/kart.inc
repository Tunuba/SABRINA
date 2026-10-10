/* MOD: SABRINA KART. Se incluye en camara_g08.c solo con -DSABRINA_KART (armar_c.py --D SABRINA_KART).
 *
 * La camara corre en cada paso del juego, asi que desde aqui se maneja todo el modo carrera: lee el mando y se lo
 * quita a Sabrina (para el resto del juego queda quieta), la mueve como un kart con su propio empuje (la fisica
 * del juego sigue chocando con las paredes y apoyandola en el suelo), pone la camara detras y lleva la carrera
 * (cuenta atras, puntos de control, vueltas, tiempos, turbos y cajas de hechizo). El texto sale con la fuente de
 * depuracion del juego (ImprimirDepuracion es su FntPrint; la pantalla la vacia en cada cuadro).
 *
 * Mando: el kart acelera solo; izquierda y derecha giran y con eso basta para correr. Sin saltos. Aparte, cuadrado o
 * abajo frena, circulo o R1 mantenido en una curva derrapa (al soltarlo: mini turbo azul o naranja segun cuanto
 * duro), triangulo o L1 usa el hechizo que se lleva y SELECT empieza otra carrera. La pista sale de
 * scripts/mapa_kart.py (kart_pista.h). */

#include "kart_pista.h"

extern s32 D_8007C8A4;               /* pasos quieta antes de una animacion de espera */
extern s16 D_8007CB70;               /* la animacion que debe tener el companero */
extern void ImprimirDepuracion(const char *formato, ...);
extern s32 rsin(s32 angulo);
extern s32 rcos(s32 angulo);
extern volatile s32 D_800649EC;      /* cuantas vueltas de la pantalla van (VSync) */
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);

#define K_PISO(o) CAMPO_S32(o, 0x50)               /* altura del suelo bajo Sabrina */
#define K_RAPIDEZ(o) CAMPO_S32(o, 0x74 + 0x04)     /* rapidez maxima que deja la fisica */
#define K_CONTACTO(o) CAMPO_S16(o, 0x74 + 0x18)    /* bit 3: choco con una pared */

#define K_ARRIBA 0x1000
#define K_DERECHA 0x2000
#define K_ABAJO 0x4000
#define K_IZQUIERDA 0x8000
#define K_X 0x40
#define K_CUADRADO 0x80
#define K_CIRCULO 0x20
#define K_TRIANGULO 0x10
#define K_R1 0x08
#define K_L1 0x04
#define K_SELECT 0x100
#define K_START 0x800

#define K_VUELTAS 3
#define K_SEG 28                     /* pasos del juego por segundo: medido 28.2 en el emulador (kart.py vuelta) */
#define K_VBL 60                     /* el cronometro va en vueltas de pantalla (VSync, 60 por segundo): no depende
                                      * de cuantos pasos de juego caben en un segundo */
#define K_VEL_MAX 7400               /* rapidez punta (en unidades de empuje; Sabrina corriendo va a ~3800) */
#define K_VEL_HIERBA 2600
#define K_VEL_TURBO 10200
#define K_VEL_ATRAS -1800
#define K_ACELERA 150
#define K_FRENA 380

enum { K_EMPEZAR, K_CUENTA, K_CARRERA, K_META };
enum { K_NADA, K_TURBO, K_TRIPLE, K_RELOJ };

static s32 k_fase, k_cuadros, k_tiempo, k_vel, k_vuelta, k_cp, k_ultimo, k_ini_vuelta, k_mejor;
static s32 k_derrape, k_carga, k_turbo, k_objeto, k_usos, k_aviso_t, k_cam_y, k_cam_d, k_cam_alto, k_en_caja;
static s16 k_rumbo, k_cam_rumbo;
static const char *k_aviso;
static s32 k_tiempos[K_VUELTAS];
static s32 k_vbl;                    /* D_800649EC del paso anterior */

/* El rival: Salem en su kart verde (el modelo 17 del HUB, FashionDiva, cambiado por kart_modelo.rival). No es un
 * objeto del juego: es un nodo de modelo colgado de los de los objetos (como hace func_8003821C) que se pone en su
 * sitio cada paso con MatrizDesdeAngulos. Corre por la linea de kart_ruta (mapa_kart.ruta_rival). */
#define K_RIVAL_MODELO 18             /* modelos_cargados va uno corrido: el 17 de la lista del .INO es el 18 */
#define K_RIVAL_LADO 280             /* va un poco a un lado de su linea: asi no van los dos por el centro */
#define K_RIVAL_VEL (46 * 16)                /* su rapidez de crucero, en 1/16 de unidad por paso */
static void *k_rival;
static s32 k_rd;                     /* lo que lleva recorrido desde la meta, sumando vueltas */
static s32 k_rv;                     /* su rapidez, en 1/16 de unidad por paso */
static s32 k_rlado;                  /* desvio a un lado de su linea (en la salida esta al lado de Sabrina) */
static s32 k_rx, k_rz, k_choque, k_puesto, k_progreso;
static s16 k_rrumbo;

static const char *const k_nombre_objeto[] = {"", "TURBO DE SALEM", "TRIPLE TURBO", "RELOJ DEL TIEMPO"};

static s32 k_dentro(const s16 *r, s32 x, s32 z) {
    return x >= r[0] && x < r[2] && z >= r[1] && z < r[3];
}

static void k_avisar(const char *texto, s32 cuadros) {
    k_aviso = texto;
    k_aviso_t = cuadros;
}

/* La diferencia de dos angulos (vuelta = 0x1000) entre -0x800 y 0x7FF. */
static s32 k_dif(s32 a, s32 b) {
    return ((a - b + 0x800) & 0xFFF) - 0x800;
}

/* Deja a Sabrina parada en (x, z) mirando a rumbo, un poco por encima del suelo (cae sola). */
static void __attribute__((noinline)) k_poner(Objeto *s, s32 x, s32 z, s32 rumbo) {
    s->x = x << 8;
    s->z = z << 8;
    s->y = -48 << 8;
    s->empuje_x = 0;
    s->empuje_z = 0;
    s->vel_y = 0;
    s->rot[1] = rumbo;
    k_rumbo = rumbo;
    k_cam_rumbo = rumbo;
    k_cam_y = s->y;
    k_cam_d = 0;
    k_vel = 0;
    k_derrape = 0;
    k_carga = 0;
    k_turbo = 0;
}

static void __attribute__((noinline)) k_empezar(Objeto *s) {
    s32 i;

    k_poner(s, KART_SALIDA_X, KART_SALIDA_Z, 0x400);
    k_fase = K_CUENTA;
    k_cuadros = 0;
    k_tiempo = 0;
    k_vuelta = 1;
    k_cp = 1;
    k_ultimo = 0;
    k_ini_vuelta = 0;
    k_objeto = K_NADA;
    k_usos = 0;
    k_aviso_t = 0;
    for (i = 0; i < K_VUELTAS; i++) {
        k_tiempos[i] = 0;
    }
}

/* Chispas detras del kart (las del suelo que quema, del color que se pida). */
static void __attribute__((noinline)) k_chispas(Objeto *s, s32 r, s32 g, s32 b, s32 n) {
    u8 *p;
    s32 dx, dz;

    while (n-- > 0) {
        dx = func_80021CE4(0x2000) - 0x1000 - (rsin(k_rumbo) << 1);
        dz = func_80021CE4(0x2000) - 0x1000 - (rcos(k_rumbo) << 1);
        p = CrearParticula(0xC, NULL, 0, s->x - (rsin(k_rumbo) << 5), s->y - 0x2000, s->z - (rcos(k_rumbo) << 5),
                           dx, -0x1400, dz, 0, 0x28F, 0, 0xF, 0, 0);
        if (p != NULL) {
            *(s32 *)(p + 0x3C) = 0x112;
            p[0x1C] = r;
            p[0x1D] = g;
            p[0x1E] = b;
        }
    }
}

static void k_imprimir_tiempo(const char *texto, s32 f) {
    s32 m = f / (60 * K_VBL), sg = (f / K_VBL) % 60, cs = (f % K_VBL) * 100 / K_VBL;

    ImprimirDepuracion("%s%d'%d%d\"%d%d", texto, m, sg / 10, sg % 10, cs / 10, cs % 10);
}

/* El texto de la pantalla. */
static void __attribute__((noinline)) k_pantalla(void) {
    s32 i;

    if (k_fase == K_CUENTA) {
        ImprimirDepuracion("\n  SABRINA KART - COPA DEL TIEMPO\n  CONTRA SALEM, 3 VUELTAS\n\n\n\n\n                     %d\n",
                           3 - k_cuadros / K_SEG);
        return;
    }
    if (k_fase == K_META) {
        ImprimirDepuracion("\n  SABRINA KART - COPA DEL TIEMPO\n\n\n        META!  LLEGASTE %s\n\n",
                           k_puesto == 1 ? "PRIMERA!" : "SEGUNDA");
        for (i = 0; i < K_VUELTAS; i++) {
            ImprimirDepuracion("          VUELTA %d  ", i + 1);
            k_imprimir_tiempo("", k_tiempos[i]);
            ImprimirDepuracion("\n");
        }
        k_imprimir_tiempo("\n          TOTAL     ", k_tiempo);
        k_imprimir_tiempo("\n          MEJOR     ", k_mejor);
        ImprimirDepuracion("\n");
        if (k_cuadros > 2 * K_SEG) {
            ImprimirDepuracion("\n       X O SELECT: OTRA CARRERA\n");
        }
        return;
    }
    /* tres lineas arriba: vuelta y puesto, tiempo y mejor vuelta, rapidez y hechizo */
    ImprimirDepuracion("\n  VUELTA %d/%d               PUESTO %d/2\n", k_vuelta, K_VUELTAS, k_rd > k_progreso ? 2 : 1);
    k_imprimir_tiempo("  TIEMPO ", k_tiempo);
    if (k_mejor != 0) {
        k_imprimir_tiempo("        MEJOR ", k_mejor);
    }
    ImprimirDepuracion("\n  %d KM/H", (k_vel < 0 ? -k_vel : k_vel) / 45);
    if (k_objeto != K_NADA) {
        ImprimirDepuracion("   %s", k_nombre_objeto[k_objeto]);
        if (k_objeto == K_TRIPLE) {
            ImprimirDepuracion(" x%d", k_usos);
        }
        ImprimirDepuracion(" (TRIANGULO)");
    }
    ImprimirDepuracion("\n");
    if (k_aviso_t > 0) {
        ImprimirDepuracion("\n\n\n            %s\n", k_aviso);
    } else if (k_fase == K_CARRERA && k_cuadros < K_SEG) {
        ImprimirDepuracion("\n\n\n                   YA!\n");
    }
}

/* Puntos de control, vueltas, turbos y cajas de hechizo. */
static void __attribute__((noinline)) k_pista(Objeto *s, s32 x, s32 z, s32 en_suelo) {
    s32 i, t, r;

    if (k_dentro(kart_cp[k_cp], x, z)) {
        if (k_cp == 0) {
            t = k_tiempo - k_ini_vuelta;
            k_tiempos[k_vuelta - 1] = t;
            if (k_mejor == 0 || t < k_mejor) {
                k_mejor = t;
            }
            k_ini_vuelta = k_tiempo;
            k_vuelta++;
            TocarSonido(1, 0, 0x30, 0x7F);
            if (k_vuelta > K_VUELTAS) {
                k_vuelta = K_VUELTAS;
                k_fase = K_META;
                k_cuadros = 0;
                k_aviso_t = 0;
                return;
            }
            k_avisar(k_vuelta == K_VUELTAS ? "ULTIMA VUELTA!" : "  OTRA VUELTA", 2 * K_SEG);
        }
        k_ultimo = k_cp;
        k_cp = k_cp + 1 == KART_NCP ? 0 : k_cp + 1;
    }
    if (!en_suelo) {
        return;
    }
    for (i = 0; i < KART_NTURBOS; i++) {
        if (k_dentro(kart_turbos[i], x, z)) {
            if (k_turbo < K_SEG) {
                TocarSonido(1, 0, 0x36, 0x7F);
            }
            k_turbo = K_SEG + K_SEG / 4;
        }
    }
    t = 0;
    for (i = 0; i < KART_NCAJAS; i++) {
        if (k_dentro(kart_cajas[i], x, z)) {
            t = 1;
        }
    }
    if (t && !k_en_caja && k_objeto == K_NADA) {
        r = func_80021CE4(100);
        k_objeto = r < 50 ? K_TURBO : (r < 80 ? K_TRIPLE : K_RELOJ);
        k_usos = k_objeto == K_TRIPLE ? 3 : 1;
        TocarSonido(1, 0, 0x3C, 0x7F);
        k_chispas(s, 0xFF, 0xD0, 0x40, 8);
    }
    k_en_caja = t;
}

/* Un paso del kart: rapidez, giro, derrape, turbos, y el empuje que se le deja a la fisica de Sabrina. */
static void __attribute__((noinline)) k_conducir(Objeto *s, u32 b, u32 nuevo, s32 en_suelo) {
    s32 giro, gas, freno, max, vuelta, rumbo, t;

    freno = (b & (K_CUADRADO | K_ABAJO)) != 0;
    gas = !freno;                    /* acelera solo */
    giro = ((b & K_DERECHA) != 0) - ((b & K_IZQUIERDA) != 0);
    if (k_fase != K_CARRERA) {
        gas = 0;
        freno = k_fase == K_META;
        giro = 0;
        nuevo = 0;
        b = 0;
    }
    /* el hechizo */
    if ((nuevo & (K_TRIANGULO | K_L1)) && k_objeto != K_NADA) {
        if (k_objeto == K_RELOJ) {
            k_tiempo = k_tiempo > 3 * K_VBL ? k_tiempo - 3 * K_VBL : 0;
            k_ini_vuelta = k_ini_vuelta > 3 * K_VBL ? k_ini_vuelta - 3 * K_VBL : 0;
            k_avisar("TIEMPO -3 SEGUNDOS!", 2 * K_SEG);
            k_chispas(s, 0xFF, 0xFF, 0x80, 12);
        } else {
            k_turbo = K_SEG + K_SEG / 2;
            k_avisar("   TURBO!", K_SEG);
            k_chispas(s, 0x60, 0xA0, 0xFF, 10);
        }
        TocarSonido(1, 0, 0x36, 0x7F);
        if (--k_usos <= 0) {
            k_objeto = K_NADA;
        }
    }
    /* derrape (sin saltito) */
    if ((b & (K_CIRCULO | K_R1)) && k_derrape == 0 && en_suelo && giro != 0 && k_vel > 2400) {
        k_derrape = giro;
        k_carga = 0;
    }
    if (k_derrape != 0) {
        if (!(b & (K_CIRCULO | K_R1)) || k_vel < 1600) {
            if (k_carga >= 2 * K_SEG + K_SEG / 2) {
                k_turbo = K_SEG;
                k_avisar(" SUPER MINI TURBO!", K_SEG);
            } else if (k_carga >= K_SEG + K_SEG / 4) {
                k_turbo = K_SEG / 2;
                k_avisar("   MINI TURBO!", K_SEG);
            }
            k_derrape = 0;
            k_carga = 0;
        } else if (en_suelo) {
            k_carga++;
            if (k_carga >= 2 * K_SEG + K_SEG / 2) {
                k_chispas(s, 0xFF, 0x80, 0x10, 1);
            } else if (k_carga >= K_SEG + K_SEG / 4) {
                k_chispas(s, 0x40, 0x80, 0xFF, 1);
            } else if (k_carga & 2) {
                k_chispas(s, 0xE0, 0xE0, 0xE0, 1);
            }
        }
    }
    /* rapidez */
    max = K_VEL_MAX;
    if (en_suelo && K_PISO(s) >= (KART_SUELO_HIERBA - 32) << 8 && k_turbo == 0) {
        max = K_VEL_HIERBA;
    }
    if (k_turbo > 0) {
        k_turbo--;
        max = K_VEL_TURBO;
        if (k_vel < K_VEL_TURBO) {
            k_vel += 400;
        }
        if (k_turbo & 1) {
            k_chispas(s, 0x60, 0xA0, 0xFF, 1);
        }
    } else if (gas) {
        k_vel += k_vel < 0 ? K_FRENA : K_ACELERA;
    } else if (freno) {
        k_vel -= k_vel > 0 ? K_FRENA : K_ACELERA / 2;
        if (k_vel < K_VEL_ATRAS) {
            k_vel = K_VEL_ATRAS;
        }
    } else {
        k_vel -= k_vel / 40;
        if (k_vel < 60 && k_vel > -60) {
            k_vel = 0;
        }
    }
    if (k_vel > max) {
        k_vel -= (k_vel - max) / 8 + 1;
    }
    /* una pared frena */
    if (K_CONTACTO(s) & 8) {
        k_vel -= k_vel / 12;
    }
    /* giro: nada parado, mas fuerte derrapando, al reves en marcha atras */
    t = k_vel < 0 ? -k_vel : k_vel;
    if (t > 3000) {
        t = 3000;
    }
    if (k_derrape != 0) {
        vuelta = k_derrape * 50 + giro * 22;
    } else {
        vuelta = giro * 44;
    }
    vuelta = vuelta * t / 3000;
    if (!en_suelo) {
        vuelta /= 2;
    }
    if (k_vel < 0) {
        vuelta = -vuelta;
    }
    k_rumbo = (k_rumbo + vuelta) & 0xFFF;
    /* derrapando el kart mira hacia dentro de la curva y resbala un poco hacia fuera */
    s->rot[1] = (k_rumbo + k_derrape * 0x140) & 0xFFF;
    rumbo = k_rumbo - k_derrape * 0x60;
    s->empuje_x = (rsin(rumbo) * k_vel) >> 12;
    s->empuje_z = (rcos(rumbo) * k_vel) >> 12;
    K_RAPIDEZ(s) = (k_vel < 0 ? -k_vel : k_vel) + 0x400;
}

/* Sabrina va sentada en el carrito (el modelo de la cadera para abajo es el kart, ver scripts/kart_modelo.py): siempre
 * la animacion de quieta, lenta, para que el kart no se mueva con la cadera; el companero tambien quieto. */
static void __attribute__((noinline)) k_animar(Objeto *s) {
    EstadoAnim *a = s->anim;
    u16 *t = s->animaciones;

    D_8007C8A4 = 150;
    if (a->animacion != t[0]) {
        a->animacion = t[0];
        a->_50 = 0;
        D_8007CB70 = 0;
    }
    a->_4E = 0x400;
}

/* Si el segmento de (ax, ay, az) a (bx, by, bz) choca con el nivel (las paredes y los setos). */
static s32 k_choca(s32 ax, s32 ay, s32 az, s32 bx, s32 by, s32 bz) {
    s32 r, antes = D_8007CBD4;

    /* la camara corre ignorando casi todos los tipos de triangulo (D_8007CBD4 = -17), entre ellos el 1 de las
     * paredes del editor: para esta prueba no se ignora ninguno */
    D_8007CBD4 = 0;
    D_800C6594[0] = ax;
    D_800C6594[1] = ay;
    D_800C6594[2] = az;
    D_800C65A0[0] = bx;
    D_800C65A0[1] = by;
    D_800C65A0[2] = bz;
    func_8003B38C(D_800C6594, D_800C6594, D_800C65A0);
    r = func_8003AE84() != 0;
    D_8007CBD4 = antes;
    return r;
}

/* La camara detras del kart: el rumbo y la altura la siguen con un poco de retraso, y se aleja con la rapidez. Si
 * entre Sabrina y ese punto hay una pared o un seto, sube (y se acerca un poco) hasta verla por encima; la distancia
 * y la altura cambian poco a poco para que no salte. */
static void __attribute__((noinline)) k_camara(Objeto *o, Objeto *s) {
    static const s16 pruebas[4][2] = {{8, 560}, {6, 760}, {5, 980}, {4, 1250}};   /* distancia en octavos, alto */
    s32 d, v[3], mx, my, mz, i, dd, alto, x, z;

    k_cam_rumbo = (k_cam_rumbo + k_dif(k_rumbo, k_cam_rumbo) / 6) & 0xFFF;
    k_cam_y += (s->y - k_cam_y) >> 2;
    d = 1100 + (k_vel > 0 ? k_vel / 30 : 0);
    for (i = 0; i < 4; i++) {
        dd = d * pruebas[i][0] / 8;
        alto = pruebas[i][1];
        x = s->x - ((rsin(k_cam_rumbo) * dd) >> 4);
        z = s->z - ((rcos(k_cam_rumbo) * dd) >> 4);
        if (!k_choca(s->x, k_cam_y - (300 << 8), s->z, x, k_cam_y - (alto << 8), z)) {
            break;
        }
    }
    if (k_cam_d == 0) {
        k_cam_d = dd;
        k_cam_alto = alto;
    }
    k_cam_d += (dd - k_cam_d) / 5;
    k_cam_alto += (alto - k_cam_alto) / 5;
    o->x = s->x - ((rsin(k_cam_rumbo) * k_cam_d) >> 4);
    o->z = s->z - ((rcos(k_cam_rumbo) * k_cam_d) >> 4);
    o->y = k_cam_y - (k_cam_alto << 8);
    mx = s->x + ((rsin(k_cam_rumbo) * 400) >> 4);
    mz = s->z + ((rcos(k_cam_rumbo) * 400) >> 4);
    my = k_cam_y - (150 << 8);
    v[0] = (mx - o->x) >> 8;
    v[1] = (my - o->y) >> 8;
    v[2] = (mz - o->z) >> 8;
    func_8001C45C(v);
    func_80022104(&o->rot[0], &o->rot[1], v);
    ojo_camara(o);
    mirar(o);
}

/* Cuanto lleva Sabrina desde la meta, sumando vueltas: su proyeccion sobre el tramo de la ruta mas cercano. */
static s32 __attribute__((noinline)) k_avance(Objeto *s) {
    s32 i, t, dx, dz, ex, ez, d2, mejor = 0x7FFFFFFF, r = 0;
    const s16 *q;

    for (i = 0; i < KART_RUTA_N; i++) {
        q = kart_ruta[i];
        dx = (s->x >> 8) - q[0];
        dz = (s->z >> 8) - q[1];
        t = (dx * q[3] + dz * q[4]) >> 12;
        d2 = (i + 1 < KART_RUTA_N ? kart_ruta_d[i + 1] : KART_RUTA_LARGO) - kart_ruta_d[i];
        if (t < 0) {
            t = 0;
        }
        if (t > d2) {
            t = d2;
        }
        ex = dx - ((q[3] * t) >> 12);
        ez = dz - ((q[4] * t) >> 12);
        d2 = ex * ex + ez * ez;
        if (d2 < mejor) {
            mejor = d2;
            r = kart_ruta_d[i] + t;
        }
    }
    /* recien salida (el siguiente punto es el 1 y no ha cruzado la meta) esta al final de la vuelta anterior */
    if (k_cp == 1 && r > KART_RUTA_LARGO * 3 / 4) {
        r -= KART_RUTA_LARGO;
    }
    return (k_vuelta - 1) * KART_RUTA_LARGO + r;
}

/* Un paso de Salem: acelera hasta su rapidez, que se estira como una goma (mas rapido si Sabrina se le escapa, mas
 * lento si le saca mucha ventaja), avanza por la ruta, gira poco a poco hacia el tramo en que va y, si toca a
 * Sabrina, los dos se frenan. */
static void __attribute__((noinline)) k_rival_paso(Objeto *s) {
    s32 i, d, meta, escala[3], pos[3], giro[3];
    const s16 *q;

    if (k_rival == NULL) {
        if (modelos_cargados[K_RIVAL_MODELO] == NULL) {
            return;
        }
        k_rival = func_8001E06C(modelos_cargados[K_RIVAL_MODELO], D_8007C9F0);
    }
    k_progreso = k_avance(s);
    if (k_fase == K_CUENTA) {
        k_rd = -900 + 350;           /* a la altura de Sabrina, un poco delante, en el otro carril */
        k_rv = 0;
        k_rlado = 520;
        k_rrumbo = 0x400;
        k_choque = 0;
    } else if (k_rd < K_VUELTAS * KART_RUTA_LARGO) {
        meta = K_RIVAL_VEL - (k_rd - k_progreso) / 8;
        meta = meta < 36 * 16 ? 36 * 16 : (meta > 58 * 16 ? 58 * 16 : meta);
        k_rv += k_rv < meta ? 14 : -14;
        k_rd += k_rv >> 4;
        k_rlado += (K_RIVAL_LADO - k_rlado) / 48;
        if (k_rd >= K_VUELTAS * KART_RUTA_LARGO && k_fase == K_CARRERA) {
            k_avisar("SALEM CRUZO LA META!", 2 * K_SEG);
        }
    } else {
        k_rv -= k_rv / 16;           /* ya llego: rueda hasta pararse */
        k_rd += k_rv >> 4;
    }
    d = k_rd % KART_RUTA_LARGO;
    if (d < 0) {
        d += KART_RUTA_LARGO;
    }
    for (i = KART_RUTA_N - 1; kart_ruta_d[i] > d; i--) {
    }
    q = kart_ruta[i];
    d -= kart_ruta_d[i];
    meta = k_dif(q[2], k_rrumbo);
    k_rrumbo = (k_rrumbo + (meta > 70 ? 70 : (meta < -70 ? -70 : meta))) & 0xFFF;
    k_rx = q[0] + ((q[3] * d) >> 12) + ((rcos(k_rrumbo) * k_rlado) >> 12);
    k_rz = q[1] + ((q[4] * d) >> 12) - ((rsin(k_rrumbo) * k_rlado) >> 12);
    escala[0] = 5734;                /* la escala del objeto de Sabrina (5734, 4096, 5734), leida en la RAM */
    escala[1] = 0x1000;
    escala[2] = 5734;
    pos[0] = k_rx << 8;
    pos[1] = 0;
    pos[2] = k_rz << 8;
    giro[0] = 0;
    giro[1] = k_rrumbo;
    giro[2] = 0;
    MatrizDesdeAngulos(k_rival, escala, pos, giro);
    /* choque */
    if (k_choque > 0) {
        k_choque--;
    } else if (k_fase == K_CARRERA && (s->x >> 8) - k_rx < 330 && k_rx - (s->x >> 8) < 330 &&
               (s->z >> 8) - k_rz < 330 && k_rz - (s->z >> 8) < 330) {
        /* Salem se aparta hacia el lado contrario de donde esta Sabrina */
        d = (((s->x >> 8) - k_rx) * rcos(k_rrumbo) - ((s->z >> 8) - k_rz) * rsin(k_rrumbo)) >> 12;
        k_rlado += d > 0 ? -420 : 420;
        k_rlado = k_rlado > 600 ? 600 : (k_rlado < -600 ? -600 : k_rlado);
        k_vel -= k_vel / 5;
        k_rv -= k_rv / 6;
        k_choque = K_SEG;
        k_avisar("  CHOCASTE CON SALEM!", K_SEG);
        TocarSonido(1, 0, 0x2A, 0x7F);
    }
}

static void __attribute__((noinline)) kart_paso(Objeto *o) {
    Objeto *s = p_sabrina;
    u32 b = D_8007CA50, nuevo = D_8007CA58;
    s32 x, z, en_suelo, dv;

    /* el mando es del kart: a Sabrina solo le llega START (la pausa) */
    D_8007CA50 &= K_START;
    D_8007CA54 = 0;
    D_8007CA58 &= K_START;
    if (k_fase == K_EMPEZAR || (nuevo & K_SELECT) ||
        (k_fase == K_META && k_cuadros > 2 * K_SEG && (nuevo & K_X))) {
        k_empezar(s);
    }
    k_cuadros++;
    if (k_aviso_t > 0) {
        k_aviso_t--;
    }
    x = s->x >> 8;
    z = s->z >> 8;
    en_suelo = s->y >= K_PISO(s) - 0xC00;
    if (k_fase == K_CUENTA) {
        if (k_cuadros % K_SEG == 1) {
            TocarSonido(1, 0, 0x2A, 0x7F);
        }
        if (k_cuadros >= 3 * K_SEG) {
            k_fase = K_CARRERA;
            k_cuadros = 0;
            TocarSonido(1, 0, 0x36, 0x7F);
        }
    } else if (k_fase == K_CARRERA) {
        /* lo que paso desde el paso anterior; mas de 6 vueltas de pantalla es una pausa (START) o una carga */
        dv = D_800649EC - k_vbl;
        k_tiempo += dv > 0 && dv <= 6 ? dv : 2;
    }
    k_vbl = D_800649EC;
    k_conducir(s, b, nuevo, en_suelo);
    if (k_fase == K_CARRERA) {
        k_pista(s, x, z, en_suelo);
        if (k_fase == K_META) {
            k_puesto = k_rd > k_avance(s) ? 2 : 1;
        }
    }
    k_rival_paso(s);
    /* al agua: Salem la saca en el ultimo punto de control */
    if (s->y > KART_FONDO << 8) {
        k_poner(s, kart_cp[k_ultimo][4], kart_cp[k_ultimo][5], kart_cp[k_ultimo][6]);
        k_avisar("SALEM TE SACO DEL AGUA", 2 * K_SEG);
    }
    k_animar(s);
    k_camara(o, s);
    k_pantalla();
}
