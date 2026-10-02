#include "objeto.h"

/* Iniciar un objeto que anda por una ruta de puntos (o, sin ruta, apoyarlo en el suelo). */

/* Un punto de ruta (0x18 bytes, en D_800D588C). */
typedef struct {
    s32 x, y, z;                     /* 0x00 */
    u8 _0C[2];
    s16 siguiente;                   /* 0x0E */
    u8 _10[8];
} PuntoRutaI;

/* La parte extra que se usa. */
typedef struct {
    PuntoRutaI *punto;               /* 0x00, al iniciar viene el numero del punto */
    u8 _04[0x0A];
    s16 pasos;                       /* 0x0E */
    s32 _10;                         /* 0x10 */
    s8 _14, _15;                     /* 0x14 */
    u8 _16[2];
    s32 paso[3];                     /* 0x18, lo que avanza en cada paso (1/16 del tramo) */
    s32 rumbo[3];                    /* 0x24, hacia donde va, de largo 1 */
} ExtraRuta;

extern PuntoRutaI D_800D588C[];
extern s32 D_8007CBA8;

extern s32 func_8002ECFC(Objeto *o);  /* 1 si tiene animacion */
extern s8 func_80030068(s32 a);
extern s32 func_800223E8(s32 *pos); /* la altura del suelo debajo de pos */
extern void func_8002205C(s32 *hacia, s32 ang_x, s32 ang_y);
extern void func_8001C45C(s32 *v);  /* dejar el vector de largo 1 */
extern s32 func_8001E588(Objeto *o);  /* rehace la matriz del modelo */

/* Con ruta: lo pone en su primer punto, con escala 5, y apunta al siguiente (16 pasos). Sin ruta: lo
 * apoya en el suelo y mira hacia su giro. Devuelve (v0) lo que devuelve func_8001E588. */
s32 func_8003477C(Objeto *o) {
    ExtraRuta *e = (ExtraRuta *)&o->extra;
    EstadoAnim *a;
    PuntoRutaI *q;
    s32 v[3];
    s32 dx, dy, dz;
    s32 r;

    e->_10 = 0;
    e->_14 = 0;
    e->_15 = 0;
    D_8007CBA8 = 0;
    if (func_8002ECFC(o)) {
        a = o->anim;
        a->velocidad = 0;
        a->_4E = 0x800;
        a->animacion = o->animaciones[0];
        a->_50 = 0;
        a->_53 = a->animacion;
        a->_52 = a->_50;
        *((s8 *)a + 8) = func_80030068(((s32 *)o->modelo)[1]);
    }
    if ((s32)e->punto != 0) {
        e->punto = &D_800D588C[(s32)e->punto];
        o->x = e->punto->x;
        o->y = e->punto->y;
        o->z = e->punto->z;
        q = &D_800D588C[e->punto->siguiente];
        dx = q->x;
        dy = q->y;
        dz = q->z;
        o->escala[0] = 5;
        o->escala[1] = 5;
        o->escala[2] = 5;
        e->paso[0] = (dx - o->x) >> 4;
        e->paso[1] = (dy - o->y) >> 4;
        e->paso[2] = (dz - o->z) >> 4;
        e->rumbo[0] = dx - o->x;
        e->rumbo[1] = dy - o->y;
        e->rumbo[2] = dz - o->z;
        func_8001C45C(e->rumbo);
        e->pasos = 16;
    } else {
        v[0] = o->x;
        v[1] = o->y - 0x6667 - 0x7FFF;
        v[2] = o->z;
        v[1] = func_800223E8(v);
        o->y = v[1] - 0x3334 - 0x7FFF;
        e->paso[0] = 0;
        e->paso[1] = 0;
        e->paso[2] = 0;
        e->pasos = 1;
        e->rumbo[0] = 0;
        e->rumbo[1] = 0x1000;
        e->rumbo[2] = 0;
        func_8002205C(e->rumbo, 0, o->rot[1]);
    }
    r = func_8001E588(o);
    o->estado = 0;
    return r;
}

/* Lleva *pp al ultimo punto de su ruta (siguiendo los siguientes); si la ruta da la vuelta, al anterior del
 * de partida. Devuelve (v0) 0, o el desplazamiento del anterior en la tabla. */
s32 func_80048104(PuntoRutaI **pp) {
    PuntoRutaI *p = *pp;
    PuntoRutaI *inicio = p;
    s32 n;

    while ((n = p->siguiente) != 0) {
        p = &D_800D588C[n];
        if (p == inicio) {
            n = *(s16 *)((u8 *)p + 0x10);
            p = &D_800D588C[n];
            *pp = p;
            return n * 0x18;
        }
    }
    *pp = p;
    return 0;
}

extern s32 D_8007CC5C;

/* Inicia un objeto que va por su ruta: su punto, el siguiente (destino), el de partida, el alcance al
 * cuadrado, y avisa que hay uno (D_8007CC5C). Devuelve 1. */
s32 func_80052784(Objeto *o) {
    u8 *e = (u8 *)&o->extra;
    PuntoRutaI *p, *q;
    s32 a;

    e[0x24] = 1;
    *(PuntoRutaI **)e = &D_800D588C[*(s32 *)e];
    p = *(PuntoRutaI **)e;
    q = &D_800D588C[p->siguiente];
    *(s32 *)(e + 0xC) = q->x;
    *(s32 *)(e + 0x10) = D_800D588C[(*(PuntoRutaI **)e)->siguiente].y;
    *(s32 *)(e + 0x14) = D_800D588C[(*(PuntoRutaI **)e)->siguiente].z;
    *(s32 *)(e + 0x18) = (*(PuntoRutaI **)e)->x;
    *(s32 *)(e + 0x1C) = (*(PuntoRutaI **)e)->y;
    *(s32 *)(e + 0x20) = (*(PuntoRutaI **)e)->z;
    o->estado = 0;
    a = *(s32 *)(e + 8) >> 8;
    *(s32 *)(e + 8) = ((a * a) >> 8) << 8;
    D_8007CC5C = 1;
    return 1;
}
