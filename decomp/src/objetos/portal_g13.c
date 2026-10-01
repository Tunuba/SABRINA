#include "objeto.h"

/* El portal a otro nivel: gira, cae al suelo, se traga a Sabrina cuando se acerca y la lleva al nivel de
 * su registro (o, desde el nivel 13, muestra la pantalla del mundo que lleva). */

/* La parte extra del portal. */
typedef struct {
    s32 llave;                       /* 0x00, distinto de 0: hace falta juntar las piezas del nivel */
    s32 destino;                     /* 0x04, el nivel al que lleva (1, 4, 7 y 10 son mundos) */
    s32 radio;                       /* 0x08, al cuadrado, desde donde se traga a Sabrina */
    u8 _0C[4];
    s32 desp_x;                      /* 0x10, corrimiento del punto que mira al caer */
    u8 _14[4];
    s32 desp_z;                      /* 0x18 */
    s32 ya_abierto;                  /* 0x1C */
    s32 centro[3];                   /* 0x20, a donde lleva a Sabrina */
} ExtraPortal;

#define FUNC_14(o) (*(void (**)(Objeto *))((u8 *)(o) + 0x14))

extern s8 D_800C8560;                /* el ultimo mundo abierto */
extern s8 D_800C8582, D_800C8583, D_800C8584, D_800C8585;  /* piezas de los niveles 3, 6, 9 y 12 */
extern s8 D_800C8948, D_800C8A89, D_800C8D0B, D_800C8E4C, D_800C90CE, D_800C920F, D_800C9491, D_800C95D2;
extern u8 D_80078F00[], D_80078F30[], D_80078F90[], D_80078FC4[];
extern u8 D_8007902C[], D_80079060[], D_800790C4[], D_800790F0[];
extern char D_80075828[];
extern s8 nivel_actual;
extern s8 D_8007CA01;
extern Objeto *D_8007CB8C;
extern s16 D_8007CC16;
extern s8 D_8007CC18;

extern void func_80025064(Objeto *o);
extern s32 func_800223E8(s32 *p);    /* altura del suelo debajo de p */
extern s32 func_8001C33C(s32 *a, s32 *b);
extern void func_8003019C(void);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern void func_80030EC8(void);
extern void func_8003E0B4(void);
extern void func_80037268(void);
extern void func_80033AD8(Objeto *o);
extern void func_80055CAC(Objeto *o);
extern void func_80047240(void);
extern void func_80019464(s32 mundo);
extern void func_8005E290(s32 r, s32 g, s32 b, u8 *texto);
extern s32 Afirmar(s32 cond, char *archivo, s32 linea);

static s32 es_mundo(s32 n) {
    return n == 10 || n == 7 || n == 4 || n == 1;
}

/* Si estan las piezas del nivel actual (para los niveles 3, 6, 9 y 12; los demas siempre). */
static s32 piezas_listas(void) {
    switch (nivel_actual) {
    case 12:
        return D_800C8585 >= 2;
    case 9:
        return D_800C8584 >= 2;
    case 6:
        return D_800C8583 >= 2;
    case 3:
        return D_800C8582 >= 2;
    }
    return 1;
}

static void tragar(Objeto *o) {
    o->estado = 4;
    func_8003019C();
    TocarSonido(0x31, 0, 0x2A, 0x7F);
    func_80030EC8();
    func_8003E0B4();
    func_80037268();
}

static void texto(s8 encendido, u8 *t) {
    if (encendido != 0) {
        func_8005E290(0xFF, 0xFF, 0xFF, t);
    } else {
        func_8005E290(0x38, 0x38, 0x38, t);
    }
}

void func_8004D0C0(Objeto *o) {
    ExtraPortal *e = (ExtraPortal *)&o->extra;
    s32 p[3], s;

    if (es_mundo(e->destino)) {
        ((s16 *)o->datos)[13] = 2;
    }
    switch ((u16)o->estado) {
    case 0:
        o->rot[1] = o->rot[1] + 0x19;
        if (o->rot[1] >= 0x1001) {
            o->rot[1] = 0;
        }
        break;
    case 1:
        o->x += o->empuje_x;
        o->z += o->empuje_z;
        p[0] = o->x + e->desp_x;
        p[2] = o->z + e->desp_z;
        p[1] = o->y - 0x48000;
        s = func_800223E8(p);
        if (o->y + 0x6667 + 0x7FFF >= s && s != p[1]) {
            o->estado = 2;
        }
        break;
    case 2:
        p[0] = (p_sabrina->x - o->x) >> 8;
        p[1] = (p_sabrina->y - o->y) >> 8;
        p[2] = (p_sabrina->z - o->z) >> 8;
        if (func_8001C33C(p, p) >= e->radio) {
            break;
        }
        if (es_mundo(e->destino)) {
            e->centro[0] = o->x;
            e->centro[1] = o->y;
            e->centro[2] = o->z;
            e->centro[1] = e->centro[1] - 0x599A - 0x7FFF;
            tragar(o);
        }
        if (e->llave != 0 && piezas_listas()) {
            tragar(o);
        }
        break;
    case 4:
        FUNC_14(p_sabrina) = func_80025064;
        FUNC_14(D_8007CB8C) = func_80025064;
        p[0] = (p_sabrina->x - e->centro[0]) >> 4;
        p[1] = (p_sabrina->y - e->centro[1]) >> 4;
        p[2] = (p_sabrina->z - e->centro[2]) >> 4;
        p_sabrina->x -= p[0];
        p_sabrina->y -= p[1];
        p_sabrina->z -= p[2];
        p_sabrina->escala[0] -= 0x4C;
        p_sabrina->escala[1] -= 0x4C;
        p_sabrina->escala[2] -= 0x4C;
        if (p_sabrina->escala[0] < 5) {
            p_sabrina->escala[0] = 5;
            p_sabrina->escala[1] = 5;
            p_sabrina->escala[2] = 5;
            o->estado = 3;
        }
        D_8007CB8C->x = p_sabrina->x;
        D_8007CB8C->y = p_sabrina->y;
        D_8007CB8C->z = p_sabrina->z;
        D_8007CB8C->escala[0] = p_sabrina->escala[0];
        D_8007CB8C->escala[1] = p_sabrina->escala[1];
        D_8007CB8C->escala[2] = p_sabrina->escala[2];
        func_80033AD8(p_sabrina);
        func_80055CAC(D_8007CB8C);
        break;
    case 3:
        if (e->ya_abierto != 0) {
            if (nivel_actual != 12 && nivel_actual != 9 && nivel_actual != 3 && nivel_actual != 6) {
                break;
            }
            if (!piezas_listas()) {
                break;
            }
        }
        switch (nivel_actual) {
        case 13:
            switch (e->destino) {
            case 1:
                func_80019464(0);
                texto(D_800C8948, D_80078F00);
                texto(D_800C8A89, D_80078F30);
                break;
            case 4:
                func_80019464(1);
                texto(D_800C8D0B, D_80078F90);
                texto(D_800C8E4C, D_80078FC4);
                break;
            case 7:
                func_80019464(2);
                texto(D_800C90CE, D_8007902C);
                texto(D_800C920F, D_80079060);
                break;
            case 10:
                func_80019464(3);
                texto(D_800C9491, D_800790C4);
                texto(D_800C95D2, D_800790F0);
                break;
            default:
                Afirmar(0, D_80075828, 0x193);
                break;
            }
            return;
        case 12:
            e->destino = 13;
            if (D_800C8560 < 5) {
                D_800C8560 = 5;
            }
            break;
        case 9:
            e->destino = 13;
            if (D_800C8560 < 4) {
                D_800C8560 = 4;
            }
            break;
        case 3:
            e->destino = 13;
            if (D_800C8560 < 2) {
                D_800C8560 = 2;
            }
            break;
        case 6:
            e->destino = 13;
            if (D_800C8560 < 3) {
                D_800C8560 = 3;
            }
            break;
        }
        D_8007CA01 = nivel_actual;
        D_8007CC16 = e->destino;
        nivel_actual = (s16)e->destino;
        D_8007CC18 = 1;
        func_80047240();
        break;
    }
}
