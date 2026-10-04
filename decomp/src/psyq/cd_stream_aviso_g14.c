#include "juego.h"

/* El aviso de "sector listo" del streaming: solo llama a la lectura (func_8002D714). Sin salto de cola: la
 * lectura copia 4 bytes de su pila sin inicializar (si D_80091478 no es 0) y con otro marco la basura cambia. */

extern void func_8002D714(void);

void func_8002CB00(void) {
    func_8002D714();
    __asm__ volatile("");
}
