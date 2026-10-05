#include "juego.h"

/* BasicTools.c: cargar un archivo entero del CD a un bloque nuevo. */

typedef struct {
    u8 pos[4];                          /* 0x00, CdlLOC */
    u32 tam;                            /* 0x04 */
    char nombre[16];                    /* 0x08 */
} CdArchivoG14;

extern char D_8007C774[];               /* "\%s;1" */
extern char D_800653F8[];               /* "BasicTools.c" */

extern void *memset(void *p, s32 c, u32 n);
extern s32 sprintf(char *d, const char *f, ...);
extern void func_80017D3C(char *nombre);
extern s32 func_8002BE88(CdArchivoG14 *a, char *nombre);   /* CdSearchFile */
extern s32 CdPosToInt(void *pos);
extern void func_80029F18(s32 sector, u8 *pos);             /* CdIntToPos */
extern s32 func_80029D28(s32 orden, u8 *param, u8 *resultado);  /* CdControl */
extern s32 CdRead(s32 sectores, void *destino, s32 modo);
extern s32 CdReadSync(s32 modo, u8 *resultado);
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void Liberar(void *p);

/* Lugar del marco de la original: el cuerpo corre con el sp de la original (ver el stub de abajo), asi que
 * el archivo, la ruta y pos se toman de sp cada vez, como la original, y no se guardan en registros s. */
#define EN_PILA(t, off) ({ t _p; __asm__ volatile("addiu %0, $sp, " #off : "=r"(_p)); _p; })
#define A (*EN_PILA(CdArchivoG14 *, 0xAC))
#define RUTA EN_PILA(char *, 0x2C)
#define POS EN_PILA(u8 *, 0xC4)

/* Busca el archivo (10 intentos), reserva su tamano, se pone en su primer sector (CdlSetloc, 10 intentos)
 * y lo lee (10 intentos). Devuelve el bloque, o 0 si fallo (lo libera). Lee un sector menos que los que
 * ocupa el archivo, como el original.
 * i y listo van en s0 y s1, como en la original: con un nombre largo CdSearchFile desborda su pila y al volver
 * deja basura en los registros s del que llama; la original sigue con esa basura en i y listo. */
__attribute__((noinline, used)) static void *cargar_entero(char *nombre) {
    register s32 i asm("$16");
    register s32 listo asm("$17");
    void *datos;
    s32 primero;
    s32 ultimo;

    i = 0;
    listo = 0;
    __asm__ volatile("" : "+r"(i), "+r"(listo));
    memset(&A, 0, 0x18);
    func_80017D3C(nombre);
    sprintf(RUTA, D_8007C774, nombre);
    do {
        func_8002BE88(&A, RUTA);
        __asm__ volatile("" : "+r"(i), "+r"(listo));
        i = (s8) (i + 1);
    } while (A.tam == 0 && i < 10);
    primero = CdPosToInt(A.pos);
    ultimo = primero + ((A.tam + 0x7FF) >> 11) - 1;
    datos = Reservar(A.tam, D_800653F8, 0x6F);
    i = 0;
    if ((u32) ultimo < (u32) primero) {
        Liberar(datos);
        return 0;
    }
    func_80029F18(primero, POS);
    do {
        if (func_80029D28(0x15, POS, 0) != 0) {
            listo = 1;
        }
        __asm__ volatile("" : "+r"(i), "+r"(listo));
        i = (s8) (i + 1);
    } while (listo == 0 && i < 10);
    if (listo == 0) {
        Liberar(datos);
        return 0;
    }
    i = 0;
    listo = 0;
    do {
        if (CdRead(ultimo - primero, datos, 0x80) != 0) {
            listo = 1;
        }
        __asm__ volatile("" : "+r"(i), "+r"(listo));
        i = (s8) (i + 1);
    } while (listo == 0 && i < 10);
    if (listo == 0) {
        Liberar(datos);
        return 0;
    }
    while (CdReadSync(1, 0) > 0) {
    }
    return datos;
}
#undef A
#undef RUTA
#undef POS

/* Como en func_800189A4: el cuarto byte de pos es lo que habia en la pila (sp+0xC7 de un marco de 0xC8), y
 * el archivo y la ruta van en sp+0xAC y sp+0x2C. Ademas CdSearchFile lee basura de su propia pila, asi que
 * el cuerpo tiene que quedar con el sp del original: este marco es de 0xA0 y el del cuerpo de 0x28 (con los
 * registros guardados donde el original). ra va en sp+0, que el original no usa; nombre sigue en a0. */
__attribute__((naked))
void *func_80017D80(char *nombre) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0xA0\n"
            "\tsw $31, 0x0($sp)\n"
            "\tjal cargar_entero\n"
            "\tnop\n"
            "\tlw $31, 0x0($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0xA0\n"
            ".set reorder");
}

extern char D_80065468[];               /* el nombre del archivo fuente, para Afirmar */
extern void Afirmar(s32 cond, char *archivo, s32 linea);

typedef struct {
    u8 *buffer;                         /* 0x00 */
    u8 *cursor;                         /* 0x04 */
    u8 _08[0x90];
    u32 sector;                         /* 0x98 el siguiente sector a leer */
    u32 ultimo;                         /* 0x9C */
} ArchivoCdG14;

/* Llena el buffer del archivo: se pone en su sector (10 intentos) y lee 0x19 sectores (10 intentos); avanza
 * el sector y vuelve el cursor al principio. Devuelve 0, o 1 si fallo. */
__attribute__((noinline, used)) static s32 llenar_buffer(ArchivoCdG14 *a, u8 *pos) {
    s32 listo;
    u8 i;

    i = 0;
    listo = 0;
    if (a->ultimo < a->sector) {
        Afirmar(0, D_80065468, 0xAA);
    }
    func_80029F18(a->sector, pos);
    do {
        if (func_80029D28(0x15, pos, 0) != 0) {
            listo = 1;
        }
        i++;
    } while (listo == 0 && i < 10);
    if (listo == 0) {
        return 1;
    }
    Afirmar(1, D_80065468, 0xBA);
    Afirmar(1, D_80065468, 0xBC);
    i = 0;
    listo = 0;
    do {
        if (CdRead(0x19, a->buffer, 0x80) != 0) {
            listo = 1;
        }
        i++;
    } while (listo == 0 && i < 10);
    if (listo == 0) {
        return 1;
    }
    a->sector += 0x19;
    a->cursor = a->buffer;
    while (CdReadSync(1, 0) > 0) {
    }
    return 0;
}

/* CdIntToPos llena 3 bytes de pos y el cuarto queda con lo que habia en la pila (sp+0x2F de un marco de
 * 0x30); func_80029D28 lo copia igual. GCC pone ahi otra cosa, asi que el marco va a mano. */
__attribute__((naked))
s32 func_800189A4(ArchivoCdG14 *a) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x30\n"
            "\tsw $31, 0x20($sp)\n"
            "\tjal llenar_buffer\n"
            "\taddiu $5, $sp, 0x2C\n"
            "\tlw $31, 0x20($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x30\n"
            ".set reorder");
}
