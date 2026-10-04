#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C98B0;
extern u8 D_800C98BC;
extern u8 D_800C98BD;
extern u8 D_800C98BE;
extern u8 D_800C98BF;
extern u8 D_800C98C0;
extern u8 D_800C98C1;
extern u8 partida[];
extern u8 hechizos;
extern u8 D_8007C8B1;
extern u8 D_8007C8B2;
extern u8 D_8007C8B3;
extern u8 D_8007C8B4;
extern u8 D_8007C8B5;
extern s8 D_8007CC14;
extern s32 D_8007CC30;


void func_8004AEAC(s32 arg0) {
    memcpy((s32) partida, arg0, D_8007CC30);
    D_8007CC14 = 1;
    hechizos = D_800C98BC;
    D_8007C8B1 = D_800C98BD;
    D_8007C8B2 = D_800C98BE;
    D_8007C8B3 = D_800C98BF;
    D_8007C8B4 = D_800C98C0;
    D_8007C8B5 = D_800C98C1;
    D_800C98B0 = 0;
    func_8004AF50();
}
