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
#define K_SEG 50                     /* pasos del juego por segundo (medido en el emulador) */
#define K_VEL_MAX 5600               /* rapidez punta (en unidades de empuje; Sabrina corriendo va a ~3800) */
#define K_VEL_HIERBA 2200
#define K_VEL_TURBO 8200
#define K_VEL_ATRAS -1600
#define K_ACELERA 95
#define K_FRENA 260

enum { K_EMPEZAR, K_CUENTA, K_CARRERA, K_META };
enum { K_NADA, K_TURBO, K_TRIPLE, K_RELOJ };

static s32 k_fase, k_cuadros, k_tiempo, k_vel, k_vuelta, k_cp, k_ultimo, k_ini_vuelta, k_mejor;
static s32 k_derrape, k_carga, k_turbo, k_objeto, k_usos, k_aviso_t, k_cam_y, k_cam_d, k_cam_alto, k_en_caja;
static s16 k_rumbo, k_cam_rumbo;
static const char *k_aviso;
static s32 k_tiempos[K_VUELTAS];

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
    s32 m = f / (60 * K_SEG), sg = (f / K_SEG) % 60, cs = (f % K_SEG) * 100 / K_SEG;

    ImprimirDepuracion("%s%d'%d%d\"%d%d\n", texto, m, sg / 10, sg % 10, cs / 10, cs % 10);
}

/* El texto de la pantalla. */
static void __attribute__((noinline)) k_pantalla(void) {
    s32 i, n;

    ImprimirDepuracion("\n  SABRINA KART - COPA DEL TIEMPO\n\n");
    if (k_fase == K_CUENTA) {
        n = 3 - k_cuadros / K_SEG;
        ImprimirDepuracion("\n\n\n\n\n                     %d\n", n);
        return;
    }
    if (k_fase == K_META) {
        ImprimirDepuracion("\n\n             META!\n\n");
        for (i = 0; i < K_VUELTAS; i++) {
            ImprimirDepuracion("          VUELTA %d  ", i + 1);
            k_imprimir_tiempo("", k_tiempos[i]);
        }
        k_imprimir_tiempo("\n          TOTAL     ", k_tiempo);
        k_imprimir_tiempo("          MEJOR     ", k_mejor);
        if (k_cuadros > 2 * K_SEG) {
            ImprimirDepuracion("\n       X O SELECT: OTRA CARRERA\n");
        }
        return;
    }
    ImprimirDepuracion("  VUELTA %d/%d     ", k_vuelta, K_VUELTAS);
    k_imprimir_tiempo("", k_tiempo);
    if (k_mejor != 0) {
        k_imprimir_tiempo("                  MEJOR ", k_mejor);
    } else {
        ImprimirDepuracion("\n");
    }
    ImprimirDepuracion("  %d KM/H\n", (k_vel < 0 ? -k_vel : k_vel) / 45);
    if (k_objeto != K_NADA) {
        ImprimirDepuracion("  HECHIZO: %s", k_nombre_objeto[k_objeto]);
        if (k_objeto == K_TRIPLE) {
            ImprimirDepuracion(" x%d", k_usos);
        }
        ImprimirDepuracion("  (TRIANGULO)\n");
    } else {
        ImprimirDepuracion("\n");
    }
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
            k_tiempo = k_tiempo > 3 * K_SEG ? k_tiempo - 3 * K_SEG : 0;
            k_ini_vuelta = k_ini_vuelta > 3 * K_SEG ? k_ini_vuelta - 3 * K_SEG : 0;
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
        k_vel -= k_vel / 6;
    }
    /* giro: nada parado, mas fuerte derrapando, al reves en marcha atras */
    t = k_vel < 0 ? -k_vel : k_vel;
    if (t > 3000) {
        t = 3000;
    }
    if (k_derrape != 0) {
        vuelta = k_derrape * 34 + giro * 16;
    } else {
        vuelta = giro * 30;
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

static void __attribute__((noinline)) kart_paso(Objeto *o) {
    Objeto *s = p_sabrina;
    u32 b = D_8007CA50, nuevo = D_8007CA58;
    s32 x, z, en_suelo;

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
        k_tiempo++;
    }
    k_conducir(s, b, nuevo, en_suelo);
    if (k_fase == K_CARRERA) {
        k_pista(s, x, z, en_suelo);
    }
    /* al agua: Salem la saca en el ultimo punto de control */
    if (s->y > KART_FONDO << 8) {
        k_poner(s, kart_cp[k_ultimo][4], kart_cp[k_ultimo][5], kart_cp[k_ultimo][6]);
        k_avisar("SALEM TE SACO DEL AGUA", 2 * K_SEG);
    }
    k_animar(s);
    k_camara(o, s);
    k_pantalla();
}
