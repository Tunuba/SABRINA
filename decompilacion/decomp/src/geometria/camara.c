#include "gte.h"
#include "nodo.h"

/* Tres enteros que el juego pasa por valor: los primeros caben en los registros de argumentos y el resto
 * viaja por la pila, asi que las tres llamadas seguidas quedan en nueve palabras corridas. */
typedef struct {
    s32 v[3];
} Vec3;

extern Matriz D_8008AB58;            /* la matriz de la camara */
extern s16 D_8007CA9C;               /* la pieza del modelo a la que sigue la camara; aqui, ninguna */

extern s32 func_80014AEC(s32 v);                          /* valor absoluto */
extern void func_8001C404(s32 *fuera, s32 *m, s32 *v);    /* producto vectorial */
extern void func_8001C45C(s32 *v);                        /* dejar el vector de largo 1 (4.12) */

/* Pone la camara en "ojo" mirando en la direccion "hacia", con "arriba" como vertical. Las tres filas de
 * la matriz son los ejes de la camara: derecha = arriba x hacia, la vertical corregida = hacia x derecha,
 * y hacia. Si la direccion es casi vertical (nada de x ni de z) los ejes no se pueden sacar asi y se deja
 * la matriz que habia; solo se recalcula la posicion.
 *
 * La traslacion es -M * ojo: se divide el ojo entre cuatro antes de multiplicar y se multiplica despues,
 * porque el coprocesador recorta a 16 bits lo que sale de la matriz. */
void func_8001FA3C(Vec3 ojo, Vec3 hacia, Vec3 arriba) {
    s32 derecha[3];
    s32 vertical[3];

    D_8007CA9C = 0;
    if (func_80014AEC(hacia.v[0]) >= 0x32 || func_80014AEC(hacia.v[2]) >= 0x32) {
        func_8001C404(derecha, arriba.v, hacia.v);
        func_8001C404(vertical, hacia.v, derecha);
        func_8001C45C(derecha);
        func_8001C45C(vertical);
        func_8001C45C(hacia.v);
        D_8008AB58.m[0][0] = derecha[0];
        D_8008AB58.m[0][1] = derecha[1];
        D_8008AB58.m[0][2] = derecha[2];
        D_8008AB58.m[1][0] = vertical[0];
        D_8008AB58.m[1][1] = vertical[1];
        D_8008AB58.m[1][2] = vertical[2];
        D_8008AB58.m[2][0] = hacia.v[0];
        D_8008AB58.m[2][1] = hacia.v[1];
        D_8008AB58.m[2][2] = hacia.v[2];
    }
    D_8008AB58.t[0] = 0;
    D_8008AB58.t[1] = 0;
    D_8008AB58.t[2] = 0;
    gte_poner_matriz(&D_8008AB58);
    gte_poner_traslacion(D_8008AB58.t);
    ojo.v[0] >>= 2;
    ojo.v[1] >>= 2;
    ojo.v[2] >>= 2;
    gte_poner_v0_xy(((u16 *) ojo.v)[0] | (((u16 *) ojo.v)[2] << 16));
    gte_cargar_v0_z(&ojo.v[2]);
    gte_mvmva_v0();
    gte_guardar_ir(D_8008AB58.t);
    D_8008AB58.t[0] = -D_8008AB58.t[0] << 2;
    D_8008AB58.t[1] = -D_8008AB58.t[1] << 2;
    D_8008AB58.t[2] = -D_8008AB58.t[2] << 2;
}
