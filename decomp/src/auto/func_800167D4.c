#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80063918[];
extern u16 * D_800649A4;
extern u16 * D_800649A8;
extern s32 * D_800649AC;


u8 *func_800167D4(void) {
    u8 *var_v0;

    var_v0 = NULL;
    if (M2C_FIELD(D_80063918, u16 *, 0) != 0) {
        func_800143E4();
        M2C_FIELD(D_80063918, u16 *, 0x32) = (u16) *D_800649A8;
        M2C_FIELD(D_80063918, s32 *, 0x34) = (s32) *D_800649AC;
        *D_800649A8 = 0;
        *D_800649A4 = *D_800649A8;
        *D_800649AC &= 0x77777777;
        ResetEntryInt();
        var_v0 = D_80063918;
        M2C_FIELD(D_80063918, u16 *, 0) = 0U;
    }
    return var_v0;
}
