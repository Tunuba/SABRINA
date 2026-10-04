#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C8566;
extern s8 nivel_actual;
extern u16 D_8007CBD4;

void func_80055E04(s32 arg0) {
    void *temp_a0;

    temp_a0 = arg0 + 0x74;
    switch (nivel_actual) {
    case 1:
    case 2:
    case 3:
        if (D_800C8566 == 2) {
            D_8007CBD4 |= 0x40;
            M2C_FIELD(temp_a0, s8 *, 0x20) = 1;
            return;
        }
    default:
        return;
    case 4:
    case 5:
    case 6:
        if (D_800C8566 == 1) {
            D_8007CBD4 |= 0x40;
            M2C_FIELD(temp_a0, s8 *, 0x20) = 1;
            return;
        }
        break;
    case 7:
    case 8:
    case 9:
        if (D_800C8566 == 4) {
            D_8007CBD4 |= 0x40;
            M2C_FIELD(temp_a0, s8 *, 0x20) = 1;
            return;
        }
        break;
    case 10:
    case 11:
    case 12:
        if (D_800C8566 == 3) {
            D_8007CBD4 |= 0x40;
            M2C_FIELD(temp_a0, s8 *, 0x20) = 1;
        }
        break;
    }
}
