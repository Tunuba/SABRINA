#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C8538[];
extern s16 partida;
extern s32 D_80074CD8;
extern s32 D_80074CDC;
extern u16 D_80074D3C[];
extern s32 D_80074D5C[];
extern s32 D_80074D98[];
extern s32 D_80074DD4[];
extern s8 nivel_actual;
extern s32 D_8007CBEC;


void func_8003DEE8(void) {
    s32 var_v0;

    if (D_8007CBEC != 0) {
        if (partida < 2) {
            var_v0 = D_80074DD4[nivel_actual];
        } else {
            var_v0 = D_80074DD4[nivel_actual];
        }
    } else if (*(D_800C8538 + (nivel_actual * 2)) < (s32) D_80074D3C[nivel_actual]) {
        var_v0 = D_80074D98[nivel_actual];
    } else {
        var_v0 = D_80074D5C[nivel_actual];
    }
    D_80074CD8 = var_v0;
    D_80074CDC = 0;
    func_8002CF28(1, (s32) &D_80074CD8, 0);
}
