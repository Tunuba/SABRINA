#include "juego.h"

/* Arranque de la tarjeta de memoria y los 15 lugares de iconos: cada uno es un sprite de 16x16 en la VRAM
 * (x = 16 * i, y = 0x1E0) con su paleta (x = 32 * i, y = 0x1F0). */

typedef struct {
    u8 _00[8];
    u16 ancho;                          /* 0x08 */
    u16 alto;                           /* 0x0A */
    u16 tpage;                          /* 0x0C */
    u16 clut;                           /* 0x0E */
    u8 u;                               /* 0x10 */
    u8 v;                               /* 0x11 */
    u16 x;                              /* 0x12 donde va la imagen en la VRAM */
    u16 y;                              /* 0x14 */
    u16 clut_x;                         /* 0x16 donde va la paleta */
    u16 clut_y;                         /* 0x18 */
    u8 _1A[6];
} IconoTarjeta;

extern IconoTarjeta D_800D50B0[15];

extern void func_8004FD04(s32);
extern s32 func_80050938(void);
extern void _bu_init(void);
extern void func_8004EB04(void);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern s32 LoadClut2(void *clut, s32 x, s32 y);

/* El cuerpo; paleta es el lugar de la pila del original (abajo). */
__attribute__((noinline, used)) static void iniciar_iconos(u8 *paleta) {
    IconoTarjeta *ic;
    u16 i;
    u16 x;
    s16 clut_x;
    s32 o;

    func_8004FD04(0);
    func_80050938();
    _bu_init();
    func_8004EB04();
    o = 0;
    x = 0;
    clut_x = 0;
    for (i = 0; i != 15; i++) {
        ic = (IconoTarjeta *) ((u8 *) D_800D50B0 + o);
        ic->ancho = 0x10;
        ic->alto = 0x10;
        ic->x = x;
        ic->y = 0x1E0;
        ic->clut_x = clut_x;
        ic->clut_y = 0x1F0;
        ic->u = (ic->x & 0x3F) << 2;
        ic->v = ic->y;
        ic->tpage = GetTPage(0, 0, ic->x & ~0x3F, ic->y);
        ic->clut = LoadClut2(paleta, ic->clut_x, ic->clut_y);
        clut_x += 0x20;
        x += 0x10;
        o += 0x20;
    }
}

/* La paleta que sube LoadClut2 son los 32 bytes de la pila sin llenar (sp+0x28 de un marco de 0x48): el
 * marco va a mano para que la basura sea la misma. */
__attribute__((naked))
void func_8004EBD0(void) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x48\n"
            "\tsw $31, 0x20($sp)\n"
            "\tjal iniciar_iconos\n"
            "\taddiu $4, $sp, 0x28\n"
            "\tlw $31, 0x20($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x48\n"
            ".set reorder");
}
