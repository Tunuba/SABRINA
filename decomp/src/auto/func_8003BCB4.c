#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006C454;
extern s32 D_8006C458;
extern void * D_8007CAFC;


void func_8003BCB4(void *arg0) {
    s32 sp24;
    s32 sp28;
    s32 sp2C;

    if ((D_8007CAFC != NULL) && (M2C_FIELD(D_8007CAFC, s16 *, 0x70) == 0)) {
        sp24 = M2C_FIELD(D_8007CAFC, s32 *, 0x24) - M2C_FIELD(arg0, s32 *, 0x24);
        sp28 = M2C_FIELD(D_8007CAFC, s32 *, 0x28) - M2C_FIELD(arg0, s32 *, 0x28);
        sp2C = M2C_FIELD(D_8007CAFC, s32 *, 0x2C) - M2C_FIELD(arg0, s32 *, 0x2C);
        if (func_8001BF8C(0, 0, sp24, sp2C) < 0x20000) {
            func_8001C45C((s32) &sp24);
            if (func_8001C2D0(sp24, sp28, sp2C, subroutine_arg3, /* extra? */ D_8006C454, /* extra? */ D_8006C458) >= 0xBB9) {
                M2C_FIELD(D_8007CAFC, s16 *, 0x70) = 1;
                M2C_FIELD(D_8007CAFC, s32 *, 0x74) = (s32) M2C_FIELD(arg0, s32 *, 0x74);
                M2C_FIELD((D_8007CAFC + 0x74), s8 *, 0x24) = (s8) M2C_FIELD((arg0 + 0x74), s8 *, 4);
            }
        }
    }
}
