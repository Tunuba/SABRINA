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

/* Raiz cuadrada entera por el metodo de Newton: empieza en la mitad y repite x = (x + n / x) / 2 hasta
 * que no cambia, 40 vueltas como mucho. Con n de 0 o 1 la primera division es entre cero (el juego no lo
 * revisa). */
s32 func_8001C3C4(s32 n) {
    s32 x = n >> 1;
    s32 antes;
    u32 vueltas = 0;

    do {
        antes = x;
        x = (x + n / x) >> 1;
        vueltas++;
    } while (vueltas < 40 && x != antes);
    return x;
}
