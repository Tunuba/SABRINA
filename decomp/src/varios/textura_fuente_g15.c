#include "juego.h"

/* Herramienta de desarrollo: carga una fuente de la carpeta D_8007A220 (GRAPHICS\FONT\): un .TGA con todas
 * las letras, que func_8001ADD8 va recortando de a una. Cada letra (12 bytes en letras) queda con su tpage, su
 * paleta de 16 colores y su lugar en la VRAM. Devuelve cuantas letras cargo. */

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
    u8 prof;                            /* 0x1D */
    u8 _1E[2];
} TexFuente;

extern char D_800686C4[];               /* el nombre del archivo fuente */
extern char D_80068718[];
extern char D_80068730[];               /* "graphics/font/" y espacios: lo que tiene la ruta antes del sprintf */
extern char D_8007C7C8[];               /* "%s%s" */
extern char D_8007A220[];               /* "GRAPHICS\FONT\" */

extern void ArchivoIniciar(void *a);
extern void ArchivoAbrir(void *a, char *ruta, s32 modo);
extern void ArchivoLeer(void *a, void *d, s32 n);
extern void ArchivoCerrar(void *a, s32 n);
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void Liberar(void *p);
extern s32 sprintf(char *d, const char *f, ...);
extern s32 printf(const char *f, ...);
extern char *func_80014FF0(char *s, s32 c);     /* strchr */
extern void func_80019FBC(void *a, TexFuente *t, void *d);
extern void func_8001A108(void *a, TexFuente *t, void *d);
extern void func_8001A668(void *d, s32 ancho, s32 alto, s32 n);
extern void *func_8001ADD8(void *imagen, u8 *letra, s32 ancho, s32 x);   /* recorta la letra que sigue */
extern void *func_8001A754(TexFuente *t, void *d, void *paleta, s32 n);
extern void func_8001A4C0(TexFuente *t);
extern void func_8001A228(TexFuente *t, s32 n);
extern void func_8001A620(TexFuente *t, s32 n, void *d);
extern s32 LoadClut2(void *c, s32 x, s32 y);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);

/* Un lugar del marco del original: el cuerpo corre con el mismo sp (ver func_8001B9C0 abajo). */
#define PILA(off) ({ u8 *_p; __asm__ volatile("addiu %0, $sp, " #off : "=r"(_p)); _p; })
#define RUTA ((char *) PILA(0x34))
#define TEX ((TexFuente *) PILA(0xB4))  /* a medio llenar: el resto es lo que habia en la pila */
#define CABECERA PILA(0xD4)             /* los 0x12 bytes de la cabecera del .TGA */
#define ARCHIVO PILA(0xE8)

__attribute__((noinline, used)) static s32 cargar_fuente(u8 *letras, char *nombre) {
    u8 *imagen;
    u8 *letra;
    u16 *paleta;
    char *p;
    u16 x;
    u16 n;
    u8 w;
    s32 k;

    for (k = 0; k < 0x80; k++) {
        RUTA[k] = D_80068730[k];
        __asm__ volatile("" : : : "memory");    /* que GCC no lo cambie por un memcpy */
    }
    ArchivoIniciar(ARCHIVO);
    paleta = Reservar(0xFA2, D_800686C4, 0x129);
    TEX->colores = 0x10;
    TEX->prof = 0;
    x = 0;
    n = 0;
    TEX->alto = 0x20;
    sprintf(RUTA, D_8007C7C8, D_8007A220, nombre);
    p = func_80014FF0(RUTA, '.');
    p[1] = 'T';
    p[2] = 'G';
    p[3] = 'A';
    ArchivoAbrir(ARCHIVO, RUTA, 1);
    ArchivoLeer(ARCHIVO, CABECERA, 0x12);
    TEX->ancho = CABECERA[0xC] + (CABECERA[0xD] << 8);
    TEX->alto = CABECERA[0xE] + (CABECERA[0xF] << 8);
    imagen = Reservar(TEX->ancho * TEX->alto * 2, D_800686C4, 0x13D);
    if (CABECERA[0x10] == 0x18) {
        func_80019FBC(ARCHIVO, TEX, imagen);
    } else if (CABECERA[0x10] == 0xF || CABECERA[0x10] == 0x10) {
        func_8001A108(ARCHIVO, TEX, imagen);
    } else {
        printf(D_80068718);
    }
    func_8001A668(imagen, TEX->ancho, TEX->alto, 2);
    do {
        letra = func_8001ADD8(imagen, letras, (u16) TEX->ancho, x);
        if (letra != 0) {
            func_8001A4C0(TEX);
            letra = func_8001A754(TEX, letra, paleta, letras[0xA] * letras[0xB]);
            *(u16 *) (letras + 6) = LoadClut2(paleta, TEX->clut_x, TEX->clut_y);
            func_8001A228(TEX, letras[0xA]);
            func_8001A620(TEX, (u16) (letras[0xA] / 4), letra);
            letras[4] = GetTPage(TEX->prof, 0, TEX->x & ~0x3F, TEX->y);
            letras[8] = (TEX->x & 0x3F) << 2;
            letras[9] = TEX->y;
            w = letras[0xA];
            x += (u16) (w + 1);
            letras[0xA] = w - 1;
            n++;
            letras += 0xC;
            Liberar(letra);
        }
    } while (letra != 0);
    Liberar(paleta);
    Liberar(imagen);
    ArchivoCerrar(ARCHIVO, -1);
    return n;
}

/* El cuerpo corre con el sp del original: 0x188 = 0x158 de este marco + 0x30 del cuerpo. ra va en sp+0
 * (sp+0x30 del original, que no se usa). */
__attribute__((naked))
s32 func_8001B9C0(u8 *letras, char *nombre) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x158\n"
            "\tsw $31, 0x0($sp)\n"
            "\tjal cargar_fuente\n"
            "\tnop\n"
            "\tlw $31, 0x0($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x158\n"
            ".set reorder");
}
