#include "objeto.h"

/* Lo que pasa cuando un enemigo toca a Sabrina: la empuja, suena el quejido, le quita vida y, si se queda
 * sin vida, muere. */

extern s32 D_8007C8A4;
extern s8 nivel_actual;
extern s32 truco_invencible;         /* distinto de 0: no pierde vida */
extern s8 vida_barra;                /* la vida que muestra la barra */
extern s16 D_8007CB70;

s32 func_8001C33C(s32 *a, s32 *b);   /* producto escalar de dos vectores, en 24.8 */
s32 func_80021CE4(s32 n);            /* numero al azar de 0 a n - 1 */
s32 TocarSonido(s32 sonido, s32 a, s32 b, s32 volumen);
void ActualizarBarraVida(void);

void DanoPorEnemigo(Objeto *sab, Objeto *ene) {
    EstadoAnim *anim = sab->anim;
    u16 *animaciones = sab->animaciones;
    ObjExtra *extra = &sab->extra;
    s32 dir[3];                      /* de Sabrina al enemigo, sin la altura */
    s32 emp[3];                      /* el empuje que lleva Sabrina */
    s16 banderas;
    s8 dano;

    D_8007C8A4 = 0x96;
    dir[1] = 0;
    emp[1] = 0;
    /* En el nivel 14 el objeto de tipo 0x1C no la empuja ni le hace dano: solo recibe el aviso */
    if (nivel_actual != 0xE && ene->tipo == 0x1C) {
        return;
    }
    dir[0] = -(ene->x - sab->x) >> 8;
    dir[2] = -(ene->z - sab->z) >> 8;
    emp[0] = sab->empuje_x >> 8;
    emp[2] = sab->empuje_z >> 8;
    /* Si no se esta alejando ya del enemigo, se la empuja hacia atras */
    if (func_8001C33C(emp, dir) < 1000) {
        sab->empuje_x += dir[0] << 6;
        sab->empuje_z += dir[2] << 6;
    }
    if (nivel_actual == 0xE && ene->tipo == 0x1C) {
        ene->aviso(ene, sab);
        return;
    }
    if (ene->tipo == 0xC) {
        ene->aviso(ene, sab);
    }
    banderas = ene->forma.banderas;
    if (!(banderas & 0x800) || (banderas & 0x8000) || extra->espera_golpe > 0) {
        return;
    }
    if (ene->tipo != 0x32) {
        switch (func_80021CE4(4)) {
        case 0:
            TocarSonido(7, 0, 0x2A, 0x7F);
            break;
        case 1:
            TocarSonido(8, 0, 0x2A, 0x7F);
            break;
        case 2:
            TocarSonido(7, 0, 0x2A, 0x7F);
            break;
        case 3:
            TocarSonido(8, 0, 0x2A, 0x7F);
            break;
        default:
            TocarSonido(8, 0, 0x2A, 0x7F);
            break;
        }
    }
    extra->espera_golpe = 0x1E;
    dano = ene->dano;
    if (dano <= 0) {
        return;
    }
    if (truco_invencible == 0) {
        sab->vida = sab->vida - (s8)(dano * 4);
    }
    if (sab->vida < 0) {
        sab->vida = 0;
    }
    vida_barra = sab->vida;
    ActualizarBarraVida();
    if (sab->vida > 0) {
        if (extra->_1D == 0) {
            anim->animacion = animaciones[3];
            anim->_50 = 0;
            anim->_4E = 0x800;
            D_8007CB70 = 3;
        }
    } else {
        anim->animacion = animaciones[0];
        anim->_50 = 0;
        anim->_4E = 0x800;
        D_8007CB70 = 0;
        extra->_1A = -1;
        extra->_1B = -1;
        sab->estado = 2;
    }
}
