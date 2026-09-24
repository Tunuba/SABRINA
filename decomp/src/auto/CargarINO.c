#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8007A1D0[];
extern u8 D_8007C784[];


void CargarINO(s32 arg0, s32 arg1) {
    M2C_UNK sp20;
    M2C_UNK spA0;
    void *temp_v0;

    ArchivoIniciar((s32) &spA0);
    sprintf((s32) &sp20, (s32) "%s%s", "GRAPHICS\\", arg0);
    temp_v0 = func_80014FF0((s32) &sp20, 0x2E);
    M2C_FIELD(temp_v0, s8 *, 1) = 0x49;
    M2C_FIELD(temp_v0, s8 *, 2) = 0x4E;
    M2C_FIELD(temp_v0, s8 *, 3) = 0x4F;
    ArchivoAbrir((s32) &spA0, (s32) &sp20, 1);
    LeerCuadriculaINO((s32) &spA0);
    LeerSpritesINO((s32) &spA0);
    LeerModelosINO((s32) &spA0, arg1);
    LeerLetraINO((s32) &spA0);
    LeerParticulasINO((s32) &spA0);
    ArchivoCerrar((s32) &spA0, -1);
}
