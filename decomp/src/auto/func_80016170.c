#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80016170(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) saved_reg_ra;
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) saved_reg_gp;
    M2C_FIELD(arg0, void **, 4) = (void *) sp;
    M2C_FIELD(arg0, s32 *, 8) = (s32) saved_reg_fp;
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) saved_reg_s0;
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) saved_reg_s1;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) saved_reg_s2;
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) saved_reg_s3;
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) saved_reg_s4;
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) saved_reg_s5;
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) saved_reg_s6;
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) saved_reg_s7;
    return 0;
}
