#include "objeto.h"

/* Crear un objeto del mundo de una clase del nivel. */

typedef void (*IniciarClase)(Objeto *o, s32 a, s32 b);

/* Una clase de objeto (0x54 bytes, en la tabla del nivel). */
typedef struct {
    IniciarClase iniciar;            /* 0x00, se llama con el objeto nuevo y los dos ultimos argumentos */
    u32 cabeza[7];                   /* 0x04, se copian al comienzo del objeto */
    u8 _20[2];
    s16 modelo;                      /* 0x22, indice en modelos_cargados */
    void *animaciones;               /* 0x24 */
    s16 escala[3];                   /* 0x28 */
    u8 _2E[2];
    u32 forma[9];                    /* 0x30, la forma de colision */
} ClaseObjeto;
EN(ClaseObjeto, modelo, 0x22);
EN(ClaseObjeto, escala, 0x28);
EN(ClaseObjeto, forma, 0x30);

extern ClaseObjeto *tabla_clases_niveles[];
extern s8 nivel_actual;
extern void *modelos_cargados[];
extern void *D_8007C9F0;
extern char D_8006CF48[];            /* "Cannot Spawn: Out of World Objects" */

extern Objeto *func_800256E0(void);  /* un objeto libre */
extern void *func_8001E06C(void *modelo, void *padre);
extern void func_800206E0(Objeto *o);
extern void func_8001E588(Objeto *o);
extern void ImprimirDepuracion(char *texto);
extern void *func_8003A250(Forma *f);
extern void *func_8003A258(Forma *f);
extern void *func_8003A260(Forma *f);
extern void func_80039A34(Forma *f, void *m, s32 a, s32 b);
extern void func_80039A70(Forma *f, void *m, s32 a, s32 b);
extern void func_80039B1C(Forma *f, void *m, s32 a, s32 b);
extern s32 rsin(s32 a);
extern s32 rcos(s32 a);

/* Crea un objeto de la clase (1 a 0x36) en (x, y, z) con velocidad (vx, vy, vz) y giro (rx, ry, rz). Con
 * padre, la posicion, la velocidad horizontal y el giro son relativos a el (girados con su giro y). Copia
 * de la clase la cabecera, la escala, la forma y el modelo, y llama a su iniciar con a y b. Devuelve el
 * objeto, o NULL. */
Objeto *func_800252A0(s32 clase, Objeto *padre, s32 x, s32 y, s32 z, s32 vx, s32 vy, s32 vz, s32 rx, s32 ry,
                      s32 rz, s32 a, s32 b) {
    ClaseObjeto *c;
    Objeto *o;
    void *m;
    s16 gx = rx, gy = ry, gz = rz, s, co;
    s32 i;

    if (clase >= 0x37 || clase == 0) {
        return NULL;
    }
    c = &tabla_clases_niveles[nivel_actual][clase];
    o = func_800256E0();
    if (o == NULL) {
        ImprimirDepuracion(D_8006CF48);
        return NULL;
    }
    o->tipo = clase;
    o->datos = NULL;
    m = NULL;
    if (modelos_cargados[c->modelo] != NULL) {
        m = func_8001E06C(modelos_cargados[c->modelo], D_8007C9F0);
        func_800206E0(o);
    }
    o->animaciones = c->animaciones;
    o->modelo = m;
    if (padre != NULL) {
        gx = gx + padre->rot[0];
        gy = gy + padre->rot[1];
        gz = gz + padre->rot[2];
        s = rsin(gy);
        co = rcos(gy);
        o->x = padre->x + ((co * x) >> 12) + ((s * z) >> 12);
        o->z = padre->z - ((s * x) >> 12) + ((co * z) >> 12);
        o->y = y + padre->y;
        o->empuje_x = ((co * vx) >> 12) + ((s * vz) >> 12);
        o->empuje_z = ((co * vz) >> 12) - ((s * vx) >> 12);
        /* que GCC no junte las dos ramas: guardaria el valor en la pila del llamador (el lugar de vz) */
        __asm__ volatile("" ::: "memory");
    } else {
        o->x = x;
        o->y = y;
        o->z = z;
        o->empuje_x = vx;
        o->empuje_z = vz;
        __asm__ volatile("" ::: "memory");
    }
    o->vel_y = vy;
    o->rot[0] = gx;
    o->rot[1] = gy;
    o->rot[2] = gz;
    o->escala[0] = c->escala[0];
    o->escala[1] = c->escala[1];
    o->escala[2] = c->escala[2];
    for (i = 0; i < 7; i++) {
        ((u32 *)o)[i] = c->cabeza[i];
    }
    func_8001E588(o);
    for (i = 0; i < 9; i++) {
        ((u32 *)&o->forma)[i] = c->forma[i];
    }
    o->forma.centro = &o->x;
    switch (o->forma.tipo) {
    case 3:
        func_80039A34(&o->forma, func_8003A258(&o->forma), o->forma._20, o->forma.banderas);
        break;
    case 2:
        func_80039A70(&o->forma, func_8003A250(&o->forma), o->forma._20, o->forma.banderas);
        break;
    case 1:
        func_80039B1C(&o->forma, func_8003A260(&o->forma), o->forma._20, o->forma.banderas);
        break;
    }
    c->iniciar(o, a, b);
    return o;
}

/* Un registro de WRLDDATA (0x9C bytes): donde va un objeto del nivel. */
typedef struct {
    s32 x, y, z;                     /* 0x00 */
    s16 tipo;                        /* 0x0C, la clase */
    s16 rot[3];                      /* 0x0E */
    s16 escala[3];                   /* 0x14, se multiplica por la de la clase */
    u8 _1A[2];
    u8 extra[0x80];                  /* 0x1C, se copian 0x7F bytes a la parte extra del objeto */
} RegistroMundo;
EN(RegistroMundo, tipo, 0x0C);
EN(RegistroMundo, escala, 0x14);
EN(RegistroMundo, extra, 0x1C);

extern s32 RecogibleNoTomado(RegistroMundo *r);
extern s32 CrearRecogible(RegistroMundo *r);
extern void func_80024A48(Objeto *o);
extern void *memcpy(void *d, const void *s, u32 n);
typedef s32 (*IniciarClaseV)(Objeto *o, s32 a, s32 b);

/* Crea el objeto de un registro de WRLDDATA. Los recogibles (tipos 4, 0x12, 0x13 y 0x17) van por
 * CrearRecogible, si no se tomaron ya. Devuelve lo que devuelve el iniciar de la clase (v0 del original;
 * con un tipo de 0x37 o mas, el tipo). */
s32 CrearObjetoMundo(RegistroMundo *r) {
    s32 tipo = r->tipo;
    ClaseObjeto *c;
    Objeto *o;
    s32 i;

    if (tipo >= 0x37) {
        return tipo;
    }
    if (tipo == 0x17 || tipo == 0x13 || tipo == 0x12 || tipo == 4) {
        if (RecogibleNoTomado(r) == 0) {
            return 0;
        }
        return CrearRecogible(r);
    }
    c = &tabla_clases_niveles[nivel_actual][tipo];
    o = func_800256E0();
    if (o == NULL) {
        return 0;
    }
    o->tipo = r->tipo;
    o->datos = r;
    if (modelos_cargados[c->modelo] != NULL) {
        o->modelo = func_8001E06C(modelos_cargados[c->modelo], D_8007C9F0);
        func_800206E0(o);
    }
    o->animaciones = c->animaciones;
    o->x = r->x;
    o->y = r->y;
    o->z = r->z;
    o->rot[0] = r->rot[0];
    o->rot[1] = r->rot[1];
    o->rot[2] = r->rot[2];
    o->escala[0] = (c->escala[0] * r->escala[0]) >> 12;
    o->escala[1] = (c->escala[1] * r->escala[1]) >> 12;
    o->escala[2] = (c->escala[2] * r->escala[2]) >> 12;
    func_8001E588(o);
    func_80024A48(o);
    for (i = 0; i < 7; i++) {
        ((u32 *)o)[i] = c->cabeza[i];
    }
    for (i = 0; i < 9; i++) {
        ((u32 *)&o->forma)[i] = c->forma[i];
    }
    o->forma.centro = &o->x;
    switch (o->forma.tipo) {
    case 3:
        func_80039A34(&o->forma, func_8003A258(&o->forma), o->forma._20, o->forma.banderas);
        break;
    case 2:
        func_80039A70(&o->forma, func_8003A250(&o->forma), o->forma._20, o->forma.banderas);
        break;
    case 1:
        func_80039B1C(&o->forma, func_8003A260(&o->forma), o->forma._20, o->forma.banderas);
        break;
    }
    memcpy(&o->extra, r->extra, 0x7F);
    return ((IniciarClaseV)c->iniciar)(o, 0, 0);
}
