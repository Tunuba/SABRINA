#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C86C6[];
extern s8 D_8007C7AC;
extern u16 D_8007C8D8[];
extern s16 jugando;
extern s8 nivel_actual;
extern s8 D_8007CA01;
extern s8 D_8007CA38;
extern s32 D_8007CB34;
extern u16 D_8007CC00;
extern s32 D_8007CC04;


void func_80046ED8(void) {
    s8 temp_v1;

    temp_v1 = D_8007C8D8[D_8007CC00] + 2;
    if (*(D_800C86C6 + (temp_v1 * 0x141)) != 0) {
        jugando = 0;
        D_8007CA01 = nivel_actual;
        nivel_actual = temp_v1;
        D_8007CA38 = 0;
        D_8007CB34 = 0;
    } else {
        TocarSonido(0x30, 0, 0x2A, 0x7F);
        D_8007C7AC = 0;
    }
    D_8007CC04 = 0;
}
