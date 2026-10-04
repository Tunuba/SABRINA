#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D5680;
extern s32 D_800D5684;
extern s32 D_800D5688;

void func_80053A64(s32 arg0) {
    D_800D5680 = M2C_FIELD(arg0, s16 *, 0) << 8;
    D_800D5684 = M2C_FIELD(arg0, s16 *, 2) << 8;
    D_800D5688 = M2C_FIELD(arg0, s16 *, 4) << 8;
}
