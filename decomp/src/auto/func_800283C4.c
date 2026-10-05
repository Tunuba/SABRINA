#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80090A08[];
extern u8 D_80090A50[];
extern u8 D_80090A98[];
extern u8 D_80090C78[];
extern u8 D_8006CFB8[];
extern s32 D_8006CFBC;
extern s32 D_8006CFD0;
extern s32 D_8006D018;
extern s32 func_80027D7C();
extern s32 func_80027DF0();
extern s32 func_80027F08();
extern s32 func_80027F4C();
extern s32 func_8002805C();
extern s32 func_800282D8();
extern s32 func_80028354();

extern s32 (*D_8006CF84)(s32);
extern s32 (*D_8006CF88)(s32);
extern s32 (*D_8006CF8C)(s32, s32);
extern s32 (*D_8006CF90)(s32);
extern s32 (*D_8006CF94)(s32);
extern s32 (*D_8006CF98)(s32);
extern s32 (*D_8006CFA8)(s32);

void func_800283C4(s32 arg0, s32 arg1) {
    s32 *var_t7;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_s4;
    s32 var_t1;
    s32 var_t4;
    u8 *var_a0;
    u8 *var_a2;
    u8 *var_a2_2;
    u8 *var_a3;
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_t0;
    u8 *var_t2;
    u8 *var_t3;
    u8 *var_t6;
    u8 *var_t8;
    u8 *var_t9;
    u8 *var_v1;

    D_8006CFBC = 0;
    D_8006CFD0 = 1;
    func_80028D0C();
    var_s0 = D_80090A98;
    D_8006CF84 = func_80027DF0;
    D_8006CF88 = func_80027D7C;
    D_8006CF8C = func_80027F4C;
    D_8006CF90 = func_8002805C;
    D_8006CF94 = func_800282D8;
    D_8006CF98 = func_80028354;
    *D_8006CFB8 = D_80090A98;
    D_8006CFA8 = func_80027F08;
    bzero((s32) D_80090A98, 0x1E0);
    var_s1 = D_80090C78;
    bzero((s32) D_80090C78, 0x780);
    var_s4 = 0;
    var_a3 = D_80090A98 + 0x30;
    var_v1 = D_80090A50;
    var_t9 = D_80090A50 + 3;
    var_t8 = D_80090A08 + 2;
    var_t7 = &D_8006D018;
    var_t6 = D_80090A08;
    M2C_FIELD(D_80090A98, s32 *, 0x30) = arg0;
    M2C_FIELD(D_80090A98, s32 *, 0x120) = arg1;
    do {
        var_a2 = var_s0 + 0x5D;
        M2C_FIELD(var_a3, u8 **, -0x24) = var_s1;
        M2C_FIELD(var_a3, u8 **, -0x20) = var_s0;
        M2C_FIELD(M2C_FIELD(var_a3, void **, 0), s8 *, 0) = 0xFF;
        var_a1 = 5;
        M2C_FIELD(M2C_FIELD(var_a3, void **, 0), s8 *, 1) = 0;
        M2C_FIELD(var_a3, u8 **, 0xC) = var_t6;
        M2C_FIELD(var_a3, u8 **, 0x10) = var_v1;
        *var_t7 = 0;
loop_2:
        *var_a2 = 0xFF;
        var_a1 -= 1;
        var_a2 += 1;
        if (var_a1 >= 0) {
            goto loop_2;
        }
        var_t0 = M2C_FIELD(var_a3, u8 **, -0x24);
        var_t4 = 0;
        var_t3 = var_t9;
        var_t2 = var_t8;
        var_t1 = 2;
        var_a0 = var_t0 + 0x40;
loop_4:
        M2C_FIELD(var_a0, u8 **, -0x30) = var_s0;
        M2C_FIELD(var_a0, void **, -0x10) = (void *) (M2C_FIELD(var_a3, void **, 0) + var_t1);
        var_a2_2 = var_t0 + 0x5D;
        M2C_FIELD(var_a0, s8 *, -8) = 0xFF;
        M2C_FIELD(var_a0, s8 *, -0xA) = 0;
        M2C_FIELD(var_a0, s8 *, -0xC) = 0;
        M2C_FIELD(M2C_FIELD(var_a0, void **, -0x10), s8 *, 0) = 0xFF;
        var_a1_2 = 5;
        M2C_FIELD(M2C_FIELD(var_a0, void **, -0x10), s8 *, 1) = 0;
        M2C_FIELD(var_a0, u8 **, -4) = var_t2;
        M2C_FIELD(var_a0, u8 **, 0) = var_t3;
loop_5:
        *var_a2_2 = 0xFF;
        var_a1_2 -= 1;
        var_a2_2 += 1;
        if (var_a1_2 >= 0) {
            goto loop_5;
        }
        var_t3 += 8;
        var_t2 += 8;
        var_t1 += 8;
        var_t4 += 1;
        var_a0 += 0xF0;
        var_t0 += 0xF0;
        if (var_t4 < 4) {
            goto loop_4;
        }
        var_t9 += 0x23;
        var_t8 += 0x23;
        var_t7 += 4;
        var_v1 += 0x23;
        var_t6 += 0x23;
        var_s1 += 0x3C0;
        var_s4 += 1;
        var_a3 += 0xF0;
        var_s0 += 0xF0;
    } while (var_s4 < 2);
    func_80025DA8();
    D_8006CFBC = 1;
}
