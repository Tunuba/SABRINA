#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007CB50;
extern s32 func_80024F6C();


void func_8005473C(s32 arg0, s32 arg1) {
    void *temp_v1;

    func_80048468(arg0, arg1);
    if ((M2C_FIELD(arg1, u16 *, 0x22) == 6) && (func_800221FC(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0x28), M2C_FIELD(arg0, s32 *, 0x2C), M2C_FIELD(arg1, s32 *, 0x24), /* extra? */ M2C_FIELD(arg1, s32 *, 0x28), /* extra? */ M2C_FIELD(arg1, s32 *, 0x2C)) < 0x40000)) {
        temp_v1 = M2C_FIELD(arg0, void **, 0x1C);
        M2C_FIELD(arg0, s32 (**)(), 8) = func_80024F6C;
        M2C_FIELD(arg0, s16 *, 0x70) = 3;
        M2C_FIELD(temp_v1, s16 *, 0x4E) = 0x1000;
        M2C_FIELD(temp_v1, s8 *, 0x51) = (s8) D_8007CB50;
        M2C_FIELD(temp_v1, s8 *, 0x50) = 0;
    }
}
