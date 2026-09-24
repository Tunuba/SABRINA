#include "banco.h"

/* Afirmar(cond, archivo, linea): si cond es 0 avisa del fallo. */
extern s32 Afirmar(s32 cond, const char *archivo, s32 linea);
extern char D_800758EC[];            /* nombre del archivo fuente (membank.cpp) */

s32 func_8004E2A4(u32 tam);
Bloque *func_8004E8C4(Banco *b, Bloque *bl);
void func_8004E86C(Banco *b, Bloque *bl, s32 clase);

/* Palabra guardada sin alinear: el juego escribe asi la copia del tamano al final del bloque. */
typedef struct {
    s32 v;
} __attribute__((packed)) PalabraSuelta;

/* Direccion de la copia del tamano al final del bloque (cab lleva el bit de ocupado, por eso el -5). */
#define PIE(bl, cab) ((u8 *)(bl) + (cab) - 5)

/* Libera el bloque cuyo espacio de usuario empieza en p: repara la copia del tamano del final, lo junta
 * con los vecinos libres y lo pone en la lista de su clase. Devuelve la cabecera que tenia (tamano | 1). */
s32 func_8004E618(Banco *b, void *p) {
    Bloque *bl = (Bloque *)((u8 *)p - 4);
    s32 cab;
    s32 *pie;

    Afirmar((bl->cab & 1) != 0, D_800758EC, 0x113);
    cab = bl->cab;
    pie = (s32 *)PIE(bl, cab);
    if (cab != *pie) {
        *pie = cab;
    }
    bl = func_8004E8C4(b, bl);
    func_8004E86C(b, bl, func_8004E2A4(bl->cab));
    return cab;
}

/* Saca un bloque libre de la clase pedida o, si esta vacia, de la primera clase mayor que tenga alguno
 * (hasta la 0x38). Lo marca ocupado y lo descuenta de lo libre. NULL si no hay. */
Bloque *func_8004E774(Banco *b, s32 clase) {
    Bloque *bl = b->libres[clase];
    Bloque *sig;

    while (bl == NULL && clase < 0x38) {
        clase++;
        bl = b->libres[clase];
    }
    if (bl != NULL) {
        b->libres[clase] = bl->sig;
        sig = bl->sig;
        if (sig != NULL) {
            sig->ant = NULL;
        }
        b->libre -= bl->cab;
        bl->cab |= 1;
    }
    return bl;
}

/* Pone el bloque al principio de la lista de libres de su clase, lo marca libre y lo suma a lo libre. */
void func_8004E86C(Banco *b, Bloque *bl, s32 clase) {
    Bloque *primero = b->libres[clase];

    if (primero != NULL) {
        primero->ant = bl;
    }
    b->libres[clase] = bl;
    bl->sig = primero;
    bl->ant = NULL;
    bl->cab &= ~1;
    b->libre += bl->cab;
}

/* Saca un bloque libre de su lista, lo descuenta de lo libre y lo marca ocupado. */
static void quitar_libre(Banco *b, Bloque *v) {
    if (v->ant != NULL) {
        v->ant->sig = v->sig;
    } else {
        b->libres[func_8004E2A4(v->cab)] = v->sig;
    }
    if (v->sig != NULL) {
        v->sig->ant = v->ant;
    }
    b->libre -= v->cab;
    v->cab |= 1;
}

/* Junta el bloque (ocupado) con el de adelante y el de atras si estan libres. Devuelve el bloque que
 * queda (el de atras si se junto con el). Actualiza la copia del tamano del final. */
Bloque *func_8004E8C4(Banco *b, Bloque *bl) {
    Bloque *v;

    v = (Bloque *)((u8 *)bl + bl->cab - 1);
    if ((u8 *)v < b->fin && !(v->cab & 1)) {
        quitar_libre(b, v);
        bl->cab += v->cab - 1;
        ((PalabraSuelta *)PIE(bl, bl->cab))->v = bl->cab;
    }
    if (b->ini < (u8 *)bl) {
        v = (Bloque *)((u8 *)bl - ((s32 *)bl)[-1] + 1);
        if (!(v->cab & 1)) {
            quitar_libre(b, v);
            v->cab += bl->cab - 1;
            ((PalabraSuelta *)PIE(v, v->cab))->v = v->cab;
            bl = v;
        }
    }
    return bl;
}
