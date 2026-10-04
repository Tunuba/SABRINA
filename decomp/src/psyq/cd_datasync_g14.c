#include "juego.h"

/* CdDataSync (libcd): esperar a que termine el DMA de los datos del CD. */

extern s32 D_80091460;               /* el cuadro en que vence la espera */
extern s32 D_80091464;               /* vueltas de la espera */
extern char *D_80091468;             /* lo que se esta esperando (para el aviso) */
extern char D_8006148C[];            /* "CD_datasync" */
extern char D_80061380[];            /* "CD timeout: " */
extern char D_80061390[];            /* "%s:(%s) Sync=%s, Ready=%s\n" */
extern char *D_8006D328[];           /* los nombres de las ordenes */
extern char *D_8006D3A8[];           /* los nombres de los estados */
extern u8 D_8006D2C8[];              /* [0] fin de orden, [1] datos listos */
extern u8 D_8006D321;                /* la ultima orden */
extern volatile s32 *D_8006D2F4;     /* control del DMA del CD */

extern s32 func_8001626C(s32 modo);  /* VSync */
extern s32 puts(const char *s);
extern s32 printf(const char *f, ...);
extern void func_8002B0AC(void);     /* reiniciar el CD */

/* modo 0 espera; si no, solo pregunta. Devuelve 0 si el DMA termino, 1 si sigue (modo 1) y -1 si vencio la
 * espera (16 segundos o 0x3C0000 vueltas), y entonces avisa y reinicia el CD. */
s32 func_8002B49C(s32 modo) {
    D_80091460 = func_8001626C(-1) + 0x3C0;
    D_80091464 = 0;
    D_80091468 = D_8006148C;
    do {
        if (D_80091460 < func_8001626C(-1) || D_80091464++ > 0x3C0000) {
            puts(D_80061380);
            printf(D_80061390, D_80091468, D_8006D328[D_8006D321], D_8006D3A8[D_8006D2C8[0]],
                   D_8006D3A8[D_8006D2C8[1]]);
            func_8002B0AC();
            return -1;
        }
        if (!(*D_8006D2F4 & 0x01000000)) {
            return 0;
        }
    } while (modo == 0);
    return 1;
}
