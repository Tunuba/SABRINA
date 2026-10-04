#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80056C18(void *arg0, s32 arg1) {
    s32 temp_s0;
    u16 var_s0;
    void *temp_s1;
    void *temp_s2;

    temp_s1 = M2C_FIELD(arg0, void **, 0x64);
    temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s0 = func_80021CE4(3);
    if ((func_8002EFD0((s32) arg0) != 0) || (arg1 == 1)) {
        if (temp_s0 != 2) {
            if (temp_s0 != 1) {
                var_s0 = M2C_FIELD(temp_s1, u16 *, 0xE);
                if (temp_s0 == 0) {
                    var_s0 = M2C_FIELD(temp_s1, u16 *, 8);
                }
            } else {
                var_s0 = M2C_FIELD(temp_s1, u16 *, 4);
            }
        } else {
            var_s0 = M2C_FIELD(temp_s1, u16 *, 0xE);
        }
        M2C_FIELD(temp_s2, s16 *, 0x4C) = 0;
        M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
        M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) var_s0;
        M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
    }
}
