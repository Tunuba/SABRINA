#include "juego.h"

/* Funciones del tramo que sigue a WobjCode (por el orden del enlazador, probablemente membank: la tarjeta
 * de memoria). Hay una lista de pasos que se corren de a uno y ranuras de 0xF0 bytes con banderas de lo que
 * paso en este paso y en los anteriores. */

typedef struct Ranura Ranura;
struct Ranura {
    u8 _00[0x0C];
    Ranura *primera;                 /* 0x0C, la primera de las 4 ranuras */
    Ranura *_10;
    u8 _14[0x1C];
    u8 *_30;                         /* 0x30, si el byte al que apunta no es 0 hay algo pendiente */
    u8 _34[3];
    u8 ahora;                        /* 0x37, lo de este paso */
    u8 antes;                        /* 0x38, lo del paso anterior */
    u8 antes2;                       /* 0x39, lo de hace dos pasos */
    u8 _3A[0x0F];
    u8 estado;                       /* 0x49 */
    u8 _4A[0xA6];
};
EN(Ranura, primera, 0x0C);
EN(Ranura, _10, 0x10);
EN(Ranura, _30, 0x30);
EN(Ranura, ahora, 0x37);
EN(Ranura, estado, 0x49);
typedef char tam_Ranura[sizeof(Ranura) == 0xF0 ? 1 : -1];

typedef struct {
    u8 _00[0x3C];
    u8 *_3C;
} Tarea;

typedef s32 (*FuncPaso)(Tarea *);

extern s32 D_8006CFC8;               /* paso que toca */
extern FuncPaso D_8006CFF4[];        /* los pasos */
extern void (*D_8006CF84)(s32);      /* se le avisa del error */
extern Ranura *(*D_8006CF98)(void);  /* da la ranura actual */

void func_8002908C(s32 n);
s32 func_800266B4(void);

/* Corre el paso que toca y avanza. Si el paso devuelve < 0 se avisa con ese valor. Si no, salvo en el
 * paso 0 (o en el 3 cuando el byte de +0x3C es 0x80), se llama func_8002908C(60) y, si func_800266B4 da
 * 0, se avisa -3. Desde el paso 5 se vuelve uno atras (el ultimo se repite). */
void func_80025BA0(Tarea *t) {
    s32 r;
    s32 k = D_8006CFC8;

    D_8006CFC8 = k + 1;
    r = D_8006CFF4[k](t);
    if (r < 0) {
        D_8006CF84(r);
        return;
    }
    if (D_8006CFC8 != 0) {
        if (D_8006CFC8 != 3 || *t->_3C != 0x80) {
            func_8002908C(0x3C);
            if (func_800266B4() == 0) {
                D_8006CF84(-3);
            }
        }
    }
    if (D_8006CFC8 >= 5) {
        D_8006CFC8 = D_8006CFC8 - 1;
    }
}

/* Estado de la ranura actual. Si tiene algo (banderas de este paso o del anterior, las de hace dos pasos
 * cuando no es la suya propia, o algo pendiente en +0x30), 2 y 3 se ven como 1 y 6 como 4. */
u8 func_80027A04(void) {
    Ranura *r = D_8006CF98();

    if (r->ahora != 0 || r->antes != 0 || (r != r->_10 && r->antes2 != 0) || *r->_30 != 0) {
        switch (r->estado) {
        case 2:
        case 3:
            return 1;
        case 6:
            return 4;
        }
    }
    return r->estado;
}

/* Pasa las banderas un paso atras: en la ranura, las de este paso a las del anterior; en las 4 ranuras de
 * la lista, las de este paso a las del anterior y esas a las de hace dos. Devuelve siempre 0 (en el juego
 * v0 queda en 0 al salir del lazo; solo se la llama por puntero y no se sabe si alguien lo lee). */
s32 func_80027F08(Ranura *r) {
    Ranura *e;
    s32 i;

    r->antes = r->ahora;
    r->ahora = 0;
    e = r->primera;
    for (i = 0; i < 4; i++, e++) {
        u8 a = e->antes;
        u8 b = e->ahora;
        e->ahora = 0;
        e->antes2 = a;
        e->antes = b;
    }
    return 0;
}
