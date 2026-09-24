#include "juego.h"

/* Zonas del nivel. Cada celda de la cuadricula (64 de ancho, 12 bytes cada una) dice en +8 a que zona
 * pertenece. BitDeZona mira la celda y sus ocho vecinas, cuenta cuantas caen en cada zona y devuelve la
 * zona que mas se repite como un bit: zona 0 -> 0, zona n -> 1 << (n - 1). */

typedef struct {
    u8 _00[8];
    s32 zona;                        /* 0x08 */
} CeldaZona;

extern CeldaZona *D_8007CA48;        /* celdas de zona del nivel */
extern u16 D_8008AF38[9];            /* zona de la celda y de sus ocho vecinas */
extern s8 D_8008AF4C[17];            /* cuantas vecinas hay en cada zona */
extern char D_800688E8[];            /* nombre del archivo fuente, para Afirmar */

extern void memset(void *p, s32 c, s32 n);
extern s32 Afirmar(s32 cond, char *archivo, s32 linea);
extern void func_80020818(s8 *cuentas, s32 zona);   /* suma uno a la cuenta de esa zona */

s32 BitDeZona(s32 celda) {
    CeldaZona *c = D_8007CA48;
    s32 i;
    s32 mejor;
    s32 zona;

    D_8008AF38[0] = c[celda].zona;
    D_8008AF38[1] = c[celda + 1].zona;
    D_8008AF38[2] = c[celda - 1].zona;
    D_8008AF38[3] = c[celda - 63].zona;
    D_8008AF38[4] = c[celda - 64].zona;
    D_8008AF38[5] = c[celda - 65].zona;
    D_8008AF38[6] = c[celda + 63].zona;
    D_8008AF38[7] = c[celda + 64].zona;
    D_8008AF38[8] = c[celda + 65].zona;

    mejor = 0;
    zona = 0;
    memset(D_8008AF4C, 0, 17);
    for (i = 0; i < 9; i++) {
        func_80020818(D_8008AF4C, D_8008AF38[i]);
    }
    for (i = 0; i < 17; i++) {
        if (mejor < D_8008AF4C[i]) {
            mejor = D_8008AF4C[i];
            zona = i;
        }
    }

    switch (zona) {
    case 0:  return 0;
    case 1:  return 0x1;
    case 2:  return 0x2;
    case 3:  return 0x4;
    case 4:  return 0x8;
    case 5:  return 0x10;
    case 6:  return 0x20;
    case 7:  return 0x40;
    case 8:  return 0x80;
    case 9:  return 0x100;
    case 10: return 0x200;
    case 11: return 0x400;
    case 12: return 0x800;
    case 13: return 0x1000;
    case 14: return 0x2000;
    case 15: return 0x4000;
    case 16: return 0x8000;
    }
    /* no puede pasar: la zona sale del bucle de 17 */
    return Afirmar(0, D_800688E8, 0xED);
}
