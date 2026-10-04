#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D2AD0[];
extern u8 ascii_a_letra[];
extern u8 D_800795FC[];
extern u8 D_8007961C[];
extern u16 D_8007CC50;
extern u16 D_8007CC58;
extern u16 D_8007CC5A;


void func_80019738(void) {
    s32 var_a0;
    u8 *temp_v1;

    if ((D_8007CC58 + D_8007CC5A) != 0) {
        func_8001951C((s32) D_8007961C, (s32) (D_800D2AD0 + (D_8007CC50 << 6)));
        var_a0 = 0;
loop_3:
        if ((var_a0 != 0x40) && (M2C_ERROR(/* Read from unset register $t0 */) != 0)) {
            temp_v1 = &D_8007961C[var_a0];
            *temp_v1 = (u8) (s8) ascii_a_letra[(s8) *temp_v1];
            var_a0 = (var_a0 + 1) & 0xFFFF;
            goto loop_3;
        }
    }
    func_800191D8((s32) D_8007961C, (s32) D_800795FC);
}
