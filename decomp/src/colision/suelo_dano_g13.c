#include "objeto.h"

/* El dano del suelo: lo que pasa cuando Sabrina pisa un suelo que quema o que mata. */

/* La parte extra de Sabrina que se usa aqui. */
typedef struct {
    u8 _00[0x0C];
    u16 suelo;                       /* 0x0C, el tipo del suelo que pisa */
    u8 _0E[0x0A];
    s16 contacto;                    /* 0x18, 0x10: en el piso */
    s8 cuadro_a, cuadro_b;           /* 0x1A */
    u8 _1C;
    s8 accion;                       /* 0x1D, 0xE: recien quemada */
} ExtraSuelo;

extern s32 truco_invencible;
extern char texto_invencible[];
extern Objeto *D_8007CB8C;           /* el companero */
extern s8 vida_barra;
extern s8 nivel_actual;
extern s32 ImprimirDepuracion(char *texto);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern s32 func_80021CE4(s32 n);     /* al azar, de 0 a n - 1 */
extern u8 *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                          s32 d, s32 e, s32 f, s32 g, s32 h);
extern void ActualizarBarraVida(void);

#define ANIMAR(a, n) ((a)->animacion = (n), (a)->_50 = 0, (a)->_4E = 0x1000)

/* Cae muerta: Sabrina y su companero en su primera animacion y el estado 2. */
static s32 morir(Objeto *o, ExtraSuelo *e, u16 *t, u16 *tc) {
    ANIMAR(o->anim, t[0]);
    ANIMAR(D_8007CB8C->anim, tc[0]);
    e->cuadro_a = -1;
    e->cuadro_b = -1;
    o->estado = 2;
    return 2;
}

/* Un suelo que quema: chispas del color del mundo, la animacion de dolor y una vida menos. */
static s32 quemar(Objeto *o, ExtraSuelo *e, u16 *t, u16 *tc) {
    s32 r, g, b, i, dx, dz;
    u8 *p;

    if (e->accion == 0xE) {
        return 0xE;
    }
    TocarSonido(7, 0, 0x2A, 0x7F);
    switch (nivel_actual) {
    case 3:
        r = 0xFF;
        g = 0x8C;
        b = 0;
        break;
    case 1: case 2: case 4: case 5: case 6: case 7: case 8: case 9:
        r = 0x8C;
        g = 0xD8;
        b = 0xE8;
        break;
    default:
        r = 0xB4;
        g = 0xB0;
        b = 0x7C;
        break;
    }
    for (i = 0; i < 16; i++) {
        dx = func_80021CE4(0x3333);
        dx -= func_80021CE4(0x1999);
        dz = func_80021CE4(0x3333);
        dz -= func_80021CE4(0x1999);
        p = CrearParticula(0xC, NULL, 0, o->x, o->y, o->z, dx, -0x1999, dz, 0, 0x28F, 0, 0xF, 0, 0);
        if (p != NULL) {
            *(s32 *)(p + 0x3C) = 0x112;
            p[0x1C] = r;
            p[0x1D] = g;
            p[0x1E] = b;
        }
    }
    e->contacto = 0;
    ANIMAR(o->anim, t[0x12]);
    ANIMAR(D_8007CB8C->anim, tc[0x12]);
    e->accion = 0xE;
    o->vida--;
    vida_barra = o->vida;
    ActualizarBarraVida();
    if (o->vida > 0) {
        return o->vida;
    }
    if (o->estado == 2) {
        return 2;
    }
    return morir(o, e, t, tc);
}

/* Devuelve (v0) lo que deja el original en cada camino. */
s32 DanoPorSuelo(Objeto *o) {
    ExtraSuelo *e = (ExtraSuelo *)&o->extra;
    u16 *t = o->animaciones;
    u16 *tc = D_8007CB8C->animaciones;

    if (truco_invencible != 0) {
        return ImprimirDepuracion(texto_invencible);
    }
    if (!(e->contacto & 0x10)) {
        return 0;
    }
    switch (e->suelo) {
    case 2:
    case 4:
        return quemar(o, e, t, tc);
    case 8:
        if (o->estado == 2) {
            return 2;
        }
        return morir(o, e, t, tc);
    default:
        return e->suelo;
    }
}
