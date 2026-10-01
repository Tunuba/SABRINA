#include "gpu_g00.h"

/* libgpu: ResetGraph y SetDispMask. */

extern char D_80060B50[];            /* "ResetGraph:jtb=%08x,env=%08x\n" */
extern char D_80060B70[];            /* "ResetGraph(%d)...\n" */
extern char D_80060BE0[];            /* "SetDispMask(%d)...\n" */
extern u8 D_80063688[];              /* la tabla del controlador */
extern u8 D_80063798[0x80];          /* el estado de libgpu (D_8006379A es el nivel de depuracion) */
extern u32 D_800636CC[], D_800636D8[];  /* ancho y alto de la VRAM por modo */
extern s32 printf(const char *f, ...);
s32 func_80012AE4(u8 *p, s32 c, s32 n);
extern void func_80016910(void);
extern void GPU_cw(u32 a);
extern u8 func_80012640(s32 modo);   /* reinicia el GPU, devuelve el tipo de video */

#define CONTROL(off) (*(s32 (**)(s32))((u8 *)D_800636C8 + (off)))

/* ResetGraph: con modo 0 o 3 avisa y reinicia todo (con 5 sin avisar): borra el estado de libgpu, anota el
 * tipo de video y el tamano de la VRAM, y deja sin entorno guardado. Con otro modo solo vacia la cola.
 * Devuelve el tipo de video, o lo que devuelve la cola. */
s32 func_80012B0C(s32 modo) {
    switch (modo & 7) {
    case 0:
    case 3:
        printf(D_80060B50, D_80063688, D_80063798);
        /* sigue */
    case 5:
        func_80012AE4(D_80063798, 0, 0x80);
        func_80016910();
        GPU_cw((u32)D_800636C8 & 0xFFFFFF);
        D_80063798[0] = func_80012640(modo);
        D_80063798[1] = 1;
        *(u16 *)(D_80063798 + 4) = D_800636CC[D_80063798[0]];
        *(u16 *)(D_80063798 + 6) = D_800636D8[D_80063798[0]];
        func_80012AE4(D_80063798 + 0x10, -1, 0x5C);
        func_80012AE4(D_80063798 + 0x6C, -1, 0x14);
        return D_80063798[0];
    default:
        if (D_8006379A.depuracion >= 2) {
            D_80063794(D_80060B70, modo);
        }
        return CONTROL(0x34)(1);
    }
}

/* SetDispMask: 0 apaga la pantalla (y olvida el entorno de la pantalla), otro la prende. */
s32 func_80012CDC(s32 mascara) {
    if (D_8006379A.depuracion >= 2) {
        D_80063794(D_80060BE0, mascara);
    }
    if (mascara == 0) {
        func_80012AE4((u8 *)&D_8006379A + 0x6A, -1, 0x14);
    }
    return CONTROL(0x10)(mascara != 0 ? 0x03000000 : 0x03000001);
}

extern char D_80060B84[];            /* "SetGraphDebug:level:%d,type:%d reverse:%d\n" */

/* SetGraphDebug: pone el nivel de depuracion y devuelve el que habia. */
s32 func_80012C80(s32 nivel) {
    u8 antes = D_8006379A.depuracion;

    D_8006379A.depuracion = nivel;
    if (nivel & 0xFF) {
        D_80063794(D_80060B84, D_8006379A.depuracion, ((u8 *)&D_8006379A)[-2], ((u8 *)&D_8006379A)[1]);
    }
    return antes;
}

/* Llena n bytes desde p con c. Devuelve -1 (lo que queda de la cuenta). */
s32 func_80012AE4(u8 *p, s32 c, s32 n) {
    while (n-- != 0) {
        *p++ = c;
    }
    return -1;
}
