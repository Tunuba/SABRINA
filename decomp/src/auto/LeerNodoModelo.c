#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80068830[];
extern u8 D_8007C7D8[];


void LeerNodoModelo(s32 arg0, s32 arg1, s32 arg2) {
    s16 sp2C;
    s16 sp2E;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;

loop_1:
    ArchivoLeer(arg0, (s32) &sp2E, 2);
    if (sp2E < 0) {

    } else {
        temp_v0 = func_8001E164(arg1);
        Afirmar(temp_v0);
        M2C_FIELD(temp_v0, s16 *, 0x5C) = sp2E;
        ArchivoLeer(arg0, temp_v0 + 0x5E, 2);
        ArchivoLeer(arg0, (s32) &sp2C, 2);
        ArchivoLeer(arg0, temp_v0 + 0x14, 0x20);
        ArchivoLeer(arg0, (s32) &sp2E, 2);
        if (sp2E != 0) {
            temp_v0_2 = Reservar(sp2E + 1, (s32) "modelLoader.c");
            ArchivoLeer(arg0, temp_v0_2, (s32) sp2E);
            *(temp_v0_2 + sp2E) = 0;
            func_8001E2DC(temp_v0, temp_v0_2);
            Liberar(temp_v0_2);
        } else {
            printf((s32) "EMPTY!\n");
        }
loop_7:
        sp2C -= 1;
        if (sp2C != 0) {
            LeerNodoModelo(arg0, temp_v0, 0);
            goto loop_7;
        }
        M2C_FIELD(temp_v0, s32 *, 0x58) = Reservar(M2C_FIELD(temp_v0, s16 *, 0x5E) * 0x1C, (s32) "modelLoader.c");
        Afirmar(M2C_FIELD(temp_v0, s32 *, 0x58));
        ArchivoLeer(arg0, M2C_FIELD(temp_v0, s32 *, 0x58), M2C_FIELD(temp_v0, s16 *, 0x5E) * 0x1C);
        M2C_FIELD(temp_v0, s32 *, 0x54) = Reservar(M2C_FIELD(temp_v0, s16 *, 0x5C) * 0xC, (s32) "modelLoader.c");
        Afirmar(M2C_FIELD(temp_v0, s32 *, 0x54));
        ArchivoLeer(arg0, M2C_FIELD(temp_v0, s32 *, 0x54), M2C_FIELD(temp_v0, s16 *, 0x5C) * 0xC);
        var_s0 = M2C_FIELD(temp_v0, s32 *, 0x58);
        sp2E = 0;
loop_10:
        if (sp2E < M2C_FIELD(temp_v0, s16 *, 0x5E)) {
            M2C_FIELD(var_s0, s32 *, 0) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x54) + (M2C_FIELD(var_s0, s32 *, 0) * 0xC));
            M2C_FIELD(var_s0, s32 *, 4) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x54) + (M2C_FIELD(var_s0, s32 *, 4) * 0xC));
            M2C_FIELD(var_s0, s32 *, 8) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x54) + (M2C_FIELD(var_s0, s32 *, 8) * 0xC));
            M2C_FIELD(var_s0, s32 *, 0xC) = TexturaPorIndice(M2C_FIELD(var_s0, s32 *, 0xC));
            M2C_FIELD(var_s0, u8 *, 0x10) = (u8) (M2C_FIELD(var_s0, u8 *, 0x10) + M2C_FIELD(M2C_FIELD(var_s0, s32 *, 0xC), u8 *, 0x10));
            M2C_FIELD(var_s0, u8 *, 0x11) = (u8) (M2C_FIELD(var_s0, u8 *, 0x11) + M2C_FIELD(M2C_FIELD(var_s0, s32 *, 0xC), u8 *, 0x11));
            M2C_FIELD(var_s0, u8 *, 0x12) = (u8) (M2C_FIELD(var_s0, u8 *, 0x12) + M2C_FIELD(M2C_FIELD(var_s0, s32 *, 0xC), u8 *, 0x10));
            M2C_FIELD(var_s0, u8 *, 0x13) = (u8) (M2C_FIELD(var_s0, u8 *, 0x13) + M2C_FIELD(M2C_FIELD(var_s0, s32 *, 0xC), u8 *, 0x11));
            M2C_FIELD(var_s0, u8 *, 0x14) = (u8) (M2C_FIELD(var_s0, u8 *, 0x14) + M2C_FIELD(M2C_FIELD(var_s0, s32 *, 0xC), u8 *, 0x10));
            M2C_FIELD(var_s0, u8 *, 0x15) = (u8) (M2C_FIELD(var_s0, u8 *, 0x15) + M2C_FIELD(M2C_FIELD(var_s0, s32 *, 0xC), u8 *, 0x11));
            var_s0 += 0x1C;
            sp2E += 1;
            goto loop_10;
        }
        M2C_FIELD(temp_v0, u8 *, 0x64) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x64) | 8);
        if (arg2 != 0) {
            goto loop_1;
        }
    }
}
