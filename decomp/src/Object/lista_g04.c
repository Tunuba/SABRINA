#include "juego.h"

/* Reserva de 200 registros de 0x58 bytes en D_80086698: una lista de libres (D_8007CA90) y una de usados
 * (D_8007CA94 el primero, D_8007CA98 el ultimo), enlazados por la palabra 0. */

typedef struct Registro58 {
    struct Registro58 *sig;          /* 0x00 */
    u8 _04[0x54];
} Registro58;

extern Registro58 D_80086698[200];
extern Registro58 *D_8008AB00;       /* el sig del ultimo, D_80086698[199].sig */
extern Registro58 *D_8007CA90;       /* libres */
extern Registro58 *D_8007CA94;       /* usados: el primero */
extern Registro58 *D_8007CA98;       /* usados: el ultimo */
extern s32 D_8007CA8C;
extern s16 D_8007CA84;

extern void memset(void *p, s32 c, s32 n);

/* Saca un registro de los libres y lo pone al principio de los usados; si la lista de usados estaba vacia
 * tambien es el ultimo. NULL si no quedan. */
Registro58 *func_8001ED9C(void) {
    Registro58 *r = D_8007CA90;

    if (r == NULL) {
        return NULL;
    }
    D_8007CA90 = r->sig;
    r->sig = D_8007CA94;
    if (D_8007CA94 == NULL) {
        D_8007CA98 = r;
    }
    D_8007CA94 = r;
    return r;
}

/* Limpia los 200 registros y los encadena todos en la lista de libres. */
void func_8001F23C(void) {
    s32 i;

    for (i = 0; i < 200; i++) {
        memset(&D_80086698[i], 0, sizeof(Registro58));
        D_80086698[i].sig = &D_80086698[i + 1];
    }
    D_8007CA8C = 0;
    D_8008AB00 = NULL;
    D_8007CA90 = D_80086698;
    D_8007CA94 = NULL;
    D_8007CA98 = NULL;
    D_8007CA84 = 0;
}
