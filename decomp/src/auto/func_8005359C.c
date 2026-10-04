#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CC64;
extern s32 func_8003CE04();


void func_8005359C(void *arg0) {
    s32 sp54;
    s32 sp58;
    s16 temp_v0;
    s16 var_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_s0;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    if (temp_v0 != 3) {
        if (temp_v0 != 2) {
            if (temp_v0 != 1) {
                if ((temp_v0 == 0) && (M2C_FIELD(arg0, s32 *, 0x74) != 0)) {
                    var_v0 = 1;
                    goto block_18;
                }
            } else {
                temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x74);
                if (temp_v0_2 < 0x82) {
                    M2C_FIELD(arg0, s32 *, 0x74) = (s32) (temp_v0_2 + 1);
                    temp_v0_3 = M2C_FIELD(arg0, s32 *, 0x74);
                    if ((temp_v0_3 < 0x32) && (temp_v0_3 & 1)) {
                        func_800224B8((s32) &sp54);
                        temp_v0_4 = ((s32) ((sp58 >> 8) * 0x5B3) >> 8) << 8;
                        sp58 = temp_v0_4;
                        temp_v0_5 = func_800252A0(0xC, (s32) arg0, 0, -0x10000, /* extra? */ 0, /* extra? */ sp54, /* extra? */ temp_v0_4, /* extra? */ sp5C, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0);
                        func_800249CC(temp_v0_5, 0x2F);
                        M2C_FIELD(temp_v0_5, s32 (**)(s32), 0) = func_8003CE04;
                        M2C_FIELD(temp_v0_5, s16 *, 0x96) = 0x4B;
                    }
                    if (M2C_FIELD(arg0, s32 *, 0x74) == 0x32) {
                        func_800249CC((s32) arg0, 0x2E);
                    }
                    var_s0 = 0;
loop_14:
                    if (var_s0 < 5) {
                        func_800224B8((s32) &sp54);
                        CrearParticula(0x12, (s32) arg0, 0, sp54, /* extra? */ sp58, /* extra? */ sp5C, /* extra? */ sp54, /* extra? */ (((s32) ((sp58 >> 8) * 0x5B3) >> 8) << 8), /* extra? */ sp5C, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x32, /* extra? */ 0, /* extra? */ 0);
                        var_s0 += 1;
                        goto loop_14;
                    }
                    return;
                }
                M2C_FIELD(arg0, s16 *, 0x70) = 2;
            }
        } else {
            D_8007CC64 += 1;
            var_v0 = 3;
block_18:
            M2C_FIELD(arg0, s16 *, 0x70) = var_v0;
        }
    }
}
