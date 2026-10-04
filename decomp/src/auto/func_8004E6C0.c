#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800758F8[];


void func_8004E6C0(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        M2C_FIELD(arg0, u8 **, 8) = D_800758F8;
        M2C_FIELD(arg0, M2C_UNK (**)(), 4) = D_80075900;
        if ((arg0 + 4) != 0) {
            M2C_FIELD(arg0, M2C_UNK (**)(), 4) = D_80060A58;
        }
        if (arg1 > 0) {
            func_80017CE4(arg0);
        }
    }
}
