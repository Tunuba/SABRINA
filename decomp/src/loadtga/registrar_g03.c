#include "juego.h"

/* loadtga.c: lista enlazada de las texturas cargadas (la misma que recorre TexturaPorIndice). */

typedef struct NodoTextura {
    s32 textura;
    struct NodoTextura *siguiente;
} NodoTextura;

extern NodoTextura *D_8007CA40;      /* primera de la lista */
extern char D_800686C4[];            /* "loadtga.c" */
extern void *Reservar(s32 tam, char *archivo, s32 linea);

/* Agrega la textura al final de la lista si no estaba. */
void RegistrarTextura(s32 textura) {
    NodoTextura *n;

    if (textura == 0) {
        return;
    }
    n = D_8007CA40;
    if (n == NULL) {
        D_8007CA40 = Reservar(sizeof(NodoTextura), D_800686C4, 0x44);
        D_8007CA40->siguiente = NULL;
        D_8007CA40->textura = textura;
        return;
    }
    while (n->textura != textura && n->siguiente != NULL) {
        n = n->siguiente;
    }
    if (n->textura != textura) {
        n->siguiente = Reservar(sizeof(NodoTextura), D_800686C4, 0x4F);
        n->siguiente->siguiente = NULL;
        n->siguiente->textura = textura;
    }
}
