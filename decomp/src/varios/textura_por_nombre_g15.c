#include "juego.h"

/* La textura de ese nombre: la da el gancho D_8007CA44 si hay uno y si no func_8001B0C8 (la lee del .TGA). Si
 * todavia no tiene nombre guardado (+4), le guarda una copia. */

typedef struct {
    u8 _0[4];
    char *nombre;                       /* 0x4 */
} Textura;

extern Textura *(*D_8007CA44)(char *nombre);
extern char D_800686C4[];               /* el nombre del archivo fuente */
extern Textura *func_8001B0C8(char *nombre);
extern s32 func_800150F0(char *s);      /* strlen */
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern char *strcpy(char *d, const char *s);

Textura *func_8001B600(char *nombre) {
    Textura *t;

    if (D_8007CA44 != 0) {
        t = D_8007CA44(nombre);
    } else {
        t = func_8001B0C8(nombre);
    }
    if (t != 0 && t->nombre == 0) {
        t->nombre = Reservar(func_800150F0(nombre) + 1, D_800686C4, 0x85);
        strcpy(t->nombre, nombre);
    }
    return t;
}
