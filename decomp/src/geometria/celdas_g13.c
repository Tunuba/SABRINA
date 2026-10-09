#include "objeto.h"

/* Dibujar las celdas de la cuadricula del nivel que se ven desde la camara. */

/* Una celda de la cuadricula del nivel (12 bytes, en D_8007CA48). */
typedef struct {
    s16 _00;                         /* 0x00, -1 si esta vacia */
    u8 _02[6];
    u32 zona;                        /* 0x08 */
} CeldaVista;

extern s16 **D_8006C240[];           /* por tabla: 32 listas (una por rumbo) de corrimientos (z, x), fin 0x7F */
extern u16 D_8007CAE2;               /* rumbo de la camara */
extern s32 D_8006C444[3];            /* el ojo de la camara */
extern CeldaVista *D_8007CA48;
extern void *D_8008AB78[];           /* los nodos de las piezas, 0xF0 */
extern s32 BitDeZona(s32 celda);
extern Objeto *D_8007CAFC;           /* el objeto camara; en su extra +0x20 la camara libre (MOD) */
extern s32 func_800207AC(s32 a, void *nodo, CeldaVista *c);  /* arma el dibujo de una celda */
extern s32 func_80020764(s32 i);     /* deja sin dibujo los nodos que sobran */

/* Recorre los corrimientos de la tabla para el rumbo de la camara y arma con un nodo nuevo cada celda que
 * no este vacia y cuya zona este entre la mitad y el doble (si cabe) de la de Sabrina. Despues apaga los
 * nodos que no se usaron. */
s32 DibujarCeldasVisibles(s32 *a, s32 tabla) {
    s16 *d = D_8006C240[tabla][((s16)(D_8007CAE2 >> 7) + 0x18) & 0x1F];
    s32 x, z, b;
    u32 alto, bajo, celda;
    CeldaVista *c;
    s16 n = 0;
    Objeto *ref;
    s32 dx, dz;

    b = a[1];
    /* MOD: con la camara libre la zona sale de la celda de la camara, no de la de Sabrina. */
    ref = (D_8007CAFC != NULL && *((u8 *)D_8007CAFC + 0x74 + 0x20) != 0) ? D_8007CAFC : p_sabrina;
    x = (s16)(((ref->x >> 16) + 0x80) >> 2);
    z = (s16)((~((ref->z >> 16) + 0x80) & 0xFF) >> 2);
    alto = BitDeZona(((z << 6) + x) & 0xFFFF) & 0xFFFF;
    bajo = (alto >> 1) & 0xFFFF;
    if (alto < 0x8000) {
        alto = (alto << 1) & 0xFFFF;
    }
    x = (s16)(((D_8006C444[0] >> 8) + 0x80) >> 2);
    z = (s16)((~((D_8006C444[2] >> 8) + 0x80) & 0xFF) >> 2);
    do {
        dz = d[0];
        dx = d[1];
        d += 2;
        celda = (((z + dz) << 6) + (x + dx)) & 0xFFFF;
        if (celda < 0x1000) {
            c = &D_8007CA48[celda];
            if (c->zona >= bajo && alto >= c->zona && c->_00 != -1) {
                func_800207AC(b, D_8008AB78[n], c);
                n++;
            }
        }
    } while (*d != 0x7F);
    return func_80020764(n & 0xFFFF);
}
