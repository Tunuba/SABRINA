#include "dibujo.h"
#include "gte.h"
#include "nodo.h"

/* Un cuadro de la seccion 5 del .INO: el dibujito que usa cada particula. */
typedef struct {
    u8 _00[8];
    s16 ancho, alto;                 /* 0x08, tamano en el mundo, 0x1000 = 1.0 */
    u16 pagina;                      /* 0x0C */
    u16 paleta;                      /* 0x0E */
    u8 u0, v0;                       /* 0x10, esquina de arriba a la izquierda en la VRAM */
    u8 _12[10];
    u8 u1, v1;                       /* 0x1C, esquina de abajo a la derecha */
    u8 _1E[2];
} CuadroParticula;

typedef struct Particula {
    struct Particula *sig;           /* 0x00 */
    s32 x, y, z;                     /* 0x04, la posicion en el mundo, con 8 bits de decimales */
    u8 _10[12];
    u8 r, g, b;                      /* 0x1C */
    u8 _1F;
    CuadroParticula *cuadro;         /* 0x20 */
    s32 tamano;                      /* 0x24 */
    u8 banderas;                     /* 0x28, bit 2: se mezcla con lo que hay debajo */
    u8 _29[0x1B];
    s16 angulo;                      /* 0x44, cuanto gira el cuadrado en pantalla */
    s16 _46;
} Particula;

extern Matriz D_8008AB58;            /* la matriz de la camara */
extern Particula *D_8007CA8C;        /* las particulas vivas */
extern CuadroTex *D_8007CAC8;        /* donde se va armando la lista de dibujo */

/* Dibuja todas las particulas vivas: cada una es un cuadrado suelto que siempre mira a la camara, del
 * tamano que le toque por su distancia y girado su angulo. Las que quedan demasiado cerca o demasiado
 * lejos no se dibujan. */
void func_8001F6C8(u32 *lista) {
    Particula *p;
    CuadroParticula *cuadro;
    CuadroTex *pieza;
    union {
        s32 w[2];
        s16 h[4];
    } punto;
    s32 z;
    s16 escala, c, s;

    gte_poner_matriz(&D_8008AB58);
    gte_poner_traslacion(D_8008AB58.t);
    for (p = D_8007CA8C; p != NULL; p = p->sig) {
        punto.h[0] = p->x >> 8;
        punto.h[1] = p->y >> 8;
        punto.h[2] = p->z >> 8;
        gte_poner_v0(punto.w);
        gte_rtps();
        gte_guardar_sz3(&z);
        if (z < 0x81 || z >= 0x4000) {
            continue;
        }
        pieza = D_8007CAC8;
        gte_guardar_sxy2(&pieza->x0);
        cuadro = p->cuadro;
        escala = (s16) ((u32) p->tamano / (u32) z);
        c = (s16) ((escala * rcos(p->angulo)) >> 12);
        s = (s16) ((escala * rsin(p->angulo)) >> 12);
        /* las cuatro esquinas, girando el cuadrado alrededor del punto que salio del coprocesador */
        pieza->x1 = pieza->x0 + s;
        pieza->y1 = pieza->y0 - c;
        pieza->x2 = pieza->x0 - s;
        pieza->y2 = pieza->y0 + c;
        pieza->x3 = pieza->x0 + c;
        pieza->y3 = pieza->y0 + s;
        pieza->x0 = pieza->x0 - c;
        pieza->y0 = pieza->y0 - s;
        pieza->u0 = cuadro->u0;
        pieza->v0 = cuadro->v0;
        pieza->u1 = cuadro->u1;
        pieza->v1 = cuadro->v0;
        pieza->u2 = cuadro->u0;
        pieza->v2 = cuadro->v1;
        pieza->u3 = cuadro->u1;
        pieza->v3 = cuadro->v1;
        pieza->pagina = cuadro->pagina;
        pieza->paleta = cuadro->paleta;
        pieza->r = p->r;
        pieza->g = p->g;
        pieza->b = p->b;
        if (p->banderas & 4) {
            pieza->codigo |= 2;
        } else {
            pieza->codigo &= 0xFD;
        }
        D_8007CAC8 = pieza + 1;
        AddPrim(&lista[z >> 4], pieza);
    }
}
