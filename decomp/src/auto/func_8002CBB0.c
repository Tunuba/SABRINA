#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80093A14[];
extern u8 D_80093A15;
extern u8 D_8006170C[];
extern u8 D_80061738[];
extern s32 D_8006D30C;
extern s32 D_8006D41C[];
extern s32 D_8006D5AC;
extern s32 D_8006D5B0;
extern s32 D_8006D5B8;


void func_8002CBB0(s32 arg0, u8 *arg1) {
    s32 temp_v0;
    s32 var_v1;
    s32 var_v1_2;
    u8 *var_v0;

    var_v1 = arg0 & 0xFF;
    if (var_v1 == 1) {
        var_v1_2 = 0;
        var_v0 = arg1;
        do {
            D_80093A14[var_v1_2] = *var_v0;
            var_v1_2 += 1;
            var_v0 = arg1 + var_v1_2;
        } while (var_v1_2 < 8);
        var_v1 = arg0 & 0xFF;
        if (D_8006D5B8 < ((((u8) D_80093A15 >> 4) * 0xA) + (D_80093A15 & 0xF))) {
            var_v1 = 4 & 0xFF;
        }
    }
    if (var_v1 == 4) {
        func_80029AA4(0);
        if (D_8006D30C >= 2) {
            printf((s32) "cbdataready: CdlDataEnd (track=%d,time=%d)\n", D_8006D5AC, func_8001626C(-1));
        }
        temp_v0 = D_8006D5AC + 1;
        D_8006D5AC = temp_v0;
        D_8006D5B8 = D_8006D41C[temp_v0];
        goto block_14;
    }
    if ((var_v1 == 5) && !(M2C_FIELD(arg1, u8 *, 0) & 1)) {
        D_8006D5B0 = 1;
        if (D_8006D30C >= 2) {
            printf((s32) "CdPlay Error:%s:%02x,%02x\n", func_80029A1C(5), M2C_FIELD(arg1, u8 *, 0), M2C_FIELD(arg1, u8 *, 1));
        }
        if (!(M2C_FIELD(arg1, u8 *, 0) & 0x11)) {
block_14:
            func_8002CD3C();
        }
    }
}
