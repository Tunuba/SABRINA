#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006C444;
extern s32 D_8006C448;
extern s32 D_8006C44C;
extern s32 D_8006C450;
extern s32 D_8006C454;
extern s32 D_8006C458;
extern s32 D_8006C45C;
extern s32 D_8006C460;
extern s32 D_8006C464;
extern s16 D_8007CA1C;
extern s16 D_8007CA20;


void func_80048024(void) {
    D_8007CA1C = 7;
    D_8006C444 = 0x300;
    D_8006C448 = -0x28E;
    D_8006C44C = -0xB4;
    D_8006C450 = -0x1000;
    D_8006C454 = 0x400;
    D_8006C458 = 0;
    D_8006C45C = 0;
    D_8006C460 = 0x1000;
    D_8007CA20 = 0;
    D_8006C464 = 0;
}
