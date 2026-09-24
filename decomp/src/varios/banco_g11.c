#include "banco.h"

/* Mas piezas del banco de memoria (membank.cpp): el resumen de lo reservado, la reserva que no puede
 * fallar y el corte de un bloque libre demasiado grande. */

/* Afirmar(cond, archivo, linea): si cond es 0 avisa del fallo. */
extern s32 Afirmar(s32 cond, const char *archivo, s32 linea);
extern s32 printf(const char *fmt, ...);
extern char D_800758EC[];            /* "membank.cpp" */
extern char D_800758AC[];            /* "MEMORY FOOT PRINT here === %d\n" */

extern void *func_8004E32C(Banco *b, u32 tam);
extern s32 func_8004E618(Banco *b, void *p);

/* Una entrada de la tabla de reservas que se van anotando (0x10 bytes cada una). */
typedef struct {
    u32 tam;                         /* 0x00, bytes reservados */
    u8 _04[0x0C];
} Reserva;

extern Reserva D_800C98E0[];         /* tabla de reservas anotadas */
extern u32 D_8007CC20;               /* cuantas hay */

/* Palabra guardada sin alinear: asi escribe el juego la copia del tamano al final del bloque. */
typedef struct {
    s32 v;
} __attribute__((packed)) PalabraSueltaG11;

/* Escribe la copia del tamano al final del bloque (la cabecera lleva el bit de ocupado: por eso el -5). */
#define PONER_PIE(bl) (((PalabraSueltaG11 *)((u8 *)(bl) + (bl)->cab - 5))->v = (bl)->cab)

/* Suma lo reservado en la tabla y lo imprime ("MEMORY FOOT PRINT"). Separa las reservas grandes (desde
 * 0x400 bytes; el juego anota su indice en una lista de la pila que nadie lee, aqui no se guarda) de las chicas. printf recibe tambien
 * las dos cuentas en a2 y a3, aunque el formato solo lleva el total. */
void func_8004E194(void) {
    u32 total = 0;
    u32 suma_grandes = 0;
    u32 suma_chicas = 0;
    s32 n_grandes = 0;
    s32 n_chicas = 0;
    u32 i;
    u32 tam;

    for (i = 0; i < D_8007CC20; i++) {
        tam = D_800C98E0[i].tam;
        total += tam;
        if (tam >= 0x400) {
            suma_grandes += tam;
            n_grandes++;
        } else {
            suma_chicas += tam;
            n_chicas++;
        }
    }
    (void)suma_grandes;
    (void)suma_chicas;
    printf(D_800758AC, total, n_grandes, n_chicas);
}

/* Reserva tam bytes en el banco; si no hay lugar avisa (membank.cpp, linea 0x40). Devuelve el bloque. */
void *func_8004E2E4(Banco *b, u32 tam) {
    void *p = func_8004E32C(b, tam);

    if (p == NULL) {
        Afirmar(0, D_800758EC, 0x40);
    }
    return p;
}

/* Si al bloque le sobran 0x10 bytes o mas despues de quitarle tam, corta el resto como bloque nuevo (con
 * su tamano al principio y al final) y lo libera; el bloque queda con tam, marcado ocupado. */
void func_8004E7FC(Banco *b, Bloque *bl, u32 tam) {
    u32 resto = bl->cab - tam;
    Bloque *nuevo;

    if (resto >= 0x10) {
        nuevo = (Bloque *)((u8 *)bl + tam);
        nuevo->cab = resto;
        PONER_PIE(nuevo);
        bl->cab = tam + 1;
        PONER_PIE(bl);
        func_8004E618(b, (u8 *)nuevo + 4);
    }
}
