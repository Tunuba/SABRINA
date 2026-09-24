#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800831B0[];
extern u8 D_800831D8[];
extern s32 * D_80063754;
extern s16 D_8006379C;
extern s16 D_8006379E;


s32 func_80011930(void *arg0, u32 arg1) {
    s16 temp_v1;
    s16 temp_v1_2;
    u16 var_v0;
    u16 var_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 4);
    if (temp_v1 >= 0) {
        var_v0 = (u16) D_8006379C - 1;
        if ((D_8006379C - 1) >= temp_v1) {
            var_v0 = (u16) M2C_FIELD(arg0, s16 *, 4);
        }
    } else {
        var_v0 = 0;
    }
    temp_v1_2 = M2C_FIELD(arg0, s16 *, 6);
    M2C_FIELD(arg0, s16 *, 4) = (s16) var_v0;
    if (temp_v1_2 >= 0) {
        var_v1 = (u16) D_8006379E - 1;
        if ((D_8006379E - 1) >= temp_v1_2) {
            var_v1 = (u16) M2C_FIELD(arg0, s16 *, 6);
        }
    } else {
        var_v1 = 0;
    }
    M2C_FIELD(arg0, s16 *, 6) = (s16) var_v1;
    if ((M2C_FIELD(arg0, u16 *, 0) & 0x3F) || ((u16) M2C_FIELD(arg0, s16 *, 4) & 0x3F)) {
        M2C_FIELD(D_800831B0, s32 *, 0) = (s32) (((s32) D_800831D8 & 0xFFFFFF) | 0x08000000);
        M2C_FIELD(D_800831B0, s32 *, 0x10) = 0xE6000000;
        M2C_FIELD(D_800831B0, s32 *, 4) = 0xE3000000;
        M2C_FIELD(D_800831B0, s32 *, 8) = 0xE4FFFFFF;
        M2C_FIELD(D_800831B0, s32 *, 0xC) = 0xE5000000;
        M2C_FIELD(D_800831B0, s32 *, 0x18) = (s32) ((arg1 & 0xFFFFFF) | 0x60000000);
        M2C_FIELD(D_800831B0, s32 *, 0x14) = (s32) ((*D_80063754 & 0x7FF) | (((arg1 >> 0x1F) << 0xA) | 0xE1000000));
        M2C_FIELD(D_800831B0, s32 *, 0x1C) = (s32) M2C_FIELD(arg0, u16 *, 0);
        M2C_FIELD(D_800831D8, s32 *, 0) = 0x03FFFFFF;
        M2C_FIELD(D_800831B0, s32 *, 0x20) = (s32) M2C_FIELD(arg0, s16 *, 4);
        M2C_FIELD(D_800831D8, s32 *, 4) = (s32) (func_800120DC(3) | 0xE3000000);
        M2C_FIELD(D_800831D8, s32 *, 8) = (s32) (func_800120DC(4) | 0xE4000000);
        M2C_FIELD(D_800831D8, s32 *, 0xC) = (s32) (func_800120DC(5) | 0xE5000000);
    } else {
        M2C_FIELD(D_800831B0, s32 *, 0) = 0x05FFFFFF;
        M2C_FIELD(D_800831B0, s32 *, 4) = 0xE6000000;
        M2C_FIELD(D_800831B0, s32 *, 0xC) = (s32) ((arg1 & 0xFFFFFF) | 0x02000000);
        M2C_FIELD(D_800831B0, s32 *, 8) = (s32) ((*D_80063754 & 0x7FF) | (((arg1 >> 0x1F) << 0xA) | 0xE1000000));
        M2C_FIELD(D_800831B0, s32 *, 0x10) = (s32) M2C_FIELD(arg0, u16 *, 0);
        M2C_FIELD(D_800831B0, s32 *, 0x14) = (s32) M2C_FIELD(arg0, s16 *, 4);
    }
    func_80012094((s32) D_800831B0);
    return 0;
}
