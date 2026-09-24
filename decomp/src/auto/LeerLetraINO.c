#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8007C798[];
extern u16 D_8007CA0C;
extern s32 D_8007CA10;
extern u8 D_8007CAE8;


void LeerLetraINO(s32 arg0) {
    ArchivoLeer(arg0, (s32) &D_8007CA0C, 2);
    D_8007CA10 = Reservar(D_8007CA0C * 0xC, (s32) "Font.c");
    ArchivoLeer(arg0, D_8007CA10, D_8007CA0C * 0xC);
    D_8007CAE8 += 1;
}
