#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8004866C(void *arg0) {
    void *temp_v0;

    if (M2C_FIELD(arg0, s16 *, 0x112) & 0x8000) {
        temp_v0 = M2C_FIELD(arg0, void **, 0x11C);
        if (temp_v0 != NULL) {
            M2C_FIELD(temp_v0, M2C_UNK (**)(void *), 0x18)(temp_v0);
        }
    }
}
