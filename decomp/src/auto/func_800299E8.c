#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80061234[];
extern u8 D_80061244[];
extern u8 D_80061250[];
extern u8 D_8006125C[];
extern u8 D_80061268[];
extern u8 D_80061274[];
extern u8 D_80061280[];
extern u8 D_8006128C[];
extern u8 D_80061298[];
extern u8 D_8006129C[];
extern u8 D_800612A8[];
extern u8 D_800612B8[];
extern u8 D_800612C4[];
extern u8 D_800612CC[];
extern u8 D_800612D8[];
extern u8 D_800612E4[];
extern u8 D_800612EC[];
extern u8 D_800612F8[];
extern u8 D_80061304[];
extern u8 D_80061310[];
extern u8 D_8006131C[];
extern u8 D_80061324[];
extern u8 D_80061330[];
extern u8 D_80061338[];
extern u8 D_8006D328[];

u8 D_8006D328[0x80];                                /* unable to generate initializer: cannot parse D_80061338 as integer */

u8 *func_800299E8(s32 arg0) {
    u32 temp_a0;

    temp_a0 = arg0 & 0xFF;
    if (temp_a0 < 0x1CU) {
        return *(D_8006D328 + (temp_a0 * 4));
    }
    return D_80061234;
}
