#include "objeto.h"

/* Los hechizos de Sabrina: elegir uno, lanzarlo y recargarlo. */

/* Un hechizo (16 bytes, en D_80074BC4). */
typedef struct {
    void (*efecto)(Objeto *o);       /* 0x00, si no crea un proyectil */
    s32 proyectil;                   /* 0x04, mayor que 0: crea el objeto 6 */
    u8 _08[5];
    s8 espera;                       /* 0x0D, pasos antes de poder volver a lanzar */
    u8 _0E[2];
} Hechizo;

/* Lo que lleva Sabrina de los hechizos. */
typedef struct {
    u8 _00[8];
    s32 botones;                     /* 0x08, los recien apretados */
    u8 _0C[0x12];
    s8 estado;                       /* 0x1E, 0 esperar, 1 preparar, 2 lanzar, 3 terminar, 4 repetir si quedan */
    u8 _1F[3];
    s8 actual;                       /* 0x22, el que se va a lanzar (-1 ninguno, 8 el basico) */
    s8 espera;                       /* 0x23 */
    s8 elegido;                      /* 0x24, el del marcador */
    s8 recarga;                      /* 0x25 */
} EstadoHechizo;

extern Hechizo D_80074BC4[];
extern s8 hechizos[];                /* cuantas cargas hay de cada uno */
extern s8 nivel_actual;
extern s8 D_8007C8B8;                /* cargas del basico */
extern Objeto *D_8007CB8C;           /* el objeto que va con Sabrina */
extern s32 D_8007CB7C;
extern s32 D_8007CA58;               /* botones apretados en este paso */
extern s32 func_80022EF4(s32 paso);
extern void func_8003012C(Objeto *o);
extern s32 func_8003015C(Objeto *o);
extern s32 func_8002EFD0(Objeto *o);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern Objeto *func_800252A0(s32 clase, Objeto *padre, s32 x, s32 y, s32 z, s32 vx, s32 vy, s32 vz, s32 rx,
                             s32 ry, s32 rz, s32 a, s32 b);

/* Un paso de los hechizos de Sabrina (o): cambia el elegido con los botones 4 y 8 y avanza el estado. Los
 * botones 0x20 (el elegido) y 0x80 (el basico) lanzan. El basico se recarga solo, hasta 99. */
void func_80032B98(Objeto *o, EstadoHechizo *s) {
    s32 b = s->botones;
    EstadoAnim *anim = D_8007CB8C->anim;
    s32 r, v;
    void (*f)(Objeto *);

    if (D_8007CB7C == 0) {
        if (D_8007CA58 & 4) {
            r = (s8)func_80022EF4(0xFF);
            if (r >= 0) {
                s->elegido = r;
            }
        }
        if (D_8007CA58 & 8) {
            r = (s8)func_80022EF4(1);
            if (r >= 0) {
                s->elegido = r;
            }
        }
    }
    switch (s->estado) {
    case 0:
        if (b & 0xA0) {
            if (b & 0x20) {
                s->actual = -1;
                if (nivel_actual != 13) {
                    v = s->elegido;
                    if (hechizos[v] == 0) {
                        return;
                    }
                    s->actual = v;
                }
            } else {
                s->actual = 8;
            }
            v = s->actual;
            if (v >= 0 && hechizos[v] != 0) {
                s->estado = 1;
                func_8003012C(D_8007CB8C);
            }
        }
        if (D_8007C8B8 < 0x63) {
            v = s->recarga;
            s->recarga = v - 1;
            if (v <= 0) {
                v = D_8007C8B8;
                D_8007C8B8 = v + 1;
                s->recarga = v >> 2;
            }
        }
        break;
    case 1:
        if (func_8003015C(D_8007CB8C) == 1) {
            s->estado = 2;
        }
        break;
    case 4:
        s->estado = 3;
        v = s->actual;
        if (v >= 0 && hechizos[v] != 0) {
            s->estado = 2;
        }
        break;
    case 2:
        s->estado = 3;
        if (s->espera <= 0) {
            hechizos[s->actual]--;
            v = s->actual;
            if (D_80074BC4[v].proyectil > 0) {
                TocarSonido(v == 8 ? 2 : 3, 0, 0x2A, 0x7F);
                func_800252A0(6, o, 0x4000, 0xFFFF0000, 0, 0, 0, 0, 0, 0, 1, s->actual, 0);
            } else {
                f = D_80074BC4[v].efecto;
                if (f != NULL) {
                    f(o);
                }
            }
            s->espera = D_80074BC4[s->actual].espera;
        }
        if (b & 0xA0) {
            s->actual = (b & 0x20) ? s->elegido : 8;
        } else {
            s->estado = 3;
        }
        break;
    case 3:
        if (func_8002EFD0(D_8007CB8C) != 0) {
            s->estado = 0;
            anim->animacion = *D_8007CB8C->animaciones;
            anim->_50 = 0;
        }
        break;
    }
}
