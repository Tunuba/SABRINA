#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_80063918;
extern u8 D_80063954[];
extern u8 D_80064980[];
extern u8 D_800649A0[];
extern u16 * D_800649A4;
extern u16 * D_800649A8;
extern s32 * D_800649AC;

u8 D_800649A0[4];                                   /* unable to generate initializer: cannot parse D_80064980 as integer */

u8 *func_800163E4(void) {
    u8 *var_v0;

    var_v0 = NULL;
    if (D_80063918 == 0) {
        *D_800649A8 = 0;
        *D_800649A4 = *D_800649A8;
        *D_800649AC = 0x33333333;
        func_800168EC((s32) &D_80063918, 0x41A);
        if (func_80016170((s32) (&D_80063918 + 0x38)) != 0) {
            func_800164BC();
        }
        M2C_FIELD(D_80063954, u8 **, 0) = (u8 *) (D_80063954 + 0xFDC);
        HookEntryInt();
        M2C_FIELD(D_80063954, s16 *, -0x3C) = 1;
        M2C_FIELD(*D_800649A0, s32 *, 0x14) = func_80016AF4();
        M2C_FIELD(*D_800649A0, s32 *, 4) = func_80016DA0();
        func_800142FC();
        func_800143F4();
        var_v0 = D_80063954 - 0x3C;
    }
    return var_v0;
}
