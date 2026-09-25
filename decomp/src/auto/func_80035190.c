#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80086398;
extern s32 D_800863B4;
extern s32 D_800863C0;
extern s32 D_80086414;
extern u8 D_800D588C[];
extern s32 D_8006C444;
extern s32 D_8006C448;
extern s32 D_8006C44C;
extern s32 D_8006C450;
extern s32 D_8006C454;
extern s32 D_8006C458;
extern s32 D_8006C45C;
extern s32 D_8006C460;
extern s32 D_8006C464;
extern s16 D_8007C872;
extern s32 D_8007C9F0;
extern s8 nivel_actual;
extern void * D_8007CAFC;
extern s32 D_8007CBAC;
extern s32 D_8007CBB0;
extern s32 D_8007CBBC;
extern u16 D_8007CBC0;
extern u16 D_8007CBD4;


void func_80035190(void *arg0) {
    void *temp_s0;

    temp_s0 = arg0 + 0x74;
    D_8007CBC0 = D_8007CBD4;
    D_8007CBBC = 0;
    M2C_FIELD(temp_s0, s32 *, 0x4C) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x48) = 0;
    D_8007CAFC = arg0;
    D_8006C444 = (s32) M2C_FIELD(arg0, s32 *, 0x24) >> 8;
    D_8006C448 = (s32) M2C_FIELD(arg0, s32 *, 0x28) >> 8;
    D_8006C44C = (s32) M2C_FIELD(arg0, s32 *, 0x2C) >> 8;
    D_8006C450 = 0;
    D_8006C454 = 0;
    D_8006C458 = -0x1000;
    D_8006C45C = 0;
    D_8006C460 = 0x1000;
    D_8006C464 = 0;
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
    M2C_FIELD(arg0, u8 **, 0x74) = D_800D588C;
    M2C_FIELD(temp_s0, s32 *, 0x34) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
    M2C_FIELD(temp_s0, s32 *, 0x38) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(temp_s0, s32 *, 0x3C) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
    M2C_FIELD(temp_s0, s16 *, 0x40) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x42) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x25) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x5C) = 0;
    D_8007CBAC = 0;
    D_8007CBB0 = 0;
    M2C_FIELD(temp_s0, s32 *, 0x48) = func_8001E06C(D_80086398, D_8007C9F0);
    switch (nivel_actual) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        M2C_FIELD(temp_s0, s32 *, 0x4C) = func_8001E06C(D_80086414, D_8007C9F0);
        return;
    case 13:
        M2C_FIELD(temp_s0, s32 *, 0x4C) = func_8001E06C(D_800863B4, D_8007C9F0);
        return;
    case 14:
        M2C_FIELD(temp_s0, s32 *, 0x4C) = func_8001E06C(D_800863C0, D_8007C9F0);
        D_8007C872 = 1;
        /* fallthrough */
    default:
        return;
    }
}
