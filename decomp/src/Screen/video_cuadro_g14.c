#include "juego.h"

/* El reproductor de video: subir a la VRAM la tira decodificada y pedir la siguiente. */

extern u8 D_800D5818[];              /* el estado del reproductor (ver los desplazamientos abajo) */
extern s32 D_8008143C;               /* hay que leer mas del CD */
extern void func_8002D714(void);     /* seguir leyendo el video */
extern s32 SubirAVRAM(u8 *rect, s32 datos);              /* LoadImage */
extern s32 func_8005D0F4(void);      /* ancho de la tira siguiente */
extern s32 func_8005DD50(s32 bufer, s32 ancho);          /* decodificar la tira siguiente (MDEC) */

#define V16(d) (*(s16 *)(D_800D5818 + (d)))
#define V32(d) (*(s32 *)(D_800D5818 + (d)))

/* 0x00 leyendo; 0x18 los rectangulos de las dos paginas (x en 0x18 + 8i, ancho en 0x1C + 8i); 0x28 el
 * rectangulo de la tira (x en 0x28, ancho en 0x2C); 0x32 cuadro terminado; 0x34 la pagina; 0x38 el bufer
 * (0 o 1); 0x44 los dos buferes. Sube la tira, cambia de bufer y corre la x; si no llego al borde decodifica
 * la siguiente, si no marca el cuadro terminado. Devuelve lo que el original deja en v0. */
s32 func_8005D26C(void) {
    if (V16(0x00) != 0 && D_8008143C != 0) {
        func_8002D714();
        D_8008143C = 0;
    }
    SubirAVRAM(D_800D5818 + 0x28, V32(0x44 + V16(0x38) * 4));
    V16(0x38) ^= 1;
    V16(0x28) = SUMA_TRAMPA(V16(0x28), V16(0x2C));
    if (V16(0x28) < SUMA_TRAMPA(V16(0x18 + V16(0x34) * 8), V16(0x1C + V16(0x34) * 8))) {
        s32 ancho = func_8005D0F4();
        return func_8005DD50(V32(0x44 + V16(0x38) * 4), ancho);
    }
    V16(0x32) = 1;
    return 1;
}
