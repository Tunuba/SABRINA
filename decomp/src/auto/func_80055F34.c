#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CC70;


void func_80055F34(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x74) = arg1;
    switch (arg1) {                                 /* irregular */
    case 2:
        func_800249CC((s32) arg0, 0x18);
        break;
    case 1:
        func_800249CC((s32) arg0, 0x16);
        break;
    case 3:
        func_800249CC((s32) arg0, 0x19);
        break;
    case 4:
        func_800249CC((s32) arg0, 0x17);
        break;
    }
    D_8007CC70 = 1;
}
