#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C98C4[];
extern u8 D_800C98D4[];
extern u8 D_800C98D8[];
extern u8 D_800C98DC[];
extern u8 D_800C98E0[];
extern u8 D_80075844[];
extern u8 D_8007585C[];
extern u8 D_8007587C[];
extern u8 D_8007C8E0;
extern void * D_8007C9DC;
extern s32 D_8007CC20;
extern u8 D_8007CC24;
extern s32 D_8007CC28;


s32 Reservar(s32 arg0, s32 arg1) {
    s32 *var_v1;
    s32 var_v0;

    D_8007CC28 += arg0;
    if (D_8007CC24 == 1) {
        if (*(D_800C98D8 + (D_8007CC20 * 0x10)) != 0) {
            printf((s32) "MEMPTRS system corupted");
        }
        if (*(D_800C98DC + (D_8007CC20 * 0x10)) != 0) {
            printf((s32) "MEMPTRS system corupted");
        }
        if (arg1 != 0) {
            if (D_8007C8E0 != 0) {
                func_800150F0(arg1);
                *(D_800C98D8 + (D_8007CC20 * 0x10)) = func_800161BC();
            }
            strcpy(M2C_FIELD((D_800C98D4 + (D_8007CC20 * 0x10)), s32 *, 4), arg1);
        } else {
            printf((s32) "NO FILENAME AVAILABLE FROM new");
        }
        *(D_800C98E0 + (D_8007CC20 * 0x10)) = arg0;
        if (D_8007C8E0 == 0) {
            var_v0 = M2C_FIELD(M2C_FIELD(D_8007C9DC, void **, 8), s32 (**)(void *, s32), 0x30)(D_8007C9DC, arg0);
            var_v1 = D_800C98D4 + (D_8007CC20 * 0x10);
        } else {
            var_v0 = func_800161BC();
            var_v1 = D_800C98D4 + (D_8007CC20 * 0x10);
        }
        *var_v1 = var_v0;
        D_8007CC20 += 1;
        if (D_8007CC20 == 0x7D0) {
            printf((s32) "MEMPTRS LIMIT REACHED");
loop_15:
            goto loop_15;
        }
        return *(D_800C98C4 + (D_8007CC20 * 0x10));
    }
    if (D_8007C8E0 == 0) {
        return M2C_FIELD(M2C_FIELD(D_8007C9DC, void **, 8), s32 (**)(void *, s32), 0x30)(D_8007C9DC, arg0);
    }
    return func_800161BC();
}
