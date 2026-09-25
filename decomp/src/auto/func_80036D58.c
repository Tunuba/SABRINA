#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C6594;
extern s32 D_800C6598;
extern s32 D_800C659C;
extern s32 D_800C65A0;
extern s32 D_800C65A4;
extern s32 D_800C65A8;
extern void * D_8007CAFC;
extern s16 D_8007CBD4;


s32 func_80036D58(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v1;
    s32 temp_v1_2;

    D_8007CBD4 = 0;
    D_800C6594 = p_sabrina->x;
    D_800C6598 = p_sabrina->y;
    D_800C659C = p_sabrina->z;
    temp_v1 = arg0 >> 4;
    temp_v1_2 = arg2 >> 4;
    temp_s2 = ((s32) (temp_v1 * 0x300) >> 8) << 8;
    D_800C6598 = arg3;
    temp_s1 = ((s32) (temp_v1_2 * 0x300) >> 8) << 8;
    D_800C65A0 = D_800C6594 - temp_s2;
    D_800C65A8 = D_800C659C - temp_s1;
    temp_s4 = ((s32) (temp_v1 * 0xCC) >> 8) << 8;
    D_800C65A4 = arg3;
    temp_s3 = ((s32) (temp_v1_2 * 0xCC) >> 8) << 8;
    D_800C6594 += temp_s4;
    D_800C659C += temp_s3;
    func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
    if (func_8003AE84() != 0) {
        D_8007CBD4 = -0x11;
        return 0;
    }
    D_800C65A0 = (D_800C6594 - temp_s2) + (func_80021CE4(0x4000) - 0x2000);
    D_800C65A8 = (D_800C659C - temp_s1) + (func_80021CE4(0x4000) - 0x2000);
    D_800C65A4 = arg3;
    D_800C6594 = p_sabrina->x;
    D_800C6598 = p_sabrina->y;
    D_800C659C = p_sabrina->z;
    D_800C6594 += temp_s4;
    D_800C659C += temp_s3;
    D_800C6598 = arg3;
    func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
    if (func_8003AE84() != 0) {
        D_8007CBD4 = -0x11;
        return 0;
    }
    D_800C65A0 = (D_800C6594 - temp_s2) + (func_80021CE4(0x4000) - 0x2000);
    D_800C65A8 = (D_800C659C - temp_s1) + (func_80021CE4(0x4000) - 0x2000);
    D_800C65A4 = arg3;
    D_800C6594 = p_sabrina->x;
    D_800C6598 = p_sabrina->y;
    D_800C659C = p_sabrina->z;
    D_800C6594 += temp_s4;
    D_800C659C += temp_s3;
    D_800C6598 = arg3;
    func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
    if (func_8003AE84() != 0) {
        D_8007CBD4 = -0x11;
        return 0;
    }
    D_800C65A0 = (D_800C6594 - temp_s2) + (func_80021CE4(0x4000) - 0x2000);
    D_800C65A8 = (D_800C659C - temp_s1) + (func_80021CE4(0x4000) - 0x2000);
    D_800C65A4 = arg3;
    D_800C6594 = p_sabrina->x;
    D_800C6598 = p_sabrina->y;
    D_800C659C = p_sabrina->z;
    D_800C6594 += temp_s4;
    D_800C659C += temp_s3;
    D_800C6598 = arg3;
    func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
    if (func_8003AE84() != 0) {
        D_8007CBD4 = -0x11;
        return 0;
    }
    D_800C65A0 = D_800C6594 - (((s32) ((arg0 >> 4) * 0x300) >> 8) << 8);
    D_800C65A8 = D_800C659C - (((s32) ((arg2 >> 4) * 0x300) >> 8) << 8);
    D_800C65A4 = func_800350FC(M2C_FIELD(p_sabrina, s32 *, 0x50)) + 0xFFFECCCD;
    M2C_FIELD(D_8007CAFC, s32 *, 0x24) = (s32) D_800C65A0;
    M2C_FIELD(D_8007CAFC, s32 *, 0x28) = (s32) D_800C65A4;
    M2C_FIELD(D_8007CAFC, s32 *, 0x2C) = (s32) D_800C65A8;
    D_8007CBD4 = -0x11;
    return 1;
}
