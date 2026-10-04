#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];
extern u8 D_800D5890[];
extern u8 D_800D5894[];
extern s32 D_8007CC5C;


void func_80052784(void *arg0) {
    s32 temp_a0;
    void *temp_v1;

    temp_v1 = arg0 + 0x74;
    M2C_FIELD(temp_v1, s8 *, 0x24) = 1;
    M2C_FIELD(arg0, s32 *, 0x74) = (s32) (D_800D588C + (M2C_FIELD(arg0, s32 *, 0x74) * 0x18));
    M2C_FIELD(temp_v1, s32 *, 0xC) = (s32) *(D_800D588C + (M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s16 *, 0xE) * 0x18));
    M2C_FIELD(temp_v1, s32 *, 0x10) = (s32) *(D_800D5890 + (M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s16 *, 0xE) * 0x18));
    M2C_FIELD(temp_v1, s32 *, 0x14) = (s32) *(D_800D5894 + (M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s16 *, 0xE) * 0x18));
    M2C_FIELD(temp_v1, s32 *, 0x18) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 0);
    M2C_FIELD(temp_v1, s32 *, 0x1C) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 4);
    M2C_FIELD(temp_v1, s32 *, 0x20) = (s32) M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s32 *, 8);
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
    temp_a0 = (s32) M2C_FIELD(temp_v1, s32 *, 8) >> 8;
    M2C_FIELD(temp_v1, s32 *, 8) = (s32) (((s32) (temp_a0 * temp_a0) >> 8) << 8);
    D_8007CC5C = 1;
}
