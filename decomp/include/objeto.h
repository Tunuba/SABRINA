/* El objeto del mundo: Sabrina, enemigos, Salem, cofres... Lo que se sabe de cada campo sale de las
 * funciones ya verificadas; los huecos (_XX) son lo que falta entender. */
#ifndef OBJETO_H
#define OBJETO_H

#include "juego.h"

typedef struct Objeto Objeto;

/* Forma de colision de un objeto: el centro (apunta a la posicion del objeto) y las medidas, que dependen
 * del tipo. Los radios van en 16.16 y se guardan tambien al cuadrado. */
typedef struct {
    s32 *centro;                     /* 0x00 */
    s32 m[6];                        /* 0x04, medidas: tipo 1 radio en m[0] y su cuadrado en m[1]; tipo 2
                                      * radio en m[1] y su cuadrado en m[2] */
    s16 tipo;                        /* 0x1C, 1, 2 o 3 */
    s16 banderas;                    /* 0x1E, 0x800 hace dano al tocar, 0x8000 no */
    s16 _20;
} Forma;
typedef void (*FuncObjeto)(Objeto *);
typedef void (*FuncObjeto2)(Objeto *, Objeto *);

/* Estado de la animacion de un objeto. */
typedef struct EstadoAnim {
    u8 _00[0x48];
    struct EstadoAnim *sig;          /* 0x48, siguiente libre mientras esta en la lista de libres */
    s16 velocidad;                   /* 0x4C, 0x1000 = normal */
    s16 _4E;
    u8 _50;
    u8 animacion;                    /* 0x51, animacion que se esta mostrando */
    u8 _52;
    u8 _53;
} EstadoAnim;
EN(EstadoAnim, sig, 0x48);
EN(EstadoAnim, velocidad, 0x4C);
EN(EstadoAnim, animacion, 0x51);

/* La segunda parte del objeto, en +0x74; el juego pasa su direccion por separado. */
typedef struct {
    u8 _00[0x14];
    s16 espera_golpe;                /* 0x14 (0x88 del objeto), pasos que faltan para poder volver a doler */
    u8 _16[4];
    s8 _1A;
    s8 _1B;
    s8 _1C;
    s8 _1D;                          /* 0x1D (0x91 del objeto) */
} ObjExtra;
EN(ObjExtra, espera_golpe, 0x14);

struct Objeto {
    FuncObjeto actualizar;           /* 0x00, lo que hace el objeto en cada paso (su estado) */
    u8 _04[4];
    FuncObjeto2 aviso;               /* 0x08, le avisa de otro objeto (a Sabrina la toca un enemigo) */
    u8 _0C[0x10];
    EstadoAnim *anim;                /* 0x1C */
    u16 _20;
    u16 tipo;                        /* 0x22, el tipo de WRLDDATA */
    s32 x, y, z;                     /* 0x24 */
    u8 _30[8];
    s32 empuje_x;                    /* 0x38 */
    s32 vel_y;                       /* 0x3C, la gravedad le suma 0x51E en cada paso */
    s32 empuje_z;                    /* 0x40 */
    u8 _44[0x20];
    u16 *animaciones;                /* 0x64, numero de animacion para cada accion */
    u8 _68[4];
    void *datos;                     /* 0x6C, su registro de WRLDDATA (0x9C bytes) */
    s16 estado;                      /* 0x70, 2 = muerto */
    s16 _72;
    ObjExtra extra;                  /* 0x74 */
    u8 _92[0x62];
    Forma forma;                     /* 0xF4, 0x24 bytes con el relleno; sus banderas caen en 0x112 */
    s8 vida;                       /* 0x118, de todos los objetos, enemigos incluidos */
    s8 dano;                         /* 0x119, lo que quita a Sabrina al tocarla, por cuatro */
};
EN(Objeto, aviso, 0x08);
EN(Objeto, anim, 0x1C);
EN(Objeto, tipo, 0x22);
EN(Objeto, x, 0x24);
EN(Objeto, empuje_x, 0x38);
EN(Objeto, vel_y, 0x3C);
EN(Objeto, animaciones, 0x64);
EN(Objeto, estado, 0x70);
EN(Objeto, extra, 0x74);
EN(Objeto, forma, 0xF4);
EN(Objeto, vida, 0x118);

extern Objeto *p_sabrina;            /* 0x8007CAF8 */

#endif
