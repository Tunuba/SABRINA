#include "objeto.h"

/* Del final de WobjCode: dibujo del marcador segun el nivel, el modelo de un objeto y a quien avisa. */

typedef void (*FuncNivel)(void);

extern s8 nivel_actual;
extern FuncNivel jtbl_8006CF00[15];  /* 0 (menu): caseD_0; 1-14: caseD_1 */
extern void *modelos_cargados[];     /* desde el indice 1 */
extern s32 D_8007C9F0;
extern s8 D_8008AF88[0x50];          /* que ranuras de objetos del mundo estan en uso */
extern u8 D_8008AFD8[0x50][0x120];   /* los objetos del mundo, de 0x120 bytes */

void func_800206E8(void);
s32 func_8001E230(void *modelo);
void *func_8001E06C(void *modelo, s32 b);
s32 func_80039BC8(Forma *a, Forma *b);
s32 func_8001C33C(s32 *a, s32 *b);   /* producto escalar de dos vectores, en 24.8 */

/* Salta por la tabla del nivel: en el menu (nivel 0) una cosa y en los niveles otra. No mira el rango,
 * igual que el juego. */
void func_80024300(void) {
    jtbl_8006CF00[nivel_actual]();
}

/* Cambia el modelo del objeto: suelta el que tenga y, si n >= 0, le pone una copia de modelos_cargados[n]. */
s32 func_800249CC(Objeto *o, s32 n) {
    s32 v = (s32)o->modelo;    /* lo que queda en v0 */

    if (o->modelo != NULL) {
        func_800206E8();
        v = func_8001E230(o->modelo);
        o->modelo = NULL;
    }
    if (n >= 0) {
        o->modelo = func_8001E06C(modelos_cargados[n], D_8007C9F0);
        v = (s32)o->modelo;
    }
    return v;
}

/* Busca el objeto del mundo mas cercano cuya forma toca la del objeto y se lo pasa a su funcion de aviso
 * (+0x08). Sin funcion de aviso no hace nada. La distancia es la del centro, al cuadrado y en 24.8. */
void func_80024DFC(Objeto *o) {
    FuncObjeto2 aviso = o->aviso;
    Objeto *mejor = NULL;
    s32 hay = 0;
    s32 dist_mejor;
    s32 i;

    if (aviso == NULL) {
        return;
    }
    for (i = 0; i < 0x50; i++) {
        Objeto *p = (Objeto *)D_8008AFD8[i];
        if (D_8008AF88[i] != 0 && p != o && func_80039BC8(&o->forma, &p->forma) == 1) {
            s32 d[3];
            s32 dist;
            d[0] = (p->x - o->x) >> 8;
            d[1] = (p->y - o->y) >> 8;
            d[2] = (p->z - o->z) >> 8;
            dist = func_8001C33C(d, d);
            if (!hay) {
                dist_mejor = dist;
                mejor = p;
                hay = 1;
            } else if (dist < dist_mejor) {
                mejor = p;
                dist_mejor = dist;
            }
        }
    }
    if (mejor != NULL) {
        aviso(o, mejor);
    }
}

/* El objeto del mundo en uso mas cercano a pos (x, y, z en 24.8), sin contar a fuera. Si tipo es menor
 * que 0x38 solo cuentan los de ese tipo; si no, todos. NULL si no hay ninguno. */
Objeto *func_8002506C(s32 *pos, u32 tipo, Objeto *fuera) {
    s32 menor = 0x0FFFFFFF;
    s32 x = pos[0] >> 8, y = pos[1] >> 8, z = pos[2] >> 8;
    Objeto *cerca = NULL;
    Objeto *p = (Objeto *)D_8008AFD8;
    s32 v[3];
    s32 d, i;

    for (i = 0; i < 0x50; i++, p = (Objeto *)((u8 *)p + 0x120)) {
        if (D_8008AF88[i] == 0 || p == fuera) {
            continue;
        }
        if (tipo < 0x38 && p->tipo != tipo) {
            continue;
        }
        v[0] = (p->x >> 8) - x;
        v[1] = (p->y >> 8) - y;
        v[2] = (p->z >> 8) - z;
        d = func_8001C33C(v, v);
        if (d < menor) {
            menor = d;
            cerca = p;
        }
    }
    return cerca;
}
