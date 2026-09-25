#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007C9E8;
extern s16 D_8007CC4A;
extern u16 D_8007CC54;


void func_80024294(void) {
    func_800197E4();
    func_8004FC4C(0);
    func_80023FD4(D_8007C9E8);
    DibujarTexto(D_8007C9E8, ((D_8007CC4A * 3) + 0xE6) & 0xFFFF);
    DibujarTexto(D_8007C9E8, 0x107);
    DibujarTexto(D_8007C9E8, (s32) D_8007CC54);
}
