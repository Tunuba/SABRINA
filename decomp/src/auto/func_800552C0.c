#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80024F6C();
extern s32 func_80038154();


void func_800552C0(Objeto *arg0) {
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s16 temp_v0;
    s32 temp_s0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s1;
    s32 var_s3;
    void *temp_a0;
    void *temp_a1;

    temp_a0 = arg0 + 0x74;
    M2C_FIELD(arg0->datos, s16 *, 0x1A) = 2;
    if (M2C_FIELD(temp_a0, s32 *, 0xC) != 0) {
        arg0->estado = 3;
    }
    temp_v0 = arg0->estado;
    switch (temp_v0) {                              /* irregular */
    case 0:
        if (M2C_FIELD(temp_a0, s32 *, 8) != 0) {
            arg0->estado = 1;
            return;
        }
        return;
    case 1:
        temp_v0_2 = M2C_FIELD(temp_a0, s32 *, 8);
        if (temp_v0_2 <= 0) {
            arg0->estado = 2;
        } else {
            M2C_FIELD(temp_a0, s32 *, 8) = (s32) (temp_v0_2 - 1);
        }
        func_80021D44((s32) &arg0->rot[1], (s32) func_8002218C(arg0, p_sabrina->x, p_sabrina->z), 0x7D);
        return;
    case 2:
        M2C_FIELD(temp_a0, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x74);
        arg0->estado = 1;
        temp_s0 = func_800252A0(5, (s32) arg0, 0, -0x18000, /* extra? */ 0xC000, /* extra? */ 0, /* extra? */ 0xFFFF0000, /* extra? */ 0x20000, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 1, /* extra? */ arg0);
        func_8002205C((s32) &sp5C, 0, (s32) arg0->rot[1]);
        func_8001C45C((s32) &sp5C);
        temp_a1 = temp_s0 + 0x74;
        sp5C *= 2;
        sp60 *= 2;
        temp_v0_3 = sp64 * 2;
        sp64 = temp_v0_3;
        M2C_FIELD(temp_s0, s32 *, 0x38) = sp5C;
        M2C_FIELD(temp_s0, s32 *, 0x3C) = sp60;
        M2C_FIELD(temp_s0, s32 *, 0x40) = temp_v0_3;
        M2C_FIELD(temp_a1, s32 *, 8) = 0xC8;
        M2C_FIELD(temp_a1, Objeto **, 0xC) = arg0;
        M2C_FIELD(temp_s0, s32 (**)(s32), 0) = func_80038154;
        M2C_FIELD(temp_s0, s32 (**)(), 8) = func_80024F6C;
        M2C_FIELD(temp_s0, s16 *, 0x114) = (s16) (M2C_FIELD(temp_s0, s16 *, 0x114) | 2);
        M2C_FIELD(temp_s0, s16 *, 0x112) = (s16) (M2C_FIELD(temp_s0, s16 *, 0x112) | 0x1803);
        func_800249CC(temp_s0, 0x2F);
        M2C_FIELD(temp_s0, s32 *, 0x54) = 0x1000;
        M2C_FIELD(temp_s0, s32 *, 0x58) = 0x1000;
        M2C_FIELD(temp_s0, s32 *, 0x5C) = 0x1000;
        var_s0 = 0;
        var_s3 = 0;
        var_s1 = 0;
loop_14:
        if (var_s0 < 3) {
            temp_v1 = 0xA - var_s0;
            CrearParticula(6, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ (0xFFFF0000 - var_s1), /* extra? */ (var_s3 + 0x20000), /* extra? */ 0, /* extra? */ -(temp_v1 * 0x10), /* extra? */ -(temp_v1 << 5), /* extra? */ 5, /* extra? */ 0, /* extra? */ 0);
            var_s0 += 1;
            var_s1 += 0x80;
            var_s3 += 0x100;
            goto loop_14;
        }
        return;
    case 3:
        func_80048228((s32) arg0);
        break;
    }
}
