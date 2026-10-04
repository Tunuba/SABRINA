#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800628A4[];
extern s32 * D_80075CAC;
extern s32 * D_80075CB8;
extern s32 * D_80075CC0;


void func_8005DC1C(s32 arg0) {
    printf((s32) D_800628A4, arg0);
    *D_80075CC0 = 0x80000000;
    *D_80075CAC = 0;
    *D_80075CB8 = 0;
    *D_80075CC0 = 0x60000000;
}
