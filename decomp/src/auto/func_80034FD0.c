#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C64FC;
extern s32 D_800C6500;
extern s32 D_800C6504;
extern s32 D_800C6508;
extern s32 D_800C650C;
extern s32 D_800C6510;
extern void * D_8007CAFC;
extern s8 D_8007CBB4;
extern s8 D_8007CBB5;


void func_80034FD0(s32 arg0, s32 arg1) {
    void *temp_a3;

    temp_a3 = D_8007CAFC + 0x74;
    if (arg0 != 0) {
        D_8007CBB5 = 1;
        D_800C6508 = M2C_FIELD(arg0, s32 *, 0);
        D_800C650C = M2C_FIELD(arg0, s32 *, 4);
        D_800C6510 = M2C_FIELD(arg0, s32 *, 8);
    }
    if (arg1 != 0) {
        D_8007CBB4 = 1;
        D_800C64FC = M2C_FIELD(arg1, s32 *, 0);
        D_800C6500 = M2C_FIELD(arg1, s32 *, 4);
        D_800C6504 = M2C_FIELD(arg1, s32 *, 8);
    }
    M2C_FIELD(D_8007CAFC, s16 *, 0x70) = 6;
    M2C_FIELD(temp_a3, s32 *, 0x28) = (s32) D_800C64FC;
    M2C_FIELD(temp_a3, s32 *, 0x2C) = (s32) D_800C6500;
    M2C_FIELD(temp_a3, s32 *, 0x30) = (s32) D_800C6504;
    M2C_FIELD(temp_a3, s32 *, 0x34) = (s32) D_800C6508;
    M2C_FIELD(temp_a3, s32 *, 0x38) = (s32) D_800C650C;
    M2C_FIELD(temp_a3, s32 *, 0x3C) = (s32) D_800C6510;
}
