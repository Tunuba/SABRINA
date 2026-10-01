#include "juego.h"

/* libgpu: SetDrawEnv, arma el primitivo de un entorno de dibujo (DRAWENV). */

typedef struct {
    s16 x, y, w, h;
} RectE;

typedef struct {
    RectE clip;                      /* 0x00, el area de dibujo */
    s16 ofs[2];                      /* 0x08 */
    RectE tw;                        /* 0x0C, la ventana de textura */
    u16 tpage;                       /* 0x14 */
    u8 dtd, dfe;                     /* 0x16 */
    u8 isbg;                         /* 0x18, borrar el fondo */
    u8 r0, g0, b0;                   /* 0x19 */
} EntornoDibujo;

extern s16 D_8006379C, D_8006379E;   /* ancho y alto de la VRAM */

extern u32 func_8001166C(s32 x, s32 y);        /* esquina de arriba del area */
extern u32 func_80011704(s32 x, s32 y);        /* esquina de abajo */
extern u32 func_8001179C(s32 x, s32 y);        /* desplazamiento */
extern u32 func_8001164C(s32 dfe, s32 dtd, s32 tpage);
extern u32 func_800117B8(RectE *tw);

/* Llena prim desde la palabra 1: area, desplazamiento, modo, ventana de textura y 0xE6000000; si hay que
 * borrar el fondo agrega un rectangulo de color (relleno rapido si x y el ancho son multiplos de 64).
 * Deja en el byte 3 cuantas palabras siguen y devuelve ese numero. */
s32 func_800113DC(u32 *prim, EntornoDibujo *env) {
    RectE r;
    s32 n;
    s16 v;

    prim[1] = func_8001166C(env->clip.x, env->clip.y);
    prim[2] = func_80011704((s16)(env->clip.x + env->clip.w - 1), (s16)(env->clip.y + env->clip.h - 1));
    prim[3] = func_8001179C(env->ofs[0], env->ofs[1]);
    prim[4] = func_8001164C(env->dfe, env->dtd, env->tpage);
    prim[5] = func_800117B8(&env->tw);
    prim[6] = 0xE6000000;
    n = 7;
    if (env->isbg != 0) {
        r = env->clip;
        v = r.w;
        if (v < 0) {
            r.w = 0;
        } else if (D_8006379C - 1 < v) {
            r.w = (u16)D_8006379C - 1;
        } else {
            r.w = v;
        }
        v = r.h;
        if (v < 0) {
            r.h = 0;
        } else if (D_8006379E - 1 < v) {
            r.h = (u16)D_8006379E - 1;
        } else {
            r.h = v;
        }
        if ((r.x & 0x3F) || (r.w & 0x3F)) {
            r.x -= env->ofs[0];
            r.y -= env->ofs[1];
            prim[n] = (env->b0 << 16) | (env->g0 << 8) | 0x60000000 | env->r0;
            prim[n + 1] = *(u32 *)&r.x;
            prim[n + 2] = *(u32 *)&r.w;
        } else {
            prim[n] = (env->b0 << 16) | (env->g0 << 8) | 0x02000000 | env->r0;
            prim[n + 1] = *(u32 *)&r.x;
            prim[n + 2] = *(u32 *)&r.w;
        }
        n += 3;
    }
    ((u8 *)prim)[3] = n - 1;
    return n - 1;
}
