#include "juego.h"

/* File.cpp: buscar un archivo en el CD y leer de su buffer de sectores. */

/* CdlFILE de Sony: posicion (CdlLOC), tamano y nombre. */
typedef struct {
    u8 pos[4];                          /* 0x00, minuto, segundo, sector, modo */
    u32 tam;                            /* 0x04 */
    char nombre[16];                    /* 0x08 */
} CdArchivo;

/* Lo que se sabe del archivo abierto. */
typedef struct {
    u8 *buffer;                         /* 0x00, inicio del buffer de lectura (0xC800 bytes) */
    u8 *cursor;                         /* 0x04, lo que falta entregar del buffer */
    u8 *fin;                            /* 0x08, fin de lo leido en el buffer */
    u8 _0C[4];
    u32 tam;                            /* 0x10, tamano del archivo en el CD */
    u8 _14[0x84];
    s32 sector;                         /* 0x98, primer sector del archivo */
    s32 ultimo;                         /* 0x9C, ultimo sector del archivo */
} ArchivoCd;
EN(ArchivoCd, tam, 0x10);
EN(ArchivoCd, sector, 0x98);
EN(ArchivoCd, ultimo, 0x9C);

extern void *memset(void *p, s32 c, u32 n);
extern void *memcpy(void *d, const void *s, u32 n);
extern s32 sprintf(char *s, const char *formato, ...);
extern CdArchivo *func_8002BE88(CdArchivo *f, char *nombre);  /* CdSearchFile */
extern s32 CdPosToInt(void *pos);
extern void func_80017D3C(char *nombre);
extern s32 Afirmar(s32 cond, char *archivo, s32 linea);
extern s32 func_800189A4(ArchivoCd *a);  /* llena el buffer con los sectores siguientes */

extern char D_8007C790[];               /* "\\%s;1" */
extern char D_80065468[];               /* "File.cpp" */

/* Busca nombre en el CD (hasta 10 intentos) y deja en el archivo su primer y ultimo sector y su tamano.
 * Devuelve 1 si lo encontro. */
s32 func_800188C4(ArchivoCd *a, char *nombre) {
    CdArchivo f;
    char ruta[0x80];
    u8 intentos = 0;
    s32 hallado = 0;

    memset(&f, 0, sizeof(f));
    func_80017D3C(nombre);
    sprintf(ruta, D_8007C790, nombre);
    do {
        func_8002BE88(&f, ruta);
        if (f.tam != 0) {
            hallado = 1;
        }
        intentos++;
    } while (f.tam == 0 && intentos < 10);
    a->sector = CdPosToInt(&f);
    a->ultimo = a->sector + ((f.tam + 0x7FF) >> 11) - 1;
    a->tam = f.tam;
    return hallado;
}

/* Copia tam bytes del archivo a destino (que primero se pone en cero). Si el buffer no alcanza, copia lo
 * que queda, rellena el buffer y sigue de a 0xC800 bytes. */
void ArchivoLeer(ArchivoCd *a, u8 *destino, s32 tam) {
    u32 quedan = a->fin - a->cursor;

    Afirmar((s32)destino, D_80065468, 0xED);
    memset(destino, 0, tam);
    if (quedan < (u32)tam) {
        memcpy(destino, a->cursor, quedan);
        destino += quedan;
        tam -= quedan;
        func_800189A4(a);
        while (tam >= 0xC801) {
            memcpy(destino, a->buffer, 0xC800);
            destino += 0xC800;
            tam -= 0xC800;
            func_800189A4(a);
        }
        a->cursor = a->buffer;
    }
    if (tam > 0) {
        memcpy(destino, a->cursor, tam);
        a->cursor += tam;
    }
}
