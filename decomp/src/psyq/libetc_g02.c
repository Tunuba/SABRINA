#include "juego.h"

/* Interrupciones de libetc (biblioteca de Sony). El juego la trae enlazada tal cual. */

int printf(const char *formato, ...);

typedef s32 (*FuncCallback)(void);

/* Tabla de funciones del modulo de interrupciones: +0x0C ResetCallback, +0x10 StopCallback,
 * +0x14 RestartCallback. */
extern FuncCallback *D_800649A0;
extern FuncCallback D_800649C0[8];      /* funciones que se llaman en cada vuelta de la pantalla */
extern s32 D_800649EC;                  /* cuantas vueltas van */
extern volatile u32 *D_800649F0;        /* DICR, registro de interrupciones de DMA (0x1F8010F4) */
extern FuncCallback D_800649F4[7];      /* una funcion por canal de DMA */
extern u8 *D_80064A14;                  /* registros de DMA (0x1F801080), 16 bytes por canal, MADR en +0 */
extern char D_800610C8[];               /* "DMA bus error: code=%08x\n" */
extern char D_800610E4[];               /* "MADR[%d]=%08x\n" */

/* RestartCallback: pasa a la funcion de la tabla. */
s32 func_800169D4(void) {
    return D_800649A0[5]();
}

/* Cuenta una vuelta y llama a las funciones puestas. Devuelve 0 (lo que queda en v0 al salir del bucle). */
s32 func_80016A2C(void) {
    s32 i;

    D_800649EC++;
    for (i = 0; i < 8; i++) {
        if (D_800649C0[i] != NULL) {
            D_800649C0[i]();
        }
    }
    return 0;
}

/* Atiende la interrupcion de DMA: por cada canal con el bit prendido en DICR (bits 24 a 30) lo apaga y llama
 * a su funcion, hasta que no quede ninguno. Si hay error de bus lo muestra con los MADR. Devuelve 0. */
s32 func_80016B4C(void) {
    u32 pendientes;
    s32 canal;

    pendientes = (*D_800649F0 >> 24) & 0x7F;
    while (pendientes != 0) {
        canal = 0;
        while (pendientes != 0 && canal < 7) {
            if (pendientes & 1) {
                *D_800649F0 &= (1 << (canal + 24)) | 0xFFFFFF;
                if (D_800649F4[canal] != NULL) {
                    D_800649F4[canal]();
                }
            }
            pendientes >>= 1;
            canal++;
        }
        pendientes = (*D_800649F0 >> 24) & 0x7F;
    }
    if ((*D_800649F0 & 0xFF000000) == 0x80000000 || (*D_800649F0 & 0x8000) != 0) {
        printf(D_800610C8, *D_800649F0);
        for (canal = 0; canal < 7; canal++) {
            printf(D_800610E4, canal, *(u32 *)(D_80064A14 + canal * 16));
        }
    }
    return 0;
}
