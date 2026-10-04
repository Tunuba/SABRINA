#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80074EBC;
extern s32 D_80074ED0;


u16 func_8003E9FC(s32 arg0, s32 arg1) {
    u16 temp_a0;

    temp_a0 = *((arg0 * 2) + D_80074EBC);
    if (arg1 != -1) {
        return temp_a0 << D_80074ED0;
    }
    return temp_a0;
}
