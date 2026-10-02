#include "objeto.h"

/* Listas de objetos que se llenan cada cuadro: cada una es un arreglo de punteros y su cuenta. */

extern void *D_80086324[];
extern s32 D_8007CA24;
extern void *D_80086338[];
extern s32 D_8007CA28;

/* Agrega o a la primera lista y le borra la marca de 0x70/0x74. */
void func_800534A0(u8 *o) {
    *(s32 *)(o + 0x74) = 0;
    *(s16 *)(o + 0x70) = 0;
    D_80086324[D_8007CA24] = o;
    D_8007CA24++;
}

/* Agrega o a la segunda lista y copia su posicion (0x114, 0x112) al bloque de 0x74. */
s32 func_800537C4(u8 *o) {
    s16 y;
    u8 *b = o + 0x74;
    D_80086338[D_8007CA28] = o;
    D_8007CA28++;
    *(s16 *)(b + 8) = *(s16 *)(o + 0x114);
    y = *(s16 *)(o + 0x112);
    *(s16 *)(b + 0xA) = y;
    return y;   /* lo que queda en v0 */
}

/* Deja el bloque de 0x74 en sus valores de partida y agrega o a la primera lista. */
void func_80052F6C(u8 *o) {
    u8 *b = o + 0x74;
    *(s32 *)(b + 0xC) = 0;
    *(s32 *)(b + 4) = 0x800;
    *(s32 *)(b + 8) = 0;
    *(s32 *)(b + 0) = 0x15E;
    *(s32 *)(b + 0x14) = 0;
    *(s32 *)(b + 0x18) = 0;
    D_80086324[D_8007CA24] = o;
    D_8007CA24++;
}

extern s32 func_8002244C(u8 *o, s32 a, s32 b);

void func_8003B53C(u8 *o, s32 a, s32 c) {
    u8 *b = o + 0x74;
    *(s16 *)(b + 0x1C) = c;
    *(s16 *)(b + 0x18) = 0x14;
    *(s32 *)(o + 0x50) = func_8002244C(o, 0, 0);
}

/* Copia a o la posicion del objeto guia (o+0x74) con la altura de su suelo (0x50) y la escala que sale
   de la distancia a ese suelo; si el guia tiene escala propia menor que 1000 usa la suya. */
void func_80053400(u8 *o) {
    u8 **g = (u8 **)(o + 0x74);
    s32 e;
    *(s32 *)(o + 0x24) = *(s32 *)(*g + 0x24);
    *(s32 *)(o + 0x28) = *(s32 *)(*g + 0x28);
    *(s32 *)(o + 0x2C) = *(s32 *)(*g + 0x2C);
    *(s32 *)(o + 0x28) = *(s32 *)(*g + 0x50);
    e = RESTA_TRAMPA(0x1000, RESTA_TRAMPA(*(s32 *)(o + 0x28), *(s32 *)(*g + 0x28)) >> 5);
    *(s32 *)(o + 0x54) = e;
    *(s32 *)(o + 0x5C) = e;
    if (*(s32 *)(*g + 0x54) < 0x3E8) {
        u8 *h = *g;
        *(s32 *)(o + 0x54) = *(s32 *)(h + 0x54);
        *(s32 *)(o + 0x58) = *(s32 *)(h + 0x58);
        *(s32 *)(o + 0x5C) = *(s32 *)(h + 0x5C);
    }
}

extern s32 thunk_FUN_8004866c(u8 *o);

/* Saca o de la segunda lista corriendo los que siguen, y sigue con thunk_FUN_8004866c. */
s32 func_80053808(u8 *o) {
    s32 i, j, n;
    for (i = 0; i < D_8007CA28; i++) {
        if (D_80086338[i] == o) {
            n = D_8007CA28;
            for (j = i + 1; i < n; i++, j++) {
                D_80086338[i] = D_80086338[j];
            }
            D_8007CA28--;
        }
    }
    return thunk_FUN_8004866c(o);
}

extern void func_800483F8(u8 *o);
extern s32 func_800223E8(s32 *pos);

/* Arranque de un objeto que se apoya en el suelo: busca el suelo bajo su posicion (un poco arriba) y lo
   baja hasta ahi si no estaba. */
s32 func_800551FC(u8 *o) {
    s32 v[3];
    s32 bajo;
    u8 *b = o + 0x74;
    *(s32 *)(b + 0xC) = 0;
    *(s32 *)(b + 8) = 0;
    *(s32 *)(b + 0) = 0x64;
    func_800483F8(o);
    v[0] = *(s32 *)(o + 0x24);
    v[1] = SUMA_TRAMPA(SUMA_TRAMPA(*(s32 *)(o + 0x28), -0x6667), -0x7FFF);
    v[2] = *(s32 *)(o + 0x2C);
    v[1] = func_800223E8(v);
    bajo = SUMA_TRAMPA(SUMA_TRAMPA(*(s32 *)(o + 0x28), -0x6667), -0x7FFF);
    if (v[1] != bajo) {
        *(s32 *)(o + 0x28) = v[1];
    }
    *(s16 *)(o + 0x70) = 0;
    return bajo;   /* lo que queda en v0 */
}

extern u32 func_8001C180(s32 *v);

/* Si Sabrina esta (bandera 1 de su forma) a menos del radio de o (bloque 0x74, +8, en 1/256), llama al
   aviso de o (0x10) con o y Sabrina. Devuelve lo que queda en v0 en cada camino. */
s32 func_8005794C(u8 *o) {
    u8 *b = o + 0x74;
    Objeto *s;
    s32 d[3];
    u32 dist;
    *(s32 *)(b + 0x28) = 0;
    s = p_sabrina;
    if (s == NULL) {
        return 0;
    }
    if (!(s->forma.banderas & 1)) {
        return 0;
    }
    d[0] = RESTA_TRAMPA(*(s32 *)(o + 0x24), s->x);
    d[1] = RESTA_TRAMPA(*(s32 *)(o + 0x28), s->y);
    d[2] = RESTA_TRAMPA(*(s32 *)(o + 0x2C), s->z);
    dist = func_8001C180(d);
    if ((u32)(*(s32 *)(b + 8) >> 8) < dist) {
        return dist;
    }
    return (*(s32 (**)(u8 *, Objeto *))(o + 0x10))(o, p_sabrina);
}

/* Si s (con bandera 1 o 2) esta mas de 0x10000 por encima de o, lo anota en la lista de o (bloque 0x74,
   hasta 5, cuenta en +0x14). Devuelve lo que queda en v0 en cada camino. */
s32 func_8003B4DC(u8 *o, u8 *s) {
    u8 *b = o + 0x74;
    s32 m = *(s16 *)(s + 0x112) & 3;
    s16 n;
    s32 y;
    if (m == 0) {
        return 0;
    }
    n = *(s16 *)(b + 0x14);
    if (n >= 5) {
        return m;
    }
    y = SUMA_TRAMPA(*(s32 *)(o + 0x28), 0x10000);
    if (!(y < *(s32 *)(s + 0x28))) {
        return y;
    }
    *(s16 *)(b + 0x14) = SUMA_TRAMPA(n, 1);
    ((u8 **)b)[n] = s;
    return (s32)(b + n * 4);
}

extern u8 D_800D588C[];
extern void func_8002205C(s32 *v, s32 a, s32 b);

/* Arranque: el bloque 0x74 pasa de indice a puntero a su ficha (D_800D588C, 0x18 bytes cada una), la
   direccion sale de los angulos 0x30/0x32, y si la ficha no tiene velocidad (+0x10) queda marcado. */
s32 func_8003BC04(u8 *o) {
    u8 *b = o + 0x74;
    s32 v[3];
    s32 i;
    s16 r;
    *(s16 *)(o + 0x70) = 0;
    i = (s16)*(s32 *)b;
    *(u8 **)b = D_800D588C + SUMA_TRAMPA(i * 2, i) * 8;
    func_8002205C(v, *(s16 *)(o + 0x30), *(s16 *)(o + 0x32));
    *(s32 *)(o + 0x38) = v[0];
    *(s32 *)(o + 0x3C) = v[1];
    *(s32 *)(o + 0x40) = v[2];
    r = *(s16 *)(*(u8 **)b + 0x10);
    if (r != 0) {
        return r;
    }
    b[4] = 1;
    return 1;
}

/* Suelta lo que o tenia agarrado (bloque 0x74, +0xC): le pone 1 en +0x40 y lo borra. */
s32 func_8005655C(u8 *o) {
    u8 *b = o + 0x74;
    u8 *a = *(u8 **)(b + 0xC);
    if (a == NULL) {
        return 0;
    }
    *(s16 *)(a + 0x40) = 1;
    *(u8 **)(b + 0xC) = NULL;
    return 1;
}

/* Si o tiene la bandera 0x8000 y algo enganchado en 0x11C, llama al aviso (0x18) de eso. */
s32 func_8004866C(u8 *o) {
    u8 *e;
    if (!(*(s16 *)(o + 0x112) & 0x8000)) {
        return 0;
    }
    e = *(u8 **)(o + 0x11C);
    if (e == NULL) {
        return 0;
    }
    return (*(s32 (**)(u8 *))(e + 0x18))(e);
}

/* Igual que func_8005794C pero borra 0x2C del bloque (otra clase de objeto). */
s32 func_80045EE0(u8 *o) {
    u8 *b = o + 0x74;
    Objeto *s;
    s32 d[3];
    u32 dist;
    *(s32 *)(b + 0x2C) = 0;
    s = p_sabrina;
    if (s == NULL) {
        return 0;
    }
    if (!(s->forma.banderas & 1)) {
        return 0;
    }
    d[0] = RESTA_TRAMPA(*(s32 *)(o + 0x24), s->x);
    d[1] = RESTA_TRAMPA(*(s32 *)(o + 0x28), s->y);
    d[2] = RESTA_TRAMPA(*(s32 *)(o + 0x2C), s->z);
    dist = func_8001C180(d);
    if ((u32)(*(s32 *)(b + 8) >> 8) < dist) {
        return dist;
    }
    return (*(s32 (**)(u8 *, Objeto *))(o + 0x10))(o, p_sabrina);
}

/* Arranque de un objeto que rebota: 0x32 de vida al bloque, el tipo en 0x119 (1 si no viene), velocidad
   hacia abajo y empuje minimo 0x4000; con la bandera 0x100 queda sin colision. Con c != 0 solo lo
   primero. Devuelve lo que queda en v0. */
s32 func_8003C8F8(u8 *o, s32 a, s32 c) {
    u8 *b = o + 0x74;
    s32 v;
    *(s16 *)(b + 0x24) = 0x32;
    *(s16 *)(b + 0x20) = 0;
    *(s16 *)(b + 0x26) = 0;
    if (c != 0) {
        return (s32)b;
    }
    o[0x119] = a != 0 ? a : 1;
    v = *(s32 *)(b + 4);
    if (v > 0) {
        *(s32 *)(b + 4) = -v;
    }
    if (*(s32 *)b <= 0) {
        *(s32 *)b = 0x4000;
    }
    if (*(s16 *)(b + 0xC) & 0x100) {
        u8 *m = *(u8 **)(o + 0x60);
        m[0x64] |= 1;
        *(s32 *)(o + 0x54) = 1;
        *(s32 *)(o + 0x58) = 1;
        *(s32 *)(o + 0x5C) = 1;
        *(s16 *)(o + 0x112) = 0;
    }
    *(s32 *)(b + 0x14) = *(s32 *)(o + 0x24);
    *(s32 *)(b + 0x18) = *(s32 *)(o + 0x28);
    *(s32 *)(b + 0x1C) = *(s32 *)(o + 0x2C);
    *(s16 *)(b + 0x20) = *(s16 *)(o + 0x32);
    *(s16 *)(o + 0x70) = 1;
    return 1;
}

extern s32 func_80056A08(u8 *o);
extern s32 func_8002ECFC(u8 *o);
extern s32 func_80030068(s32 x);
extern s32 D_800C98B0;
extern s8 D_800C855F;

/* Arranque de un objeto con animacion: la pone en su primer cuadro (el de o+0x64) y lo deja quieto en el
   modo 6 si D_800C98B0 == 1; marca 0x38 del bloque si D_800C855F >= 4. Devuelve lo que queda en v0. */
s32 func_80056B18(u8 *o) {
    u8 *b = o + 0x74;
    u8 *e;
    s8 n;
    *(s32 *)(b + 0x28) = 0;
    *(s32 *)(b + 0x30) = 0;
    *(s32 *)(b + 0x2C) = func_80056A08(o);
    if (func_8002ECFC(o) != 0) {
        e = *(u8 **)(o + 0x1C);
        *(s16 *)(e + 0x4C) = 0;
        e[0x51] = **(u16 **)(o + 0x64);
        e[0x50] = 0;
        e[0x53] = e[0x51];
        e[0x52] = e[0x50];
        e[8] = func_80030068(*(s32 *)(*(u8 **)(o + 0x60) + 4));
        *(s16 *)(e + 0x4E) = 0x800;
    }
    *(s32 *)(b + 0x34) = 0;
    func_800483F8(o);
    if (D_800C98B0 == 1) {
        *(s16 *)(o + 0x70) = 6;
    }
    *(s32 *)(b + 0x38) = 0;
    n = D_800C855F;
    if (n < 4) {
        return n;
    }
    *(s32 *)(b + 0x38) = 1;
    return 1;
}
