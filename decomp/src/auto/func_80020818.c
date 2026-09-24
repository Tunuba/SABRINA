#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800688C4[];


void func_80020818(s32 arg0, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 0x1:
        M2C_FIELD(arg0, s8 *, 1) = (s8) (M2C_FIELD(arg0, s8 *, 1) + 1);
        return;
    case 0x2:
        M2C_FIELD(arg0, s8 *, 2) = (s8) (M2C_FIELD(arg0, s8 *, 2) + 1);
        return;
    case 0x4:
        M2C_FIELD(arg0, s8 *, 3) = (s8) (M2C_FIELD(arg0, s8 *, 3) + 1);
        return;
    case 0x8:
        M2C_FIELD(arg0, s8 *, 4) = (s8) (M2C_FIELD(arg0, s8 *, 4) + 1);
        return;
    case 0x10:
        M2C_FIELD(arg0, s8 *, 5) = (s8) (M2C_FIELD(arg0, s8 *, 5) + 1);
        return;
    case 0x20:
        M2C_FIELD(arg0, s8 *, 6) = (s8) (M2C_FIELD(arg0, s8 *, 6) + 1);
        return;
    case 0x40:
        M2C_FIELD(arg0, s8 *, 7) = (s8) (M2C_FIELD(arg0, s8 *, 7) + 1);
        return;
    case 0x80:
        M2C_FIELD(arg0, s8 *, 8) = (s8) (M2C_FIELD(arg0, s8 *, 8) + 1);
        return;
    case 0x100:
        M2C_FIELD(arg0, s8 *, 9) = (s8) (M2C_FIELD(arg0, s8 *, 9) + 1);
        return;
    case 0x200:
        M2C_FIELD(arg0, s8 *, 0xA) = (s8) (M2C_FIELD(arg0, s8 *, 0xA) + 1);
        return;
    case 0x400:
        M2C_FIELD(arg0, s8 *, 0xB) = (s8) (M2C_FIELD(arg0, s8 *, 0xB) + 1);
        return;
    case 0x800:
        M2C_FIELD(arg0, s8 *, 0xC) = (s8) (M2C_FIELD(arg0, s8 *, 0xC) + 1);
        return;
    case 0x1000:
        M2C_FIELD(arg0, s8 *, 0xD) = (s8) (M2C_FIELD(arg0, s8 *, 0xD) + 1);
        return;
    case 0x2000:
        M2C_FIELD(arg0, s8 *, 0xE) = (s8) (M2C_FIELD(arg0, s8 *, 0xE) + 1);
        return;
    case 0x4000:
        M2C_FIELD(arg0, s8 *, 0xF) = (s8) (M2C_FIELD(arg0, s8 *, 0xF) + 1);
        return;
    case 0x8000:
        M2C_FIELD(arg0, s8 *, 0x10) = (s8) (M2C_FIELD(arg0, s8 *, 0x10) + 1);
        return;
    default:
        printf((s32) "\nValue unkown in taillie system\n");
        /* fallthrough */
        return;
    }
}
