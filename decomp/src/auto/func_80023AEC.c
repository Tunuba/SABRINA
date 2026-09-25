#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8006CE50[];
extern s16 D_8007C884[];
extern u16 D_8007C888[];
extern s8 nivel_actual;
extern u16 D_8007CB38;


void func_80023AEC(void) {
    s16 var_v0;

    *D_8007C888 = D_8006CE50[nivel_actual];
    if (D_8007CB38 != 0) {
        var_v0 = D_8007CB38 + 0x37;
    } else {
        var_v0 = 0x32;
    }
    *D_8007C884 = var_v0;
}
