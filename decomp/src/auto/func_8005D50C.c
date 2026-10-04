#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D5818[];
extern s16 D_800D5848;
extern s16 D_800D584E;
extern s16 D_800D5850;
extern u8 D_8007C930[];
extern s32 D_8007CC88;
extern s32 D_8007CC8C;
extern s32 D_8007CC94;


s32 func_8005D50C(s32 arg0, s32 arg1) {
    M2C_UNK sp28;
    s8 sp40;
    s8 sp41;
    s8 sp42;
    s8 sp43;
    s16 sp46;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 var_s0;
    s16 var_s1;
    s16 var_s1_2;
    s32 temp_v0;
    s32 temp_v0_2;

    var_s1 = 0;
    var_s0 = 0;
    sp46 = 0;
    D_8007CC88 = Reservar(0x80000, (s32) D_8007C930);
    Afirmar(D_8007CC88 != 0);
    D_8007CC8C = Reservar(0x11000, (s32) D_8007C930);
    func_8005D844();
    sp40 = 0x80;
    sp41 = 0x80;
    sp42 = 0x80;
    sp43 = 0x80;
    CdMix((s32) &sp40);
    if (func_8002BE88((s32) &sp28, *arg0) == 0) {
        Liberar(D_8007CC88);
        Liberar(D_8007CC8C);
        return 3;
    }
    func_8005C964();
    func_8005C9D0(arg0);
    if (func_8005CD98((s32) &sp28) == 0) {
        func_8005CE48();
        Liberar(D_8007CC88);
        Liberar(D_8007CC8C);
        return 3;
    }
loop_6:
    temp_v0 = func_8005CEBC();
    if (temp_v0 != 0) {
        var_s1_2 = 0;
        func_8005D02C(temp_v0);
loop_21:
        if ((D_800D5848 == 0) && (var_s0 == 0)) {
            func_8005DCD4(M2C_FIELD((D_800D5818 + (D_800D584E * 4)), s32 *, 0x3C), func_8005D0D0());
            func_8005DD50(M2C_FIELD((D_800D5818 + (D_800D5850 * 4)), s32 *, 0x44), func_8005D0F4());
            temp_v0_2 = func_8005CEBC();
            if (temp_v0_2 == 0) {
                temp_v0_3 = var_s1_2 + 1;
                var_s1_2 = temp_v0_3;
                if (temp_v0_3 == 5) {
                    var_s0 = 3;
                }
            } else {
                var_s1_2 = 0;
            }
            func_8005D02C(temp_v0_2);
            SpuSetCommonMasterVolume(0x3FFF, 0x3FFF);
            func_8001D778();
            if ((sp46 == 0) && (((s32 (*)()) arg1)() != 0)) {
                if (D_8007CC94 > 0) {
                    sp46 = (s16) D_8007CC94;
                } else {
                    sp46 = 0;
                }
            }
            if (sp46 != 0) {
                var_s0 = func_8005D164((s32) &sp46);
            } else {
                func_8005D3F4();
            }
            func_8005D1D0();
            func_80012D74(0);
            func_8001626C(0);
            GsSwapDispBuff();
            goto loop_21;
        }
        func_8005CE48();
        if (D_800D5848 != 0) {
            var_s0 = 1;
        }
        Liberar(D_8007CC88);
        Liberar(D_8007CC8C);
        return (s32) var_s0;
    }
    temp_v0_4 = var_s1 + 1;
    var_s1 = temp_v0_4;
    if (temp_v0_4 == 5) {
        func_8005CE48();
        Liberar(D_8007CC88);
        Liberar(D_8007CC8C);
        return 3;
    }
    goto loop_6;
}
