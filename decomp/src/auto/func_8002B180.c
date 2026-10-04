#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 * D_8006D2B0;
extern s8 * D_8006D2B4;
extern u8 * D_8006D2B8;
extern u8 * D_8006D2BC;
extern void * D_8006D2C4;


s32 func_8002B180(void) {
    u8 sp0;
    u8 sp1;
    u8 sp2;
    u8 sp3;

    if (M2C_FIELD(D_8006D2C4, u16 *, 0x1B8) == 0) {
        if (M2C_FIELD(D_8006D2C4, u16 *, 0x1BA) == 0) {
            M2C_FIELD(D_8006D2C4, s16 *, 0x180) = 0x3FFF;
            M2C_FIELD(D_8006D2C4, s16 *, 0x182) = 0x3FFF;
        }
    }
    M2C_FIELD(D_8006D2C4, s16 *, 0x1B0) = 0x3FFF;
    M2C_FIELD(D_8006D2C4, s16 *, 0x1B2) = 0x3FFF;
    M2C_FIELD(D_8006D2C4, s16 *, 0x1AA) = 0xC001;
    sp2 = 0x80;
    sp0 = 0x80;
    sp3 = 0;
    sp1 = 0;
    *D_8006D2B0 = 2;
    *D_8006D2B8 = 0x80;
    *D_8006D2BC = sp1;
    *D_8006D2B0 = 3;
    *D_8006D2B4 = 0x80;
    *D_8006D2B8 = sp3;
    *D_8006D2BC = 0x20;
    return 0;
}
