#include "juego.h"

/* Reservar los buferes de primitivas de la GPU y darles su codigo. */

extern char D_8006C438[];            /* el nombre del archivo fuente */
extern u8 *D_8007CAA0, *D_8007CAA4, *D_8007CAA8, *D_8007CAAC, *D_8007CAB0, *D_8007CAB4, *D_8007CAB8,
    *D_8007CABC;                     /* el comienzo de cada bufer */
extern u8 *D_8007CAC0, *D_8007CAC4, *D_8007CAC8, *D_8007CACC, *D_8007CAD0, *D_8007CAD4, *D_8007CAD8,
    *D_8007CADC;                     /* el siguiente libre de cada uno */
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void func_8001410C(void *p), func_8001412C(void *p), func_8001414C(void *p), func_8001418C(void *p);
extern void func_800141AC(void *p), func_800141CC(void *p);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern void SetDrawMode(void *p, s32 dfe, s32 dtd, s32 tpage, void *tw);
extern s32 func_800217D0(void);

/* Reserva los ocho buferes, pone el codigo de primitiva en cada lugar y vuelve los punteros al principio
 * (func_800217D0). */
s32 func_8002153C(void) {
    u16 i;

    D_8007CAC0 = D_8007CAA0 = Reservar(0x27100, D_8006C438, 0xD1);
    D_8007CAC4 = D_8007CAA4 = Reservar(0x190, D_8006C438, 0xD2);
    D_8007CAC8 = D_8007CAA8 = Reservar(0x3E80, D_8006C438, 0xD3);
    D_8007CACC = D_8007CAAC = Reservar(0x2710, D_8006C438, 0xD4);
    D_8007CAD0 = D_8007CAB0 = Reservar(0xFA0, D_8006C438, 0xD5);
    D_8007CAD4 = D_8007CAB4 = Reservar(0x1900, D_8006C438, 0xD6);
    D_8007CAD8 = D_8007CAB8 = Reservar(0x7D0, D_8006C438, 0xD7);
    D_8007CADC = D_8007CABC = Reservar(0x18, D_8006C438, 0xD8);
    for (i = 0; i < 0xFA0; i++) {
        D_8007CAC0 += 0x28;
        func_8001412C(D_8007CAC0 - 0x28);
    }
    for (i = 0; i < 0x14; i++) {
        D_8007CAC4 += 0x14;
        func_8001410C(D_8007CAC4 - 0x14);
    }
    for (i = 0; i < 0x190; i++) {
        D_8007CAC8 += 0x28;
        func_8001414C(D_8007CAC8 - 0x28);
    }
    for (i = 0; i < 0x1F4; i++) {
        D_8007CACC += 0x14;
        func_8001418C(D_8007CACC - 0x14);
    }
    for (i = 0; i < 0x190; i++) {
        D_8007CAD4 += 0x10;
        func_800141AC(D_8007CAD4 - 0x10);
    }
    for (i = 0; i < 0x64; i++) {
        D_8007CAD8 += 0x14;
        func_800141CC(D_8007CAD8 - 0x14);
    }
    for (i = 0; i < 2; i++) {
        SetDrawMode(D_8007CADC, 1, 0, GetTPage(0, 1, 0, 0), NULL);
        D_8007CADC += 0xC;
    }
    return func_800217D0();
}
