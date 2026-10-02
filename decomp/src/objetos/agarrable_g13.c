#include "objeto.h"

/* Objetos que se pueden agarrar (bandera 0x8000 de 0x112): al tocarlos crean un objeto de la clase 9 que
   los lleva (con su aviso en el bloque +0x10 y el objeto en +0xC), cambian sus funciones y quedan marcados
   con el que los lleva en 0x11C. */

extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern Objeto *func_800252A0(s32 clase, Objeto *padre, s32 x, s32 y, s32 z, s32 vx, s32 vy, s32 vz, s32 rx,
                             s32 ry, s32 rz, s32 a, s32 b);
extern void func_800399A0(Objeto *o, Objeto *h);
extern s32 func_80024DE4(), func_80024DF4(), func_80024F74(), func_80024F84(), func_80039670();
extern s32 thunk_FUN_8001e588(), func_80038EB4(), func_80038F08(), func_8003BBA8(), func_8003909C();
extern s32 func_80039030();

typedef s32 (*Funcion)();

/* f: las seis funciones del objeto (0x00 a 0x14); NULL deja la que tenia. Devuelve lo que queda en v0. */
static s32 agarrar(Objeto *o, s32 sonido, s32 tipo, Funcion aviso, const Funcion *f) {
    u8 *ob = (u8 *)o;
    Objeto *h;
    s32 i;
    s16 b;

    if (*(s16 *)(ob + 0x112) & 0x8000) {
        return 0x8000;
    }
    TocarSonido(sonido, 0, 0x2A, 0x7F);
    h = func_800252A0(9, o, 0, 0, 0, 0, 0, 0, 0, 0, 0, tipo, 0xC8);
    if (h == NULL) {
        return 0;
    }
    *(Funcion *)((u8 *)h + 0x74 + 0x10) = aviso;
    *(Objeto **)((u8 *)h + 0x74 + 0xC) = o;
    func_800399A0(o, h);
    for (i = 0; i < 6; i++) {
        if (f[i] != NULL) {
            *(Funcion *)(ob + i * 4) = f[i];
        }
    }
    b = *(s16 *)(ob + 0x112) | 0x8000;
    *(s16 *)(ob + 0x112) = b;
    *(Objeto **)(ob + 0x11C) = h;
    return b;
}

s32 func_800389DC(Objeto *o) {
    static const Funcion f[6] = {func_80024DE4, func_80024DF4, func_80039670, func_80024F74, func_80024F84,
                                 thunk_FUN_8001e588};
    return agarrar(o, 0x24, 4, func_80038EB4, f);
}

s32 func_80038C38(Objeto *o) {
    static const Funcion f[6] = {func_8003BBA8, NULL, func_80039670, func_80024F74, func_80024F84, NULL};
    return agarrar(o, 0x23, 2, func_80038F08, f);
}

s32 func_80038D38(Objeto *o) {
    static const Funcion f[6] = {func_80039030, func_80024DF4, func_80039670, func_80024F74, func_80024F84,
                                 thunk_FUN_8001e588};
    return agarrar(o, 0x26, 1, func_8003909C, f);
}

extern s8 nivel_actual;
extern s16 huevos;
extern s8 D_800C86A6[];         /* por nivel (0x141 bytes): [0] cuantos huevos hay, [1 + i] si se tomo el i */
extern s8 D_800C86B5[];         /* por nivel: cuantos se tomaron */
extern s32 func_8004AB24();
extern s32 func_8004AAE4(Objeto *o, s32 a, s32 b);

/* Anota el huevo i del nivel; al juntarlos todos crea el premio (clase 0x18). Devuelve lo que queda en
 * v0. */
s32 func_8004C730(s32 i) {
    s32 n = nivel_actual;
    s32 k = SUMA_TRAMPA(SUMA_TRAMPA(n << 2, n) << 6, n);
    s8 *r = D_800C86A6 + k;
    Objeto *h;

    r[i] = 1;
    huevos = SUMA_TRAMPA(huevos, 1);
    D_800C86B5[k] = huevos;
    if (huevos < r[0]) {
        return r[0];
    }
    h = func_800252A0(0x18, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
    if (h == NULL) {
        return 0;
    }
    *(Funcion *)h = func_8004AB24;
    return func_8004AAE4(h, 0, 0);
}
