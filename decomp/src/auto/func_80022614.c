#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8008AF60[];
extern u8 D_8008AF74[];
extern u8 D_8006C478[];
extern u8 D_8007CB10;


void func_80022614(s32 arg0) {
    s16 temp_v0;
    s32 *temp_a0;
    s32 var_t9;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a0_4;
    void *temp_a0_5;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v1;

    *(D_8008AF60 + (D_8007CB10 * 4)) = Reservar(0x1388, (s32) "TexAnima.c");
    temp_a0 = D_8008AF74 + (D_8007CB10 * 4);
    *temp_a0 = Reservar(0x18, (s32) "TexAnima.c");
    **temp_a0 = (u16) M2C_FIELD(arg0, u16 *, 0x12);
    M2C_FIELD(*(D_8008AF74 + (D_8007CB10 * 4)), u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 0x14);
    temp_v0 = M2C_FIELD(arg0, s16 *, 8);
    var_t9 = temp_v0 >> 2;
    if (temp_v0 < 0) {
        var_t9 = (s32) (temp_v0 + 3) >> 2;
    }
    M2C_FIELD(*(D_8008AF74 + (D_8007CB10 * 4)), s8 *, 4) = (s8) var_t9;
    M2C_FIELD(*(D_8008AF74 + (D_8007CB10 * 4)), s8 *, 5) = (s8) M2C_FIELD(arg0, s16 *, 0xA);
    temp_a0_2 = *(D_8008AF74 + (D_8007CB10 * 4));
    M2C_FIELD(temp_a0_2, u16 *, 0xC) = (u16) M2C_FIELD(temp_a0_2, u16 *, 0);
    temp_a0_3 = *(D_8008AF74 + (D_8007CB10 * 4));
    M2C_FIELD(temp_a0_3, u16 *, 0xE) = (u16) M2C_FIELD(temp_a0_3, u16 *, 2);
    temp_a0_4 = *(D_8008AF74 + (D_8007CB10 * 4));
    M2C_FIELD(temp_a0_4, s16 *, 0x10) = (s16) M2C_FIELD(temp_a0_4, u8 *, 4);
    temp_a0_5 = *(D_8008AF74 + (D_8007CB10 * 4));
    M2C_FIELD(temp_a0_5, s16 *, 0x12) = (s16) M2C_FIELD(temp_a0_5, u8 *, 5);
    temp_v0_2 = *(D_8008AF74 + (D_8007CB10 * 4));
    M2C_FIELD(*(D_8008AF74 + (D_8007CB10 * 4)), s32 *, 8) = Reservar(M2C_FIELD(temp_v0_2, u8 *, 4) * (M2C_FIELD(temp_v0_2, u8 *, 5) + 6) * 4, (s32) "TexAnima.c");
    temp_v0_3 = *(D_8008AF74 + (D_8007CB10 * 4));
    func_80012ECC((s32) (temp_v0_3 + 0xC), M2C_FIELD(temp_v0_3, s32 *, 8));
    func_80012D74(0);
    M2C_FIELD(*(D_8008AF74 + (D_8007CB10 * 4)), s16 *, 0x12) = 6;
    temp_v0_4 = *(D_8008AF74 + (D_8007CB10 * 4));
    func_80012ECC((s32) (temp_v0_4 + 0xC), M2C_FIELD(temp_v0_4, s32 *, 8) + 0x480);
    func_80012D74(0);
    temp_v1 = *(D_8008AF74 + (D_8007CB10 * 4));
    M2C_FIELD(temp_v1, s16 *, 0x12) = (s16) M2C_FIELD(temp_v1, u8 *, 5);
    M2C_FIELD(*(D_8008AF74 + (D_8007CB10 * 4)), s8 *, 0x14) = 0;
    M2C_FIELD(*(D_8008AF74 + (D_8007CB10 * 4)), s8 *, 0x15) = 0;
    M2C_FIELD(*(D_8008AF74 + (D_8007CB10 * 4)), s8 *, 0x16) = 0;
    D_8007CB10 += 1;
}
