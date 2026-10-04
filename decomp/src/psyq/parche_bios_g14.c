#include "juego.h"

/* Parche de la BIOS (libapi): si el codigo de la tabla C0 de la BIOS tiene las 6 instrucciones viejas,
 * las cambia por las 6 nuevas. Las dos versiones estan guardadas una detras de la otra en func_80017B8C. */

extern s32 D_80084CD0;               /* donde guarda ra mientras trabaja */
extern s32 func_80017B8C[];          /* 6 palabras viejas y 6 nuevas (no es codigo que se llame) */
extern s32 *func_800143E4(void);     /* EnterCriticalSection */
extern void func_800143F4(void);     /* ExitCriticalSection */
extern void FlushCache(void);

/* GetC0Table: la funcion 0x56 de la tabla B0 de la BIOS. */
static s32 *tabla_c0(s32 *antes) {
    register s32 n asm("$9") = 0x56;
    register s32 b0 asm("$10") = 0xB0;
    register s32 *r asm("$2") = antes;

    /* como el original: v0 llega con lo que devolvio EnterCriticalSection (si la BIOS no lo toca, queda) */
    __asm__ volatile("jalr %3\n\tnop" : "=r"(r) : "0"(r), "r"(n), "r"(b0)
                     : "$1", "$3", "$4", "$5", "$6", "$7", "$8", "$11", "$12", "$13", "$14", "$15",
                       "$24", "$25", "$31", "memory");
    return r;
}

void func_80017BC0(void) {
    s32 *codigo;
    s32 i;

    D_80084CD0 = (s32) __builtin_return_address(0);
    codigo = func_800143E4();
    codigo = (s32 *) (tabla_c0(codigo)[6] + 0x28);
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

extern s32 D_800653C0;               /* donde guarda ra mientras trabaja */

/* InitGeom (libgte): parchea la BIOS, prende el coprocesador geometrico (bit 30 del registro de estado) y
 * pone sus valores de fabrica: ZSF3 0x155, ZSF4 0x100, H 1000, DQA -0x1062, DQB 0x1400000 y OFX/OFY 0. */
void func_800177B4(void) {
    u32 sr;

    D_800653C0 = (s32) __builtin_return_address(0);
    func_80017BC0();
    __asm__ volatile("mfc0 %0, $12" : "=r"(sr));
    sr |= 0x40000000;
    __asm__ volatile("mtc0 %0, $12\n\tnop" : : "r"(sr));
    __asm__ volatile("ctc2 %0, $29\n\tnop" : : "r"(0x155));
    __asm__ volatile("ctc2 %0, $30\n\tnop" : : "r"(0x100));
    __asm__ volatile("ctc2 %0, $26\n\tnop" : : "r"(0x3E8));
    __asm__ volatile("ctc2 %0, $27\n\tnop" : : "r"(-0x1062));
    __asm__ volatile("ctc2 %0, $28\n\tnop" : : "r"(0x1400000));
    __asm__ volatile("ctc2 $0, $24\n\tctc2 $0, $25\n\tnop");
}
