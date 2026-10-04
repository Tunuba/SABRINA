#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007C8D8[];
extern s16 jugando;
extern s8 nivel_actual;
extern s8 D_8007CA01;
extern s8 D_8007CA38;
extern s32 D_8007CB34;
extern u16 D_8007CC00;
extern s32 D_8007CC04;


void func_80047010(void) {
    D_8007CA01 = nivel_actual;
    nivel_actual = (s8) D_8007C8D8[D_8007CC00];
    jugando = 0;
    D_8007CA38 = 0;
    D_8007CC04 = 0;
    D_8007CB34 = 0;
}
