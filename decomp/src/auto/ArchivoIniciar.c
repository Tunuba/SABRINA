#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80065468[];


void ArchivoIniciar(s32 arg0) {
    M2C_FIELD(arg0, s8 *, 0x14) = 1;
    M2C_FIELD(arg0, s32 *, 0) = Reservar(0xC801, (s32) "File.cpp");
    Afirmar(M2C_FIELD(arg0, s32 *, 0));
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 0) + 0x4801 + 0x7FFF);
}
