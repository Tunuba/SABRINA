#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 puntos_ruta[];
extern u8 D_8006CF3C[];
extern u8 D_8007A1DC[];
extern u8 D_8007C894[];
extern s32 D_8007CB3C;
extern s32 D_8007CB40;
extern s32 D_8007CCAC;


void CargarWRLDDATA(s32 arg0) {
    M2C_UNK sp18;
    M2C_UNK sp98;
    s32 temp_s0;
    void *temp_v0;

    ArchivoIniciar((s32) &sp98);
    sprintf((s32) &sp18, (s32) "%s%s", "WRLDDATA\\", arg0);
    temp_v0 = func_80014FF0((s32) &sp18, 0x2E);
    M2C_FIELD(temp_v0, s8 *, 1) = 0x42;
    M2C_FIELD(temp_v0, s8 *, 2) = 0x49;
    M2C_FIELD(temp_v0, s8 *, 3) = 0x4E;
    ArchivoAbrir((s32) &sp98, (s32) &sp18, 1);
    ArchivoLeer((s32) &sp98, (s32) &D_8007CB3C, 4);
    temp_s0 = D_8007CB3C * 0x9C;
    D_8007CB40 = Reservar(temp_s0, (s32) "WobjCode.c");
    memset(D_8007CB40, 0, temp_s0);
    ArchivoLeer((s32) &sp98, D_8007CB40, temp_s0);
    ArchivoLeer((s32) &sp98, (s32) &D_8007CCAC, 4);
    if (D_8007CCAC != 0) {
        ArchivoLeer((s32) &sp98, (s32) puntos_ruta, D_8007CCAC * 0x18);
    }
    CrearObjetoMundo(D_8007CB40);
    CrearObjetoMundo(D_8007CB40 + 0x9C);
    ArchivoCerrar((s32) &sp98, -1);
}
