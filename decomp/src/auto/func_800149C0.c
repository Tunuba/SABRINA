#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void * D_80063844;


s32 func_800149C0(void) {
    s32 sp0;
    s32 temp_v0;

    M2C_FIELD(D_80063844, s16 *, 0xA) = 0;
    sp0 = 0xA;
    sp0 = 9;
    if (sp0 != -1) {
        do {
            temp_v0 = sp0 - 1;
            sp0 = temp_v0;
        } while (temp_v0 != -1);
    }
    return 0;
}
