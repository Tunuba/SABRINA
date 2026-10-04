#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006886C[];
extern u8 D_8007C4E4[];
extern u8 D_8007C558[];
extern u8 D_8007C5CC[];
extern u8 D_8007C644[];
extern u8 D_8007C6BC[];
extern s8 nivel_actual;

u8 D_8007C6BC[0x44];                                /* unable to generate initializer: cannot parse D_8007C4E4 as integer */

void func_8001F524(s32 arg0) {
    u32 sp20;
    s32 sp24;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;
    s32 var_s1;
    s32 var_v1;
    u32 temp_v0_2;

    sp20 = 0;
    temp_s1 = *(D_8007C6BC + (nivel_actual * 4));
    var_v1 = 0;
loop_2:
    if (*(temp_s1 + var_v1) != 0) {
        var_v1 += 4;
        sp20 += 1;
        goto loop_2;
    }
    temp_s0 = Reservar((sp20 + 1) * 4, (s32) D_8006886C);
    sp20 = 0;
    do {
        temp_v0 = *(temp_s1 + (sp20 * 4));
        if (temp_v0 != 0) {
            *(temp_s0 + (sp20 * 4)) = func_8001B698(temp_v0);
        }
        temp_v0_2 = sp20 + 1;
        sp20 = temp_v0_2;
        if (temp_v0_2 >= 0x32U) {
            Afirmar(0);
        }
    } while (*(temp_s1 + (sp20 * 4)) != 0);
    func_80029530(arg0, (s32) &sp20);
    var_s1 = 0;
    sp24 = 0;
loop_11:
    if (var_s1 != sp20) {
        func_80029530(arg0, *(temp_s0 + sp24));
        Liberar(*(temp_s0 + sp24));
        var_s1 += 1;
        sp24 += 4;
        goto loop_11;
    }
    Liberar(temp_s0);
}
