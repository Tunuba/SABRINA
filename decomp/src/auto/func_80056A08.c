#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800C8558;
extern s16 D_800C855A;
extern s16 D_800C855C;
extern s8 D_800C8562;
extern s8 D_800C8563;
extern s8 D_800C8564;
extern s8 D_800C8565;
extern s16 gemas;
extern s8 D_8007CA01;


s32 func_80056A08(void) {
    switch (D_8007CA01) {
    case 1:
    case 2:
    case 3:
        if ((D_800C8563 == 0) && (gemas >= 0x64)) {
            return 2;
        }
    default:
block_14:
        return 0;
    case 4:
    case 5:
    case 6:
        if ((D_800C8562 == 0) && (D_800C8558 >= 0x64)) {
            return 1;
        }
        goto block_14;
    case 7:
    case 8:
    case 9:
        if ((D_800C8565 == 0) && (D_800C855A >= 0x64)) {
            return 4;
        }
        goto block_14;
    case 10:
    case 11:
    case 12:
        if ((D_800C8564 == 0) && (D_800C855C >= 0x64)) {
            return 3;
        }
        goto block_14;
    }
}
