#include "juego.h"

/* Herramienta de desarrollo: convierte una imagen .TGA de 16 bits de GRAPHICS\PICTURES\ al formato .PIC del
 * juego (la imagen ya convertida y derecha) y la guarda en la PC con el mismo nombre en GRAPHICS\. */

typedef struct {
    u8 _00[8];
    s16 ancho;                          /* 0x08 */
    s16 alto;                           /* 0x0A */
    u8 _0C[0x14];
} TexPIC;

extern char D_800686C4[];               /* el nombre del archivo fuente */
extern char D_8007C7C8[];               /* "%s%s" */
extern char D_8007A20C[];               /* "GRAPHICS\PICTURES\" */
extern char D_8007A1D0[];               /* "GRAPHICS\" */

extern void ArchivoIniciar(void *a);
extern void ArchivoAbrir(void *a, char *ruta, s32 modo);
extern void ArchivoLeer(void *a, void *d, s32 n);
extern void ArchivoCerrar(void *a, s32 n);
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void Liberar(void *p);
extern void *memset(void *p, s32 c, u32 n);
extern s32 sprintf(char *d, const char *f, ...);
extern char *func_80014FF0(char *s, s32 c);     /* strchr */
extern void func_8001A108(void *a, TexPIC *t, void *d);
extern void func_8001A668(void *d, s32 ancho, s32 alto, s32 n);
extern s32 func_800294F0(char *nombre, s32 a, s32 b);    /* PCcreat */
extern s32 func_80029518(s32 arch);                      /* PCclose */
extern s32 func_80029530(s32 arch, void *datos, s32 n);  /* PCwrite */

/* Un lugar del marco del original: el cuerpo corre con el mismo sp (ver HerramientaConvertirPIC abajo). */
#define PILA(off) ({ u8 *_p; __asm__ volatile("addiu %0, $sp, " #off : "=r"(_p)); _p; })
#define CABECERA PILA(0x24)             /* los 0x12 bytes de la cabecera del .TGA */
#define RUTA ((char *) PILA(0x38))
#define ARCHIVO PILA(0xB8)
#define DIR(x) ({ void *_d; __asm__ volatile("la %0, " #x : "=r"(_d)); _d; })  /* sin guardarla en un registro */

__attribute__((noinline, used)) static void convertir_pic(char *nombre) {
    TexPIC *t;
    u8 *imagen;
    char *p;
    s32 arch;

    ArchivoIniciar(ARCHIVO);
    t = Reservar(0x20, DIR(D_800686C4), 0x171);
    memset(t, 0, 0x20);
    sprintf(RUTA, DIR(D_8007C7C8), DIR(D_8007A20C), nombre);
    p = func_80014FF0(RUTA, '.');
    p[1] = 'T';
    p[2] = 'G';
    p[3] = 'A';
    ArchivoAbrir(ARCHIVO, RUTA, 1);
    ArchivoLeer(ARCHIVO, CABECERA, 0x12);
    t->ancho = CABECERA[0xC] + (CABECERA[0xD] << 8);
    t->alto = CABECERA[0xE] + (CABECERA[0xF] << 8);
    imagen = Reservar(t->ancho * t->alto * 2, DIR(D_800686C4), 0x180);
    func_8001A108(ARCHIVO, t, imagen);
    func_8001A668(imagen, t->ancho, t->alto, 2);
    sprintf(RUTA, DIR(D_8007C7C8), DIR(D_8007A1D0), nombre);
    p = func_80014FF0(RUTA, '.');
    p[1] = 'P';
    p[2] = 'I';
    p[3] = 'C';
    arch = func_800294F0(RUTA, 0x200, 2);
    func_80029530(arch, imagen, t->ancho * t->alto * 2);
    func_80029518(arch);
    Liberar(imagen);
    Liberar(t);
    ArchivoCerrar(ARCHIVO, -1);
}

/* El cuerpo corre con el sp del original: 0x158 = 0x138 de este marco + 0x20 del cuerpo. ra va en sp+0
 * (sp+0x20 del original, que no se usa). */
__attribute__((naked))
void HerramientaConvertirPIC(char *nombre) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x138\n"
            "\tsw $31, 0x0($sp)\n"
            "\tjal convertir_pic\n"
            "\tnop\n"
            "\tlw $31, 0x0($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x138\n"
            ".set reorder");
}
