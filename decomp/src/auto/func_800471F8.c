#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 jugando;
extern s8 nivel_actual;
extern s8 D_8007CA01;
extern s8 D_8007CA38;
extern s32 D_8007CC04;


void func_800471F8(void) {
    jugando = 0;
    D_8007CA38 = 0;
    D_8007CA01 = 0;
    nivel_actual = 0xD;
    func_8004C82C();
    D_8007CC04 = 2;
}
