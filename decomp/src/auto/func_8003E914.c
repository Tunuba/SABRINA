#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80074EBC;
extern s32 D_80074ED0;


void func_8003E914(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = arg0 * 2;
    if (arg2 == 0) {
        *(temp_v0 + D_80074EBC) = (s16) arg1;
        return;
    }
    *(temp_v0 + D_80074EBC) = (s16) ((u32) arg1 >> D_80074ED0);
}
