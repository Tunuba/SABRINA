#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void MatrizDesdeAngulos(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 sp30;
    s16 sp32;
    s16 sp34;
    s16 sp36;
    s16 sp38;
    s16 sp3A;
    s16 sp3C;
    s16 sp3E;
    s16 sp40;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s3;
    s32 temp_s4;

    if (arg0 != 0) {
        if (M2C_FIELD(arg1, s32 *, 0) == 0) {
            M2C_FIELD(arg1, s32 *, 0) = 0x1000;
        }
        if (M2C_FIELD(arg1, s32 *, 4) == 0) {
            M2C_FIELD(arg1, s32 *, 4) = 0x1000;
        }
        if (M2C_FIELD(arg1, s32 *, 8) == 0) {
            M2C_FIELD(arg1, s32 *, 8) = 0x1000;
        }
        temp_s2 = M2C_FIELD(arg3, s32 *, 0);
        temp_s3 = M2C_FIELD(arg3, s32 *, 4);
        temp_s4 = M2C_FIELD(arg3, s32 *, 8);
        M2C_FIELD(arg0, s16 *, 0x14) = 0x1000;
        M2C_FIELD(arg0, s16 *, 0x16) = 0;
        M2C_FIELD(arg0, s16 *, 0x18) = 0;
        M2C_FIELD(arg0, s16 *, 0x1A) = 0;
        M2C_FIELD(arg0, s16 *, 0x1C) = rcos(temp_s2);
        M2C_FIELD(arg0, s16 *, 0x1E) = (s16) -rsin(temp_s2);
        M2C_FIELD(arg0, s16 *, 0x20) = 0;
        M2C_FIELD(arg0, s16 *, 0x22) = rsin(temp_s2);
        M2C_FIELD(arg0, s16 *, 0x24) = rcos(temp_s2);
        sp30 = rcos(temp_s3);
        sp32 = 0;
        sp34 = rsin(temp_s3);
        sp36 = 0;
        sp38 = 0x1000;
        sp3A = 0;
        sp3C = -rsin(temp_s3);
        sp3E = 0;
        temp_s2_2 = arg0 + 0x14;
        sp40 = rcos(temp_s3);
        MulMatrix0(temp_s2_2, (s32) &sp30, temp_s2_2);
        sp30 = rcos(temp_s4);
        sp32 = -rsin(temp_s4);
        sp34 = 0;
        sp36 = rsin(temp_s4);
        sp38 = rcos(temp_s4);
        sp3A = 0;
        sp3C = 0;
        sp3E = 0;
        sp40 = 0x1000;
        MulMatrix0(temp_s2_2, (s32) &sp30, temp_s2_2);
        sp30 = (s16) M2C_FIELD(arg1, s32 *, 0);
        sp32 = 0;
        sp34 = 0;
        sp36 = 0;
        sp38 = (s16) M2C_FIELD(arg1, s32 *, 4);
        sp3A = 0;
        sp3C = 0;
        sp3E = 0;
        sp40 = (s16) M2C_FIELD(arg1, s32 *, 8);
        MulMatrix0(temp_s2_2, (s32) &sp30, temp_s2_2);
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) ((s32) M2C_FIELD(arg2, s32 *, 0) >> 8);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) ((s32) M2C_FIELD(arg2, s32 *, 4) >> 8);
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) ((s32) M2C_FIELD(arg2, s32 *, 8) >> 8);
    }
}
