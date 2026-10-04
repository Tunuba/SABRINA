#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007C9E0;
extern s16 D_8007C9E2;
extern s16 D_8007C9E4;
extern s16 D_8007C9E6;
extern u8 D_8007C9E8[];
extern s16 D_8007C9EC;
extern u8 D_8007CCBC[];
extern s8 D_8007CCD2;
extern s8 D_8007CCD3;
extern s8 D_8007CCD4[];
extern u8 D_8007CD18[];
extern s8 D_8007CD2E;
extern s8 D_8007CD2F;
extern s8 D_8007CD30[];
extern u8 D_8007CD74[];
extern s16 D_8007CD7C;
extern s16 D_8007CD7E;
extern s16 D_8007CD80;
extern s16 D_8007CD82;
extern u8 D_8007CD88[];
extern s16 D_8007CD90;
extern s16 D_8007CD92;
extern s16 D_8007CD94;
extern s16 D_8007CD96;
extern u8 D_8007CD9C[];


void func_800213A0(void) {
    memset((s32) D_8007CCBC, 0, 0x5C);
    memset((s32) D_8007CD18, 0, 0x5C);
    SetDefDrawEnv((s32) D_8007CCBC, 0, 0, 0x200, /* extra? */ 0xDC);
    SetDefDrawEnv((s32) D_8007CD18, 0, 0xDC, 0x200, /* extra? */ 0xDC);
    SetDefDispEnv((s32) D_8007CD74, 0, 0xDC, 0x200, /* extra? */ 0xDC);
    SetDefDispEnv((s32) D_8007CD88, 0, 0, 0x200, /* extra? */ 0xDC);
    D_8007CD90 = 0;
    D_8007CD7C = 0;
    D_8007C9E0 = 0;
    D_8007CD92 = 0xA;
    D_8007CD7E = 0xA;
    D_8007CD94 = 0x100;
    D_8007CD80 = 0x100;
    D_8007CD96 = 0xDC;
    D_8007CD82 = 0xDC;
    *D_8007CD30 = 0;
    *D_8007CCD4 = 0;
    D_8007CD2F = 0;
    D_8007CCD3 = 0;
    D_8007CD2E = 1;
    D_8007CCD2 = 1;
    D_8007C9E2 = 0;
    D_8007C9E4 = 0x400;
    D_8007C9E6 = 0x1B8;
    func_80021120((s32) D_8007C9E0, (s32) D_8007C9E4);
    func_8001315C((s32) D_8007CCBC);
    func_8001321C((s32) D_8007CD88);
    *D_8007C9E8 = D_8007CD9C;
    D_8007C9EC = 0;
    func_80012FE4((s32) *D_8007C9E8, 0x400);
}
