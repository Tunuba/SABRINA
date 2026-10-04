#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_80075B64[];
extern s32 D_8007C8A8;
extern u16 D_8007C8C4;
extern u16 D_8007C8C6;
extern u16 D_8007C92C;
extern s16 jugando;
extern s8 nivel_actual;
extern s32 D_8007CAFC;
extern s32 D_8007CB78;
extern void * D_8007CB8C;
extern s32 D_8007CB98;
extern s32 D_8007CB9C;
extern s32 D_8007CBBC;
extern s32 D_8007CC04;
extern s16 D_8007CC16;
extern s8 D_8007CC18;


void func_8005A360(void *arg0) {
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s16 temp_v0;
    s16 var_s2;
    s32 temp_s4;
    s32 temp_s4_2;
    s32 temp_v0_11;
    s32 temp_v0_16;
    s32 temp_v0_17;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    u16 temp_v0_10;
    u16 temp_v0_12;
    u16 temp_v0_13;
    u16 temp_v0_14;
    u16 temp_v0_15;
    u16 temp_v0_2;
    u16 temp_v0_8;
    u16 temp_v0_9;
    u16 temp_v1;
    u16 temp_v1_2;
    u16 temp_v1_3;
    void *temp_a0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s3;

    temp_s1 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s3 = M2C_FIELD(arg0, void **, 0x64);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    temp_s2 = arg0 + 0x74;
    switch (temp_v0) {
    case 9:
        D_8007CBBC = 1;
        temp_v0_2 = M2C_FIELD(temp_s3, u16 *, 0xE);
        if (M2C_FIELD(temp_s1, u8 *, 0x51) != temp_v0_2) {
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) temp_v0_2;
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
        }
        temp_v0_3 = p_sabrina->escala[0];
        if (temp_v0_3 < 0x1000) {
            p_sabrina->escala[0] = temp_v0_3 + 0xFA;
            p_sabrina->escala[1] = p_sabrina->escala[0];
            p_sabrina->escala[2] = p_sabrina->escala[0];
        } else {
            p_sabrina->escala[0] = 0x1666;
            p_sabrina->escala[1] = 0x1000;
            p_sabrina->escala[2] = 0x1666;
            M2C_FIELD(D_8007CB8C, s32 *, 0x54) = (s32) p_sabrina->escala[0];
            M2C_FIELD(D_8007CB8C, s32 *, 0x58) = (s32) p_sabrina->escala[1];
            M2C_FIELD(D_8007CB8C, s32 *, 0x5C) = (s32) p_sabrina->escala[2];
        }
        func_800487B0((s32) arg0, (s32) p_sabrina, 0x96);
        temp_v0_4 = func_8003E060();
        if ((temp_v0_4 != 0x57) || (temp_v0_4 == -1)) {
            func_8003DDA0(0x58, 0);
            func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
            M2C_FIELD(arg0, s16 *, 0x70) = 0xA;
            func_8002205C((s32) &sp30, 0, (s32) M2C_FIELD(arg0, s16 *, 0x32));
            sp30 = ((s32) ((sp30 >> 4) * 0x600) >> 8) << 8;
            temp_v0_5 = ((s32) ((sp34 >> 4) * 0x600) >> 8) << 8;
            sp34 = temp_v0_5;
            sp38 = ((s32) ((sp38 >> 4) * 0x600) >> 8) << 8;
            sp34 = temp_v0_5 + 0xFFFB8000;
            sp3C = M2C_FIELD(arg0, s32 *, 0x24);
            sp40 = M2C_FIELD(arg0, s32 *, 0x28);
            sp44 = M2C_FIELD(arg0, s32 *, 0x2C);
            sp40 = (sp40 - 0x4CCD) - 0x7FFF;
            func_80034FD0((s32) &sp30, (s32) &sp3C);
            p_sabrina->escala[0] = 0x1666;
            p_sabrina->escala[1] = 0x1000;
            p_sabrina->escala[2] = 0x1666;
            M2C_FIELD(D_8007CB8C, s32 *, 0x54) = (s32) p_sabrina->escala[0];
            M2C_FIELD(D_8007CB8C, s32 *, 0x58) = (s32) p_sabrina->escala[1];
            M2C_FIELD(D_8007CB8C, s32 *, 0x5C) = (s32) p_sabrina->escala[2];
            func_80033AD8((s32) p_sabrina);
            func_80055CAC((s32) D_8007CB8C);
            return;
        }
    default:
        return;
    case 10:
        temp_v0_6 = func_8003E060();
        if ((temp_v0_6 != 0x58) || (temp_v0_6 == -1)) {
            M2C_FIELD(arg0, s16 *, 0x70) = 0xD;
            func_8003DDA0(0x59, 0);
            func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
            func_80035098();
            func_80030E64();
            func_80037278(D_8007CAFC, (s32) p_sabrina);
            M2C_FIELD(arg0, s16 *, 0x70) = 0;
            D_8007CB78 = 0xA;
            D_8007CBBC = 0;
            return;
        }
        break;
    case 13:
        temp_v0_7 = func_8003E060();
        if ((temp_v0_7 != 0x59) || (temp_v0_7 == -1)) {
            M2C_FIELD(arg0, s16 *, 0x70) = 0;
            func_8003DFF0();
            func_8003DD44((D_8007C8C4 * 0xF) & 0xFF);
            return;
        }
        break;
    case 0:
        temp_v1 = M2C_FIELD(temp_s2, u16 *, 0x38);
        M2C_FIELD(temp_s2, u16 *, 0x38) = (u16) (temp_v1 + 1);
        if (temp_v1 >= 0xBU) {
            M2C_FIELD(arg0, s16 *, 0x70) = 1;
            M2C_FIELD(temp_s2, s16 *, 0x3C) = 1;
            D_8007CB98 = 1;
            D_8007C8A8 = 4;
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s3, u16 *, 0xC);
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
            return;
        }
        temp_v0_8 = M2C_FIELD(temp_s3, u16 *, 0);
        if (M2C_FIELD(temp_s1, u8 *, 0x51) != temp_v0_8) {
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) temp_v0_8;
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
            M2C_FIELD(temp_s2, s16 *, 0x3C) = 0;
        }
        func_80021D44((s32) (arg0 + 0x32), (s32) func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z), 0x2D);
        return;
    case 1:
        M2C_FIELD(temp_s2, u16 *, 0x38) = 0U;
        if (M2C_FIELD(temp_s1, u8 *, 0x50) == 0x28) {
            M2C_FIELD(temp_s2, u16 *, 0x3A) = func_80021CE4(3);
            func_800249CC((s32) arg0, M2C_FIELD(temp_s2, u16 *, 0x3A) + 0x14);
            M2C_FIELD(temp_s2, s16 *, 0x3C) = 3;
        }
        if (func_8002EFD0((s32) arg0) != 0) {
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s3, u16 *, 0);
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
        }
        if (D_8007CB9C != 0) {
            if (D_80075B64[M2C_FIELD(temp_s2, u16 *, 0x3A) + (D_8007C92C * 3)] != 0) {
                M2C_FIELD(arg0, s16 *, 0x70) = 2;
                return;
            }
            M2C_FIELD(arg0, s16 *, 0x70) = 3;
            return;
        }
        break;
    case 2:
        temp_v1_2 = M2C_FIELD(temp_s2, u16 *, 0x38);
        M2C_FIELD(temp_s2, u16 *, 0x38) = (u16) (temp_v1_2 + 1);
        if (temp_v1_2 >= 0x12DU) {
            M2C_FIELD(arg0, s16 *, 0x70) = 6;
            M2C_FIELD(temp_s2, s16 *, 0x3C) = 4;
        }
        temp_v0_9 = M2C_FIELD(temp_s3, u16 *, 2);
        if (M2C_FIELD(temp_s1, u8 *, 0x51) != temp_v0_9) {
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) temp_v0_9;
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
        }
        func_80021D44((s32) (arg0 + 0x32), (s32) func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z), 0x2D);
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + ((s32) (rsin((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x32) >> 4));
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + ((s32) (rcos((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x32) >> 4));
        return;
    case 3:
        temp_v1_3 = M2C_FIELD(temp_s2, u16 *, 0x38);
        M2C_FIELD(temp_s2, u16 *, 0x38) = (u16) (temp_v1_3 + 1);
        if (temp_v1_3 >= 0x12DU) {
            temp_v0_10 = M2C_FIELD(temp_s3, u16 *, 8);
            if (M2C_FIELD(temp_s1, u8 *, 0x51) != temp_v0_10) {
                M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) temp_v0_10;
                M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
                M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
                TocarSonido(0x34, 0, 0x28, 2);
            }
            if (func_8002EFD0((s32) arg0) != 0) {
                M2C_FIELD(arg0, s16 *, 0x70) = 6;
                M2C_FIELD(temp_s2, s16 *, 0x3C) = 4;
                return;
            }
        } else {
            var_s2 = (func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z) + 0x800) & 0xFFF;
            temp_s4 = M2C_FIELD(arg0, s32 *, 0x24) + ((s32) (rsin((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x12C) >> 4);
            temp_a0 = arg0 + 0x24;
            temp_s4_2 = func_8001BE8C(temp_s4, M2C_FIELD(arg0, s32 *, 0x2C) + ((s32) (rcos((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x12C) >> 4), 0, 0);
            if ((s32) (func_8001C180((s32) temp_a0) >> 8) >= 0x41) {
                temp_v0_11 = (var_s2 - temp_s4_2) & 0xFFF;
                if (temp_v0_11 >= 0x801) {
                    var_s2 += (s32) (0x1000 - temp_v0_11) >> 1;
                } else {
                    var_s2 -= temp_v0_11 >> 1;
                }
            }
            func_80021D44((s32) (arg0 + 0x32), (s32) var_s2, 0x37);
            if (func_8001C180((s32) temp_a0) < 0x4900) {
                M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + ((s32) (rsin((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x1E) >> 4));
                M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + ((s32) (rcos((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x1E) >> 4));
                temp_v0_12 = M2C_FIELD(temp_s3, u16 *, 2);
                if (M2C_FIELD(temp_s1, u8 *, 0x51) != temp_v0_12) {
                    M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) temp_v0_12;
                    M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
                    M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
                    return;
                }
            } else {
                M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x800);
                M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) & 0xFFF);
                M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + ((s32) (rsin((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x1E) >> 4));
                M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + ((s32) (rcos((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x1E) >> 4));
                return;
            }
        }
        break;
    case 4:
        temp_v0_13 = M2C_FIELD(temp_s3, u16 *, 8);
        if (M2C_FIELD(temp_s1, u8 *, 0x51) != temp_v0_13) {
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) temp_v0_13;
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
        }
        if (func_8002EFD0((s32) arg0) != 0) {
            M2C_FIELD(arg0, s16 *, 0x70) = 6;
            M2C_FIELD(temp_s2, s16 *, 0x3C) = 4;
            return;
        }
        break;
    case 5:
        temp_v0_14 = M2C_FIELD(temp_s3, u16 *, 6);
        if (M2C_FIELD(temp_s1, u8 *, 0x51) != temp_v0_14) {
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) temp_v0_14;
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
        }
        if (func_8002EFD0((s32) arg0) != 0) {
            M2C_FIELD(arg0, s16 *, 0x70) = 6;
            M2C_FIELD(temp_s2, s16 *, 0x3C) = 4;
            return;
        }
        break;
    case 6:
        M2C_FIELD(temp_s2, u16 *, 0x38) = 0U;
        M2C_FIELD(temp_s2, s16 *, 0x3C) = 0;
        M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) - 0x190);
        if (M2C_FIELD(arg0, s32 *, 0x54) < 5) {
            M2C_FIELD(arg0, s32 *, 0x54) = 5;
        }
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        temp_v0_15 = M2C_FIELD(temp_s3, u16 *, 0xC);
        if (M2C_FIELD(temp_s1, u8 *, 0x51) != temp_v0_15) {
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) temp_v0_15;
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
        }
        if (M2C_FIELD(temp_s1, u8 *, 0x50) == 0x28) {
            func_800249CC((s32) arg0, 0xC);
            M2C_FIELD(arg0, s16 *, 0x70) = 7;
            M2C_FIELD(arg0, s32 *, 0x54) = 5;
            M2C_FIELD(arg0, s32 *, 0x58) = 5;
            M2C_FIELD(arg0, s32 *, 0x5C) = 5;
        }
        if (func_8002EFD0((s32) arg0) != 0) {
            M2C_FIELD(arg0, s16 *, 0x70) = 7;
            return;
        }
        break;
    case 7:
        M2C_FIELD(arg0, s32 *, 0x24) = 0;
        M2C_FIELD(arg0, s32 *, 0x2C) = 0;
        M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) + 0x190);
        if (M2C_FIELD(arg0, s32 *, 0x54) >= 0x1000) {
            M2C_FIELD(arg0, s32 *, 0x54) = 0x1000;
            M2C_FIELD(arg0, s32 *, 0x58) = 0x1000;
            M2C_FIELD(arg0, s32 *, 0x5C) = 0x1000;
            M2C_FIELD(arg0, s16 *, 0x70) = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        return;
    case 8:
        func_80048228((s32) arg0);
        if (M2C_FIELD(arg0, u8 *, 0x20) & 0x80) {
            nivel_actual = 0;
            D_8007CC04 = 1;
            D_8007CC16 = 0;
            D_8007CC18 = 1;
            jugando = 0;
            return;
        }
        break;
    case 11:
        func_80031000();
        M2C_FIELD(arg0, s16 *, 0x70) = 0xC;
        return;
    case 14:
        p_sabrina->escala[0] -= 0xFA;
        if (p_sabrina->escala[0] < 5) {
            p_sabrina->escala[0] = 5;
        }
        p_sabrina->escala[1] = p_sabrina->escala[0];
        p_sabrina->escala[2] = p_sabrina->escala[0];
        M2C_FIELD(D_8007CB8C, s32 *, 0x54) = (s32) p_sabrina->escala[0];
        M2C_FIELD(D_8007CB8C, s32 *, 0x58) = (s32) p_sabrina->escala[1];
        M2C_FIELD(D_8007CB8C, s32 *, 0x5C) = (s32) p_sabrina->escala[2];
        func_80033AD8((s32) p_sabrina);
        func_80055CAC((s32) D_8007CB8C);
        if (M2C_FIELD(temp_s1, u8 *, 0x50) == 0x28) {
            func_800249CC((s32) arg0, 0xC);
        }
        if (func_8002EFD0((s32) arg0) != 0) {
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s3, u16 *, 0xA);
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
            func_8003DDA0(0x45, 0);
            func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
            M2C_FIELD(arg0, s16 *, 0x70) = 0xF;
            return;
        }
        break;
    case 15:
        temp_v0_16 = func_8003E060();
        if ((temp_v0_16 != 0x45) || (temp_v0_16 == -1)) {
            nivel_actual = 0;
            D_8007CC04 = 0;
            D_8007CC16 = 0;
            D_8007CC18 = 1;
            jugando = 0;
        }
        if (func_8002EFD0((s32) arg0) != 0) {
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s3, u16 *, 0);
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
            return;
        }
        break;
    case 17:
        if (M2C_FIELD(temp_s1, u8 *, 0x50) == 0x28) {
            func_800249CC((s32) arg0, 0xC);
        }
        if (func_8002EFD0((s32) arg0) != 0) {
            M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s3, u16 *, 4);
            M2C_FIELD(temp_s1, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
            func_8003DDA0(0x46, 0);
            func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
            M2C_FIELD(arg0, s16 *, 0x70) = 0x12;
            return;
        }
        break;
    case 18:
        func_80048228((s32) arg0);
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) & 0x7F);
        temp_v0_17 = func_8003E060();
        if ((temp_v0_17 != 0x46) || (temp_v0_17 == -1)) {
            nivel_actual = 0;
            D_8007CC04 = 1;
            D_8007CC16 = 0;
            D_8007CC18 = 1;
            jugando = 0;
        }
        break;
    }
}
