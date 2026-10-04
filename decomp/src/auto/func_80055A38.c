#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80055A38(void *arg0) {
    s16 temp_v0;
    s32 temp_v0_2;
    void *temp_v0_3;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    switch (temp_v0) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        M2C_FIELD(arg0, s16 *, 0x70) = 1;
        return;
    case 2:                                         /* switch 1 */
        func_8004C6D0(M2C_FIELD(arg0, s32 *, 0x74));
        temp_v0_2 = func_80021CE4(4);
        switch (temp_v0_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            TocarSonido(0xB, 0, 0x2A, 0x7F);
            break;
        case 1:                                     /* switch 2 */
            TocarSonido(0x11, 0, 0x2A, 0x7F);
            break;
        case 2:                                     /* switch 2 */
            TocarSonido(0xD, 0, 0x2A, 0x7F);
            break;
        case 3:                                     /* switch 2 */
            TocarSonido(0x10, 0, 0x2A, 0x7F);
            break;
        default:                                    /* switch 2 */
            TocarSonido(0x10, 0, 0x2A, 0x7F);
            break;
        }
        temp_v0_3 = func_800252A0(0x18, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0);
        M2C_FIELD(temp_v0_3, s8 *, 0x79) = 0;
        func_8004A3B4((s32) temp_v0_3, 0, 0);
        M2C_FIELD(arg0, s16 *, 0x70) = 4;
        func_8004C81C();
        return;
    case 3:                                         /* switch 1 */
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), u8 *, 0x50) == M2C_FIELD((arg0 + 0x74), s8 *, 5)) {
            M2C_FIELD(arg0, s16 *, 0x70) = 2;
            return;
        }
        return;
    case 4:                                         /* switch 1 */
        if (func_8002EFD0((s32) arg0) != 0) {
            M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
            return;
        }
        break;
    default:                                        /* switch 1 */
        M2C_FIELD(arg0, s16 *, 0x70) = 0;
        break;
    }
}
