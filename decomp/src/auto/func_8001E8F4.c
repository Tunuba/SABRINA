#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 * D_8007CA80;


void func_8001E8F4(s32 arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;

    temp_v1 = D_8007CA80;
    D_8007CA80 = temp_v1 + 1;
    temp_v1_2 = D_8007CA80;
    D_8007CA80 = temp_v1_2 + 1;
    temp_v1_3 = D_8007CA80;
    D_8007CA80 = temp_v1_3 + 1;
    func_8001E7A8(arg0, (*temp_v1 * 0x10) & 0xFFFF, (*temp_v1_2 * 0x10) & 0xFFFF, (*temp_v1_3 * 0x10) & 0xFFFF);
    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0 != 0) {
        func_8001E8F4(temp_v0);
    }
    temp_v0_2 = M2C_FIELD(arg0, s32 *, 8);
    if (temp_v0_2 != 0) {
        func_8001E8F4(temp_v0_2);
    }
}
