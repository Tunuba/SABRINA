/* Ajustes a m2c_macros.h: MULT_HI y MULTU_HI valen 0 alli y el compilador los usa para dividir entre
 * constantes (la parte alta de una multiplicacion de 64 bits). Aqui hacen la cuenta de verdad. */
#ifndef M2C_AJUSTES_H
#define M2C_AJUSTES_H
#undef MULT_HI
#undef MULTU_HI
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
