#include "juego.h"

/* Herramienta de desarrollo: las texturas ya cargadas por nombre, en una lista (D_8007CA3C). Si el nombre
 * ya esta devuelve su textura; si no, la carga con func_8001B0C8 y la agrega al principio. */

typedef struct TexCargada {
    void *tex;                          /* 0x00 */
    char *nombre;                       /* 0x04, copia */
    struct TexCargada *sig;             /* 0x08 */
} TexCargada;

extern TexCargada *D_8007CA3C;
extern char D_800686C4[];               /* el nombre del archivo fuente, para Reservar */

extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern s32 strcmp(const char *a, const char *b);
extern char *strcpy(char *d, const char *s);
extern s32 func_800150F0(char *s);      /* strlen */
extern void *func_8001B0C8(char *nombre);

/* func_8001B0C8 imprime valores que lee de la pila sin llenar, asi que este marco tiene que ser como el del
 * original (solo s0 y s1): las direcciones se arman con asm para que GCC no las guarde en registros. */
#define DIR(x) ({ void *_d; __asm__ volatile("la %0, " #x : "=r"(_d)); _d; })

void *func_8001B000(char *nombre) {
    TexCargada *t;

    for (t = D_8007CA3C; t != NULL; t = t->sig) {
        if (strcmp(t->nombre, nombre) == 0) {
            return t->tex;
        }
    }
    t = Reservar(0xC, DIR(D_800686C4), 0x1F);
    t->nombre = Reservar(func_800150F0(nombre) + 1, DIR(D_800686C4), 0x20);
    strcpy(t->nombre, nombre);
    t->tex = func_8001B0C8(nombre);
    t->sig = *(TexCargada **) DIR(D_8007CA3C);
    *(TexCargada **) DIR(D_8007CA3C) = t;
    return t->tex;
}
