#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 nivel_actual;
extern s16 D_8007CA1C;
extern u16 D_8007CA1E;
extern u16 D_8007CA20;
extern s16 D_8007CA22;
extern s32 D_8007CA2C;
extern u32 D_8007CA30;
extern s32 D_8007CA34;
extern u8 D_8007CA38;
extern u16 D_8007CA3A;
extern s32 D_8007CA50;
extern s32 D_8007CA58;
extern u16 D_8007CBFE;
extern u16 D_8007CC4C;
extern s32 D_8007CC68;


void func_80019D80(void) {
    u16 var_v0;

    if (D_8007CA2C < -1) {
        D_8007CA2C = func_80021CE4(0x32) + 0x32;
    }
    D_8007CA2C -= 1;
    D_8007CA30 += 1;
    if ((u32) D_8007CA30 >= 0x64U) {
        D_8007CA30 = 0;
    }
    if (D_8007CC68 != 0) {
        D_8007CC68 -= 1;
        if (D_8007CC68 == 0) {
            D_8007CA20 = 0;
        }
    }
    func_8003D7E8();
    if (D_8007CBFE == 0) {
        func_8001D778();
    } else {
        D_8007CBFE -= 1;
        D_8007CA58 = 0;
        D_8007CA50 = 0;
    }
    if ((D_8007CA58 & 0x800) && (nivel_actual != 0)) {
        if (D_8007CA34 == 0) {
            D_8007CA34 = 2;
        }
        if ((D_8007CA20 != 0xDD) && (D_8007CA38 == 0)) {
            D_8007CA1E = 0;
            D_8007CA38 = 1;
            if ((nivel_actual == 0xE) || (nivel_actual == 0xD)) {
                D_8007CA1C = 9;
                var_v0 = 0x11E;
            } else {
                var_v0 = 2;
                D_8007CA1C = 0;
            }
            D_8007CA20 = var_v0;
            func_8003E0B4();
            func_8004B21C((s32) nivel_actual);
        }
    }
    if (D_8007CA38 == 0) {
        D_8007CA34 = 0;
        if (D_8007CC4C == 0) {
            func_8001F334();
            ActivarObjetosCercanos();
            func_800257F4();
            return;
        }
        func_80024294();
        return;
    }
    if (D_8007CC4C == 0) {
        if (D_8007CA20 != D_8007CA3A) {
            D_8007CA22 = func_80019234((s32) D_8007CA20);
        }
        D_8007CA3A = D_8007CA20;
        func_8001981C();
        func_80019288();
        func_80019374((s32) D_8007CA20, (s32) D_8007CA1E);
        return;
    }
    func_80024294();
}
