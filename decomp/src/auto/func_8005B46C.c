#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80024F8C();
extern s32 func_8005B460();

void func_8005B46C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_s1;

    M2C_FIELD(arg0, s32 *, 0x74) = arg3;
    M2C_FIELD(arg0, s32 *, 0x78) = 0;
    M2C_FIELD(arg0, s32 *, 0x7C) = (s32) (arg4 >> 8);
    if (func_8002ECFC(arg0) != 0) {
        temp_s1 = M2C_FIELD(arg0, void **, 0x1C);
        M2C_FIELD(temp_s1, s16 *, 0x4C) = 0;
        M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x1000;
        M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) arg2;
        M2C_FIELD(temp_s1, s8 *, 0x50) = 0;
        M2C_FIELD(temp_s1, s8 *, 0x53) = (s8) arg2;
        M2C_FIELD(temp_s1, s8 *, 0x52) = 0;
        M2C_FIELD(temp_s1, s8 *, 8) = func_80030068(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s32 *, 4));
    }
    M2C_FIELD(arg0, s32 (**)(s32), 0x14) = func_80024F8C;
    M2C_FIELD(arg0, s32 (**)(s32), 8) = func_8005B460;
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
    M2C_FIELD(arg0, s8 *, 0x118) = 0;
    M2C_FIELD(arg0, s8 *, 0x119) = 1;
    M2C_FIELD(arg0, s16 *, 0x112) = 0x801;
    M2C_FIELD(arg0, s16 *, 0x114) = 1;
}
