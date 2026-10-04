#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80024F6C();
extern s32 func_80024F74();

void func_80044E30(void *arg0, s32 arg1) {
    void *temp_s2;
    void *temp_s3;
    void *temp_s4;

    temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s4 = M2C_FIELD(arg0, void **, 0x64);
    temp_s3 = arg0 + 0x74;
    func_80048468((s32) arg0, arg1);
    if ((M2C_FIELD(arg1, s16 *, 0x112) & 0x1000) && !(M2C_FIELD(arg0, s16 *, 0x112) & 0x100)) {
        M2C_FIELD(arg0, s8 *, 0x118) = (s8) (M2C_FIELD(arg0, s8 *, 0x118) - M2C_FIELD(arg1, s8 *, 0x119));
        func_80049110(arg1 + 0x24, 0x28F);
        if (M2C_FIELD(arg0, s8 *, 0x118) < 0) {
            M2C_FIELD(arg0, s16 *, 0x112) = 0;
            M2C_FIELD(arg0, s32 (**)(), 0xC) = func_80024F74;
            M2C_FIELD(arg0, s32 (**)(), 8) = func_80024F6C;
            M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(temp_s4, u16 *, 4);
            M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
            M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x800;
            M2C_FIELD(arg0, s16 *, 0x70) = 0xA;
            M2C_FIELD(temp_s3, s16 *, 0x2A) = 0x64;
            M2C_FIELD(temp_s3, s8 *, 0x29) = 0xA;
            TocarSonido(0x2A, 0, 0x2A, 0x7F);
            return;
        }
        TocarSonido(0x2B, 0, 0x2A, 0x7F);
    }
}
