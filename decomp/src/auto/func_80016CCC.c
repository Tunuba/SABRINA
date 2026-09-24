#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_800649F0;
extern s32 D_800649F4[];


s32 func_80016CCC(s32 arg0, s32 arg1) {
    s32 *temp_v1;
    s32 temp_a3;

    temp_v1 = &D_800649F4[arg0];
    temp_a3 = *temp_v1;
    if (arg1 != temp_a3) {
        if (arg1 != 0) {
            *temp_v1 = arg1;
            *D_800649F0 = (*D_800649F0 & 0xFFFFFF) | ((1 << (arg0 + 0x10)) | 0x800000);
            return temp_a3;
        }
        *temp_v1 = 0;
        *D_800649F0 = ((*D_800649F0 & 0xFFFFFF) | 0x800000) & ~(1 << (arg0 + 0x10));
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return temp_a3;
    }
    return temp_a3;
}
