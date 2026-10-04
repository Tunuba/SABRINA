#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8005655C(s32 arg0) {
    void *temp_v0;
    void *temp_v1;

    temp_v1 = arg0 + 0x74;
    temp_v0 = M2C_FIELD(temp_v1, void **, 0xC);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s16 *, 0x40) = 1;
        M2C_FIELD(temp_v1, void **, 0xC) = NULL;
    }
}
