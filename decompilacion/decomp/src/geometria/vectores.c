#include "gte.h"

/* Producto vectorial de v con la diagonal de la matriz m, usando el coprocesador geometrico. Guarda y
 * devuelve la matriz de giro que habia, porque la orden op trabaja con ella. */
void func_8001C404(s32 *fuera, s32 *m, s32 *v) {
    s32 g0, g1, g2;

    gte_leer_giro(g0, g1, g2);
    gte_poner_giro(m[0], m[1], m[2]);
    gte_cargar_ir3(v);
    gte_op();
    gte_guardar_mac3(fuera);
    gte_poner_giro(g0, g1, g2);
}
