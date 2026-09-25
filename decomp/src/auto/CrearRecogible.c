#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006EE70[];
extern u8 D_8007007C[];
extern u8 D_80071288[];
extern u8 D_80072494[];
extern u8 D_800736A0[];
extern u8 tabla_clases_niveles[];
extern s8 nivel_actual;

u8 tabla_clases_niveles[0x40];                      /* unable to generate initializer: cannot parse D_8007007C as integer */

void CrearRecogible(s32 arg0) {
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s16 sp42;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s16 sp50;
    s16 sp52;
    s16 sp54;
    s32 sp74;
    s32 sp78;
    s32 sp7C;
    s32 sp8C;
    M2C_UNK sp94;
    s32 *sp114;
    s16 temp_v1;
    s32 **var_t7;
    s32 **var_t8;
    s32 var_t9;
    void *temp_s0;

    memset((s32) &sp20, 0, 0x120);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xC);
    sp42 = temp_v1;
    temp_s0 = *(tabla_clases_niveles + (nivel_actual * 4)) + (temp_v1 * 0x54);
    sp8C = arg0;
    sp44 = M2C_FIELD(arg0, s32 *, 0);
    sp48 = M2C_FIELD(arg0, s32 *, 4);
    sp4C = M2C_FIELD(arg0, s32 *, 8);
    sp50 = M2C_FIELD(arg0, s16 *, 0xE);
    sp52 = M2C_FIELD(arg0, s16 *, 0x10);
    sp54 = M2C_FIELD(arg0, s16 *, 0x12);
    sp74 = (s32) (M2C_FIELD(temp_s0, s16 *, 0x28) * M2C_FIELD(arg0, s16 *, 0x14)) >> 0xC;
    sp78 = (s32) (M2C_FIELD(temp_s0, s16 *, 0x2A) * M2C_FIELD(arg0, s16 *, 0x16)) >> 0xC;
    sp7C = (s32) (M2C_FIELD(temp_s0, s16 *, 0x2C) * M2C_FIELD(arg0, s16 *, 0x18)) >> 0xC;
    func_8001E588((s32) &sp20);
    func_80024A48((s32) &sp20);
    var_t8 = temp_s0 + 0x30;
    sp20 = M2C_FIELD(temp_s0, s32 *, 4);
    var_t7 = &sp114;
    sp24 = M2C_FIELD(temp_s0, s32 *, 8);
    var_t9 = 9;
    sp28 = M2C_FIELD(temp_s0, s32 *, 0xC);
    sp2C = M2C_FIELD(temp_s0, s32 *, 0x10);
    sp30 = M2C_FIELD(temp_s0, s32 *, 0x14);
    sp34 = M2C_FIELD(temp_s0, s32 *, 0x18);
    sp38 = M2C_FIELD(temp_s0, s32 *, 0x1C);
    do {
        var_t9 -= 1;
        *var_t7 = *var_t8;
        var_t8 += 4;
        var_t7 += 4;
    } while (var_t9 > 0);
    sp114 = &sp44;
    if (sp130 != 1) {
        if (sp130 != 2) {
            if (sp130 == 3) {
                func_80039A34((s32) &sp114, func_8003A258((s32) &sp114), (s32) sp134, (s32) sp132);
            }
        } else {
            func_80039A70((s32) &sp114, func_8003A250((s32) &sp114), (s32) sp134, (s32) sp132);
        }
    } else {
        func_80039B1C((s32) &sp114, func_8003A260((s32) &sp114), (s32) sp134, (s32) sp132);
    }
    memcpy((s32) &sp94, arg0 + 0x1C, 0x7F);
    M2C_FIELD(temp_s0, M2C_UNK (**)(s32 *, M2C_UNK, M2C_UNK), 0)(&sp20, 0, 0);
}
