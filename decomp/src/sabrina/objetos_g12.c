#include "objeto.h"

/* Dos funciones de objetos que van con Sabrina (sin nombre conocido en simbolos.tsv). */

/* Lo que cuelga de Objeto.modelo: en +4 el estado del modelo, con dos matrices de 32 bytes en +0x14 y
 * +0x34 que se copian enteras. */
typedef struct {
    s32 m[8];
} Bloque32;

typedef struct {
    u8 _00[0x14];
    Bloque32 a;                      /* 0x14 */
    Bloque32 b;                      /* 0x34 */
} EstadoModelo;

typedef struct {
    u8 _00[4];
    EstadoModelo *estado;            /* 0x04 */
} ModeloObj;

extern u16 D_8007C8C6;
extern s32 D_8007CBBC;

void func_8002ED4C(Objeto *o);
void func_8002EF8C(Objeto *o);
void func_8002EDC8(Objeto *o);
void func_8001E998(Objeto *o);
s32 func_8001E588(Objeto *o);
s32 func_8002ECFC(Objeto *o);
s32 func_80030068(EstadoModelo *e);
void func_8003019C(void);
void func_8003DD44(s32 a);
void func_8003DDA0(s32 a, s32 b);
s32 func_80022FD8(s32 a, s32 b);
s32 func_800487B0(Objeto *o, Objeto *s, s32 n);

/* Pone el objeto donde esta Sabrina, con su giro y su escala, lo actualiza y le copia las dos matrices
 * del modelo de ella. */
void func_80055CAC(Objeto *o) {
    o->x = p_sabrina->x;
    o->y = p_sabrina->y;
    o->z = p_sabrina->z;
    o->rot[0] = p_sabrina->rot[0];
    o->rot[1] = p_sabrina->rot[1];
    o->rot[2] = p_sabrina->rot[2];
    o->escala[0] = p_sabrina->escala[0];
    o->escala[1] = p_sabrina->escala[1];
    o->escala[2] = p_sabrina->escala[2];
    func_8002ED4C(o);
    func_8002EF8C(o);
    func_8002EDC8(o);
    func_8001E998(o);
    func_8001E588(o);
    ((ModeloObj *)o->modelo)->estado->a = ((ModeloObj *)p_sabrina->modelo)->estado->a;
    ((ModeloObj *)o->modelo)->estado->b = ((ModeloObj *)p_sabrina->modelo)->estado->b;
}

/* Pasa el objeto al estado 9 con vida 5: si func_8002ECFC lo permite reinicia la animacion con la
 * primera de su tabla, guarda su posicion en la parte extra (+0x2C de extra), avisa seis veces contra
 * Sabrina y la pasa a ella al estado de la animacion 21. */
void func_8005A1EC(Objeto *o) {
    u16 *tabla = o->animaciones;
    u8 *extra = (u8 *)&o->extra;
    EstadoAnim *a;

    if (func_8002ECFC(o) != 0) {
        a = o->anim;
        a->velocidad = 0;
        a->_4E = 0x1000;
        a->animacion = *tabla;
        a->_50 = 0;
        a->_53 = a->animacion;
        a->_52 = a->_50;
        a->_00[8] = func_80030068(((ModeloObj *)o->modelo)->estado);
    }
    *(s32 *)(extra + 0x2C) = o->x;
    *(s32 *)(extra + 0x30) = o->y;
    *(s32 *)(extra + 0x34) = o->z;
    *(s16 *)(extra + 0x38) = 0;
    o->estado = 9;
    o->vida = 5;
    func_8003DDA0(0x57, 0);
    func_8003DD44((D_8007C8C6 * 15) & 0xFF);
    func_80022FD8(o->vida & 0xFF, 5);
    func_800487B0(o, p_sabrina, 0x96);
    func_800487B0(o, p_sabrina, 0x96);
    func_800487B0(o, p_sabrina, 0x96);
    func_800487B0(o, p_sabrina, 0x96);
    func_800487B0(o, p_sabrina, 0x96);
    func_800487B0(o, p_sabrina, 0x96);
    func_8003019C();
    D_8007CBBC = 1;
}
