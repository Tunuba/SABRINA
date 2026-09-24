#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 jugando[];
extern void * D_8007CAD4;
extern u8 D_8007CAE6[];
extern u8 D_8007CAE8;
extern u16 D_8007CAEA;
extern u16 D_8007CAEC;
extern u16 D_8007CAEE;
extern s16 D_8007CC48;


void func_800211D4(void) {
    M2C_FIELD(D_8007CAE6, u8 *, 0) += 1;
    D_8007CC48 += 1;
    if (M2C_FIELD(jugando, u16 *, 2) != 0) {
        if ((s32) D_8007CAE6[1] < (D_8007CAE8 * 0x1E)) {
            D_8007CAE6[1] += 1;
        }
        if ((u8) D_8007CAE6[1] >= 0xD2U) {
            M2C_FIELD(jugando, u16 *, 2) = 0U;
        }
        M2C_FIELD(D_8007CAD4, s8 *, 4) = (s8) D_8007CAEA;
        M2C_FIELD(D_8007CAD4, s8 *, 5) = (s8) D_8007CAEC;
        M2C_FIELD(D_8007CAD4, s8 *, 6) = (s8) D_8007CAEE;
        M2C_FIELD(D_8007CAD4, s16 *, 8) = 0x97;
        M2C_FIELD(D_8007CAD4, s16 *, 0xA) = 0xB0;
        M2C_FIELD(D_8007CAD4, s16 *, 0xC) = (s16) D_8007CAE6[1];
        M2C_FIELD(D_8007CAD4, s16 *, 0xE) = 0xF;
        func_80013090((s32) D_8007CAD4);
        return;
    }
    D_8007CAE8 = 0;
    D_8007CAE6[1] = 0;
}
