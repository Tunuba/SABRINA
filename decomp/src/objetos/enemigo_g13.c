#include "objeto.h"

/* Un enemigo que patrulla y ataca a Sabrina cuando esta cerca (la clase de func_80045278). */

/* Su parte extra. */
typedef struct {
    u8 _00[8];
    s32 alcance;                     /* 0x08, 24.8: desde donde ataca en el estado 11 */
    s32 boca[3];                     /* 0x0C, de donde sale el ataque */
    u8 _18[0xC];
    s8 modo;                         /* 0x24, bit 2: al terminar el estado 8 pasa al 11 */
    u8 _25[2];
    s8 cuadro1, cuadro2;             /* 0x27, cuadros de la animacion en que ataca */
    s8 despues;                      /* 0x29, estado al terminar de atacar */
    s16 patrulla;                    /* 0x2A */
    s16 _2C;                         /* 0x2C */
    u8 _2E[0x16];
    s16 ataco;                       /* 0x44, 1 mientras dura la animacion de ataque */
} ExtraEnemigo;

extern s8 nivel_actual;
extern s32 D_8007CBA8;               /* distinto de 0: los enemigos no atacan */
extern s32 func_800487B0(Objeto *o, Objeto *a, s32 paso);  /* gira hacia a; devuelve la distancia */
extern void func_80048908(Objeto *o, s16 *a, s16 *b, s32 modo);
extern void func_800492B4(Objeto *o, ExtraEnemigo *e, u16 *anims);
extern void func_80048804(Objeto *o, s32 modo, EstadoAnim *a, s32 anim);
extern void func_80048228(Objeto *o, s16 *p);
extern void func_800489C4(Objeto *o);
extern void func_80049A28(Objeto *o, ExtraEnemigo *e, u16 *anims);
extern void func_80049BD0(Objeto *o, ExtraEnemigo *e, u16 *anims);
extern s32 func_8002EFD0(Objeto *o);  /* si termino la animacion */
extern u32 func_8001C180(s32 *v);
extern void func_80048DC0(Objeto *o, s32 *desde, s32 *fuera, s32 tipo, s32 e);
extern void func_8003C1E8(Objeto *o, s32 *desde, s32 *fuera, s32 tipo, s32 a, s32 b, s32 c, s32 d);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);

/* El ataque, segun el nivel: un disparo (niveles 1 a 12, de tres clases) y su sonido. */
static void atacar(Objeto *o, ExtraEnemigo *e, s32 *fuera) {
    s32 p[3];

    p[0] = e->boca[0];
    p[1] = e->boca[1];
    p[2] = e->boca[2];
    switch (nivel_actual) {
    case 1: case 2: case 3:
        func_80048DC0(o, p, fuera, 0x2F, 0x1000);
        TocarSonido(0x33, 0, 0x2A, 0x7F);
        break;
    case 4: case 5: case 6:
        func_8003C1E8(o, p, fuera, 0x21, 0x32, 5, 0x200, -0x8C0);
        TocarSonido(0x32, 0, 0x2A, 0x7F);
        break;
    case 7: case 8: case 9:
        func_8003C1E8(o, p, fuera, 0x22, 0x32, 5, 0x200, -0x8C0);
        TocarSonido(0x35, 0, 0x2A, 0x7F);
        break;
    case 10: case 11: case 12:
        func_8003C1E8(o, p, fuera, 0x26, 0x32, 5, 0x200, -0x8C0);
        TocarSonido(0x36, 0, 0x2A, 0x7F);
        break;
    case 13: case 14:
        TocarSonido(0x2C, 0, 0x2A, 0x7F);
        break;
    }
}

/* Pone la animacion n de la tabla si no estaba; devuelve 1 si la puso. */
static s32 poner(EstadoAnim *a, u16 n) {
    if (a->animacion == n) {
        return 0;
    }
    a->animacion = n;
    a->_50 = 0;
    a->_4E = 0x800;
    return 1;
}

/* La animacion de ataque: en el primer paso la pone; despues, si los enemigos pueden atacar, dispara en
 * uno de sus dos cuadros (una vez). Devuelve 1 si la animacion termino. */
static s32 animar_ataque(Objeto *o, ExtraEnemigo *e, EstadoAnim *a, u16 *t, s32 *fuera) {
    if (poner(a, t[7])) {
        return 0;
    }
    if (D_8007CBA8 != 0) {
        return 0;
    }
    a->_4E = 0x800;
    if ((a->_50 == e->cuadro2 || a->_50 == e->cuadro1) && e->ataco == 0) {
        e->ataco = 1;
        atacar(o, e, fuera);
    }
    return func_8002EFD0(o) != 0;
}

void func_80045278(Objeto *o) {
    EstadoAnim *a = o->anim;
    u16 *t = o->animaciones;
    ExtraEnemigo *e = (ExtraEnemigo *)&o->extra;
    s32 fuera[3], fuera2[3], v[3];

    switch ((u16)o->estado) {
    case 0:
        e->patrulla = 5;
        o->estado = 1;
        break;
    case 1:
        if (a->animacion != t[0]) {
            a->velocidad = 0;
            a->_4E = 0x800;
            a->animacion = t[0];
            a->_50 = 0;
        }
        func_80048908(o, &e->patrulla, &e->_2C, e->modo);
        break;
    case 2:
        func_800492B4(o, e, t);
        break;
    case 3:
    case 4:
        if (func_800487B0(o, p_sabrina, 100) >= 0x200) {
            break;
        }
        if (o->estado != 4 && a->animacion != t[4]) {
            a->animacion = t[4];
            a->_50 = 0;
            a->_4E = 0x800;
            o->estado = 4;
        }
        func_80048804(o, e->modo, a, (s8)t[0]);
        break;
    case 7:
        func_800487B0(o, p_sabrina, 100);
        if (animar_ataque(o, e, a, t, fuera)) {
            a->animacion = t[0];
            a->_50 = 0;
            o->estado = e->despues;
        }
        break;
    case 8:
        func_800487B0(o, p_sabrina, 100);
        if (func_8002EFD0(o) != 0) {
            o->estado = (e->modo & 4) ? 11 : 4;
        }
        break;
    case 10:
        func_80048228(o, &e->patrulla);
        break;
    case 11:
        func_800489C4(o);
        func_800487B0(o, p_sabrina, 100);
        v[0] = o->x - p_sabrina->x;
        v[1] = 0;
        v[2] = o->z - p_sabrina->z;
        if ((s32)func_8001C180(v) <= (e->alcance >> 8)) {
            if (!animar_ataque(o, e, a, t, fuera2)) {
                break;
            }
        } else if (func_8002EFD0(o) == 0) {
            break;
        }
        a->animacion = t[0];
        a->_50 = 0;
        e->ataco = 0;
        break;
    case 12:
        func_80049A28(o, e, t);
        break;
    case 6:
        func_80049BD0(o, e, t);
        break;
    default:
        o->estado = 0;
        break;
    }
}
