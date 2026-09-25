#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80090A98[];
extern s32 D_8006CFC4;
extern s32 D_8006CFC8;
extern s32 D_8006CFD8;
extern s32 D_8006CFDC[];
extern void * D_8006D014;
extern s32 D_8006D018[];


void func_80027DF0(s32 arg0) {
    s32 temp_v1;
    s32 var_a1;
    s32 var_v0;
    void *temp_a0;

    var_a1 = arg0;
    do {
        M2C_FIELD(D_8006D014, s16 *, 0xA) = 0;
        D_8006D018[D_8006CFC4] = var_a1;
        temp_a0 = (D_8006CFC4 * 0xF0) + D_80090A98;
        if (var_a1 != -9) {
            if (var_a1 == 0) {
                D_8006CFDC[D_8006CFC4] = (((u8) *M2C_FIELD(temp_a0, u8 **, 0x3C) >> 4) == 8) * 4;
            } else {
                func_80028D40((s32) temp_a0);
            }
        }
        D_8006CFC8 = 0;
        temp_v1 = D_8006CFC4 + 1;
        D_8006CFC4 = temp_v1;
        var_v0 = 1;
        if (D_8006CFD8 >= temp_v1) {
            var_v0 = func_80025EF8((s32) ((temp_v1 * 0xF0) + D_80090A98));
            var_a1 = 0xFFFF;
        } else {
            var_a1 = 0xFFFF;
        }
    } while (var_v0 == 0);
}
