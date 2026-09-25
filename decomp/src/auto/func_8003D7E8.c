#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C6630[];

void func_8003D7E8(void) {
    memset((s32) D_800C6630, 0, 0x14);
}
