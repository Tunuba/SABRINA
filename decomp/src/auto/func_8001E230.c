#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8001E230(s32 arg0) {
    s32 temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v1;

loop_2:
    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0 != 0) {
        func_8001E230(temp_v0);
        goto loop_2;
    }
    temp_v0_2 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_v0_2 != NULL) {
        M2C_FIELD(temp_v0_2, void **, 8) = (void *) M2C_FIELD(arg0, void **, 8);
    } else {
        temp_v1 = M2C_FIELD(arg0, void **, 0x10);
        if (M2C_FIELD(temp_v1, void **, 4) == arg0) {
            M2C_FIELD(temp_v1, void **, 4) = (void *) M2C_FIELD(arg0, void **, 8);
        }
    }
    temp_v0_3 = M2C_FIELD(arg0, void **, 8);
    if (temp_v0_3 != NULL) {
        M2C_FIELD(temp_v0_3, void **, 0xC) = (void *) M2C_FIELD(arg0, void **, 0xC);
    }
    func_80018488((s32) (s16) M2C_FIELD(arg0, u16 *, 0x62));
}
