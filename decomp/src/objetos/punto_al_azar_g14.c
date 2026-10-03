#include "juego.h"

/* Un punto al azar cerca de otro, en la direccion de un tercero. */

extern void func_8001C45C(s32 *v);   /* normaliza un vector (largo 0x1000) */
extern s32 func_80021CE4(s32 n);     /* numero al azar entre 0 y n-1 */

/* centro + direccion(a - centro) * dist, y despues ese punto mas una direccion al azar * dist (en fijo de
 * 8 bits). Deja el resultado en r. Ojo: al sumar, el original cruza y con z (r[2] toma la y del primer punto
 * y r[1] la z). */
void func_800484CC(s32 *a, s32 *centro, s32 dist, s32 *r) {
    s32 v[3];
    s32 d;

    v[0] = RESTA_TRAMPA(a[0], centro[0]);
    v[1] = RESTA_TRAMPA(a[1], centro[1]);
    v[2] = RESTA_TRAMPA(a[2], centro[2]);
    func_8001C45C(v);
    d = dist >> 8;
    v[0] = SUMA_TRAMPA(centro[0], ((v[0] >> 8) * d >> 8) << 8);
    v[2] = SUMA_TRAMPA(centro[2], ((v[2] >> 8) * d >> 8) << 8);
    v[1] = SUMA_TRAMPA(centro[1], ((v[1] >> 8) * d >> 8) << 8);
    r[0] = SUMA_TRAMPA(func_80021CE4(0x1000), -0x800);
    r[2] = SUMA_TRAMPA(func_80021CE4(0x1000), -0x800);
    r[1] = SUMA_TRAMPA(func_80021CE4(0x1000), -0x800);
    func_8001C45C(r);
    r[0] = SUMA_TRAMPA(v[0], ((r[0] >> 8) * d >> 8) << 8);
    r[2] = SUMA_TRAMPA(v[1], ((r[2] >> 8) * d >> 8) << 8);
    r[1] = SUMA_TRAMPA(v[2], ((r[1] >> 8) * d >> 8) << 8);
}
