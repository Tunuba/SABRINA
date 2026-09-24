#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C86C6[];
extern u8 D_80075628[];
extern u8 D_80075638[];
extern u8 D_80075644[];
extern u8 D_80075650[];
extern u8 D_8007565C[];
extern u8 D_80075668[];
extern u8 D_80075678[];
extern u8 D_80075684[];
extern u8 D_80075690[];
extern u16 D_800756E0[];
extern u16 D_800756F4[];
extern u8 D_8007C7AC;
extern u8 D_8007C8C8[];
extern u8 D_8007C8D0[];
extern u16 D_8007CA14;
extern s32 D_8007CA18;
extern u16 D_8007CA1C;
extern u16 D_8007CA1E;
extern u16 D_8007CA20;
extern u16 D_8007CA22;
extern s32 D_8007CA34;
extern s32 D_8007CA58;
extern s32 func_80046B90();
extern s32 func_80046BAC();
extern s32 func_80046D54();
extern s32 func_80046EA4();

u8 D_80075690[0x28];                                /* unable to generate initializer: cannot parse D_80075628 as integer */
static s32 (*D_800756B8[0xA])() = {
    func_80046B90,
    func_80046BAC,
    func_80046D54,
    func_80046D54,
    func_80046BAC,
    func_80046EA4,
    func_80046EA4,
    func_80046EA4,
    func_80046BAC,
    func_80046B90,
};

void func_8001981C(void) {
    s32 temp_a0;

    D_8007CA20 = D_800756E0[D_8007CA1C];
    if (D_8007CA14 != 0) {
        *(*(D_80075690 + (D_8007CA1C * 4)) + (D_8007CA1E * 4))(D_8007CA1C, D_8007CA1C * 2, D_8007CA1C);
        if (D_8007CA58 & 0x40) {
            D_8007CA14 = 0;
        }
        if (D_8007CA58 & 0x10) {
            D_8007CA14 = 0;
        }
    } else {
        if (D_8007CA58 & 0x4000) {
            if (D_8007CA1E != (D_8007CA22 - D_800756F4[D_8007CA1C])) {
                D_8007CA1E += 1;
                if (D_8007CA1C == 5) {
                    if (*(D_800C86C6 + ((D_8007CA18 + D_8007CA1E) * 0x141)) == 0) {
                        TocarSonido(0x30, 0, 0x2A, 0x7F);
                        D_8007CA1E -= 1;
                    } else {
                        TocarSonido(0x2E, 0, 0x2A, 0x7F);
                    }
                } else {
                    TocarSonido(0x2E, 0, 0x2A, 0x7F);
                }
            } else {
                TocarSonido(0x30, 0, 0x2A, 0x7F);
            }
        }
        if (D_8007CA58 & 0x1000) {
            if (D_8007CA1E != 0) {
                D_8007CA1E -= 1;
                if (D_8007CA1C == 5) {
                    if (*(D_800C86C6 + ((D_8007CA18 + D_8007CA1E) * 0x141)) == 0) {
                        TocarSonido(0x30, 0, 0x2A, 0x7F);
                        D_8007CA1E += 1;
                    } else {
                        TocarSonido(0x2E, 0, 0x2A, 0x7F);
                    }
                } else {
                    TocarSonido(0x2E, 0, 0x2A, 0x7F);
                }
            } else {
                TocarSonido(0x30, 0, 0x2A, 0x7F);
            }
        }
        if (D_8007CA58 & 0x40) {
            D_8007C7AC = 1;
            temp_a0 = D_8007CA1C * 4;
            *(*(D_80075690 + temp_a0) + (D_8007CA1E * 4))(temp_a0);
            if (D_8007C7AC == 1) {
                TocarSonido(0x2F, 0, 0x2A, 0x7F);
            }
        }
        if (D_8007CA58 & 0x10) {
            TocarSonido(0x30, 0, 0x2A, 0x7F);
            D_800756B8[D_8007CA1C]();
        }
        if (D_8007CA58 & 0x800) {
            if ((D_8007CA34 == 1) && ((D_8007CA1C == 7) || (D_8007CA1C == 0))) {
                TocarSonido(0x30, 0, 0x2A, 0x7F);
                D_800756B8[D_8007CA1C]();
                D_8007CA34 = 0;
            }
        } else if (D_8007CA34 == 2) {
            D_8007CA34 = 1;
        }
    }
}
