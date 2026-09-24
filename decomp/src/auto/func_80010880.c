#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8008319C;
extern s16 D_800831A0;
extern s32 D_80062AF8;
extern u8 D_80062B00[];
extern u8 D_80063508[];


void func_80010880(s32 arg0, s32 arg1) {
    D_800831A0 = LoadClut2((s32) D_80062B00, arg0, arg1 + 0x80);
    D_8008319C = LoadTPage((s32) &D_80062B00[0x200], 0, 0, arg0, /* extra? */ arg1, /* extra? */ 0x80, /* extra? */ 0x20);
    D_80062AF8 = 0;
    memset((s32) D_80063508, 0, 0x180);
}
