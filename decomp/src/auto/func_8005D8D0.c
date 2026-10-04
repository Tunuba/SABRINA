#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80062868[];
extern u8 D_80075B9C[];
extern u8 D_80075C20[];
extern s32 * D_80075CAC;
extern s32 * D_80075CB8;
extern s32 * D_80075CC0;


void func_8005D8D0(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0:
        *D_80075CC0 = 0x80000000;
        *D_80075CAC = 0;
        *D_80075CB8 = 0;
        *D_80075CC0 = 0x60000000;
        func_8005D9C0((s32) D_80075B9C, 0x20);
        func_8005D9C0((s32) D_80075C20, 0x20);
        return;
    case 1:
        *D_80075CC0 = 0x80000000;
        *D_80075CAC = 0;
        *D_80075CB8 = 0;
        *D_80075CC0 = 0x60000000;
        return;
    default:
        printf((s32) "MDEC_rest:bad option(%d)\n", arg0);
        return;
    }
}
