#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80065408;
extern s32 D_8006540C;
extern s32 D_80065410;
extern s32 D_80065414;
extern u8 D_80065418[];
extern u8 D_8007A1D0[];
extern u8 D_8007C700[];
extern u8 D_8007C710[];
extern u8 D_8007C720[];
extern u8 D_8007C730[];
extern s32 D_8007C740;
extern s32 D_8007C744;
extern s32 D_8007C748;
extern s32 D_8007C74C;
extern u8 D_8007C77C[];
extern u8 D_8007C784[];
extern s32 D_8007C9E0;
extern s32 D_8007C9E4;
extern s32 D_8007CA58;

s32 D_8007C9E0;                                     /* unable to generate initializer: not enough data */
s32 D_8007C9E4;                                     /* unable to generate initializer: not enough data */

void PantallasLegales(void) {
    s16 sp20;
    s16 sp22;
    s16 sp24;
    s16 sp26;
    M2C_UNK sp28;
    s32 spA8;
    s32 spAC;
    s32 spB0;
    s32 spB4;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    var_s1 = 0;
    sp20 = M2C_FIELD(D_8007C77C, s16 *, 0);
    sp22 = M2C_FIELD(D_8007C77C, s16 *, 2);
    sp24 = M2C_FIELD(D_8007C77C, s16 *, 4);
    spA8 = D_80065408;
    spAC = D_8006540C;
    sp26 = M2C_FIELD(D_8007C77C, s16 *, 6);
    spB0 = D_80065410;
    spB4 = D_80065414;
    var_s2 = 0;
loop_14:
    if (var_s1 == 4) {
        func_80021120(D_8007C9E0, D_8007C9E4);
        return;
    }
    sprintf((s32) &sp28, (s32) "%s%s", "GRAPHICS\\", *(&D_8007C740 + var_s2));
    temp_v0 = CargarArchivoEntero((s32) &sp28, 0);
    if (temp_v0 != 0) {
        func_8001D778();
        func_800219C8();
        SubirAVRAM((s32) &sp20, temp_v0);
        Liberar(temp_v0);
        var_s0 = M2C_FIELD((sp + var_s2), s32 *, 0xA8);
        if (var_s1 != 0) {
loop_5:
            if (D_8007CA58 == 0) {
                if (var_s0 == 0) {

                } else {
                    func_8001D778();
                    var_s0 -= 1;
                    goto loop_5;
                }
            }
        } else {
loop_9:
            if (var_s0 != 0) {
                func_8001D778();
                var_s0 -= 1;
                goto loop_9;
            }
        }
        var_s1 = (var_s1 + 1) & 0xFFFF;
        var_s2 += 4;
        goto loop_14;
    }
    HerramientaConvertirPIC(D_8007C740);
    HerramientaConvertirPIC(D_8007C744);
    HerramientaConvertirPIC(D_8007C748);
    HerramientaConvertirPIC(D_8007C74C);
    printf((s32) "Picture convertion complete.....\n Please restart.... :oP\n");
loop_12:
    goto loop_12;
}
