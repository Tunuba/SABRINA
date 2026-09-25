#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 vida_barra;
extern s16 D_8007CB1E;


void ActualizarBarraVida(void) {
    if (vida_barra < 0) {
        vida_barra = 0;
    }
    D_8007CB1E = vida_barra * 6;
    if (vida_barra == 0x14) {
        D_8007CB1E = 0x80;
    }
    if (D_8007CB1E < 0) {
        D_8007CB1E = 0;
    }
}
