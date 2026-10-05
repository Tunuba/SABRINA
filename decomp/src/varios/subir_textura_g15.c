#include "juego.h"

/* Sube a VRAM los pixeles de la textura t: el rectangulo en (t+0x12, t+0x14) con ancho w y alto t+0xA. */

typedef struct {
    s16 x, y, w, h;
} Rect;

extern void SubirAVRAM(Rect *r, void *pixeles);

/* El rectangulo va en sp+0x18 del marco del original: SubirAVRAM deja su direccion en la cola del GPU. */
#define PILA(off) ({ u8 *_p; __asm__ volatile("addiu %0, $sp, " #off : "=r"(_p)); _p; })
#define RECT ((Rect *) PILA(0x18))

__attribute__((noinline, used, optimize("no-optimize-sibling-calls"))) static void subir_textura(u8 *t, s32 w, void *pixeles) {
    RECT->x = *(u16 *) (t + 0x12);
    RECT->y = *(u16 *) (t + 0x14);
    RECT->w = w;
    RECT->h = *(s16 *) (t + 0xA);
    SubirAVRAM(RECT, pixeles);
}

/* El cuerpo corre con el sp del original: 0x20 = 8 de este marco + 0x18 del cuerpo. ra va en sp+0 de la entrada
 * (el lugar que la convencion le da a esta funcion para guardar a0). */
__attribute__((naked))
void func_8001A620(u8 *t, s32 w, void *pixeles) {
    __asm__(".set noreorder\n"
            "\tsw $31, 0x0($sp)\n"
            "\taddiu $sp, $sp, -0x8\n"
            "\tjal subir_textura\n"
            "\tnop\n"
            "\taddiu $sp, $sp, 0x8\n"
            "\tlw $31, 0x0($sp)\n"
            "\tjr $31\n"
            "\tnop\n"
            ".set reorder");
}
