#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80063918[];
extern u16 * D_800649A8;
extern s32 * D_800649AC;


u8 *func_80016874(void) {
    if (M2C_FIELD(D_80063918, u16 *, 0) == 0) {
        HookEntryInt();
        M2C_FIELD(D_80063918, u16 *, 0) = 1U;
        *D_800649A8 = M2C_FIELD(D_80063918, u16 *, 0x32);
        *D_800649AC = M2C_FIELD(D_80063918, s32 *, 0x34);
        func_800143F4();
        return D_80063918;
    }
    return NULL;
}
