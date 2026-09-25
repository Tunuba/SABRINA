#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8002205C(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s1;
    s32 temp_s3;

    temp_s3 = rsin(arg2);
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((s32) (temp_s3 * rcos(arg1)) >> 0xC);
    temp_s1 = rcos(arg2);
    M2C_FIELD(arg0, s32 *, 8) = (s32) ((s32) (temp_s1 * rcos(arg1)) >> 0xC);
    M2C_FIELD(arg0, s32 *, 4) = rsin(arg1);
    func_8001C45C(arg0);
}
