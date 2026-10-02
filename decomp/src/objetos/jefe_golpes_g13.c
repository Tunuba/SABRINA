#include "objeto.h"

/* Los golpes entre un jefe y Sabrina (estado del jefe en 0x70). */

extern s16 partida;
extern s8 vida_barra;
extern void ActualizarBarraVida(void);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern s32 func_80031000(void);
extern void func_80022FD8(s32 vida, s32 x);

/* Le quita 4 de vida a Sabrina y redibuja la barra; si se quedo sin vida (y sin partidas de sobra) el jefe
 * pasa al estado 0xE, si no sigue con func_80031000. Devuelve lo que queda en v0. */
static s32 pegar_a_sabrina(Objeto *o) {
    p_sabrina->vida = SUMA_TRAMPA(p_sabrina->vida, -4);
    vida_barra = p_sabrina->vida;
    return 0;
}

static s32 tras_el_golpe(Objeto *o) {
    ActualizarBarraVida();
    if (vida_barra == 0 && partida < 2) {
        o->estado = 0xE;
        return 0xE;
    }
    return func_80031000();
}

s32 func_80059FBC(Objeto *o) {
    EstadoAnim *a = o->anim;
    u16 *t = o->animaciones;
    u8 *e = (u8 *)&o->extra;
    s16 est = o->estado;

    if (est == 2) {
        o->estado = 4;
        *(s16 *)(e + 0x3C) = 5;
        pegar_a_sabrina(o);
        TocarSonido(0x33, 0, 0x28, 2);
        TocarSonido(7, 0, 0x2A, 0x7F);
        return tras_el_golpe(o);
    }
    if (est == 3) {
        if (a->animacion == t[4]) {
            return t[4];
        }
        TocarSonido(0x32, 0, 0x28, 2);
        o->estado = 5;
        *(s16 *)(e + 0x3C) = 6;
        o->vida = SUMA_TRAMPA(o->vida, -1);
        func_80022FD8(o->vida & 0xFF, 5);
        if (o->vida != 0) {
            return o->vida;
        }
        o->estado = 0x11;
        a->animacion = t[6];
        a->_50 = 0;
        a->_4E = 0x800;
        return 0x800;
    }
    if (est != 0) {
        return est;
    }
    if (p_sabrina->extra.espera_golpe > 0) {
        return p_sabrina->extra.espera_golpe;
    }
    p_sabrina->extra.espera_golpe = 0x1E;
    pegar_a_sabrina(o);
    TocarSonido(7, 0, 0x2A, 0x7F);
    return tras_el_golpe(o);
}

extern s8 nivel_actual;
extern s8 D_800C8582, D_800C8583, D_800C8584, D_800C8585;   /* jefe vencido en los niveles 3, 6, 9 y 12 */
extern u16 D_8007CBD4;
extern s32 func_8002ECFC(Objeto *o);
extern s32 func_80030068(s32 x);
extern void func_8001E588(Objeto *o);

/* Arranque del jefe de los niveles 3, 6, 9 y 12: 5 de vida, la animacion de partida, la escala y la
 * velocidad y el cuadro de cada uno; si ya se vencio queda marcado (0x80 y bandera 0x40 de D_8007CBD4).
 * Devuelve lo que queda en v0. */
s32 func_8005EAD4(Objeto *o) {
    u8 *ob = (u8 *)o;
    u16 *t = o->animaciones;
    u8 *e = (u8 *)&o->extra;
    EstadoAnim *a;
    s8 n, vencido;
    s32 esc;

    ob[0x119] = 1;
    o->vida = 5;
    o->estado = 8;
    func_80022FD8(o->vida & 0xFF, 5);
    if (func_8002ECFC(o) != 0) {
        a = o->anim;
        *(s16 *)((u8 *)a + 0x4C) = 0;
        a->_4E = 0x800;
        a->animacion = t[1];
        a->_50 = 0;
        a->_53 = a->animacion;
        a->_52 = a->_50;
        *((u8 *)a + 8) = func_80030068(*(s32 *)(*(u8 **)(ob + 0x60) + 4));
    }
    o->estado = 8;
    n = nivel_actual;
    esc = (n == 6 || n == 0xC || n == 9 || n == 3) ? 5 : 0x1800;
    *(s32 *)(ob + 0x54) = esc;
    *(s32 *)(ob + 0x58) = esc;
    *(s32 *)(ob + 0x5C) = esc;
    func_8001E588(o);
    n = nivel_actual;
    switch (n) {
    case 3:
        *(s32 *)(e + 0xC) = 0x8000;
        *(s32 *)(e + 0x10) = 0;
        *(s32 *)(e + 0x14) = 0x4CCC;
        e[0x27] = 0x16;
        vencido = D_800C8582;
        break;
    case 6:
        *(s32 *)(e + 0xC) = 0x8000;
        *(s32 *)(e + 0x10) = 0;
        *(s32 *)(e + 0x14) = 0x4CCC;
        e[0x27] = 0x1E;
        vencido = D_800C8583;
        break;
    case 9:
        *(s32 *)(e + 0xC) = 0;
        *(s32 *)(e + 0x10) = 0;
        *(s32 *)(e + 0x14) = 0x9999;
        e[0x27] = 0x17;
        vencido = D_800C8584;
        break;
    case 12:
        *(s32 *)(e + 0xC) = 0;
        *(s32 *)(e + 0x10) = 0;
        *(s32 *)(e + 0x14) = 0x4CCC;
        e[0x27] = 0x27;
        vencido = D_800C8585;
        break;
    default:
        return n;
    }
    if (vencido == 0) {
        return 0;
    }
    ob[0x20] |= 0x80;
    D_8007CBD4 |= 0x40;
    return D_8007CBD4;
}
