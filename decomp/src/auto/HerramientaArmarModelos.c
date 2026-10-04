#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80068830[];
extern u8 D_8007A1D0[];
extern u8 D_8007B7C0[];
extern u8 D_8007B7CC[];
extern u8 D_8007B834[];
extern u8 D_8007B8AC[];
extern u8 D_8007B974[];
extern u8 D_8007BA3C[];
extern u8 D_8007BB04[];
extern u8 D_8007BBD0[];
extern u8 D_8007BC9C[];
extern u8 D_8007BD68[];
extern u8 D_8007BE34[];
extern u8 D_8007BF04[];
extern u8 D_8007BFD4[];
extern u8 D_8007C0A4[];
extern u8 D_8007C174[];
extern u8 tabla_modelos_niveles[];
extern u8 D_8007C7E0[];

u8 tabla_modelos_niveles[0x40];                     /* unable to generate initializer: cannot parse D_8007B7C0 as integer */

void HerramientaArmarModelos(s32 arg0, s32 arg1) {
    s16 sp38;
    M2C_UNK sp514;
    M2C_UNK sp594;
    M2C_UNK sp634;
    s32 sp6D4;
    u16 sp6DA;
    u16 sp6DC;
    u16 sp6DE;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s7;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s4;
    s32 var_s6;
    s32 var_s6_2;
    u16 temp_a0;
    void *temp_v0;

    sp6DA = 0;
    temp_s7 = *(tabla_modelos_niveles + (arg1 * 4));
    var_s6 = 0;
    sp38 = 0;
    var_s4 = 0;
    do {
        temp_v1 = var_s6;
        var_s6 = (temp_v1 + 1) & 0xFFFF;
        temp_s3 = *(temp_s7 + (temp_v1 * 4));
        var_s4 += 2;
        if (temp_s3 != 0) {
            ArchivoIniciar((s32) &sp594);
            sprintf((s32) &sp514, (s32) D_8007C7E0, D_8007A1D0, temp_s3);
            temp_v0 = func_80014FF0((s32) &sp514, 0x2E);
            M2C_FIELD(temp_v0, s8 *, 1) = 0x54;
            M2C_FIELD(temp_v0, s8 *, 2) = 0x4E;
            M2C_FIELD(temp_v0, s8 *, 3) = 0x46;
            ArchivoAbrir((s32) &sp594, (s32) &sp514, 1);
            ArchivoLeer((s32) &sp594, (s32) &sp6DC, 2);
            ArchivoLeer((s32) &sp594, (s32) &sp6DE, 2);
            temp_v0_2 = Reservar((s32) sp6DE, (s32) D_80068830);
            ArchivoLeer((s32) &sp594, temp_v0_2, (s32) sp6DE);
            var_s0 = temp_v0_2;
loop_4:
            sp6DC -= 1;
            if (sp6DC != 0) {
                temp_v1_2 = var_s0 + 1;
                temp_s2 = *var_s0 & 0xFF;
                temp_v0_3 = func_8001B600(temp_v1_2);
                temp_a0 = sp6DA;
                var_s0 = temp_v1_2 + temp_s2;
                sp6DA = temp_a0 + 1;
                M2C_FIELD((sp + (temp_a0 * 4)), s32 *, 0x114) = temp_v0_3;
                goto loop_4;
            }
            Liberar(temp_v0_2);
            ArchivoCerrar((s32) &sp594, -1);
        }
        M2C_FIELD((sp + var_s4), u16 *, 0x38) = sp6DA;
    } while (temp_s3 != 0);
    func_80029530(arg0, (s32) &sp6DA);
    var_s0_2 = 0;
    sp6D4 = 0;
loop_9:
    if (var_s0_2 != sp6DA) {
        func_80029530(arg0, M2C_FIELD((sp + sp6D4), s32 *, 0x114));
        var_s0_2 = (var_s0_2 + 1) & 0xFFFF;
        sp6D4 += 4;
        goto loop_9;
    }
    func_80029530(arg0, (s32) &sp38);
    var_s6_2 = 0;
    var_s0_3 = -1;
    do {
        temp_v1_3 = var_s6_2;
        var_s6_2 = (temp_v1_3 + 1) & 0xFFFF;
        temp_s3_2 = *(temp_s7 + (temp_v1_3 * 4));
        var_s0_3 += 1;
        if (temp_s3_2 != 0) {
            ArchivoIniciar((s32) &sp634);
            sprintf((s32) &sp514, (s32) D_8007C7E0, D_8007A1D0, temp_s3_2);
            ArchivoAbrir((s32) &sp634, (s32) &sp514, 1);
            func_8001CB4C((s32) &sp634, 1, arg0, (s32) M2C_FIELD((sp + (var_s0_3 * 2)), u16 *, 0x38));
            ArchivoCerrar((s32) &sp634, -1);
        }
    } while (temp_s3_2 != 0);
}
