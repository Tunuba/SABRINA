#include "objeto.h"

/* El paso de Sabrina (su funcion de cada cuadro): estados generales, musica de algunos momentos, el
 * parpadeo al recibir dano y la animacion del companero que la sigue (D_8007CB8C). */

/* Campos crudos (los que objeto.h no nombra). */
#define FUNC_04(o) (*(void (**)(Objeto *))((u8 *)(o) + 4))   /* otra funcion de cada paso */
#define CAMPO_U8(p, d) (*(u8 *)((u8 *)(p) + (d)))
#define CAMPO_S16(p, d) (*(s16 *)((u8 *)(p) + (d)))

/* La parte extra de Sabrina que se usa aqui. */
typedef struct {
    Objeto *mirando;                 /* 0x00, a quien mira en el estado 1 */
    u8 _04[4];
    s32 botones;                     /* 0x08 */
    u8 _0C[8];
    s16 parpadeo;                    /* 0x14, pasos que quedan de parpadeo rojo */
    u8 _16[9];
    s8 inclinacion;                  /* 0x1F */
    u8 _20[3];
    s8 espera;                       /* 0x23 */
} ExtraSabrina;

extern s8 D_800C855E;                /* cuantas cosas se juntaron en el nivel 13 */
extern s32 D_800C98B4, D_800C98B8;
extern s16 partida;                  /* vidas */
extern u16 D_8007C872;
extern u16 D_8007C8C6;               /* volumen de la musica */
extern s32 jugando;
extern s8 nivel_actual;
extern s8 D_8007CA01;
extern s16 D_8007CA20;
extern s32 D_8007CA50;
extern s8 vida_barra;
extern s16 D_8007CB70;               /* la animacion que debe tener el companero */
extern s32 D_8007CB78;               /* cuenta para revisar si sigue la musica */
extern s32 D_8007CB80;
extern s32 D_8007CB84;
extern s8 D_8007CB88;
extern Objeto *D_8007CB8C;           /* el companero */
extern s32 D_8007CBA4;
extern s16 D_8007CBF0;
extern s16 D_8007CC16;
extern s8 D_8007CC18;

extern void DanoPorEnemigo(Objeto *o, Objeto *a);
extern void func_80024DF4(Objeto *o);
extern void func_80024DFC(Objeto *o);
extern void func_80024F6C(Objeto *o, Objeto *a);
extern void func_800318F4(Objeto *o);
extern void func_800313E4(void);
extern void func_8003DDA0(s32 pista, s32 a);  /* empieza una pista de musica */
extern void func_8003DD44(s32 volumen);
extern s32 func_8003E060(void);      /* la pista que suena, -1 ninguna */
extern void func_8003DDFC(void);
extern void func_800325AC(Objeto *o, void *c, EstadoAnim *a);
extern void func_80032B98(Objeto *o, void *c);
extern s32 func_800221A8(Objeto *o, s32 x, s32 y, s32 z);
extern s32 func_80021C3C(Objeto *o);
extern void func_80021F70(s8 *v, s32 meta, s32 paso);
extern s32 func_80021D44(s16 *ang, s32 meta, s32 paso);
extern s32 func_8002218C(Objeto *o, s32 x, s32 z);
extern void func_80032F50(Objeto *o);
extern void func_80031698(Objeto *o);
extern s32 func_8002EFD0(Objeto *o);
extern s32 func_80021CE4(s32 n);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);

/* Escala de Sabrina hacia la normal (0x1666 de ancho, 0x1000 de alto), de a 0xFA. */
static void crecer(void) {
    if (p_sabrina->escala[0] < 0x1000) {
        p_sabrina->escala[0] += 0xFA;
        p_sabrina->escala[1] = p_sabrina->escala[0];
        p_sabrina->escala[2] = p_sabrina->escala[0];
        return;
    }
    p_sabrina->escala[0] = 0x1666;
    p_sabrina->escala[1] = 0x1000;
    p_sabrina->escala[2] = 0x1666;
    D_8007CB8C->escala[0] = p_sabrina->escala[0];
    D_8007CB8C->escala[1] = p_sabrina->escala[1];
    D_8007CB8C->escala[2] = p_sabrina->escala[2];
}

/* Achica el objeto hacia 0x64 (de a un octavo y 5 mas) girando; devuelve 1 si ya llego. */
static s32 achicar(Objeto *o, s32 giro) {
    s32 e = o->escala[0];

    if (e < 0x64) {
        return 1;
    }
    o->escala[0] = e + (((0x64 - e) >> 3) - 5);
    o->escala[1] = o->escala[0];
    o->escala[2] = o->escala[0];
    o->rot[1] += giro;
    return 0;
}

void func_80030208(Objeto *o) {
    EstadoAnim *a = o->anim;
    EstadoAnim *ca = D_8007CB8C->anim;
    u16 *ct = D_8007CB8C->animaciones;
    u16 *t = o->animaciones;
    ExtraSabrina *e = (ExtraSabrina *)&o->extra;
    Objeto *m;
    s16 v;
    s32 r;

    if (D_8007CB80 == 0) {
        func_800318F4(o);
    }
    ((s16 *)o->datos)[13] = 2;
    ((s16 *)D_8007CB8C->datos)[13] = 2;
    vida_barra = p_sabrina->vida;
    if (partida <= 0 && nivel_actual != 14) {
        D_8007CA20 = 0xDD;
        if (o->estado != 8) {
            o->estado = 8;
            D_8007CB84 = 300;
            D_8007CB80 = 1;
            func_800313E4();
            FUNC_04(p_sabrina) = func_80024DF4;
            p_sabrina->aviso = func_80024F6C;
        }
    }
    if (D_800C98B4 == 1) {
        D_800C98B4 = 2;
        func_8003DDA0(0x4F, 0);
        func_8003DD44((D_8007C8C6 * 15) & 0xFF);
        D_8007CB88 = 1;
        crecer();
        return;
    }
    if (D_800C98B4 == 2) {
        r = func_8003E060();
        if (r != 0x4F || r == -1) {
            func_8003DDFC();
            D_800C98B4 = 0;
            D_8007CB88 = 0;
        }
        crecer();
        return;
    }
    if (nivel_actual == 13 && D_800C98B8 != 0) {
        D_800C98B8 = 0;
        D_8007CB78 = 10;
        if (D_800C855E >= 12) {
            func_8003DDA0(0x51, 0);
            func_8003DD44((D_8007C8C6 * 15) & 0xFF);
            o->estado = 6;
            D_8007CB78 = 0;
            return;
        }
        func_8003DDA0(0x50, 0);
        func_8003DD44((D_8007C8C6 * 15) & 0xFF);
    }
    if (D_8007CB78 != 0) {
        D_8007CB78--;
        if (D_8007CB78 == 0) {
            D_8007CB78 = 30;
            if (func_8003E060() == -1) {
                func_8003DDFC();
                D_8007CB78 = 0;
            }
        }
    }
    switch (o->estado) {
    case 8:
        D_8007CB84--;
        if (D_8007CB84 < 0) {
            nivel_actual = 0;
            D_8007CC16 = 0;
            D_8007CC18 = 1;
            jugando = 0;
        }
        break;
    case 0:
        e->botones = D_8007CA50;
        func_800325AC(o, e, a);
        func_80032B98(o, e);
        break;
    case 1:
        e->botones = 0;
        m = e->mirando;
        if (m != NULL) {
            v = (o->rot[0] + func_800221A8(o, m->x, m->y + 0x16666 + (s16)func_80021C3C(m), m->z)) >> 4;
            if (v >= 0x10) {
                v = 0xF;
            }
            if (v < -0xF) {
                v = -0xF;
            }
            func_80021F70(&e->inclinacion, (s8)v, 1);
            func_80021D44(&o->rot[1], func_8002218C(o, m->x, m->z), 0x30);
        } else {
            func_80032F50(o);
        }
        if (o->escala[1] >= 0xFFB) {
            o->escala[1] = 0x1000;
            o->escala[0] = 0x1666;
            o->escala[2] = 0x1666;
        } else {
            o->escala[0] += 0xB4;
            o->escala[1] += 0xB4;
            o->escala[2] += 0xB4;
        }
        break;
    case 4:
        D_8007CB80 = 1;
        FUNC_04(o) = func_80024DF4;
        o->aviso = func_80024F6C;
        if (o->escala[1] >= 0xFFB) {
            o->escala[0] = 0x1000;
            o->escala[1] = 0x1000;
            o->escala[2] = 0x1000;
            D_8007CB80 = 0;
            FUNC_04(o) = func_80024DFC;
            o->aviso = DanoPorEnemigo;
            o->escala[0] = 0x1666;
            o->escala[2] = 0x1666;
            o->estado = 0;
        } else {
            o->escala[0] += 0xB4;
            o->escala[1] += 0xB4;
            o->escala[2] += 0xB4;
        }
        break;
    case 2:
        if (D_8007C872 == 0) {
            D_8007CB80 = 1;
            FUNC_04(o) = func_80024DF4;
            o->aviso = func_80024F6C;
            if (achicar(o, 0x7D)) {
                D_8007CB78 = 0;
                partida--;
                func_80031698(o);
                D_8007CBF0 = D_8007CBA4 != 0 ? 0 : 1;
            }
        }
        break;
    case 7:
        r = func_8003E060();
        if (r != 0x52 || r == -1) {
            D_8007CB80 = 1;
            FUNC_04(o) = func_80024DF4;
            o->aviso = func_80024F6C;
            if (achicar(o, 0xE1)) {
                D_8007CC18 = 1;
                D_8007CA01 = nivel_actual;
                D_8007CC16 = 14;
                nivel_actual = 14;
                jugando = 0;
            }
        }
        if (o->escala[0] >= 0x33) {
            o->escala[0] -= 0x32;
            o->escala[1] = o->escala[0];
            o->escala[2] = o->escala[0];
            o->rot[1] += 0x20D;
        }
        break;
    case 6:
        if (nivel_actual == 13 && D_800C855E >= 12) {
            if (o->escala[0] < 0x1001) {
                o->escala[0] += 0xFA;
                o->escala[1] += 0xFA;
                o->escala[2] += 0xFA;
            }
            r = func_8003E060();
            if (r != 0x51 || r == -1) {
                func_8003DDA0(0x52, 0);
                func_8003DD44((D_8007C8C6 * 15) & 0xFF);
                o->estado = 7;
                o->escala[0] = 0x1000;
                o->escala[1] = 0x1000;
                o->escala[2] = 0x1000;
            }
        }
        if (func_8002EFD0(o) != 0) {
            a->_50 = 0;
            a->_4E = 0x800;
            switch (func_80021CE4(4)) {
            case 3:
                a->animacion = t[24];
                D_8007CB70 = 24;
                break;
            case 2:
                a->animacion = t[23];
                D_8007CB70 = 23;
                break;
            case 0:
                a->animacion = t[21];
                D_8007CB70 = 21;
                break;
            default:
                a->animacion = t[22];
                D_8007CB70 = 22;
                break;
            }
        }
        break;
    }
    if (e->espera != 0) {
        e->espera--;
    }
    if (e->parpadeo != 0) {
        e->parpadeo--;
        CAMPO_U8(o->modelo, 0x65) = 0xFF;
        CAMPO_U8(o->modelo, 0x66) = 0x40;
        CAMPO_U8(o->modelo, 0x67) = 0x40;
        CAMPO_S16(o->modelo, 0x60) = e->parpadeo << 7;
    }
    /* pasos del companero */
    if (ca->animacion == ct[2]) {
        if (ca->_50 == 5 || ca->_50 == 11) {
            TocarSonido(0, 0, 0x2B, 0x7F);
        }
    } else if (ca->animacion == ct[1] && (ca->_50 == 7 || ca->_50 == 16)) {
        TocarSonido(0, 0, 0x2B, 0x7F);
    }
    if (ca->animacion != ct[14]) {
        ca->_50 = a->_50;
        ca->_4E = a->_4E;
        ca->animacion = (u32)(s32)D_8007CB70 < 25 ? ct[D_8007CB70] : ct[0];
    } else {
        ca->_4E = 0x1000;
        if (func_8002EFD0(D_8007CB8C) != 0) {
            ca->animacion = ct[0];
            ca->_50 = 0;
        }
    }
}
