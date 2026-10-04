#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CB70;
extern void * D_8007CB8C;


void func_80030EC8(void) {
    EstadoAnim *temp_a0;
    void *temp_a1;

    temp_a1 = M2C_FIELD(D_8007CB8C, void **, 0x1C);
    temp_a0 = p_sabrina->anim;
    temp_a0->animacion = (u8) M2C_FIELD(p_sabrina->animaciones, u16 *, 0x32);
    temp_a0->_50 = 0;
    temp_a0->_4E = 0x800;
    M2C_FIELD(temp_a1, s8 *, 0x51) = (s8) M2C_FIELD(M2C_FIELD(D_8007CB8C, void **, 0x64), u16 *, 0x32);
    M2C_FIELD(temp_a1, s8 *, 0x50) = 0;
    M2C_FIELD(temp_a1, s16 *, 0x4E) = 0x800;
    D_8007CB70 = 0x19;
}
