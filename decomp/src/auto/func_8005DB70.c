#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80062894[];
extern s32 * D_80075CB8;


s32 func_8005DB70(void) {
    s32 sp10;
    s32 temp_v0;

    sp10 = 0x100000;
    if (*D_80075CB8 & 0x01000000) {
loop_2:
        temp_v0 = sp10 - 1;
        sp10 = temp_v0;
        if (temp_v0 == -1) {
            func_8005DC1C((s32) "MDEC_out_sync");
            return -1;
        }
        if (!(*D_80075CB8 & 0x01000000)) {
            /* Duplicate return node #5. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_2;
    }
    return 0;
}
