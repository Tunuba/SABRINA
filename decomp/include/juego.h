/* Tipos y declaraciones comunes para la descompilacion de Sabrina the Teenage Witch: A Twitch in Time!
 * (SLUS-01208). Las direcciones de cada simbolo estan en symbol_addrs.txt y en el ELF de build/. */
#ifndef JUEGO_H
#define JUEGO_H

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

/* Comprobacion en compilacion de que un campo cae donde debe. Con SIN_COMPROBACIONES no se pone: es para
 * darle estos tipos a m2c, que no entiende __builtin_offsetof. */
#ifdef SIN_COMPROBACIONES
#define EN(tipo, campo, desp)
#else
#define EN(tipo, campo, desp) typedef char en_##tipo##_##campo[(__builtin_offsetof(tipo, campo) == (desp)) ? 1 : -1]
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif


#ifndef SIN_COMPROBACIONES   /* m2c no lee asm */
/* add/addi/sub de MIPS que el original usa a mano: saltan a la excepcion si se desbordan, y GCC solo
   emite addu/subu. Para que el C haga lo mismo con cualquier valor. */
static inline s32 SUMA_TRAMPA(s32 a, s32 b) {
    s32 r;
    __asm__ volatile("add %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    return r;
}
static inline s32 RESTA_TRAMPA(s32 a, s32 b) {
    s32 r;
    __asm__ volatile("sub %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    return r;
}
#endif
#endif
