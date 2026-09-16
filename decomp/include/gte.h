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
#define gte_cargar_ir3(p) __asm__ volatile("lwc2 $11, 8(%0)" :: "r"(p)); \
                          __asm__ volatile("lwc2 $9, 0(%0)" :: "r"(p)); \
                          __asm__ volatile("lwc2 $10, 4(%0)" :: "r"(p))
#define gte_guardar_mac3(p) __asm__ volatile("swc2 $25, 0(%0)" :: "r"(p)); \
                            __asm__ volatile("swc2 $26, 4(%0)" :: "r"(p)); \
                            __asm__ volatile("swc2 $27, 8(%0)" :: "r"(p))
/* Producto vectorial de IR con la diagonal de la matriz de giro, con el resultado corrido 12 bits. */
#define gte_op() __asm__ volatile(".word 0x4B78000C")

/* La matriz de giro entera (controles 0 a 4) y la traslacion (5 a 7), como los guarda el juego: cinco
 * palabras con dos numeros de 16 bits cada una y tres palabras enteras. */
#define gte_poner_matriz(p) __asm__ volatile("ctc2 %0, $0" :: "r"(((s32 *)(p))[0]));                             __asm__ volatile("ctc2 %0, $1" :: "r"(((s32 *)(p))[1]));                             __asm__ volatile("ctc2 %0, $2" :: "r"(((s32 *)(p))[2]));                             __asm__ volatile("ctc2 %0, $3" :: "r"(((s32 *)(p))[3]));                             __asm__ volatile("ctc2 %0, $4" :: "r"(((s32 *)(p))[4]))
#define gte_poner_traslacion(p) __asm__ volatile("ctc2 %0, $5" :: "r"(((s32 *)(p))[0]));                                 __asm__ volatile("ctc2 %0, $6" :: "r"(((s32 *)(p))[1]));                                 __asm__ volatile("ctc2 %0, $7" :: "r"(((s32 *)(p))[2]))
/* El vector 0: x e y en una palabra (dato 0) y z en la siguiente (dato 1). */
#define gte_poner_v0_xy(w) __asm__ volatile("mtc2 %0, $0" :: "r"(w))
#define gte_cargar_v0_z(p) __asm__ volatile("lwc2 $1, 0(%0)" :: "r"(p))
/* Multiplicar por la matriz: mvmva con matriz de giro, vector 0, sin traslacion y sin recorte. */
#define gte_mvmva_v0() __asm__ volatile(".word 0x4A480012")
/* Guardar IR1, IR2 e IR3 en tres palabras seguidas. */
#define gte_guardar_ir(p) __asm__ volatile("swc2 $9, 0(%0)" :: "r"(p));                           __asm__ volatile("swc2 $10, 4(%0)" :: "r"(p));                           __asm__ volatile("swc2 $11, 8(%0)" :: "r"(p))

#endif
