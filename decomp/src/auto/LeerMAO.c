#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800B4C5C[];
extern u8 D_800B4C66[];
extern s32 D_8007CB5C;
extern void * D_8007CB60;
extern void * D_8007CB64;
extern void * D_8007CB68;


void LeerMAO(s32 arg0) {
    M2C_UNK sp20;
    u16 sp26;
    s32 temp_s2;
    u16 var_s1;

    ArchivoLeer(arg0, (s32) &sp20, 4);
    ArchivoLeer(arg0, (s32) &sp26, 2);
    var_s1 = sp26;
    M2C_FIELD(D_8007CB64, s8 *, 2) = (s8) sp26;
    ArchivoLeer(arg0, (s32) &sp26, 2);
    M2C_FIELD(D_8007CB64, s8 *, 3) = (s8) sp26;
    M2C_FIELD(D_8007CB64, u16 *, 0) = (u16) (((D_8007CB60 - D_800B4C5C) / 12) + ((u32) (D_8007CB60 - D_800B4C5C) >> 0x1F));
    D_8007CB68 = D_8007CB64;
    temp_s2 = sp26 * 3;
loop_2:
    if ((s32) var_s1 > 0) {
        M2C_FIELD(D_8007CB60, s32 *, 0) = (s32) D_8007CB5C;
        M2C_FIELD(D_8007CB60, s16 *, 0xA) = 0;
        ArchivoLeer(arg0, (s32) (D_8007CB60 + 4), 2);
        ArchivoLeer(arg0, (s32) (D_8007CB60 + 6), 2);
        ArchivoLeer(arg0, (s32) (D_8007CB60 + 8), 2);
        ArchivoLeer(arg0, D_8007CB5C, temp_s2);
        var_s1 -= 1;
        D_8007CB5C += temp_s2;
        D_8007CB60 += 0xC;
        goto loop_2;
    }
    D_8007CB60 -= 0xC;
    M2C_FIELD(D_8007CB60, s16 *, 0xA) = 2;
    D_8007CB60 += 0xC;
    *(D_800B4C66 + (M2C_FIELD(D_8007CB64, u16 *, 0) * 0xC)) = 1;
    D_8007CB64 += 4;
}
