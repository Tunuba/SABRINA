#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80060CF8[];
extern s32 * D_80063754;
extern s32 * D_80063758;
extern s32 * D_80063760;
extern s32 * D_80063770;
extern s32 D_8006377C;
extern s32 D_80063780;
extern s32 D_80063784;
extern s32 D_80063818;
extern s32 D_8006381C[];


s32 func_80012900(void) {
    s32 temp_a0;
    s32 temp_v0;

    if ((D_80063780 < func_8001626C(-1)) || (temp_a0 = D_80063784, D_80063784 += 1, ((temp_a0 > 0xF0000) != 0))) {
        printf((s32) "GPU timeout:que=%d,stat=%08x,chcr=%08x,madr=%08x\n", (D_80063818 - *D_8006381C) & 0x3F, *D_80063754, *D_80063760, *D_80063758);
        temp_v0 = func_80016A14(0);
        *D_8006381C = 0;
        D_8006377C = temp_v0;
        D_80063818 = *D_8006381C;
        *D_80063760 = 0x401;
        *D_80063770 |= 0x800;
        *D_80063754 = 0x02000000;
        *D_80063754 = 0x01000000;
        func_80016A14(D_8006377C);
        return -1;
    }
    return 0;
}
