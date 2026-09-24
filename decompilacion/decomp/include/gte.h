/* El coprocesador geometrico (GTE) desde C: cada macro es la instruccion cop2 que toca.
 *
 * Los registros de control 0, 2 y 4 llevan la matriz de giro empaquetada (dos numeros de 16 bits por
 * palabra); IR1, IR2 e IR3 son los datos 9, 10 y 11, y MAC1, MAC2 y MAC3 los datos 25, 26 y 27.
 * Los verifica gte.py, que emula estas instrucciones dentro de Unicorn. */
#ifndef GTE_H
#define GTE_H

#include "juego.h"

#define gte_leer_giro(a, b, c) __asm__ volatile("cfc2 %0, $0" : "=r"(a)); \
                               __asm__ volatile("cfc2 %0, $2" : "=r"(b)); \
                               __asm__ volatile("cfc2 %0, $4" : "=r"(c))
#define gte_poner_giro(a, b, c) __asm__ volatile("ctc2 %0, $0" :: "r"(a)); \
                                __asm__ volatile("ctc2 %0, $2" :: "r"(b)); \
                                __asm__ volatile("ctc2 %0, $4" :: "r"(c))
#define gte_cargar_ir3(p) __asm__ volatile("lwc2 $11, 8(%0)" :: "r"(p) : "memory"); \
                          __asm__ volatile("lwc2 $9, 0(%0)" :: "r"(p) : "memory"); \
                          __asm__ volatile("lwc2 $10, 4(%0)" :: "r"(p) : "memory")
#define gte_guardar_mac3(p) __asm__ volatile("swc2 $25, 0(%0)" :: "r"(p) : "memory"); \
                            __asm__ volatile("swc2 $26, 4(%0)" :: "r"(p) : "memory"); \
                            __asm__ volatile("swc2 $27, 8(%0)" :: "r"(p) : "memory")
/* Producto vectorial de IR con la diagonal de la matriz de giro, con el resultado corrido 12 bits. */
#define gte_op() __asm__ volatile(".word 0x4B78000C")

/* La matriz de giro entera (controles 0 a 4) y la traslacion (5 a 7), como los guarda el juego: cinco
 * palabras con dos numeros de 16 bits cada una y tres palabras enteras. */
#define gte_poner_matriz(p) __asm__ volatile("ctc2 %0, $0" :: "r"(((s32 *)(p))[0]));                             __asm__ volatile("ctc2 %0, $1" :: "r"(((s32 *)(p))[1]));                             __asm__ volatile("ctc2 %0, $2" :: "r"(((s32 *)(p))[2]));                             __asm__ volatile("ctc2 %0, $3" :: "r"(((s32 *)(p))[3]));                             __asm__ volatile("ctc2 %0, $4" :: "r"(((s32 *)(p))[4]))
#define gte_poner_traslacion(p) __asm__ volatile("ctc2 %0, $5" :: "r"(((s32 *)(p))[0]));                                 __asm__ volatile("ctc2 %0, $6" :: "r"(((s32 *)(p))[1]));                                 __asm__ volatile("ctc2 %0, $7" :: "r"(((s32 *)(p))[2]))
/* El vector 0: x e y en una palabra (dato 0) y z en la siguiente (dato 1). */
#define gte_poner_v0_xy(w) __asm__ volatile("mtc2 %0, $0" :: "r"(w))
#define gte_cargar_v0_z(p) __asm__ volatile("lwc2 $1, 0(%0)" :: "r"(p) : "memory")
/* Multiplicar por la matriz: mvmva con matriz de giro, vector 0, sin traslacion y sin recorte. */
#define gte_mvmva_v0() __asm__ volatile(".word 0x4A480012")
/* Guardar IR1, IR2 e IR3 en tres palabras seguidas. */
#define gte_guardar_ir(p) __asm__ volatile("swc2 $9, 0(%0)" :: "r"(p) : "memory");                           __asm__ volatile("swc2 $10, 4(%0)" :: "r"(p) : "memory");                           __asm__ volatile("swc2 $11, 8(%0)" :: "r"(p) : "memory")

/* El vector 0 entero, tres enteros de 16 bits en dos palabras seguidas. */
#define gte_poner_v0(p) __asm__ volatile("lwc2 $0, 0(%0)" :: "r"(p) : "memory");                         __asm__ volatile("lwc2 $1, 4(%0)" :: "r"(p) : "memory")
/* Pasar el vector 0 a pantalla: gira, traslada y divide entre la z. */
#define gte_rtps() __asm__ volatile(".word 0x4A180001")
/* Lo mismo con los vectores 0, 1 y 2 de una vez (los tres vertices de un triangulo). */
#define gte_rtpt() __asm__ volatile(".word 0x4A280030")
/* El area con signo del triangulo que quedo en la cola de pantalla; negativa si se ve por detras. */
#define gte_nclip() __asm__ volatile(".word 0x4A000006")
/* La z que salio (dato 19) y el punto de pantalla que salio (dato 14). */
#define gte_guardar_sz3(p) __asm__ volatile("swc2 $19, 0(%0)" :: "r"(p) : "memory")
#define gte_guardar_sxy2(p) __asm__ volatile("swc2 $14, 0(%0)" :: "r"(p) : "memory")
#define gte_leer_mac0(v) __asm__ volatile("mfc2 %0, $24" : "=r"(v))

/* Los vectores 1 y 2, que solo usa rtpt. */
#define gte_poner_v1(p) __asm__ volatile("lwc2 $2, 0(%0)" :: "r"(p) : "memory");                         __asm__ volatile("lwc2 $3, 4(%0)" :: "r"(p) : "memory")
#define gte_poner_v2(p) __asm__ volatile("lwc2 $4, 0(%0)" :: "r"(p) : "memory");                         __asm__ volatile("lwc2 $5, 4(%0)" :: "r"(p) : "memory")
/* Los otros dos puntos de la cola de pantalla (datos 12 y 13). */
#define gte_guardar_sxy0(p) __asm__ volatile("swc2 $12, 0(%0)" :: "r"(p) : "memory")
#define gte_guardar_sxy1(p) __asm__ volatile("swc2 $13, 0(%0)" :: "r"(p) : "memory")
/* Las tres z de la cola, en tres palabras seguidas. */
#define gte_guardar_sz(p) __asm__ volatile("swc2 $17, 0(%0)" :: "r"(p) : "memory");                           __asm__ volatile("swc2 $18, 4(%0)" :: "r"(p) : "memory");                           __asm__ volatile("swc2 $19, 8(%0)" :: "r"(p) : "memory")
/* La cuenta grande (dato 24) y las banderas de lo que se salio de rango (control 31). */
#define gte_guardar_mac0(p) __asm__ volatile("swc2 $24, 0(%0)" :: "r"(p) : "memory")
#define gte_leer_banderas(v) __asm__ volatile("cfc2 %0, $31" : "=r"(v))

#endif
