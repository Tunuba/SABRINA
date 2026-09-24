#include "juego.h"

/* Consulta de suelo: la posicion que se prueba y, al volver, el punto de contacto y la normal del
 * triangulo. La llena func_8003AF9C. */
typedef struct {
    s32 x, y, z;
    u8 _0C[0x24];
    s32 punto_x;                     /* 0x30 */
    s32 altura;                      /* 0x34, y del punto de contacto */
    s32 punto_z;                     /* 0x38 */
    s32 normal[3];                   /* 0x3C */
    s16 _48;
    s16 _4A;
} ConsultaSuelo;

/* Una celda de la cuadricula de colision: cuantos triangulos tiene y sus indices. */
typedef struct {
    s16 n;
    s16 _02;
    s16 *indices;
} CeldaColision;

extern CeldaColision *D_8007CBCC;    /* cuadricula de colision del nivel */
extern void **D_8007C9F8;

extern s32 CeldaDePosicion(s32 x, s32 z);
extern s32 D_8007CBC4;               /* cantidad de celdas de la cuadricula */
extern ConsultaSuelo D_800C6594;     /* consulta que se prueba con func_8003AE84 */
extern u8 D_8007CBD6;                /* su resultado */

extern s32 func_8003AF9C(ConsultaSuelo *c, void *triangulos, s32 n, s16 *indices);
extern u8 func_8003A94C(ConsultaSuelo *c, void *triangulos, s32 n, s16 *indices);

/* Busca el suelo bajo la posicion entre los triangulos (de 28 bytes) de su celda. */
s32 func_8003AF48(ConsultaSuelo *c) {
    CeldaColision *celda = &D_8007CBCC[CeldaDePosicion(c->x, c->z)];

    return func_8003AF9C(c, *(void **)((u8 *)D_8007C9F8[1] + 0x58), celda->n, celda->indices);
}

/* Altura del suelo bajo pos; si no hay suelo, la altura de pos. */
s32 func_800223E8(s32 *pos) {
    ConsultaSuelo c;

    c.x = pos[0];
    c.y = pos[1];
    c.z = pos[2];
    if (func_8003AF48(&c)) {
        return c.altura;
    }
    return pos[1];
}

/* Prueba la consulta global D_800C6594 contra los triangulos de su celda (si la posicion cae dentro de la
 * cuadricula) y deja el resultado en D_8007CBD6. */
u8 func_8003AE84(void) {
    ConsultaSuelo c = D_800C6594;
    s32 i;

    D_8007CBD6 = 0;
    i = CeldaDePosicion(c.x, c.z);
    if (i >= 0 && i < D_8007CBC4) {
        CeldaColision *celda = &D_8007CBCC[i];

        D_8007CBD6 = func_8003A94C(&c, *(void **)((u8 *)D_8007C9F8[1] + 0x58), celda->n, celda->indices);
    }
    D_800C6594 = c;
    return D_8007CBD6;
}
