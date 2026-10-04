#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8007A1D0[];
extern u8 D_8007A3F0[];
extern u8 D_8007C784[];


void func_800185A8(s32 arg0, s32 arg1) {
    M2C_UNK sp20;
    s32 temp_v0_2;
    void *temp_v0;

    sprintf((s32) &sp20, (s32) D_8007C784, D_8007A1D0, arg0);
    temp_v0 = func_80014FF0((s32) &sp20, 0x2E);
    M2C_FIELD(temp_v0, s8 *, 1) = 0x49;
    M2C_FIELD(temp_v0, s8 *, 2) = 0x4E;
    M2C_FIELD(temp_v0, s8 *, 3) = 0x4F;
    temp_v0_2 = func_800294F0((s32) &sp20);
    HerramientaArmarCuadricula(arg0, temp_v0_2);
    func_80024450(arg1, temp_v0_2);
    HerramientaArmarModelos(temp_v0_2, arg1);
    func_80018CB8((s32) D_8007A3F0, temp_v0_2);
    func_8001F524(temp_v0_2);
    func_80029518(temp_v0_2);
}
