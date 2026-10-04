#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80086454[];
extern u8 D_80086476[];
extern s32 D_8007C7F0;
extern s32 D_8007CA50;
extern s32 D_8007CA54;
extern s32 D_8007CA58;
extern s32 D_8007CA5C;
extern s32 D_8007CA60;
extern s32 D_8007CA64;
extern s32 D_8007CA68;
extern s32 D_8007CA6C;


void func_8001D554(void) {
    func_800283C4((s32) D_80086454, (s32) D_80086476);
    func_80027998();
    func_8001D5C0(0);
    func_8001D5C0(1);
    D_8007C7F0 = 0x64;
    D_8007CA50 = 0;
    D_8007CA54 = 0;
    D_8007CA58 = 0;
    D_8007CA5C = 0;
    D_8007CA60 = 0;
    D_8007CA64 = 0;
    D_8007CA68 = 0;
    D_8007CA6C = 0;
}
