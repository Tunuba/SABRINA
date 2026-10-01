#include "objeto.h"

/* Un objeto que se activa cuando Sabrina pasa por su zona: abre la salida del nivel, empieza una pista,
 * muestra un letrero o despierta a otro objeto, segun su estado. */

typedef struct {
    s32 _00;
    s32 a[5];                        /* 0x04, la zona: 0, 0x640000, 0, 0x640000, 0 al reiniciar */
    u8 _18[4];
    s32 pista;                       /* 0x1C */
    s32 activo;                      /* 0x20, Sabrina ya paso */
    s32 espera;                      /* 0x24, pasos que quedan del letrero */
    s32 indice;                      /* 0x28 */
    s32 listo;                       /* 0x2C */
    Objeto *otro;                    /* 0x30 */
    s8 *texto;                       /* 0x34, el letrero */
} ExtraActivador;

extern s8 nivel_actual;
extern s8 D_800C8566;                /* el hechizo de la ultima puerta */
extern s8 D_800C8582, D_800C8583, D_800C8584, D_800C8585;  /* como quedo cada mundo */
extern Objeto *D_80086324[];         /* los objetos por indice */
extern u16 D_8007C8C6;
extern s16 D_8007CA20;
extern Objeto *D_8007CAFC;           /* la camara */
extern s32 D_8007CB30;
extern Objeto *D_8007CBAC, *D_8007CBB0;
extern s32 D_8007CC64, D_8007CC68;

extern void func_800486B8(Objeto *o, s32 distancia);
extern s32 func_80053B98(ExtraActivador *e, s32 x, s32 y, s32 z, s32 a);  /* 1 si el punto esta en la zona */
extern void func_80053F74(s8 *texto);
extern s32 func_8003E060(void);      /* la pista que suena, -1 ninguna */
extern void func_8003DD44(s32 volumen);
extern void func_8003DDA0(s32 pista, s32 a);
extern s32 func_8003DDFC(void);

/* Lo que dice func_80053B98 de Sabrina (1: esta en la zona). */
static s32 zona(ExtraActivador *e) {
    return func_80053B98(e, p_sabrina->x, p_sabrina->y, p_sabrina->z, 1);
}

/* El letrero: al entrar se muestra 200 pasos; cuando se acaba se reinicia la zona. Devuelve lo que el
 * original deja en v0. */
static s32 letrero(Objeto *o, ExtraActivador *e) {
    s32 *d;

    if (e->activo != 0 && e->espera == 0) {
        e->espera = 200;
        D_8007CA20 = 0x3B;
        func_80053F74(e->texto);
        D_8007CC68 = 200;
        return 200;
    }
    if (e->espera == 0) {
        if (zona(e) != 1) {
            return 0;
        }
        e->activo = 1;
        return 1;
    }
    e->espera--;
    if (e->espera != 0) {
        return e->espera;
    }
    e->activo = 0;
    d = (s32 *)((u8 *)o->datos + 0x1C);
    d[0] = 0;
    d[2] = 0;
    d[1] = 0x640000;
    d[3] = 0;
    d[5] = 0;
    d[4] = 0x640000;
    e->_00 = 0;
    e->a[1] = 0;
    e->a[0] = 0x640000;
    e->a[2] = 0;
    e->a[4] = 0;
    e->a[3] = 0x640000;
    o->estado = 0;
    return 0x640000;
}

/* Devuelve (v0) lo que deja el original; en los estados 0 a 3 la direccion a la que salta su tabla. */
s32 func_80054068(Objeto *o) {
    ExtraActivador *e = (ExtraActivador *)&o->extra;
    s8 hecho;
    s32 r;
    Objeto *b;

    switch (o->estado) {
    case 7:
        if (e->activo == 0 && zona(e) == 1) {
            func_8003DDA0(e->pista, 0);
            func_8003DD44((D_8007C8C6 * 15) & 0xFF);
            e->activo = 1;
        }
        break;
    case 4:
        func_800486B8(o, 0x1E0000);
        if (e->otro == NULL) {
            b = D_80086324[e->indice];
            if (b != NULL) {
                e->otro = b;
                *(Objeto **)((u8 *)e->otro + 0x8C) = o;
            }
        }
        break;
    case 3:
        if (D_8007CC64 == 4) {
            D_800C8584 = 1;
        }
        break;
    case 5:
        switch (nivel_actual) {
        case 12:
            hecho = D_800C8585;
            break;
        case 9:
            hecho = D_800C8584;
            break;
        case 6:
            hecho = D_800C8583;
            break;
        case 3:
            hecho = D_800C8582;
            break;
        default:
            hecho = 0;
            break;
        }
        if (hecho == 2) {
            o->estado = 0;
            o->_20 |= 0x80;
        }
        func_800486B8(o, 0x2D0000);
        if (e->activo == 0) {
            if (zona(e) == 1) {
                D_8007CBAC = o;
            }
        } else if (D_8007CBAC != NULL) {
            D_8007CBB0 = o;
        }
        break;
    }

    switch (o->estado) {
    case 0: case 1: case 2: case 3:
        return 0x80054728;
    case 5:
        if (e->activo != 0) {
            return e->activo;
        }
        r = zona(e);
        if (r != 1) {
            return r;
        }
        D_8007CAFC->estado = 4;
        o->estado = 0;
        D_8007CB30 = 1;
        return 1;
    case 4:
        if (e->listo != 0 && e->otro != NULL && zona(e) == 1) {
            b = e->otro;
            e->listo = 0;
            *(s32 *)((u8 *)b + 0x7C) = *(s32 *)((u8 *)b + 0x74);
        }
        if (e->listo != 0) {
            return e->listo;
        }
        if (e->otro->estado != 0) {
            return e->otro->estado;
        }
        e->listo = 1;
        return 1;
    case 8:
        return letrero(o, e);
    case 6:
        if (e->indice == 1) {
            switch (nivel_actual) {
            case 1: case 2: case 3:
                hecho = D_800C8566 == 1;
                break;
            case 4: case 5: case 6:
                hecho = D_800C8566 == 4;
                break;
            case 7: case 8: case 9:
                hecho = D_800C8566 == 3;
                break;
            case 10: case 11: case 12:
                hecho = D_800C8566 == 2;
                break;
            default:
                hecho = 0;
                break;
            }
            if (hecho) {
                *(u8 *)&o->_20 |= 0x80;
                return *(u8 *)&o->_20;
            }
        }
        return letrero(o, e);
    case 7:
        if (e->activo == 0) {
            return 0;
        }
        r = func_8003E060();
        if (r == e->pista && r != -1) {
            return r;
        }
        r = func_8003DDFC();
        o->estado = 0;
        return r;
    }
    return o->estado;
}
