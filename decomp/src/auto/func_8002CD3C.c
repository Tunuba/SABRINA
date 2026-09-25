#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8009387C[];
extern s32 D_80093A0C;
extern s8 D_80093A1B;
extern u8 D_80061754[];
extern s32 D_8006D30C;
extern s32 D_8006D418;
extern s32 D_8006D41C[];
extern s32 D_8006D5AC;
extern s32 D_8006D5B0;
extern s32 D_8006D5B4;
extern s32 D_8006D5B8;
extern s32 func_8002CBB0();


void func_8002CD3C(void) {
    s32 temp_a1;
    s32 var_v1;
    s8 *var_v0;

    D_8006D5B0 = 0;
    if (D_8006D41C[D_8006D5AC] == 0) {
        if (D_8006D5B4 != 0) {
            D_8006D5AC = 0;
            D_8006D5B8 = *D_8006D41C;
        } else {
            D_8006D5AC = -1;
            func_8002CEB4();
        }
    }
    var_v1 = 7;
    if (D_8006D5AC >= 0) {
        var_v0 = &D_80093A1B;
        do {
            *var_v0 = 0;
            var_v1 -= 1;
            var_v0 -= 1;
        } while (var_v1 >= 0);
        temp_a1 = D_8006D41C[D_8006D5AC];
        D_8006D418 += 1;
        if (D_80093A0C < temp_a1) {
            if (D_8006D30C >= 2) {
                printf((s32) "%d: track overflow\n", temp_a1);
            }
            D_8006D41C[D_8006D5AC] = D_80093A0C;
        }
        func_80029AA4((s32) func_8002CBB0);
        func_80029AB8(3, (s32) ((D_8006D41C[D_8006D5AC] * 4) + D_8009387C), 0);
    }
}
