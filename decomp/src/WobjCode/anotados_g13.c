#include "objeto.h"

/* La lista de cosas anotadas (D_800C7960, D_8007CC0C entradas de 0x38 bytes; en +0x30 esta lo que
 * recogibles.c llama recogidos). Cada cuadro se mueve cada una segun su forma y se quitan las que se
 * fueron lejos o pidieron salir. */

/* Lo que mueve una entrada: solo se usan su posicion (+4) y un contador en +0x40. */
typedef struct {
    u8 _00[4];
    s32 x, y, z;                     /* 0x04 */
    u8 _10[0x14];
    s32 _24;                         /* 0x24 */
    u8 _28[0x18];
    s16 vida;                        /* 0x40 */
    u16 banderas;                    /* 0x42 */
} ObjAnotado;
EN(ObjAnotado, x, 0x04);
EN(ObjAnotado, vida, 0x40);

/* El objeto que se recogio: en +0x1A queda como termino (0 o 2). */
typedef struct {
    u8 _00[0x1A];
    s16 fin;                         /* 0x1A */
} ObjRecogido;
EN(ObjRecogido, fin, 0x1A);

typedef struct {
    s32 x, y, z;                     /* 0x00 */
    s32 vel[3];                      /* 0x0C */
    s32 escala[3];                   /* 0x18 */
    s16 extra0;                      /* 0x24 */
    s16 extra4;                      /* 0x26 */
    s16 giro_y;                      /* 0x28 */
    s16 forma;                       /* 0x2A, 0, 1 o 2: elige la funcion que la mueve */
    s32 y0;                          /* 0x2C */
    ObjRecogido *recogido;           /* 0x30 */
    ObjAnotado *obj;                 /* 0x34 */
} Anotado;
EN(Anotado, forma, 0x2A);
EN(Anotado, recogido, 0x30);
EN(Anotado, obj, 0x34);

extern Anotado D_800C7960[];
extern s32 D_800C8450[];             /* por entrada: 0 sigue, 1 se fue lejos, 2 pidio salir */
extern s32 D_8007CC0C;               /* cuantas hay */

extern void *memset(void *p, s32 c, u32 n);
extern s32 func_800479D8(Anotado *a);
extern s32 func_800479E8(Anotado *a);
extern s32 func_80047AA4(Anotado *a);

void func_80047710(void) {
    Anotado *a = D_800C7960;
    s32 i, j, k, d;
    s32 *de, *a_;
    s32 n;

    memset(D_800C8450, 0, 0xC8);
    for (i = 0; i < D_8007CC0C; i++, a++) {
        if (a->forma == 2) {
            d = func_80047AA4(a);
        } else if (a->forma == 1) {
            d = func_800479E8(a);
        } else if (a->forma == 0) {
            d = func_800479D8(a);
        } else {
            d = -1;
        }
        if (d >= 0x38401) {
            D_800C8450[i] = 1;
        } else if (d < 0) {
            D_800C8450[i] = 2;
        }
        D_800C7960[i].obj->vida = 100;
        D_800C7960[i].obj->x = a->x;
        D_800C7960[i].obj->y = a->y;
        D_800C7960[i].obj->z = a->z;
    }

    for (i = 0; i < D_8007CC0C; i++) {
        if (D_800C8450[i] == 0) {
            continue;
        }
        D_800C7960[i].obj->vida = 1;
        if (D_800C8450[i] == 2) {
            D_800C7960[i].recogido->fin = 2;
        } else {
            D_800C7960[i].recogido->fin = 0;
        }
        n = D_8007CC0C - 1;
        if (i < n) {
            /* corre las de atras un lugar hacia adelante */
            for (j = i, k = i + 1; j < n; j++, k++) {
                de = (s32 *)&D_800C7960[k];
                a_ = (s32 *)&D_800C7960[j];
                for (d = 14; d > 0; d--) {
                    *a_++ = *de++;
                }
                D_800C8450[j] = D_800C8450[k];
            }
            D_8007CC0C--;
            i--;
        } else {
            D_8007CC0C = n;
        }
    }
}

extern void *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                            s32 d, s32 e, s32 vida, s32 f, s32 g);

/* Anota el objeto recogible al final de la lista (posicion, velocidad, escala, giro, estado y su registro
 * de WRLDDATA) y le crea la particula que lo va a mostrar segun su tipo (4, 0x12, 0x13 y 0x17). Devuelve cuantas hay ahora. */
s32 RegistrarRecogible(Objeto *o) {
    Anotado *a = &D_800C7960[D_8007CC0C];
    u8 *extra = (u8 *)o + 0x74;
    ObjAnotado *p;

    a->x = o->x;
    a->y = o->y;
    a->z = o->z;
    D_800C7960[D_8007CC0C].vel[0] = o->empuje_x;
    D_800C7960[D_8007CC0C].vel[1] = o->vel_y;
    D_800C7960[D_8007CC0C].vel[2] = o->empuje_z;
    D_800C7960[D_8007CC0C].escala[0] = o->escala[0];
    D_800C7960[D_8007CC0C].escala[1] = o->escala[1];
    D_800C7960[D_8007CC0C].escala[2] = o->escala[2];
    D_800C7960[D_8007CC0C].giro_y = o->rot[1];
    D_800C7960[D_8007CC0C].extra0 = *(s32 *)extra;
    D_800C7960[D_8007CC0C].extra4 = *(s8 *)(extra + 4);
    D_800C7960[D_8007CC0C].forma = o->estado;
    D_800C7960[D_8007CC0C].y0 = o->y;
    switch (o->tipo) {
    case 4:
        p = CrearParticula(0x15, o, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3E80, 0, 0);
        D_800C7960[D_8007CC0C].obj = p;
        break;
    case 0x12:
        p = CrearParticula(0x16, o, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3E80, 0, 0);
        D_800C7960[D_8007CC0C].obj = p;
        break;
    case 0x13:
        p = CrearParticula(0x17, o, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3E80, 0, 0);
        D_800C7960[D_8007CC0C].obj = p;
        break;
    case 0x17:
        p = CrearParticula(0x18, o, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3E80, 0, 0);
        D_800C7960[D_8007CC0C].obj = p;
        break;
    }
    D_800C7960[D_8007CC0C].obj->_24 = 0x8000;
    D_800C7960[D_8007CC0C].obj->vida = 100;
    D_800C7960[D_8007CC0C].obj->banderas |= 0x800;
    D_800C7960[D_8007CC0C].recogido = o->datos;
    D_8007CC0C++;
    return D_8007CC0C;
}
