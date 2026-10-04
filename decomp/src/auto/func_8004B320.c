#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800C8558;
extern s16 D_800C855A;
extern s16 D_800C855C;
extern s8 D_800C8567;
extern s8 D_800C8568;
extern s8 D_800C8569;
extern s8 D_800C856A;
extern s8 D_800C856B;
extern s8 D_800C856C;
extern s8 D_800C856D;
extern s8 D_800C856E;
extern s8 D_800C856F;
extern s8 D_800C8570;
extern s8 D_800C8571;
extern s8 D_800C8572;
extern s8 D_800C857E;
extern s8 D_800C857F;
extern s8 D_800C8580;
extern s8 D_800C8581;
extern u8 D_800C8586[];
extern u8 D_800C85CE[];
extern u8 D_800C8616[];
extern u8 D_800C865E[];
extern u8 D_800C86A6[];
extern u8 D_800C86B5[];
extern u8 D_800C86B6[];
extern u8 D_800C86BE[];
extern u8 D_800C86C6[];
extern s32 D_800C98A4;
extern s16 gemas;
extern s16 huevos;
extern s16 partida;
extern s16 D_8007C872;
extern s8 objetos_anacronicos;
extern s8 D_8007C88D;
extern s8 D_8007C88E;
extern s8 D_8007C88F;
extern s8 D_8007C890;
extern s8 D_8007C891;
extern s8 D_8007C892;
extern u16 D_8007C8C4;
extern u16 D_8007C8C6;
extern s8 nivel_actual;
extern s8 D_8007CB20;
extern u8 D_8007CB28;
extern s16 D_8007CB2A;
extern s16 D_8007CB2C;
extern s16 D_8007CB38;
extern u32 D_8007CB3C;
extern s32 D_8007CB40;
extern s32 D_8007CC70;


void func_8004B320(s32 arg0) {
    s16 var_v0_8;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a1_4;
    s32 temp_a1_5;
    s32 temp_a1_6;
    s32 temp_a1_7;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_6;
    s32 var_a0_7;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_a3_3;
    s32 var_a3_4;
    s32 var_a3_5;
    s32 var_a3_6;
    s32 var_a3_7;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    s32 var_v1_6;
    s32 var_v1_7;
    u32 var_v0;
    u32 var_v0_2;
    u32 var_v0_3;
    u32 var_v0_4;
    u32 var_v0_5;
    u32 var_v0_6;
    u32 var_v0_7;
    void *temp_a2;
    void *temp_a2_2;
    void *temp_a2_3;
    void *temp_a2_4;
    void *temp_a2_5;
    void *temp_a2_6;
    void *temp_a2_7;

    D_8007C872 = 0;
    D_8007CB20 = 0;
    D_8007CB38 = 0;
    func_8004BDA0();
    func_80056290(arg0);
    if (nivel_actual == 0xD) {
        func_8004C150();
    }
    func_8003DD44((D_8007C8C4 * 0xF) & 0xFF);
    func_8003DD74((D_8007C8C6 * 0xF) & 0xFF);
    func_8004B318();
    D_8007C890 = 0;
    D_8007C891 = 0;
    D_8007C892 = 0;
    D_8007C88D = D_800C857E;
    D_8007C88E = D_800C8581;
    D_8007C88F = D_800C857F;
    objetos_anacronicos = D_800C8580;
    huevos = 0;
    D_8007CC70 = 0;
    switch (arg0) {                                 /* switch 1 */
    case 1:                                         /* switch 1 */
    case 2:                                         /* switch 1 */
    case 3:                                         /* switch 1 */
        if (D_800C8567 != 0) {
            D_8007C890 = 1;
        }
        if (D_800C8568 != 0) {
            D_8007C891 = 1;
        }
        if (D_800C8569 != 0) {
            D_8007C892 = 1;
        }
        break;
    case 4:                                         /* switch 1 */
    case 5:                                         /* switch 1 */
    case 6:                                         /* switch 1 */
        if (D_800C856A != 0) {
            D_8007C890 = 1;
        }
        if (D_800C856B != 0) {
            D_8007C891 = 1;
        }
        if (D_800C856C != 0) {
            D_8007C892 = 1;
        }
        break;
    case 7:                                         /* switch 1 */
    case 8:                                         /* switch 1 */
    case 9:                                         /* switch 1 */
        if (D_800C856D != 0) {
            D_8007C890 = 1;
        }
        if (D_800C856E != 0) {
            D_8007C891 = 1;
        }
        if (D_800C856F != 0) {
            D_8007C892 = 1;
        }
        break;
    case 10:                                        /* switch 1 */
    case 11:                                        /* switch 1 */
    case 12:                                        /* switch 1 */
        if (D_800C8570 != 0) {
            D_8007C890 = 1;
        }
        if (D_800C8571 != 0) {
            D_8007C891 = 1;
        }
        if (D_800C8572 != 0) {
            D_8007C892 = 1;
        }
        break;
    case 14:                                        /* switch 1 */
        D_8007C872 = 1;
        break;
    }
    if (*(D_800C86C6 + (arg0 * 0x141)) != 0) {
        D_800C98A4 = (s32) nivel_actual;
        func_8004C224();
        var_v1 = 0;
        var_a0 = 1;
loop_39:
        temp_a1 = D_800C98A4 * 0x141;
        if (var_v1 < *(D_800C8586 + temp_a1)) {
            if (*(var_a0 + (D_800C8586 + temp_a1)) != 0) {
                var_v0 = 0;
                var_a3 = 0;
loop_37:
                if (var_v0 < (u32) D_8007CB3C) {
                    temp_a2 = var_a3 + D_8007CB40;
                    if ((M2C_FIELD(temp_a2, s16 *, 0xC) == 4) && ((var_v1 + 1) == M2C_FIELD(temp_a2, s32 *, 0x1C))) {
                        M2C_FIELD(((var_v0 * 0x9C) + D_8007CB40), s16 *, 0x1A) = 4;
                        D_8007CB28 += 1;
                    } else {
                        var_v0 += 1;
                        var_a3 += 0x9C;
                        goto loop_37;
                    }
                }
            }
            var_v1 += 1;
            var_a0 += 1;
            goto loop_39;
        }
        var_v1_2 = 0;
        var_a0_2 = 1;
loop_49:
        temp_a1_2 = D_800C98A4 * 0x141;
        if (var_v1_2 < *(D_800C85CE + temp_a1_2)) {
            if (*(var_a0_2 + (D_800C85CE + temp_a1_2)) != 0) {
                var_v0_2 = 0;
                var_a3_2 = 0;
loop_47:
                if (var_v0_2 < (u32) D_8007CB3C) {
                    temp_a2_2 = var_a3_2 + D_8007CB40;
                    if ((M2C_FIELD(temp_a2_2, s16 *, 0xC) == 0x12) && ((var_v1_2 + 1) == M2C_FIELD(temp_a2_2, s32 *, 0x1C))) {
                        M2C_FIELD(((var_v0_2 * 0x9C) + D_8007CB40), s16 *, 0x1A) = 4;
                        D_8007CB28 += 1;
                    } else {
                        var_v0_2 += 1;
                        var_a3_2 += 0x9C;
                        goto loop_47;
                    }
                }
            }
            var_v1_2 += 1;
            var_a0_2 += 1;
            goto loop_49;
        }
        var_v1_3 = 0;
        var_a0_3 = 1;
loop_59:
        temp_a1_3 = D_800C98A4 * 0x141;
        if (var_v1_3 < *(D_800C8616 + temp_a1_3)) {
            if (*(var_a0_3 + (D_800C8616 + temp_a1_3)) != 0) {
                var_v0_3 = 0;
                var_a3_3 = 0;
loop_57:
                if (var_v0_3 < (u32) D_8007CB3C) {
                    temp_a2_3 = var_a3_3 + D_8007CB40;
                    if ((M2C_FIELD(temp_a2_3, s16 *, 0xC) == 0x13) && ((var_v1_3 + 1) == M2C_FIELD(temp_a2_3, s32 *, 0x1C))) {
                        M2C_FIELD(((var_v0_3 * 0x9C) + D_8007CB40), s16 *, 0x1A) = 4;
                        D_8007CB28 += 1;
                    } else {
                        var_v0_3 += 1;
                        var_a3_3 += 0x9C;
                        goto loop_57;
                    }
                }
            }
            var_v1_3 += 1;
            var_a0_3 += 1;
            goto loop_59;
        }
        var_v1_4 = 0;
        var_a0_4 = 1;
loop_69:
        temp_a1_4 = D_800C98A4 * 0x141;
        if (var_v1_4 < *(D_800C865E + temp_a1_4)) {
            if (*(var_a0_4 + (D_800C865E + temp_a1_4)) != 0) {
                var_v0_4 = 0;
                var_a3_4 = 0;
loop_67:
                if (var_v0_4 < (u32) D_8007CB3C) {
                    temp_a2_4 = var_a3_4 + D_8007CB40;
                    if ((M2C_FIELD(temp_a2_4, s16 *, 0xC) == 0x17) && ((var_v1_4 + 1) == M2C_FIELD(temp_a2_4, s32 *, 0x1C))) {
                        M2C_FIELD(((var_v0_4 * 0x9C) + D_8007CB40), s16 *, 0x1A) = 4;
                        D_8007CB28 += 1;
                    } else {
                        var_v0_4 += 1;
                        var_a3_4 += 0x9C;
                        goto loop_67;
                    }
                }
            }
            var_v1_4 += 1;
            var_a0_4 += 1;
            goto loop_69;
        }
        var_v1_5 = 0;
        var_a0_5 = 1;
loop_79:
        temp_a1_5 = D_800C98A4 * 0x141;
        if (var_v1_5 < *(D_800C86B6 + temp_a1_5)) {
            if (*(var_a0_5 + (D_800C86B6 + temp_a1_5)) != 0) {
                var_v0_5 = 0;
                var_a3_5 = 0;
loop_77:
                if (var_v0_5 < (u32) D_8007CB3C) {
                    temp_a2_5 = var_a3_5 + D_8007CB40;
                    if ((M2C_FIELD(temp_a2_5, s16 *, 0xC) == 0x28) && ((var_v1_5 + 1) == M2C_FIELD(temp_a2_5, s32 *, 0x1C))) {
                        M2C_FIELD(((var_v0_5 * 0x9C) + D_8007CB40), s16 *, 0x1A) = 4;
                        D_8007CB28 += 1;
                    } else {
                        var_v0_5 += 1;
                        var_a3_5 += 0x9C;
                        goto loop_77;
                    }
                }
            }
            var_v1_5 += 1;
            var_a0_5 += 1;
            goto loop_79;
        }
        var_v1_6 = 0;
        var_a0_6 = 1;
loop_89:
        temp_a1_6 = D_800C98A4 * 0x141;
        if (var_v1_6 < *(D_800C86BE + temp_a1_6)) {
            if (*(var_a0_6 + (D_800C86BE + temp_a1_6)) != 0) {
                var_v0_6 = 0;
                var_a3_6 = 0;
loop_87:
                if (var_v0_6 < (u32) D_8007CB3C) {
                    temp_a2_6 = var_a3_6 + D_8007CB40;
                    if ((M2C_FIELD(temp_a2_6, s16 *, 0xC) == 0x29) && ((var_v1_6 + 1) == M2C_FIELD(temp_a2_6, s32 *, 0x1C))) {
                        M2C_FIELD(((var_v0_6 * 0x9C) + D_8007CB40), s16 *, 0x1A) = 4;
                        D_8007CB28 += 1;
                    } else {
                        var_v0_6 += 1;
                        var_a3_6 += 0x9C;
                        goto loop_87;
                    }
                }
            }
            var_v1_6 += 1;
            var_a0_6 += 1;
            goto loop_89;
        }
        var_v1_7 = 0;
        var_a0_7 = 1;
loop_99:
        temp_a1_7 = D_800C98A4 * 0x141;
        if (var_v1_7 < *(D_800C86A6 + temp_a1_7)) {
            if (*(var_a0_7 + (D_800C86A6 + temp_a1_7)) != 0) {
                var_v0_7 = 0;
                var_a3_7 = 0;
loop_97:
                if (var_v0_7 < (u32) D_8007CB3C) {
                    temp_a2_7 = var_a3_7 + D_8007CB40;
                    if ((M2C_FIELD(temp_a2_7, s16 *, 0xC) == 0x2D) && ((var_v1_7 + 1) == M2C_FIELD(temp_a2_7, s32 *, 0x1C))) {
                        M2C_FIELD(((var_v0_7 * 0x9C) + D_8007CB40), s16 *, 0x1A) = 4;
                        D_8007CB28 += 1;
                    } else {
                        var_v0_7 += 1;
                        var_a3_7 += 0x9C;
                        goto loop_97;
                    }
                }
            }
            var_v1_7 += 1;
            var_a0_7 += 1;
            goto loop_99;
        }
    }
    func_8004C22C();
    func_8004B14C();
    switch (nivel_actual) {                         /* switch 2 */
    case 1:                                         /* switch 2 */
    case 2:                                         /* switch 2 */
    case 3:                                         /* switch 2 */
        var_v0_8 = gemas;
block_106:
        D_8007CB28 = (u8) var_v0_8;
        break;
    case 4:                                         /* switch 2 */
    case 5:                                         /* switch 2 */
    case 6:                                         /* switch 2 */
        var_v0_8 = D_800C8558;
        goto block_106;
    case 7:                                         /* switch 2 */
    case 8:                                         /* switch 2 */
    case 9:                                         /* switch 2 */
        var_v0_8 = D_800C855A;
        goto block_106;
    case 10:                                        /* switch 2 */
    case 11:                                        /* switch 2 */
    case 12:                                        /* switch 2 */
        var_v0_8 = D_800C855C;
        goto block_106;
    }
    D_8007CB2A = (s16) D_8007CB28;
    D_8007CB2C = partida - 1;
    huevos = (s16) *(D_800C86B5 + (nivel_actual * 0x141));
}
