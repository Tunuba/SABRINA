#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8007CCB0[];
extern s32 func_80010670();

extern M2C_UNK (*D_8007C9D8)();

void func_80010000(void) {
    D_8007C9D8 = D_80060A58;
    D_8007C9D8 = D_800758CC;
    func_80017C6C((s32) &D_8007C9D8, (s32) func_80010670, (s32) D_8007CCB0);
}
