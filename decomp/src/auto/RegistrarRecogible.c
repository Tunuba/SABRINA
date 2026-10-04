#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C7960[];
extern u8 D_800C796C[];
extern u8 D_800C7978[];
extern u8 D_800C7984[];
extern u8 D_800C7986[];
extern u8 D_800C7988[];
extern u8 D_800C798A[];
extern u8 D_800C798C[];
extern u8 D_800C7994[];
extern u8 recogidos[];
extern s32 D_8007CC0C;


void RegistrarRecogible(void *arg0) {
    s32 *var_v1;
    s32 temp_a1;
    s32 var_v0;
    u16 temp_v0;
    void *temp_a3;
    void *temp_a3_2;
    void *temp_a3_3;
    void *temp_v1;

    temp_a1 = D_8007CC0C * 0x38;
    temp_a3 = D_800C7960 + temp_a1;
    M2C_FIELD(temp_a3, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
    M2C_FIELD(temp_a3, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(temp_a3, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
    temp_a3_2 = D_800C796C + temp_a1;
    M2C_FIELD(temp_a3_2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x38);
    M2C_FIELD(temp_a3_2, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x3C);
    M2C_FIELD(temp_a3_2, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x40);
    temp_a3_3 = D_800C7978 + temp_a1;
    M2C_FIELD(temp_a3_3, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
    M2C_FIELD(temp_a3_3, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x58);
    M2C_FIELD(temp_a3_3, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x5C);
    *(D_800C7988 + temp_a1) = M2C_FIELD(arg0, s16 *, 0x32);
    *(D_800C7984 + temp_a1) = (s16) M2C_FIELD(arg0, s32 *, 0x74);
    *(D_800C7986 + temp_a1) = (s16) M2C_FIELD((arg0 + 0x74), s8 *, 4);
    *(D_800C798A + temp_a1) = M2C_FIELD(arg0, s16 *, 0x70);
    *(D_800C798C + temp_a1) = M2C_FIELD(arg0, s32 *, 0x28);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x22);
    switch (temp_v0) {                              /* irregular */
    case 4:
        var_v0 = CrearParticula(0x15, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x3E80, /* extra? */ 0, /* extra? */ 0);
        var_v1 = D_800C7994 + (D_8007CC0C * 0x38);
block_8:
        *var_v1 = var_v0;
        break;
    case 18:
        var_v0 = CrearParticula(0x16, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x3E80, /* extra? */ 0, /* extra? */ 0);
        var_v1 = D_800C7994 + (D_8007CC0C * 0x38);
        goto block_8;
    case 19:
        var_v0 = CrearParticula(0x17, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x3E80, /* extra? */ 0, /* extra? */ 0);
        var_v1 = D_800C7994 + (D_8007CC0C * 0x38);
        goto block_8;
    case 23:
        var_v0 = CrearParticula(0x18, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x3E80, /* extra? */ 0, /* extra? */ 0);
        var_v1 = D_800C7994 + (D_8007CC0C * 0x38);
        goto block_8;
    }
    M2C_FIELD(*(D_800C7994 + (D_8007CC0C * 0x38)), s32 *, 0x24) = 0x8000;
    M2C_FIELD(*(D_800C7994 + (D_8007CC0C * 0x38)), s16 *, 0x40) = 0x64;
    temp_v1 = *(D_800C7994 + (D_8007CC0C * 0x38));
    M2C_FIELD(temp_v1, u16 *, 0x42) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x42) | 0x800);
    *(recogidos + (D_8007CC0C * 0x38)) = M2C_FIELD(arg0, s32 *, 0x6C);
    D_8007CC0C += 1;
}
