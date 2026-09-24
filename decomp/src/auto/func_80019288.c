#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007C7A0;
extern u16 D_8007C7A2;
extern u16 D_8007C7A4;
extern u16 D_8007C7A6;
extern u8 D_8007C7A8[];


void func_80019288(void) {
    D_8007C7A0 += D_8007C7A6;
    D_8007C7A2 += M2C_FIELD(D_8007C7A8, u16 *, 0);
    D_8007C7A4 += M2C_FIELD(D_8007C7A8, u16 *, 2);
    if ((u16) D_8007C7A0 >= 0x100U) {
        D_8007C7A6 = (u16) -(s32) D_8007C7A6;
        if ((u16) D_8007C7A0 >= 0x8001U) {
            D_8007C7A0 = 0;
        } else {
            D_8007C7A0 = 0xFF;
        }
    }
    if ((u16) D_8007C7A2 >= 0x100U) {
        M2C_FIELD(D_8007C7A8, u16 *, 0) = (u16) -(s32) M2C_FIELD(D_8007C7A8, u16 *, 0);
        if ((u16) D_8007C7A2 >= 0x8001U) {
            D_8007C7A2 = 0;
        } else {
            D_8007C7A2 = 0xFF;
        }
    }
    if ((u16) D_8007C7A4 >= 0x100U) {
        M2C_FIELD(D_8007C7A8, u16 *, 2) = (u16) -(s32) M2C_FIELD(D_8007C7A8, u16 *, 2);
        if ((u16) D_8007C7A4 >= 0x8001U) {
            D_8007C7A4 = 0;
            return;
        }
        D_8007C7A4 = 0xFF;
    }
}
