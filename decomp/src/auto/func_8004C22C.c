#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C857E;
extern s8 D_800C857F;
extern s8 D_800C8580;
extern s8 D_800C8581;
extern void * D_8007C9F8;
extern s8 nivel_actual;
extern u16 D_8007CBD4;


void func_8004C22C(void) {
    s32 var_s0;
    s32 var_s1;
    s32 var_v1;
    u16 var_v0;
    void *temp_a0;
    void *temp_a1;
    void *temp_v1;

    var_v1 = 0;
    switch (nivel_actual) {                         /* irregular */
    case 1:
        if (D_800C857E != 0) {
block_11:
            var_v1 = 1;
        }
        break;
    case 4:
        if (D_800C857F != 0) {
            goto block_11;
        }
        break;
    case 7:
        if (D_800C8580 != 0) {
            goto block_11;
        }
        break;
    case 10:
        if (D_800C8581 != 0) {
            goto block_11;
        }
        break;
    }
    if (var_v1 != 0) {
        var_s0 = 0;
        var_s1 = 0;
loop_17:
        temp_v1 = M2C_FIELD(D_8007C9F8, void **, 4);
        if (var_s0 < M2C_FIELD(temp_v1, s16 *, 0x5E)) {
            temp_a0 = M2C_FIELD(temp_v1, s32 *, 0x58) + var_s1;
            if (M2C_FIELD(temp_a0, u16 *, 0x16) & 0x80) {
                temp_a1 = M2C_FIELD(temp_a0, void **, 0xC);
                M2C_FIELD(temp_a1, u8 *, 0x1C) = (u8) (M2C_FIELD(temp_a1, u8 *, 0x1C) & ~1);
                func_80053A64(M2C_FIELD(temp_a0, s32 *, 0));
            }
            var_s0 += 1;
            var_s1 += 0x1C;
            goto loop_17;
        }
        var_v0 = D_8007CBD4 & ~0x80;
    } else {
        var_v0 = D_8007CBD4 | 0x80;
    }
    D_8007CBD4 = var_v0;
}
