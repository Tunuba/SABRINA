#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007C872;
extern s16 D_8007CB70;


void func_80031000(void) {
    EstadoAnim *temp_a0;
    u16 *temp_a1;

    temp_a0 = p_sabrina->anim;
    temp_a1 = p_sabrina->animaciones;
    if (!(p_sabrina->forma.banderas & 0x8000)) {
        if (p_sabrina->vida > 0) {
            if (p_sabrina->extra._1D == 0) {
                temp_a0->animacion = (u8) M2C_FIELD(temp_a1, u16 *, 6);
                temp_a0->_50 = 0;
                temp_a0->_4E = 0x800;
                D_8007CB70 = 3;
            }
            p_sabrina->extra.espera_golpe = 0x1E;
            return;
        }
        temp_a0->animacion = (u8) M2C_FIELD(temp_a1, u16 *, 0);
        temp_a0->_50 = 0;
        temp_a0->_4E = 0x800;
        D_8007CB70 = 0;
        p_sabrina->extra._1A = -1;
        p_sabrina->extra._1B = -1;
        p_sabrina->estado = 2;
        D_8007C872 = 0;
    }
}
