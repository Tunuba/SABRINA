#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80039670(void *arg0, void *arg1) {
    s32 temp_s0;
    void *temp_s1;
    void *temp_s2;

    if ((M2C_FIELD(arg1, u16 *, 0x22) == 6) && (M2C_FIELD(arg1, s8 *, 0x93) >= 7)) {
        temp_s0 = M2C_FIELD(arg0, s32 *, 0x11C);
        Afirmar(temp_s0);
        temp_s2 = temp_s0 + 0x74;
        temp_s1 = M2C_FIELD(temp_s2, void **, 0xC);
        M2C_FIELD(temp_s1, s8 *, 0x118) = (s8) (M2C_FIELD(temp_s1, s8 *, 0x118) - 1);
        if (M2C_FIELD(temp_s1, s8 *, 0x118) < 0) {
            M2C_FIELD(temp_s2, M2C_UNK (**)(s32, void *), 0x10)(temp_s0, temp_s1);
            M2C_FIELD(temp_s0, s8 *, 0x20) = 0x80;
            M2C_FIELD(temp_s2, M2C_UNK (**)(s32, void *), 0x10) = NULL;
            M2C_FIELD(temp_s1, M2C_UNK (**)(void *, void *), 8)(temp_s1, arg1);
        }
    }
}
