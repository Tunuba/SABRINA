#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 hechizos[];


void func_80038318(void *arg0) {
    ObjExtra *temp_s0_2;
    s16 temp_v0;
    s16 var_s0;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_s1;
    s8 temp_v0_3;
    void *temp_s4;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    temp_s4 = arg0 + 0x74;
    if (temp_v0 != 2) {
        if (temp_v0 != 1) {
            if (temp_v0 == 0) {
                M2C_FIELD(arg0, s16 *, 0x70) = 1;
                return;
            }
            M2C_FIELD(arg0, s16 *, 0x70) = 0;
        } else {
            M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x28);
            M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + (rsin(M2C_FIELD(arg0, s16 *, 0x32) * 4) >> 1));
            if (p_sabrina != NULL) {
                temp_v0_2 = func_8002225C((s32) arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z);
                if (temp_v0_2 >= 0x140001) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 0;
                } else if (temp_v0_2 < 0x18000) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 2;
                }
            }
            temp_s1 = func_80021CE4(0x1000);
            temp_s0 = func_80021CE4(0x1000);
            temp_s2 = (s32) (rsin(temp_s1) * 0xC000) >> 0xC;
            temp_v1 = (s32) (rcos(temp_s1) * 0xC000) >> 0xC;
            M2C_FIELD(CrearParticula((s32) M2C_FIELD(temp_s4, s8 *, 1), (s32) arg0, (s32) (s16) temp_s0, 0, /* extra? */ (temp_s2 - 0x5999), /* extra? */ temp_v1, /* extra? */ 0, /* extra? */ ((s32) -temp_s2 >> 5), /* extra? */ ((s32) -temp_v1 >> 5), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x202, /* extra? */ 0), s32 *, 0x3C) = 0x51E;
        }
    } else {
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) ((s32) (p_sabrina->x - M2C_FIELD(arg0, s32 *, 0x24)) >> 3);
        M2C_FIELD(arg0, s32 *, 0x40) = (s32) ((s32) (p_sabrina->z - M2C_FIELD(arg0, s32 *, 0x2C)) >> 3);
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) ((s32) (((p_sabrina->y - 0x4001) - 0x7FFF) - M2C_FIELD(arg0, s32 *, 0x28)) >> 3);
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x38) >> 8) * 0x2E6) >> 8) << 8);
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x3C) >> 8) * 0x2E6) >> 8) << 8);
        M2C_FIELD(arg0, s32 *, 0x40) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x40) >> 8) * 0x2E6) >> 8) << 8);
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x54);
        M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_v1_2 - (temp_v1_2 >> 4));
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x58);
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x5C);
        func_80014F10();
        temp_s2_2 = ((func_80014F10() & 0x3F) - 0x20) << 8;
        temp_v1_3 = ((func_80014F10() & 0x3F) - 0x20) << 8;
        M2C_FIELD(CrearParticula((s32) M2C_FIELD(temp_s4, s8 *, 1), (s32) arg0, 0, 0, /* extra? */ (temp_s2_2 - 0x5999), /* extra? */ temp_v1_3, /* extra? */ 0, /* extra? */ ((s32) -temp_s2_2 >> 5), /* extra? */ ((s32) -temp_v1_3 >> 5), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x202, /* extra? */ 0), s32 *, 0x3C) = 0x51E;
        M2C_FIELD(arg0, s16 *, 0x30) = (s16) (M2C_FIELD(arg0, s16 *, 0x30) + 0xF);
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x17);
        if ((p_sabrina != NULL) && (func_8002225C((s32) arg0, p_sabrina->x, (p_sabrina->y - 0x4001) - 0x7FFF, p_sabrina->z) < 0x6666)) {
            temp_v0_3 = M2C_FIELD(arg0, s8 *, 0x74);
            switch (temp_v0_3) {
            case 0:
                TocarSonido(0x16, 0, 0x2A, 0x7F);
                break;
            case 2:
                TocarSonido(0x14, 0, 0x2A, 0x7F);
                break;
            case 3:
                TocarSonido(0x13, 0, 0x2A, 0x7F);
                break;
            case 4:
                TocarSonido(0x15, 0, 0x2A, 0x7F);
                break;
            case 5:
                TocarSonido(0x17, 0, 0x2A, 0x7F);
                break;
            case 8:
                TocarSonido(0x16, 0, 0x2A, 0x7F);
                break;
            case 1:
                TocarSonido(0x18, 0, 0x2A, 0x7F);
                break;
            }
            var_s1 = 0;
loop_28:
            if (var_s1 < 0x1000) {
                var_s0 = 0;
loop_26:
                if (var_s0 < 0x1000) {
                    temp_s2_3 = (s32) (rsin(var_s1) * 0xCCC) >> 0xC;
                    temp_v0_4 = CrearParticula((s32) M2C_FIELD(temp_s4, s8 *, 1), (s32) arg0, (s32) var_s0, 0, /* extra? */ 0, /* extra? */ 0x28F, /* extra? */ 0, /* extra? */ temp_s2_3, /* extra? */ ((s32) (rcos(var_s1) * 0xCCC) >> 0xC), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 5, /* extra? */ 0x202, /* extra? */ 0);
                    if (temp_v0_4 != 0) {
                        M2C_FIELD(temp_v0_4, s32 *, 0x3C) = 0x4E;
                    }
                    var_s0 += 0x3E8;
                    goto loop_26;
                }
                var_s1 += 0x384;
                goto loop_28;
            }
            if (func_80022EF4(1) == -1) {
                temp_s0_2 = &p_sabrina->extra;
                hechizos[M2C_FIELD(arg0, s8 *, 0x74)] = 5;
                M2C_FIELD(temp_s0_2, s8 *, 0x24) = func_80022EF4(1);
            } else {
                func_80022EF4(0xFF);
            }
            hechizos[M2C_FIELD(arg0, s8 *, 0x74)] = 5;
            M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
        }
    }
}
