#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800686C4[];
extern u8 D_80068718[];
extern s8 D_80068730[];
extern u8 D_8007A220[];
extern u8 D_8007C7C8[];


s32 func_8001B9C0(s32 arg0, s32 arg1) {
    s8 sp34;
    M2C_UNK spB4;
    s16 spBC;
    s16 spBE;
    s16 spCE;
    u8 spD1;
    M2C_UNK spD4;
    M2C_UNK spE8;
    s16 temp_v0_2;
    s32 temp_s2;
    s32 temp_s4;
    s32 var_s0;
    s32 var_s1;
    s32 var_s3;
    s32 var_s5;
    s32 var_t9;
    s32 var_t9_2;
    s8 *var_t7;
    s8 *var_t8;
    u8 temp_a0;
    u8 temp_v0_3;
    void *temp_v0;

    var_s1 = arg0;
    var_t8 = D_80068730;
    var_t7 = &sp34;
    var_t9 = 0x80;
    do {
        var_t9 -= 1;
        *var_t7 = *var_t8;
        var_t8 += 1;
        var_t7 += 1;
    } while (var_t9 > 0);
    ArchivoIniciar((s32) &spE8);
    temp_s2 = Reservar(0xFA2, (s32) D_800686C4);
    spCE = 0x10;
    spD1 = 0;
    var_s5 = 0;
    var_s3 = 0 & 0xFFFF;
    spBE = 0x20;
    sprintf((s32) &sp34, (s32) D_8007C7C8, D_8007A220, arg1);
    temp_v0 = func_80014FF0((s32) &sp34, 0x2E);
    M2C_FIELD(temp_v0, s8 *, 1) = 0x54;
    M2C_FIELD(temp_v0, s8 *, 2) = 0x47;
    M2C_FIELD(temp_v0, s8 *, 3) = 0x41;
    ArchivoAbrir((s32) &spE8, (s32) &sp34, 1);
    ArchivoLeer((s32) &spE8, (s32) &spD4, 0x12);
    spBC = spE0 + (spE1 << 8);
    temp_v0_2 = spE2 + (spE3 << 8);
    spBE = temp_v0_2;
    temp_s4 = Reservar(spBC * temp_v0_2 * 2, (s32) D_800686C4);
    if (spE4 == 0x18) {
        func_80019FBC((s32) &spE8, (s32) &spB4, temp_s4);
    } else if ((spE4 == 0xF) || (spE4 == 0x10)) {
        func_8001A108((s32) &spE8, (s32) &spB4, temp_s4);
    } else {
        printf((s32) D_80068718);
    }
    func_8001A668(temp_s4, (s32) spBC, (s32) spBE);
    do {
        var_s0 = func_8001ADD8(temp_s4, var_s1, spBC & 0xFFFF, var_s5);
        if (var_s0 != 0) {
            func_8001A4C0((s32) &spB4);
            var_s0 = func_8001A754((s32) &spB4, var_s0, temp_s2, M2C_FIELD(var_s1, u8 *, 0xA) * M2C_FIELD(var_s1, u8 *, 0xB));
            M2C_FIELD(var_s1, s16 *, 6) = LoadClut2(temp_s2, (s32) spCA, (s32) spCC);
            func_8001A228((s32) &spB4, (s32) M2C_FIELD(var_s1, u8 *, 0xA));
            temp_v0_3 = M2C_FIELD(var_s1, u8 *, 0xA);
            var_t9_2 = (s32) temp_v0_3 >> 2;
            if ((s32) temp_v0_3 < 0) {
                var_t9_2 = (s32) (temp_v0_3 + 3) >> 2;
            }
            func_8001A620((s32) &spB4, var_t9_2 & 0xFFFF, var_s0);
            M2C_FIELD(var_s1, s8 *, 4) = GetTPage((s32) spD1, 0, spC6 & ~0x3F, (s32) spC8);
            M2C_FIELD(var_s1, s8 *, 8) = (s8) ((spC6 & 0x3F) * 4);
            M2C_FIELD(var_s1, s8 *, 9) = (s8) spC8;
            temp_a0 = M2C_FIELD(var_s1, u8 *, 0xA);
            var_s5 = (var_s5 + ((temp_a0 + 1) & 0xFFFF)) & 0xFFFF;
            M2C_FIELD(var_s1, u8 *, 0xA) = (u8) (temp_a0 - 1);
            var_s1 += 0xC;
            var_s3 = (var_s3 + 1) & 0xFFFF;
            Liberar(var_s0);
        }
    } while (var_s0 != 0);
    Liberar(temp_s2);
    Liberar(temp_s4);
    ArchivoCerrar((s32) &spE8, -1);
    return var_s3;
}
