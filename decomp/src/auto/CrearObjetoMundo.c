#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 modelos_cargados[];
extern u8 D_8006EE70[];
extern u8 D_8007007C[];
extern u8 D_80071288[];
extern u8 D_80072494[];
extern u8 D_800736A0[];
extern u8 tabla_clases_niveles[];
extern s32 D_8007C9F0;
extern s8 nivel_actual;

u8 tabla_clases_niveles[0x40];                      /* unable to generate initializer: cannot parse D_8007007C as integer */

void CrearObjetoMundo(s32 arg0) {
    s16 temp_v0_2;
    s16 temp_v1;
    s32 *var_t7;
    s32 *var_t8;
    s32 temp_a0;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s3_3;
    s32 temp_v0;
    s32 var_t9;
    void *temp_s2;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0xC);
    if (temp_v1 < 0x37) {
        if ((temp_v1 == 0x17) || (temp_v1 == 0x13) || (temp_v1 == 0x12) || (temp_v1 == 4)) {
            if (RecogibleNoTomado(arg0) != 0) {
                CrearRecogible(arg0);
            }
        } else {
            temp_s2 = *(tabla_clases_niveles + (nivel_actual * 4)) + (temp_v1 * 0x54);
            temp_v0 = func_800256E0();
            if (temp_v0 != 0) {
                M2C_FIELD(temp_v0, s16 *, 0x22) = (s16) M2C_FIELD(arg0, s16 *, 0xC);
                M2C_FIELD(temp_v0, s32 *, 0x6C) = arg0;
                temp_a0 = *(modelos_cargados + (M2C_FIELD(temp_s2, s16 *, 0x22) * 4));
                if (temp_a0 != 0) {
                    M2C_FIELD(temp_v0, s32 *, 0x60) = func_8001E06C(temp_a0, D_8007C9F0);
                    func_800206E0();
                }
                M2C_FIELD(temp_v0, s32 *, 0x64) = (s32) M2C_FIELD(temp_s2, s32 *, 0x24);
                M2C_FIELD(temp_v0, s32 *, 0x24) = (s32) M2C_FIELD(arg0, s32 *, 0);
                M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) M2C_FIELD(arg0, s32 *, 4);
                M2C_FIELD(temp_v0, s32 *, 0x2C) = (s32) M2C_FIELD(arg0, s32 *, 8);
                M2C_FIELD(temp_v0, s16 *, 0x30) = (s16) M2C_FIELD(arg0, s16 *, 0xE);
                M2C_FIELD(temp_v0, s16 *, 0x32) = (s16) M2C_FIELD(arg0, s16 *, 0x10);
                M2C_FIELD(temp_v0, s16 *, 0x34) = (s16) M2C_FIELD(arg0, s16 *, 0x12);
                M2C_FIELD(temp_v0, s32 *, 0x54) = (s32) ((s32) (M2C_FIELD(temp_s2, s16 *, 0x28) * M2C_FIELD(arg0, s16 *, 0x14)) >> 0xC);
                M2C_FIELD(temp_v0, s32 *, 0x58) = (s32) ((s32) (M2C_FIELD(temp_s2, s16 *, 0x2A) * M2C_FIELD(arg0, s16 *, 0x16)) >> 0xC);
                M2C_FIELD(temp_v0, s32 *, 0x5C) = (s32) ((s32) (M2C_FIELD(temp_s2, s16 *, 0x2C) * M2C_FIELD(arg0, s16 *, 0x18)) >> 0xC);
                func_8001E588(temp_v0);
                func_80024A48(temp_v0);
                var_t8 = temp_s2 + 0x30;
                M2C_FIELD(temp_v0, s32 *, 0) = (s32) M2C_FIELD(temp_s2, s32 *, 4);
                var_t7 = temp_v0 + 0xF4;
                M2C_FIELD(temp_v0, s32 *, 4) = (s32) M2C_FIELD(temp_s2, s32 *, 8);
                var_t9 = 9;
                M2C_FIELD(temp_v0, s32 *, 8) = (s32) M2C_FIELD(temp_s2, s32 *, 0xC);
                M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) M2C_FIELD(temp_s2, s32 *, 0x10);
                M2C_FIELD(temp_v0, s32 *, 0x10) = (s32) M2C_FIELD(temp_s2, s32 *, 0x14);
                M2C_FIELD(temp_v0, s32 *, 0x14) = (s32) M2C_FIELD(temp_s2, s32 *, 0x18);
                M2C_FIELD(temp_v0, s32 *, 0x18) = (s32) M2C_FIELD(temp_s2, s32 *, 0x1C);
                do {
                    var_t9 -= 1;
                    *var_t7 = *var_t8;
                    var_t8 += 4;
                    var_t7 += 4;
                } while (var_t9 > 0);
                M2C_FIELD(temp_v0, s32 *, 0xF4) = (s32) (temp_v0 + 0x24);
                temp_v0_2 = M2C_FIELD(temp_v0, s16 *, 0x110);
                if (temp_v0_2 != 1) {
                    if (temp_v0_2 != 2) {
                        if (temp_v0_2 == 3) {
                            temp_s3 = temp_v0 + 0xF4;
                            func_80039A34(temp_s3, func_8003A258(temp_s3), (s32) M2C_FIELD(temp_v0, s16 *, 0x114), (s32) M2C_FIELD(temp_v0, s16 *, 0x112));
                        }
                    } else {
                        temp_s3_2 = temp_v0 + 0xF4;
                        func_80039A70(temp_s3_2, func_8003A250(temp_s3_2), (s32) M2C_FIELD(temp_v0, s16 *, 0x114), (s32) M2C_FIELD(temp_v0, s16 *, 0x112));
                    }
                } else {
                    temp_s3_3 = temp_v0 + 0xF4;
                    func_80039B1C(temp_s3_3, func_8003A260(temp_s3_3), (s32) M2C_FIELD(temp_v0, s16 *, 0x114), (s32) M2C_FIELD(temp_v0, s16 *, 0x112));
                }
                memcpy(temp_v0 + 0x74, arg0 + 0x1C, 0x7F);
                M2C_FIELD(temp_s2, M2C_UNK (**)(s32, M2C_UNK, M2C_UNK), 0)(temp_v0, 0, 0);
            }
        }
    }
}
