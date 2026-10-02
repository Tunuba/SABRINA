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

extern s16 partida;
extern s32 func_8002225C(Objeto *o, s32 x, s32 y, s32 z);
extern s32 func_80014F10(void);
extern void func_8004C824(Objeto *o);
extern void func_800300C4(s32 mucho);

/* Copia la posicion del objeto al que lo sigue (bloque +0xC), si hay, con 3 en su 0x40. Devuelve lo que
   queda en v0. */
static s32 mover_seguidor(u8 *ob, u8 *b) {
    u8 *s = *(u8 **)(b + 0xC);
    if (s == NULL) {
        return 0;
    }
    *(s16 *)(s + 0x40) = 3;
    *(s32 *)(*(u8 **)(b + 0xC) + 4) = *(s32 *)(ob + 0x24);
    *(s32 *)(*(u8 **)(b + 0xC) + 8) = *(s32 *)(ob + 0x28);
    *(s32 *)(*(u8 **)(b + 0xC) + 0xC) = *(s32 *)(ob + 0x2C);
    return *(s32 *)(b + 0xC);
}

/* La vida extra (o la cura): (0) se encoge escondida hasta que Sabrina se acerca, (1) crece y flota,
   (2) vuela hacia Sabrina soltando chispas y al tocarla suma una partida (si lleva seguidor) o la cura.
   Devuelve lo que queda en v0. */
s32 func_8004A4A8(Objeto *o) {
    u8 *ob = (u8 *)o;
    u8 *b = ob + 0x74;
    s16 est = o->estado;
    s32 esc, d, r0, r1, r2, ang, j;

    if (est == 2) {
        *(s32 *)(ob + 0x38) = RESTA_TRAMPA(p_sabrina->x, *(s32 *)(ob + 0x24)) >> 3;
        *(s32 *)(ob + 0x40) = RESTA_TRAMPA(p_sabrina->z, *(s32 *)(ob + 0x2C)) >> 3;
        *(s32 *)(ob + 0x3C) =
            RESTA_TRAMPA(SUMA_TRAMPA(SUMA_TRAMPA(p_sabrina->y, -0x4001), -0x7FFF), *(s32 *)(ob + 0x28)) >> 3;
        *(s32 *)(ob + 0x38) = (((*(s32 *)(ob + 0x38) >> 8) * 0x2E6) >> 8) << 8;
        *(s32 *)(ob + 0x3C) = (((*(s32 *)(ob + 0x3C) >> 8) * 0x2E6) >> 8) << 8;
        *(s32 *)(ob + 0x40) = (((*(s32 *)(ob + 0x40) >> 8) * 0x2E6) >> 8) << 8;
        *(s32 *)(ob + 0x24) = SUMA_TRAMPA(*(s32 *)(ob + 0x24), *(s32 *)(ob + 0x38));
        *(s32 *)(ob + 0x28) = SUMA_TRAMPA(*(s32 *)(ob + 0x28), *(s32 *)(ob + 0x3C));
        *(s32 *)(ob + 0x2C) = SUMA_TRAMPA(*(s32 *)(ob + 0x2C), *(s32 *)(ob + 0x40));
        mover_seguidor(ob, b);
        esc = *(s32 *)(ob + 0x54);
        *(s32 *)(ob + 0x54) = RESTA_TRAMPA(esc, esc >> 4);
        *(s32 *)(ob + 0x58) = *(s32 *)(ob + 0x54);
        *(s32 *)(ob + 0x5C) = *(s32 *)(ob + 0x54);
        r0 = SUMA_TRAMPA(func_80014F10() & 0x3F, -0x20) << 8;
        r1 = SUMA_TRAMPA(func_80014F10() & 0x3F, -0x20) << 8;
        r2 = SUMA_TRAMPA(func_80014F10() & 0x3F, -0x20) << 8;
        CrearParticula((s8)b[4], o, 0, r0, r1, r2, 0, 0, 0, 0, 0, 0, 7, 2, 0);
        *(s16 *)(ob + 0x30) = SUMA_TRAMPA(*(s16 *)(ob + 0x30), 0xF);
        *(s16 *)(ob + 0x32) = SUMA_TRAMPA(*(s16 *)(ob + 0x32), 0x17);
        if (p_sabrina == NULL) {
            return 0;
        }
        d = func_8002225C(o, p_sabrina->x, SUMA_TRAMPA(SUMA_TRAMPA(p_sabrina->y, -0x4001), -0x7FFF),
                          p_sabrina->z);
        if (d >= 0x6666) {
            return d;
        }
        TocarSonido(0x20, 0, 0x2A, 0x7F);
        func_8004C824(o);
        if (*(void **)(b + 0xC) != NULL) {
            partida = SUMA_TRAMPA(partida, 1);
        } else {
            func_800300C4((s8)b[5]);
        }
        for (ang = 0; ang < 0x1000; ang = SUMA_TRAMPA(ang, 0x320)) {
            for (j = 0; j < 0x1000; j = SUMA_TRAMPA(j, 0x3E8)) {
                r0 = (rsin(ang) * 0xCCC) >> 12;
                CrearParticula((s8)b[4], o, (s16)j, 0, 0, 0x28F, 0, r0, (rcos(ang) * 0xCCC) >> 12, 0, 0, 0, 0xF,
                               0x202, 0);
            }
        }
        ob[0x20] |= 0x80;
        if (*(u8 **)(b + 0xC) == NULL) {
            return 0;
        }
        *(s16 *)(*(u8 **)(b + 0xC) + 0x40) = 1;
        return 1;
    }
    if (est == 1) {
        esc = *(s32 *)(ob + 0x54);
        if (esc < 0x1000) {
            *(s32 *)(ob + 0x54) = SUMA_TRAMPA(esc, RESTA_TRAMPA(0x1000, esc) >> 2);
            if (*(s32 *)(ob + 0x54) >= 0x1000) {
                *(s32 *)(ob + 0x54) = 0x1000;
            }
            esc = *(s32 *)(ob + 0x54);
            *(s32 *)(ob + 0x5C) = esc;
            *(s32 *)(ob + 0x58) = esc;
        }
        *(s16 *)(ob + 0x32) = SUMA_TRAMPA(*(s16 *)(ob + 0x32), 0x28);
        *(s32 *)(ob + 0x28) = SUMA_TRAMPA(*(s32 *)(ob + 0x28), rsin(*(s16 *)(ob + 0x32) << 2) << 1);
        *(s16 *)(ob + 0x34) = rcos(*(s16 *)(ob + 0x32)) >> 4;
        mover_seguidor(ob, b);
        if (p_sabrina == NULL) {
            return 0;
        }
        d = func_8002225C(o, p_sabrina->x, p_sabrina->y, p_sabrina->z);
        if (d >= 0x140001) {
            o->estado = 0;
            return d;
        }
        if (d < 0x20000) {
            o->estado = 2;
            return 2;
        }
        return d;
    }
    if (est != 0) {
        o->estado = 0;
        return est;
    }
    esc = *(s32 *)(ob + 0x54);
    if (esc >= 2) {
        *(s32 *)(ob + 0x54) = SUMA_TRAMPA(esc, RESTA_TRAMPA(1, esc) >> 2);
        if (*(s32 *)(ob + 0x54) < 2) {
            (*(u8 **)(ob + 0x60))[0x64] |= 1;
            *(s32 *)(ob + 0x54) = 1;
        }
        *(s32 *)(ob + 0x58) = *(s32 *)(ob + 0x54);
        *(s32 *)(ob + 0x5C) = *(s32 *)(ob + 0x54);
    }
    if (p_sabrina != NULL && func_8002225C(o, p_sabrina->x, p_sabrina->y, p_sabrina->z) < 0x140000) {
        (*(u8 **)(ob + 0x60))[0x64] &= 0xFE;
        o->estado = 1;
    }
    return mover_seguidor(ob, b);
}
