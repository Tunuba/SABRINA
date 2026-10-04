#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C857E;
extern s8 D_800C857F;
extern s8 D_800C8580;
extern s8 D_800C8581;
extern s8 objetos_anacronicos;
extern s8 D_8007C88D;
extern s8 D_8007C88E;
extern s8 D_8007C88F;
extern s8 nivel_actual;


void func_8005B150(void *arg0) {
    s16 temp_v0;
    s32 temp_a0;
    s32 temp_s2;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s1;

    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x2D);
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) & 0xFFF);
    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    switch (temp_v0) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x54);
        if (temp_a0 < 0x1000) {
            M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_a0 + ((s32) (0x1000 - temp_a0) >> 2));
            if (M2C_FIELD(arg0, s32 *, 0x54) >= 0x1000) {
                M2C_FIELD(arg0, s32 *, 0x54) = 0x1000;
            }
            temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x54);
            M2C_FIELD(arg0, s32 *, 0x5C) = temp_v0_2;
            M2C_FIELD(arg0, s32 *, 0x58) = temp_v0_2;
            return;
        }
        return;
    case 1:                                         /* switch 1 */
        switch (nivel_actual) {                     /* switch 2; irregular */
        case 4:                                     /* switch 2 */
            D_800C857E = 1;
            D_8007C88D = 1;
            break;
        case 7:                                     /* switch 2 */
            D_800C8581 = 1;
            D_8007C88E = 1;
            break;
        case 8:                                     /* switch 2 */
            D_800C857F = 1;
            D_8007C88F = 1;
            break;
        case 10:                                    /* switch 2 */
            D_800C8580 = 1;
            objetos_anacronicos = 1;
            break;
        }
        TocarSonido(0x1E, 0, 0x23, 0x7F);
        func_8004C22C();
        var_s1 = 0;
loop_19:
        var_s0 = 0;
        if (var_s1 < 0x1000) {
loop_17:
            if (var_s0 < 0x1000) {
                temp_s2 = (s32) (rsin(var_s1) * 0xCCC) >> 0xC;
                CrearParticula(0xF, (s32) arg0, var_s0, 0, /* extra? */ 0, /* extra? */ 0x28F, /* extra? */ 0, /* extra? */ temp_s2, /* extra? */ ((s32) (rcos(var_s1) * 0xCCC) >> 0xC), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x202, /* extra? */ 0);
                var_s0 = (s32) (s16) (var_s0 + 0x3E8);
                goto loop_17;
            }
            var_s1 = (s32) (s16) (var_s1 + 0x384);
            goto loop_19;
        }
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
        break;
    }
}
