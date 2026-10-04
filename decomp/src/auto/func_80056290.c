#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C8566;
extern u16 D_8007CBD4;


s32 func_80056290(u32 arg0) {
    u16 var_v0;

    switch (arg0) {
    case 1:
    case 2:
    case 3:
        if (D_800C8566 == 1) {
            D_8007CBD4 |= 0x40;
            return 1;
        }
        var_v0 = D_8007CBD4 & 0xFFBF;
block_14:
        D_8007CBD4 = var_v0;
    default:
        return 0;
    case 4:
    case 5:
    case 6:
        if (D_800C8566 == 4) {
            D_8007CBD4 |= 0x40;
            return 1;
        }
        var_v0 = D_8007CBD4 & 0xFFBF;
        goto block_14;
    case 7:
    case 8:
    case 9:
        if (D_800C8566 == 3) {
            D_8007CBD4 |= 0x40;
            return 1;
        }
        var_v0 = D_8007CBD4 & 0xFFBF;
        goto block_14;
    case 10:
    case 11:
    case 12:
        if (D_800C8566 == 2) {
            D_8007CBD4 |= 0x40;
            return 1;
        }
        var_v0 = D_8007CBD4 & 0xFFBF;
        goto block_14;
    }
}
