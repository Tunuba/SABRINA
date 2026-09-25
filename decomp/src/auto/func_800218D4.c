#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void * D_8007C9E8;
extern u16 D_8007C9EC;
extern u8 D_8007CAE6;
extern u8 D_8007CCBC[];
extern u8 D_8007CD74[];
extern u8 D_8007CD9C[];


void func_800218D4(void) {
    do {

    } while (func_80012D74(1) != 0);
    func_8001626C(0);
    do {

    } while ((u8) D_8007CAE6 < 2U);
    func_8001321C((s32) (D_8007CD74 + (D_8007C9EC * 0x14)));
    func_8001315C((s32) (D_8007CCBC + (D_8007C9EC * 0x5C)));
    func_800130EC((s32) (D_8007C9E8 + 0xFFC));
    D_8007C9EC += 1;
    D_8007C9EC &= 1;
    D_8007C9E8 = D_8007CD9C + (D_8007C9EC << 0xC);
    func_80012FE4((s32) D_8007C9E8, 0x400);
    D_8007CAE6 = 0;
    func_80010BD8(-1);
}
