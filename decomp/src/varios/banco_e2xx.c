#include "juego.h"

/* Piezas del banco de memoria (membank.cpp) del grupo e2xx. El resto del banco (func_8004E618 en
 * adelante) va en otro archivo. */

/* Del banco solo se usa aqui lo que lleva gastado, en +0xFC. */
typedef struct {
    u8 pad0[0xFC];
    s32 usado;                       /* 0xFC, bytes ocupados */
} Banco;
EN(Banco, usado, 0xFC);

extern s32 func_8004E618(Banco *banco, void *bloque);

/* Logaritmo en base 2 redondeado hacia abajo: la mayor n con 1 << n <= tam (tam 0 da -1). Con eso se
 * elige la lista de bloques libres por tamano. Si tam tiene el bit 31 no termina, igual que el juego. */
s32 func_8004E2A4(u32 tam) {
    u32 potencia = 1;
    s32 n = 0;

    while (!(tam < potencia)) {
        n++;
        potencia <<= 1;
    }
    return n - 1;
}

/* Libera un bloque del banco y descuenta su tamano de lo gastado. Un puntero nulo no hace nada y da 0. */
s32 func_8004E5D8(Banco *banco, void *bloque) {
    if (bloque != NULL) {
        banco->usado -= func_8004E618(banco, bloque);
        return banco->usado;
    }
    return 0;
}
