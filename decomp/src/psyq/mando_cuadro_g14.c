#include "juego.h"

/* libpad: la parte de cada cuadro (VBlank) del protocolo del mando. */

extern volatile u8 *D_8006CF70;      /* el puerto serie del mando (0x1F801040) */
extern s32 D_8006CF74;               /* paso un cuadro */
extern s32 D_800909E8;               /* cuadros de cada puerto sin respuesta (tope 150) */
extern s32 D_800909EC;
extern s32 D_8006CFB8;               /* los buferes de los mandos (0xF0 cada uno) */
extern s32 D_8006CFBC;               /* hay que hablar con los mandos */
extern s32 D_8006CFC4;               /* el mando que toca */
extern s32 D_8006CFC8;
extern s32 D_8006CFCC;
extern s32 D_8006CFD4;               /* el primer mando */
extern s32 D_8006CFD8;               /* el ultimo */
extern void (*D_8006CF84)(s32);

extern s32 func_80025EF8(s32 bufer);
extern void func_80025BA0(s32 bufer);

#define SIO16(d) (*(volatile u16 *) (D_8006CF70 + (d)))

/* Si el puerto tiene la orden pendiente (bit 1 del control), solo la borra. Si no, cuenta el cuadro y, si
 * toca, habla con cada mando del primero al ultimo y deja la velocidad del puerto en 0x88. Devuelve 0. */
s32 func_80025A10(void) {
    if (SIO16(0xA) & 2) {
        SIO16(0xA) = 0;
        return 0;
    }
    D_8006CF74 = 1;
    if (D_8006CFD4 != 0 && D_800909E8 < 0x96) {
        D_800909E8++;
    }
    if (D_8006CFD8 == 0 && D_800909EC < 0x96) {
        D_800909EC++;
    }
    if (D_8006CFBC == 0 || D_8006CFD8 < D_8006CFD4) {
        return 0;
    }
    D_8006CFC8 = 0;
    D_8006CFC4 = D_8006CFD4;
    if (func_80025EF8(D_8006CFB8 + D_8006CFD4 * 0xF0) == 0) {
        D_8006CF84(0xFFFF);
    }
    D_8006CFCC = 0;
    while (D_8006CFD8 >= D_8006CFC4) {
        func_80025BA0(D_8006CFB8 + D_8006CFC4 * 0xF0);
    }
    SIO16(0xE) = 0x88;
    return 0;
}
