#include "juego.h"

/* Los creditos: suben de a dos lineas por paso; se ven seis renglones a la vez. */

extern u16 D_80075708[];             /* la altura de cada renglon de los creditos */
extern u16 *D_800798BC[];            /* los textos de pantalla (en +2 la y) */
extern s8 *D_80079D48[];
extern u16 D_8007CA14;               /* 1 mientras pasan */
extern s16 D_8007CA20;
extern s32 D_8007CA58;               /* botones recien apretados */
extern u16 D_8007CC08;               /* cuanto subieron */
extern u16 D_8007CC0A;               /* el primer renglon a la vista */

/* Un paso de los creditos: copia los seis renglones a la vista (desde el 0x67 + el primero) a los textos
 * 0x5F a 0x64 con su altura. Terminan tras el renglon 0x60 o con el boton 0x40. Devuelve el boton. */
s32 func_80047064(void) {
    s32 k, desde, hasta, i;

    if (D_8007CA14 == 0) {
        D_8007CC08 = 0;
        D_8007CC0A = 0;
        D_8007CA58 = 0;
    }
    D_8007CA14 = 1;
    D_8007CA20 = 0x5F;
    if ((s32)D_80075708[D_8007CC0A] - (s32)D_8007CC08 < 0) {
        D_8007CC0A++;
        if (D_8007CC0A >= 0x61) {
            D_8007CA14 = 0;
        }
    }
    k = D_8007CC0A;
    desde = k + 0x67;
    D_8007CC08 += 2;
    hasta = 0x5F;
    for (i = 0; i != 6; i++) {
        D_800798BC[hasta] = D_800798BC[desde];
        D_80079D48[hasta] = D_80079D48[desde];
        D_800798BC[hasta][1] = D_80075708[k + i] - D_8007CC08;
        hasta++;
        desde++;
    }
    if (D_8007CA58 & 0x40) {
        D_8007CA14 = 0;
    }
    return D_8007CA58 & 0x40;
}
