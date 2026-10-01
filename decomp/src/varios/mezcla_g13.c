#include "objeto.h"

/* Mezcla de dos cuadros de animacion. */

/* Un cuadro clave (12 bytes, en D_800B4C5C): los angulos de los huesos (3 bytes por hueso), la
 * posicion y un dato que se copia tal cual. */
typedef struct {
    u8 *angulos;                     /* 0x00 */
    s16 x, y, z;                     /* 0x04 */
    u16 dato;                        /* 0x0A */
} CuadroClave;

/* La vista de EstadoAnim que usa la mezcla. */
typedef struct {
    s16 x, y, z;                     /* 0x00 */
    u8 _06[2];
    u8 huesos;                       /* 0x08 */
    u8 _09;
    u8 angulos[0x42];                /* 0x0A */
    s16 t;                           /* 0x4C, cuanto de b (0x1000 = todo) */
    u8 _4E[2];
    u8 cuadro_b, anim_b;             /* 0x50 */
    u8 cuadro_a, anim_a;             /* 0x52 */
    u16 dato;                        /* 0x54 */
} Mezcla;
EN(Mezcla, huesos, 0x08);
EN(Mezcla, t, 0x4C);
EN(Mezcla, anim_a, 0x53);
EN(Mezcla, dato, 0x54);

extern CuadroClave D_800B4C5C[];
extern u16 D_800C4E2C[];             /* por animacion, 4 bytes: su primer cuadro en D_800B4C5C */
extern s32 func_80014AEC(s32 v);     /* valor absoluto */

/* Deja en el estado de animacion del objeto la mezcla del cuadro a con el b segun t: la posicion en
 * linea recta y cada angulo (de 0 a 255) por el camino mas corto. */
void func_8002EDC8(Objeto *o) {
    Mezcla *m = (Mezcla *)o->anim;
    s32 t = m->t;
    CuadroClave *a = &D_800B4C5C[m->cuadro_a + D_800C4E2C[m->anim_a * 2]];
    CuadroClave *b = &D_800B4C5C[m->cuadro_b + D_800C4E2C[m->anim_b * 2]];
    u8 *out = m->angulos;
    u8 *pa, *pb;
    s32 n, d, va;

    m->x = a->x + ((t * (b->x - a->x)) >> 12);
    m->y = a->y + ((t * (b->y - a->y)) >> 12);
    m->z = a->z + ((t * (b->z - a->z)) >> 12);
    m->dato = b->dato;
    pa = a->angulos;
    pb = b->angulos;
    for (n = m->huesos * 3; n > 0; n--) {
        d = *pb++;
        va = *pa++;
        d -= va;
        if (func_80014AEC(d) >= 0x80) {
            if (d > 0) {
                d = -(0x100 - d);
            } else {
                d += 0x100;
            }
        }
        *out++ = va + (((d * t) >> 12) & 0xFF);
    }
}

/* Una animacion (4 bytes, en D_8007CB64 al leerla): su primer cuadro en D_800B4C5C, cuantos cuadros tiene
 * y cuantos huesos. */
typedef struct {
    u16 primero;
    u8 cuadros;
    u8 huesos;
} Animacion;

extern CuadroClave *D_8007CB60;      /* el siguiente cuadro libre */
extern Animacion *D_8007CB64;        /* la siguiente animacion libre */
extern Animacion *D_8007CB68;        /* la ultima animacion leida */
extern u8 *D_8007CB5C;               /* donde van los angulos */
extern void ArchivoLeer(void *a, void *destino, s32 tam);

/* Lee una animacion .MAO: 4 bytes que no se usan, cuantos cuadros, cuantos huesos y, por cuadro, la
 * posicion (tres s16) y los angulos (3 bytes por hueso). El primer cuadro queda marcado con 1 y el
 * ultimo con 2 en su dato. */
void LeerMAO(void *a) {
    s32 nada;
    u16 v;
    s32 cuadros, tam;

    ArchivoLeer(a, &nada, 4);
    ArchivoLeer(a, &v, 2);
    cuadros = v;
    D_8007CB64->cuadros = v;
    ArchivoLeer(a, &v, 2);
    D_8007CB64->huesos = v;
    /* division con signo de verdad: la resta de punteros de C supone que da exacta */
    D_8007CB64->primero = (s32)((u8 *)D_8007CB60 - (u8 *)D_800B4C5C) / 12;
    D_8007CB68 = D_8007CB64;
    tam = v * 3;
    for (; cuadros > 0; cuadros--) {
        D_8007CB60->angulos = D_8007CB5C;
        D_8007CB60->dato = 0;
        ArchivoLeer(a, &D_8007CB60->x, 2);
        ArchivoLeer(a, &D_8007CB60->y, 2);
        ArchivoLeer(a, &D_8007CB60->z, 2);
        ArchivoLeer(a, D_8007CB5C, tam);
        D_8007CB5C += tam;
        D_8007CB60++;
    }
    D_8007CB60--;
    D_8007CB60->dato = 2;
    D_8007CB60++;
    D_800B4C5C[D_8007CB64->primero].dato = 1;
    D_8007CB64++;
}
