#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80074CD8;
extern s32 D_80074CDC;
extern s32 D_80074CE0;
extern s32 D_80074CE4;
extern s32 D_80074CE8;
extern s32 D_80074CEC[];
extern s32 D_80074E10[];
extern s32 D_80074E4C[];
extern s8 nivel_actual;


void func_8003DFF0(void) {
    s32 temp_v0;

    D_80074CD8 = D_80074E10[nivel_actual];
    temp_v0 = D_80074E4C[nivel_actual];
    D_80074CE8 = temp_v0;
    D_80074CE4 = temp_v0;
    D_80074CE0 = temp_v0;
    D_80074CDC = temp_v0;
    *D_80074CEC = 0;
    func_8002CF28(1, 0x80074CD8, 1);
}
