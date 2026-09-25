#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006C444;
extern s32 D_8006C448;
extern s32 D_8006C44C;
extern s16 D_8007CAE2;
extern s16 D_8007CAE4;


void func_80037278(void *arg0, void *arg1) {
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 temp_v0;
    s32 var_s2;
    void *temp_s1;

    temp_s1 = arg0 + 0x74;
    if (arg0 != NULL) {
        func_800350A4(arg1 + 0x24);
        sp34 = (s32) (M2C_FIELD(arg0, s32 *, 0x24) - M2C_FIELD(arg1, s32 *, 0x24)) >> 8;
        sp38 = (s32) (M2C_FIELD(arg0, s32 *, 0x28) - M2C_FIELD(arg1, s32 *, 0x28)) >> 8;
        sp3C = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) - M2C_FIELD(arg1, s32 *, 0x2C)) >> 8;
        func_8002205C((s32) &sp34, 0, (s32) M2C_FIELD(arg1, s16 *, 0x32));
        sp34 = M2C_FIELD(arg1, s32 *, 0x24) - (((s32) ((sp34 >> 4) * 0x300) >> 8) << 8);
        temp_v0 = M2C_FIELD(arg1, s32 *, 0x2C) - (((s32) ((sp3C >> 4) * 0x300) >> 8) << 8);
        sp3C = temp_v0;
        sp38 = M2C_FIELD(arg1, s32 *, 0x28) + 0xFFFEB334;
        M2C_FIELD(arg0, s32 *, 0x24) = sp34;
        M2C_FIELD(arg0, s32 *, 0x28) = sp38;
        M2C_FIELD(arg0, s32 *, 0x2C) = temp_v0;
        M2C_FIELD(temp_s1, s32 *, 0x34) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
        M2C_FIELD(temp_s1, s32 *, 0x38) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
        M2C_FIELD(temp_s1, s32 *, 0x3C) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
        M2C_FIELD(temp_s1, s32 *, 0x28) = (s32) M2C_FIELD(arg1, s32 *, 0x24);
        M2C_FIELD(temp_s1, s32 *, 0x2C) = (s32) M2C_FIELD(arg1, s32 *, 0x28);
        M2C_FIELD(temp_s1, s32 *, 0x30) = (s32) M2C_FIELD(arg1, s32 *, 0x2C);
        var_s2 = 0;
loop_3:
        if (var_s2 < 0x64) {
            func_80036410((s32) arg0, M2C_FIELD(temp_s1, s32 *, 0x34), M2C_FIELD(temp_s1, s32 *, 0x38), M2C_FIELD(temp_s1, s32 *, 0x3C), /* extra? */ M2C_FIELD(temp_s1, s32 *, 0x28), /* extra? */ M2C_FIELD(temp_s1, s32 *, 0x2C), /* extra? */ M2C_FIELD(temp_s1, s32 *, 0x30), /* extra? */ 3);
            func_80036524((s32) arg0, M2C_FIELD(temp_s1, s32 *, 0x28), M2C_FIELD(temp_s1, s32 *, 0x2C), M2C_FIELD(temp_s1, s32 *, 0x30));
            D_8007CAE2 = M2C_FIELD(arg0, s16 *, 0x32);
            var_s2 += 1;
            D_8007CAE4 = M2C_FIELD(arg0, s16 *, 0x30);
            D_8006C444 = (s32) M2C_FIELD(arg0, s32 *, 0x24) >> 8;
            D_8006C448 = (s32) M2C_FIELD(arg0, s32 *, 0x28) >> 8;
            D_8006C44C = (s32) M2C_FIELD(arg0, s32 *, 0x2C) >> 8;
            goto loop_3;
        }
    }
}
