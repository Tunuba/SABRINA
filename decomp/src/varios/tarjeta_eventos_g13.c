#include "juego.h"

/* La tarjeta de memoria en segundo plano: cada cuadro se le da un paso a la funcion puesta con
   UserFuncOpen y, cuando termina, se avisa con la funcion de D_800D52C0 + 0x44. */

extern s32 UserFuncComplete(void);
extern void UserFuncExecute(void);
extern s32 D_800D52C0[];        /* [0], [1] el resultado; [2] terminado; [0x11] el aviso; [0x14], [0x15] cuadros */
extern s32 D_800D52B0[];        /* copia del resultado para el aviso */

/* Un paso por cuadro. Devuelve D_800D52C0 (queda en v0). */
s32 func_80050828(void) {
    void (*aviso)(s32, s32, void *);
    if (UserFuncComplete() == 0) {
        UserFuncExecute();
        if (UserFuncComplete() != 0) {
            D_800D52C0[2] = 1;
            D_800D52B0[0] = D_800D52C0[0];
            D_800D52B0[1] = D_800D52C0[1];
            aviso = (void (*)(s32, s32, void *))D_800D52C0[0x11];
            D_800D52C0[0] = 0;
            D_800D52C0[1] = 0;
            if (aviso != NULL) {
                aviso(D_800D52B0[0], D_800D52B0[1], aviso);
            }
        }
    }
    D_800D52C0[0x14]++;
    D_800D52C0[0x15]++;
    return (s32)D_800D52C0;
}
