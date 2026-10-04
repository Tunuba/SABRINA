#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C8582;
extern s8 D_800C8583;
extern s8 D_800C8584;
extern s8 D_800C8585;
extern u16 D_8007C872;
extern u16 D_8007C8C4;
extern u16 D_8007C8C6;
extern s8 nivel_actual;
extern void * D_8007CAFC;
extern u16 D_8007CB58;
extern u16 D_8007CB5A;
extern u16 D_8007CBD4;
extern s8 D_8007CCA8;
extern s32 func_80024DEC();
extern s32 func_80024DF4();
extern s32 func_80024F6C();
extern s32 func_80024F8C();
extern s32 func_8005B52C();
extern s32 func_8005B780();
extern s32 func_8005B794();
extern s32 thunk_FUN_8001e588();
extern s32 thunk_FUN_8004866c();


void func_8005ED8C(void *arg0) {
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    s32 sp6C;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_15;
    s32 temp_v0_16;
    s32 temp_v0_17;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_s0;
    s32 var_v1;
    s8 temp_v0_10;
    s8 temp_v0_11;
    s8 temp_v0_8;
    s8 temp_v0_9;
    void *temp_s2;
    void *temp_s3;
    void *temp_s4;

    var_s0 = saved_reg_s0;
    temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s4 = M2C_FIELD(arg0, void **, 0x64);
    temp_s3 = arg0 + 0x74;
    if (p_sabrina->estado == 2) {
        temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
        switch (temp_v0) {                          /* switch 1 */
        case 0:                                     /* switch 1 */
        case 1:                                     /* switch 1 */
        case 2:                                     /* switch 1 */
        case 3:                                     /* switch 1 */
        case 4:                                     /* switch 1 */
        case 5:                                     /* switch 1 */
        case 6:                                     /* switch 1 */
        case 7:                                     /* switch 1 */
        case 8:                                     /* switch 1 */
        case 9:                                     /* switch 1 */
        case 13:                                    /* switch 1 */
        case 15:                                    /* switch 1 */
        case 16:                                    /* switch 1 */
        case 17:                                    /* switch 1 */
        case 19:                                    /* switch 1 */
        case 20:                                    /* switch 1 */
            if (D_8007C872 != 0) {
                func_8003019C();
                M2C_FIELD(arg0, s16 *, 0x70) = 0x12;
            }
            break;
        }
    }
    temp_v0_2 = M2C_FIELD(arg0, s16 *, 0x70);
    if (temp_v0_2 != 0x16) {
        if (temp_v0_2 != 0x15) {
            if (temp_v0_2 != 0xB) {
                if (temp_v0_2 != 0xC) {
                    if (temp_v0_2 != 0x12) {
                        if (temp_v0_2 != 0xE) {
                            if (temp_v0_2 != 0xA) {
                                if (temp_v0_2 != 9) {
                                    if (temp_v0_2 != 0x14) {
                                        if (temp_v0_2 != 0x13) {
                                            if (temp_v0_2 != 1) {
                                                if (temp_v0_2 != 5) {
                                                    if (temp_v0_2 != 0x11) {
                                                        if (temp_v0_2 != 0x17) {
                                                            if ((temp_v0_2 == 8) && ((M2C_FIELD(temp_s3, s16 *, 0x3E) = 1, temp_v0_3 = M2C_FIELD(D_8007CAFC, s16 *, 0x70), (temp_v0_3 == 5)) || (temp_v0_3 == 4))) {
                                                                if (nivel_actual != 0xC) {
                                                                    if (nivel_actual != 9) {
                                                                        if (nivel_actual != 6) {
                                                                            if (nivel_actual == 3) {
                                                                                func_8003DDA0(0x53, 0);
                                                                            }
                                                                        } else {
                                                                            func_8003DDA0(0x54, 0);
                                                                        }
                                                                    } else {
                                                                        func_8003DDA0(0x55, 0);
                                                                    }
                                                                } else {
                                                                    func_8003DDA0(0x56, 0);
                                                                }
                                                                func_8003DD44((D_8007C8C6 * 0xF) & 0xFF);
                                                                M2C_FIELD(arg0, s16 *, 0x70) = 0x17;
                                                                M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 2);
                                                                M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                                                                M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                                                                func_8002205C((s32) &sp58, 0, (s32) M2C_FIELD(arg0, s16 *, 0x32));
                                                                sp58 = ((s32) ((sp58 >> 4) * 0x600) >> 8) << 8;
                                                                temp_v0_4 = ((s32) ((sp5C >> 4) * 0x600) >> 8) << 8;
                                                                sp5C = temp_v0_4;
                                                                sp60 = ((s32) ((sp60 >> 4) * 0x600) >> 8) << 8;
                                                                sp5C = temp_v0_4 + 0xFFFB8000;
                                                                sp64 = M2C_FIELD(arg0, s32 *, 0x24);
                                                                sp68 = M2C_FIELD(arg0, s32 *, 0x28);
                                                                sp6C = M2C_FIELD(arg0, s32 *, 0x2C);
                                                                sp68 = (sp68 - 0x4CCD) - 0x7FFF;
                                                                sp58 += M2C_FIELD(arg0, s32 *, 0x24);
                                                                sp5C += M2C_FIELD(arg0, s32 *, 0x28);
                                                                sp60 += M2C_FIELD(arg0, s32 *, 0x2C);
                                                                func_80034FD0((s32) &sp58, (s32) &sp64);
                                                                func_8003019C();
                                                            }
                                                        } else {
                                                            if ((nivel_actual == 6) || (nivel_actual == 0xC) || (nivel_actual == 9) || (nivel_actual == 3)) {
                                                                temp_v0_5 = M2C_FIELD(arg0, s32 *, 0x54);
                                                                if (temp_v0_5 < 0x1800) {
                                                                    M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_v0_5 + 0x60);
                                                                    M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
                                                                    M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
                                                                    func_8005E9FC((s32) arg0, 0x14CCC, -0x1999, 0x400);
                                                                    func_8005E9FC((s32) arg0, 0x14CCC, -0x1999, 0x400);
                                                                    func_8005E9FC((s32) arg0, 0x14CCC, -0x2666, 0x400);
                                                                }
                                                            }
                                                            sp54 = func_8003E060();
                                                            if (nivel_actual != 0xC) {
                                                                if (nivel_actual != 9) {
                                                                    if (nivel_actual != 6) {
                                                                        if ((nivel_actual == 3) && (sp54 != 0x53)) {
                                                                            goto block_49;
                                                                        }
                                                                    } else if (sp54 != 0x54) {
                                                                        goto block_49;
                                                                    }
                                                                } else if (sp54 != 0x55) {
                                                                    goto block_49;
                                                                }
                                                            } else if (sp54 != 0x56) {
block_49:
                                                                sp54 = -1;
                                                            }
                                                            if (sp54 == -1) {
                                                                if (nivel_actual != 0xC) {
                                                                    if (nivel_actual != 9) {
                                                                        if (nivel_actual != 6) {
                                                                            if (nivel_actual == 3) {
                                                                                func_8003DDA0(8, 1);
                                                                            }
                                                                        } else {
                                                                            func_8003DDA0(0xC, 1);
                                                                        }
                                                                    } else {
                                                                        func_8003DDA0(0x10, 1);
                                                                    }
                                                                } else {
                                                                    func_8003DDA0(0x14, 1);
                                                                }
                                                                func_8003DD44((D_8007C8C4 * 0xF) & 0xFF);
                                                                func_80035098();
                                                                M2C_FIELD(D_8007CAFC, s16 *, 0x70) = 4;
                                                                func_80030E64();
                                                                if (M2C_FIELD(arg0, s32 *, 0x54) < 0x1800) {
                                                                    M2C_FIELD(arg0, s32 *, 0x54) = 0x1800;
                                                                    M2C_FIELD(arg0, s32 *, 0x58) = 0x1800;
                                                                    M2C_FIELD(arg0, s32 *, 0x5C) = 0x1800;
                                                                }
                                                                M2C_FIELD(arg0, s16 *, 0x70) = 0x13;
                                                                M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 6);
                                                                M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                                                                M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                                                            }
                                                        }
                                                    } else {
                                                        temp_v0_6 = func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z);
                                                        sp54 = temp_v0_6;
                                                        sp54 = func_80021D44((s32) (arg0 + 0x32), (s32) (s16) temp_v0_6, 0x96);
                                                        if (func_8002EFD0((s32) arg0) != 0) {
                                                            M2C_FIELD(arg0, s16 *, 0x70) = 5;
                                                            M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 4);
                                                            M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                                                            M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                                                        }
                                                    }
                                                } else {
                                                    temp_v0_7 = func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z);
                                                    sp54 = temp_v0_7;
                                                    sp54 = func_80021D44((s32) (arg0 + 0x32), (s32) (s16) temp_v0_7, 0x96);
                                                    if (((s32) M2C_FIELD(temp_s2, u8 *, 0x50) >= M2C_FIELD(temp_s3, s8 *, 0x27)) && (M2C_FIELD(temp_s3, s16 *, 0x3E) != 0)) {
                                                        M2C_FIELD(temp_s3, s16 *, 0x3E) = 0;
                                                        D_8007CCA8 = p_sabrina->vida;
                                                        if (nivel_actual != 0xC) {
                                                            if (nivel_actual != 9) {
                                                                if (nivel_actual != 6) {
                                                                    if (nivel_actual == 3) {
                                                                        var_s0 = func_800252A0(0xC, (s32) arg0, 0x8000, -0x3333, /* extra? */ 0x4CCC, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ (s32) M2C_FIELD(temp_s3, s8 *, 0x26), /* extra? */ 1);
                                                                        func_800249CC(var_s0, 0x2F);
                                                                        M2C_FIELD(var_s0, s32 (**)(s32), 0) = func_8005B794;
                                                                        M2C_FIELD(var_s0, s32 (**)(), 4) = func_80024DF4;
                                                                        M2C_FIELD(var_s0, s32 (**)(s32), 8) = func_8005B780;
                                                                        M2C_FIELD(var_s0, s32 (**)(), 0xC) = func_80024DEC;
                                                                        M2C_FIELD(var_s0, s32 (**)(), 0x10) = func_80024F6C;
                                                                        M2C_FIELD(var_s0, void (**)(s32), 0x14) = thunk_FUN_8001e588;
                                                                        M2C_FIELD(var_s0, s32 (**)(s32), 0x18) = thunk_FUN_8004866c;
                                                                        temp_v0_8 = M2C_FIELD(arg0, s8 *, 0x118);
                                                                        switch (temp_v0_8) { /* switch 2 */
                                                                        case 0: /* switch 2 */
                                                                            func_8005B394(var_s0, var_s0 + 0x24, (s32) &p_sabrina->x, 0x51EB);
                                                                            break;
                                                                        case 1: /* switch 2 */
                                                                            func_8005B394(var_s0, var_s0 + 0x24, (s32) &p_sabrina->x, 0x4CCC);
                                                                            break;
                                                                        case 2: /* switch 2 */
                                                                            func_8005B394(var_s0, var_s0 + 0x24, (s32) &p_sabrina->x, 0x47AE);
                                                                            break;
                                                                        case 3: /* switch 2 */
                                                                            func_8005B394(var_s0, var_s0 + 0x24, (s32) &p_sabrina->x, 0x428F);
                                                                            break;
                                                                        case 4: /* switch 2 */
                                                                            func_8005B394(var_s0, var_s0 + 0x24, (s32) &p_sabrina->x, 0x3D70);
                                                                            break;
                                                                        case 5: /* switch 2 */
                                                                            func_8005B394(var_s0, var_s0 + 0x24, (s32) &p_sabrina->x, 0x3851);
                                                                            break;
                                                                        }
                                                                        M2C_FIELD(var_s0, s32 *, 0xF8) = 0xB333;
                                                                        M2C_FIELD(var_s0, s32 *, 0xFC) = 0xB333;
                                                                        M2C_FIELD(var_s0, s32 *, 0x100) = 0x7D70;
                                                                        var_v1 = 0x2000;
                                                                        M2C_FIELD(var_s0, s32 *, 0x54) = 0x2000;
                                                                        M2C_FIELD(var_s0, s32 *, 0x58) = 0x2000;
                                                                        goto block_106;
                                                                    }
                                                                } else {
                                                                    var_s0 = func_800252A0(0xC, (s32) arg0, 0, 0, /* extra? */ 0xB333, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ (s32) M2C_FIELD(temp_s3, s8 *, 0x26), /* extra? */ 1);
                                                                    func_800249CC(var_s0, 0x28);
                                                                    M2C_FIELD(var_s0, s32 (**)(s32), 0) = func_8005B52C;
                                                                    M2C_FIELD(var_s0, s32 (**)(), 4) = func_80024DF4;
                                                                    M2C_FIELD(var_s0, s32 (**)(), 8) = func_80024F6C;
                                                                    M2C_FIELD(var_s0, s32 (**)(), 0xC) = func_80024DEC;
                                                                    M2C_FIELD(var_s0, s32 (**)(), 0x10) = func_80024F6C;
                                                                    M2C_FIELD(var_s0, s32 (**)(s32), 0x14) = func_80024F8C;
                                                                    M2C_FIELD(var_s0, s32 (**)(s32), 0x18) = thunk_FUN_8004866c;
                                                                    temp_v0_9 = M2C_FIELD(arg0, s8 *, 0x118);
                                                                    switch (temp_v0_9) { /* switch 3 */
                                                                    case 0: /* switch 3 */
                                                                        func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0xE6, /* extra? */ 0xCCC);
                                                                        break;
                                                                    case 1: /* switch 3 */
                                                                        func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0x96, /* extra? */ 0xE14);
                                                                        break;
                                                                    case 2: /* switch 3 */
                                                                        func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0x78, /* extra? */ 0xF5C);
                                                                        break;
                                                                    case 3: /* switch 3 */
                                                                        func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0x5A, /* extra? */ 0x11EB);
                                                                        break;
                                                                    case 4: /* switch 3 */
                                                                        func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0x46, /* extra? */ 0x147A);
                                                                        break;
                                                                    case 5: /* switch 3 */
                                                                        func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0x46, /* extra? */ 0x147A);
                                                                        break;
                                                                    }
                                                                    M2C_FIELD(var_s0, s32 *, 0xF8) = 0x8000;
                                                                    M2C_FIELD(var_s0, s32 *, 0xFC) = 0x8000;
                                                                    M2C_FIELD(var_s0, s32 *, 0x100) = 0x4000;
                                                                    var_v1 = 0x1000;
                                                                    M2C_FIELD(var_s0, s32 *, 0x54) = 0x1000;
                                                                    M2C_FIELD(var_s0, s32 *, 0x58) = 0x1000;
                                                                    goto block_106;
                                                                }
                                                            } else {
                                                                var_s0 = func_800252A0(0xC, (s32) arg0, M2C_FIELD(temp_s3, s32 *, 0xC), M2C_FIELD(temp_s3, s32 *, 0x10), /* extra? */ M2C_FIELD(temp_s3, s32 *, 0x14), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ (s32) M2C_FIELD(temp_s3, s8 *, 0x26), /* extra? */ 1);
                                                                func_800249CC(var_s0, 0x22);
                                                                M2C_FIELD(var_s0, s32 (**)(s32), 0) = func_8005B52C;
                                                                M2C_FIELD(var_s0, s32 (**)(), 4) = func_80024DF4;
                                                                M2C_FIELD(var_s0, s32 (**)(), 8) = func_80024F6C;
                                                                M2C_FIELD(var_s0, s32 (**)(), 0xC) = func_80024DEC;
                                                                M2C_FIELD(var_s0, s32 (**)(), 0x10) = func_80024F6C;
                                                                M2C_FIELD(var_s0, s32 (**)(s32), 0x14) = func_80024F8C;
                                                                M2C_FIELD(var_s0, s32 (**)(s32), 0x18) = thunk_FUN_8004866c;
                                                                temp_v0_10 = M2C_FIELD(arg0, s8 *, 0x118);
                                                                switch (temp_v0_10) { /* switch 4 */
                                                                case 0: /* switch 4 */
                                                                    func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0xE6, /* extra? */ 0xCCC);
                                                                    break;
                                                                case 1: /* switch 4 */
                                                                    func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0xB4, /* extra? */ 0xE14);
                                                                    break;
                                                                case 2: /* switch 4 */
                                                                    func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0x96, /* extra? */ 0x10A3);
                                                                    break;
                                                                case 3: /* switch 4 */
                                                                    func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0x82, /* extra? */ 0x11EB);
                                                                    break;
                                                                case 4: /* switch 4 */
                                                                    func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0x64, /* extra? */ 0x147A);
                                                                    break;
                                                                case 5: /* switch 4 */
                                                                    func_8005B46C(var_s0, 0, (s32) D_8007CB5A, 0x64, /* extra? */ 0x147A);
                                                                    break;
                                                                }
                                                                M2C_FIELD(var_s0, s32 *, 0xF8) = 0x18000;
                                                                M2C_FIELD(var_s0, s32 *, 0xFC) = 0xD999;
                                                                M2C_FIELD(var_s0, s32 *, 0x100) = 0xB8F5;
                                                                var_v1 = 0x1000;
                                                                M2C_FIELD(var_s0, s32 *, 0x54) = 0x1000;
                                                                M2C_FIELD(var_s0, s32 *, 0x58) = 0x1000;
                                                                goto block_106;
                                                            }
                                                        } else {
                                                            var_s0 = func_800252A0(0xC, (s32) arg0, 0xE666, 0, /* extra? */ 0x9999, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ (s32) M2C_FIELD(temp_s3, s8 *, 0x26), /* extra? */ 1);
                                                            func_800249CC(var_s0, 0x33);
                                                            M2C_FIELD(var_s0, s32 (**)(s32), 0) = func_8005B52C;
                                                            M2C_FIELD(var_s0, s32 (**)(), 4) = func_80024DF4;
                                                            M2C_FIELD(var_s0, s32 (**)(), 8) = func_80024F6C;
                                                            M2C_FIELD(var_s0, s32 (**)(), 0xC) = func_80024DEC;
                                                            M2C_FIELD(var_s0, s32 (**)(), 0x10) = func_80024F6C;
                                                            M2C_FIELD(var_s0, s32 (**)(s32), 0x14) = func_80024F8C;
                                                            M2C_FIELD(var_s0, s32 (**)(s32), 0x18) = thunk_FUN_8004866c;
                                                            temp_v0_11 = M2C_FIELD(arg0, s8 *, 0x118);
                                                            switch (temp_v0_11) { /* switch 5 */
                                                            case 0: /* switch 5 */
                                                                func_8005B46C(var_s0, 0, (s32) D_8007CB58, 0xE6, /* extra? */ 0xCCC);
                                                                break;
                                                            case 1: /* switch 5 */
                                                                func_8005B46C(var_s0, 0, (s32) D_8007CB58, 0x96, /* extra? */ 0xE14);
                                                                break;
                                                            case 2: /* switch 5 */
                                                                func_8005B46C(var_s0, 0, (s32) D_8007CB58, 0x78, /* extra? */ 0x10A3);
                                                                break;
                                                            case 3: /* switch 5 */
                                                                func_8005B46C(var_s0, 0, (s32) D_8007CB58, 0x5A, /* extra? */ 0x11EB);
                                                                break;
                                                            case 4: /* switch 5 */
                                                                func_8005B46C(var_s0, 0, (s32) D_8007CB58, 0x46, /* extra? */ 0x147A);
                                                                break;
                                                            case 5: /* switch 5 */
                                                                func_8005B46C(var_s0, 0, (s32) D_8007CB58, 0x46, /* extra? */ 0x147A);
                                                                break;
                                                            }
                                                            M2C_FIELD(var_s0, s32 *, 0xF8) = 0x18000;
                                                            M2C_FIELD(var_s0, s32 *, 0xFC) = 0xD999;
                                                            M2C_FIELD(var_s0, s32 *, 0x100) = 0xB8F5;
                                                            var_v1 = 0x4000;
                                                            M2C_FIELD(var_s0, s32 *, 0x54) = 0x4000;
                                                            M2C_FIELD(var_s0, s32 *, 0x58) = 0x4000;
block_106:
                                                            M2C_FIELD(var_s0, s32 *, 0x5C) = var_v1;
                                                        }
                                                        M2C_FIELD(var_s0, s16 *, 0x110) = 2;
                                                        M2C_FIELD(var_s0, s8 *, 0x119) = 1;
                                                    }
                                                    if (func_8002EFD0((s32) arg0) != 0) {
                                                        M2C_FIELD(arg0, s16 *, 0x70) = 1;
                                                        M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 2);
                                                        M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                                                        M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                                                        M2C_FIELD(temp_s3, s16 *, 0x3E) = 1;
                                                        if (D_8007CCA8 != p_sabrina->vida) {
                                                            M2C_FIELD(arg0, s16 *, 0x70) = 0x13;
                                                            M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 6);
                                                            M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                                                            M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                                                        }
                                                    }
                                                }
                                            } else {
                                                temp_v0_12 = func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z);
                                                sp54 = temp_v0_12;
                                                sp54 = func_80021D44((s32) (arg0 + 0x32), (s32) (s16) temp_v0_12, 0x96);
                                                if ((func_8002EFD0((s32) arg0) != 0) || (D_8007CCA8 != p_sabrina->vida)) {
                                                    M2C_FIELD(arg0, s16 *, 0x70) = 0x13;
                                                    M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 6);
                                                    M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                                                    M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                                                }
                                            }
                                        } else {
                                            temp_v0_13 = func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z);
                                            sp54 = temp_v0_13;
                                            sp54 = func_80021D44((s32) (arg0 + 0x32), (s32) (s16) temp_v0_13, 0x96);
                                            if (func_8002EFD0((s32) arg0) != 0) {
                                                M2C_FIELD(arg0, s16 *, 0x70) = 9;
                                                M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 8);
                                                M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                                                M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                                            }
                                        }
                                    } else {
                                        temp_v0_14 = func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z);
                                        sp54 = temp_v0_14;
                                        sp54 = func_80021D44((s32) (arg0 + 0x32), (s32) (s16) temp_v0_14, 0x96);
                                        if (func_8002EFD0((s32) arg0) != 0) {
                                            M2C_FIELD(arg0, s16 *, 0x70) = 5;
                                            M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 4);
                                            M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                                            M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                                        }
                                    }
                                } else {
                                    temp_v0_15 = func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z);
                                    sp54 = temp_v0_15;
                                    sp54 = func_80021D44((s32) (arg0 + 0x32), (s32) (s16) temp_v0_15, 0x96);
                                    if (func_8002EFD0((s32) arg0) != 0) {
                                        M2C_FIELD(arg0, s16 *, 0x70) = 0x14;
                                        M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0xA);
                                        M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                                        M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                                    }
                                }
                            } else if (func_8002EFD0((s32) arg0) != 0) {
                                if (nivel_actual != 0xC) {
                                    if (nivel_actual != 9) {
                                        if (nivel_actual != 6) {
                                            if (nivel_actual == 3) {
                                                TocarSonido(0x3C, 0, 0x2A, 0x7F);
                                            }
                                        } else {
                                            TocarSonido(0x3B, 0, 0x2A, 0x7F);
                                        }
                                    } else {
                                        TocarSonido(0x3B, 0, 0x2A, 0x7F);
                                    }
                                } else {
                                    TocarSonido(0x3D, 0, 0x2A, 0x7F);
                                }
                                M2C_FIELD(arg0, s16 *, 0x70) = 0xE;
                                M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0xE);
                                M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                                M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                            }
                        } else {
                            func_80048228((s32) arg0);
                            if (M2C_FIELD(arg0, u8 *, 0x20) & 0x80) {
                                D_8007CBD4 |= 0x40;
                                if (nivel_actual != 0xC) {
                                    if (nivel_actual != 9) {
                                        if (nivel_actual != 6) {
                                            if (nivel_actual == 3) {
                                                D_800C8582 = 1;
                                            }
                                        } else {
                                            D_800C8583 = 1;
                                        }
                                    } else {
                                        D_800C8584 = 1;
                                    }
                                } else {
                                    D_800C8585 = 1;
                                }
                            }
                        }
                    } else {
                        if (nivel_actual != 0xC) {
                            if (nivel_actual != 9) {
                                if (nivel_actual != 6) {
                                    if (nivel_actual == 3) {
                                        TocarSonido(0x3D, 0, 0x2A, 0x7F);
                                    }
                                } else {
                                    TocarSonido(0x3C, 0, 0x2A, 0x7F);
                                }
                            } else {
                                TocarSonido(0x3C, 0, 0x2A, 0x7F);
                            }
                        } else {
                            TocarSonido(0x3E, 0, 0x2A, 0x7F);
                        }
                        M2C_FIELD(arg0, s16 *, 0x70) = 0xC;
                        M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0x14);
                        M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                        M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                    }
                } else {
                    temp_v0_16 = func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z);
                    sp54 = temp_v0_16;
                    sp54 = func_80021D44((s32) (arg0 + 0x32), (s32) (s16) temp_v0_16, 0x96);
                    if (func_8002EFD0((s32) arg0) != 0) {
                        if (nivel_actual != 0xC) {
                            if (nivel_actual != 9) {
                                if (nivel_actual != 6) {
                                    if (nivel_actual == 3) {
                                        TocarSonido(0x3B, 0, 0x2A, 0x7F);
                                    }
                                } else {
                                    TocarSonido(0x3A, 0, 0x2A, 0x7F);
                                }
                            } else {
                                TocarSonido(0x3A, 0, 0x2A, 0x7F);
                            }
                        } else {
                            TocarSonido(0x3C, 0, 0x2A, 0x7F);
                        }
                        M2C_FIELD(arg0, s16 *, 0x70) = 0xB;
                        M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 0x10);
                        M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                        M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                    }
                }
            } else {
                temp_v0_17 = func_8002218C((s32) arg0, p_sabrina->x, p_sabrina->z);
                sp54 = temp_v0_17;
                sp54 = func_80021D44((s32) (arg0 + 0x32), (s32) (s16) temp_v0_17, 0x96);
                if (func_8002EFD0((s32) arg0) != 0) {
                    func_80030E64();
                    M2C_FIELD(arg0, s16 *, 0x70) = 0x15;
                    M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 2);
                    M2C_FIELD(temp_s2, u8 *, 0x50) = 0U;
                    M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
                }
            }
        } else {
            func_80030E64();
            p_sabrina->estado = 2;
            M2C_FIELD(arg0, s16 *, 0x70) = 0x16;
            func_8003DDFC();
        }
    } else {
        D_8007C872 = 0;
    }
}
