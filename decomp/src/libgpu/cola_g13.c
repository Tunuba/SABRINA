#include "juego.h"

/* libgpu: la cola de ordenes de dibujo (64 lugares de 0x60 bytes: la funcion y sus dos argumentos) que se
   va vaciando desde la interrupcion de la GPU. */

extern volatile u32 *D_80063754;     /* el registro de estado de la GPU */
extern volatile u32 *D_80063760;     /* el registro de control del DMA de la GPU */
extern s32 D_80063778;               /* lo que devolvio func_80016A14 al entrar */
extern s32 D_80063818;               /* donde se agrega */
extern s32 D_8006381C;               /* donde se saca */
extern s32 D_800637A4;
extern s32 D_800637A0[2];            /* [0] hay aviso, [1] la funcion de aviso */
extern u8 D_80083300[], D_80083304[], D_80083308[];   /* la cola */
extern s32 func_80016A14(s32 x);
extern s32 func_80016970(s32 canal, s32 f);

/* Despacha lo que haya en la cola mientras el DMA este libre; al vaciarla llama al aviso (con su propia
   direccion). Devuelve cuantas quedan (1 si el DMA estaba ocupado al entrar). */
s32 func_800123E0(void) {
    void (*aviso)(void *);

    if (*D_80063760 & 0x01000000) {
        return 1;
    }
    D_80063778 = func_80016A14(0);
    if (D_80063818 != D_8006381C && !(*D_80063760 & 0x01000000)) {
        do {
            if (((D_8006381C + 1) & 0x3F) == D_80063818 && D_800637A4 == 0) {
                func_80016970(2, 0);
            }
            while (!(*D_80063754 & 0x04000000)) {
            }
            (*(void (**)(s32, s32))(D_80083300 + D_8006381C * 0x60))(*(s32 *)(D_80083304 + D_8006381C * 0x60),
                                                                      *(s32 *)(D_80083308 + D_8006381C * 0x60));
            D_8006381C = (D_8006381C + 1) & 0x3F;
        } while (D_80063818 != D_8006381C && !(*D_80063760 & 0x01000000));
    }
    func_80016A14(D_80063778);
    if (D_80063818 == D_8006381C && !(*D_80063760 & 0x01000000) && D_800637A0[0] != 0 &&
        (aviso = (void (*)(void *))D_800637A0[1]) != NULL) {
        D_800637A0[0] = 0;
        aviso((void *)aviso);
    }
    return (D_80063818 - D_8006381C) & 0x3F;
}
