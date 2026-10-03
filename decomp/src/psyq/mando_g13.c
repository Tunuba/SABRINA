#include "juego.h"

/* libpad: lo que se hace con la respuesta de un mando despues de cada intercambio. */

/* Un puerto de mando (solo los campos que se usan). */
typedef struct Puerto {
    u8 _00[0x0C];
    void *multitap;                  /* 0x0C */
    struct Puerto *principal;        /* 0x10, el mismo puerto si no va por multitap */
    s32 _14;                         /* 0x14 */
    s32 (*paso)(struct Puerto *p);   /* 0x18 */
    u8 _1C[0x14];
    u8 *salida;                      /* 0x30, el bufer del juego */
    u8 _34;
    u8 largo;                        /* 0x35 */
    u8 _36;
    u8 activo_a;                     /* 0x37 */
    u8 activo_b;                     /* 0x38 */
    u8 _39;
    u8 _3A[2];
    u8 *respuesta;                   /* 0x3C, lo que contesto el mando */
    u8 _40[4];
    u8 largo_tipo;                   /* 0x44 */
    u8 _45;
    u8 estado;                       /* 0x46 */
    u8 _47;
    u8 _48;
    u8 _49;
    u8 _4A;
    u8 _4B;
    s32 _4C;                         /* 0x4C, cuantas veces se desconecto */
    u8 _50;
    u8 _51[0x95];
    u16 _E6;                         /* 0xE6 */
    u8 tipo;                         /* 0xE8 */
} Puerto;

extern s32 (*D_8006CF88)(Puerto *p);  /* avisa que cambio el mando */
s32 func_80028D40(Puerto *p, s32 a);
extern s32 func_80026ECC(Puerto *p);

/* Devuelve (v0) lo que deja el original en cada camino. */
s32 func_8002886C(Puerto *p) {
    u8 *r = p->respuesta;
    u8 *s, *q;
    u32 tipo;
    u8 antes;
    s32 i, k;

    if (!(r[0] & 0xF0)) {
        p->salida[0] = 0xFF;
        p->salida[1] = 0;
        p->tipo = 0;
        p->largo = 0;
        return D_8006CF88(p);
    }
    if (p != p->principal && ((r[1] != 0 && r[1] != 0x5A) || (r[0] >> 4) == 8)) {
        return func_80028D40(p, 0xFF);
    }
    r = p->respuesta;
    s = p->salida;
    tipo = r[0] >> 4;
    antes = p->tipo;
    if (r[1] == 0x5A) {
        if (antes == 8) {
            s[0] = 0;
        } else if (tipo != 0xF) {
            q = p->respuesta;
            p->tipo = tipo;
            s[0] = 0;
            s[1] = *q++;
            s += 2;
            if (p != p->principal) {
                p->largo = 8;
                q++;
                for (i = 2; i < 8; i++) {
                    *s++ = *q++;
                }
            } else if (tipo == 8) {
                p->largo = 2;
            } else {
                p->largo = p->largo_tipo;
                q++;
                for (i = 2; i < p->largo; i++) {
                    *s++ = *q++;
                }
            }
        }
    }
    if ((p->respuesta[1] == 0 && (p->estado != 1 || p->_14 != 0) && p->_50 == 0) || p->tipo != antes) {
        D_8006CF88(p);
    }
    if (p->multitap != NULL || p->activo_a == 0) {
        p->_4A = 0;
    }
    if (p->estado == 0xFF) {
        return 0xFD;
    }
    if ((u8)(p->estado - 2) < 0xFC && p->respuesta[0] != 0xF3) {
        return D_8006CF88(p);
    }
    if (p->tipo == 8) {
        if (p->estado != 0) {
            k = p->estado + 1;
            p->estado = k;
            return k;
        }
    } else if (p->estado != 0) {
        k = p == p->principal ? p->activo_a : p->activo_b;
        if (k == 0) {
            return 0;
        }
    }
    switch (p->estado) {
    case 1:
        p->_47 = 0;
        k = p->estado + 1;
        p->estado = k;
        return k;
    case 0:
        if (p->multitap == NULL && p->activo_a != 0) {
            return p->activo_a;
        }
        if (p->tipo == 8 && p->multitap != NULL && ((Puerto *)p->multitap)->respuesta[0] == 0xFF) {
            p->_49 = 2;
            p->estado = 0xFF;
            return 2;
        }
        p->_49 = 1;
        k = p->estado + 1;
        p->estado = k;
        return k;
    case 0xFE:
        p->estado = 0xFF;
        return 0xFF;
    case 0xFF:
        return 0xFF;
    default:
        k = p->paso != NULL ? p->paso(p) : func_80026ECC(p);
        p->estado += k;
        return k;
    }
}

/* Si alguno de los cuatro puertos del multitap m tiene activo_b. */
static s32 algun_hijo(u8 *m) {
    return m[0x38] != 0 || m[0xF0 + 0x38] != 0 || m[0x1E0 + 0x38] != 0 || m[0x2D0 + 0x38] != 0;
}

/* El mando no contesto bien: revisa los del multitap, cuenta la desconexion y, tras varios intentos, lo
 * da por desconectado. Devuelve (v0) lo que deja el original en cada camino. */
s32 func_80028D40(Puerto *p, s32 a) {
    u32 tipo = p->respuesta[0] >> 4;
    u8 *m;
    s32 i, k, v, b, est;

    if (p->tipo != 8) {
        if (tipo == 8 && p == p->principal) {
            p->tipo = tipo;
            p->salida[0] = 0xFF;
            p->salida[1] = 0x80;
            p->largo = 2;
        }
    }
    if (p->tipo == 8 && p->multitap != NULL) {
        for (i = 0; i < 4; i++) {
            func_80028D40((Puerto *)((u8 *)p->multitap + i * 0xF0), -1);
        }
    }
    m = (u8 *)p->principal->multitap;
    if (p->multitap != NULL) {
        if (p->activo_a == 0 && algun_hijo(m)) {
            goto marcar;
        }
    } else if (p->activo_b == 0 && (p->principal->activo_a != 0 || algun_hijo(m))) {
        goto marcar;
    }
    v = p->activo_a;
    b = p->activo_b;
    est = p->estado;
    p->activo_a = 0;
    p->_4C++;
    p->_39 = b;
    p->activo_b = v;
    if (est != 0) {
        if (est == 1) {
            k = p->_4A;
            if (k < 0xB && p->tipo != 8) {
                p->_4A = k + 1;
                return k + 1;
            }
            if (p->_E6 != 0) {
                k = p->_4A;
                if (k < 0x15) {
                    p->_4A = k + 1;
                    return k + 1;
                }
                D_8006CF88(p);
            }
            p->_49 = 2;
            if (p->tipo == 8) {
                p->estado = 0xFE;
                return 0xFE;
            }
            if (p->multitap != NULL) {
                p->activo_b = 0;
                p->activo_a = 0;
            }
            p->estado = 0xFF;
            return 0xFF;
        }
        k = p->_4A;
        if (k < 0xB) {
            p->_4A = k + 1;
            return k + 1;
        }
    }
    if (p->_49 != 0) {
        p->salida[0] = 0xFF;
        p->salida[1] = 0;
        p->tipo = 0;
        p->largo = 0;
        D_8006CF88(p);
    }
    if (tipo == 8) {
        if (p->multitap != NULL) {
            p->tipo = tipo;
            p->salida[1] = 0x80;
        }
        return 0x80;
    }
    if (p->tipo != 8) {
        return p->tipo;
    }
    p->tipo = 0;
    p->salida[1] = 0;
    return (s32)p->salida;

marcar:
    if (p->_4A != 0) {
        return 1;
    }
    p->_4A = 1;
    return 1;
}

/* Los registros del puerto serie de los mandos (SIO0). */
typedef struct {
    u8 dato;                         /* 0x00 */
    u8 _01[3];
    u16 estado;                      /* 0x04 */
    u16 _06;
    u16 modo;                        /* 0x08 */
    u16 control;                     /* 0x0A */
    u16 _0C;
    u16 baudios;                     /* 0x0E */
} PuertoSerie;

extern volatile PuertoSerie *D_8006CF70;
extern volatile s32 *D_8006CF6C;     /* las interrupciones pendientes */
extern s32 D_8006CFC4;               /* el puerto (0 o 1) */
extern s32 D_8006CFDC[];             /* por puerto: cuantos del multitap faltan cerrar */
extern void (*D_8006CFA4)(Puerto *p);
extern void (*D_8006CFA8)(Puerto *p);
extern void func_8002908C(s32 espera);
extern s32 func_800290AC(void);
extern s32 func_800266B4(void);
extern void func_80026744(void);

/* Manda un byte y espera el acuse (bit 0x80 de las interrupciones); 0 si no llega. */
static s32 enviar(s32 byte) {
    D_8006CF70->dato = byte;
    func_8002908C(0x3C);
    if (func_800266B4() == 0) {
        return 0;
    }
    func_80026744();
    (void)D_8006CF70->dato;
    func_8002908C(0x1AE);
    while (!(*D_8006CF6C & 0x80)) {
        if (func_800290AC() != 0) {
            return 0;
        }
    }
    return 1;
}

/* Reinicia el puerto serie del mando p, cierra los del multitap que quedaron y, si el puerto sigue
 * ocupado, le manda 01 42 01 esperando cada acuse. Devuelve 1 si se puede seguir con el mando. */
s32 func_80025EF8(Puerto *p) {
    volatile PuertoSerie *s = D_8006CF70;
    s32 n;

    s->control = 0x40;
    s->control = 0;
    s->modo = 0xD;
    s->baudios = 0x88;
    func_8002908C(p->tipo == 8 ? 0x50 : 0x91);
    D_8006CF70->control = D_8006CFC4 != 0 ? 0x3003 : 0x1003;
    if (D_8006CFDC[D_8006CFC4] >= 0) {
        while (D_8006CFDC[D_8006CFC4] > 0) {
            n = --D_8006CFDC[D_8006CFC4];
            D_8006CFA4((Puerto *)((u8 *)p->multitap + n * 0xF0));
        }
        if (D_8006CFDC[D_8006CFC4] == 0) {
            s32 *c = &D_8006CFDC[D_8006CFC4];
            *c = -1;
            /* a1 llega con la direccion de la cuenta, como en el original */
            ((void (*)(Puerto *, s32 *))D_8006CFA4)(p, c);
            D_8006CFA8(p);
        }
    }
    s = D_8006CF70;
    if (s->estado & 0x200) {
        s->control |= 0x10;
        if (!(s->estado & 0x200)) {
            *D_8006CF6C = -0x81;
        } else {
            while (func_800290AC() == 0) {
            }
            D_8006CF70->dato = 1;
            func_8002908C(0x7D0);
            if (func_800266B4() == 0) {
                return 0;
            }
            func_80026744();
            (void)D_8006CF70->dato;
            func_8002908C(0x1AE);
            while (!(*D_8006CF6C & 0x80)) {
                if (func_800290AC() != 0) {
                    return 0;
                }
            }
            if (!enviar(0x42)) {
                return 0;
            }
            D_8006CF70->dato = 1;
            func_8002908C(0x3C);
            if (func_800266B4() != 0) {
                func_80026744();
                (void)D_8006CF70->dato;
            }
            return 0;
        }
    }
    if (p->_50 == 0) {
        return 1;
    }
    return p->activo_a == 0;
}

extern s32 D_8006CFCC;               /* lo que piden los motores de vibracion de todos los mandos (tope 60) */
extern void bzero(void *p, s32 n);

#define B(p, d) (((u8 *)(p))[d])

/* Arma los seis bytes de los motores del mando (0x57 a 0x5C): con la tabla de actuadores (0xE6, 0x28)
 * enciende los que piden su motor si alcanza la corriente; sin ella, segun el tipo de mando. */
s32 func_8002805C(Puerto *p) {
    s32 n, m, i, mascara, usar, k;
    u8 *a;

    bzero((u8 *)p + 0x57, 6);
    if (p->_E6 != 0 && *(u8 **)((u8 *)p + 0x28) != NULL) {
        n = B(p, 0x34) < 7 ? B(p, 0x34) : 6;
        for (m = 0; m < B(p, 0xE9); m++) {
            a = *(u8 **)((u8 *)p + 4) + m * 5;
            usar = 0;
            mascara = a[2] != 0 ? 0xFF : 1;
            for (i = 0; i < n; i++) {
                if (B(p, 0x5D + i) == m && ((*(u8 **)((u8 *)p + 0x28))[i] & mascara)) {
                    usar = 1;
                    break;
                }
            }
            if (usar) {
                k = D_8006CFCC + a[3];
                if (k < 0x3D) {
                    D_8006CFCC = k;
                    for (i = 0; i < n; i++) {
                        if (B(p, 0x5D + i) == m) {
                            B(p, 0x57 + i) = 1;
                        }
                    }
                }
            }
        }
        return 0;   /* lo que queda en v0 */
    }
    if (((u8)(p->tipo - 4) < 2 || p->tipo == 7) && p->_E6 == 0 && B(p, 0x34) >= 2) {
        a = *(u8 **)((u8 *)p + 0x28);
        if ((a[0] & 0xC0) != 0x40) {
            return a[0] & 0xC0;
        }
        if (!(a[1] & 1)) {
            return 0;
        }
        if (D_8006CFCC + 0xA >= 0x3D) {
            return 1;
        }
        B(p, 0x58) = 1;
        B(p, 0x57) = 1;
        D_8006CFCC += 0xA;
        return D_8006CFCC;
    }
    if (p->tipo == 3) {
        B(p, 0x57) = 1;
    } else if (p->_E6 == 0) {
        for (i = 5; i >= 0; i--) {
            B(p, 0x57 + i) = 1;
        }
    }
    return 1;
}

extern void *D_8006CF9C, *D_8006CFA0;
extern void func_800285FC(void), func_80028C54(void);

/* Pone las funciones del mando de siempre. Devuelve la ultima. */
void *func_80028D0C(void) {
    D_8006CF9C = func_800285FC;
    D_8006CFA0 = func_80028C54;
    *(void **)&D_8006CFA4 = func_8002886C;
    return func_8002886C;
}

extern s32 func_80016970(s32 canal, s32 f);

/* Pone f en el canal 3 de interrupciones. */
s32 func_80029ED4(s32 f) {
    return func_80016970(3, f);
}

extern Puerto *(*D_8006CF98)(s32 a, s32 b, s32 c);  /* busca el puerto */

/* PadInfo: un dato del mando (1 tipo, 2 actuadores, 3 modo, 4 cada actuador, 100 desconexiones). */
s32 func_80027AD0(s32 puerto, s32 que, s32 n) {
    Puerto *p = D_8006CF98(puerto, que, n);

    switch (que) {
    case 1:
        return p->tipo;
    case 2:
        return p->_E6;
    case 3:
        return B(p, 0xE4);
    case 4:
        if (n < 0) {
            return B(p, 0xE3);
        }
        if (n < B(p, 0xE3)) {
            return (*(u16 **)p)[n];
        }
        return 0;
    case 100:
        return p->_4C;
    default:
        return 0;
    }
}

extern u8 D_80090A98[0x1E0];         /* los dos puertos */
extern u8 D_80090C78[0x780];         /* los cuatro del multitap de cada uno */
extern u8 D_80090A08[], D_80090A50[];  /* lo que contestan y lo que se les manda (0x23 por puerto) */
extern s32 D_8006D018[2];
extern s32 D_8006CFBC, D_8006CFD0;
extern void *D_8006CF84, *D_8006CF8C, *D_8006CF90, *D_8006CF94, *D_8006CFB8;
extern void func_80027F4C(void), func_800282D8(void);
s32 func_80027DF0(s32 r);
s32 func_80027D7C(Puerto *p);
extern void func_80028354(void), func_80027F08(void);
extern void func_80025DA8(void);

/* Arma un puerto (o uno del multitap) vacio: sin mando y con los motores apagados. */
static void vaciar(u8 *p, u8 *resp, u8 *envio) {
    s32 i;

    *(u8 **)(p + 0x3C) = resp;
    *(u8 **)(p + 0x40) = envio;
    for (i = 5; i >= 0; i--) {
        p[0x5D + 5 - i] = 0xFF;
    }
}

/* PadInitDirect: pone las funciones de libpad, limpia los dos puertos y los de sus multitap y los deja
 * escribiendo en los buferes del juego. Devuelve 1. */
s32 func_800283C4(u8 *buf1, u8 *buf2) {
    u8 *p, *mt, *c;
    s32 i, j;

    D_8006CFBC = 0;
    D_8006CFD0 = 1;
    func_80028D0C();
    D_8006CF84 = func_80027DF0;
    *(void **)&D_8006CF88 = func_80027D7C;
    D_8006CF8C = func_80027F4C;
    D_8006CF90 = func_8002805C;
    D_8006CF94 = func_800282D8;
    *(void **)&D_8006CF98 = func_80028354;
    D_8006CFB8 = D_80090A98;
    *(void **)&D_8006CFA8 = func_80027F08;
    bzero(D_80090A98, 0x1E0);
    bzero(D_80090C78, 0x780);
    *(u8 **)(D_80090A98 + 0x30) = buf1;
    *(u8 **)(D_80090A98 + 0x120) = buf2;
    for (i = 0; i < 2; i++) {
        p = D_80090A98 + i * 0xF0;
        mt = D_80090C78 + i * 0x3C0;
        *(u8 **)(p + 0xC) = mt;
        *(u8 **)(p + 0x10) = p;
        (*(u8 **)(p + 0x30))[0] = 0xFF;
        (*(u8 **)(p + 0x30))[1] = 0;
        D_8006D018[i] = 0;
        vaciar(p, D_80090A08 + i * 0x23, D_80090A50 + i * 0x23);
        for (j = 0; j < 4; j++) {
            c = mt + j * 0xF0;
            *(u8 **)(c + 0x10) = p;
            *(u8 **)(c + 0x30) = *(u8 **)(p + 0x30) + 2 + j * 8;
            c[0x38] = 0xFF;
            c[0x36] = 0;
            c[0x34] = 0;
            (*(u8 **)(c + 0x30))[0] = 0xFF;
            (*(u8 **)(c + 0x30))[1] = 0;
            vaciar(c, D_80090A08 + i * 0x23 + 2 + j * 8, D_80090A50 + i * 0x23 + 3 + j * 8);
        }
    }
    func_80025DA8();
    D_8006CFBC = 1;
    return 1;
}

/* Los pasos de una orden al mando: arrancan si D_8006CFA0 (con los mismos argumentos) deja empezar. */
#define PUEDE_EMPEZAR ((s32 (*)(Puerto *p, ...))D_8006CFA0)
extern s32 func_80026C18();
extern s32 func_80026C34();
extern s32 func_80026CFC();
extern s32 func_80026D50();

/* El paso de la orden con respuesta esperada: si el mando contesto lo esperado (0x53) termina en el
   estado 2, si no lo marca 0xFE; sin respuesta avisa con D_8006CF88. */
s32 func_80026D50(Puerto *p) {
    u8 *b = (u8 *)p;
    if (b[0x53] != 0) {
        if (b[0x46] == 2) {
            return 1;
        }
        b[0x46] = 0xFE;
        return 0;
    }
    D_8006CF88(p);
    return 0;
}

s32 func_80027248(Puerto *p, s32 dato) {
    u8 *b = (u8 *)p;
    if (PUEDE_EMPEZAR(p, dato) != 0) {
        return 0;
    }
    b[0x46] = 1;
    *(s32 (**)())(b + 0x14) = func_80026C18;
    *(s32 *)(b + 0x20) = dato;
    *(s32 (**)())(b + 0x18) = func_80026C34;
    return 1;
}

s32 func_800272B0(Puerto *p, s32 a, s32 c) {
    u8 *b = (u8 *)p;
    if (PUEDE_EMPEZAR(p, a, c) != 0) {
        return 0;
    }
    b[0x46] = 1;
    *(s32 (**)())(b + 0x14) = func_80026CFC;
    *(s32 (**)())(b + 0x18) = func_80026D50;
    b[0x51] = a;
    b[0x52] = c;
    b[0x53] = (u8)a == b[0xE4];
    return 1;
}


s32 func_80027D44(s32 a, s32 dato, s32 c) {
    return func_80027248(D_8006CF98(a, dato, c), dato);
}

/* PadInfoAct: con act < 0 cuantos actuadores hay; si no, el dato que (1 a 5) del actuador act. */
s32 func_80027BC8(s32 puerto, s32 act, s32 que) {
    u8 *b = (u8 *)D_8006CF98(puerto, act, que);
    u8 *a;
    if (act < 0) {
        return b[0xE9];
    }
    if (act >= b[0xE9]) {
        return 0;
    }
    a = *(u8 **)(b + 4) + act * 5;
    switch (que) {
    case 1:
        return a[0];
    case 2:
        return a[1];
    case 3:
        return a[2];
    case 4:
        return a[3];
    case 5:
        return a[4];
    }
    return 0;
}

/* PadInfoMode: con modo < 0 cuantos modos hay; con i < 0 cuantos datos tiene el modo; si no, el dato i. */
s32 func_80027C9C(s32 puerto, s32 modo, s32 i) {
    u8 *b = (u8 *)D_8006CF98(puerto, modo, i);
    u8 *m;
    if (modo < 0) {
        return b[0xEA];
    }
    if (modo >= b[0xEA]) {
        return 0;
    }
    m = *(u8 **)(b + 8) + modo * 8;
    if (i < 0) {
        return m[0];
    }
    if (i >= m[0]) {
        return 0;
    }
    return (*(u8 **)(m + 4))[i];
}

/* Cierra un puerto que estaba abierto (0x49): borra su estado y llena con 0xFF los 6 bytes desde 0x5D. */
s32 func_80027D7C(Puerto *p) {
    u8 *b = (u8 *)p;
    u8 *q;
    s32 n;
    if (b[0x49] == 0) {
        return 0;
    }
    q = b + 0x5D;
    b[0x49] = 0;
    b[0x46] = 0;
    *(s16 *)(b + 0xE6) = 0;
    *(s32 *)(b + 0x14) = 0;
    *(s32 *)(b + 0x18) = 0;
    b[0xE3] = 0;
    b[0xE4] = 0;
    *(s16 *)(b + 0xE6) = 0;
    b[0xE9] = 0;
    b[0xEA] = 0;
    *(s32 *)(b + 0) = 0;
    *(s32 *)(b + 4) = 0;
    *(s32 *)(b + 8) = 0;
    b[0x37] = 0;
    b[0x38] = 0;
    b[0x39] = 0;
    n = 5;
    do {
        *q++ = 0xFF;
    } while (--n >= 0);
    return n;
}

extern s32 D_8006CFC8, D_8006CFD8;
extern u8 *D_8006D014;

/* Fin del intercambio con un puerto: anota el resultado r, cierra lo del puerto (r == 0: si contesto un
   multitap, 4 que cerrar; r != -9: func_80028D40) y pasa al siguiente hasta que uno empiece o se acaben.
   Devuelve lo que queda en v0 (1 o lo que dio func_80025EF8). */
s32 func_80027DF0(s32 r) {
    s32 i, v;
    Puerto *p;
    do {
        i = D_8006CFC4;
        *(s16 *)(D_8006D014 + 0xA) = 0;
        D_8006D018[i] = r;
        p = (Puerto *)(D_80090A98 + i * 0xF0);
        if (r != -9) {
            if (r == 0) {
                D_8006CFDC[i] = ((**(u8 **)((u8 *)p + 0x3C) >> 4) == 8) * 4;
            } else {
                func_80028D40(p, r);
            }
        }
        D_8006CFC8 = 0;
        i = D_8006CFC4 + 1;
        D_8006CFC4 = i;
        if (D_8006CFD8 < i) {
            v = 1;
        } else {
            v = func_80025EF8((Puerto *)(D_80090A98 + i * 0xF0));
        }
        r = 0xFFFF;
    } while (v == 0);
    return v;
}

extern s32 func_80026DC4(Puerto *p, s32 a);
extern s32 func_80026DE4(Puerto *p, s32 a);
extern s32 func_80026E04(Puerto *p, s32 a);
extern s32 func_80026E24(Puerto *p, s32 a);

/* Un paso de la orden al mando segun su estado (0x46): 2, 3 o 4 (con 0x48 la variante). Devuelve lo que
   queda en v0. */
s32 func_80026778(Puerto *p, s32 a) {
    u8 *b = (u8 *)p;
    u32 e = b[0x46];
    if (e == 3) {
        return func_80026DE4(p, b[0x47]);
    }
    if (e < 4) {
        if (e == 2) {
            return func_80026DC4(p, b[0x47]);
        }
        return 2;
    }
    if (e != 4) {
        return 4;
    }
    if (b[0x48] != 0) {
        return func_80026E24(p, a);
    }
    return func_80026E04(p, b[0x47]);
}

extern u8 *D_800909F8;          /* por donde se va copiando la descripcion de un modo */

/* Lee la descripcion del mando, un dato por intercambio (indice en 0x47): (2) los modos (u16 cada uno, en
   la tabla de +0), (3) los actuadores (5 bytes cada uno, en +4) y (4) lo de cada modo (en +8, con sus
   bytes a continuacion). 0xEE marca si algo cambio. Devuelve 1 al terminar una tabla y 0 si no. */
s32 func_80026820(Puerto *p) {
    u8 *b = (u8 *)p;
    u8 *r, *a, *t, *src;
    u32 e = b[0x46];
    s32 n;
    u16 v;

    if (e == 3) {
        r = *(u8 **)(b + 0x3C);
        if (r[2] != 0 || r[3] != 0) {
            return 0;
        }
        a = *(u8 **)(b + 4) + b[0x47] * 5;
        if (a[0] == r[4] && a[1] == (r[5] & 0x7F) && a[2] == r[6] && a[3] == r[7] && a[4] == (r[5] >> 7)) {
            *(u16 *)(b + 0xEE) = 0;
        } else {
            *(u16 *)(b + 0xEE) = 0xFFFF;
        }
        a[0] = (*(u8 **)(b + 0x3C))[4];
        a[1] = (*(u8 **)(b + 0x3C))[5] & 0x7F;
        a[2] = (*(u8 **)(b + 0x3C))[6];
        a[3] = (*(u8 **)(b + 0x3C))[7];
        a[4] = (*(u8 **)(b + 0x3C))[5] >> 7;
        if (*(u16 *)(b + 0xEE) != 0) {
            return 0;
        }
        b[0xEB] = 0;
        if ((u8)++b[0x47] < b[0xE9]) {
            return 0;
        }
        b[0x47] = 0;
        b[0x48] = 0;
        return 1;
    }
    if (e < 4) {
        if (e != 2) {
            return 1;
        }
        r = *(u8 **)(b + 0x3C);
        if (r[2] != 0 || r[3] != 0) {
            return 0;
        }
        (*(u16 **)b)[b[0x47]] = r[5] + (r[4] << 8);
        v = (*(u16 **)b)[b[0x47]];
        if (*(u16 *)(b + 0xEE) != v) {
            *(u16 *)(b + 0xEE) = v;
            return 0;
        }
        *(u16 *)(b + 0xEE) = 0;
        b[0xEB] = 0;
        if ((u8)++b[0x47] < b[0xE3]) {
            return 0;
        }
        b[0x47] = 0;
        return 1;
    }
    if (e != 4) {
        return 1;
    }
    r = *(u8 **)(b + 0x3C);
    if (r[2] != 0) {
        b[0x48] = 0;
        return 0;
    }
    t = *(u8 **)(b + 8) + b[0x47] * 8;
    if (b[0x48] == 0) {
        b[0x48] = r[4];
        t[0] = r[4];
        src = *(u8 **)(b + 0x3C) + 5;
        if (b[0x47] == 0) {
            D_800909F8 = *(u8 **)(b + 8) + b[0xEA] * 8;
        } else {
            D_800909F8 = *(u8 **)(t - 4) + ((t[-8] + 3) & 0x1FC);
        }
        *(u8 **)(t + 4) = D_800909F8;
        n = 2;
    } else {
        src = r + 3;
        n = 4;
    }
    for (; n != -1; n--) {
        if (b[0x48] == 0) {
            goto fin;
        }
        if (!(D_800909F8 < b + 0xE3)) {
            b[0x47] = 0;
            b[0x48] = 0;
            return 0;
        }
        if (*D_800909F8 != *src) {
            *(u16 *)(b + 0xEE) = 0xFFFF;
        }
        *D_800909F8++ = *src++;
        b[0x48]--;
    }
    if (b[0x48] != 0) {
        return 0;
    }
fin:
    if (*(u16 *)(b + 0xEE) != 0) {
        *(u16 *)(b + 0xEE) = 0;
        b[0x48] = 0;
        return 0;
    }
    if ((u8)++b[0x47] < b[0xEA]) {
        b[0x48] = 0;
        b[0xEB] = 0;
        return 0;
    }
    b[0x49] = 6;
    b[0x46] = 0xFE;
    b[0xEB] = 0;
    return 0;
}

/* Paso de la orden 0x4D: deja la respuesta en +0x2C. Devuelve 6 (queda en v0). */
s32 func_80026C18(Puerto *p) {
    /* volatile: el original escribe en este orden (cuenta si p apunta al hardware) */
    volatile u8 *b = (volatile u8 *)p;
    s32 r = *(volatile s32 *)(b + 0x20);
    b[0x37] = 0x4D;
    b[0x36] = 6;
    *(volatile s32 *)(b + 0x2C) = r;
    return 6;
}

/* Paso que arma la orden segun el estado: 2 pide 0x44 (respuesta en 0x51), 3 pide 0x4D (en 0x5D).
   Devuelve lo que queda en v0. */
s32 func_80026CFC(Puerto *p) {
    u8 *b = (u8 *)p;
    u32 e = b[0x46];
    if (e == 2) {
        b[0x37] = 0x44;
        *(u8 **)(b + 0x2C) = b + 0x51;
        b[0x36] = e;
        return (s32)(b + 0x51);
    }
    if (e == 3) {
        b[0x37] = 0x4D;
        *(u8 **)(b + 0x2C) = b + 0x5D;
        b[0x36] = 6;
        return 6;
    }
    return 0x4D;
}
