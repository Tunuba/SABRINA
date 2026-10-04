#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_800649F0;
extern u8 D_800649F4[];
extern s32 func_80016CCC();


s32 func_80016DA0(void) {
    func_80016D78((s32) D_800649F4, 8);
    *D_800649F0 = 0;
    func_80016940();
    return (s32) func_80016CCC;
}
