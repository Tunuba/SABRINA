#include "objeto.h"

/* El selector de hechizos: un objeto que, al acercarse Sabrina y apretar el boton 1, muestra los hechizos
 * que tiene (uno por objeto, creciendo delante de el) y deja cambiar con izquierda y derecha y elegir. */

typedef struct {
    s32 hechizo[7];                  /* 0x00, el numero de cada uno (21 a 25) */
    s32 sel;                         /* 0x1C, el que se ve */
    u8 _20[0x14];
    s32 cuantos;                     /* 0x34 */
    s32 espera;                      /* 0x38 */
    Objeto *muestra[1];              /* 0x3C, el objeto que muestra cada uno */
} ExtraSelector;

extern s16 D_8007CA20;               /* el renglon de texto que se muestra */
extern s32 D_8007CA30;               /* botones apretados en este paso */
extern s32 D_8007CA50;               /* botones recien apretados */
extern s32 D_8007CB7C;               /* 1 mientras se elige */
extern s32 D_8007CC78;               /* pasos que queda el letrero */

extern void func_80021D44(s16 *ang, s32 hacia, s32 paso);
extern s32 func_8002218C(Objeto *o, s32 x, s32 z);
extern s32 func_8002225C(Objeto *o, s32 x, s32 y, s32 z);
extern void func_8002205C(s32 *hacia, s32 ang_x, s32 ang_y);
extern s32 func_8002EFD0(Objeto *o);  /* si termino la animacion */
extern s32 func_8005B994(Objeto *o);  /* quita lo que se muestra */
extern void func_8005BA10(Objeto *o); /* muestra los hechizos */
extern void func_80030F18(s32 n);

/* Vuelve a mostrar los hechizos dejando el elegido y espera 10 pasos. */
static void mostrar(Objeto *o, ExtraSelector *e) {
    s32 sel = e->sel;

    func_8005B994(o);
    func_8005BA10(o);
    e->sel = sel;
    e->espera = 10;
    o->estado = 5;
}

/* Devuelve (v0) lo que deja el original: con el estado 0 la direccion a la que salta su tabla. */
s32 func_8005C358(Objeto *o) {
    u16 *t = o->animaciones;
    EstadoAnim *a = o->anim;
    ExtraSelector *e = (ExtraSelector *)&o->extra;
    Objeto *m;
    s32 v[3];

    *(s16 *)((u8 *)o->datos + 0x1A) = 2;
    D_8007CB7C = 0;
    if (p_sabrina != NULL) {
        func_80021D44(&o->rot[1], func_8002218C(o, p_sabrina->x, p_sabrina->z), 0xAA);
        if (D_8007CA30 & 1) {
            if (func_8002225C(o, p_sabrina->x, p_sabrina->y, p_sabrina->z) < 0x28000) {
                if (o->estado == 0) {
                    o->estado = 1;
                    func_8005BA10(o);
                    a->_4E = 0x800;
                    a->animacion = t[0];
                    a->_50 = 0;
                }
            } else if (o->estado != 0) {
                o->estado = 2;
                a->_4E = 0x800;
                a->animacion = t[1];
                a->_50 = 0;
            }
        }
        if (e->muestra[e->sel] != NULL) {
            func_8002205C(v, 0, o->rot[1]);
            v[0] = (((v[0] >> 4) * 0x66) >> 8) << 8;
            v[2] = (((v[2] >> 4) * 0x66) >> 8) << 8;
            e->muestra[e->sel]->x = o->x + v[0];
            e->muestra[e->sel]->z = o->z + v[2];
            e->muestra[e->sel]->rot[1] = o->rot[1];
            m = e->muestra[e->sel];
            if (m->escala[0] < 0x1130) {
                m->escala[0] += 0x12C;
                m = e->muestra[e->sel];
                m->escala[1] = m->escala[0];
                m = e->muestra[e->sel];
                m->escala[2] = m->escala[0];
            } else {
                m->escala[0] = 0x1130;
                e->muestra[e->sel]->escala[1] = 0x1130;
                e->muestra[e->sel]->escala[2] = 0x1130;
            }
        }
    }
    if (a->_4E != 0 && func_8002EFD0(o) != 0) {
        a->_4E = 0;
        a->velocidad = 0;
    }
    if (D_8007CC78 > 0) {
        D_8007CC78--;
        D_8007CA20 = 0x11A;
    } else if (D_8007CC78 == 0) {
        D_8007CC78--;
        D_8007CA20 = 0;
    }
    switch (o->estado) {
    case 0:
        return 0x8005C8C4;
    case 1:
        o->estado = 3;
        D_8007CB7C = 1;
        D_8007CC78 = 150;
        return 150;
    case 2:
        o->estado = 0;
        return func_8005B994(o);
    case 3:
        D_8007CB7C = 1;
        if (D_8007CA50 & 0xC) {
            if (D_8007CA50 & 8) {
                e->sel--;
                if (e->sel < 0) {
                    e->sel = e->cuantos - 1;
                    if (e->sel < 0) {
                        e->sel = 0;
                    }
                }
            }
            if (D_8007CA50 & 4) {
                e->sel++;
                if (e->sel >= e->cuantos) {
                    e->sel = 0;
                }
            }
            mostrar(o, e);
        }
        if (!(D_8007CA50 & 0x40)) {
            return 0;
        }
        e->espera = 100;
        switch (e->hechizo[e->sel]) {
        case 21:
            func_80030F18(2);
            break;
        case 22:
            func_80030F18(4);
            break;
        case 24:
            func_80030F18(8);
            break;
        case 23:
            func_80030F18(6);
            break;
        case 25:
            func_80030F18(10);
            break;
        }
        mostrar(o, e);
        return 5;
    case 4:
        o->estado = 3;
        return 3;
    case 5:
        D_8007CB7C = 1;
        e->espera--;
        if (e->espera < 0) {
            o->estado = 3;
            return 3;
        }
        return e->espera;
    }
    return o->estado;
}
