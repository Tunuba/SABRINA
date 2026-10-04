#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80044BD4();

s32 func_80044C40(s32 arg0, s32 arg1) {
    return (s32) func_800447E4(arg0, (s32) (s16) arg1, (s32) func_80044BD4, 0);
}
