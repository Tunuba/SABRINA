#include "juego.h"

/* Una espera activa y su puesta a cero. D_8007CC20 es cuantas vueltas da la espera y D_8007CC24 una
 * bandera que la espera baja y el reinicio sube. El reinicio tambien borra la tabla de D_800C98D4
 * (0x7D10 bytes) y el contador D_8007CC28. */

extern u32 D_8007CC20;
extern u8 D_8007CC24;
extern s32 D_8007CC28;
extern u8 D_800C98D4[];

extern void *memset(void *, s32, u32);

/* Baja la bandera y da D_8007CC20 vueltas sin hacer nada (el compilador puede quitar el lazo vacio:
 * no cambia nada que se vea). */
void func_8004E238(void) {
    u32 i;

    D_8007CC24 = 0;
    for (i = 0; i < D_8007CC20; i++) {
    }
}

/* Sube la bandera, pone la espera en cero y borra la tabla. */
void func_8004E268(void) {
    D_8007CC24 = 1;
    D_8007CC20 = 0;
    memset(D_800C98D4, 0, 0x7D10);
    D_8007CC28 = 0;
}
