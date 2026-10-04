#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800D53B0;
extern s32 func_80052184();

void func_800521AC(void) {
    s32 (*var_t2)();
    s32 *var_v0;
    void *temp_v0;

    D_800D53B0 = saved_reg_ra;
    func_800143E4();
    temp_v0 = M2C_FIELD((void *(*)())0xB0(), void **, 0x18);
    var_v0 = ((M2C_FIELD(temp_v0, s32 *, 0x70) & 0xFFFF) << 0x10) + (M2C_FIELD(temp_v0, s32 *, 0x74) & 0xFFFF) + 0x28;
    var_t2 = func_80052184;
    do {
        *var_v0 = *var_t2;
        var_t2 += 4;
        var_v0 += 4;
    } while (var_t2 != (func_80052184 + 0x14));
    *(s32 **)0xDFFC = var_v0;
    FlushCache();
}
