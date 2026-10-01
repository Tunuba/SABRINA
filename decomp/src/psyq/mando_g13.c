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
