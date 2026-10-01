#include "juego.h"

/* Contadores por bit (el "taillie system" de su mensaje). */

extern char D_800688C4[];            /* "\nValue unkown in taillie system\n" */
extern s32 printf(const char *formato, ...);

/* Suma uno al contador del bit pedido (0x1 a 0x8000, contadores de un byte desde c+1). Con 0 no hace
 * nada; con otro valor avisa. */
void func_80020818(s8 *c, s32 bit) {
    s32 i;

    if (bit == 0) {
        return;
    }
    for (i = 0; i < 16; i++) {
        if (bit == 1 << i) {
            c[i + 1]++;
            return;
        }
    }
    printf(D_800688C4);
}
