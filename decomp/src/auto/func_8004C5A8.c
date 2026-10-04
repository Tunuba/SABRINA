#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C8538[];
extern s16 D_800C8578;
extern u8 D_800C8616[];
extern s8 nivel_actual;
extern s8 D_8007CB28;


void func_8004C5A8(s32 arg0) {
    s16 *temp_v1;

    *(arg0 + (D_800C8616 + (nivel_actual * 0x141))) = 1;
    temp_v1 = D_800C8538 + (nivel_actual * 2);
    *temp_v1 += 1;
    D_800C8578 = *temp_v1;
    D_8007CB28 = func_8004C3A0();
    TocarSonido(0x1B, 0, 0x2A, 0x7F);
}
