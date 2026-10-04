#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80053038(s32 arg0) {
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    void *temp_s0;

    temp_s0 = arg0 + 0x74;
    func_800486B8(arg0, 0x1E0000);
    if (M2C_FIELD(temp_s0, s32 *, 0x14) == 0) {
        temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
        switch (temp_v0) {                          /* irregular */
        case 0:
            if (M2C_FIELD(temp_s0, s32 *, 8) != 0) {
                M2C_FIELD(arg0, s16 *, 0x70) = 2;
                M2C_FIELD(temp_s0, s32 *, 0x10) = 1;
                M2C_FIELD(temp_s0, s32 *, 4) = 0x800;
                return;
            }
            break;
        case 1:
            temp_v0_2 = M2C_FIELD(temp_s0, s32 *, 8);
            if (temp_v0_2 == 0) {
                M2C_FIELD(arg0, s16 *, 0x70) = 2;
                M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
                M2C_FIELD(temp_s0, s32 *, 4) = 0x800;
                return;
            }
            M2C_FIELD(temp_s0, s32 *, 8) = (s32) (temp_v0_2 - 1);
            return;
        case 2:
            temp_v0_3 = M2C_FIELD(temp_s0, s32 *, 4);
            if (temp_v0_3 != 0) {
                M2C_FIELD(temp_s0, s32 *, 4) = (s32) (temp_v0_3 - 0x40);
                M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) - 0x40);
                return;
            }
            M2C_FIELD(arg0, s16 *, 0x70) = (s16) M2C_FIELD(temp_s0, s32 *, 0x10);
            break;
        }
    }
}
