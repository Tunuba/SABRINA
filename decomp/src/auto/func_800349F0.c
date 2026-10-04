#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007C8C6;
extern s32 D_8007CA50;
extern s32 D_8007CB00;
extern s32 D_8007CB04;
extern s32 D_8007CB08;
extern s16 D_8007CB0C;
extern s32 D_8007CBA4;
extern s32 D_8007CBA8;
extern s32 D_8007CBEC;


void func_800349F0(void *arg0) {
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 var_v0;
    void *temp_s1;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    temp_s1 = arg0 + 0x74;
    switch (temp_v0) {
    case 0:
        if (M2C_FIELD(temp_s1, s32 *, 0x10) != 0) {
            M2C_FIELD(arg0, s16 *, 0x70) = 6;
            M2C_FIELD(temp_s1, s16 *, 0xE) = 0x10;
            M2C_FIELD(arg0, s32 *, 0x54) = 5;
            M2C_FIELD(arg0, s32 *, 0x58) = 5;
            M2C_FIELD(arg0, s32 *, 0x5C) = 5;
            M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x74), s32 *, 0);
            M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x74), s32 *, 4);
            M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x74), s32 *, 8);
            TocarSonido(0x31, 0, 0x2A, 0x7F);
            return;
        }
        M2C_FIELD(arg0, M2C_UNK (**)(void *), 0xC)();
        return;
    case 6:
        M2C_FIELD(temp_s1, s16 *, 0xE) = (s16) (M2C_FIELD(temp_s1, s16 *, 0xE) - 1);
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(temp_s1, s32 *, 0x18));
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(temp_s1, s32 *, 0x1C));
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(temp_s1, s32 *, 0x20));
        M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) + 0x100);
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) + 0x100);
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) (M2C_FIELD(arg0, s32 *, 0x5C) + 0x100);
        if (M2C_FIELD(temp_s1, s16 *, 0xE) <= 0) {
            M2C_FIELD(arg0, s16 *, 0x70) = 1;
            M2C_FIELD(arg0, s32 *, 0x54) = 0x1000;
            M2C_FIELD(arg0, s32 *, 0x58) = 0x1000;
            M2C_FIELD(arg0, s32 *, 0x5C) = 0x1000;
            return;
        }
        return;
    case 1:
        temp_v0_2 = M2C_FIELD(temp_s1, s32 *, 0x10);
        if ((temp_v0_2 != 0) && (func_80034F84((s32) arg0, temp_v0_2) != 0)) {
            temp_v0_3 = M2C_FIELD(temp_s1, s32 *, 0x10);
            temp_v0_4 = func_8002225C((s32) arg0, M2C_FIELD(temp_v0_3, s32 *, 0x24), M2C_FIELD(temp_v0_3, s32 *, 0x28), M2C_FIELD(temp_v0_3, s32 *, 0x2C));
            if (temp_v0_4 < 0x38000) {
                temp_v1 = M2C_FIELD(temp_s1, s32 *, 0x10);
                if ((M2C_FIELD(temp_v1, s16 *, 0x70) == 0) && (M2C_FIELD((temp_v1 + 0x74), s8 *, 0x1D) == 0)) {
                    D_8007CBEC = (s32) M2C_FIELD(temp_s1, s16 *, 0xA);
                    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + ((s32) (M2C_FIELD(temp_s1, s32 *, 4) * rsin((s32) M2C_FIELD(temp_s1, s16 *, 8))) >> 0xC));
                    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + ((s32) (M2C_FIELD(temp_s1, s32 *, 4) * rcos((s32) M2C_FIELD(temp_s1, s16 *, 8))) >> 0xC));
                    D_8007CB00 = p_sabrina->x;
                    D_8007CB04 = p_sabrina->y;
                    D_8007CB08 = p_sabrina->z;
                    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + ((s32) (-M2C_FIELD(temp_s1, s32 *, 4) * rsin((s32) M2C_FIELD(temp_s1, s16 *, 8))) >> 0xC));
                    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + ((s32) (-M2C_FIELD(temp_s1, s32 *, 4) * rcos((s32) M2C_FIELD(temp_s1, s16 *, 8))) >> 0xC));
                    D_8007CB0C = p_sabrina->rot[1];
                    M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x10), s16 *, 0x70) = 1;
                    M2C_FIELD(temp_v1, void **, 0x74) = arg0;
                    M2C_FIELD(temp_s1, s16 *, 0xE) = 0x32;
                    M2C_FIELD(arg0, s16 *, 0x70) = 2;
                    sp2C = M2C_FIELD(arg0, s32 *, 0x24);
                    sp30 = M2C_FIELD(arg0, s32 *, 0x28);
                    sp34 = M2C_FIELD(arg0, s32 *, 0x2C);
                    temp_v0_5 = M2C_FIELD(temp_s1, s32 *, 0x2C);
                    sp20 = M2C_FIELD(temp_s1, s32 *, 0x24);
                    sp24 = M2C_FIELD(temp_s1, s32 *, 0x28);
                    sp28 = temp_v0_5;
                    temp_v0_6 = ((s32) ((sp20 >> 4) * 0x480) >> 8) << 8;
                    sp20 = temp_v0_6;
                    sp24 = D_8007CB04 + 0xFFFF0000;
                    temp_v0_7 = ((s32) ((temp_v0_5 >> 4) * 0x480) >> 8) << 8;
                    sp28 = temp_v0_7;
                    sp20 = sp2C + temp_v0_6;
                    sp28 = sp34 + temp_v0_7;
                    func_80034FD0((s32) &sp20, (s32) &sp2C);
                    D_8007CB00 = sp20;
                    D_8007CB04 = func_800223E8((s32) &sp20);
                    D_8007CB08 = sp28;
                    return;
                }
            } else if (temp_v0_4 >= 0x40001) {
                M2C_FIELD(arg0, M2C_UNK (**)(void *), 0xC)(arg0);
                return;
            }
        }
        break;
    case 2:
        D_8007CBA8 = 1;
        if (D_8007CBA4 != 0) {
            D_8007CBA4 = 0;
            func_8003DDA0(0x15, 0);
            func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
        } else {
            func_8003DEE8();
            func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
        }
        M2C_FIELD(arg0, s16 *, 0x70) = 3;
        return;
    case 3:
        func_80034F84((s32) arg0, M2C_FIELD(temp_s1, s32 *, 0x10));
        var_v0 = func_8003E060();
        if ((var_v0 < 0x15) || (var_v0 >= 0x45)) {
            var_v0 = -1;
        }
        if ((D_8007CA50 & 0x40) || (var_v0 == -1)) {
            M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0x10), s16 *, 0x70) = 0;
            M2C_FIELD(arg0, s16 *, 0x70) = 4;
            func_80035098();
            return;
        }
        break;
    case 4:
        func_8003DDFC();
        func_80034F84((s32) arg0, M2C_FIELD(temp_s1, s32 *, 0x10));
        M2C_FIELD(arg0, s16 *, 0x70) = 5;
        p_sabrina->estado = 0;
        if (D_8007CBA4 != 0) {
            D_8007CBA4 = 0;
            return;
        }
        break;
    case 5:
        func_80034F84((s32) arg0, M2C_FIELD(temp_s1, s32 *, 0x10));
        D_8007CBA8 = 0;
        return;
    default:
        M2C_FIELD(arg0, s16 *, 0x70) = 0;
        break;
    }
}
