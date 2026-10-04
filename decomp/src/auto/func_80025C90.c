#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800909E8;
extern s32 D_800909EC;
extern s32 D_8006CFB8;
extern s32 D_8006CFBC;
extern s32 D_8006CFD4;
extern s32 D_8006CFD8;
extern s32 (*D_8006CF88)();


s32 func_80025C90(s32 arg0) {
    s32 temp_s1;

    temp_s1 = (D_8006CFD8 * 2) | (D_8006CFD4 == 0);
    if (temp_s1 != arg0) {
        D_8006CFBC = 0;
        if (arg0 & 1) {
            D_8006CFD4 = 0;
            if (D_800909E8 >= 0x96) {
                D_8006CF88(D_8006CFB8);
            }
            D_800909E8 = 0;
        } else {
            D_8006CFD4 = 1;
        }
        if (arg0 & 2) {
            D_8006CFD8 = 1;
            if (D_800909EC >= 0x96) {
                D_8006CF88(D_8006CFB8 + 0xF0);
            }
            D_800909EC = 0;
        } else {
            D_8006CFD8 = 0;
        }
        D_8006CFBC = 1;
    }
    return temp_s1;
}
