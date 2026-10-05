#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"
/* 05-10: copia del borrador de m2c (src/auto/func_80050034.c) con el puerto en _card_info / _card_load, que el borrador
 * llamaba sin argumentos (prototipos.h las declara void) y pasaba porque el modelo de la BIOS no los miraba; ahora
 * verificar.py compara los argumentos (ARGS_BIOS). El alias en asm evita chocar con esa declaracion. */
extern void tarjeta_info(s32 puerto) __asm__("_card_info");
extern void tarjeta_cargar(s32 puerto) __asm__("_card_load");

extern s32 D_800D5298;
extern s32 D_800D529C;
extern s32 D_800D52A0;
extern s32 D_800D52A4;
extern s32 D_800D52A8;
extern u8 D_800D52C0[];
extern u8 D_800D52C4[];
extern s32 func_8004FD34();

s32 func_80050034(u32 *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_v1;
    u32 temp_v1;
    u32 var_v0;

    temp_v1 = *arg0;
    switch (temp_v1) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        D_800D529C = 0;
        D_800D52A0 = 0;
        D_800D5298 = 0;
        D_800D52A8 = 0;
        D_800D52A4 = 0;
        *arg0 += 1;
        /* fallthrough */
    case 1:                                         /* switch 1 */
        UserFuncOpen((s32) func_8004FD34);
        var_v0 = 0xA;
block_33:
        *arg0 = var_v0;
    default:                                        /* switch 1 */
block_34:
        return 0;
    case 10:                                        /* switch 1 */
        switch (M2C_FIELD(D_800D52C4, s32 *, 0)) {  /* switch 2; irregular */
        case 3:                                     /* switch 2 */
            D_800D52A8 = 1;
            M2C_FIELD((D_800D52C4 - 4), s32 *, 0xC) = (s32) (M2C_FIELD(D_800D52C4, s32 *, 8) | (1 << M2C_FIELD(D_800D52C4, s32 *, 0xC)));
            func_80051D14();
            _card_clear(M2C_FIELD(D_800D52C4, s32 *, 0xC));
            var_v0 = 0x15;
            goto block_33;
        case 0:                                     /* switch 2 */
            var_v0 = 0x1E;
            goto block_33;
        case 1:                                     /* switch 2 */
block_25:
            return 1;
        default:                                    /* switch 2 */
            return 1;
        }
        break;
    case 21:                                        /* switch 1 */
        if (func_80052008() != 0) {
            func_80051EF4();
            *arg0 = 0x1E;
        case 30:                                    /* switch 1 */
            func_80051D14();
            tarjeta_cargar(M2C_FIELD(D_800D52C4, s32 *, 0xC));
            var_v0 = *arg0 + 1;
            goto block_33;
        }
        goto block_34;
    case 31:                                        /* switch 1 */
        if (func_80051FCC() != 0) {
            temp_v0 = func_80051E1C();
            D_800D52A4 = temp_v0;
            switch (temp_v0) {                      /* switch 3; irregular */
            case 0:                                 /* switch 3 */
                var_v1 = 0;
                if (D_800D52A8 != 0) {
                    var_v1 = 3;
                }
                M2C_FIELD(D_800D52C0, s32 *, 4) = var_v1;
                goto block_25;
            case 4:                                 /* switch 3 */
                func_80051D14();
                tarjeta_info(M2C_FIELD(D_800D52C4, s32 *, 0xC));
                var_v0 = 0x32;
                goto block_33;
            case 2:                                 /* switch 3 */
                *arg0 = 1;
                goto block_34;
            case 1:                                 /* switch 3 */
                temp_v0_2 = D_800D529C + 1;
                D_800D529C = temp_v0_2;
                var_v0 = 0x1E;
                if (temp_v0_2 >= 9) {
                default:                            /* switch 3 */
                    M2C_FIELD(D_800D52C0, s32 *, 4) = func_800507D4(D_800D52A4);
                    return 1;
                }
                goto block_33;
            }
        } else {
            /* Duplicate return node #35. Try simplifying control flow for better match */
            return 0;
        }
        break;
    case 50:                                        /* switch 1 */
        if (func_80051FCC() != 0) {
            temp_v0_3 = func_80051E1C();
            D_800D52A4 = temp_v0_3;
            var_v0 = 1;
            if (temp_v0_3 == 0) {
                M2C_FIELD(D_800D52C0, s32 *, 4) = 4;
                return 1;
            }
            goto block_33;
        }
        /* Duplicate return node #35. Try simplifying control flow for better match */
        return 0;
    }
}
