#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800686C4[];
extern u8 D_800686DC[];
extern u8 D_80068718[];
extern u8 D_8007A1E8[];
extern u8 D_8007C7C8[];


s32 func_8001B0C8(s32 arg0) {
    M2C_UNK sp2C;
    M2C_UNK sp40;
    M2C_UNK spC0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s3;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a1;
    s32 var_t9;
    s32 var_v0;
    u16 *temp_v1;
    u16 temp_v0_2;
    u32 var_s4;

    var_s4 = saved_reg_s4;
    ArchivoIniciar((s32) &spC0);
    temp_v0 = Reservar(0x20, (s32) D_800686C4);
    memset(temp_v0, 0, 0x20);
    if (func_80014FF0(arg0, 0x21) != 0) {
        var_s4 = (M2C_FIELD(func_80014FF0(arg0, 0x21), s8 *, 1) - 0x41) & 0xFFFF;
        M2C_FIELD(temp_v0, u8 *, 0x1C) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x1C) | 1);
        if (var_s4 >= 4U) {
            printf((s32) D_800686DC);
            Afirmar(0);
        }
    }
    if (func_80014FF0(arg0, 0x26) != 0) {
        M2C_FIELD(temp_v0, u8 *, 0x1C) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x1C) | 2);
    }
    if (func_80014FF0(arg0, -0x5D) != 0) {
        M2C_FIELD(temp_v0, u8 *, 0x1C) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x1C) | 8);
    }
    if (func_80014FF0(arg0, 0x23) != 0) {
        M2C_FIELD(temp_v0, u8 *, 0x1C) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x1C) | 4);
    }
    sprintf((s32) &sp40, (s32) D_8007C7C8, D_8007A1E8, arg0);
    ArchivoAbrir((s32) &spC0, (s32) &sp40, 1);
    ArchivoLeer((s32) &spC0, (s32) &sp2C, 0x12);
    M2C_FIELD(temp_v0, s16 *, 8) = (s16) (sp38 + (sp39 << 8));
    M2C_FIELD(temp_v0, s16 *, 0xA) = (s16) (sp3A + (sp3B << 8));
    temp_s2 = Reservar(M2C_FIELD(temp_v0, s16 *, 8) * M2C_FIELD(temp_v0, s16 *, 0xA) * 2, (s32) D_800686C4);
    temp_s3 = Reservar(M2C_FIELD(temp_v0, s16 *, 8) * M2C_FIELD(temp_v0, s16 *, 0xA) * 2, (s32) D_800686C4);
    if (sp3C == 0x18) {
        func_80019FBC((s32) &spC0, temp_v0, temp_s2);
    } else if ((sp3C == 0xF) || (sp3C == 0x10)) {
        func_8001A108((s32) &spC0, temp_v0, temp_s2);
    } else {
        printf((s32) D_80068718);
    }
    func_8001A668(temp_s2, (s32) M2C_FIELD(temp_v0, s16 *, 8), (s32) M2C_FIELD(temp_v0, s16 *, 0xA));
    temp_s2_2 = func_8001A754(temp_v0, temp_s2, temp_s3, M2C_FIELD(temp_v0, s16 *, 8) * M2C_FIELD(temp_v0, s16 *, 0xA));
    func_8001A4C0(temp_v0);
    temp_s1 = M2C_FIELD(temp_v0, s16 *, 8) << M2C_FIELD(temp_v0, u8 *, 0x1D);
    if (M2C_FIELD(temp_v0, u8 *, 0x1C) & 1) {
        var_a0 = 0;
        var_a1 = 0;
loop_20:
        if (var_a0 != M2C_FIELD(temp_v0, u16 *, 0x1A)) {
            temp_v1 = temp_s3 + var_a1;
            temp_v0_2 = *temp_v1;
            if (temp_v0_2 != 0) {
                *temp_v1 = temp_v0_2 | 0x8000;
            }
            var_a0 = (var_a0 + 1) & 0xFFFF;
            var_a1 += 2;
            goto loop_20;
        }
    }
    if (M2C_FIELD(temp_v0, u8 *, 0x1D) == 0) {
        var_v0 = LoadClut2(temp_s3, (s32) M2C_FIELD(temp_v0, u16 *, 0x16), (s32) M2C_FIELD(temp_v0, u16 *, 0x18));
    } else {
        var_v0 = LoadClut(temp_s3, (s32) M2C_FIELD(temp_v0, u16 *, 0x16), (s32) M2C_FIELD(temp_v0, u16 *, 0x18));
    }
    M2C_FIELD(temp_v0, s16 *, 0xE) = (s16) var_v0;
    func_8001A228(temp_v0, temp_s1);
    var_t9 = temp_s1 >> 2;
    if (temp_s1 < 0) {
        var_t9 = (s32) (temp_s1 + 3) >> 2;
    }
    func_8001A620(temp_v0, var_t9 & 0xFFFF, temp_s2_2);
    M2C_FIELD(temp_v0, s16 *, 0xC) = GetTPage((s32) M2C_FIELD(temp_v0, u8 *, 0x1D), (s32) var_s4, M2C_FIELD(temp_v0, u16 *, 0x12) & ~0x3F, (s32) M2C_FIELD(temp_v0, u16 *, 0x14));
    M2C_FIELD(temp_v0, s8 *, 0x10) = (s8) ((M2C_FIELD(temp_v0, u16 *, 0x12) & 0x3F) << (2 - M2C_FIELD(temp_v0, u8 *, 0x1D)));
    M2C_FIELD(temp_v0, s8 *, 0x11) = (s8) M2C_FIELD(temp_v0, u16 *, 0x14);
    Liberar(temp_s2_2);
    Liberar(temp_s3);
    ArchivoCerrar((s32) &spC0, -1);
    return temp_v0;
}
