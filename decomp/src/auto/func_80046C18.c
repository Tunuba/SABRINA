#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA14;
extern s16 D_8007CA20;
extern s32 D_8007CA50;
extern s16 D_8007CD7C;
extern s16 D_8007CD7E;
extern s16 D_8007CD90;
extern s16 D_8007CD92;


void func_80046C18(void) {
    D_8007CA14 = 1;
    D_8007CA20 = 0xF;
    if ((D_8007CA50 & 0x8000) && (D_8007CD7C != 0)) {
        D_8007CD7C -= 1;
        D_8007CD90 -= 1;
    }
    if ((D_8007CA50 & 0x2000) && (D_8007CD7C < 0x1E)) {
        D_8007CD7C += 1;
        D_8007CD90 += 1;
    }
    if ((D_8007CA50 & 0x1000) && (D_8007CD7E != 0)) {
        D_8007CD7E -= 1;
        D_8007CD92 -= 1;
    }
    if ((D_8007CA50 & 0x4000) && (D_8007CD7E < 0x32)) {
        D_8007CD7E += 1;
        D_8007CD92 += 1;
    }
}
