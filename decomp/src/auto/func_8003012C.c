#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void * D_8007CB8C;


void func_8003012C(void) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(D_8007CB8C, void **, 0x1C);
    M2C_FIELD(temp_v1, s8 *, 0x51) = (s8) M2C_FIELD(M2C_FIELD(D_8007CB8C, void **, 0x64), u16 *, 0x1C);
    M2C_FIELD(temp_v1, s8 *, 0x50) = 0;
    M2C_FIELD(temp_v1, s16 *, 0x4C) = 0x1000;
}
