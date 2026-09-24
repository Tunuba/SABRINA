#include "juego.h"

/* Acercar un angulo (0..0xFFF, una vuelta = 0x1000) o un valor de 8 bits a un objetivo, paso a paso, por
 * el lado mas corto. Devuelven cuanto faltaba (0 si ya se llego). */

extern s32 func_80014AEC(s32 v);     /* valor absoluto */

/* Gira *ang hacia objetivo como mucho |paso|. Si esta mas cerca que eso, lo deja en el objetivo y
 * devuelve 0; si no, devuelve la distancia (por el lado mas corto) que habia. */
s32 func_80021D44(s16 *ang, s32 objetivo, s32 paso) {
    s16 max;
    s16 obj;
    s16 d;
    s16 d0;

    max = func_80014AEC(paso);
    obj = objetivo & 0xFFF;
    *ang = *ang & 0xFFF;
    d = obj - *ang;
    d0 = d;
    if (func_80014AEC(d) <= max) {
        *ang = obj;
        return 0;
    }
    if (func_80014AEC(d0) > 0x800) {
        d = -d0;
    }
    if (d > 0) {
        *ang = (*ang + max) & 0xFFF;
    } else {
        *ang = (*ang - max) & 0xFFF;
    }
    return (s16) func_80014AEC(d);
}

/* Gira *ang hacia objetivo una fraccion de la distancia (distancia >> corrimiento). Cuando la fraccion
 * quedaria por debajo de minimo, gira de a minimo con func_80021D44. */
s32 func_80021E54(s16 *ang, s32 objetivo, s32 corrimiento, s32 minimo) {
    s16 obj;
    s16 d;
    s16 d0;

    obj = objetivo & 0xFFF;
    *ang = *ang & 0xFFF;
    d = obj - *ang;
    d0 = d;
    if (func_80014AEC(d) < (minimo << corrimiento)) {
        return func_80021D44(ang, obj, minimo);
    }
    if (func_80014AEC(d0) > 0x800) {
        if (d > 0) {
            d = d - 0x1000;
        } else {
            d = (d0 + 0x1000) & 0xFFF;
        }
    }
    *ang = (*ang + (d >> corrimiento) + 0x1000) & 0xFFF;
    return (s16) func_80014AEC(d);
}

/* Lo mismo que func_80021D44 para un valor de 8 bits con signo (media vuelta = 0x80). */
s32 func_80021F70(s8 *v, s32 objetivo, s32 paso) {
    s8 max;
    s16 d;
    s16 d0;

    max = func_80014AEC(paso);
    d = objetivo - *v;
    d0 = d;
    if (func_80014AEC(d) <= max) {
        *v = objetivo;
        return 0;
    }
    if (func_80014AEC(d0) > 0x80) {
        d = -d0;
    }
    if (d > 0) {
        *v = *v + max;
    } else {
        *v = *v - max;
    }
    return func_80014AEC(d) & 0xFF;
}
