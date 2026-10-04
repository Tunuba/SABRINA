#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80068830[];
extern u8 D_8007A1D0[];
extern u8 D_8007C7E0[];
extern s32 D_8007CA48;
extern s32 D_8007CBCC;
extern s32 D_8007CBD0;


void HerramientaArmarCuadricula(s32 arg0, s32 arg1) {
    M2C_UNK sp24;
    M2C_UNK spA4;
    s16 sp144;
    void *temp_v0;

    ArchivoIniciar((s32) &spA4);
    sprintf((s32) &sp24, (s32) D_8007C7E0, D_8007A1D0, arg0);
    temp_v0 = func_80014FF0((s32) &sp24, 0x2E);
    M2C_FIELD(temp_v0, s8 *, 1) = 0x58;
    M2C_FIELD(temp_v0, s8 *, 2) = 0x44;
    M2C_FIELD(temp_v0, s8 *, 3) = 0x58;
    ArchivoAbrir((s32) &spA4, (s32) &sp24, 1);
    ArchivoLeer((s32) &spA4, (s32) &sp144, 0xC);
    func_80029530(arg1, (s32) &sp144);
    D_8007CA48 = Reservar(sp144 * 0xC, (s32) D_80068830);
    D_8007CBCC = Reservar(sp146 * 8, (s32) D_80068830);
    D_8007CBD0 = Reservar(sp14C * 2, (s32) D_80068830);
    ArchivoLeer((s32) &spA4, D_8007CA48, sp144 * 0xC);
    func_80029530(arg1, D_8007CA48);
    ArchivoLeer((s32) &spA4, D_8007CBCC, sp146 * 8);
    func_80029530(arg1, D_8007CBCC);
    ArchivoLeer((s32) &spA4, D_8007CBD0, sp14C * 2);
    func_80029530(arg1, D_8007CBD0);
    Liberar(D_8007CA48);
    Liberar(D_8007CBCC);
    Liberar(D_8007CBD0);
    ArchivoCerrar((s32) &spA4, -1);
}
