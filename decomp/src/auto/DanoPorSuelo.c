#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 texto_invencible[];
extern s8 nivel_actual;
extern s8 vida_barra;
extern s32 truco_invencible;
extern void * D_8007CB8C;


void DanoPorSuelo(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *sp6C;
    void *sp70;
    s32 sp74;
    s32 temp_s4;
    s32 temp_s4_2;
    s32 temp_s5;
    s32 temp_s5_2;
    s32 temp_s5_3;
    s32 temp_s5_4;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_fp;
    s32 var_fp_2;
    s8 var_s6;
    s8 var_s6_2;
    s8 var_s7;
    s8 var_s7_2;
    u16 temp_v0;
    void *temp_s0;
    void *temp_s2;
    void *temp_s3;

    temp_s2 = M2C_FIELD(arg0, void **, 0x1C);
    sp6C = M2C_FIELD(arg0, void **, 0x64);
    temp_s0 = M2C_FIELD(D_8007CB8C, void **, 0x1C);
    sp70 = M2C_FIELD(D_8007CB8C, void **, 0x64);
    temp_s3 = arg0 + 0x74;
    if (truco_invencible != 0) {
        ImprimirDepuracion((s32) "\nSABRINA IS INVINCIBLE\n", arg1, arg2, arg3);
        return;
    }
    if ((M2C_FIELD(temp_s3, s16 *, 0x18) & 0x10) && (temp_v0 = M2C_FIELD(temp_s3, u16 *, 0xC), (temp_v0 != 0x80)) && (temp_v0 != 0x40) && (temp_v0 != 0x20) && (temp_v0 != 0x10)) {
        switch (temp_v0) {                          /* switch 1; irregular */
        case 2:                                     /* switch 1 */
            if (M2C_FIELD(temp_s3, s8 *, 0x1D) != 0xE) {
                TocarSonido(7, 0, 0x2A, 0x7F);
                switch (nivel_actual) {             /* switch 2 */
                case 1:                             /* switch 2 */
                    sp74 = 0x8C;
                    var_s7 = 0xD8;
                    var_s6 = 0xE8;
                    break;
                case 2:                             /* switch 2 */
                    sp74 = 0x8C;
                    var_s7 = 0xD8;
                    var_s6 = 0xE8;
                    break;
                case 3:                             /* switch 2 */
                    sp74 = 0xFF;
                    var_s7 = 0x8C;
                    var_s6 = 0;
                    break;
                case 4:                             /* switch 2 */
                    sp74 = 0x8C;
                    var_s7 = 0xD8;
                    var_s6 = 0xE8;
                    break;
                case 5:                             /* switch 2 */
                    sp74 = 0x8C;
                    var_s7 = 0xD8;
                    var_s6 = 0xE8;
                    break;
                case 6:                             /* switch 2 */
                    sp74 = 0x8C;
                    var_s7 = 0xD8;
                    var_s6 = 0xE8;
                    break;
                case 7:                             /* switch 2 */
                    sp74 = 0x8C;
                    var_s7 = 0xD8;
                    var_s6 = 0xE8;
                    break;
                case 8:                             /* switch 2 */
                    sp74 = 0x8C;
                    var_s7 = 0xD8;
                    var_s6 = 0xE8;
                    break;
                case 9:                             /* switch 2 */
                    sp74 = 0x8C;
                    var_s7 = 0xD8;
                    var_s6 = 0xE8;
                    break;
                case 10:                            /* switch 2 */
                    sp74 = 0xB4;
                    var_s7 = 0xB0;
block_28:
                    var_s6 = 0x7C;
                    break;
                case 11:                            /* switch 2 */
                    sp74 = 0xB4;
                    var_s7 = 0xB0;
                    goto block_28;
                case 12:                            /* switch 2 */
                    sp74 = 0xB4;
                    var_s7 = 0xB0;
                    goto block_28;
                default:                            /* switch 2 */
                    sp74 = 0xB4;
                    var_s7 = 0xB0;
                    goto block_28;
                }
                var_fp = 0;
loop_33:
                if (var_fp < 0x10) {
                    temp_s5 = func_80021CE4(0x3333);
                    temp_s5_2 = temp_s5 - func_80021CE4(0x1999);
                    temp_s4 = func_80021CE4(0x3333);
                    temp_v0_2 = CrearParticula(0xC, 0, 0, M2C_FIELD(arg0, s32 *, 0x24), /* extra? */ M2C_FIELD(arg0, s32 *, 0x28), /* extra? */ M2C_FIELD(arg0, s32 *, 0x2C), /* extra? */ temp_s5_2, /* extra? */ -0x1999, /* extra? */ (temp_s4 - func_80021CE4(0x1999)), /* extra? */ 0, /* extra? */ 0x28F, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0, /* extra? */ 0);
                    if (temp_v0_2 != 0) {
                        M2C_FIELD(temp_v0_2, s32 *, 0x3C) = 0x112;
                        M2C_FIELD(temp_v0_2, s8 *, 0x1C) = (s8) sp74;
                        M2C_FIELD(temp_v0_2, s8 *, 0x1D) = var_s7;
                        M2C_FIELD(temp_v0_2, s8 *, 0x1E) = var_s6;
                    }
                    var_fp += 1;
                    goto loop_33;
                }
                M2C_FIELD(temp_s3, s16 *, 0x18) = 0;
                M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(sp6C, u16 *, 0x24);
                M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x1000;
                M2C_FIELD(temp_s0, s8 *, 0x51) = (s8) M2C_FIELD(sp70, u16 *, 0x24);
                M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
                M2C_FIELD(temp_s3, s8 *, 0x1D) = 0xE;
                M2C_FIELD(arg0, s8 *, 0x118) = (s8) (M2C_FIELD(arg0, s8 *, 0x118) - 1);
                vida_barra = M2C_FIELD(arg0, s8 *, 0x118);
                ActualizarBarraVida();
                if ((M2C_FIELD(arg0, s8 *, 0x118) <= 0) && (M2C_FIELD(arg0, s16 *, 0x70) != 2)) {
                    M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(sp6C, u16 *, 0);
                    M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
                    M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x1000;
                    M2C_FIELD(temp_s0, s8 *, 0x51) = (s8) M2C_FIELD(sp70, u16 *, 0);
                    M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                    M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
                    M2C_FIELD(temp_s3, s8 *, 0x1A) = -1;
                    M2C_FIELD(temp_s3, s8 *, 0x1B) = -1;
block_64:
                    M2C_FIELD(arg0, s16 *, 0x70) = 2;
                }
            }
            break;
        case 4:                                     /* switch 1 */
            if (M2C_FIELD(temp_s3, s8 *, 0x1D) != 0xE) {
                TocarSonido(7, 0, 0x2A, 0x7F);
                switch (nivel_actual) {             /* switch 3 */
                case 1:                             /* switch 3 */
                    sp74 = 0x8C;
                    var_s7_2 = 0xD8;
                    var_s6_2 = 0xE8;
                    break;
                case 2:                             /* switch 3 */
                    sp74 = 0x8C;
                    var_s7_2 = 0xD8;
                    var_s6_2 = 0xE8;
                    break;
                case 3:                             /* switch 3 */
                    sp74 = 0xFF;
                    var_s7_2 = 0x8C;
                    var_s6_2 = 0;
                    break;
                case 4:                             /* switch 3 */
                    sp74 = 0x8C;
                    var_s7_2 = 0xD8;
                    var_s6_2 = 0xE8;
                    break;
                case 5:                             /* switch 3 */
                    sp74 = 0x8C;
                    var_s7_2 = 0xD8;
                    var_s6_2 = 0xE8;
                    break;
                case 6:                             /* switch 3 */
                    sp74 = 0x8C;
                    var_s7_2 = 0xD8;
                    var_s6_2 = 0xE8;
                    break;
                case 7:                             /* switch 3 */
                    sp74 = 0x8C;
                    var_s7_2 = 0xD8;
                    var_s6_2 = 0xE8;
                    break;
                case 8:                             /* switch 3 */
                    sp74 = 0x8C;
                    var_s7_2 = 0xD8;
                    var_s6_2 = 0xE8;
                    break;
                case 9:                             /* switch 3 */
                    sp74 = 0x8C;
                    var_s7_2 = 0xD8;
                    var_s6_2 = 0xE8;
                    break;
                case 10:                            /* switch 3 */
                    sp74 = 0xB4;
                    var_s7_2 = 0xB0;
block_53:
                    var_s6_2 = 0x7C;
                    break;
                case 11:                            /* switch 3 */
                    sp74 = 0xB4;
                    var_s7_2 = 0xB0;
                    goto block_53;
                case 12:                            /* switch 3 */
                    sp74 = 0xB4;
                    var_s7_2 = 0xB0;
                    goto block_53;
                default:                            /* switch 3 */
                    sp74 = 0xB4;
                    var_s7_2 = 0xB0;
                    goto block_53;
                }
                var_fp_2 = 0;
loop_58:
                if (var_fp_2 < 0x10) {
                    temp_s5_3 = func_80021CE4(0x3333);
                    temp_s5_4 = temp_s5_3 - func_80021CE4(0x1999);
                    temp_s4_2 = func_80021CE4(0x3333);
                    temp_v0_3 = CrearParticula(0xC, 0, 0, M2C_FIELD(arg0, s32 *, 0x24), /* extra? */ M2C_FIELD(arg0, s32 *, 0x28), /* extra? */ M2C_FIELD(arg0, s32 *, 0x2C), /* extra? */ temp_s5_4, /* extra? */ -0x1999, /* extra? */ (temp_s4_2 - func_80021CE4(0x1999)), /* extra? */ 0, /* extra? */ 0x28F, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0, /* extra? */ 0);
                    if (temp_v0_3 != 0) {
                        M2C_FIELD(temp_v0_3, s32 *, 0x3C) = 0x112;
                        M2C_FIELD(temp_v0_3, s8 *, 0x1C) = (s8) sp74;
                        M2C_FIELD(temp_v0_3, s8 *, 0x1D) = var_s7_2;
                        M2C_FIELD(temp_v0_3, s8 *, 0x1E) = var_s6_2;
                    }
                    var_fp_2 += 1;
                    goto loop_58;
                }
                M2C_FIELD(temp_s3, s16 *, 0x18) = 0;
                M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(sp6C, u16 *, 0x24);
                M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x1000;
                M2C_FIELD(temp_s0, s8 *, 0x51) = (s8) M2C_FIELD(sp70, u16 *, 0x24);
                M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
                M2C_FIELD(temp_s3, s8 *, 0x1D) = 0xE;
                M2C_FIELD(arg0, s8 *, 0x118) = (s8) (M2C_FIELD(arg0, s8 *, 0x118) - 1);
                vida_barra = M2C_FIELD(arg0, s8 *, 0x118);
                ActualizarBarraVida();
                if ((M2C_FIELD(arg0, s8 *, 0x118) <= 0) && (M2C_FIELD(arg0, s16 *, 0x70) != 2)) {
                    M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(sp6C, u16 *, 0);
                    M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
                    M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x1000;
                    M2C_FIELD(temp_s0, s8 *, 0x51) = (s8) M2C_FIELD(sp70, u16 *, 0);
                    M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                    M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
                    M2C_FIELD(temp_s3, s8 *, 0x1A) = -1;
                    M2C_FIELD(temp_s3, s8 *, 0x1B) = -1;
                    goto block_64;
                }
            }
            break;
        case 8:                                     /* switch 1 */
            if (M2C_FIELD(arg0, s16 *, 0x70) != 2) {
                M2C_FIELD(temp_s2, s8 *, 0x51) = (s8) M2C_FIELD(sp6C, u16 *, 0);
                M2C_FIELD(temp_s2, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s2, s16 *, 0x4E) = 0x1000;
                M2C_FIELD(temp_s0, s8 *, 0x51) = (s8) M2C_FIELD(sp70, u16 *, 0);
                M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x1000;
                M2C_FIELD(temp_s3, s8 *, 0x1A) = -1;
                M2C_FIELD(temp_s3, s8 *, 0x1B) = -1;
                goto block_64;
            }
            break;
        }
    } else {
    case 1:                                         /* switch 1 */
    }
}
