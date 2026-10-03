#include "juego.h"

/* La atencion de la interrupcion del lector de CD (libcd de PsyQ). */

extern volatile u8 *D_8006D2B0;      /* registro de indice / estado */
extern volatile u8 *D_8006D2B4;      /* respuesta */
extern volatile u8 *D_8006D2B8;      /* reconocer interrupciones (indice 1) */
extern volatile u8 *D_8006D2BC;      /* tipo de interrupcion / mascara */
extern u8 D_8006D2C8[3];             /* estados: fin de orden, datos listos, fin de datos */
extern u8 D_8006D321;                /* la ultima orden */
extern s32 D_8006D0B0[];             /* por orden: si responde en dos pasos (acuse y despues completa) */
extern s32 D_8006D1B0[];             /* por orden: si el acuse trae estado */
extern s32 D_8006D30C;               /* nivel de depuracion */
extern s32 D_8006D310;               /* el ultimo estado del lector */
extern s32 D_8006D314;
extern s32 D_8006D318;               /* veces que se abrio la tapa */
extern char *D_8006D328[];           /* nombres de las ordenes */
extern u8 D_80091448[8];             /* la ultima respuesta de fin de orden */
extern u8 D_80091450[8];             /* la ultima respuesta de datos listos */
extern u8 D_80091458[8];             /* la ultima respuesta de fin de datos */
extern char D_800613AC[], D_800613B8[], D_800613D4[], D_800613E8[];
extern s32 printf(char *fmt, ...);
extern s32 puts(char *s);

static inline void copiar8(u8 *a, u8 *de) {
    s32 k;
    for (k = 7; k != -1; k--) {
        *a++ = *de++;
    }
}

/* Lee el tipo de interrupcion (hasta que dos lecturas coincidan) y la respuesta (hasta 8 bytes), las
 * reconoce, anota el estado del lector y deja el resultado en el estado que toca. Devuelve que paso: 0 nada
 * (o tipo desconocido), 1 acuse de una orden en dos pasos, 2 orden completa, 4 datos listos o fin de datos,
 * 6 error de disco. */
s32 func_8002A09C(void) {
    u8 r[8];
    u8 tipo;
    s32 err = 0;
    s32 n, k;

    *D_8006D2B0 = 1;
    tipo = *D_8006D2BC & 7;
    if (tipo == 0) {
        return 0;
    }
    while (tipo != (*D_8006D2BC & 7)) {
        tipo = *D_8006D2BC & 7;
    }
    for (n = 0; n < 8; ) {
        if (!(*D_8006D2B0 & 0x20)) {
            break;
        }
        r[n] = *D_8006D2B4;
        n++;
    }
    for (k = n; k < 8; k++) {
        r[k] = 0;
    }
    *D_8006D2B0 = 1;
    *D_8006D2BC = 7;
    *D_8006D2B8 = 7;
    if (tipo != 3 || D_8006D1B0[D_8006D321] != 0) {
        if (!(D_8006D310 & 0x10) && (r[0] & 0x10)) {
            D_8006D318++;
        }
        D_8006D310 = r[0];
        D_8006D314 = r[1];
        err = r[0] & 0x1D;
    }
    if (tipo == 5 && D_8006D30C > 0) {
        printf(D_800613AC);
        if (D_8006D30C > 0) {
            printf(D_800613B8, D_8006D328[D_8006D321], D_8006D310, D_8006D314);
        }
    }
    switch (tipo) {
    case 3:
        if (err != 0) {
            D_8006D2C8[0] = 5;
            copiar8(D_80091448, r);
            return 2;
        }
        if (D_8006D0B0[D_8006D321] != 0) {
            D_8006D2C8[0] = 3;
            copiar8(D_80091448, r);
            return 1;
        }
        D_8006D2C8[0] = 2;
        copiar8(D_80091448, r);
        return 2;
    case 2:
        D_8006D2C8[0] = err != 0 ? 5 : 2;
        copiar8(D_80091448, r);
        return 2;
    case 1:
        if (err != 0 && n == 1) {
            err = 0;
        }
        D_8006D2C8[1] = err != 0 ? 5 : 1;
        copiar8(D_80091450, r);
        *D_8006D2B0 = 0;
        *D_8006D2BC = 0;
        return 4;
    case 4:
        D_8006D2C8[2] = 4;
        D_8006D2C8[1] = D_8006D2C8[2];
        copiar8(D_80091458, r);
        copiar8(D_80091450, r);
        return 4;
    case 5:
        D_8006D2C8[1] = 5;
        D_8006D2C8[0] = D_8006D2C8[1];
        copiar8(D_80091448, r);
        copiar8(D_80091450, r);
        return 6;
    default:
        puts(D_800613D4);
        printf(D_800613E8, tipo);
        return 0;
    }
}
