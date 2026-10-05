#include "juego.h"

/* Herramienta de desarrollo: carga la fuente nombre (func_8001B9C0) y manda a la PC, por el archivo arch, la
 * cantidad de letras (2 bytes) y despues 12 bytes por letra. El bloque de las letras no se libera. */

extern char D_8007C798[];               /* el nombre del archivo fuente */
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern s32 func_8001B9C0(u8 *letras, char *nombre);
extern s32 func_80029530(s32 arch, void *datos, s32 n);  /* PCwrite */

void func_80018CB8(char *nombre, s32 arch) {
    u8 *letras;
    u16 n;

    letras = Reservar(0x4B0, D_8007C798, 0x49);
    n = func_8001B9C0(letras, nombre);
    func_80029530(arch, &n, 2);
    func_80029530(arch, letras, n * 12);
}
