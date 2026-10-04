#include "juego.h"

/* Parche de la BIOS (libapi): si el codigo de la tabla C0 de la BIOS tiene las 6 instrucciones viejas,
 * las cambia por las 6 nuevas. Las dos versiones estan guardadas una detras de la otra en func_80017B8C. */

extern s32 D_80084CD0;               /* donde guarda ra mientras trabaja */
extern s32 func_80017B8C[];          /* 6 palabras viejas y 6 nuevas (no es codigo que se llame) */
extern void func_800143E4(void);     /* EnterCriticalSection */
extern void func_800143F4(void);     /* ExitCriticalSection */
extern void FlushCache(void);

/* GetC0Table: la funcion 0x56 de la tabla B0 de la BIOS. */
static s32 *tabla_c0(void) {
    register s32 n asm("$9") = 0x56;
    register s32 *r asm("$2");

    __asm__ volatile("jalr %2\n\tnop" : "=r"(r) : "r"(n), "r"(0xB0)
                     : "$1", "$3", "$4", "$5", "$6", "$7", "$8", "$10", "$11", "$12", "$13", "$14", "$15",
                       "$24", "$25", "$31", "memory");
    return r;
}

void func_80017BC0(void) {
    s32 *codigo;
    s32 i;

    D_80084CD0 = (s32) __builtin_return_address(0);
    func_800143E4();
    codigo = (s32 *) (tabla_c0()[6] + 0x28);
    for (i = 0; i < 6; i++) {
        if (func_80017B8C[i] != codigo[i]) {
            break;
        }
    }
    if (i == 6) {
        for (i = 0; i < 6; i++) {
            codigo[i] = func_80017B8C[6 + i];
        }
    }
    FlushCache();
    func_800143F4();
}
