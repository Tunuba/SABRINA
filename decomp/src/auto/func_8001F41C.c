#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CA88;


void func_8001F41C(s32 arg0) {
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x49);
    M2C_FIELD(arg0, u8 *, 0x49) = (u8) (temp_v1 - 1);
    if (temp_v1 == 0) {
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x4C);
        if (temp_v1_2 >= (u8) M2C_FIELD(arg0, u8 *, 0x4A)) {
            if (M2C_FIELD(arg0, u16 *, 0x42) & 0x800) {
                M2C_FIELD(arg0, u8 *, 0x4C) = 0U;
            } else {
                M2C_FIELD(arg0, s16 *, 0x40) = -1;
            }
        } else {
            M2C_FIELD(arg0, u8 *, 0x4C) = (u8) (temp_v1_2 + 1);
        }
        M2C_FIELD(arg0, u8 *, 0x49) = (u8) M2C_FIELD(arg0, u8 *, 0x48);
    }
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (D_8007CA88 + ((M2C_FIELD(arg0, u8 *, 0x4C) + M2C_FIELD(arg0, u8 *, 0x4B)) << 5));
}
