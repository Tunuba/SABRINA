#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8005B994(void *arg0) {
    s32 var_a3;
    s32 var_t0;
    void *temp_a0;
    void *temp_a2;

    temp_a2 = arg0 + 0x74;
    var_a3 = 0;
    var_t0 = 0;
loop_2:
    if (var_a3 < M2C_FIELD(temp_a2, s32 *, 0x34)) {
        temp_a0 = var_t0 + temp_a2;
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x3C), s32 *, 0x54) = 2;
        var_a3 += 1;
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x3C), s32 *, 0x58) = 2;
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x3C), s32 *, 0x5C) = 2;
        var_t0 += 4;
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x3C), s8 *, 0x20) = 0x80;
        M2C_FIELD(temp_a0, void **, 0x3C) = NULL;
        M2C_FIELD(arg0, s32 *, 0x74) = -1;
        goto loop_2;
    }
    M2C_FIELD(temp_a2, s32 *, 0x1C) = 0;
}
