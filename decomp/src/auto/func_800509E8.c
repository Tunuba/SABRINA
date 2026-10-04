#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D52C0[];
extern u8 D_800621BC[];
extern s32 func_8004FD34();
extern s32 open();


void func_800509E8(s32 arg0) {
    if (M2C_FIELD(D_800D52C0, s32 *, 0) <= 0) {
        M2C_FIELD(D_800D52C0, s32 *, 0) = 1;
        M2C_FIELD(D_800D52C0, s32 *, 4) = 0;
        M2C_FIELD(D_800D52C0, s32 *, 8) = 0;
        M2C_FIELD(D_800D52C0, s32 *, 0x10) = arg0;
        UserFuncOpen((s32) func_8004FD34);
        return;
    }
    printf((s32) "Access Denied. : event multiple open\n", arg0);
}
