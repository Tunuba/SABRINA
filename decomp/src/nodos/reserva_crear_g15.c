#include "nodo.h"

/* Crea la reserva fija de nodos (BasicTools.c): un solo bloque de 950 nodos de 0x6C bytes, en cero, y en
 * D_80084CE0[i] el puntero a cada uno; cada nodo guarda su numero en +0x62. */

#define NODOS_RESERVA 0x3B6

extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void *memset(void *p, s32 c, u32 n);
extern char D_800653F8[];               /* "BasicTools.c" */
extern Nodo *D_80084CE0[NODOS_RESERVA];

void func_80018218(void) {
    u8 *p;
    s16 i;

    p = Reservar(NODOS_RESERVA * 0x6C, D_800653F8, 0x142);
    memset(p, 0, NODOS_RESERVA * 0x6C);
    for (i = 0; i != NODOS_RESERVA; i++) {
        D_80084CE0[i] = (Nodo *) p;
        p += 0x6C;
        *(s16 *) &D_80084CE0[i]->_60[2] = i;
    }
}
