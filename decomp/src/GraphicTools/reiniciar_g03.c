#include "juego.h"

/* Entre Font.c y GraphicTools.c (modulo sin nombre conocido): vuelve a cero el estado de la pantalla. */

extern s32 D_8007CA24;
extern s32 D_8007CA28;
extern u8 D_8007C8AC;
extern s32 D_80086324[5];
extern s32 D_80086338[11];
extern s32 D_800C98C4[5];
extern s32 D_8007CC1C;
extern s16 D_8007CBD4;
extern s32 D_8007CC0C;
extern s32 D_8007CA2C;
extern s32 D_8007CA30;
extern s32 D_8007CAFC;

void func_80019C04(void) {
    s32 i;

    D_8007CA24 = 0;
    D_8007CA28 = 0;
    D_8007C8AC = 1;
    for (i = 0; i < 5; i++) {
        D_80086324[i] = 0;
    }
    for (i = 0; i < 11; i++) {
        D_80086338[i] = 0;
    }
    for (i = 0; i < 5; i++) {
        D_800C98C4[i] = 0;
    }
    D_8007CC1C = 0;
    D_8007CBD4 = 0;
    D_8007CC0C = 0;
    D_8007CA2C = 50;
    D_8007CA30 = 0;
    D_8007CAFC = 0;
}
