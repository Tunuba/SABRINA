#include "juego.h"

/* Limpiar la VRAM de la pantalla (las dos paginas). */

extern u16 D_800D581A;               /* modo de video */
extern s32 func_8005D3A0(s32 modo);  /* ancho de la pantalla en ese modo */
extern s32 func_80012DDC(s16 *r, s32 rojo, s32 verde, s32 azul);   /* ClearImage */

/* Pinta de negro un rectangulo del ancho de la pantalla y 256 de alto en y = 0 y despues en y = 256. */
s32 func_8005C964(void) {
    s16 r[4];

    r[0] = 0;
    r[1] = 0;
    r[2] = func_8005D3A0(D_800D581A);
    r[3] = 0x100;
    func_80012DDC(r, 0, 0, 0);
    r[1] = 0x100;
    return func_80012DDC(r, 0, 0, 0);
}
