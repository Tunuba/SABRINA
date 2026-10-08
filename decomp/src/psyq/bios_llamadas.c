#include "juego.h"

/* Llamadas a la BIOS y setjmp de la biblioteca de PsyQ (08-10). En la biblioteca son asm: cada llamada a la
 * BIOS salta a la tabla A (0xA0) con el numero de la funcion en t1. En C el numero va en t1 con una variable
 * de registro y la llamada sale como salto al final (la BIOS vuelve directo al que llamo). */

typedef void *(*BiosA)(s32 a0, s32 a1, s32 a2, s32 a3);

#define LLAMAR_A(numero, a0, a1, a2, a3)                                         \
    do {                                                                          \
        register s32 _t1 asm("$9") = (numero);                                    \
        __asm__ volatile("" : : "r"(_t1));                                        \
        return ((BiosA)0xA0)((a0), (a1), (a2), (a3));                             \
    } while (0)

/* A(72h) CdRemove: quita el manejador de CD de la BIOS. */
void *func_800142FC(s32 a0, s32 a1, s32 a2, s32 a3) {
    LLAMAR_A(0x72, a0, a1, a2, a3);
}

/* A(33h) malloc. */
void *func_800161BC(s32 a0, s32 a1, s32 a2, s32 a3) {
    LLAMAR_A(0x33, a0, a1, a2, a3);
}

/* A(34h) free. */
void *func_800161C8(s32 a0, s32 a1, s32 a2, s32 a3) {
    LLAMAR_A(0x34, a0, a1, a2, a3);
}
