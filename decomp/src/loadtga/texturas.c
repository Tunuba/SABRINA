#include "juego.h"

/* Lista enlazada de las texturas cargadas. */
typedef struct NodoTextura {
    s32 textura;
    struct NodoTextura *siguiente;
} NodoTextura;

extern NodoTextura *D_8007CA40;      /* primera de la lista */
extern char D_800686D0[];            /* mensaje de error */
extern s32 printf(const char *fmt, ...);

/* Textura numero i de la lista (desde 0). Si la lista se acaba antes avisa y devuelve 0. */
s32 TexturaPorIndice(s32 i) {
    NodoTextura *t = D_8007CA40;

    while (i--) {
        if (t == NULL) {
            printf(D_800686D0);
            return 0;
        }
        t = t->siguiente;
    }
    return t->textura;
}
