#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8006CE30;
extern s16 D_8006CE32[];
extern s16 D_8006CE42[];
extern u8 D_8007C864[];
extern u8 D_8007CAE8;
extern s32 D_8007CB24;


void LeerSpritesINO(s32 arg0) {
    u16 sp1E;
    s16 temp_v0;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s32 var_t9;
    s32 var_t9_2;
    s32 var_t9_3;
    s32 var_t9_4;
    s32 var_t9_5;

    sp1E = 0;
    ArchivoLeer(arg0, (s32) &sp1E, 2);
    D_8007CB24 = Reservar(sp1E << 5, (s32) "UI.c");
    ArchivoLeer(arg0, D_8007CB24, sp1E << 5);
    temp_v1 = M2C_FIELD(D_8007CB24, s16 *, 8);
    var_t9 = temp_v1 >> 1;
    if (temp_v1 < 0) {
        var_t9 = (s32) (temp_v1 + 1) >> 1;
    }
    D_8006CE30 = 0x3C - var_t9;
    temp_v1_2 = M2C_FIELD(D_8007CB24, s16 *, 8);
    var_t9_2 = temp_v1_2 >> 1;
    if (temp_v1_2 < 0) {
        var_t9_2 = (s32) (temp_v1_2 + 1) >> 1;
    }
    temp_v1_3 = M2C_FIELD(D_8007CB24, s16 *, 0x128);
    var_t9_3 = temp_v1_3 >> 1;
    if (temp_v1_3 < 0) {
        var_t9_3 = (s32) (temp_v1_3 + 1) >> 1;
    }
    *D_8006CE32 = (D_8006CE30 + var_t9_2) - var_t9_3;
    temp_v1_4 = M2C_FIELD(D_8007CB24, s16 *, 0xA);
    var_t9_4 = temp_v1_4 >> 1;
    if (temp_v1_4 < 0) {
        var_t9_4 = (s32) (temp_v1_4 + 1) >> 1;
    }
    temp_v0 = M2C_FIELD(D_8007CB24, s16 *, 0x12A);
    var_t9_5 = temp_v0 >> 1;
    if (temp_v0 < 0) {
        var_t9_5 = (s32) (temp_v0 + 1) >> 1;
    }
    *D_8006CE42 = (var_t9_4 + 0xA5) - var_t9_5;
    D_8007CAE8 += 1;
}
