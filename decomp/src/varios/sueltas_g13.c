#include "juego.h"

/* Funciones chicas sueltas que no tienen todavia un sistema propio. */

/* Devuelve el segundo argumento (un "no hace nada" de una tabla de funciones). */
s32 func_800447DC(s32 a, s32 b) {
    return b;
}

/* El tamano guardado justo antes de un bloque (0 si no hay bloque). */
s32 func_8004EA90(s32 a, s32 *bloque) {
    if (bloque == NULL) {
        return 0;
    }
    return bloque[-1];
}

extern s32 func_80016970(s32 canal, s32 f);

/* Instala f en el canal 3 de libetc. */
s32 func_8005C940(s32 f) {
    return func_80016970(3, f);
}

extern s32 func_80052114();
extern s32 func_80052184();

/* Copia el trozo de codigo func_80052114..func_80052184 a 0xDF80 (lo que corre desde ahi). */
void func_800522B0(void) {
    u32 *d = (u32 *)0xDF80;
    u32 *s = (u32 *)func_80052114;
    do {
        *d++ = *s++;
    } while (s != (u32 *)func_80052184);
}

extern s32 func_8003AF48(s32 *consulta);

/* Pregunta por la posicion de o (0x24..0x2C) y, si hay respuesta, guarda en o+0x50 la palabra 0x34
   de la consulta y la devuelve. */
s32 func_8002244C(u8 *o) {
    s32 c[0x13];
    c[0] = *(s32 *)(o + 0x24);
    c[1] = *(s32 *)(o + 0x28);
    c[2] = *(s32 *)(o + 0x2C);
    if (func_8003AF48(c) == 0) {
        return 0;
    }
    *(s32 *)(o + 0x50) = c[13];
    return *(s32 *)(o + 0x50);
}

extern char *D_8006D3A8[];
extern char D_80061234[];      /* "none" */

/* El nombre de un tipo (0 a 6), o "none". */
char *func_80029A1C(s32 n) {
    u32 i = n & 0xFF;
    if (i < 7) {
        return D_8006D3A8[i];
    }
    return D_80061234;
}

extern char *D_8006D328[];

/* El nombre de otro tipo (0 a 27), o "none". */
char *func_800299E8(s32 n) {
    u32 i = n & 0xFF;
    if (i < 0x1C) {
        return D_8006D328[i];
    }
    return D_80061234;
}

/* Copia n palabras de s a d. */
s32 func_8002D540(u32 *d, u32 *s, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        *d++ = *s++;
    }
    return 0;
}

extern s16 D_8007CA20, D_8007CC4E;
extern u16 D_8007CC58, D_8007CC5A;
extern u8 D_8007CC3C;

/* Dos arranques de un modo (0x103/0xFF y 0x105/0x101 segun c); devuelven el valor puesto (queda en v0). */
s32 func_8004F968(s32 a, s32 b, s32 c) {
    s32 v;
    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CC4E = 0;
    D_8007CC3C = 1;
    v = c != 0 ? 0x103 : 0xFF;
    D_8007CA20 = v;
    return v;
}

s32 func_8004F99C(s32 a, s32 b, s32 c) {
    s32 v;
    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CC4E = 0;
    v = c != 0 ? 0x105 : 0x101;
    D_8007CA20 = v;
    return v;
}

extern s16 jugando, D_8007CC4C;
extern s32 D_8007CA58;
extern s8 D_8007CC18, D_8007CA38;

/* Sale del modo de func_8004F968: si estaba puesto (D_8007CC3C == 1) tambien corta el juego. */
s32 func_8004F9C8(void) {
    u8 m = D_8007CC3C;
    D_8007CC4C = 0;
    D_8007CA58 = 0;
    D_8007CA20 = 0;
    if (m == 1) {
        jugando = 0;
        D_8007CC18 = 1;
        D_8007CA38 = 0;
    }
    return m;
}

extern u16 D_8007C8C0, D_8007C8C2;

s32 func_8003DD74(s32 v) {
    D_8007C8C0 = v;
    D_8007C8C2 = v;
    return v & 0xFFFF;
}

extern s8 nivel_actual, D_8007CA01;
extern s32 D_8007CC04;
extern void func_8004C82C(void);

/* Corta el juego y pasa al nivel 13. */
s32 func_800471F8(void) {
    jugando = 0;
    D_8007CA38 = 0;
    D_8007CA01 = 0;
    nivel_actual = 0xD;
    func_8004C82C();
    D_8007CC04 = 2;
    return 2;
}

extern s8 D_8006553C[];

/* Largo de un texto terminado en 0x7F (cuenta la marca); uno vacio se rellena con D_8006553C[0] y cuenta
   como de 1. Lo deja en t+0x16 y pone 0 en t+0x18. */
s32 func_800191D8(s8 *s, u8 *t) {
    u32 n = 0;
    u32 c = 0x45;
    while (c != 0x7F) {
        c = s[n] & 0xFFFF;
        n = (n + 1) & 0xFFFF;
    }
    if (n == 1) {
        n = 2;
        s[0] = D_8006553C[0];
    }
    *(s16 *)(t + 0x16) = SUMA_TRAMPA(n, -1);
    *(s16 *)(t + 0x18) = 0;
    return SUMA_TRAMPA(n, -1);
}

extern u16 D_8007C8D8[], D_8007CC00;
extern s32 D_8007CB34;

/* Pasa al nivel elegido en la tabla (D_8007C8D8[D_8007CC00]) guardando el actual, y corta el juego. */
s32 func_80047010(void) {
    u16 n;
    D_8007CA01 = nivel_actual;
    n = D_8007C8D8[D_8007CC00];
    nivel_actual = n;
    jugando = 0;
    D_8007CA38 = 0;
    D_8007CC04 = 0;
    D_8007CB34 = 0;
    return n;
}

extern s32 func_80021CE4(s32 x);
extern void func_8001C45C(s32 *v);

/* Una direccion al azar hacia arriba (y negativa), de largo 1. Devuelve su z (queda en v0). */
s32 func_800224B8(s32 *d) {
    s32 v[3];
    v[0] = SUMA_TRAMPA(func_80021CE4(0x2000), -0x1000);
    v[2] = SUMA_TRAMPA(func_80021CE4(0x2000), -0x1000);
    v[1] = RESTA_TRAMPA(0, func_80021CE4(0x1000));
    func_8001C45C(v);
    d[0] = v[0];
    d[1] = v[1];
    d[2] = v[2];
    return v[2];
}

extern u16 D_8007CC50;
extern u8 D_800D2AD0[];         /* nombres de 0x40 bytes */
extern s8 D_8007961C[0x40];     /* el nombre elegido, en letras de la fuente */
extern u8 D_800795FC[];
extern s8 ascii_a_letra[];
extern s32 func_8001951C(s8 *d, u8 *s);

/* Copia el nombre elegido (D_8007CC50) y lo pasa de ASCII a letras de la fuente, hasta el 0 incluido;
   despues le mide el largo. Devuelve lo que queda en v0. */
s32 func_80019738(void) {
    u32 i;
    s8 c = 1;
    if (SUMA_TRAMPA(D_8007CC58, D_8007CC5A) != 0) {
        func_8001951C(D_8007961C, D_800D2AD0 + (D_8007CC50 << 6));
        for (i = 0; i != 0x40 && c != 0; i = (i + 1) & 0xFFFF) {
            c = D_8007961C[i];
            D_8007961C[i] = ascii_a_letra[c];
        }
    }
    return func_800191D8(D_8007961C, D_800795FC);
}

extern char **D_8006CDD4[];     /* listas de nombres de archivo (terminadas en NULL) */
extern char D_8007C86C[], D_8007C9D4[];
extern s32 sprintf(char *d, const char *f, ...);
extern s32 func_8001B0C8(char *nombre);
extern void func_80029530(void *dst, void *src, s32 n);

/* Escribe en dst la lista k de archivos: la cuenta (2 bytes) y despues los 0x20 bytes de cada uno (lo
   que da func_8001B0C8 con su ruta completa). Devuelve la cuenta (queda en v0). */
s32 func_80024450(s32 k, void *dst) {
    struct {
        s32 n;
        s32 ficha[0x64];
    } t;
    char ruta[0x80];
    char **lista = D_8006CDD4[k];
    s32 i;

    t.n = 0;
    do {
        sprintf(ruta, D_8007C86C, D_8007C9D4, lista[t.n]);
        if (lista[t.n] != NULL) {
            s32 f = func_8001B0C8(ruta);
            t.ficha[t.n++] = f;
        }
    } while (lista[t.n] != NULL);
    func_80029530(dst, &t.n, 2);
    for (i = 0; i != t.n; i++) {
        func_80029530(dst, (void *)t.ficha[i], 0x20);
    }
    return t.n;
}

extern u8 D_800654C4[];          /* signos de SJIS 0x8140.. en ASCII */

/* Pasa un nombre de SJIS (la tarjeta de memoria) a ASCII, hasta 0x40 bytes: letras y numeros de ancho
   completo a los comunes, los signos por tabla, el espacio y lo desconocido a '#' y los kanji a '*'.
   Devuelve por donde quedo el origen (queda en v0). */
s32 func_8001951C(s8 *d, u8 *s0) {
    u8 *s = s0;
    u32 c, c2;
    while ((c = *s) != 0 && s < s0 + 0x40) {
        if (c < 0x80) {
            *d++ = *s++;
            continue;
        }
        if (c == 0x80 || c == 0xA0) {
            *d++ = '#';
            s++;
            continue;
        }
        if (c < 0x81 || c >= 0xFD) {
            *d++ = '#';
            s++;
            continue;
        }
        if (c == 0x81 && (c2 = s[1]) >= 0x40 && c2 < 0x98) {
            s += 2;
            *d++ = D_800654C4[c2 - 0x40];
        } else if (c == 0x82 && (c2 = s[1]) >= 0x4F && c2 < 0x59) {
            *d++ = c2 - 0x1F;
            s += 2;
        } else if (c == 0x82 && (c2 = s[1]) >= 0x60 && c2 < 0x7B) {
            *d++ = c2 - 0x1F;
            s += 2;
        } else if (c == 0x82 && (c2 = s[1]) >= 0x81 && c2 < 0x9C) {
            *d++ = c2 - 0x20;
            s += 2;
        } else if (c >= 0xA1 && c < 0xE0) {
            *d++ = '*';
            s++;
        } else {
            *d++ = '*';
            s += 2;
        }
    }
    *d = 0;
    return (s32)s;
}

/* Arranques de pantallas y modos: dejan los contadores en 0 y ponen el modo de D_8007CA20. Cada una
   devuelve el ultimo valor puesto (queda en v0). */
extern s16 D_8007CC56;
extern s32 D_8007CC44;
extern u16 D_8007CA1C, D_8007CA1E;

s32 func_8004F2BC(void) {
    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CC50 = 0;
    D_8007CC4E = 0;
    D_8007CA20 = 0xE3;
    return 0xE3;
}

s32 func_8004F4F0(void) {
    D_8007CC4E = 3;
    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CA20 = 0xEF;
    return 0xEF;
}

s32 func_8004F94C(void) {
    D_8007CC4E = 4;
    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CA20 = 0xF6;
    return 0xF6;
}

s32 func_8004F9F8(void) {
    D_8007CC44 = 1;
    D_8007CA20 = 0;
    D_8007CC56 = 0xF;
    return 0xF;
}

s32 func_80047240(void) {
    D_8007CA1C = 6;
    D_8007CA38 = 1;
    D_8007CA1E = 1;
    D_8007CA20 = 0xDF;
    return 0xDF;
}

/* Corta el juego y pasa al nivel 13 guardando el actual. */
s32 func_80046B50(void) {
    s8 n = nivel_actual;
    jugando = 0;
    D_8007CA01 = n;
    D_8007CA38 = 0;
    nivel_actual = 0xD;
    return 0xD;
}

extern u8 *D_8007CB8C;
extern s32 D_8007CB78;

s32 func_800318D4(void) {
    u8 f = D_8007CB8C[0x20] | 0x80;
    D_8007CB8C[0x20] = f;
    D_8007CB78 = 0;
    return f;
}
