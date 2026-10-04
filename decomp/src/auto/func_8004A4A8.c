#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 partida;


void func_8004A4A8(void *arg0) {
    s16 temp_v0;
    s16 var_s0;
    s32 temp_a0;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_v0_3;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_4;
    s32 var_s1;
    void *temp_s4;
    void *temp_v0_2;
    void *temp_v0_4;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v1_2;
    void *temp_v1_3;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    temp_s4 = arg0 + 0x74;
    switch (temp_v0) {                              /* irregular */
    case 0:
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x54);
        if (temp_v1 >= 2) {
            M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_v1 + ((s32) (1 - temp_v1) >> 2));
            if (M2C_FIELD(arg0, s32 *, 0x54) < 2) {
                temp_v1_2 = M2C_FIELD(arg0, void **, 0x60);
                M2C_FIELD(temp_v1_2, u8 *, 0x64) = (u8) (M2C_FIELD(temp_v1_2, u8 *, 0x64) | 1);
                M2C_FIELD(arg0, s32 *, 0x54) = 1;
            }
            M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
            M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        }
        if ((p_sabrina != NULL) && (func_8002225C((s32) arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z) < 0x140000)) {
            temp_v1_3 = M2C_FIELD(arg0, void **, 0x60);
            M2C_FIELD(temp_v1_3, u8 *, 0x64) = (u8) (M2C_FIELD(temp_v1_3, u8 *, 0x64) & 0xFE);
            M2C_FIELD(arg0, s16 *, 0x70) = 1;
        }
        temp_v0_2 = M2C_FIELD(temp_s4, void **, 0xC);
        if (temp_v0_2 != NULL) {
            M2C_FIELD(temp_v0_2, s16 *, 0x40) = 3;
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
            return;
        }
        return;
    case 1:
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x54);
        if (temp_a0 < 0x1000) {
            M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_a0 + ((s32) (0x1000 - temp_a0) >> 2));
            if (M2C_FIELD(arg0, s32 *, 0x54) >= 0x1000) {
                M2C_FIELD(arg0, s32 *, 0x54) = 0x1000;
            }
            temp_v0_3 = M2C_FIELD(arg0, s32 *, 0x54);
            M2C_FIELD(arg0, s32 *, 0x5C) = temp_v0_3;
            M2C_FIELD(arg0, s32 *, 0x58) = temp_v0_3;
        }
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x28);
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + (rsin(M2C_FIELD(arg0, s16 *, 0x32) * 4) * 2));
        M2C_FIELD(arg0, s16 *, 0x34) = (s16) (rcos((s32) M2C_FIELD(arg0, s16 *, 0x32)) >> 4);
        temp_v0_4 = M2C_FIELD(temp_s4, void **, 0xC);
        if (temp_v0_4 != NULL) {
            M2C_FIELD(temp_v0_4, s16 *, 0x40) = 3;
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
        }
        if (p_sabrina != NULL) {
            temp_v0_5 = func_8002225C((s32) arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z);
            if (temp_v0_5 >= 0x140001) {
            default:
                M2C_FIELD(arg0, s16 *, 0x70) = 0;
            } else if (temp_v0_5 < 0x20000) {
                M2C_FIELD(arg0, s16 *, 0x70) = 2;
                return;
            }
        }
        break;
    case 2:
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) ((s32) (p_sabrina->x - M2C_FIELD(arg0, s32 *, 0x24)) >> 3);
        M2C_FIELD(arg0, s32 *, 0x40) = (s32) ((s32) (p_sabrina->z - M2C_FIELD(arg0, s32 *, 0x2C)) >> 3);
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) ((s32) (((p_sabrina->y - 0x4001) - 0x7FFF) - M2C_FIELD(arg0, s32 *, 0x28)) >> 3);
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x38) >> 8) * 0x2E6) >> 8) << 8);
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x3C) >> 8) * 0x2E6) >> 8) << 8);
        M2C_FIELD(arg0, s32 *, 0x40) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x40) >> 8) * 0x2E6) >> 8) << 8);
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
        temp_v0_6 = M2C_FIELD(temp_s4, void **, 0xC);
        if (temp_v0_6 != NULL) {
            M2C_FIELD(temp_v0_6, s16 *, 0x40) = 3;
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
        }
        temp_v1_4 = M2C_FIELD(arg0, s32 *, 0x54);
        M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_v1_4 - (temp_v1_4 >> 4));
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        temp_s0 = ((func_80014F10() & 0x3F) - 0x20) << 8;
        temp_s2 = ((func_80014F10() & 0x3F) - 0x20) << 8;
        CrearParticula((s32) M2C_FIELD(temp_s4, s8 *, 4), (s32) arg0, 0, temp_s0, /* extra? */ temp_s2, /* extra? */ (((func_80014F10() & 0x3F) - 0x20) << 8), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 7, /* extra? */ 2, /* extra? */ 0);
        M2C_FIELD(arg0, s16 *, 0x30) = (s16) (M2C_FIELD(arg0, s16 *, 0x30) + 0xF);
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x17);
        if ((p_sabrina != NULL) && (func_8002225C((s32) arg0, p_sabrina->x, (p_sabrina->y - 0x4001) - 0x7FFF, p_sabrina->z) < 0x6666)) {
            TocarSonido(0x20, 0, 0x2A, 0x7F);
            func_8004C824();
            if (M2C_FIELD(temp_s4, void **, 0xC) != NULL) {
                partida += 1;
            } else {
                func_800300C4();
            }
            var_s1 = 0;
loop_35:
            if (var_s1 < 0x1000) {
                var_s0 = 0;
loop_33:
                if (var_s0 < 0x1000) {
                    temp_s2_2 = (s32) (rsin(var_s1) * 0xCCC) >> 0xC;
                    CrearParticula((s32) M2C_FIELD(temp_s4, s8 *, 4), (s32) arg0, (s32) var_s0, 0, /* extra? */ 0, /* extra? */ 0x28F, /* extra? */ 0, /* extra? */ temp_s2_2, /* extra? */ ((s32) (rcos(var_s1) * 0xCCC) >> 0xC), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x202, /* extra? */ 0);
                    var_s0 += 0x3E8;
                    goto loop_33;
                }
                var_s1 += 0x320;
                goto loop_35;
            }
            M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
            temp_v0_7 = M2C_FIELD(temp_s4, void **, 0xC);
            if (temp_v0_7 != NULL) {
                M2C_FIELD(temp_v0_7, s16 *, 0x40) = 1;
                return;
            }
        }
        break;
    }
}
