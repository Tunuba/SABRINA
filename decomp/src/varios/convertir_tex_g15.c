#include "juego.h"

/* Herramienta de desarrollo: guarda en la PC media VRAM (el rectangulo de D_8007C7B8, 0x80000 bytes) como
 * GRAPHICS\<nombre> con la extension cambiada a .TEX. El bufer va en la pila (marco de 0x800A0). */

typedef struct {
    s16 x, y, w, h;
} Rect;

extern Rect D_8007C7B8;
extern char D_8007C7C0[];               /* "%s%s" */
extern char D_8007A1D0[];               /* "GRAPHICS\" */

extern s32 sprintf(char *d, const char *f, ...);
extern char *func_80014FF0(char *s, s32 c);     /* strchr */
extern s32 func_800294F0(char *nombre, s32 a, s32 b);    /* PCcreat */
extern s32 func_80029518(s32 arch);                      /* PCclose */
extern s32 func_80029530(s32 arch, void *datos, s32 n);  /* PCwrite */
extern void func_80012ECC(Rect *r, void *destino);       /* StoreImage */
extern s32 func_80012D74(s32 modo);                      /* DrawSync */

/* Un lugar del marco del original: el cuerpo corre con el mismo sp (ver HerramientaConvertirTEX abajo). */
#define PILA(off) ({ u8 *_p; __asm__ volatile("addiu %0, $sp, " #off : "=r"(_p)); _p; })
#define DIR(x) ({ void *_d; __asm__ volatile("la %0, " #x : "=r"(_d)); _d; })  /* sin guardarla en un registro */
#define RECT ((Rect *) PILA(0x18))
#define RUTA ((char *) PILA(0x20))
#define BUFER PILA(0xA0)

__attribute__((noinline, used)) static void convertir_tex(char *nombre) {
    Rect *r = DIR(D_8007C7B8);
    char *p;
    s32 arch;

    RECT->x = r->x;
    RECT->y = r->y;
    RECT->w = r->w;
    RECT->h = r->h;
    sprintf(RUTA, DIR(D_8007C7C0), DIR(D_8007A1D0), nombre);
    p = func_80014FF0(RUTA, '.');
    p[1] = 'T';
    p[2] = 'E';
    p[3] = 'X';
    arch = func_800294F0(RUTA, 0x200, 2);
    func_80012ECC(RECT, BUFER);
    func_80012D74(0);
    func_80029530(arch, BUFER, 0x80000);
    func_80029518(arch);
}

/* El cuerpo corre con el sp del original: 0x800A0 = 0x80088 de este marco + 0x18 del cuerpo (s0 y ra en 0x10 y
 * 0x14, como el original). ra va en sp+0 de la entrada, el lugar que la convencion le da a esta funcion para
 * guardar a0 (el original no lo usa); el marco entero queda debajo. */
__attribute__((naked))
void HerramientaConvertirTEX(char *nombre) {
    __asm__(".set noreorder\n"
            ".set noat\n"
            "\tsw $31, 0x0($sp)\n"
            "\tlui $1, 0xFFF7\n"
            "\tori $1, $1, 0xFF78\n"
            "\taddu $sp, $sp, $1\n"
            "\tjal convertir_tex\n"
            "\tnop\n"
            "\tlui $1, 0x8\n"
            "\tori $1, $1, 0x88\n"
            "\taddu $sp, $sp, $1\n"
            "\tlw $31, 0x0($sp)\n"
            "\tjr $31\n"
            "\tnop\n"
            ".set at\n"
            ".set reorder");
}
