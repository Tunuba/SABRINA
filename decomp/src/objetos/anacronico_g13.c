#include "objeto.h"

/* El objeto anacronico de cada nivel (los niveles 4, 7, 8 y 10): gira, crece al aparecer (estado 0) y al
   tomarlo (estado 1) se anota, suena y suelta un anillo de particulas. */

extern s8 D_800C857E, D_800C857F, D_800C8580, D_800C8581;
extern s8 objetos_anacronicos, D_8007C88D, D_8007C88E, D_8007C88F;
extern s8 nivel_actual;
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern void func_8004C22C(void);
extern s32 rsin(s32 a);
extern s32 rcos(s32 a);
extern void *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                            s32 d, s32 e, s32 f, s32 g, s32 h);

/* Devuelve lo que queda en v0. */
s32 func_8005B150(Objeto *o) {
    u8 *ob = (u8 *)o;
    s16 est;
    s32 esc, ang, j, s;
    u8 f;

    *(s16 *)(ob + 0x32) = SUMA_TRAMPA(*(s16 *)(ob + 0x32), 0x2D);
    *(s16 *)(ob + 0x32) &= 0xFFF;
    est = o->estado;
    if (est == 1) {
        switch (nivel_actual) {
        case 10:
            D_800C8580 = 1;
            objetos_anacronicos = 1;
            break;
        case 8:
            D_800C857F = 1;
            D_8007C88F = 1;
            break;
        case 7:
            D_800C8581 = 1;
            D_8007C88E = 1;
            break;
        case 4:
            D_800C857E = 1;
            D_8007C88D = 1;
            break;
        }
        TocarSonido(0x1E, 0, 0x23, 0x7F);
        func_8004C22C();
        for (ang = 0; ang < 0x1000; ang = (s16)SUMA_TRAMPA(ang, 0x384)) {
            for (j = 0; j < 0x1000; j = (s16)SUMA_TRAMPA(j, 0x3E8)) {
                s = (rsin(ang) * 0xCCC) >> 12;
                CrearParticula(0xF, o, j, 0, 0, 0x28F, 0, s, (rcos(ang) * 0xCCC) >> 12, 0, 0, 0, 0xF, 0x202, 0);
            }
        }
        f = ob[0x20] | 0x80;
        ob[0x20] = f;
        return f;
    }
    if (est != 0) {
        return est;
    }
    esc = *(s32 *)(ob + 0x54);
    if (esc >= 0x1000) {
        return 0;
    }
    *(s32 *)(ob + 0x54) = SUMA_TRAMPA(esc, RESTA_TRAMPA(0x1000, esc) >> 2);
    if (*(s32 *)(ob + 0x54) >= 0x1000) {
        *(s32 *)(ob + 0x54) = 0x1000;
    }
    esc = *(s32 *)(ob + 0x54);
    *(s32 *)(ob + 0x5C) = esc;
    *(s32 *)(ob + 0x58) = esc;
    return esc;
}
