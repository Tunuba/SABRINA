#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80063754;
extern s32 * D_80063758;
extern s32 * D_8006375C;
extern s32 * D_80063760;


void func_80012094(s32 arg0) {
    *D_80063754 = 0x04000002;
    *D_80063758 = arg0;
    *D_8006375C = 0;
    *D_80063760 = 0x01000401;
}
