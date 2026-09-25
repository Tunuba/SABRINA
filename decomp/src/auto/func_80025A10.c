#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800909E8;
extern s32 D_800909EC;
extern void * D_8006CF70;
extern s32 D_8006CF74;
extern s32 D_8006CFB8;
extern s32 D_8006CFBC;
extern s32 D_8006CFC4;
extern s32 D_8006CFC8;
extern s32 D_8006CFCC;
extern s32 D_8006CFD4;
extern s32 D_8006CFD8;

static M2C_UNK (*D_8006CF84)(M2C_UNK) = NULL;

s32 func_80025A10(void) {
    s32 temp_v1;

    if (M2C_FIELD(D_8006CF70, u16 *, 0xA) & 2) {
        M2C_FIELD(D_8006CF70, u16 *, 0xA) = 0U;
    } else {
        D_8006CF74 = 1;
        if ((D_8006CFD4 != 0) && (D_800909E8 < 0x96)) {
            D_800909E8 += 1;
        }
        if ((D_8006CFD8 == 0) && (D_800909EC < 0x96)) {
            D_800909EC += 1;
        }
        if ((D_8006CFBC != 0) && (D_8006CFD8 >= D_8006CFD4)) {
            D_8006CFC8 = 0;
            D_8006CFC4 = D_8006CFD4;
            if (func_80025EF8(D_8006CFB8 + (D_8006CFD4 * 0xF0)) == 0) {
                D_8006CF84(0xFFFF);
            }
            temp_v1 = D_8006CFC4;
            D_8006CFCC = 0;
            if (D_8006CFD8 >= temp_v1) {
                do {
                    func_80025BA0(D_8006CFB8 + (temp_v1 * 0xF0));
                } while (D_8006CFD8 >= D_8006CFC4);
            }
            M2C_FIELD(D_8006CF70, s16 *, 0xE) = 0x88;
        }
    }
    return 0;
}
