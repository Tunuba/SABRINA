#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8001E164(s32 arg0) {
    s16 temp_s2;
    void *temp_v0;
    void *temp_v0_2;
    void *var_v1;

    temp_v0 = func_80018408();
    temp_s2 = (s16) M2C_FIELD(temp_v0, u16 *, 0x62);
    memset((s32) temp_v0, 0, 0x6C);
    M2C_FIELD(temp_v0, u16 *, 0x62) = (u16) temp_s2;
    M2C_FIELD(temp_v0, s16 *, 0x14) = 0x1000;
    M2C_FIELD(temp_v0, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_v0, s16 *, 0x24) = 0x1000;
    M2C_FIELD(temp_v0, s16 *, 0x34) = 0x1000;
    M2C_FIELD(temp_v0, s16 *, 0x3C) = 0x1000;
    M2C_FIELD(temp_v0, s16 *, 0x44) = 0x1000;
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
    if (arg0 != 0) {
        var_v1 = M2C_FIELD(arg0, void **, 4);
        if (var_v1 != NULL) {
loop_4:
            temp_v0_2 = M2C_FIELD(var_v1, void **, 8);
            if (temp_v0_2 != NULL) {
                var_v1 = temp_v0_2;
                goto loop_4;
            }
            M2C_FIELD(var_v1, void **, 8) = temp_v0;
            M2C_FIELD(temp_v0, void **, 0xC) = var_v1;
        } else {
            M2C_FIELD(arg0, void **, 4) = temp_v0;
        }
    }
    return (s32) temp_v0;
}
