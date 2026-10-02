#include "objeto.h"

/* Iniciar la puerta de un mundo: que hechizo da segun su numero (o a que nivel lleva desde el HUB), su
 * alcance, hacia donde mira y su ruta. */

typedef struct {
    s32 punto;                       /* 0x00, numero del punto de ruta (despues el puntero) */
    s32 tipo;                        /* 0x04 */
    s32 alcance;                     /* 0x08, al cuadrado */
    u8 _0C[4];
    s32 frente[3];                   /* 0x10 */
    s32 gana;                        /* 0x1C, 1 si al cruzarla se gana el mundo */
    s32 destino[3];                  /* 0x20, el punto siguiente */
} ExtraPuerta;

/* Un punto de ruta (0x18 bytes, en D_800D588C). */
typedef struct {
    s32 x, y, z;
    u8 _0C[2];
    s16 siguiente;                   /* 0x0E */
    u8 _10[8];
} PuntoPuerta;

extern Objeto *D_800C98C4[];         /* las puertas del nivel */
extern s32 D_8007CC1C;               /* cuantas */
extern s8 nivel_actual;
extern s8 D_800C8560;                /* el ultimo mundo abierto */
extern PuntoPuerta D_800D588C[];
extern void func_800249CC(Objeto *o, s32 n);
extern void func_8001C45C(s32 *v);   /* dejar el vector de largo 1 */

static s32 cuadrado(s32 v) {
    v >>= 8;
    return (v * v) >> 8;
}

void func_8004CB48(Objeto *o) {
    ExtraPuerta *e = (ExtraPuerta *)&o->extra;

    D_800C98C4[D_8007CC1C] = o;
    D_8007CC1C++;
    if (e->punto < 0) {
        e->punto = 0;
    }
    e->gana = 0;
    switch (e->tipo) {
    case 1:
        func_800249CC(o, 0xE);
        e->tipo = 1;
        o->estado = 1;
        e->alcance = cuadrado(0x50000);
        break;
    case 2:
        func_800249CC(o, 0xF);
        e->tipo = 4;
        e->alcance = cuadrado(0x50000);
        if (D_800C8560 >= 2) {
            o->estado = 1;
        }
        break;
    case 3:
        func_800249CC(o, 0x10);
        e->tipo = 7;
        e->alcance = cuadrado(0x50000);
        if (D_800C8560 >= 3) {
            o->estado = 1;
        }
        break;
    case 4:
        func_800249CC(o, 0x11);
        e->tipo = 0xA;
        e->alcance = cuadrado(0x50000);
        if (D_800C8560 >= 4) {
            o->estado = 1;
        }
        break;
    case 0:
    case 14:
        e->alcance = cuadrado(0x20000);
        func_800249CC(o, -1);
        o->estado = 2;
        switch (nivel_actual) {
        case 0:
            e->tipo = 0xD;
            break;
        case 1:
            e->tipo = 2;
            break;
        case 2:
            e->tipo = 3;
            break;
        case 3:
            e->tipo = 0xD;
            if (D_800C8560 < 2) {
                D_800C8560 = 2;
            }
            e->gana = 1;
            break;
        case 4:
            e->tipo = 5;
            break;
        case 5:
            e->tipo = 6;
            break;
        case 6:
            e->tipo = 0xD;
            if (D_800C8560 < 3) {
                D_800C8560 = 3;
            }
            e->gana = 1;
            break;
        case 7:
            e->tipo = 8;
            break;
        case 8:
            e->tipo = 9;
            break;
        case 9:
            e->tipo = 0xD;
            if (D_800C8560 < 4) {
                D_800C8560 = 4;
            }
            e->gana = 1;
            break;
        case 10:
            e->tipo = 0xB;
            break;
        case 11:
            e->tipo = 0xC;
            break;
        case 12:
            e->tipo = 0xD;
            if (D_800C8560 < 5) {
                D_800C8560 = 5;
            }
            e->gana = 1;
            break;
        }
        break;
    default:
        e->tipo = 0;
        break;
    }
    o->empuje_x = -o->x;
    o->vel_y = 0;
    o->empuje_z = -o->z;
    func_8001C45C(&o->empuje_x);
    e->frente[0] = o->empuje_x;
    e->frente[1] = o->vel_y;
    e->frente[2] = o->empuje_z;
    o->empuje_x *= 2;
    o->empuje_z *= 2;
    e->frente[0] >>= 4;
    e->frente[2] >>= 4;
    e->frente[0] = ((e->frente[0] * 0x3CC) >> 8) << 8;
    e->frente[2] = ((e->frente[2] * 0x3CC) >> 8) << 8;
    e->frente[1] = o->y;
    if (e->punto != 0) {
        PuntoPuerta *p = &D_800D588C[e->punto];

        e->punto = (s32)p;
        e->destino[0] = D_800D588C[p->siguiente].x;
        e->destino[1] = D_800D588C[p->siguiente].y;
        e->destino[2] = D_800D588C[p->siguiente].z;
    }
    *(s16 *)((u8 *)o->datos + 0x1A) = 2;
}

extern s32 thunk_FUN_8004866c(Objeto *o);

/* Saca la puerta de la lista (corriendo las de atras) y la borra. */
s32 func_8004DAC4(Objeto *o) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_800C98C4[i] == o) {
            D_800C98C4[i] = NULL;
            break;
        }
    }
    for (; i + 1 < 4; i++) {
        D_800C98C4[i] = D_800C98C4[i + 1];
    }
    D_8007CC1C--;
    return thunk_FUN_8004866c(o);
}
