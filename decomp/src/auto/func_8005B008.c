#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C857E;
extern s8 D_800C857F;
extern s8 D_800C8580;
extern s8 D_800C8581;
extern s8 nivel_actual;


void func_8005B008(s32 arg0) {
    u8 var_v0;

    func_8004C22C();
    switch (nivel_actual) {                         /* irregular */
    case 4:
        func_800249CC(arg0, 0x30);
        M2C_FIELD(arg0, s32 *, 0x74) = 1;
        if (D_800C857E != 0) {
            var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
block_12:
            M2C_FIELD(arg0, u8 *, 0x20) = var_v0;
        }
        break;
    case 7:
        func_800249CC(arg0, 0x31);
        M2C_FIELD(arg0, s32 *, 0x74) = 0xA;
        if (D_800C8581 != 0) {
            var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
            goto block_12;
        }
        break;
    case 8:
        func_800249CC(arg0, 0x32);
        M2C_FIELD(arg0, s32 *, 0x74) = 4;
        if (D_800C857F != 0) {
            var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
            goto block_12;
        }
        break;
    case 10:
        func_800249CC(arg0, 0x31);
        M2C_FIELD(arg0, s32 *, 0x74) = 7;
        if (D_800C8580 != 0) {
            var_v0 = M2C_FIELD(arg0, u8 *, 0x20) | 0x80;
            goto block_12;
        }
        break;
    }
    M2C_FIELD(arg0, s8 *, 0x118) = 0;
}
