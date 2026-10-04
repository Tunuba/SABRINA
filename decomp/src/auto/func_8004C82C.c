#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C8538[];
extern s8 D_800C8560;
extern u8 D_800C8561[];
extern u8 D_800C8567[];
extern u8 D_800C8574[];
extern u8 D_800C857E[];
extern s32 D_800C98A4;
extern s32 D_800C98B0;
extern s32 D_800C98B4;
extern s8 D_800C98BC;
extern s8 D_800C98BD;
extern s8 D_800C98BE;
extern s8 D_800C98BF;
extern s8 D_800C98C0;
extern s8 D_800C98C1;
extern u8 D_800C98C4[];
extern s16 partida;
extern s8 objetos_anacronicos;
extern s8 D_8007C88D;
extern s8 D_8007C88E;
extern s8 D_8007C88F;
extern s8 D_8007C890;
extern s8 D_8007C891;
extern s8 D_8007C892;
extern s8 hechizos;
extern s8 D_8007C8B1;
extern s8 D_8007C8B2;
extern s8 D_8007C8B3;
extern s8 D_8007C8B4;
extern s8 D_8007C8B5;
extern s8 D_8007CB28;
extern s16 D_8007CB2A;
extern s16 D_8007CB2C;
extern s32 D_8007CBA4;
extern s32 D_8007CC6C;


void func_8004C82C(void) {
    s16 *var_s1;
    s32 var_a0;
    s32 var_a1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;

    memset((s32) &partida, 0, 0x13AC);
    partida = 5;
    D_800C8560 = 1;
    var_s0 = 0;
loop_2:
    if (var_s0 < 5) {
        D_800C8561[var_s0] = 0;
        var_s0 += 1;
        goto loop_2;
    }
    var_s0_2 = 0;
    var_a0 = 0;
    var_a1 = 0;
loop_5:
    if (var_s0_2 < 4) {
        D_800C8574[var_s0_2] = 1;
        D_800C98C4[var_a0] = 0;
        D_800C8538[var_a1] = 0;
        var_s0_2 += 1;
        var_a1 += 2;
        var_a0 += 4;
        goto loop_5;
    }
    var_s0_3 = 0;
    var_s1 = &partida;
loop_8:
    if (var_s0_3 < 0xD) {
        D_800C8567[var_s0_3] = 0;
        memset((s32) (var_s1 + 0x6E), 0, 0x141);
        var_s0_3 += 1;
        var_s1 += 0x141;
        goto loop_8;
    }
    var_s0_4 = 0;
loop_11:
    if (var_s0_4 < 4) {
        D_800C857E[var_s0_4] = 0;
        var_s0_4 += 1;
        goto loop_11;
    }
    D_800C98A4 = -1;
    D_800C98B0 = 1;
    objetos_anacronicos = 0;
    D_8007C88D = 0;
    D_8007C88E = 0;
    D_8007C88F = 0;
    D_8007C890 = 0;
    D_8007C891 = 0;
    D_8007C892 = 0;
    hechizos = 0;
    D_800C98BC = 0;
    D_8007C8B1 = 0;
    D_800C98BD = 0;
    D_8007C8B2 = 0;
    D_800C98BE = 0;
    D_8007C8B3 = 0;
    D_800C98BF = 0;
    D_8007C8B4 = 0;
    D_800C98C0 = 0;
    D_8007C8B5 = 0;
    D_8007CBA4 = 1;
    D_800C98C1 = 0;
    D_8007CB2A = -1;
    D_8007CB28 = 0;
    D_8007CB2C = partida;
    D_800C98B4 = 1;
    D_8007CC6C = 0;
}
