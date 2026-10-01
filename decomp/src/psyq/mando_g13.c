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
            D_8006CFDC[D_8006CFC4] = -1;
            D_8006CFA4(p);
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
void func_8002805C(Puerto *p) {
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
                        if (B(p, 0x5E + i) == m) {
                            B(p, 0x57 + i) = 1;
                        }
                    }
                }
            }
        }
    } else if (((u8)(p->tipo - 4) < 2 || p->tipo == 7) && p->_E6 == 0 && B(p, 0x34) >= 2) {
        a = *(u8 **)((u8 *)p + 0x28);
        if ((a[0] & 0xC0) == 0x40 && (a[1] & 1) && D_8006CFCC + 0xA < 0x3D) {
            B(p, 0x58) = 1;
            B(p, 0x57) = 1;
            D_8006CFCC += 0xA;
        }
    } else if (p->tipo == 3) {
        B(p, 0x57) = 1;
    } else if (p->_E6 == 0) {
        for (i = 5; i >= 0; i--) {
            B(p, 0x57 + i) = 1;
        }
    }
}
