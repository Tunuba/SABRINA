#include "juego.h"

/* Un cuadro de pantalla sin camara: borra, dibuja los dos modelos sueltos y el texto. */

typedef struct {
    s16 x, y, w, h;
} RectC;

extern RectC D_8007C804;             /* lo que se borra */
extern void *D_8007C9E8;             /* la tabla de orden de este cuadro */
extern void *D_8007C9F0, *D_8007C9F4;
extern s32 func_80021120(RectC r);
extern void func_8001FD50(void *modelo, void *ot, s32 c);
extern void DibujarTexto(void *ot, s32 n);
extern s32 func_800218D4(void);      /* cierra el cuadro y lo muestra */

s32 func_80021A30(void) {
    func_80021120(D_8007C804);
    func_8001FD50(D_8007C9F0, D_8007C9E8, 0);
    func_8001FD50(D_8007C9F4, D_8007C9E8, 0);
    DibujarTexto(D_8007C9E8, 0x5D);
    func_800218D4();
    return func_800218D4();
}
