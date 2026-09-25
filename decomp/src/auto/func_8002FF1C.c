#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_80093CE4;
extern u16 D_80093CE8;
extern u16 D_80093CEC;
extern u16 D_80093CF2;
extern u8 D_8006EDC0[];
extern u8 D_8006EDD4[];
extern u8 D_8006EDE8[];
extern u8 D_8006EDFC[];
extern u8 D_8006EE10[];
extern u8 D_8006EE28[];
extern u8 mao_hub[];
extern u8 D_8007C89C[];
extern u16 D_8007CB54;
extern u16 D_8007CB56;

u8 mao_hub[0x18];                                   /* unable to generate initializer: cannot parse D_8006EDC0 as integer */

void func_8002FF1C(void) {
    s32 sp1C;
    u16 sp34;
    s32 *var_t7;
    s32 var_t9;
    u8 *var_t8;

    var_t8 = mao_hub;
    var_t7 = &sp1C;
    var_t9 = 6;
    do {
        var_t9 -= 1;
        *var_t7 = *var_t8;
        var_t8 += 4;
        var_t7 += 4;
    } while (var_t9 > 0);
    CargarANI((s32) &sp1C, 6, (s32) "Hub.ANI", (s32) &sp34);
    D_80093CE4 = sp34;
    D_80093CEC = sp36;
    D_80093CE8 = sp38;
    D_80093CF2 = sp3A;
    D_8007CB56 = sp3C;
    D_8007CB54 = sp3E;
}
