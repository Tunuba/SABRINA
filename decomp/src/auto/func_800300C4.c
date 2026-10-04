#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 vida_barra;


void func_800300C4(void) {
    s8 var_a0;

    var_a0 = 4;
    if (M2C_ERROR(/* Read from unset register $a0 */) != 0) {
        var_a0 = 0x14;
    }
    p_sabrina->vida += var_a0;
    if (p_sabrina->vida >= 0x15) {
        p_sabrina->vida = 0x14;
    }
    vida_barra = p_sabrina->vida;
    ActualizarBarraVida();
}
