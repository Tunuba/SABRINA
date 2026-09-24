#include "juego.h"

s8 func_80014B4C(s32 c);             /* letra minuscula a mayuscula */

/* Pasa la cadena a mayusculas en su lugar. */
void func_80017D3C(s8 *s) {
    while (*s != 0) {
        *s = func_80014B4C(*s);
        s++;
    }
}
