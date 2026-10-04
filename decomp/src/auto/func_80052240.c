#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D53B0;
extern s32 func_80052184();
extern s32 func_800521AC();

void func_80052240(void) {
    s32 *var_t2;
    void *var_v0;

    D_800D53B0 = saved_reg_ra;
    func_800143E4();
    var_v0 = M2C_FIELD((void *(*)())0xB0(), void **, 0x16C);
    var_t2 = func_80052184 + 0x14;
    do {
        M2C_FIELD(var_v0, s32 *, 0x9C8) = (s32) *var_t2;
        var_t2 += 4;
        var_v0 += 4;
    } while (var_t2 != func_800521AC);
    FlushCache();
}
