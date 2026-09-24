#include "objeto.h"

/* Formas de colision. CrearObjetoMundo copia la forma de la clase del objeto y la ajusta con estas
 * funciones segun el tipo. Las copias van enteras (28 bytes) y el tipo con sus dos valores aparte. */

typedef struct {
    s32 w[7];
} Medidas;

/* Radio de una forma de tipo 1, guardado tambien al cuadrado (16.16, con 8 bits de precision). */
void func_80039BA0(Medidas *m, s32 radio) {
    m->w[1] = radio;
    m->w[2] = (((m->w[1] >> 8) * (m->w[1] >> 8)) >> 8) << 8;
}

/* Radio de una forma de tipo 2. */
void func_80039AF4(Medidas *m, s32 radio) {
    m->w[2] = radio;
    m->w[3] = (((m->w[2] >> 8) * (m->w[2] >> 8)) >> 8) << 8;
}

/* Las tres vuelven la forma tal cual; el juego las llama antes de ajustar cada tipo. */
Forma *func_8003A250(Forma *f) {
    return f;
}

Forma *func_8003A258(Forma *f) {
    return f;
}

Forma *func_8003A260(Forma *f) {
    return f;
}

void func_80039A34(Forma *dst, Medidas *src, s16 a, s16 b) {
    dst->tipo = 3;
    dst->_20 = a;
    dst->banderas = b;
    *(Medidas *)dst = *src;
}

void func_80039A70(Forma *dst, Medidas *src, s16 a, s16 b) {
    Medidas m;

    dst->tipo = 2;
    dst->_20 = a;
    dst->banderas = b;
    m = *src;
    func_80039AF4(&m, m.w[2]);
    *(Medidas *)dst = m;
}

void func_80039B1C(Forma *dst, Medidas *src, s16 a, s16 b) {
    Medidas m;

    dst->tipo = 1;
    dst->_20 = a;
    dst->banderas = b;
    m = *src;
    func_80039BA0(&m, m.w[1]);
    *(Medidas *)dst = m;
}
