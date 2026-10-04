#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800C8558;
extern s16 D_800C855A;
extern s16 D_800C855C;
extern s16 gemas;
extern s8 nivel_actual;


s32 func_8004C3A0(void) {
    switch (nivel_actual) {
    case 1:
    case 2:
    case 3:
        gemas += 1;
        return (s32) gemas;
    case 4:
    case 5:
    case 6:
        D_800C8558 += 1;
        return (s32) D_800C8558;
    case 7:
    case 8:
    case 9:
        D_800C855A += 1;
        return (s32) D_800C855A;
    case 10:
    case 11:
    case 12:
        D_800C855C += 1;
        return (s32) D_800C855C;
    default:
        return 0;
    }
}
