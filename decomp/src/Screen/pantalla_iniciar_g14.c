#include "juego.h"

/* Preparar la pantalla: los entornos de dibujo y de video de las dos paginas. */

extern u8 D_8007CCBC[0x5C];          /* entorno de dibujo de la pagina 0 */
extern u8 D_8007CD18[0x5C];          /* entorno de dibujo de la pagina 1 */
extern u8 D_8007CD74[0x14];          /* entorno de video de la pagina 0 */
extern u8 D_8007CD88[0x14];          /* entorno de video de la pagina 1 */
extern u8 D_8007CD9C[];              /* la tabla de orden */
extern s16 D_8007C9E0[4];            /* un rectangulo de toda la VRAM usada */
extern u8 *D_8007C9E8;               /* la tabla de orden en uso */
extern s16 D_8007C9EC;               /* la pagina en uso */
extern void *memset(void *p, s32 c, s32 n);
extern void SetDefDrawEnv(u8 *e, s32 x, s32 y, s32 w, s32 h);
extern void SetDefDispEnv(u8 *e, s32 x, s32 y, s32 w, s32 h);
extern void func_80021120(u32 xy, u32 wh);   /* limpiar un rectangulo (pasado por valor) */
extern void func_8001315C(u8 *e);            /* PutDrawEnv */
extern void func_8001321C(u8 *e);            /* PutDispEnv */
extern s32 func_80012FE4(u8 *ot, s32 n);     /* ClearOTagR */

/* Dos paginas de 512x220 (una en y = 0 y otra en y = 220) con la pantalla corrida 10 abajo, 256 de alto,
 * borrado de fondo en la pagina 1; limpia la VRAM, pone la pagina 0 para dibujar y la 1 para mostrar, y
 * limpia la tabla de orden. */
s32 func_800213A0(void) {
    memset(D_8007CCBC, 0, 0x5C);
    memset(D_8007CD18, 0, 0x5C);
    SetDefDrawEnv(D_8007CCBC, 0, 0, 0x200, 0xDC);
    SetDefDrawEnv(D_8007CD18, 0, 0xDC, 0x200, 0xDC);
    SetDefDispEnv(D_8007CD74, 0, 0xDC, 0x200, 0xDC);
    SetDefDispEnv(D_8007CD88, 0, 0, 0x200, 0xDC);
    *(s16 *)(D_8007CD88 + 8) = 0;
    *(s16 *)(D_8007CD74 + 8) = 0;
    D_8007C9E0[0] = 0;
    *(s16 *)(D_8007CD88 + 0xA) = 0xA;
    *(s16 *)(D_8007CD74 + 0xA) = 0xA;
    *(s16 *)(D_8007CD88 + 0xC) = 0x100;
    *(s16 *)(D_8007CD74 + 0xC) = 0x100;
    *(s16 *)(D_8007CD88 + 0xE) = 0xDC;
    *(s16 *)(D_8007CD74 + 0xE) = 0xDC;
    D_8007CD18[0x18] = 0;
    D_8007CCBC[0x18] = 0;
    D_8007CD18[0x17] = 0;
    D_8007CCBC[0x17] = 0;
    D_8007CD18[0x16] = 1;
    D_8007CCBC[0x16] = 1;
    D_8007C9E0[1] = 0;
    D_8007C9E0[2] = 0x400;
    D_8007C9E0[3] = 0x1B8;
    func_80021120(*(u32 *)&D_8007C9E0[0], *(u32 *)&D_8007C9E0[2]);
    func_8001315C(D_8007CCBC);
    func_8001321C(D_8007CD88);
    D_8007C9E8 = D_8007CD9C;
    D_8007C9EC = 0;
    return func_80012FE4(D_8007C9E8, 0x400);
}
