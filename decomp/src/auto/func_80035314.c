#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C64FC;
extern s32 D_800C6500;
extern s32 D_800C6504;
extern s32 D_800C6508;
extern s32 D_800C650C;
extern s32 D_800C6510;
extern s32 D_8006C444;
extern s32 D_8006C448;
extern s32 D_8006C44C;
extern s32 D_8006C450;
extern s32 D_8006C454;
extern s32 D_8006C458;
extern s16 D_8007C872;
extern s32 D_8007CA50;
extern s16 D_8007CAE2;
extern s16 D_8007CAE4;
extern void * D_8007CBAC;
extern void * D_8007CBB0;
extern s32 D_8007CBBC;
extern u16 D_8007CBC0;
extern u16 D_8007CBD4;


void func_80035314(void *arg0) {
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    s32 sp6C;
    s32 sp70;
    s32 sp74;
    s32 sp78;
    s32 sp84;
    s16 sp92;
    s16 sp94;
    s16 sp96;
    ObjExtra *temp_s4;
    ObjExtra *temp_s4_2;
    s16 temp_v0;
    s16 var_v0_2;
    s16 var_v0_3;
    s32 temp_a0;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_s2_4;
    s32 temp_s2_5;
    s32 temp_s3_2;
    s32 temp_s3_3;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0;
    s32 var_v1;
    s8 temp_v0_2;
    s8 var_v1_2;
    void *temp_s0;
    void *temp_s3;
    void *temp_v0_6;

    D_8007CBC0 = D_8007CBD4;
    D_8007CBD4 = 0xFFEF;
    temp_s0 = arg0 + 0x74;
    func_80047710();
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
    temp_s3 = temp_s0 + 0x1C;
    if (p_sabrina == NULL) {

    } else {
        func_80036250();
        func_8003630C();
        temp_s4 = &p_sabrina->extra;
        sp3C = p_sabrina->x - M2C_FIELD(arg0, s32 *, 0x24);
        sp40 = p_sabrina->y - M2C_FIELD(arg0, s32 *, 0x28);
        sp44 = p_sabrina->z - M2C_FIELD(arg0, s32 *, 0x2C);
        temp_s2 = func_8001BF8C(0, 0, sp3C, sp44);
        func_8001C45C((s32) &sp3C);
        temp_s2_2 = (s32) (temp_s2 + 0xFFFC0000) >> 4;
        temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
        switch (temp_v0) {
        case 6:
            func_80036410((s32) arg0, D_800C6508, D_800C650C, D_800C6510, /* extra? */ D_800C64FC, /* extra? */ D_800C6500, /* extra? */ D_800C6504, /* extra? */ 3);
            func_80036524((s32) arg0, D_800C64FC, D_800C6500, D_800C6504);
            break;
        case 4:
            if ((D_8007CBAC != NULL) && (D_8007CBB0 != NULL)) {
                sp54 = M2C_FIELD(D_8007CBB0, s32 *, 0x24);
                sp58 = M2C_FIELD(D_8007CBB0, s32 *, 0x28);
                sp5C = M2C_FIELD(D_8007CBB0, s32 *, 0x2C);
                M2C_FIELD(temp_s0, s32 *, 0x44) = func_8002225C((s32) D_8007CBAC, sp54, M2C_FIELD(D_8007CBAC, s32 *, 0x28), sp5C);
                D_8007C872 = 1;
                func_80034FD0((s32) (D_8007CBB0 + 0x24), (s32) (D_8007CBAC + 0x24));
                M2C_FIELD(arg0, s16 *, 0x70) = 5;
            }
            break;
        case 5:
            func_80036524((s32) arg0, D_800C64FC, D_800C6500, D_800C6504);
            func_80036410((s32) arg0, D_800C6508, D_800C650C, D_800C6510, /* extra? */ D_800C64FC, /* extra? */ D_800C6500, /* extra? */ D_800C6504, /* extra? */ 3);
            D_8006C444 = (s32) M2C_FIELD(arg0, s32 *, 0x24) >> 8;
            D_8006C448 = (s32) M2C_FIELD(arg0, s32 *, 0x28) >> 8;
            var_v0 = (s32) M2C_FIELD(arg0, s32 *, 0x2C) >> 8;
block_71:
            D_8006C44C = var_v0;
            break;
        case 0:
            temp_v0_2 = M2C_FIELD(temp_s0, s8 *, 0x25);
            if (temp_v0_2 >= 0) {
                M2C_FIELD(temp_s0, s8 *, 0x25) = (s8) (temp_v0_2 - 1);
                if (M2C_FIELD(temp_s0, s8 *, 0x25) < 0) {
                    M2C_FIELD(temp_s0, s8 *, 0x25) = 0;
                }
            }
            if (D_8007CA50 & 3) {
                if ((D_8007CBBC == 0) && (M2C_FIELD(temp_s0, s8 *, 0x25) == 0)) {
                    M2C_FIELD(temp_s0, s8 *, 0x5C) = -0x32;
                    if (D_8007CA50 & 2) {
                        M2C_FIELD(temp_s0, s16 *, 0x40) = -0x12C;
                    }
                    if (D_8007CA50 & 1) {
                        var_v0_2 = 0x12C;
                        goto block_26;
                    }
                }
            } else {
                var_v1 = 0;
                if (temp_s4->_1D == 0) {
                    func_8002205C((s32) &sp60, 0, (s32) p_sabrina->rot[1]);
                    func_8002205C((s32) &sp6C, 0, (s32) M2C_FIELD(arg0, s16 *, 0x32));
                    sp60 = sp60 >> 4;
                    sp64 = sp64 >> 4;
                    sp68 = sp68 >> 4;
                    sp6C = sp6C >> 4;
                    sp70 = sp70 >> 4;
                    sp74 = sp74 >> 4;
                    func_8001C33C((s32) &sp60, (s32) &sp6C);
                    var_v1 = 1;
                    M2C_FIELD(temp_s0, s8 *, 0x5C) = 0;
                } else {
                    M2C_FIELD(temp_s0, s8 *, 0x5C) = (s8) (M2C_FIELD(temp_s0, s8 *, 0x5C) + 1);
                    if (M2C_FIELD(temp_s0, s8 *, 0x5C) >= 3) {
                        M2C_FIELD(temp_s0, s8 *, 0x5C) = -0x7E;
                        var_v1 = 1;
                    }
                }
                if ((var_v1 == 1) && (M2C_FIELD(temp_s0, s8 *, 0x25) == 0)) {
                    sp96 = M2C_FIELD(arg0, s16 *, 0x32);
                    func_80021E54((s32) &sp96, (s32) p_sabrina->rot[1], 2, 3);
                    var_v0_2 = sp96 - M2C_FIELD(arg0, s16 *, 0x32);
block_26:
                    M2C_FIELD(temp_s0, s16 *, 0x40) = var_v0_2;
                }
            }
            M2C_FIELD(temp_s0, s32 *, 0x28) = (s32) p_sabrina->x;
            M2C_FIELD(temp_s0, s32 *, 0x2C) = (s32) (func_800350FC(M2C_FIELD(p_sabrina, s32 *, 0x50)) + 0xFFFEE667);
            M2C_FIELD(temp_s0, s32 *, 0x30) = (s32) p_sabrina->z;
            sp3C = -(M2C_FIELD(temp_s0, s32 *, 0x28) - M2C_FIELD(arg0, s32 *, 0x24));
            sp40 = 0;
            temp_v0_3 = -(M2C_FIELD(temp_s0, s32 *, 0x30) - M2C_FIELD(arg0, s32 *, 0x2C));
            sp44 = temp_v0_3;
            sp48 = sp3C;
            sp4C = sp40;
            sp50 = temp_v0_3;
            if (func_800365F0((s32) &sp94, (s32) &sp92) == 1) {
                if (temp_s4->_1D == 0) {
                    if (sp92 == 0) {
                        sp92 = -1;
                    }
                } else {
                    M2C_FIELD(temp_s0, s16 *, 0x40) = sp94;
                    sp92 = 0;
                }
            }
            if (M2C_FIELD(temp_s0, s16 *, 0x40) != 0) {
                var_v0_3 = func_8001BE8C(0, 0, sp3C, sp44) + M2C_FIELD(temp_s0, s16 *, 0x40);
loop_35:
                if (var_v0_3 < 0) {
                    var_v0_3 += 0xFFF;
                    goto loop_35;
                }
loop_38:
                if (var_v0_3 >= 0x1001) {
                    var_v0_3 -= 0xFFF;
                    goto loop_38;
                }
                func_8002205C((s32) &sp78, 0, (s32) var_v0_3);
                if (func_80036880((s32) &sp78, (s32) sp92) == 0) {
                    sp3C = sp78;
                    sp40 = sp7C;
                    sp44 = sp80;
                } else {
                    func_8001C45C((s32) &sp3C);
                }
            } else {
                func_8001C45C((s32) &sp3C);
            }
            sp3C = sp3C >> 4;
            sp44 = sp44 >> 4;
            M2C_FIELD(temp_s0, s32 *, 0x34) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x28) + (((s32) (sp3C * 0x300) >> 8) << 8));
            M2C_FIELD(temp_s0, s32 *, 0x3C) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x30) + (((s32) (sp44 * 0x300) >> 8) << 8));
            sp3C = p_sabrina->x;
            sp40 = 0;
            sp44 = p_sabrina->z;
            M2C_FIELD(temp_s0, s32 *, 0x38) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x2C) + 0x11999 + 0xFFFDCCCD);
            sp3C = -(M2C_FIELD(temp_s0, s32 *, 0x28) - M2C_FIELD(temp_s0, s32 *, 0x34));
            sp40 = 0;
            sp44 = -(M2C_FIELD(temp_s0, s32 *, 0x30) - M2C_FIELD(temp_s0, s32 *, 0x3C));
            sp48 = (s32) (M2C_FIELD(temp_s0, s32 *, 0x28) - M2C_FIELD(temp_s0, s32 *, 0x34)) >> 8;
            sp4C = 0;
            sp50 = (s32) (M2C_FIELD(temp_s0, s32 *, 0x30) - M2C_FIELD(temp_s0, s32 *, 0x3C)) >> 8;
            temp_s2_3 = func_8001C33C((s32) &sp48, (s32) &sp48) - 0x900;
            if (temp_s2_3 <= 0) {
                M2C_FIELD(temp_s0, s32 *, 0x38) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x38) + (temp_s2_3 * 0x40));
            }
            func_80036410((s32) arg0, M2C_FIELD(temp_s0, s32 *, 0x34), M2C_FIELD(temp_s0, s32 *, 0x38), M2C_FIELD(temp_s0, s32 *, 0x3C), /* extra? */ M2C_FIELD(temp_s0, s32 *, 0x28), /* extra? */ M2C_FIELD(temp_s0, s32 *, 0x2C), /* extra? */ M2C_FIELD(temp_s0, s32 *, 0x30), /* extra? */ 3);
            func_80036524((s32) arg0, M2C_FIELD(temp_s0, s32 *, 0x28), M2C_FIELD(temp_s0, s32 *, 0x2C), M2C_FIELD(temp_s0, s32 *, 0x30));
            if (temp_s4->_1D == 0xD) {
                func_80022104((s32) (arg0 + 0x30), (s32) (arg0 + 0x32), (s32) &D_8006C450);
                M2C_FIELD(temp_s0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
                M2C_FIELD(temp_s0, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
                M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
                M2C_FIELD(arg0, s16 *, 0x70) = 2;
                func_8002205C((s32) &sp48, 0, (s32) p_sabrina->rot[1]);
                temp_v0_4 = sp48 << 5;
                sp48 = temp_v0_4;
                temp_v0_5 = sp50 << 5;
                sp50 = temp_v0_5;
                M2C_FIELD(arg0, s32 *, 0x24) = (s32) (p_sabrina->x - temp_v0_4);
                M2C_FIELD(arg0, s32 *, 0x28) = (s32) (p_sabrina->y + 0xFFFECCCD);
                M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (p_sabrina->z - temp_v0_5);
                D_8006C444 = (s32) M2C_FIELD(arg0, s32 *, 0x24) >> 8;
                D_8006C448 = (s32) M2C_FIELD(arg0, s32 *, 0x28) >> 8;
                D_8006C44C = (s32) M2C_FIELD(arg0, s32 *, 0x2C) >> 8;
                func_8002205C((s32) &D_8006C450, (s32) M2C_FIELD(arg0, s16 *, 0x30), (s32) M2C_FIELD(arg0, s16 *, 0x32));
                D_8007CAE2 = M2C_FIELD(arg0, s16 *, 0x32);
                D_8007CAE4 = M2C_FIELD(arg0, s16 *, 0x30);
            }
            M2C_FIELD(temp_s0, s16 *, 0x40) = 0;
            break;
        case 1:
            if ((temp_s2_2 >= 0x101) || (temp_s2_2 < -0x80)) {
                M2C_FIELD(temp_s0, s32 *, 0x1C) = func_80014AEC(temp_s2_2);
                if (M2C_FIELD(temp_s0, s32 *, 0x1C) >= 0x199A) {
                    M2C_FIELD(temp_s0, s32 *, 0x1C) = 0x1999;
                }
                var_v1_2 = -1;
                if (temp_s2_2 > 0) {
                    var_v1_2 = 1;
                }
                if (M2C_FIELD(temp_s0, s8 *, 0x24) != 0) {
                    M2C_FIELD(temp_s3, s8 *, 5) = (s8) -var_v1_2;
                } else {
                    M2C_FIELD(temp_s3, s8 *, 5) = var_v1_2;
                }
                temp_v0_6 = M2C_FIELD(arg0, void **, 0x74);
                if (temp_v0_6 != NULL) {
                    sp3C = M2C_FIELD(temp_v0_6, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0x24);
                    sp40 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x74), s32 *, 4) - M2C_FIELD(arg0, s32 *, 0x28);
                    sp44 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x74), s32 *, 8) - M2C_FIELD(arg0, s32 *, 0x2C);
                    func_8001C45C((s32) &sp3C);
                    if ((func_80014AEC(func_8001C2D0(sp3C, sp40, sp44, subroutine_arg3, /* extra? */ D_8006C454, /* extra? */ D_8006C458)) >= 0x801) && (func_800605C8((s32) arg0, (s32) temp_s3, (s32) temp_s0) == 8)) {
                        goto block_61;
                    }
                } else {
block_61:
                    M2C_FIELD(arg0, s16 *, 0x70) = 0;
                }
            }
            D_8006C444 = (s32) M2C_FIELD(arg0, s32 *, 0x24) >> 8;
            D_8006C448 = (s32) M2C_FIELD(arg0, s32 *, 0x28) >> 8;
            D_8006C44C = (s32) M2C_FIELD(arg0, s32 *, 0x2C) >> 8;
            sp3C = p_sabrina->x - M2C_FIELD(arg0, s32 *, 0x24);
            sp40 = (p_sabrina->y + 0xFFFEE667) - M2C_FIELD(arg0, s32 *, 0x28);
            sp44 = p_sabrina->z - M2C_FIELD(arg0, s32 *, 0x2C);
            func_8001C45C((s32) &sp3C);
            func_80022104((s32) &sp92, (s32) &sp94, (s32) &sp3C);
            func_80021E54((s32) (arg0 + 0x30), (s32) sp92, 3, 3);
            func_80021E54((s32) (arg0 + 0x32), (s32) sp94, 3, 3);
            func_8002205C((s32) &D_8006C450, (s32) M2C_FIELD(arg0, s16 *, 0x30), (s32) M2C_FIELD(arg0, s16 *, 0x32));
            D_8007CAE2 = M2C_FIELD(arg0, s16 *, 0x32);
            D_8007CAE4 = M2C_FIELD(arg0, s16 *, 0x30);
            if (p_sabrina->estado == 2) {
                M2C_FIELD(arg0, s16 *, 0x70) = 0;
            }
            break;
        case 2:
            temp_s4_2 = &p_sabrina->extra;
            sp94 = p_sabrina->rot[1] - ((s8) p_sabrina->_92[2] * 0x10);
            sp92 = -((s8) p_sabrina->_92[1] * 0x10);
            temp_s2_4 = rsin((s32) sp94);
            temp_s2_5 = p_sabrina->x - ((s32) (((s32) (temp_s2_4 * rcos((s32) sp92)) >> 0xC) << 0x11) >> 0xC);
            temp_s3_2 = rcos((s32) sp94);
            temp_s3_3 = p_sabrina->z - ((s32) (((s32) (temp_s3_2 * rcos((s32) sp92)) >> 0xC) << 0x11) >> 0xC);
            temp_a0 = p_sabrina->y - ((s32) (rsin((s32) sp92) << 0x11) >> 0xC);
            temp_v1 = M2C_FIELD(arg0, s32 *, 0x24);
            M2C_FIELD(arg0, s32 *, 0x24) = (s32) (temp_v1 + ((s32) (temp_s2_5 - temp_v1) >> 3));
            temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x28);
            M2C_FIELD(arg0, s32 *, 0x28) = (s32) (temp_v1_2 + ((s32) ((temp_a0 + 0xFFFECCCD) - temp_v1_2) >> 3));
            temp_v1_3 = M2C_FIELD(arg0, s32 *, 0x2C);
            M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (temp_v1_3 + ((s32) (temp_s3_3 - temp_v1_3) >> 3));
            func_80021E54((s32) (arg0 + 0x30), (s32) sp92, 3, 3);
            func_80021E54((s32) (arg0 + 0x32), (s32) sp94, 3, 3);
            func_8002205C((s32) &D_8006C450, (s32) M2C_FIELD(arg0, s16 *, 0x30), (s32) M2C_FIELD(arg0, s16 *, 0x32));
            D_8007CAE2 = M2C_FIELD(arg0, s16 *, 0x32);
            D_8007CAE4 = M2C_FIELD(arg0, s16 *, 0x30);
            if (temp_s4_2->_1D != 0xD) {
                sp94 = p_sabrina->rot[1];
                M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) (p_sabrina->x - ((s32) (rsin((s32) sp94) << 0x12) >> 0xC));
                M2C_FIELD(temp_s0, s32 *, 0x18) = (s32) (p_sabrina->y - ((s32) (rcos((s32) sp94) << 0x12) >> 0xC));
                M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) (p_sabrina->z + 0xFFFC8000);
                M2C_FIELD(arg0, s16 *, 0x70) = 3;
            }
            D_8006C444 = (s32) M2C_FIELD(arg0, s32 *, 0x24) >> 8;
            D_8006C448 = (s32) M2C_FIELD(arg0, s32 *, 0x28) >> 8;
            var_v0 = (s32) M2C_FIELD(arg0, s32 *, 0x2C) >> 8;
            goto block_71;
        case 3:
            sp3C = (s32) (M2C_FIELD(temp_s0, s32 *, 0x10) - M2C_FIELD(arg0, s32 *, 0x24)) >> 4;
            sp40 = (s32) (M2C_FIELD(temp_s0, s32 *, 0x14) - M2C_FIELD(arg0, s32 *, 0x28)) >> 4;
            sp44 = (s32) (M2C_FIELD(temp_s0, s32 *, 0x18) - M2C_FIELD(arg0, s32 *, 0x2C)) >> 4;
            M2C_FIELD(temp_s0, s32 *, 0x34) = (s32) (sp3C + M2C_FIELD(arg0, s32 *, 0x24));
            M2C_FIELD(temp_s0, s32 *, 0x38) = (s32) (sp40 + M2C_FIELD(arg0, s32 *, 0x28));
            M2C_FIELD(temp_s0, s32 *, 0x3C) = (s32) (sp44 + M2C_FIELD(arg0, s32 *, 0x2C));
            if (p_sabrina->extra._1D != 0xD) {
                M2C_FIELD(arg0, s16 *, 0x70) = 0;
                func_8002205C((s32) &sp84, 0, (s32) p_sabrina->rot[1]);
                if (func_80036D58(sp84, sp88, sp8C, p_sabrina->y + 0xFFFDCCCD) == 0) {
                    M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(temp_s0, s32 *, 4);
                    M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(temp_s0, s32 *, 8);
                    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(temp_s0, s32 *, 0xC);
                    D_8006C444 = (s32) M2C_FIELD(arg0, s32 *, 0x24) >> 8;
                    D_8006C448 = (s32) M2C_FIELD(arg0, s32 *, 0x28) >> 8;
                    var_v0 = (s32) M2C_FIELD(arg0, s32 *, 0x2C) >> 8;
                    goto block_71;
                }
            }
            break;
        case 8:
            func_80036410((s32) arg0, M2C_FIELD(temp_s0, s32 *, 0x34), M2C_FIELD(temp_s0, s32 *, 0x38), M2C_FIELD(temp_s0, s32 *, 0x3C), /* extra? */ M2C_FIELD(temp_s0, s32 *, 0x28), /* extra? */ M2C_FIELD(temp_s0, s32 *, 0x2C), /* extra? */ M2C_FIELD(temp_s0, s32 *, 0x30), /* extra? */ 3);
            func_80036524((s32) arg0, M2C_FIELD(temp_s0, s32 *, 0x28), M2C_FIELD(temp_s0, s32 *, 0x2C), M2C_FIELD(temp_s0, s32 *, 0x30));
            D_8007CAE2 = M2C_FIELD(arg0, s16 *, 0x32);
            D_8007CAE4 = M2C_FIELD(arg0, s16 *, 0x30);
            D_8006C444 = (s32) M2C_FIELD(arg0, s32 *, 0x24) >> 8;
            D_8006C448 = (s32) M2C_FIELD(arg0, s32 *, 0x28) >> 8;
            var_v0 = (s32) M2C_FIELD(arg0, s32 *, 0x2C) >> 8;
            goto block_71;
        }
    }
    D_8007CBD4 = D_8007CBC0;
}
