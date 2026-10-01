#include "gpu_g00.h"

/* libgpu: PutDispEnv, poner el entorno de la pantalla. */

/* DISPENV de libgpu (0x14 bytes). */
typedef struct {
    RectVram disp;                   /* 0x00, lo que se muestra de la VRAM */
    RectVram screen;                 /* 0x08, donde va en la pantalla de la tele */
    u8 isinter;                      /* 0x10 */
    u8 isrgb24;                      /* 0x11 */
    u8 pal;                          /* 0x12, 1 si la consola es PAL (8: hay que rehacer el rango) */
    u8 pad;
} EntornoPantalla;

typedef s32 (*ComandoGpu)(u32 cmd, ControladorGpu *c);

extern char D_80060CE0[];            /* "PutDispEnv(%08x)...\n" */
extern EntornoPantalla D_80063804;   /* el entorno puesto */
extern u16 D_80063720[];             /* por (pal, ancho): primer y ultimo punto de la tele, de a pares */
extern u8 D_80063748[];              /* por ancho: puntos de la tele por pixel */
extern s32 func_80016E00(void);      /* 1 si la consola es PAL */
extern void *memcpy(void *d, const void *s, u32 n);

#define COMANDO(cmd) ((*(ComandoGpu *)((u8 *)D_800636C8 + 0x10))((cmd), D_800636C8))

/* La clase de ancho de libgpu: 256, 320, 384, 512 o 640. */
static s32 clase_ancho(s32 w) {
    if (w < 0x119) {
        return 0;
    }
    if (w < 0x161) {
        return 1;
    }
    if (w < 0x191) {
        return 2;
    }
    if (w >= 0x231) {
        return 4;
    }
    return 3;
}

EntornoPantalla *func_8001321C(EntornoPantalla *env) {
    u32 modo = 0x08000000;
    s32 c, x1, x2, y1, y2, a, d;

    if (D_8006379A.depuracion >= 2) {
        D_80063794(D_80060CE0, env);
    }
    COMANDO(((env->disp.y & 0x3FF) << 10) | (env->disp.x & 0x3FF) | 0x05000000);
    if (*(s32 *)&D_80063804.isinter != *(s32 *)&env->isinter || D_80063804.disp.x != env->disp.x ||
        D_80063804.disp.y != env->disp.y || D_80063804.disp.w != env->disp.w ||
        D_80063804.disp.h != env->disp.h) {
        env->pal = func_80016E00();
        if (env->pal == 1) {
            modo |= 8;
        }
        if (env->isrgb24 != 0) {
            modo |= 0x10;
        }
        if (env->isinter != 0) {
            modo |= 0x20;
        }
        if (D_8006379A.pad1 != 0) {
            modo |= 0x80;
        }
        if (env->disp.w >= 0x119) {
            if (env->disp.w < 0x161) {
                modo |= 1;
            } else if (env->disp.w < 0x191) {
                modo |= 0x40;
            } else if (env->disp.w < 0x231) {
                modo |= 2;
            } else {
                modo |= 3;
            }
        }
        if (!(env->pal != 0 ? env->disp.h < 0x121 : env->disp.h < 0x101)) {
            modo |= 0x24;
        }
        (*(s32 (**)(u32))((u8 *)D_800636C8 + 0x10))(modo);
        env->pal = 8;
    }
    if (D_80063804.screen.x != env->screen.x || D_80063804.screen.y != env->screen.y ||
        D_80063804.screen.w != env->screen.w || D_80063804.screen.h != env->screen.h || env->pal == 8) {
        env->pal = func_80016E00();
        y1 = env->pal != 0 ? env->screen.y + 0x13 : env->screen.y + 0x10;
        y2 = env->screen.h != 0 ? y1 + env->screen.h : y1 + 0xF0;
        c = clase_ancho(env->disp.w);
        a = D_80063720[(env->pal * 5 + c) * 2];
        d = D_80063720[(env->pal * 5 + c) * 2 + 1] - a;
        x1 = a + env->screen.x * D_80063748[c];
        if (env->screen.w != 0) {
            d = (d * env->screen.w) >> 8;
        }
        x2 = x1 + d;
        if (env->pal != 0) {
            x1 = x1 < 0x21C ? 0x21C : x1 < 0xC95 ? x1 : 0xC94;
            if (x2 < x1 + D_80063748[c] * 4) {
                x2 = x1 + D_80063748[c] * 4;
            } else if (x2 >= 0xCBD) {
                x2 = 0xCBC;
            }
            y1 = y1 < 0x13 ? 0x13 : y1 < 0x130 ? y1 : 0x12F;
            y2 = y2 < y1 + 2 ? y1 + 2 : y2 < 0x132 ? y2 : 0x131;
        } else {
            x1 = x1 < 0x1F4 ? 0x1F4 : x1 < 0xCB3 ? x1 : 0xCB2;
            if (x2 < x1 + D_80063748[c] * 4) {
                x2 = x1 + D_80063748[c] * 4;
            } else if (x2 >= 0xCDB) {
                x2 = 0xCDA;
            }
            y1 = y1 < 0x10 ? 0x10 : y1 < 0x102 ? y1 : 0x101;
            y2 = y2 < y1 + 2 ? y1 + 2 : y2 < 0x103 ? y2 : 0x102;
        }
        COMANDO(((x2 & 0xFFF) << 12) | (x1 & 0xFFF) | 0x06000000);
        COMANDO(((y2 & 0x3FF) << 10) | (y1 & 0x3FF) | 0x07000000);
    }
    memcpy(&D_80063804, env, 0x14);
    return env;
}
