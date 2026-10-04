#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800686C4[];
extern u8 D_8007A1D0[];
extern u8 D_8007A20C[];
extern u8 D_8007C7C8[];


void HerramientaConvertirPIC(s32 arg0) {
    M2C_UNK sp24;
    M2C_UNK sp38;
    M2C_UNK spB8;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 temp_v0_5;
    void *temp_v0_2;
    void *temp_v0_4;

    ArchivoIniciar((s32) &spB8);
    temp_v0 = Reservar(0x20, (s32) D_800686C4);
    memset(temp_v0, 0, 0x20);
    sprintf((s32) &sp38, (s32) D_8007C7C8, D_8007A20C, arg0);
    temp_v0_2 = func_80014FF0((s32) &sp38, 0x2E);
    M2C_FIELD(temp_v0_2, s8 *, 1) = 0x54;
    M2C_FIELD(temp_v0_2, s8 *, 2) = 0x47;
    M2C_FIELD(temp_v0_2, s8 *, 3) = 0x41;
    ArchivoAbrir((s32) &spB8, (s32) &sp38, 1);
    ArchivoLeer((s32) &spB8, (s32) &sp24, 0x12);
    M2C_FIELD(temp_v0, s16 *, 8) = (s16) (sp30 + (sp31 << 8));
    M2C_FIELD(temp_v0, s16 *, 0xA) = (s16) (sp32 + (sp33 << 8));
    temp_v0_3 = Reservar(M2C_FIELD(temp_v0, s16 *, 8) * M2C_FIELD(temp_v0, s16 *, 0xA) * 2, (s32) D_800686C4);
    func_8001A108((s32) &spB8, temp_v0, temp_v0_3);
    func_8001A668(temp_v0_3, (s32) M2C_FIELD(temp_v0, s16 *, 8), (s32) M2C_FIELD(temp_v0, s16 *, 0xA));
    sprintf((s32) &sp38, (s32) D_8007C7C8, D_8007A1D0, arg0);
    temp_v0_4 = func_80014FF0((s32) &sp38, 0x2E);
    M2C_FIELD(temp_v0_4, s8 *, 1) = 0x50;
    M2C_FIELD(temp_v0_4, s8 *, 2) = 0x49;
    M2C_FIELD(temp_v0_4, s8 *, 3) = 0x43;
    temp_v0_5 = func_800294F0((s32) &sp38);
    func_80029530(temp_v0_5, temp_v0_3);
    func_80029518(temp_v0_5);
    Liberar(temp_v0_3);
    Liberar(temp_v0);
    ArchivoCerrar((s32) &spB8, -1);
}
