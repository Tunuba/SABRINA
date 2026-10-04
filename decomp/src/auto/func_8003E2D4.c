#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800C6644;
extern u8 D_80061D10[];
extern u8 D_80061D20[];
extern s32 * D_80074E94;
extern u8 D_80074E9C[];
extern void * D_80074EBC;
extern s16 D_80074EC0;
extern s32 D_80074EC4;
extern s32 D_80074EC8;
extern s32 D_80074ECC;
extern s32 D_80074ED0;
extern s32 D_80074ED4;
extern s32 D_80074ED8;
extern s32 D_80074EDC;
extern s32 D_80074EE0;
extern s32 D_80074EE4;


void func_8003E2D4(s32 arg0) {
    s16 *var_a1;
    s32 var_a0;
    s32 var_a0_2;
    u32 var_v1;
    void *var_v1_2;

    *D_80074E94 |= 0xB0000;
    D_80074EC4 = 0;
    D_80074EC8 = 0;
    D_80074EC0 = 0;
    M2C_FIELD(D_80074EBC, s16 *, 0x180) = 0;
    M2C_FIELD(D_80074EBC, s16 *, 0x182) = 0;
    M2C_FIELD(D_80074EBC, s16 *, 0x1AA) = 0;
    func_8003EA90();
    M2C_FIELD(D_80074EBC, s16 *, 0x180) = 0;
    M2C_FIELD(D_80074EBC, s16 *, 0x182) = 0;
    if (M2C_FIELD(D_80074EBC, u16 *, 0x1AE) & 0x7FF) {
        var_v1 = 1;
loop_2:
        if (var_v1 >= 0xF01U) {
            printf((s32) "SPU:T/O [%s]\n", "wait (reset)");
            var_a0 = 0;
        } else {
            var_v1 += 1;
            if (!(M2C_FIELD(D_80074EBC, u16 *, 0x1AE) & 0x7FF)) {
                goto block_5;
            }
            goto loop_2;
        }
    } else {
block_5:
        var_a0 = 0;
    }
    var_a1 = &D_800C6644;
    D_80074ECC = 2;
    D_80074ED0 = 3;
    D_80074ED4 = 8;
    D_80074ED8 = 7;
    M2C_FIELD(D_80074EBC, s16 *, 0x1AC) = 4;
    M2C_FIELD(D_80074EBC, s16 *, 0x184) = 0;
    M2C_FIELD(D_80074EBC, s16 *, 0x186) = 0;
    M2C_FIELD(D_80074EBC, s16 *, 0x18C) = 0xFFFF;
    M2C_FIELD(D_80074EBC, s16 *, 0x18E) = 0xFFFF;
    M2C_FIELD(D_80074EBC, s16 *, 0x198) = 0;
    M2C_FIELD(D_80074EBC, s16 *, 0x19A) = 0;
    do {
        *var_a1 = 0;
        var_a0 += 1;
        var_a1 += 2;
    } while (var_a0 < 0xA);
    if (arg0 == 0) {
        D_80074EC0 = 0x200;
        M2C_FIELD(D_80074EBC, s16 *, 0x190) = 0;
        M2C_FIELD(D_80074EBC, s16 *, 0x192) = 0;
        M2C_FIELD(D_80074EBC, s16 *, 0x194) = 0;
        M2C_FIELD(D_80074EBC, s16 *, 0x196) = 0;
        M2C_FIELD(D_80074EBC, s16 *, 0x1B0) = 0;
        M2C_FIELD(D_80074EBC, s16 *, 0x1B2) = 0;
        M2C_FIELD(D_80074EBC, s16 *, 0x1B4) = 0;
        M2C_FIELD(D_80074EBC, s16 *, 0x1B6) = 0;
        func_8003E0C4((s32) D_80074E9C, 0x10);
        var_a0_2 = 0;
        var_v1_2 = D_80074EBC;
        do {
            M2C_FIELD(var_v1_2, s16 *, 0) = 0;
            M2C_FIELD(var_v1_2, s16 *, 2) = 0;
            M2C_FIELD(var_v1_2, s16 *, 4) = 0x3FFF;
            M2C_FIELD(var_v1_2, s16 *, 6) = 0x200;
            M2C_FIELD(var_v1_2, s16 *, 8) = 0;
            M2C_FIELD(var_v1_2, s16 *, 0xA) = 0;
            var_a0_2 += 1;
            var_v1_2 += 0x10;
        } while (var_a0_2 < 0x18);
        M2C_FIELD(D_80074EBC, s16 *, 0x188) = 0xFFFF;
        M2C_FIELD(D_80074EBC, s16 *, 0x18A) = 0xFF;
        func_8003EA90();
        func_8003EA90();
        func_8003EA90();
        func_8003EA90();
        M2C_FIELD(D_80074EBC, s16 *, 0x18C) = 0xFFFF;
        M2C_FIELD(D_80074EBC, s16 *, 0x18E) = 0xFF;
        func_8003EA90();
        func_8003EA90();
        func_8003EA90();
        func_8003EA90();
    }
    D_80074EDC = 1;
    M2C_FIELD(D_80074EBC, s16 *, 0x1AA) = 0xC000;
    D_80074EE0 = 0;
    D_80074EE4 = 0;
}
