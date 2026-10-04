#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80068830[];


void func_8001CB4C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_UNK sp28;
    s16 sp48;
    s16 sp4A;
    s16 sp4C;
    s16 sp4E;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a0;

loop_1:
    ArchivoLeer(arg0, (s32) &sp4C, 2);
    func_80029530(arg2, (s32) &sp4C);
    if (sp4C >= 0) {
        ArchivoLeer(arg0, (s32) &sp4A, 2);
        func_80029530(arg2, (s32) &sp4A);
        ArchivoLeer(arg0, (s32) &sp48, 2);
        func_80029530(arg2, (s32) &sp48);
        ArchivoLeer(arg0, (s32) &sp28, 0x20);
        func_80029530(arg2, (s32) &sp28);
        ArchivoLeer(arg0, (s32) &sp4E, 2);
        func_80029530(arg2, (s32) &sp4E);
        if (sp4E != 0) {
            temp_v0 = Reservar(sp4E + 1, (s32) D_80068830);
            ArchivoLeer(arg0, temp_v0, (s32) sp4E);
            func_80029530(arg2, temp_v0);
            Liberar(temp_v0);
        }
loop_5:
        sp48 -= 1;
        if (sp48 != 0) {
            func_8001CB4C(arg0, 0, arg2, arg3);
            goto loop_5;
        }
        temp_v0_2 = Reservar(sp4A * 0x1C, (s32) D_80068830);
        Afirmar(temp_v0_2);
        ArchivoLeer(arg0, temp_v0_2, sp4A * 0x1C);
        var_a0 = temp_v0_2;
        sp4E = 0;
loop_8:
        if (sp4E < sp4A) {
            M2C_FIELD(var_a0, s32 *, 0xC) = (s32) (((M2C_FIELD(var_a0, s32 *, 0xC) & 0xFF) + (arg3 & 0xFF)) & 0xFF);
            var_a0 += 0x1C;
            sp4E += 1;
            goto loop_8;
        }
        func_80029530(arg2, temp_v0_2);
        Liberar(temp_v0_2);
        temp_v0_3 = Reservar(sp4C * 0xC, (s32) D_80068830);
        Afirmar(temp_v0_3);
        ArchivoLeer(arg0, temp_v0_3, sp4C * 0xC);
        func_80029530(arg2, temp_v0_3);
        Liberar(temp_v0_3);
        if (arg1 != 0) {
            goto loop_1;
        }
    }
}
