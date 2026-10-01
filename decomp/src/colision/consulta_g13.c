#include "juego.h"

/* Choque de un segmento contra una lista de triangulos de colision. */

/* Consulta de choque (0x4C bytes): de x, y, z a x2, y2, z2 (24.8); func_8003A750 deja en punto y normal
 * donde corta un triangulo. */
typedef struct {
    s32 x, y, z;                     /* 0x00 */
    s32 x2, y2, z2;                  /* 0x0C */
    u8 _18[0x18];
    s32 punto[3];                    /* 0x30 */
    s32 normal[3];                   /* 0x3C */
    u16 tipo;                        /* 0x48, el del triangulo que choco */
    u8 _4A[2];
} ConsultaSegmento;
EN(ConsultaSegmento, x2, 0x0C);
EN(ConsultaSegmento, punto, 0x30);
EN(ConsultaSegmento, tipo, 0x48);

typedef struct {
    s16 *v[3];                       /* 0x00 */
    u8 _0C[0x0A];
    u16 tipo;                        /* 0x16 */
    u8 _18[4];
} TrianguloSeg;
EN(TrianguloSeg, tipo, 0x16);

extern s32 func_8001C33C(s32 *a, s32 *b);  /* producto escalar */
extern s32 func_8003A750(ConsultaSegmento *c, TrianguloSeg *t);  /* corta el segmento con el triangulo */

/* Prueba el segmento de la consulta contra los triangulos de la lista (n indices s16 en tris) y se queda
 * con el corte mas cercano al comienzo que no pase del largo del segmento: guarda su punto (24.8), su
 * normal y el tipo del triangulo. Antes descarta los triangulos cuya caja en x y z no toca la del
 * segmento. Devuelve 1 si hubo corte. */
s32 func_8003A94C(ConsultaSegmento *c, TrianguloSeg *tris, s32 n, s16 *indices) {
    ConsultaSegmento l;
    s32 dir[3], mejor_p[3];
    s32 d[3];
    s32 largo, dist, hallado = 0, i;
    s32 sx_min, sx_max, sz_min, sz_max;
    s32 tx_min, tx_max, tz_min, tz_max, k, x, z;
    s32 *de = (s32 *)c, *a = (s32 *)&l;
    TrianguloSeg *t;

    for (i = 0; i < 19; i++) {
        a[i] = de[i];
    }
    l.x >>= 8;
    l.y >>= 8;
    l.z >>= 8;
    l.x2 >>= 8;
    l.y2 >>= 8;
    l.z2 >>= 8;
    dir[0] = l.x2 - l.x;
    dir[1] = l.y2 - l.y;
    dir[2] = l.z2 - l.z;
    largo = func_8001C33C(dir, dir);
    if (l.x2 < l.x) {
        sx_min = l.x2;
        sx_max = l.x;
    } else {
        sx_min = l.x;
        sx_max = l.x2;
    }
    if (l.z2 < l.z) {
        sz_min = l.z2;
        sz_max = l.z;
    } else {
        sz_min = l.z;
        sz_max = l.z2;
    }
    for (i = 0; i < n; i++) {
        t = &tris[indices[i]];
        tx_min = tx_max = t->v[0][0];
        tz_min = tz_max = t->v[0][2];
        for (k = 1; k < 3; k++) {
            x = t->v[k][0];
            z = t->v[k][2];
            if (x < tx_min) {
                tx_min = x;
            } else if (tx_max < x) {
                tx_max = x;
            }
            if (z < tz_min) {
                tz_min = z;
            } else if (tz_max < z) {
                tz_max = z;
            }
        }
        if (sx_max < tx_min || sz_max < tz_min || tz_max < sz_min || tx_max < sx_min) {
            continue;
        }
        if (func_8003A750(&l, t) == 0) {
            continue;
        }
        d[0] = l.punto[0] - l.x;
        d[1] = l.punto[1] - l.y;
        d[2] = l.punto[2] - l.z;
        if (!hallado) {
            /* la primera vez la distancia queda anotada aunque no sirva */
            dist = func_8001C33C(d, d);
            if (dist >= largo) {
                continue;
            }
            hallado = 1;
        } else {
            k = func_8001C33C(d, d);
            if (k >= largo || k >= dist) {
                continue;
            }
            dist = k;
        }
        dir[0] = l.normal[0];
        dir[1] = l.normal[1];
        dir[2] = l.normal[2];
        mejor_p[0] = l.punto[0];
        mejor_p[1] = l.punto[1];
        mejor_p[2] = l.punto[2];
        c->tipo = t->tipo;
    }
    if (hallado) {
        c->punto[0] = mejor_p[0] << 8;
        c->punto[1] = mejor_p[1] << 8;
        c->punto[2] = mejor_p[2] << 8;
        c->normal[0] = dir[0];
        c->normal[1] = dir[1];
        c->normal[2] = dir[2];
    }
    return hallado;
}

extern u8 D_8007CBD6;                /* 1 si la ultima busqueda de suelo encontro uno */
extern void func_8003B38C(ConsultaSegmento *c, s32 *desde, s32 *hasta, s16 *indices);
extern s32 func_8003A524(ConsultaSegmento *c, TrianguloSeg *t);  /* triangulo_g09.c */

/* Busca el suelo bajo la consulta: prueba los triangulos de la lista cuya caja en x y z contiene el punto
 * (con func_8003A524, que deja el corte en la consulta) y se queda con el que corta mas cerca por encima
 * del punto (altura de corte menos la del punto, no negativa). Antes llama a func_8003B38C con el punto y
 * otro 0x1E80 mas abajo. Si hallo uno deja su punto (24.8), su normal y su tipo, marca D_8007CBD6 y
 * devuelve 1. */
s32 func_8003AF9C(ConsultaSegmento *c, TrianguloSeg *tris, s32 n, s16 *indices) {
    s32 p[3], q[3], normal[3], punto[3];
    s32 px, pz, hallado = 0, mejor = 0, d, i, k, x, z;
    s32 tx_min, tx_max, tz_min, tz_max;
    TrianguloSeg *t;

    p[0] = c->x >> 8;
    p[1] = c->y >> 8;
    p[2] = c->z >> 8;
    q[0] = p[0];
    q[2] = p[2];
    q[1] = p[1] + 0x1E80;
    px = c->x >> 8;
    pz = c->z >> 8;
    func_8003B38C(c, p, q, indices);
    for (i = 0; i < n; i++) {
        t = &tris[indices[i]];
        tx_min = tx_max = t->v[0][0];
        tz_min = tz_max = t->v[0][2];
        for (k = 1; k < 3; k++) {
            x = t->v[k][0];
            z = t->v[k][2];
            if (x < tx_min) {
                tx_min = x;
            } else if (tx_max < x) {
                tx_max = x;
            }
            if (z < tz_min) {
                tz_min = z;
            } else if (tz_max < z) {
                tz_max = z;
            }
        }
        if (px < tx_min || tx_max < px || pz < tz_min || tz_max < pz) {
            continue;
        }
        if (func_8003A524(c, t) == 0) {
            continue;
        }
        d = c->punto[1] - p[1];
        if (d < 0) {
            continue;
        }
        if (hallado && d >= mejor) {
            continue;
        }
        mejor = d;
        hallado = 1;
        normal[0] = c->normal[0];
        normal[1] = c->normal[1];
        normal[2] = c->normal[2];
        punto[0] = c->punto[0];
        punto[1] = c->punto[1];
        punto[2] = c->punto[2];
        c->tipo = t->tipo;
    }
    if (hallado != 1) {
        return 0;
    }
    c->normal[0] = normal[0];
    c->normal[1] = normal[1];
    c->normal[2] = normal[2];
    c->punto[0] = punto[0] << 8;
    c->punto[1] = punto[1] << 8;
    c->punto[2] = punto[2] << 8;
    D_8007CBD6 = 1;
    return 1;
}
