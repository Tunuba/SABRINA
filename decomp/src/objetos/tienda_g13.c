#include "objeto.h"

/* Un objeto con el que Sabrina habla (con su musica propia): al acercarse y apretar el boton 1 se abre una
 * conversacion; si Sabrina puede pagar lo que ofrece (func_80056A08), se lo cobra al terminar. */

/* La parte extra que se usa. */
typedef struct {
    u8 _00[0x2C];
    s32 oferta;                      /* 0x2C, 1 a 4: que se compra (0 nada) */
    u8 _30[4];
    s32 espera;                      /* 0x34, pasos antes de poder volver a hablar (100 = recien cerrado) */
    s32 apagado;                     /* 0x38 */
} ExtraTienda;

extern s16 D_800C8558, D_800C855A, D_800C855C, gemas;  /* lo que Sabrina tiene para pagar */
extern s8 D_800C855F;                /* compras hechas */
extern s8 D_800C8562, D_800C8563, D_800C8564, D_800C8565;  /* lo comprado de cada mundo */
extern s32 D_800C98B0, D_800C98B4;
extern u16 D_8007C8C4, D_8007C8C6;   /* volumenes de la musica */
extern s8 D_8007CA01;                /* el nivel del que se vino */
extern s32 D_8007CA30;               /* botones apretados en este paso */
extern s32 D_8007CA50;

extern s32 func_800487B0(Objeto *o, Objeto *a, s32 paso);
extern s32 func_8002225C(Objeto *o, s32 x, s32 y, s32 z);
extern s32 func_8003E060(void);      /* la pista que suena, -1 ninguna */
extern s32 func_80056A08(Objeto *o); /* que se puede comprar aqui (0 nada) */
extern void func_8003DE68(s32 n);    /* empieza una conversacion con su musica */
extern void func_8003DD44(s32 volumen);
extern void func_8003DDA0(s32 pista, s32 a);
extern void func_80056C18(Objeto *o, s32 a);

/* Si Sabrina esta a mano, parada o caminando y sin hacer nada. */
static s32 puede_hablar(Objeto *o) {
    if (func_8002225C(o, p_sabrina->x, p_sabrina->y, p_sabrina->z) >= 0x28000) {
        return 0;
    }
    if (p_sabrina->estado != 0 && p_sabrina->estado != 1) {
        return 0;
    }
    return p_sabrina->extra._1D == 0;
}

/* Cierra la conversacion: vuelve la musica del nivel y Sabrina queda libre. */
static void cerrar(Objeto *o, ExtraTienda *e, s16 estado) {
    o->estado = estado;
    e->espera = 100;
    func_8003DDA0(3, 1);
    func_8003DD44((D_8007C8C4 * 15) & 0xFF);
    p_sabrina->estado = 0;
}

void func_80056CE8(Objeto *o) {
    u16 *t = o->animaciones;
    EstadoAnim *a = o->anim;
    ExtraTienda *e = (ExtraTienda *)&o->extra;
    s32 r, ya;

    if (D_800C98B4 != 0 || e->apagado != 0) {
        return;
    }
    func_800487B0(o, p_sabrina, 0x96);
    switch ((u16)o->estado) {
    case 0:
        if (a->animacion != t[0]) {
            a->animacion = t[0];
            a->_50 = 0;
            a->_4E = 0x800;
        }
        if (!(D_8007CA30 & 1)) {
            return;
        }
        if (func_8002225C(o, p_sabrina->x, p_sabrina->y, p_sabrina->z) >= 0x28000 || e->espera == 100) {
            return;
        }
        if (p_sabrina->estado != 0 && p_sabrina->estado != 1) {
            return;
        }
        if (p_sabrina->extra._1D != 0) {
            return;
        }
        r = func_8003E060();
        if (r == 0x52 || r == 0x51 || r == 0x50 || r == 0x4F) {
            return;
        }
        *(Objeto **)&p_sabrina->extra = o;
        e->oferta = func_80056A08(o);
        if (e->oferta != 0) {
            o->estado = 1;
            e->espera = 0x32;
            func_8003DE68(1);
            func_8003DD44((D_8007C8C6 * 15) & 0xFF);
            p_sabrina->estado = 1;
            return;
        }
        /* nada que comprar: si lo de este mundo ya se compro, no dice nada */
        switch (D_8007CA01) {
        case 1: case 2: case 3:
            ya = D_800C8563 == 2;
            break;
        case 4: case 5: case 6:
            ya = D_800C8562 == 1;
            break;
        case 7: case 8: case 9:
            ya = D_800C8565 == 4;
            break;
        case 10: case 11: case 12:
            ya = D_800C8564 == 3;
            break;
        default:
            ya = 1;
            break;
        }
        if (ya) {
            return;
        }
        e->espera = 0x32;
        o->estado = 4;
        func_8003DE68(2);
        func_8003DD44((D_8007C8C6 * 15) & 0xFF);
        p_sabrina->estado = 1;
        return;
    case 6:
        if (!puede_hablar(o)) {
            return;
        }
        p_sabrina->estado = 1;
        *(Objeto **)&p_sabrina->extra = o;
        if (D_800C98B0 == 0) {
            return;
        }
        if (D_800C98B0 == 1) {
            func_8003DE68(0);
            func_8003DD44((D_8007C8C6 * 15) & 0xFF);
            D_800C98B0 = 2;
            func_80056C18(o, 1);
        }
        if (D_800C98B0 == 2) {
            r = func_8003E060();
            if (r != 0x5A || r == -1) {
                D_800C98B0 = 0;
                func_8003DDA0(3, 1);
                func_8003DD44((D_8007C8C4 * 15) & 0xFF);
                o->estado = 0;
                p_sabrina->estado = 0;
            }
            func_80056C18(o, 0);
        }
        return;
    case 1:
        r = func_8003E060();
        if (r != 0x5D && r != 0x5C && r != 0x5B) {
            r = -1;
        }
        if (r == -1 || (D_8007CA50 & 0x40)) {
            cerrar(o, e, 3);
        }
        return;
    case 4:
        r = func_8003E060();
        if (r != 0x60 && r != 0x5F && r != 0x5E) {
            r = -1;
        }
        if (r == -1 || (D_8007CA50 & 0x40)) {
            cerrar(o, e, 0);
        }
        return;
    case 2:
        o->estado = 0;
        e->espera = 500;
        p_sabrina->estado = 0;
        return;
    case 3:
        D_800C855F++;
        switch (e->oferta) {
        case 3:
            D_800C8564 = 3;
            D_800C855C -= 100;
            break;
        case 4:
            D_800C8565 = 4;
            D_800C855A -= 100;
            break;
        case 1:
            D_800C8562 = 1;
            D_800C8558 -= 100;
            break;
        case 2:
            D_800C8563 = 2;
            gemas -= 100;
            break;
        }
        o->estado = 5;
        e->espera = 500;
        p_sabrina->estado = 0;
        return;
    case 5:
        e->espera--;
        if (e->espera < 0) {
            o->estado = 0;
        }
        return;
    }
}
