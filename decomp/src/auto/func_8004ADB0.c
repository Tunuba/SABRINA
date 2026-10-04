#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800C8578;
extern s32 D_800C988C;
extern s32 D_800C9890;
extern s32 D_800C9894;
extern s32 D_800C9898;
extern s32 D_800C989C;
extern s32 D_800C98A0;
extern u8 D_800C98BC;
extern u8 D_800C98BD;
extern u8 D_800C98BE;
extern u8 D_800C98BF;
extern u8 D_800C98C0;
extern u8 D_800C98C1;
extern u8 hechizos;
extern u8 D_8007C8B1;
extern u8 D_8007C8B2;
extern u8 D_8007C8B3;
extern u8 D_8007C8B4;
extern u8 D_8007C8B5;
extern s8 D_8007CB28;
extern s32 D_8007CC2C;
extern s32 D_8007CC30;


void func_8004ADB0(s32 arg0) {
    D_800C988C = p_sabrina->x;
    D_800C9890 = p_sabrina->y;
    D_800C9894 = p_sabrina->z;
    D_800C9898 = (s32) p_sabrina->rot[0];
    D_800C989C = (s32) p_sabrina->rot[1];
    D_800C98A0 = (s32) p_sabrina->rot[2];
    func_8004AEA4();
    D_8007CB28 = (s8) D_800C8578;
    D_800C98BC = hechizos;
    D_800C98BD = D_8007C8B1;
    D_800C98BE = D_8007C8B2;
    D_800C98BF = D_8007C8B3;
    D_800C98C0 = D_8007C8B4;
    D_800C98C1 = D_8007C8B5;
    memcpy(arg0, D_8007CC2C, D_8007CC30);
}
