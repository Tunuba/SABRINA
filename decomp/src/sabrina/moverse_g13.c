#include "objeto.h"

/* Las acciones de Sabrina que dependen de los botones: quieta, caminar, correr, los saltos y su caida, y
 * apuntar (la 13). Al final aplica la fisica. */

/* La parte extra de Sabrina que se usa aqui. */
typedef struct {
    u8 _00[4];
    s32 velocidad;                   /* 0x04 */
    s32 botones;                     /* 0x08 */
    u8 _0C[2];
    s16 pasos_caminar;               /* 0x0E */
    s16 pasos_correr;                /* 0x10 */
    u8 _12[6];
    s16 contacto;                    /* 0x18, 0x10: en el piso */
    u8 cuadro_a;                     /* 0x1A */
    u8 cuadro_b;                     /* 0x1B */
    s8 lado;                         /* 0x1C */
    s8 accion;                       /* 0x1D */
    u8 _1E;
    s8 apunta_x;                     /* 0x1F */
    s8 apunta_y;                     /* 0x20 */
    s8 doble;                        /* 0x21 */
    u8 _22[4];
    s8 frenada;                      /* 0x26 */
} ExtraMoverse;

#define PISO(o) (*(s32 *)((u8 *)(o) + 0x50))   /* la altura del piso bajo el objeto */

extern s32 D_8007C8A4;               /* pasos quieta antes de una animacion de espera */
extern s16 D_8007CB70;               /* la animacion que debe tener el companero */
extern Objeto *D_8007CB8C;           /* el companero */

extern s32 func_8002EFD0(Objeto *o);  /* si termino la animacion */
extern s32 func_80021CE4(s32 n);     /* al azar, de 0 a n - 1 */
extern void func_80032F90(Objeto *o, s32 flechas);  /* moverse con las flechas */
extern void func_80032F50(Objeto *o);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern s32 FisicaObjeto(Objeto *o, s32 a);

/* Pone la animacion n desde el cuadro 0 a la velocidad dada. */
#define ANIMAR(a, n, vel) ((a)->animacion = (n), (a)->_50 = 0, (a)->_4E = (vel))

/* En el aire: el cuadro de la animacion sigue la velocidad vertical; al tocar el piso cae parada en la
 * animacion fin con la accion siguiente. */
static void en_el_aire(Objeto *o, ExtraMoverse *e, EstadoAnim *a, u32 b, u16 fin, s16 companero,
                       s8 siguiente) {
    s32 c;

    if ((b & 0xF000) && e->frenada == 0) {
        func_80032F90(o, b & 0xF000);
    }
    e->cuadro_a = 0xFF;
    e->cuadro_b = 0xFF;
    c = o->vel_y / 1638 + 7;
    if (c < 0) {
        c = 0;
    }
    if (c >= 15) {
        c = 14;
    }
    if (c == a->_50) {
        if (a->_50 == a->_52) {
            a->_4E = 0x1000;
        }
    } else {
        a->_50 = c;
        a->_4E = 0x800;
    }
    if (o->vel_y >= 0 && o->y >= PISO(o) && (e->contacto & 0x10)) {
        o->y = PISO(o);
        ANIMAR(a, fin, 0x800);
        D_8007CB70 = companero;
        e->accion = siguiente;
        e->cuadro_a = 0;
        e->cuadro_b = 0;
        TocarSonido(1, 0, 0x2A, 0x7F);
    }
}

/* Al terminar de caer vuelve a quieta. */
static void aterrizar(Objeto *o, ExtraMoverse *e, EstadoAnim *a, u16 *t, u16 caida) {
    if (a->_53 == caida) {
        if (func_8002EFD0(o)) {
            o->empuje_x = 0;
            o->vel_y = 0;
            o->empuje_z = 0;
            a->animacion = t[0];
            D_8007CB70 = 0;
            e->cuadro_a = 0xFF;
            e->cuadro_b = 0xFF;
            e->accion = 0;
        } else {
            a->_4E = 0x1000;
        }
    }
}

/* Despega: al terminar la animacion de impulso pasa a la de subir. */
static void despegar(Objeto *o, ExtraMoverse *e, EstadoAnim *a, u16 impulso, u16 subir, s16 companero,
                     s8 siguiente, s32 velocidad) {
    if (a->_53 == impulso) {
        if (func_8002EFD0(o)) {
            o->empuje_x = 0;
            o->vel_y = -0x2AAA;
            o->empuje_z = 0;
            a->animacion = subir;
            a->_4E = 0x800;
            D_8007CB70 = companero;
            e->cuadro_a = a->_50;
            e->cuadro_b = a->_50;
            e->accion = siguiente;
            e->velocidad = velocidad;
        } else {
            a->_4E = 0x1000;
        }
    }
}

/* De caminar o correr a quieta: espera a que la animacion de parar vuelva a la de quieta. */
static void parar(Objeto *o, ExtraMoverse *e, EstadoAnim *a, u16 *t, u16 parada, s32 f1, s32 f2,
                  s16 *pasos) {
    if (a->animacion == parada) {
        if (a->_52 == f1 || a->_52 == f2) {
            ANIMAR(a, t[0], 0x800);
            D_8007CB70 = 0;
            e->velocidad = 0;
        } else {
            func_80032F90(o, 0);
        }
    } else if (a->_53 == t[0]) {
        a->_4E = 0x1000;
        e->accion = 0;
        *pasos = 0;
        e->lado ^= 0xC;
    }
}

s32 func_800318F4(Objeto *o) {
    ExtraMoverse *e = (ExtraMoverse *)&o->extra;
    EstadoAnim *ca = D_8007CB8C->anim;
    EstadoAnim *a = o->anim;
    u16 *t = o->animaciones;
    u32 b = e->botones & 0xFFFF;
    s32 n;

    if (e->accion != 0) {
        D_8007C8A4 = 150;
    }
    if (D_8007C8A4 >= 0) {
        D_8007C8A4--;
    }
    switch (e->accion) {
    case 0:
        if (b & 0xF000) {
            a->animacion = t[1];
            a->_50 = e->lado;
            a->_4E = 0x1000;
            D_8007CB70 = 1;
            e->velocidad = 0;
            e->accion = 1;
        } else {
            if (a->animacion == t[3] && func_8002EFD0(o)) {
                ANIMAR(a, t[0], 0x1000);
                D_8007CB70 = 0;
            }
            if (D_8007C8A4 < 0 && func_8002EFD0(o)) {
                a->_50 = 0;
                a->_4E = 0x800;
                switch (func_80021CE4(4)) {
                case 0:
                    a->animacion = t[0x15];
                    D_8007CB70 = 0x15;
                    break;
                case 1:
                    a->animacion = t[0x16];
                    D_8007CB70 = 0x16;
                    break;
                case 2:
                    a->animacion = t[0x17];
                    D_8007CB70 = 0x17;
                    break;
                case 3:
                    a->animacion = t[0x18];
                    D_8007CB70 = 0x18;
                    break;
                default:
                    a->animacion = t[0x16];
                    D_8007CB70 = 0x16;
                    break;
                }
            }
        }
        break;
    case 1:
        a->_4E += 0x800;
        ca->_4E += 0x800;
        e->velocidad = (a->_4E * 0x5F9) >> 12;
        if (a->animacion == a->_53) {
            a->_4E = 0x1000;
            e->velocidad = 0x5F9;
            e->cuadro_a = 5;
            e->cuadro_b = 0x13;
            e->accion = 2;
        }
        func_80032F90(o, b & 0xF000);
        e->pasos_caminar++;
        break;
    case 2:
        if (b & 0xF000) {
            func_80032F90(o, b & 0xF000);
            e->pasos_caminar++;
            if (e->pasos_caminar >= 3) {
                ANIMAR(a, t[2], 0x800);
                D_8007CB70 = 2;
                e->cuadro_a = 3;
                e->cuadro_b = 9;
                e->accion = 4;
            }
        } else {
            e->accion = 3;
        }
        break;
    case 3:
        parar(o, e, a, t, t[1], 6, 0x12, &e->pasos_caminar);
        break;
    case 4:
        if (b & 0xF000) {
            e->velocidad = (a->_4E * 0xDA7 + 0x5F9) >> 12;
            if (a->animacion == a->_53) {
                a->_4E = 0x1000;
                e->velocidad = 0x13A0;
                e->cuadro_a = 3;
                e->cuadro_b = 9;
                e->accion = 5;
                e->pasos_caminar = 0;
            }
            func_80032F90(o, b & 0xF000);
        } else {
            e->accion = 6;
        }
        break;
    case 5:
        if (b & 0xF000) {
            a->_4E = 0x1000;
            func_80032F90(o, b & 0xF000);
            e->pasos_correr++;
        } else {
            e->accion = 6;
        }
        break;
    case 6:
        parar(o, e, a, t, t[2], 4, 0xC, &e->pasos_correr);
        break;
    case 13:
        if (b & 0x10) {
            if ((b & 0x4000) && e->apunta_x < 15) {
                e->apunta_x += 2;
            }
            if ((b & 0x1000) && e->apunta_x >= -14) {
                e->apunta_x -= 2;
            }
            if ((b & 0x8000) && e->apunta_y < 32) {
                e->apunta_y += 3;
            }
            if ((b & 0x2000) && e->apunta_y >= -31) {
                e->apunta_y -= 3;
            }
        } else {
            e->accion = 0;
        }
        break;
    case 14:
        despegar(o, e, a, t[0x12], t[0x13], 0x13, 0xF, 0x2147);
        break;
    case 15:
        en_el_aire(o, e, a, b, t[0x14], 0x14, 0x10);
        break;
    case 16:
        aterrizar(o, e, a, t, t[0x14]);
        break;
    case 7:
        despegar(o, e, a, t[5], t[6], 6, 9, 0x13A0);
        break;
    case 9:
        en_el_aire(o, e, a, b, t[7], 7, 0xA);
        break;
    case 10:
        aterrizar(o, e, a, t, t[7]);
        break;
    case 8:
        if (a->_53 == (s8)(e->doble == 0 ? t[8] : t[9])) {
            if (func_8002EFD0(o)) {
                if (e->doble == 0) {
                    a->animacion = t[10];
                    n = 10;
                } else {
                    a->animacion = t[11];
                    n = 11;
                }
                D_8007CB70 = n;
                e->cuadro_a = 0xFF;
                e->cuadro_b = 0xFF;
                e->accion = 0xB;
                e->velocidad = 0x13A0;
            } else {
                a->_4E = 0x1000;
            }
        }
        func_80032F90(o, b & 0xF000);
        e->pasos_correr++;
        break;
    case 11:
        if (b & 0xF000) {
            func_80032F90(o, b & 0xF000);
        }
        if (PISO(o) - 0x3333 < o->y && o->vel_y <= 0) {
            e->accion = 0xC;
            a->animacion = t[12];
            a->_4E = 0x1000;
            TocarSonido(1, 0, 0x2A, 0x7F);
            D_8007CB70 = 0xC;
        }
        break;
    case 12:
        o->vel_y = 0;
        if (a->_53 == t[12]) {
            if (func_8002EFD0(o)) {
                a->_50 = 0;
                a->animacion = t[2];
                a->_4E = 0x800;
                D_8007CB70 = 2;
                e->velocidad = 0x13A0;
                e->cuadro_a = 3;
                e->cuadro_b = 9;
                e->accion = 5;
            } else {
                a->_4E = 0x800;
            }
        }
        func_80032F90(o, b & 0xF000);
        e->pasos_correr++;
        break;
    default:
        o->empuje_x = 0;
        o->vel_y = 0;
        o->empuje_z = 0;
        break;
    }
    if (e->accion != 0xD && e->accion != 0) {
        func_80032F50(o);
    }
    e->contacto = 0;
    return FisicaObjeto(o, 1);
}
