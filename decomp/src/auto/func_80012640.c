#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800831F8[];
extern u8 D_80083300[];
extern s32 * D_80063754;
extern s32 * D_80063760;
extern s32 * D_80063770;
extern s32 D_8006377C;
extern s32 D_80063818;
extern s32 D_8006381C[];


s32 func_80012640(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;

    temp_v0 = func_80016A14(0);
    *D_8006381C = 0;
    D_8006377C = temp_v0;
    D_80063818 = *D_8006381C;
    temp_v1 = arg0 & 7;
    switch (temp_v1) {                              /* irregular */
    case 5:
    case 0:
        *D_80063760 = 0x401;
        *D_80063770 |= 0x800;
        *D_80063754 = 0;
        func_80012AE4((s32) D_800831F8, 0, 0x100);
        func_80012AE4((s32) D_80083300, 0, 0x1800);
        break;
    case 1:
    case 3:
        *D_80063760 = 0x401;
        *D_80063770 |= 0x800;
        *D_80063754 = 0x02000000;
        *D_80063754 = 0x01000000;
        break;
    }
    func_80016A14(D_8006377C);
    var_v0 = 0;
    if (!(arg0 & 7)) {
        var_v0 = func_80012A44(arg0);
    }
    return var_v0;
}
