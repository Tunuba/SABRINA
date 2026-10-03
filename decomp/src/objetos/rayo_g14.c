#include "objeto.h"

/* Un rayo de particulas entre dos objetos, y el objeto que flota y lanza rayos a los que tiene enganchados. */

extern u8 *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                          s32 d, s32 e, s32 f, s32 g, s32 h);
extern s32 func_8002225C(u8 *o, s32 dx, s32 dy, s32 dz);   /* largo de un vector */
extern s32 func_80021CE4(s32 n);     /* al azar */
extern s32 rsin(s32 a);
extern u8 *func_8002506C(s32 *p, s32 alcance, u8 *excepto);   /* el objeto mas cercano a p */
extern s32 func_8001C33C(s32 *v);    /* largo de un vector */

#define C8(p, d) (*(u8 *)((u8 *)(p) + (d)))
#define C16(p, d) (*(s16 *)((u8 *)(p) + (d)))
#define C32(p, d) (*(s32 *)((u8 *)(p) + (d)))

/* Parte el camino de a hasta b en tramos de unos `paso` de largo y une los puntos con particulas del tipo
 * dado; cada punto intermedio se corre al azar hasta paso/4 para cada lado. */
void func_8003B894(u8 *a, u8 *b, s32 paso, s32 tipo) {
    s32 p[3];
    s32 d[3];
    s32 x, y, z, nx, ny, nz;
    s32 mitad, cuarto;
    s16 k, v;

    p[0] = C32(a, 0x24);
    p[1] = C32(a, 0x28);
    p[2] = C32(a, 0x2C);
    d[0] = RESTA_TRAMPA(C32(b, 0x24), p[0]);
    d[1] = RESTA_TRAMPA(C32(b, 0x28), p[1]);
    d[2] = RESTA_TRAMPA(C32(b, 0x2C), p[2]);
    k = func_8002225C(a, d[0], d[1], d[2]) / paso;
    x = p[0];
    y = p[1];
    z = p[2];
    cuarto = paso >> 2;
    mitad = paso >> 1;
    d[0] /= k;
    d[1] /= k;
    d[2] /= k;
    for (;;) {
        v = k;
        k = v - 1;
        if (v < 2) {
            break;
        }
        p[0] = SUMA_TRAMPA(p[0], d[0]);
        p[1] = SUMA_TRAMPA(p[1], d[1]);
        p[2] = SUMA_TRAMPA(p[2], d[2]);
        nx = SUMA_TRAMPA(p[0], RESTA_TRAMPA(func_80021CE4(mitad), cuarto));
        ny = SUMA_TRAMPA(p[1], RESTA_TRAMPA(func_80021CE4(mitad), cuarto));
        nz = SUMA_TRAMPA(p[2], RESTA_TRAMPA(func_80021CE4(mitad), cuarto));
        CrearParticula((s8)tipo, NULL, 0, x, y, z, RESTA_TRAMPA(nx, x), RESTA_TRAMPA(ny, y), RESTA_TRAMPA(nz, z),
                       0, 0, 0, 0xF, 0x402, 0);
        x = nx;
        y = ny;
        z = nz;
    }
    CrearParticula((s8)tipo, NULL, 0, x, y, z, RESTA_TRAMPA(C32(b, 0x24), x), RESTA_TRAMPA(C32(b, 0x28), y),
                   RESTA_TRAMPA(C32(b, 0x2C), z), 0, 0, 0, 0xF, 0x402, 0);
}

/* Zona extra: hasta 5 objetos enganchados (0..0x10), su cantidad (0x14), el que toca (0x16), la cuenta del
 * rayo (0x18), la espera entre rayos (0x1A) y la vida (0x1C). Flota en circulos; mientras vive crece hacia
 * 0x1000 y al acabarse se achica hasta desaparecer. Si tiene menos de 5, engancha al objeto mas cercano que
 * este a menos de 0x1900 (llamando a su funcion 0x08). Cada 20 cuadros le tira un rayo al que toca (si ya
 * no esta lo saca de la lista); mientras dura el rayo es solido. Devuelve lo que el original deja en v0. */
s32 func_8003B57C(u8 *o) {
    u8 *e = o + 0x74;
    s32 p[3];
    s32 t, meta, n, c, w;
    u8 *s;
    s32 *lugar;

    C32(o, 0x28) = SUMA_TRAMPA(C32(o, 0x28), rsin(C16(e, 0x1C) << 6));
    C32(o, 0x24) = SUMA_TRAMPA(C32(o, 0x24), rsin(C16(e, 0x1C) << 5));
    C32(o, 0x2C) = SUMA_TRAMPA(C32(o, 0x2C), rsin(C16(e, 0x1C) << 4));
    t = C16(e, 0x1C);
    C16(e, 0x1C) = SUMA_TRAMPA(t, -1);
    if (t > 0) {
        meta = 0x1000;
    } else {
        meta = 0x12C;
        if (C32(o, 0x54) < 0x200) {
            C8(o, 0x20) |= 0x80;
            return C8(o, 0x20);
        }
    }
    C32(o, 0x54) = SUMA_TRAMPA(C32(o, 0x54), RESTA_TRAMPA(meta, C32(o, 0x54)) >> 2);
    C32(o, 0x58) = C32(o, 0x54);
    C32(o, 0x5C) = C32(o, 0x54);
    if (C16(e, 0x14) < 5) {
        p[0] = C32(o, 0x24);
        p[1] = C32(o, 0x28);
        p[2] = C32(o, 0x2C);
        s = func_8002506C(p, 0x3E8, o);
        if (s != NULL) {
            p[0] = RESTA_TRAMPA(p[0], C32(s, 0x24)) >> 8;
            p[1] = RESTA_TRAMPA(p[1], C32(s, 0x28)) >> 8;
            p[2] = RESTA_TRAMPA(p[2], C32(s, 0x2C)) >> 8;
            if (func_8001C33C(p) < 0x1900) {
                (*(void (**)(u8 *, u8 *))(o + 8))(o, s);
            }
        }
    }
    n = C16(e, 0x14);
    if (n == 0) {
        return 0;
    }
    c = C16(e, 0x18);
    if (c > 0) {
        lugar = (s32 *)(e + C16(e, 0x16) * 4);
        s = (u8 *)*lugar;
        if (s != NULL) {
            if (c == 0x14) {
                func_8003B894(o, s, 0x20000, 0xF);
                func_8003B894(o, s, 0x10000, 0x10);
            }
        } else {
            *lugar = C32(e, SUMA_TRAMPA(n, -1) * 4);
            C32(e, SUMA_TRAMPA(C16(e, 0x14), -1) * 4) = 0;
            C16(e, 0x14) = SUMA_TRAMPA(C16(e, 0x14), -1);
            C16(e, 0x18) = 0;
        }
        if (C16(e, 0x18) == 1) {
            C16(o, 0x112) = 0x1800;
            C8(o, 0x119) = 1;
        } else {
            C16(o, 0x112) = 8;
            C8(o, 0x119) = 0;
        }
        w = SUMA_TRAMPA(C16(e, 0x18), -1);
        C16(e, 0x18) = w;
        return w;
    }
    w = C16(e, 0x1A);
    C16(e, 0x1A) = SUMA_TRAMPA(w, -1);
    if (w >= 0) {
        return SUMA_TRAMPA(w, -1);
    }
    C16(e, 0x1A) = 5;
    C16(e, 0x18) = 0x14;
    C16(e, 0x16) = SUMA_TRAMPA(C16(e, 0x16), 1);
    n = C16(e, 0x14);
    if (C16(e, 0x16) >= n) {
        C16(e, 0x16) = 0;
    }
    return n;
}
