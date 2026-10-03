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

/* Suelta los objetos enganchados (bloque 0x74: cuantos en +0x34, punteros desde +0x3C): los deja con
   escala 2 y 0x80 en +0x20. Devuelve la cuenta (queda en v0). */
s32 func_8005B994(u8 *o) {
    u8 *b = o + 0x74;
    s32 i = 0;
    s32 k = 0;
    while (i < *(s32 *)(b + 0x34)) {
        u8 *a = b + k;
        *(s32 *)(*(u8 **)(a + 0x3C) + 0x54) = 2;
        i = SUMA_TRAMPA(i, 1);
        *(s32 *)(*(u8 **)(a + 0x3C) + 0x58) = 2;
        *(s32 *)(*(u8 **)(a + 0x3C) + 0x5C) = 2;
        k = SUMA_TRAMPA(k, 4);
        *(*(u8 **)(a + 0x3C) + 0x20) = 0x80;
        *(u8 **)(a + 0x3C) = NULL;
        *(s32 *)b = -1;
    }
    *(s32 *)(b + 0x1C) = 0;
    return *(s32 *)(b + 0x34);
}

extern s32 func_80021CE4(s32 x);
extern s32 func_8002EFD0(u8 *o);

/* Pone la animacion de o en el cuadro que toca segun func_80021CE4(3) (0: +8, 1: +4, si no +0xE de la
   tabla de o+0x64), si el objeto lo pide o si forzar == 1. Devuelve lo que queda en v0. */
s32 func_80056C18(u8 *o, s32 forzar) {
    u8 *t = *(u8 **)(o + 0x64);
    u8 *e;
    s32 m;
    u16 c;
    m = func_80021CE4(3);
    e = *(u8 **)(o + 0x1C);
    if (func_8002EFD0(o) == 0 && forzar != 1) {
        return 0;
    }
    if (m == 2) {
        c = *(u16 *)(t + 0xE);
    } else if (m == 1) {
        c = *(u16 *)(t + 4);
    } else if (m == 0) {
        c = *(u16 *)(t + 8);
    } else {
        c = *(u16 *)(t + 0xE);
    }
    *(s16 *)(e + 0x4C) = 0;
    e[0x50] = 0;
    e[0x51] = c;
    *(s16 *)(e + 0x4E) = 0x800;
    return 0x800;
}

extern s8 nivel_actual;
extern s32 D_8007CC74, D_8007CC10;
extern void func_8003D278(u8 *o);

/* Lo que cambia por grupo de niveles (1-3, 4-6, 7-9, 10-12). */
typedef struct {
    s32 velocidad;   /* bloque +0xC */
    u8 cuadro;       /* bloque +0x23 */
    u8 modo;         /* 0x118 */
    u8 sonido;
} PorGrupo;

/* Arranque comun de los objetos que dependen del grupo de niveles; en los niveles 10 a 12 ademas la
   bandera 0x100. Devuelve lo que queda en v0. */
#define SIN_ESCRIBIR 0x10000

static s32 arranque_por_grupo(u8 *o, const PorGrupo *t, s32 *sonido, s32 cuadro0, s32 v42, s32 bandera_desde) {
    u8 *b = o + 0x74;
    s8 n;
    s32 g;
    o[0x119] = 1;
    *(s32 *)(b + 0x28) = 0;
    if (cuadro0 != SIN_ESCRIBIR) {
        b[0x23] = cuadro0;
    }
    o[0x118] = 2;
    n = nivel_actual;
    if ((u32)n < 0xD && n != 0) {
        g = (n - 1) / 3;
        *(s32 *)(b + 0xC) = t[g].velocidad;
        *(s32 *)(b + 0x10) = 0;
        *(s32 *)(b + 0x14) = 0;
        b[0x23] = t[g].cuadro;
        o[0x118] = t[g].modo;
        *sonido = t[g].sonido;
    }
    o[0x119] = 1;
    if (v42 != SIN_ESCRIBIR) {
        *(s16 *)(b + 0x42) = v42;
    }
    func_8003D278(o);
    n = nivel_actual;
    if (n >= bandera_desde && n <= bandera_desde + 2) {
        s16 f = *(s16 *)(o + 0x112) | 0x100;
        *(s16 *)(o + 0x112) = f;
        return f;
    }
    return n;
}

static const PorGrupo grupos_80057B38[4] = {
    {0, 1, 0, 0x2D}, {0x14CCC, 0xD, 1, 0x34}, {0x18000, 0x1F, 1, 0x33}, {0xB333, 7, 1, 0x34}};
static const PorGrupo grupos_80049FCC[4] = {
    {0x29999, 8, 1, 0x34}, {0x28000, 7, 2, 0x2D}, {0x1C000, 0xB, 2, 0x36}, {0xCCCC, 0xC, 0, 0x39}};

s32 func_80057B38(u8 *o) {
    return arranque_por_grupo(o, grupos_80057B38, &D_8007CC74, SIN_ESCRIBIR, 0, 10);
}

s32 func_80049FCC(u8 *o) {
    return arranque_por_grupo(o, grupos_80049FCC, &D_8007CC10, SIN_ESCRIBIR, -1, 10);
}

extern s32 D_8007CBD8;
static const PorGrupo grupos_8003D478[4] = {
    {0x1E666, 0xA, 2, 0x35}, {0x19999, 0xD, 2, 0x35}, {0x18F9D, 8, 2, 0x2D}, {0x13333, 8, 1, 0x35}};

s32 func_8003D478(u8 *o) {
    return arranque_por_grupo(o, grupos_8003D478, &D_8007CBD8, 0xA, SIN_ESCRIBIR, 1);
}

extern u16 D_8007CBC0, D_8007CBD4;
extern s32 D_8007CBBC, D_8007CBAC, D_8007CBB0, D_8007C9F0;
extern u8 *D_8007CAFC;
extern s32 D_8006C444, D_8006C448, D_8006C44C, D_8006C450, D_8006C454, D_8006C458, D_8006C45C, D_8006C460,
    D_8006C464;
extern s32 D_80086398, D_80086414, D_800863B4, D_800863C0;
extern s16 D_8007C872;
extern s32 func_8001E06C(s32 a, s32 b);

/* Arranque del objeto que lleva la camara: la pone en su posicion (en 1/256) mirando de frente, y le busca
   los dos recursos (0x48 y, segun el nivel, 0x4C). Devuelve lo que queda en v0; en el nivel 0 el original
   deja la direccion a la que salta su tabla de casos. */
s32 func_80035190(u8 *o) {
    u8 *b = o + 0x74;
    s32 r;
    s8 n;
    D_8007CBC0 = D_8007CBD4;
    D_8007CBBC = 0;
    *(s32 *)(b + 0x4C) = 0;
    *(s32 *)(b + 0x48) = 0;
    D_8007CAFC = o;
    D_8006C444 = *(s32 *)(o + 0x24) >> 8;
    D_8006C448 = *(s32 *)(o + 0x28) >> 8;
    D_8006C44C = *(s32 *)(o + 0x2C) >> 8;
    D_8006C450 = 0;
    D_8006C454 = 0;
    D_8006C458 = -0x1000;
    D_8006C45C = 0;
    D_8006C460 = 0x1000;
    D_8006C464 = 0;
    *(s16 *)(o + 0x70) = 0;
    *(u8 **)b = D_800D588C;
    *(s32 *)(b + 0x34) = *(s32 *)(o + 0x24);
    *(s32 *)(b + 0x38) = *(s32 *)(o + 0x28);
    *(s32 *)(b + 0x3C) = *(s32 *)(o + 0x2C);
    *(s16 *)(b + 0x40) = 0;
    *(s16 *)(b + 0x42) = 0;
    b[0x25] = 0;
    b[0x5C] = 0;
    D_8007CBAC = 0;
    D_8007CBB0 = 0;
    *(s32 *)(b + 0x48) = func_8001E06C(D_80086398, D_8007C9F0);
    n = nivel_actual;
    switch (n) {
    case 0:
        return 0x80035304;
    case 1: case 2: case 3: case 4: case 5: case 6:
    case 7: case 8: case 9: case 10: case 11: case 12:
        r = func_8001E06C(D_80086414, D_8007C9F0);
        *(s32 *)(b + 0x4C) = r;
        return r;
    case 13:
        r = func_8001E06C(D_800863B4, D_8007C9F0);
        *(s32 *)(b + 0x4C) = r;
        return r;
    case 14:
        *(s32 *)(b + 0x4C) = func_8001E06C(D_800863C0, D_8007C9F0);
        D_8007C872 = 1;
        return 1;
    }
    return n;
}

extern s32 D_8007CBF4;
static const PorGrupo grupos_80045B60[4] = {
    {0x19999, 9, 2, 0x36}, {0x18000, 0xB, 2, 0x37}, {0xE666, 6, 1, 0x37}, {0x18000, 7, 2, 0x38}};

/* Como arranque_por_grupo, con 0x1999 en +0x1C del bloque en los niveles 7 a 9 y la z guardada en +0x3C
   despues de func_8003D278. */
s32 func_80045B60(u8 *o) {
    u8 *b = o + 0x74;
    s8 n;
    s32 g;
    o[0x119] = 1;
    *(s32 *)(b + 0x28) = 0;
    o[0x118] = 2;
    n = nivel_actual;
    if ((u32)n < 0xD && n != 0) {
        g = (n - 1) / 3;
        *(s32 *)(b + 0xC) = grupos_80045B60[g].velocidad;
        *(s32 *)(b + 0x10) = 0;
        *(s32 *)(b + 0x14) = 0;
        b[0x23] = grupos_80045B60[g].cuadro;
        o[0x118] = grupos_80045B60[g].modo;
        D_8007CBF4 = grupos_80045B60[g].sonido;
        if (g == 2) {
            *(s32 *)(b + 0x1C) = 0x1999;
        }
    }
    o[0x119] = 1;
    *(s16 *)(b + 0x42) = -1;
    func_8003D278(o);
    *(s32 *)(b + 0x3C) = *(s32 *)(o + 0x2C);
    n = nivel_actual;
    if (n >= 1 && n <= 3) {
        s16 f = *(s16 *)(o + 0x112) | 0x100;
        *(s16 *)(o + 0x112) = f;
        return f;
    }
    return n;
}

extern void *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                            s32 d, s32 e, s32 f, s32 g, s32 h);

/* Arranque de un objeto con particula propia segun el grupo de niveles (0x19, 0x1C, 0x1B, 0x1A); el angulo
   sale de su posicion. Devuelve lo que queda en v0 (en el nivel 0, la direccion de su tabla de casos). */
s32 func_800563C4(u8 *o) {
    u8 *b = o + 0x74;
    s8 n;
    s32 tipo;
    void *p;
    *(s16 *)(o + 0x32) = (SUMA_TRAMPA(*(s32 *)(o + 0x24), *(s32 *)(o + 0x2C)) >> 8) & 0xFFF;
    *(s32 *)(b + 8) = *(s32 *)(o + 0x28);
    n = nivel_actual;
    switch (n) {
    case 0:
        return 0x8005654C;
    case 1: case 2: case 3:
        tipo = 0x19;
        break;
    case 4: case 5: case 6:
        tipo = 0x1C;
        break;
    case 7: case 8: case 9:
        tipo = 0x1B;
        break;
    case 10: case 11: case 12:
        tipo = 0x1A;
        break;
    default:
        return n;
    }
    p = CrearParticula(tipo, (Objeto *)o, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3E80, 0, 0);
    *(void **)(b + 0xC) = p;
    return (s32)p;
}

extern s8 D_800C8567[];
extern s32 func_800249CC(u8 *o, s32 modelo);

/* Arranque de la puerta de cada nivel: su modelo (0x1A, 0x1B o 0x1C segun el nivel dentro de su grupo de
   3; la tercera queda abierta), el numero de nivel que lleva (bloque +4) y la marca 0x80 si ese nivel ya
   se paso (D_800C8567). Devuelve lo que queda en v0. */
s32 func_80054A58(u8 *o) {
    u8 *b = o + 0x74;
    s8 n;
    s32 g;
    *(s16 *)(o + 0x32) = 0;
    *(s16 *)(o + 0x34) = 0;
    *(s16 *)(o + 0x30) = 0;
    *(s16 *)(o + 0x70) = 1;
    *(s32 *)(b + 4) = nivel_actual;
    *(s32 *)(o + 0x54) = 5;
    *(s32 *)(o + 0x58) = 5;
    *(s32 *)(o + 0x5C) = 5;
    *(s32 *)(b + 8) = 0;
    n = nivel_actual;
    if ((u32)n < 0xE) {
        if (n == 0 || n == 13) {
            *(s32 *)(b + 8) = 0;
        } else {
            g = (n - 1) % 3;
            *(s32 *)(b + 8) = g == 2;
            func_800249CC(o, 0x1A + g);
            if (g == 2) {
                *(s16 *)(o + 0x70) = 0;
            }
            *(s32 *)(b + 4) = n - 1;
        }
    }
    if (D_800C8567[*(s32 *)(b + 4)] != 0) {
        u8 f = o[0x20] | 0x80;
        o[0x20] = f;
        return f;
    }
    return 0;
}

extern s32 D_8007CC70;

/* Pone el tipo (1 a 4) en el bloque 0x74 y su modelo (0x16, 0x18, 0x19, 0x17). Devuelve 1 (queda en v0). */
s32 func_80055F34(u8 *o, s32 tipo) {
    *(s32 *)(o + 0x74) = tipo;
    switch (tipo) {
    case 2:
        func_800249CC(o, 0x18);
        break;
    case 1:
        func_800249CC(o, 0x16);
        break;
    case 3:
        func_800249CC(o, 0x19);
        break;
    case 4:
        func_800249CC(o, 0x17);
        break;
    }
    D_8007CC70 = 1;
    return 1;
}

extern void func_800206E8(u8 *o);
extern void func_8001E230(void *modelo);
extern void func_800399E8(u8 *o, u8 *a);

/* Le pone a a el modelo guardado por o (bloque +0x40) en lugar del suyo, lo suelta (0x11C) y sigue con
   func_800399E8. Devuelve 0x80 (queda en v0). */
s32 func_80038FAC(u8 *o, u8 *a) {
    u8 *b = o + 0x74;
    *(s16 *)(a + 0x112) &= 0x7FFF;
    if (*(void **)(a + 0x60) != NULL) {
        func_800206E8(a);
        func_8001E230(*(void **)(a + 0x60));
    }
    *(s32 *)(a + 0x60) = *(s32 *)(b + 0x40);
    *(s32 *)(a + 0x11C) = 0;
    func_800399E8(o, a);
    o[0x20] = 0x80;
    return 0x80;
}

extern s32 func_80021D44(s16 *ang, s32 objetivo, s32 paso);
extern s32 func_80022310(u8 *o, s32 ang, s32 a, s32 b, s32 anim);
extern void func_800484CC(s32 *desde, s32 *hasta, s32 dist, s32 *fuera);
extern s32 func_8002218C(Objeto *o, s32 a, s32 b);

/* Un objeto que se acerca a Sabrina: (1) toma un punto hacia ella, (2) gira hacia ese punto y, ya de frente,
   avanza con la animacion t[1]. Devuelve lo que queda en v0. */
s32 func_80052EA4(u8 *o) {
    u16 *t = *(u16 **)(o + 0x64);
    u8 *b = o + 0x74;
    s16 est = *(s16 *)(o + 0x70);
    s32 r;
    if (est == 2) {
        r = func_80021D44((s16 *)(o + 0x32), (s16)func_8002218C((Objeto *)o, *(s32 *)(b + 8), *(s32 *)(b + 0x10)), 0x96);
        if (r != 0) {
            return r;
        }
        return func_80022310(o, *(s16 *)(o + 0x32), 0x3333, 0x1000, t[1]);
    }
    if (est == 1) {
        func_800484CC((s32 *)(o + 0x24), (s32 *)((u8 *)p_sabrina + 0x24), 0x40000, (s32 *)(b + 8));
        *(s16 *)(o + 0x70) = 2;
        return 2;
    }
    if (est != 0) {
        return est;
    }
    *(s16 *)(o + 0x70) = 1;
    return 1;
}

extern void Afirmar(void *p, char *archivo, s32 linea);
extern char D_80074C64[];

/* Si lo que toca (a) es de la clase 6 y con 0x93 >= 7, le resta 1 de vida al objeto que vigila o (el de
   o+0x11C, bloque +0xC); si se le acabo, avisa (bloque +0x10), lo marca y le pasa a ese objeto su aviso de
   +8 con a. Devuelve lo que queda en v0. */
s32 func_80039670(u8 *o, u8 *a) {
    u8 *g, *b, *v;
    s8 n;
    if (*(u16 *)(a + 0x22) != 6) {
        return *(u16 *)(a + 0x22);
    }
    n = a[0x93];
    if (n < 7) {
        return n;
    }
    g = *(u8 **)(o + 0x11C);
    Afirmar(g, D_80074C64, 0x21);
    b = g + 0x74;
    v = *(u8 **)(b + 0xC);
    v[0x118] = SUMA_TRAMPA((s8)v[0x118], -1);
    n = v[0x118];
    if (n >= 0) {
        return n;
    }
    (*(void (**)(u8 *, u8 *))(b + 0x10))(g, v);
    g[0x20] = 0x80;
    *(void **)(b + 0x10) = NULL;
    return (*(s32 (**)(u8 *, u8 *))(v + 8))(v, a);
}

/* Suelta 20 particulas (del tipo de su bloque +4) hacia abajo y al azar, y queda marcado. Devuelve lo que
   queda en v0. */
s32 func_80037DE0(u8 *o) {
    u8 *b = o + 0x74;
    s32 base = RESTA_TRAMPA(0, *(s32 *)(o + 0x3C)) >> 1;
    s32 i, j, dy;
    u8 f;
    for (i = 0; i < 0x14; i = (s16)SUMA_TRAMPA(i, 1)) {
        j = (s16)SUMA_TRAMPA(func_80021CE4(0x190), -0xC8);
        dy = RESTA_TRAMPA(base, func_80021CE4(0xCCC));
        CrearParticula((s8)b[4], (Objeto *)o, j, 0, 0, 0x28F, 0, dy, func_80021CE4(0xCCC), 0, 0x51E, 0, 0x32,
                       0x10, 0);
    }
    f = o[0x20] | 0x80;
    o[0x20] = f;
    return f;
}

extern s32 func_8001BF8C(s32 a, s32 b, s32 x, s32 z);
extern s32 func_8001C2D0(s32 x, ...);
extern s32 D_8006C450, D_8006C454, D_8006C458;

/* Si el objeto de la camara (D_8007CAFC) esta libre y o queda a menos de 2 unidades en el piso y de
   frente a la camara, lo engancha (estado 1, con la ficha de o y su tipo). Devuelve lo que queda en v0. */
s32 func_8003BCB4(u8 *o) {
    u8 *b = o + 0x74;
    u8 *c = D_8007CAFC;
    s32 v[3];
    s32 r;
    if (c == NULL) {
        return 0;
    }
    if (*(s16 *)(c + 0x70) != 0) {
        return *(s16 *)(c + 0x70);
    }
    v[0] = RESTA_TRAMPA(*(s32 *)(c + 0x24), *(s32 *)(o + 0x24));
    v[1] = RESTA_TRAMPA(*(s32 *)(c + 0x28), *(s32 *)(o + 0x28));
    v[2] = RESTA_TRAMPA(*(s32 *)(c + 0x2C), *(s32 *)(o + 0x2C));
    r = func_8001BF8C(0, 0, v[0], v[2]);
    if (r >= 0x20000) {
        return r;
    }
    func_8001C45C(v);
    r = func_8001C2D0(v[0], v[1], v[2], D_8006C450, D_8006C454, D_8006C458);
    if (r < 0xBB9) {
        return r;
    }
    c = D_8007CAFC;
    *(s16 *)(c + 0x70) = 1;
    *(s32 *)(c + 0x74) = *(s32 *)b;
    c[0x74 + 0x24] = b[4];
    return (s8)b[4];
}

/* Un chorro que sube con el objeto que lleva (bloque +0): lo empuja hacia arriba y suelta una particula
   por paso hasta agotar la cuenta (bloque +4); despues marca al otro (1) y a si mismo (2). Devuelve lo que
   queda en v0. */
s32 func_8005329C(u8 *o) {
    u8 *b = o + 0x74;
    s16 est = *(s16 *)(o + 0x70);
    u8 *p;
    s32 r1, n;
    if (est == 2) {
        u8 f = o[0x20] | 0x80;
        o[0x20] = f;
        return f;
    }
    if (est == 1) {
        (*(u8 **)b)[0x20] |= 0x80;
        *(s16 *)(o + 0x70) = 2;
        return 2;
    }
    if (est != 0) {
        return est;
    }
    *(s32 *)(o + 0x3C) = SUMA_TRAMPA(*(s32 *)(o + 0x3C), -0xE6);
    p = *(u8 **)b;
    *(s32 *)(p + 0x28) = SUMA_TRAMPA(*(s32 *)(p + 0x28), *(s32 *)(o + 0x3C));
    r1 = SUMA_TRAMPA(func_80021CE4(0x800), -0x400);
    p = CrearParticula((s8) * (s32 *)(b + 8), *(Objeto **)b, 0, 0, 0, 0, r1, 0,
                       SUMA_TRAMPA(func_80021CE4(0x800), -0x400), 0, 0, 0, 0x37, 0x202, 0);
    *(s32 *)(p + 0x3C) = 0xB4;
    *(s32 *)(b + 4) = SUMA_TRAMPA(*(s32 *)(b + 4), -1);
    n = *(s32 *)(b + 4);
    if (n >= 0) {
        return n;
    }
    *(s16 *)(o + 0x70) = 1;
    return 1;
}

/* Con la bandera 8 (bloque +0xC) vuelve a su lugar de partida (y con 0x100 queda sin colision) y pasa al
   estado 1; si no, se deshace en 10 particulas y queda marcado. Devuelve lo que queda en v0. */
s32 func_8003BE38(u8 *o) {
    u8 *b = o + 0x74;
    s32 base = RESTA_TRAMPA(0, *(s32 *)(o + 0x3C)) >> 1;
    s16 fl = *(s16 *)(b + 0xC);
    s32 i, j, dy;
    u8 f;
    if (fl & 8) {
        *(s32 *)(o + 0x24) = *(s32 *)(b + 0x14);
        *(s32 *)(o + 0x28) = *(s32 *)(b + 0x18);
        *(s32 *)(o + 0x2C) = *(s32 *)(b + 0x1C);
        *(s16 *)(o + 0x32) = *(s16 *)(b + 0x20);
        *(s16 *)(o + 0x30) = 0;
        if (fl & 0x100) {
            (*(u8 **)(o + 0x60))[0x64] |= 1;
            *(s32 *)(o + 0x54) = 1;
            *(s32 *)(o + 0x58) = 1;
            *(s32 *)(o + 0x5C) = 1;
        }
        *(s16 *)(o + 0x70) = 1;
        return 1;
    }
    for (i = 0; i < 0xA; i = (s16)SUMA_TRAMPA(i, 1)) {
        j = (s16)SUMA_TRAMPA(func_80021CE4(0x190), -0xC8);
        dy = RESTA_TRAMPA(base, func_80021CE4(0xCCC));
        CrearParticula((s8)b[0x12], (Objeto *)o, j, 0, 0, 0x28F, 0, dy, func_80021CE4(0xCCC), 0, 0x51E, 0, 0x32,
                       0x10, 0);
    }
    f = o[0x20] | 0x80;
    o[0x20] = f;
    return f;
}
