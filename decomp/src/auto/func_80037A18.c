#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80037A18(void *arg0) {
    s32 sp54;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s32 temp_a0;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_v1;
    void *temp_s0;
    void *temp_s2;

    temp_s0 = arg0 + 0x74;
    temp_a0 = M2C_FIELD(arg0, s32 *, 0x54);
    temp_s2 = M2C_FIELD(temp_s0, void **, 0x10);
    if (temp_a0 < 0x400) {
        M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_a0 + ((s32) (0x400 - temp_a0) >> 2));
        if (M2C_FIELD(arg0, s32 *, 0x54) >= 0x400) {
            M2C_FIELD(arg0, s32 *, 0x54) = 0x400;
        }
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
    }
    if (temp_s2 != NULL) {
        func_80021D44((s32) (arg0 + 0x30), (s32) func_800221A8((s32) arg0, M2C_FIELD(temp_s2, s32 *, 0x24), M2C_FIELD(temp_s2, s32 *, 0x28) + (func_80021C3C() >> 1), M2C_FIELD(temp_s2, s32 *, 0x2C)), 0x32);
        func_80021D44((s32) (arg0 + 0x32), (s32) func_8002218C((s32) arg0, M2C_FIELD(temp_s2, s32 *, 0x24), M2C_FIELD(temp_s2, s32 *, 0x2C)), 0x32);
        M2C_FIELD(arg0, s32 *, 0x74) = (s32) (M2C_FIELD(arg0, s32 *, 0x74) + 0x28F);
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x74);
        M2C_FIELD(arg0, s32 *, 0x74) = (s32) (temp_v1 - (temp_v1 >> 8));
    }
    func_8002205C((s32) &sp54, (s32) M2C_FIELD(arg0, s16 *, 0x30), (s32) M2C_FIELD(arg0, s16 *, 0x32));
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) ((s32) (sp54 * M2C_FIELD(arg0, s32 *, 0x74)) >> 0xC);
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) ((s32) (sp58 * M2C_FIELD(arg0, s32 *, 0x74)) >> 0xC);
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) ((s32) (sp5C * M2C_FIELD(arg0, s32 *, 0x74)) >> 0xC);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
    if (M2C_FIELD(temp_s0, s16 *, 0x1C) > 0) {
        temp_s2_2 = (s32) (rsin((s32) M2C_FIELD(temp_s0, s16 *, 0x18)) * 0xCCC) >> 0xC;
        temp_v1_2 = M2C_FIELD(temp_s0, s16 *, 0x1C);
        CrearParticula(0x12, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ ((s32) (rcos((s32) M2C_FIELD(temp_s0, s16 *, 0x18)) * 0xCCC) >> 0xC), /* extra? */ temp_s2_2, /* extra? */ 0, /* extra? */ (s32) temp_v1_2, /* extra? */ (s32) temp_v1_2, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 2, /* extra? */ 0);
        temp_s2_3 = (s32) (rsin((s32) M2C_FIELD(temp_s0, s16 *, 0x1A)) * 0xCCC) >> 0xC;
        temp_v1_3 = M2C_FIELD(temp_s0, s16 *, 0x1C);
        CrearParticula(0x12, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ ((s32) (rcos((s32) M2C_FIELD(temp_s0, s16 *, 0x1A)) * 0xCCC) >> 0xC), /* extra? */ temp_s2_3, /* extra? */ 0, /* extra? */ (s32) temp_v1_3, /* extra? */ (s32) temp_v1_3, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 2, /* extra? */ 0);
    }
    CrearParticula((s32) M2C_FIELD(temp_s0, s8 *, 0x1E), (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x14, /* extra? */ 2, /* extra? */ (s32) M2C_FIELD(temp_s0, s16 *, 0x18));
    M2C_FIELD(temp_s0, s16 *, 0x18) = (s16) (M2C_FIELD(temp_s0, s16 *, 0x18) + 0xF0);
    M2C_FIELD(temp_s0, s16 *, 0x18) = (s16) (M2C_FIELD(temp_s0, s16 *, 0x18) & 0xFFF);
    M2C_FIELD(temp_s0, s16 *, 0x1A) = (s16) (M2C_FIELD(temp_s0, s16 *, 0x1A) + 0xF0);
    M2C_FIELD(temp_s0, s16 *, 0x1A) = (s16) (M2C_FIELD(temp_s0, s16 *, 0x1A) & 0xFFF);
    M2C_FIELD(temp_s0, s16 *, 0x1C) = (s16) (M2C_FIELD(temp_s0, s16 *, 0x1C) - 1);
    M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_s0, s32 *, 0xC) + M2C_FIELD(arg0, s32 *, 0x74));
    if (M2C_FIELD(temp_s0, s32 *, 8) < M2C_FIELD(temp_s0, s32 *, 0xC)) {
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
    }
}
