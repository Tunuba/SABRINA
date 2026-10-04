#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D5818[];
extern s16 D_800D584E;
extern u8 D_80075B78[];
extern u8 D_80075B8C[];
extern s32 D_8007CC8C;


void func_8005D02C(s32 arg0) {
    s32 temp_v0;

    if (arg0 != 0) {
        D_800D584E ^= 1;
        temp_v0 = DecDCTvlc2(arg0, M2C_FIELD((D_800D5818 + (D_800D584E * 4)), s32 *, 0x3C), D_8007CC8C);
        if (temp_v0 != 0) {
            if (temp_v0 == 1) {
                printf((s32) "Incomplete decode\n");
            } else {
                printf((s32) "Failed decode\n");
            }
        }
        StFreeRing(arg0);
    }
}
