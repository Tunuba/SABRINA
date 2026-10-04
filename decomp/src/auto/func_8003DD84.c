#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007C8C4;
extern s16 D_8007CBE8;


void func_8003DD84(void) {
    D_8007CBE8 = D_8007C8C4 * 0x3F8;
}
