#include "objeto.h"

/* Un punto de reaparicion con su companero: aparece creciendo desde su punto de ruta; cuando Sabrina
 * llega cerca, anota ahi donde reaparece, suena su musica y espera a que termine. */

/* La parte extra que se usa. */
typedef struct {
    s32 *punto;                      /* 0x00, su punto de ruta (x, y, z) */
    s32 distancia;                   /* 0x04 */
    s16 rumbo;                       /* 0x08 */
    s16 numero;                      /* 0x0A */
    u8 _0C[2];
    s16 pasos;                       /* 0x0E */
    Objeto *otro;                    /* 0x10 */
    u8 _14[4];
    s32 paso[3];                     /* 0x18 */
    s32 frente[3];                   /* 0x24 */
} ExtraReaparicion;

#define FUNC_0C(o) (*(s32 (**)(Objeto *))((u8 *)(o) + 0xC))

extern s32 D_8007CB00, D_8007CB04, D_8007CB08;  /* donde reaparece Sabrina */
extern s16 D_8007CB0C;
extern s32 D_8007CBEC;
extern s32 D_8007CBA4, D_8007CBA8;
extern u16 D_8007C8C6;
extern s32 D_8007CA50;

extern s32 rsin(s32 a);
extern s32 rcos(s32 a);
extern s32 func_80034F84(Objeto *o, Objeto *otro);
extern s32 func_8002225C(Objeto *o, s32 x, s32 y, s32 z);
extern void func_80034FD0(s32 *v, s32 *p);
extern s32 func_800223E8(s32 *pos);
extern void func_8003DDA0(s32 pista, s32 a);
extern void func_8003DD44(s32 volumen);
extern void func_8003DEE8(void);
extern s32 func_8003E060(void);
extern void func_8003DDFC(void);
extern s32 func_80035098(void);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);

/* Devuelve (v0) lo que deja el original en cada camino. */
s32 func_800349F0(Objeto *o) {
    ExtraReaparicion *e = (ExtraReaparicion *)&o->extra;
    Objeto *b;
    s32 v[3], p[3];
    s32 d, r;

    switch (o->estado) {
    case 0:
        if (e->otro != NULL) {
            o->estado = 6;
            e->pasos = 16;
            o->escala[0] = 5;
            o->escala[1] = 5;
            o->escala[2] = 5;
            o->x = e->punto[0];
            o->y = e->punto[1];
            o->z = e->punto[2];
            return TocarSonido(0x31, 0, 0x2A, 0x7F);
        }
        return FUNC_0C(o)(o);
    case 6:
        e->pasos--;
        o->x += e->paso[0];
        o->y += e->paso[1];
        o->z += e->paso[2];
        o->escala[0] += 0x100;
        o->escala[1] += 0x100;
        o->escala[2] += 0x100;
        if (e->pasos > 0) {
            return e->pasos;
        }
        o->estado = 1;
        o->escala[0] = 0x1000;
        o->escala[1] = 0x1000;
        o->escala[2] = 0x1000;
        return 0x1000;
    case 1:
        if (e->otro == NULL || func_80034F84(o, e->otro) == 0) {
            return 0;
        }
        d = func_8002225C(o, e->otro->x, e->otro->y, e->otro->z);
        if (d >= 0x38000) {
            if (d > 0x40000) {
                return FUNC_0C(o)(o);
            }
            return d;
        }
        b = e->otro;
        if (b->estado != 0) {
            return b->estado;
        }
        if (b->extra._1D != 0) {
            return b->extra._1D;
        }
        D_8007CBEC = e->numero;
        o->x += (e->distancia * rsin(e->rumbo)) >> 12;
        o->z += (e->distancia * rcos(e->rumbo)) >> 12;
        D_8007CB00 = p_sabrina->x;
        D_8007CB04 = p_sabrina->y;
        D_8007CB08 = p_sabrina->z;
        o->x += (-e->distancia * rsin(e->rumbo)) >> 12;
        o->z += (-e->distancia * rcos(e->rumbo)) >> 12;
        D_8007CB0C = p_sabrina->rot[1];
        e->otro->estado = 1;
        *(Objeto **)&b->extra = o;
        e->pasos = 50;
        o->estado = 2;
        p[0] = o->x;
        p[1] = o->y;
        p[2] = o->z;
        v[0] = e->frente[0];
        v[1] = e->frente[1];
        v[2] = e->frente[2];
        v[0] = (((v[0] >> 4) * 0x480) >> 8) << 8;
        v[1] = D_8007CB04 - 0x10000;
        v[2] = (((v[2] >> 4) * 0x480) >> 8) << 8;
        v[0] = p[0] + v[0];
        v[2] = p[2] + v[2];
        func_80034FD0(v, p);
        D_8007CB00 = v[0];
        D_8007CB04 = func_800223E8(v);
        D_8007CB08 = v[2];
        return v[2];
    case 2:
        D_8007CBA8 = 1;
        if (D_8007CBA4 != 0) {
            D_8007CBA4 = 0;
            func_8003DDA0(0x15, 0);
            func_8003DD44((D_8007C8C6 * 15) & 0xFF);
        } else {
            func_8003DEE8();
            func_8003DD44((D_8007C8C6 * 15) & 0xFF);
        }
        o->estado = 3;
        return 3;
    case 3:
        func_80034F84(o, e->otro);
        r = func_8003E060();
        if (r < 0x15 || r >= 0x45) {
            r = -1;
        }
        if (!(D_8007CA50 & 0x40) && r != -1) {
            return r;
        }
        e->otro->estado = 0;
        o->estado = 4;
        return func_80035098();
    case 4:
        func_8003DDFC();
        func_80034F84(o, e->otro);
        o->estado = 5;
        p_sabrina->estado = 0;
        r = D_8007CBA4;
        if (r != 0) {
            D_8007CBA4 = 0;
        }
        return r;
    case 5:
        r = func_80034F84(o, e->otro);
        D_8007CBA8 = 0;
        return r;
    default:
        r = o->estado;
        o->estado = 0;
        return r;
    }
}
