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

#ifndef NULL
#define NULL ((void *)0)
#endif

#endif
