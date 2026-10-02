#include "juego.h"

/* Screen.c: reserva los buferes de primitivas de cada clase (el inicio queda en D_8007CAA0.. y el puntero
   que avanza en D_8007CAC0..) y deja cada primitiva con su codigo puesto. */

extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern char D_8006C438[];       /* "Screen.c" */
extern u8 *D_8007CAA0, *D_8007CAA4, *D_8007CAA8, *D_8007CAAC, *D_8007CAB0, *D_8007CAB4, *D_8007CAB8,
    *D_8007CABC;
extern u8 *D_8007CAC0, *D_8007CAC4, *D_8007CAC8, *D_8007CACC, *D_8007CAD0, *D_8007CAD4, *D_8007CAD8,
    *D_8007CADC;
extern void func_8001412C(u8 *p);   /* SetPolyFT4 */
extern void func_8001410C(u8 *p);
extern void func_8001414C(u8 *p);
extern void func_8001418C(u8 *p);
extern void func_800141AC(u8 *p);
extern void func_800141CC(u8 *p);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern void SetDrawMode(u8 *p, s32 dfe, s32 dtd, s32 tpage, void *tw);
extern s32 func_800217D0(void);

#define RESERVAR(inicio, cursor, tam, linea) \
    do { \
        u8 *b_ = Reservar(tam, D_8006C438, linea); \
        inicio = b_; \
        cursor = b_; \
    } while (0)

#define ARMAR(cursor, n, paso, armar) \
    do { \
        u32 i_; \
        for (i_ = 0; i_ < (n); i_ = (i_ + 1) & 0xFFFF) { \
            u8 *p_ = cursor; \
            cursor = p_ + (paso); \
            armar(p_); \
        } \
    } while (0)

s32 func_8002153C(void) {
    u32 i;

    RESERVAR(D_8007CAA0, D_8007CAC0, 0x27100, 0xD1);
    RESERVAR(D_8007CAA4, D_8007CAC4, 0x190, 0xD2);
    RESERVAR(D_8007CAA8, D_8007CAC8, 0x3E80, 0xD3);
    RESERVAR(D_8007CAAC, D_8007CACC, 0x2710, 0xD4);
    RESERVAR(D_8007CAB0, D_8007CAD0, 0xFA0, 0xD5);
    RESERVAR(D_8007CAB4, D_8007CAD4, 0x1900, 0xD6);
    RESERVAR(D_8007CAB8, D_8007CAD8, 0x7D0, 0xD7);
    RESERVAR(D_8007CABC, D_8007CADC, 0x18, 0xD8);
    ARMAR(D_8007CAC0, 0xFA0, 0x28, func_8001412C);
    ARMAR(D_8007CAC4, 0x14, 0x14, func_8001410C);
    ARMAR(D_8007CAC8, 0x190, 0x28, func_8001414C);
    ARMAR(D_8007CACC, 0x1F4, 0x14, func_8001418C);
    ARMAR(D_8007CAD4, 0x190, 0x10, func_800141AC);
    ARMAR(D_8007CAD8, 0x64, 0x14, func_800141CC);
    for (i = 0; i < 2; i = (i + 1) & 0xFFFF) {
        SetDrawMode(D_8007CADC, 1, 0, GetTPage(0, 1, 0, 0), NULL);
        D_8007CADC += 0xC;
    }
    return func_800217D0();
}
