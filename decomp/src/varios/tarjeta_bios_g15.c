#include "juego.h"

/* Parches de libcard a la BIOS: copian unas instrucciones suyas (guardadas en func_80052184 y D_80052424,
 * no son funciones que se llamen) dentro del codigo de la BIOS. Guardan ra en memoria mientras trabajan,
 * como el original (es la direccion del que llama: la misma en C). */

extern s32 D_800D53B0;               /* donde guarda ra mientras trabaja */
extern s32 D_800D53C0;
extern s32 func_80052184[];          /* 5 instrucciones y despues otras 5 */
extern s32 D_80052424[];             /* 3 instrucciones */
extern s32 D_80052430[];
extern s32 *func_800143E4(void);     /* EnterCriticalSection */
extern void func_800143F4(void);     /* ExitCriticalSection */
extern void FlushCache(void);

/* Una funcion de la tabla B0 de la BIOS que devuelve una tabla: 0x56 GetC0Table, 0x57 GetB0Table. */
#define TABLA_BIOS(f) ({ \
    register s32 _n asm("$9") = (f); \
    register s32 _b0 asm("$10") = 0xB0; \
    register s32 *_r asm("$2"); \
    __asm__ volatile("jalr %2\n\tnop" : "=r"(_r) : "r"(_n), "r"(_b0) \
                     : "$1", "$3", "$4", "$5", "$6", "$7", "$8", "$11", "$12", "$13", "$14", "$15", \
                       "$24", "$25", "$31", "memory"); \
    _r; })

/* Busca en el manejador de excepciones de la BIOS (entrada 6 de la tabla C0) la direccion que arma con
 * lui/ori en +0x70 y +0x74, copia en esa direccion + 0x28 las 5 primeras instrucciones de func_80052184 y
 * deja el final de lo copiado en 0xDFFC. */
void func_800521AC(void) {
    s32 *codigo;
    s32 *d;
    s32 *s;

    D_800D53B0 = (s32) __builtin_return_address(0);
    func_800143E4();
    codigo = (s32 *) TABLA_BIOS(0x56)[6];
    d = (s32 *) ((((u32) codigo[0x70 / 4] & 0xFFFF) << 16) + ((u32) codigo[0x74 / 4] & 0xFFFF) + 0x28);
    for (s = func_80052184; s != func_80052184 + 5; s++) {
        *d++ = *s;
    }
    *(s32 **) 0xDFFC = d;
    FlushCache();
}

/* Copia las 5 instrucciones siguientes de func_80052184 en +0x9C8 de la funcion 0x5B de la tabla B0. */
void func_80052240(void) {
    s32 *d;
    s32 *s;

    D_800D53B0 = (s32) __builtin_return_address(0);
    func_800143E4();
    d = (s32 *) TABLA_BIOS(0x57)[0x5B];
    for (s = func_80052184 + 5; s != func_80052184 + 10; s++) {
        d[0x9C8 / 4] = *s;
        d++;
    }
    FlushCache();
}

/* Copia las 3 instrucciones de D_80052424 en +0x70 del manejador de excepciones de la BIOS. */
void func_800523B4(void) {
    s32 *d;
    s32 *s;

    D_800D53C0 = (s32) __builtin_return_address(0);
    func_800143E4();
    d = (s32 *) TABLA_BIOS(0x56)[6];
    for (s = D_80052424; s != D_80052430; s++) {
        d[0x70 / 4] = *s;
        d++;
    }
    FlushCache();
    func_800143F4();
}
