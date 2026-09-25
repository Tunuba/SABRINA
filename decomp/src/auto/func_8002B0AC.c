#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 * D_8006D2B0;
extern s8 * D_8006D2B8;
extern u8 * D_8006D2BC;
extern s32 * D_8006D2C0;
extern u8 D_8006D2C8[];


void func_8002B0AC(void) {
    *D_8006D2B0 = 1;
    if (*D_8006D2BC & 7) {
        do {
            *D_8006D2B0 = 1;
            *D_8006D2BC = 7;
            *D_8006D2B8 = 7;
        } while (*D_8006D2BC & 7);
    }
    M2C_FIELD(D_8006D2C8, u8 *, 2) = 0U;
    M2C_FIELD(D_8006D2C8, u8 *, 1) = (u8) M2C_FIELD(D_8006D2C8, u8 *, 2);
    M2C_FIELD(D_8006D2C8, u8 *, 0) = 2;
    *D_8006D2B0 = 0;
    *D_8006D2BC = 0;
    *D_8006D2C0 = 0x1325;
}
