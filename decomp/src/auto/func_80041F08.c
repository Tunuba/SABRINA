#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80075500[];


void func_80041F08(void) {
    if (M2C_FIELD(D_80075500, M2C_UNK (**)(), 0) != NULL) {
        M2C_FIELD(D_80075500, M2C_UNK (**)(), 0)();
    }
    M2C_FIELD(D_80075500, M2C_UNK (**)(), -4)();
}
