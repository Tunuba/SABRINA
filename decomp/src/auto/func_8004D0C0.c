#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C8560;
extern s8 D_800C8582;
extern s8 D_800C8583;
extern s8 D_800C8584;
extern s8 D_800C8585;
extern s8 D_800C8948;
extern s8 D_800C8A89;
extern s8 D_800C8D0B;
extern s8 D_800C8E4C;
extern s8 D_800C90CE;
extern s8 D_800C920F;
extern s8 D_800C9491;
extern s8 D_800C95D2;
extern u8 D_80078F00[];
extern u8 D_80078F30[];
extern u8 D_80078F90[];
extern u8 D_80078FC4[];
extern u8 D_8007902C[];
extern u8 D_80079060[];
extern u8 D_800790C4[];
extern u8 D_800790F0[];
extern s8 nivel_actual;
extern s8 D_8007CA01;
extern void * D_8007CB8C;
extern s16 D_8007CC16;
extern s8 D_8007CC18;
extern s32 func_80025064();


void func_8004D0C0(void *arg0) {
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s16 temp_v0_2;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_v1;
    void *temp_s0;

    temp_s0 = arg0 + 0x74;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 4);
    if ((temp_v0 == 0xA) || (temp_v0 == 7) || (temp_v0 == 4) || (temp_v0 == 1)) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
    }
    temp_v0_2 = M2C_FIELD(arg0, s16 *, 0x70);
    switch (temp_v0_2) {
    case 0:
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x19);
        if (M2C_FIELD(arg0, s16 *, 0x32) >= 0x1001) {
            M2C_FIELD(arg0, s16 *, 0x32) = 0;
            return;
        }
    default:
        return;
    case 1:
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
        sp24 = M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(temp_s0, s32 *, 0x10);
        sp2C = M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(temp_s0, s32 *, 0x18);
        sp28 = M2C_FIELD(arg0, s32 *, 0x28) + 0xFFFB8000;
        temp_v0_3 = func_800223E8((s32) &sp24);
        if (((M2C_FIELD(arg0, s32 *, 0x28) + 0x6667 + 0x7FFF) >= temp_v0_3) && (temp_v0_3 != sp28)) {
            M2C_FIELD(arg0, s16 *, 0x70) = 2;
            return;
        }
        break;
    case 2:
        sp24 = (s32) (p_sabrina->x - M2C_FIELD(arg0, s32 *, 0x24)) >> 8;
        sp28 = (s32) (p_sabrina->y - M2C_FIELD(arg0, s32 *, 0x28)) >> 8;
        sp2C = (s32) (p_sabrina->z - M2C_FIELD(arg0, s32 *, 0x2C)) >> 8;
        if (func_8001C33C((s32) &sp24, (s32) &sp24) < M2C_FIELD(temp_s0, s32 *, 8)) {
            temp_v0_4 = M2C_FIELD(temp_s0, s32 *, 4);
            if ((temp_v0_4 == 0xA) || (temp_v0_4 == 7) || (temp_v0_4 == 4) || (temp_v0_4 == 1)) {
                M2C_FIELD(temp_s0, s32 *, 0x20) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
                M2C_FIELD(temp_s0, s32 *, 0x24) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
                M2C_FIELD(temp_s0, s32 *, 0x28) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
                M2C_FIELD(temp_s0, s32 *, 0x24) = (s32) ((M2C_FIELD(temp_s0, s32 *, 0x24) - 0x599A) - 0x7FFF);
                M2C_FIELD(arg0, s16 *, 0x70) = 4;
                func_8003019C();
                TocarSonido(0x31, 0, 0x2A, 0x7F);
                func_80030EC8();
                func_8003E0B4();
                func_80037268();
            }
            if (M2C_FIELD(arg0, s32 *, 0x74) != 0) {
                var_v1 = 0;
                if (nivel_actual != 0xC) {
                    if (nivel_actual != 9) {
                        if (nivel_actual != 6) {
                            if (nivel_actual == 3) {
                                if (D_800C8582 >= 2) {
                                    goto block_31;
                                }
                            } else {
                                goto block_31;
                            }
                        } else if (D_800C8583 >= 2) {
                            goto block_31;
                        }
                    } else if (D_800C8584 >= 2) {
                        goto block_31;
                    }
                } else if (D_800C8585 >= 2) {
block_31:
                    var_v1 = 1;
                }
                if (var_v1 == 1) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 4;
                    func_8003019C();
                    TocarSonido(0x31, 0, 0x2A, 0x7F);
                    func_80030EC8();
                    func_8003E0B4();
                    func_80037268();
                    return;
                }
            }
        }
        break;
    case 4:
        M2C_FIELD(p_sabrina, s32 (**)(), 0x14) = func_80025064;
        M2C_FIELD(D_8007CB8C, s32 (**)(), 0x14) = func_80025064;
        temp_v0_5 = (s32) (p_sabrina->x - M2C_FIELD(temp_s0, s32 *, 0x20)) >> 4;
        sp24 = temp_v0_5;
        sp28 = (s32) (p_sabrina->y - M2C_FIELD(temp_s0, s32 *, 0x24)) >> 4;
        sp2C = (s32) (p_sabrina->z - M2C_FIELD(temp_s0, s32 *, 0x28)) >> 4;
        p_sabrina->x -= temp_v0_5;
        p_sabrina->y -= sp28;
        p_sabrina->z -= sp2C;
        p_sabrina->escala[0] -= 0x4C;
        p_sabrina->escala[1] -= 0x4C;
        p_sabrina->escala[2] -= 0x4C;
        if (p_sabrina->escala[0] < 5) {
            p_sabrina->escala[0] = 5;
            p_sabrina->escala[1] = 5;
            p_sabrina->escala[2] = 5;
            M2C_FIELD(arg0, s16 *, 0x70) = 3;
        }
        M2C_FIELD(D_8007CB8C, s32 *, 0x24) = (s32) p_sabrina->x;
        M2C_FIELD(D_8007CB8C, s32 *, 0x28) = (s32) p_sabrina->y;
        M2C_FIELD(D_8007CB8C, s32 *, 0x2C) = (s32) p_sabrina->z;
        M2C_FIELD(D_8007CB8C, s32 *, 0x54) = (s32) p_sabrina->escala[0];
        M2C_FIELD(D_8007CB8C, s32 *, 0x58) = (s32) p_sabrina->escala[1];
        M2C_FIELD(D_8007CB8C, s32 *, 0x5C) = (s32) p_sabrina->escala[2];
        func_80033AD8((s32) p_sabrina);
        func_80055CAC((s32) D_8007CB8C);
        return;
    case 3:
        if (M2C_FIELD(temp_s0, s32 *, 0x1C) != 0) {
            if (nivel_actual != 0xC) {
                if (nivel_actual != 9) {
                    if (nivel_actual != 3) {
                        if (nivel_actual == 6) {
                            if (D_800C8583 < 2) {
                                return;
                            }
                            goto block_49;
                        }
                    } else {
                        if (D_800C8582 < 2) {
                            return;
                        }
                        goto block_49;
                    }
                } else {
                    if (D_800C8584 < 2) {
                        return;
                    }
                    goto block_49;
                }
            } else if (D_800C8585 >= 2) {
                goto block_49;
            }
        } else {
block_49:
            if (nivel_actual != 0xD) {
                if (nivel_actual != 0xC) {
                    if (nivel_actual != 9) {
                        if (nivel_actual != 3) {
                            if (nivel_actual == 6) {
                                M2C_FIELD(temp_s0, s32 *, 4) = 0xD;
                                if (D_800C8560 < 3) {
                                    D_800C8560 = 3;
                                }
                            }
                        } else {
                            M2C_FIELD(temp_s0, s32 *, 4) = 0xD;
                            if (D_800C8560 < 2) {
                                D_800C8560 = 2;
                            }
                        }
                    } else {
                        M2C_FIELD(temp_s0, s32 *, 4) = 0xD;
                        if (D_800C8560 < 4) {
                            D_800C8560 = 4;
                        }
                    }
                } else {
                    M2C_FIELD(temp_s0, s32 *, 4) = 0xD;
                    if (D_800C8560 < 5) {
                        D_800C8560 = 5;
                    }
                }
                D_8007CA01 = nivel_actual;
                temp_v0_6 = M2C_FIELD(temp_s0, s32 *, 4);
                D_8007CC16 = (s16) temp_v0_6;
                nivel_actual = (s8) (s16) temp_v0_6;
                D_8007CC18 = 1;
                func_80047240();
            } else {
                temp_v0_7 = M2C_FIELD(temp_s0, s32 *, 4);
                if (temp_v0_7 != 0xA) {
                    if (temp_v0_7 != 7) {
                        if (temp_v0_7 != 4) {
                            if (temp_v0_7 == 1) {
                                func_80019464(0);
                                if (D_800C8948 != 0) {
                                    func_8005E290(0xFF, 0xFF, 0xFF, (s32) D_80078F00);
                                } else {
                                    func_8005E290(0x38, 0x38, 0x38, (s32) D_80078F00);
                                }
                                if (D_800C8A89 != 0) {
                                    func_8005E290(0xFF, 0xFF, 0xFF, (s32) D_80078F30);
                                    return;
                                }
                                func_8005E290(0x38, 0x38, 0x38, (s32) D_80078F30);
                                return;
                            }
                            Afirmar(0);
                            return;
                        }
                        func_80019464(1);
                        if (D_800C8D0B != 0) {
                            func_8005E290(0xFF, 0xFF, 0xFF, (s32) D_80078F90);
                        } else {
                            func_8005E290(0x38, 0x38, 0x38, (s32) D_80078F90);
                        }
                        if (D_800C8E4C != 0) {
                            func_8005E290(0xFF, 0xFF, 0xFF, (s32) D_80078FC4);
                            return;
                        }
                        func_8005E290(0x38, 0x38, 0x38, (s32) D_80078FC4);
                        return;
                    }
                    func_80019464(2);
                    if (D_800C90CE != 0) {
                        func_8005E290(0xFF, 0xFF, 0xFF, (s32) D_8007902C);
                    } else {
                        func_8005E290(0x38, 0x38, 0x38, (s32) D_8007902C);
                    }
                    if (D_800C920F != 0) {
                        func_8005E290(0xFF, 0xFF, 0xFF, (s32) D_80079060);
                        return;
                    }
                    func_8005E290(0x38, 0x38, 0x38, (s32) D_80079060);
                    return;
                }
                func_80019464(3);
                if (D_800C9491 != 0) {
                    func_8005E290(0xFF, 0xFF, 0xFF, (s32) D_800790C4);
                } else {
                    func_8005E290(0x38, 0x38, 0x38, (s32) D_800790C4);
                }
                if (D_800C95D2 != 0) {
                    func_8005E290(0xFF, 0xFF, 0xFF, (s32) D_800790F0);
                    return;
                }
                func_8005E290(0x38, 0x38, 0x38, (s32) D_800790F0);
                return;
            }
        }
        break;
    }
}
