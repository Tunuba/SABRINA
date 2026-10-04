#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C8567[];
extern s32 D_800757F8[];
extern void * D_8007C9F8;


void func_8004C150(void) {
    s32 var_a0;
    s32 var_a1;
    s32 var_a3;
    void *temp_a2;
    void *temp_v1;

    var_a0 = 0;
loop_8:
    if (var_a0 < 0xD) {
        if ((s8) D_800C8567[var_a0] != 0) {
            var_a1 = 0;
            var_a3 = 0;
loop_6:
            temp_v1 = M2C_FIELD(D_8007C9F8, void **, 4);
            if (var_a1 < M2C_FIELD(temp_v1, s16 *, 0x5E)) {
                temp_a2 = M2C_FIELD(temp_v1, s32 *, 0x58) + var_a3;
                if (M2C_FIELD(temp_a2, u16 *, 0x16) == D_800757F8[var_a0]) {
                    M2C_FIELD(temp_a2, u8 *, 0x10) = (u8) (M2C_FIELD(temp_a2, u8 *, 0x10) + 0x20);
                    M2C_FIELD(temp_a2, u8 *, 0x12) = (u8) (M2C_FIELD(temp_a2, u8 *, 0x12) + 0x20);
                    M2C_FIELD(temp_a2, u8 *, 0x14) = (u8) (M2C_FIELD(temp_a2, u8 *, 0x14) + 0x20);
                }
                var_a1 += 1;
                var_a3 += 0x1C;
                goto loop_6;
            }
        }
        var_a0 += 1;
        goto loop_8;
    }
}
