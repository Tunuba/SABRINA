#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80061474[];
extern u8 D_80061480[];
extern s8 * D_8006D2B0;
extern s8 * D_8006D2B8;
extern u8 * D_8006D2BC;
extern s32 * D_8006D2C0;
extern u8 D_8006D2C8[];
extern u8 D_8006D2CC[];
extern s32 D_8006D304;
extern s32 D_8006D308;
extern s32 D_8006D310;
extern s32 D_8006D314;
extern s8 D_8006D320;
extern s8 D_8006D321;
extern s32 func_8002A5F8();

u8 D_8006D2CC[0x18];                                /* unable to generate initializer: cannot parse D_8006D2C8 as integer */

s32 func_8002B2BC(void) {
    puts((s32) D_80061474);
    printf((s32) D_80061480, D_8006D2CC);
    D_8006D321 = 0;
    D_8006D320 = 0;
    D_8006D308 = 0;
    D_8006D304 = 0;
    D_8006D314 = 0;
    D_8006D310 = 0;
    func_80016910(M2C_ERROR(/* Read from unset register $a0 */), M2C_ERROR(/* Read from unset register $a1 */), M2C_ERROR(/* Read from unset register $a2 */));
    func_80016940(2, (s32) func_8002A5F8);
    *D_8006D2B0 = 1;
    if (*D_8006D2BC & 7) {
        do {
            *D_8006D2B0 = 1;
            *D_8006D2BC = 7;
            *D_8006D2B8 = 7;
        } while (*D_8006D2BC & 7);
    }
    M2C_FIELD(D_8006D2C8, u8 *, 2) = 0U;
    M2C_FIELD(D_8006D2C8, u8 *, 1) = (u8) M2C_FIELD(D_8006D2C8, u8 *, 2);
    M2C_FIELD(D_8006D2C8, u8 *, 0) = 2;
    *D_8006D2B0 = 0;
    *D_8006D2BC = 0;
    *D_8006D2C0 = 0x1325;
    func_8002AC18(1, 0, 0, 0);
    if (D_8006D310 & 0x10) {
        func_8002AC18(1, 0, 0, 0);
    }
    if (func_8002AC18(0xA, 0, 0, 0) == 0) {
        if (func_8002AC18(0xC, 0, 0, 0) == 0) {
            if (func_8002A6D0(0, 0) == 2) {
                return 0;
            }
            /* Duplicate return node #10. Try simplifying control flow for better match */
            return -1;
        }
        /* Duplicate return node #10. Try simplifying control flow for better match */
        return -1;
    }
    return -1;
}
