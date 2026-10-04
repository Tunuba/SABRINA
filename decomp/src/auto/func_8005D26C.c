#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8008143C;
extern s16 D_800D5818;
extern u8 D_800D5830[];
extern u8 D_800D5834[];
extern s16 D_800D5840;
extern s16 D_800D5844;
extern s16 D_800D584A;
extern s16 D_800D584C;
extern s16 D_800D5850;

void func_8005D26C(void) {
    s32 temp_a0;

    if ((D_800D5818 != 0) && (D_8008143C != 0)) {
        func_8002D714();
        D_8008143C = 0;
    }
    SubirAVRAM((s32) &D_800D5840, M2C_FIELD((&D_800D5818 + (D_800D5850 * 4)), s32 *, 0x44));
    D_800D5850 ^= 1;
    D_800D5840 += D_800D5844;
    temp_a0 = D_800D584C * 8;
    if (D_800D5840 < (*(D_800D5830 + temp_a0) + *(D_800D5834 + temp_a0))) {
        func_8005DD50(M2C_FIELD((&D_800D5818 + (D_800D5850 * 4)), s32 *, 0x44), func_8005D0F4());
        return;
    }
    D_800D584A = 1;
}
