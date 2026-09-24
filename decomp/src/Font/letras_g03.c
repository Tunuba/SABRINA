#include "juego.h"

/* Font.c: textos que aparecen de a poco. D_800798BC es una tabla de punteros a lineas de texto; cada texto
 * es una tira de lineas seguidas que termina en NULL. En +4 cada linea lleva un contador (u16). */

typedef struct {
    u8 _00[4];
    u16 cuenta;                         /* 0x04 */
} LineaTexto;
EN(LineaTexto, cuenta, 0x04);

extern LineaTexto *D_800798BC[];        /* lineas de todos los textos */
extern u16 D_8007CA14;

/* Las dos recorren la tira hasta el NULL, pero tocan tambien el campo +4 de ese NULL (la direccion 4), como
 * el juego: el puntero se relee despues de mirarlo. GCC daria por hecho que un puntero ya usado no es NULL
 * y el bucle no terminaria, por eso se le quita esa suposicion. */
#define TOCA_NULL __attribute__((optimize("no-delete-null-pointer-checks")))

/* Pone en cero el contador de cada linea del texto que empieza en inicio. Devuelve cuantas lineas tiene
 * menos uno. */
TOCA_NULL u16 func_80019234(s32 inicio) {
    LineaTexto *l = D_800798BC[inicio];
    u16 i = 0;

    while (l != NULL) {
        l = D_800798BC[inicio + i];
        l->cuenta = 0;
        i++;
    }
    return i - 2;
}

/* Si D_8007CA14 es 0, la linea inicio + k arranca en 0xED8. Despues a cada linea del texto con contador
 * distinto de cero le resta 200. */
TOCA_NULL void func_80019374(s32 inicio, s32 k) {
    LineaTexto *l = D_800798BC[inicio + k];
    u16 i;

    if (D_8007CA14 == 0) {
        l->cuenta = 0xED8;
    }
    for (i = 0; l != NULL; i++) {
        l = D_800798BC[inicio + i];
        if (l->cuenta != 0) {
            l->cuenta -= 200;
        }
    }
}
