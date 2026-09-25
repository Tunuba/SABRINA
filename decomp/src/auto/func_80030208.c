#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C855E;
extern s32 D_800C98B4;
extern s32 D_800C98B8;
extern s16 partida;
extern u16 D_8007C872;
extern u16 D_8007C8C6;
extern s32 jugando;
extern s8 nivel_actual;
extern s8 D_8007CA01;
extern s16 D_8007CA20;
extern s32 D_8007CA50;
extern s8 vida_barra;
extern s16 D_8007CB70;
extern s32 D_8007CB78;
extern s32 D_8007CB80;
extern s32 D_8007CB84;
extern s8 D_8007CB88;
extern void * D_8007CB8C;
extern s32 D_8007CBA4;
extern s16 D_8007CBF0;
extern s16 D_8007CC16;
extern s8 D_8007CC18;
extern s32 DanoPorEnemigo();
extern s32 func_80024DF4();
extern s32 func_80024DFC();
extern s32 func_80024F6C();


void func_80030208(void *arg0) {
    s16 temp_v0_11;
    s16 temp_v0_4;
    s16 var_v0;
    s16 var_v0_2;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s5;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s8 temp_v0_10;
    u8 temp_v0_12;
    u8 temp_v0_13;
    u8 temp_v1;
    void *temp_s1;
    void *temp_s2;
    void *temp_s3;
    void *temp_s3_2;
    void *temp_s4;

    temp_s5 = M2C_FIELD(arg0, s32 *, 0x1C);
    temp_s1 = M2C_FIELD(D_8007CB8C, void **, 0x1C);
    temp_s2 = M2C_FIELD(D_8007CB8C, void **, 0x64);
    temp_s3 = M2C_FIELD(arg0, void **, 0x64);
    temp_s4 = arg0 + 0x74;
    if (D_8007CB80 == 0) {
        func_800318F4((s32) arg0);
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
    M2C_FIELD(M2C_FIELD(D_8007CB8C, void **, 0x6C), s16 *, 0x1A) = 2;
    vida_barra = p_sabrina->vida;
    if ((partida <= 0) && (nivel_actual != 0xE)) {
        D_8007CA20 = 0xDD;
        if (M2C_FIELD(arg0, s16 *, 0x70) != 8) {
            M2C_FIELD(arg0, s16 *, 0x70) = 8;
            D_8007CB84 = 0x12C;
            D_8007CB80 = 1;
            func_800313E4();
            M2C_FIELD(p_sabrina, s32 (**)(), 4) = func_80024DF4;
            p_sabrina->aviso = (void (*)(Objeto *, Objeto *)) func_80024F6C;
        }
    }
    if (D_800C98B4 == 1) {
        D_800C98B4 = 2;
        func_8003DDA0(0x4F, 0);
        func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
        D_8007CB88 = 1;
        temp_v0 = p_sabrina->escala[0];
        if (temp_v0 < 0x1000) {
            p_sabrina->escala[0] = temp_v0 + 0xFA;
            p_sabrina->escala[1] = p_sabrina->escala[0];
            p_sabrina->escala[2] = p_sabrina->escala[0];
            return;
        }
        p_sabrina->escala[0] = 0x1666;
        p_sabrina->escala[1] = 0x1000;
        p_sabrina->escala[2] = 0x1666;
        M2C_FIELD(D_8007CB8C, s32 *, 0x54) = (s32) p_sabrina->escala[0];
        M2C_FIELD(D_8007CB8C, s32 *, 0x58) = (s32) p_sabrina->escala[1];
        M2C_FIELD(D_8007CB8C, s32 *, 0x5C) = (s32) p_sabrina->escala[2];
        return;
    }
    if (D_800C98B4 == 2) {
        temp_v0_2 = func_8003E060();
        if ((temp_v0_2 != 0x4F) || (temp_v0_2 == -1)) {
            func_8003DDFC();
            D_800C98B4 = 0;
            D_8007CB88 = 0;
        }
        temp_v0_3 = p_sabrina->escala[0];
        if (temp_v0_3 < 0x1000) {
            p_sabrina->escala[0] = temp_v0_3 + 0xFA;
            p_sabrina->escala[1] = p_sabrina->escala[0];
            p_sabrina->escala[2] = p_sabrina->escala[0];
            return;
        }
        p_sabrina->escala[0] = 0x1666;
        p_sabrina->escala[1] = 0x1000;
        p_sabrina->escala[2] = 0x1666;
        M2C_FIELD(D_8007CB8C, s32 *, 0x54) = (s32) p_sabrina->escala[0];
        M2C_FIELD(D_8007CB8C, s32 *, 0x58) = (s32) p_sabrina->escala[1];
        M2C_FIELD(D_8007CB8C, s32 *, 0x5C) = (s32) p_sabrina->escala[2];
        return;
    }
    if ((nivel_actual == 0xD) && (D_800C98B8 != 0)) {
        D_800C98B8 = 0;
        D_8007CB78 = 0xA;
        if (D_800C855E < 0xC) {
            func_8003DDA0(0x50, 0);
            func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
            goto block_22;
        }
        func_8003DDA0(0x51, 0);
        func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
        M2C_FIELD(arg0, s16 *, 0x70) = 6;
        D_8007CB78 = 0;
        return;
    }
block_22:
    if (D_8007CB78 != 0) {
        D_8007CB78 -= 1;
        if (D_8007CB78 == 0) {
            D_8007CB78 = 0x1E;
            if (func_8003E060() == -1) {
                func_8003DDFC();
                D_8007CB78 = 0;
            }
        }
    }
    temp_v0_4 = M2C_FIELD(arg0, s16 *, 0x70);
    switch (temp_v0_4) {                            /* switch 1 */
    case 8:                                         /* switch 1 */
        D_8007CB84 -= 1;
        if (D_8007CB84 < 0) {
            nivel_actual = 0;
            D_8007CC16 = 0;
            D_8007CC18 = 1;
            jugando = 0;
        }
        break;
    case 0:                                         /* switch 1 */
        M2C_FIELD(temp_s4, s32 *, 8) = (s32) D_8007CA50;
        func_800325AC((s32) arg0, (s32) temp_s4, temp_s5);
        func_80032B98((s32) arg0, (s32) temp_s4);
        break;
    case 1:                                         /* switch 1 */
        M2C_FIELD(temp_s4, s32 *, 8) = 0;
        temp_s3_2 = M2C_FIELD(arg0, void **, 0x74);
        if (temp_s3_2 != NULL) {
            var_v0 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 0x30) + func_800221A8((s32) arg0, M2C_FIELD(temp_s3_2, s32 *, 0x24), M2C_FIELD(temp_s3_2, s32 *, 0x28) + 0x16666 + func_80021C3C(), M2C_FIELD(temp_s3_2, s32 *, 0x2C))) >> 4);
            if (var_v0 >= 0x10) {
                var_v0 = 0xF;
            }
            if (var_v0 < -0xF) {
                var_v0 = -0xF;
            }
            func_80021F70((s32) (temp_s4 + 0x1F), (s32) (s8) var_v0, 1);
            func_80021D44((s32) (arg0 + 0x32), (s32) func_8002218C((s32) arg0, M2C_FIELD(temp_s3_2, s32 *, 0x24), M2C_FIELD(temp_s3_2, s32 *, 0x2C)), 0x30);
        } else {
            func_80032F50((s32) arg0);
        }
        if (M2C_FIELD(arg0, s32 *, 0x58) >= 0xFFB) {
            M2C_FIELD(arg0, s32 *, 0x58) = 0x1000;
            M2C_FIELD(arg0, s32 *, 0x54) = 0x1666;
            M2C_FIELD(arg0, s32 *, 0x5C) = 0x1666;
        } else {
            M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) + 0xB4);
            M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) + 0xB4);
            M2C_FIELD(arg0, s32 *, 0x5C) = (s32) (M2C_FIELD(arg0, s32 *, 0x5C) + 0xB4);
        }
        break;
    case 4:                                         /* switch 1 */
        D_8007CB80 = 1;
        M2C_FIELD(arg0, s32 (**)(), 4) = func_80024DF4;
        M2C_FIELD(arg0, s32 (**)(), 8) = func_80024F6C;
        if (M2C_FIELD(arg0, s32 *, 0x58) >= 0xFFB) {
            M2C_FIELD(arg0, s32 *, 0x54) = 0x1000;
            M2C_FIELD(arg0, s32 *, 0x58) = 0x1000;
            M2C_FIELD(arg0, s32 *, 0x5C) = 0x1000;
            D_8007CB80 = 0;
            M2C_FIELD(arg0, s32 (**)(), 4) = (s32 (*)()) func_80024DFC;
            M2C_FIELD(arg0, s32 (**)(), 8) = (s32 (*)()) DanoPorEnemigo;
            M2C_FIELD(arg0, s32 *, 0x54) = 0x1666;
            M2C_FIELD(arg0, s32 *, 0x5C) = 0x1666;
            M2C_FIELD(arg0, s16 *, 0x70) = 0;
        } else {
            M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) + 0xB4);
            M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) + 0xB4);
            M2C_FIELD(arg0, s32 *, 0x5C) = (s32) (M2C_FIELD(arg0, s32 *, 0x5C) + 0xB4);
        }
        break;
    case 2:                                         /* switch 1 */
        if (D_8007C872 == 0) {
            D_8007CB80 = 1;
            M2C_FIELD(arg0, s32 (**)(), 4) = func_80024DF4;
            M2C_FIELD(arg0, s32 (**)(), 8) = func_80024F6C;
            temp_a0 = M2C_FIELD(arg0, s32 *, 0x54);
            if (temp_a0 < 0x64) {
                D_8007CB78 = 0;
                partida -= 1;
                func_80031698((s32) arg0);
                if (D_8007CBA4 != 0) {
                    D_8007CBF0 = 0;
                } else {
                    D_8007CBF0 = 1;
                }
            } else {
                M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_a0 + (((s32) (0x64 - temp_a0) >> 3) - 5));
                M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
                M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
                M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x7D);
            }
        }
        break;
    case 7:                                         /* switch 1 */
        temp_v0_5 = func_8003E060();
        if ((temp_v0_5 != 0x52) || (temp_v0_5 == -1)) {
            D_8007CB80 = 1;
            M2C_FIELD(arg0, s32 (**)(), 4) = func_80024DF4;
            M2C_FIELD(arg0, s32 (**)(), 8) = func_80024F6C;
            temp_a0_2 = M2C_FIELD(arg0, s32 *, 0x54);
            if (temp_a0_2 < 0x64) {
                D_8007CC18 = 1;
                D_8007CA01 = nivel_actual;
                D_8007CC16 = 0xE;
                nivel_actual = 0xE;
                jugando = 0;
            } else {
                M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_a0_2 + (((s32) (0x64 - temp_a0_2) >> 3) - 5));
                M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
                M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
                M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0xE1);
            }
        }
        temp_v0_6 = M2C_FIELD(arg0, s32 *, 0x54);
        if (temp_v0_6 >= 0x33) {
            M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_v0_6 - 0x32);
            M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
            M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
            M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x20D);
        }
        break;
    case 6:                                         /* switch 1 */
        if ((nivel_actual == 0xD) && (D_800C855E >= 0xC)) {
            temp_v0_7 = M2C_FIELD(arg0, s32 *, 0x54);
            if (temp_v0_7 < 0x1001) {
                M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_v0_7 + 0xFA);
                M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) + 0xFA);
                M2C_FIELD(arg0, s32 *, 0x5C) = (s32) (M2C_FIELD(arg0, s32 *, 0x5C) + 0xFA);
            }
            temp_v0_8 = func_8003E060();
            if ((temp_v0_8 != 0x51) || (temp_v0_8 == -1)) {
                func_8003DDA0(0x52, 0);
                func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
                M2C_FIELD(arg0, s16 *, 0x70) = 7;
                M2C_FIELD(arg0, s32 *, 0x54) = 0x1000;
                M2C_FIELD(arg0, s32 *, 0x58) = 0x1000;
                M2C_FIELD(arg0, s32 *, 0x5C) = 0x1000;
            }
        }
        if (func_8002EFD0((s32) arg0) != 0) {
            M2C_FIELD(temp_s5, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s5, s16 *, 0x4E) = 0x800;
            temp_v0_9 = func_80021CE4(4);
            if (temp_v0_9 != 3) {
                if (temp_v0_9 != 2) {
                    if (temp_v0_9 != 1) {
                        if (temp_v0_9 == 0) {
                            M2C_FIELD(temp_s5, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 0x2A);
                            var_v0_2 = 0x15;
                        } else {
                            M2C_FIELD(temp_s5, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 0x2C);
                            var_v0_2 = 0x16;
                        }
                    } else {
                        M2C_FIELD(temp_s5, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 0x2C);
                        var_v0_2 = 0x16;
                    }
                } else {
                    M2C_FIELD(temp_s5, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 0x2E);
                    var_v0_2 = 0x17;
                }
            } else {
                M2C_FIELD(temp_s5, s8 *, 0x51) = (s8) M2C_FIELD(temp_s3, u16 *, 0x30);
                var_v0_2 = 0x18;
            }
            D_8007CB70 = var_v0_2;
        }
        break;
    }
    temp_v0_10 = M2C_FIELD(temp_s4, s8 *, 0x23);
    if (temp_v0_10 != 0) {
        M2C_FIELD(temp_s4, s8 *, 0x23) = (s8) (temp_v0_10 - 1);
    }
    temp_v0_11 = M2C_FIELD(temp_s4, s16 *, 0x14);
    if (temp_v0_11 != 0) {
        M2C_FIELD(temp_s4, s16 *, 0x14) = (s16) (temp_v0_11 - 1);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s8 *, 0x65) = 0xFF;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s8 *, 0x66) = 0x40;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s8 *, 0x67) = 0x40;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s16 *, 0x60) = (s16) (M2C_FIELD(temp_s4, s16 *, 0x14) << 7);
    }
    temp_v1 = M2C_FIELD(temp_s1, u8 *, 0x51);
    if (temp_v1 == M2C_FIELD(temp_s2, u16 *, 4)) {
        temp_v0_12 = M2C_FIELD(temp_s1, u8 *, 0x50);
        if ((temp_v0_12 == 5) || (temp_v0_12 == 0xB)) {
            TocarSonido(0, 0, 0x2B, 0x7F);
        }
    } else if ((temp_v1 == M2C_FIELD(temp_s2, u16 *, 2)) && ((temp_v0_13 = M2C_FIELD(temp_s1, u8 *, 0x50), (temp_v0_13 == 7)) || (temp_v0_13 == 0x10))) {
        TocarSonido(0, 0, 0x2B, 0x7F);
    }
    if (M2C_FIELD(temp_s1, u8 *, 0x51) != M2C_FIELD(temp_s2, u16 *, 0x1C)) {
        M2C_FIELD(temp_s1, u8 *, 0x50) = (u8) M2C_FIELD(temp_s5, u8 *, 0x50);
        M2C_FIELD(temp_s1, s16 *, 0x4E) = (s16) M2C_FIELD(temp_s5, s16 *, 0x4E);
        switch (D_8007CB70) {                       /* switch 2 */
        case 0:                                     /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0);
            return;
        case 1:                                     /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 2);
            return;
        case 2:                                     /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 4);
            return;
        case 3:                                     /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 6);
            return;
        case 4:                                     /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 8);
            return;
        case 5:                                     /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0xA);
            return;
        case 6:                                     /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0xC);
            return;
        case 7:                                     /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0xE);
            return;
        case 8:                                     /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x10);
            return;
        case 9:                                     /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x12);
            return;
        case 10:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x14);
            return;
        case 11:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x16);
            return;
        case 12:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x18);
            return;
        case 13:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x1A);
            return;
        case 14:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x1C);
            return;
        case 15:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x1E);
            return;
        case 16:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x20);
            return;
        case 17:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x22);
            return;
        case 18:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x24);
            return;
        case 19:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x26);
            return;
        case 20:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x28);
            return;
        case 21:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x2A);
            return;
        case 22:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x2C);
            return;
        case 23:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x2E);
            return;
        case 24:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0x30);
            return;
        default:                                    /* switch 2 */
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0);
            return;
        }
    } else {
        M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x1000;
        if (func_8002EFD0((s32) D_8007CB8C) != 0) {
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s2, u16 *, 0);
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
        }
    }
}
