#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8001E588(void *arg0) {
    s16 sp28;
    s16 sp2A;
    s16 sp2C;
    s16 sp2E;
    s16 sp30;
    s16 sp32;
    s16 sp34;
    s16 sp36;
    s16 sp38;
    s16 temp_s2;
    s16 temp_s3;
    s16 temp_s4;
    void *temp_s1;
    void *temp_s2_2;

    temp_s1 = M2C_FIELD(arg0, void **, 0x60);
    if (temp_s1 != NULL) {
        if (M2C_FIELD(arg0, s32 *, 0x54) == 0) {
            M2C_FIELD(arg0, s32 *, 0x54) = 0x1000;
        }
        if (M2C_FIELD(arg0, s32 *, 0x58) == 0) {
            M2C_FIELD(arg0, s32 *, 0x58) = 0x1000;
        }
        if (M2C_FIELD(arg0, s32 *, 0x5C) == 0) {
            M2C_FIELD(arg0, s32 *, 0x5C) = 0x1000;
        }
        temp_s2 = M2C_FIELD(arg0, s16 *, 0x30);
        temp_s3 = M2C_FIELD(arg0, s16 *, 0x32);
        temp_s4 = M2C_FIELD(arg0, s16 *, 0x34);
        M2C_FIELD(temp_s1, s16 *, 0x14) = 0x1000;
        M2C_FIELD(temp_s1, s16 *, 0x16) = 0;
        M2C_FIELD(temp_s1, s16 *, 0x18) = 0;
        M2C_FIELD(temp_s1, s16 *, 0x1A) = 0;
        M2C_FIELD(temp_s1, s16 *, 0x1C) = rcos((s32) temp_s2);
        M2C_FIELD(temp_s1, s16 *, 0x1E) = (s16) -rsin((s32) temp_s2);
        M2C_FIELD(temp_s1, s16 *, 0x20) = 0;
        M2C_FIELD(temp_s1, s16 *, 0x22) = rsin((s32) temp_s2);
        M2C_FIELD(temp_s1, s16 *, 0x24) = rcos((s32) temp_s2);
        sp28 = rcos((s32) temp_s3);
        sp2A = 0;
        sp2C = rsin((s32) temp_s3);
        sp2E = 0;
        sp30 = 0x1000;
        sp32 = 0;
        sp34 = -rsin((s32) temp_s3);
        sp36 = 0;
        temp_s2_2 = temp_s1 + 0x14;
        sp38 = rcos((s32) temp_s3);
        MulMatrix0((s32) temp_s2_2, (s32) &sp28, (s32) temp_s2_2);
        sp28 = rcos((s32) temp_s4);
        sp2A = -rsin((s32) temp_s4);
        sp2C = 0;
        sp2E = rsin((s32) temp_s4);
        sp30 = rcos((s32) temp_s4);
        sp32 = 0;
        sp34 = 0;
        sp36 = 0;
        sp38 = 0x1000;
        MulMatrix0((s32) temp_s2_2, (s32) &sp28, (s32) temp_s2_2);
        sp28 = (s16) M2C_FIELD(arg0, s32 *, 0x54);
        sp2A = 0;
        sp2C = 0;
        sp2E = 0;
        sp30 = (s16) M2C_FIELD(arg0, s32 *, 0x58);
        sp32 = 0;
        sp34 = 0;
        sp36 = 0;
        sp38 = (s16) M2C_FIELD(arg0, s32 *, 0x5C);
        MulMatrix0((s32) temp_s2_2, (s32) &sp28, (s32) temp_s2_2);
        M2C_FIELD(temp_s1, s32 *, 0x28) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x24) >> 8);
        M2C_FIELD(temp_s1, s32 *, 0x2C) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x28) >> 8);
        M2C_FIELD(temp_s1, s32 *, 0x30) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x2C) >> 8);
    }
}
