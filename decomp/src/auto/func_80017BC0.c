#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80084CD0;
extern s32 func_80017B8C();

void func_80017BC0(void) {
    s32 (*var_t2)();
    s32 *temp_t7;
    s32 *var_t2_2;
    s32 *var_v0;
    s32 *var_v0_2;
    s32 temp_v1;

    D_80084CD0 = saved_reg_ra;
    func_800143E4();
    var_v0 = M2C_FIELD((void *(*)())0xB0(), s32 *, 0x18) + 0x28;
    temp_t7 = var_v0;
    var_t2 = func_80017B8C;
loop_1:
    temp_v1 = *var_t2;
    var_t2 += 4;
    var_v0 += 4;
    if (temp_v1 == *var_v0) {
        if (var_t2 == (func_80017B8C + 0x18)) {
            var_v0_2 = temp_t7;
            var_t2_2 = func_80017B8C + 0x18;
            do {
                *var_v0_2 = *var_t2_2;
                var_t2_2 += 4;
                var_v0_2 += 4;
            } while (var_t2_2 != (func_80017B8C + 0x30));
        } else {
            goto loop_1;
        }
    }
    FlushCache();
    func_800143F4();
}
