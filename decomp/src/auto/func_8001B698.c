#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800686C4[];
extern u8 D_800686DC[];
extern u8 D_8007A1F8[];
extern u8 D_8007C7C8[];


s32 func_8001B698(s32 arg0) {
    M2C_UNK sp2C;
    M2C_UNK sp40;
    M2C_UNK spC0;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a1;
    s32 var_t9;
    s32 var_t9_2;
    s32 var_t9_3;
    u16 *temp_v1;
    u16 temp_v0_2;
    u32 var_s3;

    var_s3 = saved_reg_s3;
    ArchivoIniciar((s32) &spC0);
    temp_v0 = Reservar(0x20, (s32) D_800686C4);
    memset(temp_v0, 0, 0x20);
    sprintf((s32) &sp40, (s32) D_8007C7C8, D_8007A1F8, arg0);
    if (func_80014FF0(arg0, 0x21) != 0) {
        var_s3 = (M2C_FIELD(func_80014FF0(arg0, 0x21), s8 *, 1) - 0x41) & 0xFFFF;
        if (var_s3 >= 4U) {
            printf((s32) D_800686DC);
            Afirmar(0);
        }
    }
    ArchivoAbrir((s32) &spC0, (s32) &sp40, 1);
    ArchivoLeer((s32) &spC0, (s32) &sp2C, 0x12);
    M2C_FIELD(temp_v0, s16 *, 8) = (s16) (sp38 + (sp39 << 8));
    M2C_FIELD(temp_v0, s16 *, 0xA) = (s16) (sp3A + (sp3B << 8));
    temp_s2 = Reservar(M2C_FIELD(temp_v0, s16 *, 8) * M2C_FIELD(temp_v0, s16 *, 0xA) * 2, (s32) D_800686C4);
    temp_s1 = Reservar(M2C_FIELD(temp_v0, s16 *, 8) * M2C_FIELD(temp_v0, s16 *, 0xA) * 2, (s32) D_800686C4);
    func_8001A108((s32) &spC0, temp_v0, temp_s2);
    func_8001A668(temp_s2, (s32) M2C_FIELD(temp_v0, s16 *, 8), (s32) M2C_FIELD(temp_v0, s16 *, 0xA));
    temp_s2_2 = func_8001A754(temp_v0, temp_s2, temp_s1, M2C_FIELD(temp_v0, s16 *, 8) * M2C_FIELD(temp_v0, s16 *, 0xA));
    func_8001A4C0(temp_v0);
    var_a0 = 0;
    var_a1 = 0;
loop_7:
    if (var_a0 != M2C_FIELD(temp_v0, u16 *, 0x1A)) {
        temp_v1 = temp_s1 + var_a1;
        temp_v0_2 = *temp_v1;
        if (temp_v0_2 != 0) {
            *temp_v1 = temp_v0_2 | 0x8000;
        }
        var_a0 = (var_a0 + 1) & 0xFFFF;
        var_a1 += 2;
        goto loop_7;
    }
    M2C_FIELD(temp_v0, s16 *, 0xE) = LoadClut2(temp_s1, (s32) M2C_FIELD(temp_v0, u16 *, 0x16), (s32) M2C_FIELD(temp_v0, u16 *, 0x18));
    func_8001A228(temp_v0, (s32) M2C_FIELD(temp_v0, s16 *, 8));
    temp_v0_3 = M2C_FIELD(temp_v0, s16 *, 8);
    var_t9 = temp_v0_3 >> 2;
    if (temp_v0_3 < 0) {
        var_t9 = (s32) (temp_v0_3 + 3) >> 2;
    }
    func_8001A620(temp_v0, var_t9 & 0xFFFF, temp_s2_2);
    M2C_FIELD(temp_v0, s16 *, 0xC) = GetTPage((s32) M2C_FIELD(temp_v0, u8 *, 0x1D), (s32) var_s3, M2C_FIELD(temp_v0, u16 *, 0x12) & ~0x3F, (s32) M2C_FIELD(temp_v0, u16 *, 0x14));
    M2C_FIELD(temp_v0, u8 *, 0x10) = (u8) ((M2C_FIELD(temp_v0, u16 *, 0x12) & 0x3F) << (2 - M2C_FIELD(temp_v0, u8 *, 0x1D)));
    M2C_FIELD(temp_v0, u8 *, 0x11) = (u8) M2C_FIELD(temp_v0, u16 *, 0x14);
    M2C_FIELD(temp_v0, s8 *, 0x1C) = (s8) ((M2C_FIELD(temp_v0, u8 *, 0x10) + M2C_FIELD(temp_v0, s16 *, 8)) - 1);
    M2C_FIELD(temp_v0, u8 *, 0x1D) = (u8) ((M2C_FIELD(temp_v0, u8 *, 0x11) + M2C_FIELD(temp_v0, s16 *, 0xA)) - 1);
    temp_v0_4 = M2C_FIELD(temp_v0, s16 *, 8);
    var_t9_2 = temp_v0_4 >> 1;
    if (temp_v0_4 < 0) {
        var_t9_2 = (s32) (temp_v0_4 + 1) >> 1;
    }
    M2C_FIELD(temp_v0, s16 *, 8) = (s16) (var_t9_2 << 8);
    temp_v0_5 = M2C_FIELD(temp_v0, s16 *, 0xA);
    var_t9_3 = temp_v0_5 >> 1;
    if (temp_v0_5 < 0) {
        var_t9_3 = (s32) (temp_v0_5 + 1) >> 1;
    }
    M2C_FIELD(temp_v0, s16 *, 0xA) = (s16) (var_t9_3 << 8);
    Liberar(temp_s2_2);
    Liberar(temp_s1);
    ArchivoCerrar((s32) &spC0, -1);
    return temp_v0;
}
