#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006CFC0;
extern s32 D_8006CFC4;
extern s32 D_8006CFD4;
extern s32 D_8006CFEC;

static M2C_UNK (*D_8006CF9C)(s32) = NULL;
static M2C_UNK (*D_8006CFB0)() = NULL;
static M2C_UNK (*D_8006CFB4)() = NULL;

void func_800273B0(void *arg0) {
    u8 var_a1;

    if ((D_8006CFC4 == D_8006CFD4) && (D_8006CFC0 != 0)) {
        D_8006CFB4();
        D_8006CFB0();
    }
    if (D_8006CFEC != 0) {
        D_8006CF9C(M2C_FIELD(arg0, s32 *, 0xC));
        D_8006CF9C(M2C_FIELD(arg0, s32 *, 0xC) + 0xF0);
    }
    if (M2C_FIELD(arg0, u8 *, 0x37) == 0) {
        var_a1 = 0x42;
    } else {
        var_a1 = M2C_FIELD(arg0, u8 *, 0x37);
    }
    func_8002643C((s32) arg0, (s32) var_a1);
}
