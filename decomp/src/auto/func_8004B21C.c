#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C8567[];
extern s8 D_8007C890;
extern s8 D_8007C891;
extern s8 D_8007C892;


void func_8004B21C(s32 arg0) {
    s32 var_a1;

    var_a1 = 0;
    switch (arg0) {
    case 1:
        var_a1 = 1;
        break;
    case 2:
        var_a1 = 1;
        break;
    case 3:
        var_a1 = 1;
        break;
    case 4:
        var_a1 = 4;
        break;
    case 5:
        var_a1 = 4;
        break;
    case 6:
        var_a1 = 4;
        break;
    case 7:
        var_a1 = 7;
        break;
    case 8:
        var_a1 = 7;
        break;
    case 9:
        var_a1 = 7;
        break;
    case 10:
        var_a1 = 0xA;
        break;
    case 11:
        var_a1 = 0xA;
        break;
    case 12:
        var_a1 = 0xA;
        break;
    }
    if (var_a1 != 0) {
        D_8007C890 = M2C_FIELD(&D_800C8567[var_a1], s8 *, -1);
        D_8007C891 = (s8) M2C_FIELD(&D_800C8567[var_a1], u8 *, 0);
        D_8007C892 = M2C_FIELD(&D_800C8567[var_a1], s8 *, 1);
        return;
    }
    D_8007C890 = 0;
    D_8007C891 = 0;
    D_8007C892 = 0;
}
