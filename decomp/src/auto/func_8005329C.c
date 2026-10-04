#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8005329C(void *arg0) {
    s16 temp_v0;
    s32 temp_s2;
    void *temp_a0;
    void *temp_s1;
    void *temp_v1;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    temp_s1 = arg0 + 0x74;
    switch (temp_v0) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (M2C_FIELD(arg0, s32 *, 0x3C) - 0xE6);
        temp_a0 = M2C_FIELD(arg0, void **, 0x74);
        M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) (M2C_FIELD(temp_a0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
        temp_s2 = func_80021CE4(0x800) - 0x400;
        M2C_FIELD(CrearParticula((s32) (s8) M2C_FIELD(temp_s1, s32 *, 8), (s32) M2C_FIELD(arg0, void **, 0x74), 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ temp_s2, /* extra? */ 0, /* extra? */ (func_80021CE4(0x800) - 0x400), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x37, /* extra? */ 0x202, /* extra? */ 0), s32 *, 0x3C) = 0xB4;
        M2C_FIELD(temp_s1, s32 *, 4) = (s32) (M2C_FIELD(temp_s1, s32 *, 4) - 1);
        if (M2C_FIELD(temp_s1, s32 *, 4) < 0) {
            M2C_FIELD(arg0, s16 *, 0x70) = 1;
            return;
        }
        return;
    case 1:
        temp_v1 = M2C_FIELD(arg0, void **, 0x74);
        M2C_FIELD(temp_v1, u8 *, 0x20) = (u8) (M2C_FIELD(temp_v1, u8 *, 0x20) | 0x80);
        M2C_FIELD(arg0, s16 *, 0x70) = 2;
        return;
    case 2:
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
        break;
    }
}
