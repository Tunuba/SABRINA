/* libgpu de Sony (PsyQ) enlazada en el juego: estado de depuracion y tabla de funciones del controlador
 * del GPU. Los nombres de libgpu salen de los mensajes de depuracion ("DrawSync(%d)...", "LoadImage"...). */
#ifndef GPU_G00_H
#define GPU_G00_H

#include "juego.h"

/* Rectangulo de la VRAM (RECT de libgpu). */
typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} RectVram;
EN(RectVram, h, 0x6);

/* Tabla de funciones del controlador del GPU (_GPU_cw de libgpu). Solo los campos que se usan. */
typedef struct {
    u8 pad00[0x8];
    s32 (*encolar)(void *func, void *datos, s32 tam, s32 param);  /* 0x08: pone un comando en la cola */
    void *limpiar;                                                /* 0x0C: rellena un RECT (ClearImage) */
    u8 pad10[0x4];
    s32 (*dibujarPrim)(void *datos, s32 largo);                   /* 0x14: manda un primitivo directo */
    void *dibujarOT;                                              /* 0x18: dibuja una tabla de orden */
    void *leerVram;                                               /* 0x1C: VRAM a RAM (StoreImage) */
    void *escribirVram;                                           /* 0x20: RAM a VRAM (LoadImage) */
    u8 pad24[0x8];
    s32 (*limpiarOT)(u32 *ot, s32 n);                             /* 0x2C: arma la tabla de orden al reves */
    u8 pad30[0xC];
    s32 (*sincronizar)(s32 modo);                                 /* 0x3C: espera o consulta la cola */
} ControladorGpu;
EN(ControladorGpu, encolar, 0x8);
EN(ControladorGpu, dibujarPrim, 0x14);
EN(ControladorGpu, escribirVram, 0x20);
EN(ControladorGpu, limpiarOT, 0x2C);
EN(ControladorGpu, sincronizar, 0x3C);

/* Nivel de depuracion de libgpu (_dbg) y tamano de la VRAM para revisar los RECT. */
typedef struct {
    u8 depuracion;  /* 0: nada, 1: revisa los RECT, 2: ademas imprime cada llamada */
    u8 pad1;
    s16 ancho;
    s16 alto;
} EstadoGpu;
EN(EstadoGpu, alto, 0x4);

extern ControladorGpu *D_800636C8;               /* controlador en uso */
extern EstadoGpu D_8006379A;
extern s32 (*D_80063794)(const char *fmt, ...);  /* GPU_printf */

#endif
