#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800649C0[];
extern s32 * D_800649E0;
extern s32 D_800649EC;
extern s32 func_80016A98();


s32 func_80016AF4(void) {
    *D_800649E0 = 0x100;
    D_800649EC = 0;
    func_80016AC4((s32) D_800649C0, 8);
    func_80016940();
    return (s32) func_80016A98;
}
