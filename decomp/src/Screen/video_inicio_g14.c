#include "juego.h"

/* El reproductor de video: preparar todo antes de empezar (estado, pantallas, buferes, MDEC y streaming). */

extern u8 D_800D5818[];              /* el estado del reproductor (ver video_cuadro_g14.c) */
extern s32 D_8007CC84;               /* el primer lugar libre del bloque del video */
extern s32 D_8007CC88;               /* el bloque del video (512 KB) */
extern s32 D_8007CC8C;               /* la tabla del VLC */
extern s32 D_8007CC80;               /* el anillo del streaming */
extern s16 D_8007CC7C[2];            /* el volumen del CD de antes */

extern void DecDCTvlcBuild(s32 tabla);
extern s32 func_80017304(void);      /* la pagina que se muestra (GetDispBuff) */
extern void SetDefDispEnv(void *env, s32 x, s32 y, s32 w, s32 h);
extern void func_8005C964(void);
extern s32 func_8001626C(s32 modo);  /* VSync */
extern void func_8001321C(void *env);                      /* PutDispEnv */
extern s32 func_8005D3A0(s32 x);     /* ancho en la VRAM segun la profundidad */
extern s32 func_8005D8A0(s32 tam);   /* reservar del bloque del video */
extern void func_8005DCA0(s32 modo); /* DecDCTReset */
extern void DecDCTvlcSize2(s32 n);
extern void func_8005DDE8(void *f);  /* DecDCToutCallback */
extern s32 func_8005D26C();
extern void StSetRing(s32 anillo, s32 n);
extern void StSetStream(s32 modo, s32 desde, s32 hasta, void *f1, void *f2);
extern void SsGetSerialVol(s32 s, s16 *v);
extern void SsSetSerialVol(s32 s, s32 izq, s32 der);
extern void func_8005D3DC(void);

#define V8(d) (*(u8 *) (D_800D5818 + (d)))
#define V16(d) (*(s16 *) (D_800D5818 + (d)))
#define V32(d) (*(s32 *) (D_800D5818 + (d)))
#define P16(d) (*(s16 *) (pedido + (d)))

/* pedido: 0x04 profundidad (1 = 24 bits), 0x06, 0x08 ancho de la pantalla, 0x0A, 0x0C, 0x0E y 0x10 ancho y
 * alto del video, 0x14 el ultimo cuadro, 0x18 el tamano del bufer de entrada (0 = 0x20400), 0x1C volumen. */
void func_8005C9D0(u8 *pedido) {
    s16 ancho;
    s16 alto;
    s16 w;
    s32 tam;
    s16 *r;

    D_8007CC84 = D_8007CC88;
    DecDCTvlcBuild(D_8007CC8C);
    w = P16(0x08);
    ancho = P16(0x0E);
    alto = P16(0x10);
    V16(0x00) = P16(0x04);
    V16(0x02) = w;
    V16(0x04) = P16(0x0A);
    V16(0x06) = P16(0x0C);
    V16(0x08) = ancho;
    V16(0x0A) = alto;
    V32(0x0C) = *(s32 *) (pedido + 0x14);
    V16(0x10) = P16(0x1C);
    V32(0x14) = 0;
    V16(0x30) = 0;
    V16(0x32) = 0;
    V16(0x34) = func_80017304();
    V16(0x36) = 0;
    V16(0x38) = 0;
    SetDefDispEnv(D_800D5818 + 0x4C, 0, 0, w, 0x100);
    SetDefDispEnv(D_800D5818 + 0x60, 0, 0x100, w, 0x100);
    V16(0x54) = 0;
    V16(0x56) = 0x12;
    V16(0x58) = 0;
    V16(0x5A) = 0x100;
    V16(0x68) = 0;
    V16(0x6A) = 0x12;
    V16(0x6C) = 0;
    V16(0x6E) = 0x100;
    V8(0x71) = V8(0x5D) = P16(0x04) == 1;
    if (P16(0x06) != 0 || V16(0x00) != 0) {
        func_8005C964();
    }
    func_8001626C(0);
    func_8001321C(D_800D5818 + 0x4C + V16(0x34) * 0x14);
    V16(0x18) = 0;
    V16(0x1A) = 0;
    V16(0x1C) = func_8005D3A0(ancho & 0xFFFF);
    V16(0x1E) = alto;
    V16(0x20) = 0;
    V16(0x22) = 0x100;
    V16(0x24) = func_8005D3A0(ancho & 0xFFFF);
    V16(0x26) = alto;
    r = (s16 *) (D_800D5818 + 0x18 + V16(0x34) * 8);
    V16(0x28) = r[0];
    V16(0x2A) = r[1];
    V16(0x2C) = r[2];
    V16(0x2E) = r[3];
    V16(0x2C) = func_8005D3A0(0x10);
    tam = *(s32 *) (pedido + 0x18);
    if (tam == 0) {
        tam = 0x20400;
    }
    V32(0x3C) = func_8005D8A0(tam);
    V32(0x40) = func_8005D8A0(tam);
    tam = alto << 5;
    if (V16(0x00) != 0) {
        tam = alto * 0x30;
    }
    V32(0x44) = func_8005D8A0(tam);
    V32(0x48) = func_8005D8A0(tam);
    func_8005DCA0(0);
    DecDCTvlcSize2(0);
    func_8005DDE8(func_8005D26C);
    D_8007CC80 = func_8005D8A0(0x20000);
    StSetRing(D_8007CC80, 0x40);
    StSetStream(V16(0x00), 0, -1, 0, 0);
    SsGetSerialVol(0, D_8007CC7C);
    SsSetSerialVol(0, V16(0x10), V16(0x10));
    func_8005D3DC();
}
