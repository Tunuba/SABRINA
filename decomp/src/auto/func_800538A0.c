#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C8582;

void func_800538A0(void *arg0) {
    s16 temp_v0;
    void *temp_a1;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
    temp_a1 = arg0 + 0x74;
    if (D_800C8582 == 0) {
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 5);
        if (M2C_FIELD(arg0, s16 *, 0x32) >= 0x1000) {
            M2C_FIELD(arg0, s16 *, 0x32) = 0;
        }
        temp_v0 = M2C_FIELD(temp_a1, s16 *, 6);
        if (temp_v0 >= 0) {
            M2C_FIELD(temp_a1, s16 *, 6) = (s16) (temp_v0 - 1);
            if (M2C_FIELD(temp_a1, s16 *, 6) == 0) {
                M2C_FIELD(arg0, s16 *, 0x114) = (s16) M2C_FIELD(temp_a1, s16 *, 8);
                M2C_FIELD(arg0, s16 *, 0x112) = (s16) M2C_FIELD(temp_a1, s16 *, 0xA);
                M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) + M2C_FIELD(temp_a1, s16 *, 4));
                M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) + M2C_FIELD(temp_a1, s16 *, 4));
                M2C_FIELD(arg0, s32 *, 0x5C) = (s32) (M2C_FIELD(arg0, s32 *, 0x5C) + M2C_FIELD(temp_a1, s16 *, 4));
                M2C_FIELD(arg0, s32 *, 0xF8) = (s32) (M2C_FIELD(arg0, s32 *, 0xF8) + 0x6666);
                if (M2C_FIELD(arg0, s32 *, 0x54) >= 0x1000) {
                    M2C_FIELD(arg0, s32 *, 0x54) = 0x1000;
                    M2C_FIELD(arg0, s32 *, 0x58) = 0x1000;
                    M2C_FIELD(arg0, s32 *, 0x5C) = 0x1000;
                    M2C_FIELD(arg0, s32 *, 0xF8) = 0x18000;
                }
            }
        } else if (M2C_FIELD(arg0, s32 *, 0x54) < 0xFFF) {
            M2C_FIELD(temp_a1, s16 *, 6) = 0x280;
        }
    }
}
