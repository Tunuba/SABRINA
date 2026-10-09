#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80052388(void) {
    StopCARD2();
    func_800523B4();
    /* 08-10: la original llama con jal y func_800523B4 guarda ese ra en D_800D53C0; sin esto GCC salta al final
     * ya sin marco y lo guardado es el ra del que llamo (el verificador reubica el ra de cada llamada) */
    __asm__ volatile("");
}
