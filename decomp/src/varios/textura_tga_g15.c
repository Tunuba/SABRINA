#include "juego.h"

/* Herramienta de desarrollo: carga una textura .TGA de la carpeta D_8007A1E8 y la sube a la VRAM. Las
 * marcas en el nombre: '!' seguido de una letra (A-D) el modo de mezcla, '&', '#' y 0xA3 otras banderas. */

typedef struct {
    u8 _00[8];
    s16 ancho;                          /* 0x08 */
    s16 alto;                           /* 0x0A */
    u16 tpage;                          /* 0x0C */
    u16 clut;                           /* 0x0E */
    u8 u;                               /* 0x10 */
    u8 v;                               /* 0x11 */
    u16 x;                              /* 0x12 */
    u16 y;                              /* 0x14 */
    u16 clut_x;                         /* 0x16 */
    u16 clut_y;                         /* 0x18 */
    u16 colores;                        /* 0x1A */
    u8 banderas;                        /* 0x1C */
    u8 prof;                            /* 0x1D 0: 4 bits, 1: 8 bits, 2: 16 bits */
    u8 _1E[2];
} TexTGA;

extern char D_800686C4[];               /* el nombre del archivo fuente */
extern char D_800686DC[];
extern char D_80068718[];
extern char D_8007C7C8[];               /* el formato de la ruta */
extern char D_8007A1E8[];               /* la carpeta */

extern void ArchivoIniciar(void *a);
extern void ArchivoAbrir(void *a, char *ruta, s32 modo);
extern void ArchivoLeer(void *a, void *d, s32 n);
extern void ArchivoCerrar(void *a, s32 n);
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void Liberar(void *p);
extern void *memset(void *p, s32 c, u32 n);
extern s32 sprintf(char *d, const char *f, ...);
extern s32 printf(const char *f, ...);
extern void Afirmar(s32 c, char *archivo, s32 linea);
extern char *func_80014FF0(char *s, s32 c);     /* strchr */
extern void func_80019FBC(void *a, TexTGA *t, void *d);
extern void func_8001A108(void *a, TexTGA *t, void *d);
extern void func_8001A668(void *d, s32 ancho, s32 alto, s32 n);
extern void *func_8001A754(TexTGA *t, void *d, void *paleta, s32 n);
extern void func_8001A4C0(TexTGA *t);
extern void func_8001A228(TexTGA *t, s32 n);
extern void func_8001A620(TexTGA *t, s32 n, void *d);
extern s32 LoadClut(void *c, s32 x, s32 y);
extern s32 LoadClut2(void *c, s32 x, s32 y);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);

/* Un lugar del marco del original: el cuerpo corre con el mismo sp (ver func_8001B0C8 abajo). */
#define PILA(off) ({ u8 *_p; __asm__ volatile("addiu %0, $sp, " #off : "=r"(_p)); _p; })
#define ARCHIVO PILA(0xC0)
#define RUTA ((char *) PILA(0x40))
#define CABECERA PILA(0x2C)             /* los 0x12 bytes de la cabecera del .TGA */

__attribute__((noinline, used)) static TexTGA *cargar_tga(char *nombre) {
    TexTGA *t;
    u8 *imagen;
    u16 *paleta;
    u32 modo;
    s32 n;
    u16 i;

    /* sin '!' el modo es lo que traia s4 el que llama, como en el original */
    __asm__ volatile("move %0, $20" : "=r"(modo));
    ArchivoIniciar(ARCHIVO);
    t = Reservar(0x20, D_800686C4, 0x98);
    memset(t, 0, 0x20);
    if (func_80014FF0(nombre, '!') != 0) {
        modo = (u16) (func_80014FF0(nombre, '!')[1] - 'A');
        t->banderas |= 1;
        if (modo >= 4) {
            printf(D_800686DC);
            Afirmar(0, D_800686C4, 0xA4);
        }
    }
    if (func_80014FF0(nombre, '&') != 0) {
        t->banderas |= 2;
    }
    if (func_80014FF0(nombre, -0x5D) != 0) {
        t->banderas |= 8;
    }
    if (func_80014FF0(nombre, '#') != 0) {
        t->banderas |= 4;
    }
    sprintf(RUTA, D_8007C7C8, D_8007A1E8, nombre);
    ArchivoAbrir(ARCHIVO, RUTA, 1);
    ArchivoLeer(ARCHIVO, CABECERA, 0x12);
    t->ancho = CABECERA[0xC] + (CABECERA[0xD] << 8);
    t->alto = CABECERA[0xE] + (CABECERA[0xF] << 8);
    imagen = Reservar(t->ancho * t->alto * 2, D_800686C4, 0xB4);
    paleta = Reservar(t->ancho * t->alto * 2, D_800686C4, 0xB5);
    if (CABECERA[0x10] == 0x18) {
        func_80019FBC(ARCHIVO, t, imagen);
    } else if (CABECERA[0x10] == 0xF || CABECERA[0x10] == 0x10) {
        func_8001A108(ARCHIVO, t, imagen);
    } else {
        printf(D_80068718);
    }
    func_8001A668(imagen, t->ancho, t->alto, 2);
    imagen = func_8001A754(t, imagen, paleta, t->ancho * t->alto);
    func_8001A4C0(t);
    n = t->ancho << t->prof;
    if (t->banderas & 1) {
        for (i = 0; i != t->colores; i++) {
            if (paleta[i] != 0) {
                paleta[i] |= 0x8000;
            }
        }
    }
    if (t->prof == 0) {
        t->clut = LoadClut2(paleta, t->clut_x, t->clut_y);
    } else {
        t->clut = LoadClut(paleta, t->clut_x, t->clut_y);
    }
    func_8001A228(t, n);
    func_8001A620(t, (u16) (n / 4), imagen);
    t->tpage = GetTPage(t->prof, modo, t->x & ~0x3F, t->y);
    t->u = (t->x & 0x3F) << (2 - t->prof);
    t->v = t->y;
    Liberar(imagen);
    Liberar(paleta);
    ArchivoCerrar(ARCHIVO, -1);
    return t;
}

/* El original lee la cabecera sin saber si el archivo se abrio, y las funciones que llama leen basura de su
 * pila: el cuerpo tiene que correr con el sp del original (marco de 0x160 = este de 0x138 + el del cuerpo de
 * 0x28, con los registros guardados donde el original). ra va en sp+0, que el original no usa. */
__attribute__((naked))
void *func_8001B0C8(char *nombre) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x138\n"
            "\tsw $31, 0x0($sp)\n"
            "\tjal cargar_tga\n"
            "\tnop\n"
            "\tlw $31, 0x0($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x138\n"
            ".set reorder");
}
