#include "juego.h"

/* La cola de comandos del GPU de libgpu: encolar (o mandar directo si el GPU esta libre). */

extern volatile u32 *D_80063754;     /* GP1: estado del GPU */
extern volatile u32 *D_80063760;     /* control del DMA del GPU */
extern s32 D_80063774;               /* las interrupciones guardadas */
extern u8 D_80063798[];              /* estado de la cola: 1 = usar la cola, 8 = ocupada, 0xC = esperando */
extern s32 D_80063818;               /* donde se escribe (0 a 63) */
extern s32 D_8006381C;               /* donde se lee */
extern u8 D_80083300[64][0x60];      /* la cola: funcion, datos, parametro y copia de los datos */
extern void func_800128CC(void);     /* preparar la espera */
extern s32 func_80012900(void);      /* se paso el tiempo de espera */
extern s32 func_800123E0(void);      /* atender la cola */
extern s32 func_80016A14(s32 mascara);   /* cambiar la mascara de interrupciones */
extern void func_80016970(s32 n, void *f);   /* DMACallback */

#define Q32(q, d) (*(s32 *)(D_80083300[q] + (d)))

/* Si la cola esta llena espera (atendiendola). Con la cola apagada, o vacia, el DMA libre y nada esperando,
 * llama a f(datos, param) apenas el GPU acepta comandos y devuelve 0. Si no, la encola (copiando tam bytes
 * de datos, si tam no es 0) y devuelve cuantos hay en la cola. -1 si se paso el tiempo. */
s32 func_80012130(void (*f)(void *, s32), u32 *datos, s32 tam, s32 param) {
    s32 k;

    func_800128CC();
    while (((D_80063818 + 1) & 0x3F) == D_8006381C) {
        if (func_80012900() != 0) {
            return -1;
        }
        func_800123E0();
    }
    D_80063774 = func_80016A14(0);
    *(s32 *)(D_80063798 + 8) = 1;
    if (D_80063798[1] == 0 ||
        (D_80063818 == D_8006381C && !(*D_80063760 & 0x1000000) && *(s32 *)(D_80063798 + 0xC) == 0)) {
        while (!(*D_80063754 & 0x4000000)) {
        }
        f(datos, param);
        func_80016A14(D_80063774);
        return 0;
    }
    func_80016970(2, func_800123E0);
    if (tam != 0) {
        for (k = 0; k < tam / 4; k++) {
            *(u32 *)(D_80083300[D_80063818] + 0xC + k * 4) = datos[k];
        }
        Q32(D_80063818, 4) = (s32)(D_80083300[D_80063818] + 0xC);
    } else {
        Q32(D_80063818, 4) = (s32)datos;
    }
    Q32(D_80063818, 8) = param;
    Q32(D_80063818, 0) = (s32)f;
    D_80063818 = (D_80063818 + 1) & 0x3F;
    func_80016A14(D_80063774);
    func_800123E0();
    return (D_80063818 - D_8006381C) & 0x3F;
}
