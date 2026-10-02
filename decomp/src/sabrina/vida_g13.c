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
