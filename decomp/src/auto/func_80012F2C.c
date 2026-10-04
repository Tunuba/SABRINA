#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80060C5C[];
extern u8 D_80063688[];
extern u8 D_800636C8[];
extern u8 D_800636EC[];

u8 D_800636C8[4];                                   /* unable to generate initializer: cannot parse D_80063688 as integer */

s32 func_80012F2C(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v0;

    func_800112C0((s32) "MoveImage\0\0\0ClearOTag(%08x,%d)...\n", arg0);
    var_v0 = -1;
    if (M2C_FIELD(arg0, s16 *, 4) != 0) {
        if (M2C_FIELD(arg0, s16 *, 6) == 0) {
            return -1;
        }
        M2C_FIELD(D_800636EC, s32 *, 4) = (s32) ((arg2 << 0x10) | (arg1 & 0xFFFF));
        M2C_FIELD(D_800636EC, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0);
        M2C_FIELD(D_800636EC, s32 *, 8) = (s32) M2C_FIELD(arg0, s16 *, 4);
        var_v0 = M2C_FIELD(*D_800636C8, s32 (**)(s32, u8 *, M2C_UNK, M2C_UNK), 8)(M2C_FIELD(*D_800636C8, s32 *, 0x18), D_800636EC - 8, 0x14, 0);
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
