#include "objeto.h"

extern s8 vida_barra;
extern void ActualizarBarraVida(void);

/* Cura a Sabrina: 4 puntos, o 20 si mucho != 0, sin pasar de 20, y redibuja la barra. */
void func_800300C4(s32 mucho) {
    s8 n = mucho != 0 ? 0x14 : 4;
    p_sabrina->vida += n;
    if (p_sabrina->vida >= 0x15) {
        p_sabrina->vida = 0x14;
    }
    vida_barra = p_sabrina->vida;
    ActualizarBarraVida();
}

extern s16 D_8007CB70, D_8007C872;

/* Despues de un golpe: si a Sabrina le queda vida, la animacion de dolor (si no estaba ya) y un rato sin
   que le vuelva a doler; si no, la de partida y el estado 2 (se muere). Devuelve lo que queda en v0. */
s32 func_80031000(void) {
    Objeto *s = p_sabrina;
    u8 *e = (u8 *)&s->extra;
    EstadoAnim *a = s->anim;
    u16 *t = s->animaciones;

    if (s->forma.banderas & 0x8000) {
        return 0x8000;
    }
    if (s->vida > 0) {
        if (s->extra._1D == 0) {
            a->animacion = t[3];
            a->_50 = 0;
            a->_4E = 0x800;
            D_8007CB70 = 3;
        }
        s->extra.espera_golpe = 0x1E;
        return 0x1E;
    }
    a->animacion = t[0];
    a->_50 = 0;
    a->_4E = 0x800;
    D_8007CB70 = 0;
    e[0x1A] = -1;
    e[0x1B] = -1;
    p_sabrina->estado = 2;
    D_8007C872 = 0;
    return (s32)p_sabrina;
}
