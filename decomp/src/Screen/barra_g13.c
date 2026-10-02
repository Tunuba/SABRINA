#include "juego.h"

/* La barra que se llena mientras corre la cuenta (jugando + 2): un rectangulo de color en (0x97, 0xB0) que
   crece de a 1 hasta 30 por paso de D_8007CAE8, y la cuenta se corta al llegar a 0xD2. */

extern s16 jugando;
extern u8 D_8007CAE6[];         /* [0] cuadros, [1] el ancho de la barra */
extern u8 D_8007CAE8;           /* pasos hechos */
extern u16 D_8007CAEA, D_8007CAEC, D_8007CAEE;   /* el color */
extern s16 D_8007CC48;
extern u8 *D_8007CAD4;          /* el rectangulo (TILE) */
extern s32 func_80013090(u8 *prim);

s32 func_800211D4(void) {
    u16 *cuenta = (u16 *)&jugando + 1;
    D_8007CAE6[0]++;
    D_8007CC48 = SUMA_TRAMPA(D_8007CC48, 1);
    if (*cuenta == 0) {
        D_8007CAE8 = 0;
        D_8007CAE6[1] = 0;
        return 0;
    }
    if ((s32)D_8007CAE6[1] < RESTA_TRAMPA(D_8007CAE8 * 16, D_8007CAE8) * 2) {
        D_8007CAE6[1]++;
    }
    if (D_8007CAE6[1] >= 0xD2) {
        *cuenta = 0;
    }
    D_8007CAD4[4] = D_8007CAEA;
    D_8007CAD4[5] = D_8007CAEC;
    D_8007CAD4[6] = D_8007CAEE;
    *(s16 *)(D_8007CAD4 + 8) = 0x97;
    *(s16 *)(D_8007CAD4 + 0xA) = 0xB0;
    *(s16 *)(D_8007CAD4 + 0xC) = D_8007CAE6[1];
    *(s16 *)(D_8007CAD4 + 0xE) = 0xF;
    return func_80013090(D_8007CAD4);
}
