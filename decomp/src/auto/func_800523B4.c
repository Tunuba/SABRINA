#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D53C0;

void func_800523B4(void) {
    s32 *var_t2;
    void *var_v0;

    D_800D53C0 = saved_reg_ra;
    func_800143E4();
    var_v0 = M2C_FIELD((void *(*)())0xB0(), void **, 0x18);
    var_t2 = &D_80052424;
    do {
        M2C_FIELD(var_v0, s32 *, 0x70) = (s32) *var_t2;
        var_t2 += 4;
        var_v0 += 4;
    } while (var_t2 != &D_80052430);
    FlushCache();
    func_800143F4();
}
