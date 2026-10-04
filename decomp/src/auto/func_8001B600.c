#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800686C4[];
extern void *(*D_8007CA44)();


s32 func_8001B600(s32 arg0) {
    void *var_v0;

    if (D_8007CA44 != NULL) {
        var_v0 = D_8007CA44();
    } else {
        var_v0 = func_8001B0C8(arg0);
    }
    if ((var_v0 != NULL) && (M2C_FIELD(var_v0, s32 *, 4) == 0)) {
        M2C_FIELD(var_v0, s32 *, 4) = Reservar(func_800150F0(arg0) + 1, (s32) D_800686C4);
        strcpy(M2C_FIELD(var_v0, s32 *, 4), arg0);
    }
    return (s32) var_v0;
}
