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

extern s32 func_80014B00(s32 n);
extern s32 SquareRoot0(s32 n);

/* Deja el vector de largo 1 (en 4.12) y devuelve su largo por 100 (en la escala de cada caso). Suma los
 * cuadrados en 64 bits y elige la cuenta segun el tamano: grande (31 bits o mas) con SquareRoot0 de la suma
 * / 65536, mediano (desde 0x80000) con func_8001C3C4 y la division corrida 12, chico corrida 18. */
s32 func_8001C45C(s32 *v) {
    s32 x = v[0], y = v[1], z = v[2];
    s64 suma = (s64)x * x + (s64)y * y + (s64)z * z;
    s32 alto = (s32)(suma >> 32);
    u32 bajo = (u32)suma;
    s32 r, a, w;

    if (alto > 0 || (alto == 0 && bajo >= 0x80000000)) {
        r = SquareRoot0(func_80014B00((bajo >> 16) | (alto << 16))) >> 4;
        v[0] = v[0] / r;
        v[1] = v[1] / r;
        v[2] = v[2] / r;
        return r * 100;
    }
    if (alto > 0 || (alto == 0 && bajo >= 0x80000)) {
        r = func_8001C3C4(func_80014B00(bajo));
        /* si x << 12 cambia de signo, el original niega el cociente */
        a = x << 12;
        v[0] = ((a >= 0) != (x >= 0)) ? -(a / r) : a / r;
        a = y << 12;
        v[1] = ((a >= 0) != (y >= 0)) ? -(a / r) : a / r;
        a = z << 12;
        v[2] = ((a >= 0) != (z >= 0)) ? -(a / r) : a / r;
        return (r * 100) >> 12;
    }
    r = func_8001C3C4(func_80014B00(bajo << 12));
    v[0] = (v[0] << 18) / r;
    v[1] = (v[1] << 18) / r;
    v[2] = (v[2] << 18) / r;
    w = r * 100;
    return w >= 0 ? w >> 18 : (w - 1) >> 18;
}
