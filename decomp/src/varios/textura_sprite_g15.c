#include "juego.h"

/* Herramienta de desarrollo: carga un sprite .TGA de 16 bits de la carpeta D_8007A1F8 (GRAPHICS\SPRITE\), lo
 * reduce a paleta y lo sube a la VRAM. '!' seguido de una letra (A-D) en el nombre da el modo de mezcla. */

typedef struct {
    u8 _00[8];
    s16 ancho;                          /* 0x08; al final, la mitad en 8.8 */
    s16 alto;                           /* 0x0A; al final, la mitad en 8.8 */
    u16 tpage;                          /* 0x0C */
    u16 clut;                           /* 0x0E */
    u8 u;                               /* 0x10 */
    u8 v;                               /* 0x11 */
    u16 x;                              /* 0x12 */
    u16 y;                              /* 0x14 */
    u16 clut_x;                         /* 0x16 */
    u16 clut_y;                         /* 0x18 */
    u16 colores;                        /* 0x1A */
    u8 u1;                              /* 0x1C la profundidad mientras carga; al final, el ultimo u */
    u8 v1;                              /* 0x1D */
    u8 _1E[2];
} Sprite;

extern char D_800686C4[];               /* el nombre del archivo fuente */
extern char D_800686DC[];
extern char D_8007C7C8[];               /* "%s%s" */
extern char D_8007A1F8[];               /* "GRAPHICS\SPRITE\" */

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
extern void func_8001A108(void *a, Sprite *t, void *d);
extern void func_8001A668(void *d, s32 ancho, s32 alto, s32 n);
extern void *func_8001A754(Sprite *t, void *d, void *paleta, s32 n);
extern void func_8001A4C0(Sprite *t);
extern void func_8001A228(Sprite *t, s32 n);
extern void func_8001A620(Sprite *t, s32 n, void *d);
extern s32 LoadClut2(void *c, s32 x, s32 y);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);

/* Un lugar del marco del original: el cuerpo corre con el mismo sp (ver func_8001B698 abajo). */
#define PILA(off) ({ u8 *_p; __asm__ volatile("addiu %0, $sp, " #off : "=r"(_p)); _p; })
#define ARCHIVO PILA(0xC0)
#define RUTA ((char *) PILA(0x40))
#define CABECERA PILA(0x2C)             /* los 0x12 bytes de la cabecera del .TGA */

/* modo: sin '!' es lo que traia s3 el que llama, como en el original (el stub lo pasa) */
__attribute__((noinline, used)) static Sprite *cargar_sprite(char *nombre, u32 modo) {
    Sprite *t;
    u8 *imagen;
    u16 *paleta;
    u16 i;

    ArchivoIniciar(ARCHIVO);
    t = Reservar(0x20, D_800686C4, 0xE6);
    memset(t, 0, 0x20);
    sprintf(RUTA, D_8007C7C8, D_8007A1F8, nombre);
    if (func_80014FF0(nombre, '!') != 0) {
        modo = (u16) (func_80014FF0(nombre, '!')[1] - 'A');
        if (modo >= 4) {
            printf(D_800686DC);
            Afirmar(0, D_800686C4, 0xF3);
        }
    }
    ArchivoAbrir(ARCHIVO, RUTA, 1);
    ArchivoLeer(ARCHIVO, CABECERA, 0x12);
    t->ancho = CABECERA[0xC] + (CABECERA[0xD] << 8);
    t->alto = CABECERA[0xE] + (CABECERA[0xF] << 8);
    imagen = Reservar(t->ancho * t->alto * 2, D_800686C4, 0xFD);
    paleta = Reservar(t->ancho * t->alto * 2, D_800686C4, 0xFE);
    func_8001A108(ARCHIVO, t, imagen);
    func_8001A668(imagen, t->ancho, t->alto, 2);
    imagen = func_8001A754(t, imagen, paleta, t->ancho * t->alto);
    func_8001A4C0(t);
    for (i = 0; i != t->colores; i++) {
        if (paleta[i] != 0) {
            paleta[i] |= 0x8000;
        }
    }
    t->clut = LoadClut2(paleta, t->clut_x, t->clut_y);
    func_8001A228(t, t->ancho);
    func_8001A620(t, (u16) (t->ancho / 4), imagen);
    t->tpage = GetTPage(t->v1, modo, t->x & ~0x3F, t->y);
    t->u = (t->x & 0x3F) << (2 - t->v1);
    t->v = t->y;
    t->u1 = t->u + t->ancho - 1;
    t->v1 = t->v + t->alto - 1;
    t->ancho = (t->ancho / 2) << 8;
    t->alto = (t->alto / 2) << 8;
    Liberar(imagen);
    Liberar(paleta);
    ArchivoCerrar(ARCHIVO, -1);
    return t;
}

/* Como func_8001B0C8: el cuerpo corre con el sp del original (0x160 = 0x138 de este marco + 0x28 del cuerpo).
 * ra va en sp+0, que el original no usa. */
__attribute__((naked))
void *func_8001B698(char *nombre) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x138\n"
            "\tsw $31, 0x0($sp)\n"
            "\tjal cargar_sprite\n"
            "\tmove $5, $19\n"
            "\tlw $31, 0x0($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x138\n"
            ".set reorder");
}
