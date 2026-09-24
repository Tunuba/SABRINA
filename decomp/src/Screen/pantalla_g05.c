#include "juego.h"

/* Pantalla: preparar la pantalla (borrar la VRAM y abrir la fuente de depuracion) y el dibujo de cada
 * cuadro. Las funciones de Sony que se llaman: func_80012DDC es ClearImage (copia el rectangulo a la cola
 * de la GPU), func_80012D74 es DrawSync, func_80010880 es FntLoad y func_80010920 es FntOpen. */

typedef struct {
    s16 x, y, w, h;
} Rect;

typedef struct {
    s32 v[3];
} Vec3;

extern void func_80012DDC(Rect *r, s32 rojo, s32 verde, s32 azul);          /* ClearImage */
extern s32 func_80012D74(s32 modo);                                          /* DrawSync */
extern void func_80010880(s32 tx, s32 ty);                                   /* FntLoad */
extern s32 func_80010920(s32 x, s32 y, s32 w, s32 h, s32 fondo, s32 letras); /* FntOpen */

/* El rectangulo llega por valor en a0 y a1 (el juego lo guarda en su lugar de la pila y pasa su
 * direccion). */
void func_80021120(Rect r) {
    func_80012DDC(&r, 0, 0, 0);
    while (func_80012D74(1) != 0) {
    }
    func_80010880(0x200, 0x100);
    func_80010920(5, 5, 0x1FB, 0xD7, 0, 0x7D0);
}

/* La camara: ojo, hacia donde mira y arriba, tres vectores seguidos. */
extern Vec3 D_8006C444[3];
extern void *D_8007C9F8;             /* el nivel (celdas) */
extern void *D_8007C9E8;             /* la tabla de orden (OT) de este cuadro */
extern u16 D_8007CA20;
extern void *D_8007C9F4;
extern void *D_8007C9F0;
extern u16 D_8007CA9E;               /* triangulos mirados, se dibujen o no */

extern void func_8001FA3C(Vec3 ojo, Vec3 hacia, Vec3 arriba);
extern void func_80022E58(void);
extern void DibujarCeldasVisibles(void *nivel, s32 b);
extern void DibujarTexto(void *ot, s32 n);
extern void func_80024300(void);
extern void func_8001F6C8(void *ot);
extern void func_8001FD50(void *modelo, void *ot, s32 c);
extern void func_800204F0(void *modelo, void *ot, s32 c);
extern void func_800218D4(void);
extern void func_800217D0(void);

/* Dibujo de un cuadro: pone la camara, el nivel, el texto, las particulas y los modelos. */
void func_80021B4C(void) {
    func_8001FA3C(D_8006C444[0], D_8006C444[1], D_8006C444[2]);
    func_80022E58();
    DibujarCeldasVisibles(D_8007C9F8, 0);
    DibujarTexto(D_8007C9E8, D_8007CA20);
    func_80024300();
    func_8001F6C8(D_8007C9E8);
    D_8007CA9E = 0;
    func_8001FD50(D_8007C9F4, D_8007C9E8, 0);
    func_800204F0(D_8007C9F0, D_8007C9E8, 0);
    func_800218D4();
    func_800217D0();
}
