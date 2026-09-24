#include "nodo.h"

/* Reserva fija de 950 nodos. Los libres forman una lista: D_80085BB8[i] es el siguiente libre despues de i y
 * D_8007CA08 el primero. D_8007CA0A cuenta los que estan en uso. */

#define NODOS_RESERVA 0x3B6

int printf(const char *formato, ...);
void Liberar(void *p);

extern Nodo *D_80084CE0[NODOS_RESERVA];
extern s16 D_80085BB8[NODOS_RESERVA];
extern s16 D_8007CA08;                  /* primer nodo libre (NODOS_RESERVA: no queda ninguno) */
extern s16 D_8007CA0A;                  /* nodos en uso */
extern char D_80065454[];               /* "Out of Elements \n" */

/* Lo que el nodo tiene pedido a la memoria. */
#define NODO_MEMORIA(n) (*(void **)&(n)->_00[0])  /* 0x00, se libera si banderas & 4 */
#define NODO_EXTRA(n) (*(void **)&(n)->_54[0])    /* 0x54, se libera con el dibujo si banderas & 8 */
/* Del triangulo (28 bytes) solo se mira la textura y en ella el s16 de +8. */
#define TEXTURA_USO(t) (*(s16 *)((u8 *)(t) + 8))

/* Arma la lista de libres con todos los nodos y suelta lo que cada uno tenia pedido. */
void func_800182A8(void) {
    s16 i;
    s16 j;
    Nodo *n;
    u8 *tri;

    for (i = 0; i != NODOS_RESERVA; i++) {
        D_80085BB8[i] = i + 1;
        n = D_80084CE0[i];
        if (n->banderas & 8) {
            tri = n->dibujo;
            for (j = 0; j != n->triangulos; j++) {
                if (TEXTURA_USO(*(void **)(tri + 0xC)) != 0) {
                    TEXTURA_USO(*(void **)(tri + 0xC)) = 0;
                    Liberar(*(void **)(tri + 0xC));
                }
                tri += 0x1C;
            }
            Liberar(n->dibujo);
            Liberar(NODO_EXTRA(n));
        }
        if (n->banderas & 4) {
            Liberar(NODO_MEMORIA(n));
        }
        n->dibujo = NULL;
        NODO_EXTRA(n) = NULL;
        n->banderas = 0;
        NODO_MEMORIA(n) = NULL;
    }
    D_8007CA08 = 0;
    D_8007CA0A = 0;
}

/* Saca un nodo de la lista de libres. Si no queda ninguno avisa y se cuelga. */
Nodo *func_80018408(void) {
    s16 i;
    Nodo *n;

    i = D_8007CA08;
    if (i == NODOS_RESERVA) {
        printf(D_80065454);
        for (;;) {
        }
    }
    n = D_80084CE0[i];
    D_8007CA08 = D_80085BB8[i];
    D_8007CA0A++;
    return n;
}

/* Devuelve el nodo i a la lista de libres y suelta lo que tenia pedido. */
void func_80018488(s32 i) {
    D_80085BB8[i] = D_8007CA08;
    D_8007CA08 = i;
    if (D_80084CE0[i]->banderas & 8) {
        Liberar(D_80084CE0[i]->dibujo);
        Liberar(NODO_EXTRA(D_80084CE0[i]));
    }
    if (D_80084CE0[i]->banderas & 4) {
        Liberar(NODO_MEMORIA(D_80084CE0[i]));
    }
    D_80084CE0[i]->dibujo = NULL;
    NODO_EXTRA(D_80084CE0[i]) = NULL;
    D_80084CE0[i]->banderas = 0;
    NODO_MEMORIA(D_80084CE0[i]) = NULL;
    D_8007CA0A--;
}
