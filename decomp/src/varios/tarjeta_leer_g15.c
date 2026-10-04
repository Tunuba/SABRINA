#include "juego.h"

/* Un paso de la lectura de la tarjeta de memoria, como maquina de estados en *estado: en 0 pone los reintentos
 * en 0; en 0 o 10 se posiciona y lanza la lectura (y pasa a 30); en 30, si la tarjeta ya contesto
 * (func_80051FCC), mira el resultado: con error reintenta desde 10 hasta 4 veces y si no, o si salio bien,
 * guarda lo que da func_800507D4 en D_800D52C0[1] y devuelve 1 (terminado). */

typedef struct {
    s32 archivo;                        /* 0x0 */
    s32 desde;                          /* 0x4 */
    s32 n;                              /* 0x8 */
    void *destino;                      /* 0xC */
} LecturaTarjeta;

extern s32 D_800D52C0[];
extern LecturaTarjeta D_800D52D4;
extern s32 D_80075B2C;                  /* reintentos */

extern s32 lseek(s32 archivo, s32 desde, s32 modo);
extern s32 read(s32 archivo, void *destino, s32 n);
extern void func_80051D14(void);
extern s32 func_80051FCC(void);
extern s32 func_80051E1C(void);
extern s32 func_800507D4(s32 error);

s32 func_800502DC(s32 *estado) {
    s32 error;

    switch (*estado) {
    case 0:
        D_80075B2C = 0;
        *estado = 10;
        /* sigue */
    case 10:
        while (lseek(D_800D52D4.archivo, D_800D52D4.desde, 0) != D_800D52D4.desde) {
        }
        func_80051D14();
        while (read(D_800D52D4.archivo, D_800D52D4.destino, D_800D52D4.n) != 0) {
        }
        *estado = 30;
        return 0;
    case 30:
        if (func_80051FCC() == 0) {
            return 0;
        }
        error = func_80051E1C();
        if (error != 0 && ++D_80075B2C < 4) {
            *estado = 10;
            return 0;
        }
        D_800D52C0[1] = func_800507D4(error);
        return 1;
    }
    return 0;
}
