#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8007CA20;
extern s32 D_8007CC40;
extern s32 D_8007CC44;
extern s16 D_8007CC4E;
extern s16 D_8007CC50;
extern s16 D_8007CC58;
extern s16 D_8007CC5A;


void func_8004FA10(void) {
    D_8007CC40 = 0;
    D_8007CC44 = 0;
    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CC50 = 0;
    D_8007CC4E = 0;
    D_8007CA20 = 0;
    func_800509A8();
    func_80050938();
}
