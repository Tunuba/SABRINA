#include "juego.h"

/* Tabla de 128 entradas de 0x2C bytes en D_80091A80: una clave (0 = fin de la tabla) y un nombre en +8. */
typedef struct {
    s32 clave;
    s32 _04;
    char nombre[0x24];               /* 0x08 */
} EntradaNombre;

extern EntradaNombre D_80091A80[];
extern s32 D_8006D400;

extern s32 strcmp(const char *a, const char *b);
extern s32 func_80029A90(s32);

/* Busca la entrada con esa clave y ese nombre. Devuelve su indice mas uno, o -1 si llega a una clave 0
 * o al final de la tabla. */
s32 func_8002BAD4(s32 clave, const char *nombre) {
    s32 i;

    for (i = 0; i < 0x80; i++) {
        if (D_80091A80[i].clave == 0) {
            break;
        }
        if (D_80091A80[i].clave == clave && strcmp(nombre, D_80091A80[i].nombre) == 0) {
            return i + 1;
        }
    }
    return -1;
}

/* Llama a func_80029A90 con D_8006D400 y pone en cero la palabra anterior (D_8006D3FC). Deja en v0 lo
 * que devolvio func_80029A90 (solo se llega por punteros: no se sabe si alguien lo lee). */
s32 func_8002C160(void) {
    s32 *p = &D_8006D400;
    s32 r = func_80029A90(*p);

    p[-1] = 0;
    return r;
}
