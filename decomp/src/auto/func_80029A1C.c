#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80061234[];
extern u8 D_80061298[];
extern u8 D_80061340[];
extern u8 D_8006134C[];
extern u8 D_80061354[];
extern u8 D_80061360[];
extern u8 D_8006136C[];
extern u8 D_80061378[];
extern s32 D_8006D3A8[];


s32 func_80029A1C(s32 arg0) {
    u32 temp_a0;

    temp_a0 = arg0 & 0xFF;
    if (temp_a0 < 7U) {
        return D_8006D3A8[temp_a0];
    }
    return (s32) "none";
}
