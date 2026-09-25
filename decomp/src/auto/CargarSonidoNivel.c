#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_80074C74[];
extern s16 D_80074C94[];
extern u8 D_80074CB4[];
extern u8 D_80074CC0[];
extern u8 D_8007C8B8[];
extern s8 nivel_actual;
extern s32 D_8007CBDC;
extern s32 D_8007CBE0;
extern s16 D_8007CBE4;


void CargarSonidoNivel(s32 arg0) {
    M2C_UNK sp20;
    M2C_UNK spA0;
    M2C_UNK sp140;
    s16 temp_s0;
    s32 temp_s1;
    s32 temp_s1_2;
    void *temp_v0;

    ArchivoIniciar((s32) &spA0);
    ArchivoIniciar((s32) &sp140);
    sprintf((s32) &sp20, (s32) "SOUND\\%s", arg0);
    temp_v0 = func_80014FF0((s32) &sp20, 0x2E);
    M2C_FIELD(temp_v0, s8 *, 1) = 0x56;
    M2C_FIELD(temp_v0, s8 *, 2) = 0x48;
    M2C_FIELD(temp_v0, s8 *, 3) = 0x44;
    ArchivoAbrir((s32) &spA0, (s32) &sp20, 1);
    temp_s1 = D_80074C74[nivel_actual] << 0xA;
    D_8007CBDC = Reservar(temp_s1, (s32) D_8007C8B8);
    ArchivoLeer((s32) &spA0, D_8007CBDC, temp_s1);
    M2C_FIELD(temp_v0, s8 *, 1) = 0x56;
    M2C_FIELD(temp_v0, s8 *, 2) = 0x42;
    M2C_FIELD(temp_v0, s8 *, 3) = 0x44;
    ArchivoAbrir((s32) &sp140, (s32) &sp20, 1);
    temp_s1_2 = D_80074C94[nivel_actual] << 0xA;
    D_8007CBE0 = Reservar(temp_s1_2, (s32) D_8007C8B8);
    ArchivoLeer((s32) &sp140, D_8007CBE0, temp_s1_2);
    SpuSetTransferMode(0);
    D_8007CBE4 = func_80044C40(D_8007CBDC, -1);
    temp_s0 = D_8007CBE4;
    if ((temp_s0 >= 0) && (temp_s0 == SsVabTransBody(D_8007CBE0, (s32) temp_s0))) {
        SsVabTransCompleted(1);
        Liberar(D_8007CBE0);
        ArchivoCerrar((s32) &sp140, -1);
        ArchivoCerrar((s32) &spA0, -1);
        return;
    }
    printf((s32) "SsVabError..!  :o( \n");
    Afirmar(0);
    ArchivoCerrar((s32) &sp140, -1);
    ArchivoCerrar((s32) &spA0, -1);
}
