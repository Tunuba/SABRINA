#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80074CD8;
extern s32 D_80074CDC;
extern s32 D_80074D00[];
extern u16 D_8007C8C4;
extern s8 nivel_actual;


void func_8003DDFC(void) {
    D_80074CD8 = D_80074D00[nivel_actual];
    D_80074CDC = 0;
    func_8002CF28(2, (s32) &D_80074CD8, 0);
    func_8003DD44((D_8007C8C4 * 0xF) & 0xFF);
}
