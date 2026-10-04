#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80024DE4();
extern s32 func_80024DF4();
extern s32 func_80024F6C();
extern s32 func_80024F74();
extern s32 func_80024F84();
extern s32 thunk_FUN_8001e588();

void func_80039104(s32 arg0, void *arg1) {
    s16 temp_v0_2;
    s16 var_s0_2;
    s16 var_v0;
    s32 temp_s2;
    s32 var_s0;
    s32 var_v1;
    u16 temp_v0;
    void *temp_s3;

    temp_v0 = M2C_FIELD(arg1, u16 *, 0x22);
    temp_s3 = arg0 + 0x74;
    if ((temp_v0 != 0x1C) && (temp_v0 != 1)) {
        temp_v0_2 = M2C_FIELD(arg1, s16 *, 0x112);
        if (!(temp_v0_2 & 0x8000)) {
            var_s0 = 0;
            var_v1 = 0;
loop_6:
            if (var_s0 >= M2C_FIELD(temp_s3, s16 *, 0x32)) {
                if (temp_v0_2 & 0x200) {
                    var_s0_2 = 0;
loop_10:
                    if (var_s0_2 < 0x1000) {
                        temp_s2 = func_80021CE4(-0x1999);
                        CrearParticula(6, arg0, (s32) var_s0_2, 0, /* extra? */ -0x1999, /* extra? */ 0x8000, /* extra? */ 0, /* extra? */ temp_s2, /* extra? */ func_80021CE4(0x1999), /* extra? */ 0, /* extra? */ 0x51E, /* extra? */ 0, /* extra? */ 0x3E8, /* extra? */ 0x214, /* extra? */ 0);
                        var_s0_2 += func_80021CE4(0x64) + 0x32;
                        goto loop_10;
                    }
                    var_v0 = 3;
                } else {
                    func_80048468((s32) arg1, arg0);
                    if (!(M2C_FIELD(arg1, s16 *, 0x112) & 1)) {
                        M2C_FIELD(arg1, s32 (**)(), 0) = func_80024DE4;
                        M2C_FIELD(arg1, s32 (**)(), 4) = func_80024DF4;
                        M2C_FIELD(arg1, s32 (**)(), 8) = func_80024F6C;
                        M2C_FIELD(arg1, s32 (**)(), 0xC) = func_80024F74;
                        M2C_FIELD(arg1, s32 (**)(), 0x10) = func_80024F84;
                        M2C_FIELD(arg1, void (**)(s32), 0x14) = thunk_FUN_8001e588;
                        TocarSonido(0x21, 0, 0x2A, 0x7F);
                    }
                    M2C_FIELD(((M2C_FIELD(temp_s3, s16 *, 0x32) * 4) + temp_s3), void **, 0x14) = arg1;
                    *(temp_s3 + (M2C_FIELD(temp_s3, s16 *, 0x32) * 4)) = func_80014AEC(M2C_FIELD(arg0, s32 *, 0x28) - M2C_FIELD(arg1, s32 *, 0x28));
                    M2C_FIELD(((M2C_FIELD(temp_s3, s16 *, 0x32) * 2) + temp_s3), s16 *, 0x28) = (s16) M2C_FIELD(arg1, s32 *, 0x58);
                    M2C_FIELD(temp_s3, s16 *, 0x32) = (s16) (M2C_FIELD(temp_s3, s16 *, 0x32) + 1);
                    var_v0 = 1;
                }
                M2C_FIELD(arg0, s16 *, 0x70) = var_v0;
            } else if (arg1 != M2C_FIELD((var_v1 + temp_s3), s32 *, 0x14)) {
                var_s0 += 1;
                var_v1 += 4;
                goto loop_6;
            }
        }
    }
}
