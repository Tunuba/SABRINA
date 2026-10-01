#include "objeto.h"

/* Acciones de Sabrina segun los botones (encogerse, saltar, agacharse...). */

/* Lo que lleva Sabrina de los controles (la parte extra de su objeto). */
typedef struct {
    u8 _00[4];
    s32 _04;                         /* 0x04 */
    s32 botones;                     /* 0x08, recien apretados */
    u8 _0C[0x0C];
    s16 suelo;                       /* 0x18, se miran los bits 2 y 8 */
    u8 _1A, _1B;                     /* 0x1A */
    u8 _1C;
    s8 accion;                       /* 0x1D */
    u8 _1E[3];
    s8 lado;                         /* 0x21 */
} Controles;

extern s8 nivel_actual;
extern s16 D_8007CB38;
extern s16 D_8007CB70;
extern Objeto *D_8007CB8C;           /* el objeto que va con Sabrina */
extern s32 D_8007CB9C;
extern s32 D_8007CBA0;
extern void func_80033B1C(Objeto *o, Controles *c, EstadoAnim *a);
extern void func_80030F18(s32 n);
extern s32 func_8002EFD0(Objeto *o);

/* Saltar: con 0x40 y una direccion (0xF000) salta de lado (8), sin direccion salta (7). */
static void saltar(Objeto *o, Controles *c, EstadoAnim *a, EstadoAnim *ca, u16 *t, u16 *ct, s32 b) {
    if (!(b & 0x40)) {
        return;
    }
    if (b & 0xF000) {
        if (a->_50 < 5 || a->_50 >= 0xD) {
            c->lado = 0;
            a->animacion = t[8];
            ca->animacion = ct[8];
        } else {
            c->lado = 1;
            a->animacion = t[9];
            ca->animacion = ct[9];
        }
        a->_50 = 0;
        a->_4E = 0x800;
        ca->_50 = 0;
        ca->_4E = 0x800;
        c->accion = 8;
        o->vel_y = -0x2AAA;
    } else {
        a->animacion = t[5];
        a->_50 = 0;
        ca->animacion = ct[5];
        ca->_50 = 0;
        a->_4E = 0x800;
        c->accion = 7;
    }
}

/* Aterrizar o caer: la animacion 6 a media velocidad y la accion 9. */
static void caer(Controles *c, EstadoAnim *a, EstadoAnim *ca, u16 *t, u16 *ct) {
    a->animacion = t[6];
    a->_50 = 0;
    a->_4E = 0x800;
    ca->animacion = ct[6];
    ca->_50 = 0;
    ca->_4E = 0x800;
    c->_1A = a->_50;
    c->_1B = a->_50;
    c->_04 = 0x13A0;
    c->accion = 9;
}

void func_800325AC(Objeto *o, Controles *c, EstadoAnim *a) {
    u16 *ct = D_8007CB8C->animaciones;
    EstadoAnim *ca = D_8007CB8C->anim;
    u16 *t = o->animaciones;
    s32 b = c->botones;
    s32 e;

    if (nivel_actual == 14) {
        func_80033B1C(o, c, a);
    }
    switch (c->accion) {
    case 17:
        /* encogerse */
        p_sabrina->escala[0] -= 100;
        if (p_sabrina->escala[0] < 3) {
            p_sabrina->escala[0] = 2;
        }
        p_sabrina->escala[1] = p_sabrina->escala[0];
        p_sabrina->escala[2] = p_sabrina->escala[0];
        D_8007CB8C->escala[0] = p_sabrina->escala[0];
        D_8007CB8C->escala[1] = p_sabrina->escala[1];
        D_8007CB8C->escala[2] = p_sabrina->escala[2];
        if (p_sabrina->escala[0] < 0xB || a->_50 >= 0x1E) {
            func_80030F18(D_8007CBA0);
            if (D_8007CBA0 == 0x18 || D_8007CBA0 == 0x1C || D_8007CBA0 == 0x1A) {
                D_8007CB9C = 1;
            } else {
                D_8007CB38 = 0;
            }
            c->accion = 0x13;
        }
        break;
    case 19:
        /* volver a crecer */
        p_sabrina->escala[0] += 0xFA;
        if (func_8002EFD0(o) != 0 || p_sabrina->escala[0] >= 0x1000) {
            p_sabrina->escala[0] = 0x1666;
            p_sabrina->escala[2] = 0x1666;
            p_sabrina->escala[1] = 0x1000;
            D_8007CB8C->escala[0] = p_sabrina->escala[0];
            D_8007CB8C->escala[1] = p_sabrina->escala[1];
            D_8007CB8C->escala[2] = p_sabrina->escala[2];
            c->accion = 0;
            a->_53 = t[0];
            a->_52 = a->_50;
            a->animacion = t[0];
            a->_50 = 0;
            a->velocidad = 0;
            a->_4E = 0x800;
            ca->_53 = ct[0];
            ca->_52 = ca->_50;
            ca->animacion = ct[0];
            ca->_50 = 0;
            ca->velocidad = 0;
            ca->_4E = 0x800;
            D_8007CB70 = 0;
            break;
        }
        e = p_sabrina->escala[0];
        p_sabrina->escala[1] = e;
        p_sabrina->escala[2] = p_sabrina->escala[0];
        D_8007CB8C->escala[0] = p_sabrina->escala[0];
        D_8007CB8C->escala[1] = p_sabrina->escala[1];
        D_8007CB8C->escala[2] = p_sabrina->escala[2];
        break;
    case 0:
        if (b & 0x10) {
            c->accion = 0xD;
        }
        /* sigue */
    case 1:
    case 2:
    case 3:
        saltar(o, c, a, ca, t, ct, b);
        if (c->suelo & 2) {
            caer(c, a, ca, t, ct);
        }
        break;
    case 4:
    case 5:
    case 6:
        saltar(o, c, a, ca, t, ct, b);
        if (c->suelo & 2) {
            if (a->_50 < 7) {
                c->lado = 0;
                a->animacion = t[10];
                ca->animacion = ct[10];
            } else {
                c->lado = 1;
                a->animacion = t[11];
                ca->animacion = ct[11];
            }
            a->_50 = 0;
            a->_4E = 0x1000;
            ca->_50 = 0;
            ca->_4E = 0x1000;
            c->_04 = 0x13A0;
            c->accion = 0xB;
        }
        break;
    case 8:
    case 11:
    case 12:
    case 14:
    case 15:
        if (c->suelo & 8) {
            caer(c, a, ca, t, ct);
        }
        break;
    }
}
