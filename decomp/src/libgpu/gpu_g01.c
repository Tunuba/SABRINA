#include "gpu_g00.h"

/* Mas funciones de libgpu (PsyQ): PutDrawEnv y TermPrim. */

extern char D_80060CAC[];  /* "PutDrawEnv(%08x)...\n" */

void func_800113DC(u32 *prim, u8 *env);  /* SetDrawEnv: arma el primitivo de un DRAWENV */
void *memcpy(void *destino, const void *origen, u32 n);

/* PutDrawEnv: arma el primitivo del entorno de dibujo (DRAWENV, 0x5C bytes; el primitivo va en +0x1C),
 * le pone el fin de lista, lo manda a la cola del GPU como tabla de orden y guarda una copia del entorno
 * en el estado de libgpu (0xE bytes despues de D_8006379A). Devuelve el mismo entorno. */
u8 *func_8001315C(u8 *env) {
    u32 *prim;

    if (D_8006379A.depuracion >= 2) {
        D_80063794(D_80060CAC, env);
    }
    prim = (u32 *)(env + 0x1C);
    func_800113DC(prim, env);
    *prim |= 0xFFFFFF;
    D_800636C8->encolar(D_800636C8->dibujarOT, prim, 0x40, 0);
    memcpy((u8 *)&D_8006379A + 0xE, env, 0x5C);
    return env;
}

/* TermPrim: marca el primitivo como el ultimo de la lista (direccion del siguiente = 0xFFFFFF). */
void func_800140BC(u32 *prim) {
    *prim |= 0xFFFFFF;
}
