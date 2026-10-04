#include "juego.h"

/* Herramienta de desarrollo: copia la cuadricula de un nivel (GRAPHICS\<nombre>.XDX) al archivo de la PC. La
 * cabecera (12 bytes) dice cuantos elementos tiene cada bloque: de 12 bytes, de 8 y de 2. */

typedef struct {
    s16 n12;                            /* 0x0 */
    s16 n8;                             /* 0x2 */
    u8 _4[4];
    s32 n2;                             /* 0x8 */
} CabXDX;

extern char D_80068830[];               /* el nombre del archivo fuente */
extern char D_8007C7E0[];               /* "%s%s" */
extern char D_8007A1D0[];               /* "GRAPHICS\" */
extern void *D_8007CA48;
extern void *D_8007CBCC;
extern void *D_8007CBD0;

extern void ArchivoIniciar(void *a);
extern void ArchivoAbrir(void *a, char *ruta, s32 modo);
extern void ArchivoLeer(void *a, void *d, s32 n);
extern void ArchivoCerrar(void *a, s32 n);
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void Liberar(void *p);
extern s32 sprintf(char *d, const char *f, ...);
extern char *func_80014FF0(char *s, s32 c);     /* strchr */
extern s32 func_80029530(s32 arch, void *datos, s32 n);  /* PCwrite */

/* Un lugar del marco del original: el cuerpo corre con el mismo sp (ver HerramientaArmarCuadricula abajo). */
#define PILA(off) ({ u8 *_p; __asm__ volatile("addiu %0, $sp, " #off : "=r"(_p)); _p; })
#define DIR(x) ({ void *_d; __asm__ volatile("la %0, " #x : "=r"(_d)); _d; })  /* sin guardarla en un registro */
#define G(x) (*(void **) DIR(x))       /* una global, leida cada vez como en el original */
#define RUTA ((char *) PILA(0x24))
#define ARCHIVO PILA(0xA4)
#define CAB ((CabXDX *) PILA(0x144))

__attribute__((noinline, used)) static void armar_cuadricula(char *nombre, s32 arch) {
    char *p;

    ArchivoIniciar(ARCHIVO);
    sprintf(RUTA, DIR(D_8007C7E0), DIR(D_8007A1D0), nombre);
    p = func_80014FF0(RUTA, '.');
    p[1] = 'X';
    p[2] = 'D';
    p[3] = 'X';
    ArchivoAbrir(ARCHIVO, RUTA, 1);
    ArchivoLeer(ARCHIVO, CAB, 0xC);
    func_80029530(arch, CAB, 0xC);
    G(D_8007CA48) = Reservar(CAB->n12 * 12, DIR(D_80068830), 0x200);
    G(D_8007CBCC) = Reservar(CAB->n8 * 8, DIR(D_80068830), 0x201);
    G(D_8007CBD0) = Reservar(CAB->n2 * 2, DIR(D_80068830), 0x202);
    ArchivoLeer(ARCHIVO, G(D_8007CA48), CAB->n12 * 12);
    func_80029530(arch, G(D_8007CA48), CAB->n12 * 12);
    ArchivoLeer(ARCHIVO, G(D_8007CBCC), CAB->n8 * 8);
    func_80029530(arch, G(D_8007CBCC), CAB->n8 * 8);
    ArchivoLeer(ARCHIVO, G(D_8007CBD0), CAB->n2 * 2);
    func_80029530(arch, G(D_8007CBD0), CAB->n2 * 2);
    Liberar(G(D_8007CA48));
    Liberar(G(D_8007CBCC));
    Liberar(G(D_8007CBD0));
    ArchivoCerrar(ARCHIVO, -1);
}

/* El cuerpo corre con el sp del original: 0x150 = 0x130 de este marco + 0x20 del cuerpo. ra va en sp+0
 * (sp+0x20 del original, que no se usa). */
__attribute__((naked))
void HerramientaArmarCuadricula(char *nombre, s32 arch) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x130\n"
            "\tsw $31, 0x0($sp)\n"
            "\tjal armar_cuadricula\n"
            "\tnop\n"
            "\tlw $31, 0x0($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x130\n"
            ".set reorder");
}
