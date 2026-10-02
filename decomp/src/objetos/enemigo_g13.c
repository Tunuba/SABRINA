#include "objeto.h"

/* Dos clases de enemigo que patrullan y atacan a Sabrina cuando esta cerca (func_80045278 y
 * func_80046428): solo cambian el disparo de cada nivel y que la segunda olvida que ya ataco al reiniciar
 * la animacion. */

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
extern void func_8003C678(Objeto *o, s32 *desde, s32 *fuera, s32 tipo, s32 a, s32 b, s32 c, s32 d);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);

/* El ataque, segun el nivel: un disparo (niveles 1 a 12, de tres clases) y su sonido. */
static void atacar(Objeto *o, ExtraEnemigo *e, s32 *fuera, s32 clase, s32 en_11) {
    s32 p[3];

    p[0] = e->boca[0];
    p[1] = e->boca[1];
    p[2] = e->boca[2];
    if (clase == 2) {
        switch (nivel_actual) {
        case 1: case 2: case 3:
            func_8003C1E8(o, p, fuera, 0x1E, 0x32, 5, 0x200, -0x8C0);
            TocarSonido(0x38, 0, 0x2A, 0x7F);
            break;
        case 4: case 5: case 6:
            func_8003C1E8(o, p, fuera, 0x20, 0x32, 5, 0x200, -0x8C0);
            TocarSonido(0x36, 0, 0x2A, 0x7F);
            break;
        case 7: case 8: case 9:
            func_80048DC0(o, p, fuera, -1, 0x1000);
            TocarSonido(0x34, 0, 0x2A, 0x7F);
            break;
        case 10: case 11: case 12:
            /* en el estado 7 usa func_8003C678 y en el 11 func_8003C1E8 */
            if (en_11) {
                func_8003C1E8(o, p, fuera, 0x27, 0x32, 5, 0x200, -0x8C0);
            } else {
                func_8003C678(o, p, fuera, 0x27, 0x32, 5, 0x200, -0x8C0);
            }
            TocarSonido(0x37, 0, 0x2A, 0x7F);
            break;
        case 13: case 14:
            TocarSonido(0x2C, 0, 0x2A, 0x7F);
            break;
        }
        return;
    }
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
static s32 animar_ataque(Objeto *o, ExtraEnemigo *e, EstadoAnim *a, u16 *t, s32 *fuera, s32 clase, s32 en_11) {
    if (poner(a, t[7])) {
        if (clase == 2) {
            e->ataco = 0;
        }
        return 0;
    }
    if (D_8007CBA8 != 0) {
        return 0;
    }
    a->_4E = 0x800;
    if ((a->_50 == e->cuadro2 || a->_50 == e->cuadro1) && e->ataco == 0) {
        e->ataco = 1;
        atacar(o, e, fuera, clase, en_11);
    }
    return func_8002EFD0(o) != 0;
}

static void paso_enemigo(Objeto *o, s32 clase) {
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
        if (animar_ataque(o, e, a, t, fuera, clase, 0)) {
            a->animacion = t[0];
            a->_50 = 0;
            o->estado = e->despues;
            if (clase == 2) {
                e->ataco = 0;
            }
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
            if (!animar_ataque(o, e, a, t, fuera2, clase, 1)) {
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

void func_80045278(Objeto *o) {
    paso_enemigo(o, 1);
}

void func_80046428(Objeto *o) {
    paso_enemigo(o, 2);
}

/* Un punto de ruta (0x18 bytes, en D_800D588C). */
typedef struct {
    s32 x, y, z;                     /* 0x00 */
    u8 _0C[2];
    s16 siguiente;                   /* 0x0E, 0: usar el de 0x10 */
    s16 anterior;                    /* 0x10 */
    u8 _12[6];
} PuntoRuta;

extern PuntoRuta D_800D588C[];
extern s32 func_8001C1D4(s32 *a, s32 *b);  /* producto de dos vectores */

/* Avanza al enemigo por su ruta (el punto de extra+0) hacia donde esta Sabrina: elige ir hacia el punto
 * actual o hacia el siguiente (o el anterior) segun de que lado quede Sabrina, avanza 8 veces ese
 * vector (en 24.8 / 256) y, si se paso de Sabrina, vuelve atras. */
void func_800489C4(Objeto *o) {
    PuntoRuta *p, *q;
    s32 a[3], b[3], c[3];

    func_800487B0(o, p_sabrina, 0x96);
    c[0] = o->x >> 8;
    c[1] = o->y >> 8;
    c[2] = o->z >> 8;
    p = *(PuntoRuta **)&o->extra;
    a[0] = p->x >> 8;
    a[1] = p->y >> 8;
    a[2] = p->z >> 8;
    q = &D_800D588C[p->siguiente != 0 ? p->siguiente : p->anterior];
    b[0] = q->x >> 8;
    b[1] = q->y >> 8;
    b[2] = q->z >> 8;
    a[0] -= c[0];
    a[1] -= c[1];
    a[2] -= c[2];
    b[0] -= c[0];
    b[1] -= c[1];
    b[2] -= c[2];
    c[0] = (p_sabrina->x - o->x) >> 8;
    c[1] = (p_sabrina->y - o->y) >> 8;
    c[2] = (p_sabrina->z - o->z) >> 8;
    if (a[1] + (a[0] + a[2]) != 0) {
        if (func_8001C1D4(c, a) < 0) {
            a[0] = b[0];
            a[1] = b[1];
            a[2] = b[2];
        }
    } else if (func_8001C1D4(c, b) > 0) {
        a[0] = b[0];
        a[1] = b[1];
        a[2] = b[2];
    }
    a[0] <<= 3;
    a[1] <<= 3;
    a[2] <<= 3;
    o->x += a[0];
    o->y += a[1];
    o->z += a[2];
    b[0] = (p_sabrina->x - o->x) >> 8;
    b[1] = (p_sabrina->y - o->y) >> 8;
    b[2] = (p_sabrina->z - o->z) >> 8;
    if (func_8001C1D4(a, b) < 0) {
        o->x -= a[0];
        o->y -= a[1];
        o->z -= a[2];
    }
}

extern Objeto *func_800252A0(s32 clase, Objeto *padre, s32 x, s32 y, s32 z, s32 vx, s32 vy, s32 vz, s32 rx,
                             s32 ry, s32 rz, s32 a, s32 b);
extern void func_800249CC(Objeto *o, s32 n);
extern void func_80048CF4(Objeto *o, s32 *hacia, s32 rapidez, s32 *vel);  /* velocidad hacia un punto */
extern void func_8001C45C(s32 *v);
extern void func_8003B38C(s32 *c, s32 *desde, s32 *hasta);
extern s32 func_8003AE84(void);
extern s32 D_800C6594[3], D_800C65A0[3];
extern void func_8003BFEC(Objeto *o);
extern void func_80024DF4(Objeto *o);
extern void func_8003BFC4(Objeto *o, Objeto *a);
extern void func_80024F74(void);
extern void func_80024F84(void);
extern void thunk_FUN_8001e588(Objeto *o);
extern void thunk_FUN_8004866c(Objeto *o);

/* Los primeros campos de un objeto: sus funciones. */
typedef struct {
    void (*actualizar)(Objeto *o);
    void (*f04)(Objeto *o);
    void (*aviso)(Objeto *o, Objeto *a);
    void (*f0C)(void);
    void (*f10)(void);
    void (*f14)(Objeto *o);
    void (*f18)(Objeto *o);
} FuncionesObjeto;

/* Crea un disparo (objeto 12) en desde, apuntado al pecho de Sabrina a 0x4000 de rapidez, con su modelo
 * (tipo) y sus datos (a, b, c, d en la parte extra). Si nace dentro de una pared se marca para borrar. */
void func_8003C1E8(Objeto *o, s32 *desde, s32 *fuera, s32 tipo, s32 a, s32 b, s32 c, s32 d) {
    Objeto *t;
    FuncionesObjeto *f;
    u8 *e;
    s32 v[3], p[3];
    s16 sa = a, sb = b, sc = c, sd = d;

    t = func_800252A0(12, o, desde[0], desde[1], desde[2], 0, 0, 0, 0, 0, 0, 1, 1);
    if (t == NULL) {
        return;
    }
    e = (u8 *)&t->extra;
    *(s16 *)(e + 0x24) = sb;
    *(s16 *)(e + 0x20) = sc;
    e[0x12] = tipo;
    *(s16 *)(e + 0x22) = sa;
    *(s16 *)(e + 0x26) = sd;
    func_800249CC(t, -1);
    f = (FuncionesObjeto *)t;
    f->actualizar = func_8003BFEC;
    f->f04 = func_80024DF4;
    f->aviso = func_8003BFC4;
    f->f0C = func_80024F74;
    f->f10 = func_80024F84;
    f->f14 = thunk_FUN_8001e588;
    f->f18 = thunk_FUN_8004866c;
    t->forma.banderas = 0x801;
    t->forma._20 = 1;
    t->dano = 1;
    p[0] = p_sabrina->x;
    p[1] = p_sabrina->y - 0xCCD - 0x7FFF;
    p[2] = p_sabrina->z;
    func_80048CF4(t, p, 0x4000, v);
    t->empuje_x = v[0];
    t->vel_y = v[1];
    t->empuje_z = v[2];
    func_8001C45C(v);
    p[0] = (((v[0] >> 4) * 0xCC) >> 8) << 8;
    p[1] = (((v[1] >> 4) * 0xCC) >> 8) << 8;
    p[2] = (((v[2] >> 4) * 0xCC) >> 8) << 8;
    D_800C6594[0] = t->x;
    D_800C6594[1] = t->y;
    D_800C6594[2] = t->z;
    D_800C6594[0] -= p[0];
    D_800C6594[1] -= p[1];
    D_800C6594[2] -= p[2];
    D_800C65A0[0] = t->x + t->empuje_x;
    D_800C65A0[1] = t->y + t->vel_y;
    D_800C65A0[2] = t->z + t->empuje_z;
    func_8003B38C(D_800C6594, D_800C6594, D_800C65A0);
    if (func_8003AE84() != 0) {
        *((u8 *)t + 0x20) |= 0x80;
    }
}

extern s32 func_8001C0D0(s32 x, s32 y, s32 z);  /* largo de un vector */
extern s32 func_80021D44(s16 *ang, s32 meta, s32 paso);  /* acerca un angulo; devuelve lo que falta */
extern s32 func_8002218C(Objeto *o, s32 x, s32 z);      /* angulo hacia un punto */
extern PuntoRuta *func_80060558(PuntoRuta *p);  /* el punto siguiente */
extern PuntoRuta *func_80060590(PuntoRuta *p);  /* el anterior */
extern void func_80022298(Objeto *o, s32 ang, s32 paso);  /* avanza en el plano */

/* Sigue la ruta: si el objeto llego a menos de 0x8000 del punto *pp pasa al siguiente (o al anterior si
 * el byte 5 de mov es negativo) y devuelve 8 si no hay mas. Si no, pone la animacion anim (acelerandola
 * de a 0x80 hasta 0x1000), gira hacia el punto y, si ya mira mas o menos hacia el, avanza (mas rapido
 * cuanto mejor mira; sube o baja con el punto). */
s32 func_800607AC(Objeto *o, s32 *mov, PuntoRuta **pp, s32 a3, u16 anim) {
    PuntoRuta *p = *pp;
    s32 rapidez = mov[0];
    EstadoAnim *a = o->anim;
    s32 v[3];
    s16 dif;

    v[0] = p->x - o->x;
    v[1] = p->y - o->y;
    v[2] = p->z - o->z;
    if (func_8001C0D0(v[0], v[1], v[2]) < 0x8000) {
        if (((s8 *)mov)[5] >= 0) {
            *pp = func_80060558(*pp);
        } else {
            *pp = func_80060590(*pp);
        }
        return *pp == NULL ? 8 : 0;
    }
    if (a != NULL) {
        if (a->animacion == anim) {
            if (a->_4E < 0x1000) {
                a->_4E = a->_4E + 0x80;
                rapidez = (rapidez * a->_4E) >> 12;
            }
        } else {
            a->animacion = anim;
            a->_50 = 0;
            a->_4E = 0;
        }
    }
    dif = func_80021D44(&o->rot[1], (s16)func_8002218C(o, p->x, p->z), 0x96);
    if (dif < 0x400) {
        func_8001C45C(v);
        rapidez = (rapidez * (s16)(0x400 - dif)) >> 10;
        func_80022298(o, o->rot[1], rapidez);
        o->y += (((v[1] >> 8) * (rapidez >> 4)) >> 8) << 8;
    }
    return 0;
}

/* El disparo de la tercera clase de enemigo, segun el nivel. */
static void atacar3(Objeto *o, ExtraEnemigo *e, s32 *fuera) {
    s32 p[3];

    p[0] = e->boca[0];
    p[1] = e->boca[1];
    p[2] = e->boca[2];
    switch (nivel_actual) {
    case 1: case 2: case 3:
        func_8003C1E8(o, p, fuera, 0x1F, 0x32, 5, 0x200, -0x8C0);
        TocarSonido(0x37, 0, 0x2A, 0x7F);
        break;
    case 4: case 5: case 6:
        func_80048DC0(o, p, fuera, 0x2E, 0x1000);
        TocarSonido(0x33, 0, 0x2A, 0x7F);
        break;
    case 7: case 8: case 9:
        func_8003C1E8(o, p, fuera, 0x23, 0x32, 5, 0x200, -0x8C0);
        TocarSonido(0x2C, 0, 0x2A, 0x7F);
        break;
    case 10: case 11: case 12:
        func_8003C1E8(o, p, fuera, 0x25, 0x32, 5, 0x200, -0x8C0);
        TocarSonido(0x33, 0, 0x2A, 0x7F);
        break;
    case 13: case 14:
        TocarSonido(0x2C, 0, 0x2A, 0x7F);
        break;
    }
}

/* Dispara en uno de los dos cuadros de la animacion de ataque (una vez); 1 si la animacion termino. */
static s32 disparo3(Objeto *o, ExtraEnemigo *e, EstadoAnim *a, s32 *fuera) {
    if (D_8007CBA8 != 0) {
        return 0;
    }
    a->_4E = 0x800;
    if ((a->_50 == e->cuadro2 || a->_50 == e->cuadro1) && e->ataco == 0) {
        e->ataco = 1;
        atacar3(o, e, fuera);
    }
    return func_8002EFD0(o) != 0;
}

/* La tercera clase de enemigo: como las otras dos, con su disparo. */
void func_8002E51C(Objeto *o) {
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
        if (poner(a, t[7])) {
            break;
        }
        if (disparo3(o, e, a, fuera)) {
            a->animacion = t[0];
            a->_50 = 0;
            o->estado = e->despues;
            e->ataco = 0;
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
            if (poner(a, t[7])) {
                e->ataco = 0;
                break;
            }
            if (!disparo3(o, e, a, fuera2)) {
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

extern s32 D_800C6598, D_800C659C, D_800C65A4, D_800C65A8;
extern void func_8001E588(Objeto *o);

/* Crea una bola (objeto 5) en desde, de escala dada y modelo tipo, lanzada al pecho de Sabrina a 0x4000;
 * si nace dentro de una pared se marca para borrar. */
void func_80048DC0(Objeto *o, s32 *desde, s32 *fuera, s32 tipo, s32 escala) {
    Objeto *t;
    s32 v[3];

    t = func_800252A0(5, o, desde[0], desde[1], desde[2], 0, 0, 0, 0, 0, 0, 1, 1);
    t->escala[0] = escala;
    t->escala[1] = escala;
    t->escala[2] = escala;
    func_800249CC(t, tipo);
    func_8001E588(t);
    fuera[0] = p_sabrina->x;
    fuera[1] = p_sabrina->y - 0xCCD - 0x7FFF;
    fuera[2] = p_sabrina->z;
    func_80048CF4(t, fuera, 0x4000, v);
    t->empuje_x = v[0];
    t->vel_y = v[1];
    t->empuje_z = v[2];
    func_8001C45C(v);
    D_800C6594[0] = t->x;
    D_800C6598 = t->y;
    D_800C659C = t->z;
    D_800C6594[0] -= ((((v[0] >> 4) * 0xCC) >> 8) << 8);
    D_800C6598 -= ((((v[1] >> 4) * 0xCC) >> 8) << 8);
    D_800C659C -= ((((v[2] >> 4) * 0x33 * 4) >> 8) << 8);
    D_800C65A0[0] = t->x + t->empuje_x;
    D_800C65A4 = t->y + t->vel_y;
    D_800C65A8 = t->z + t->empuje_z;
    func_8003B38C(D_800C6594, D_800C6594, D_800C65A0);
    if (func_8003AE84() != 0) {
        *(u8 *)&t->_20 |= 0x80;
    }
}

extern void func_80048900(Objeto *o, s32 a);

/* Un objeto que va y viene por su ruta: si Sabrina anda cerca de su centro lo mantiene vivo; al terminar la
 * ruta (8) vuelve a su punto de partida (dando la vuelta si va y viene, o volviendo a su lugar). */
void func_80057800(Objeto *o) {
    u16 *t = o->animaciones;
    u8 *e = (u8 *)&o->extra;
    s32 dx, dz, a, d;

    func_80048900(o, 0x280000);
    dx = p_sabrina->x - *(s32 *)(e + 0x28);
    dz = p_sabrina->z - *(s32 *)(e + 0x30);
    a = dx >> 8;
    d = ((a * a) >> 8) << 8;
    a = dz >> 8;
    d += ((a * a) >> 8) << 8;
    if (d < *(s32 *)(e + 0x34)) {
        *(s16 *)((u8 *)o->datos + 0x1A) = 2;
    }
    if (func_800607AC(o, (s32 *)(e + 0x1C), (PuntoRuta **)e, t[0], t[0]) != 8) {
        return;
    }
    if ((s8)e[4] != 0) {
        e[0x21] = -(s8)e[0x21];
        *(s32 *)e = *(s32 *)(e + 0xC);
        return;
    }
    *(s32 *)e = *(s32 *)(e + 0xC);
    o->x = *(s32 *)(e + 0x10);
    o->y = *(s32 *)(e + 0x14);
    o->z = *(s32 *)(e + 0x18);
}
