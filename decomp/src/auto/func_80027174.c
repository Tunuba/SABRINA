#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 (*D_8006CFA0)();
extern s32 func_80026778();
extern s32 func_80026820();


void func_80027174(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_a1_2;

    if (arg1 != 0) {
        if (M2C_FIELD(arg0, s32 *, 4) == 0) {
            if (D_8006CFA0() != 0) {

            } else {
                M2C_FIELD(arg0, s8 *, 0x49) = 4;
                M2C_FIELD(arg0, s8 *, 0x46) = 1;
                M2C_FIELD(arg0, s32 (**)(s32), 0x14) = func_80026778;
                M2C_FIELD(arg0, s32 (**)(s32), 0x18) = func_80026820;
                temp_a1 = ((s32) (arg1 + 3) >> 2) * 4;
                M2C_FIELD(arg0, s32 *, 0) = temp_a1;
                M2C_FIELD(arg0, s8 *, 0x47) = 0;
                temp_a1_2 = temp_a1 + (((s32) (M2C_FIELD(arg0, u8 *, 0xE3) + 1) >> 1) * 4);
                M2C_FIELD(arg0, s32 *, 4) = temp_a1_2;
                M2C_FIELD(arg0, s32 *, 8) = (s32) (temp_a1_2 + (((M2C_FIELD(arg0, u8 *, 0xE9) * 5) + 3) & 0xFFC));
            }
        }
    }
}
