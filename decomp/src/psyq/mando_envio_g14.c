#include "juego.h"

/* El protocolo del mando (libpad): mandar un paquete de varias partes y esperar la respuesta de cada una. */

extern s32 D_8006CFB8;               /* los buferes de envio (0xF0 cada uno) */
extern s32 D_8006CFC4;               /* el bufer que se esta usando */
extern s32 D_8006CFDC[2];            /* el estado de cada bufer */
extern s32 D_8006CFE4;               /* partes que faltan */
extern u8 *D_8006CFE8;               /* la respuesta */
extern s32 D_8006CFF0;               /* hay que repetir la cabecera */
extern void (*D_8006CF84)(s32);
extern s32 (*D_8006CF8C)(void *puerto, s32 n);
extern void (*D_8006CF90)();
extern void (*D_8006CFA4)(s32);
extern void (*D_8006CFA8)(s32);

extern s32 func_8002643C(void *puerto, s32 b);
extern s32 func_8002622C(void *puerto, s32 b);
extern void func_8002908C(s32 n);
extern s32 func_800266B4(void);
extern void func_80026744(void);

/* Devuelve 0 si se mando todo, -3 si el mando dejo de responder o lo que devolvio el envio si fallo. */
s32 func_800275F8(u8 *puerto) {
    s32 *estado;
    s32 cabecera;
    s32 base;
    s32 p;
    s32 off;
    s32 e;
    s32 r;
    s32 i;
    u8 k;

    if (D_8006CFF0 != 0) {
        D_8006CF90(puerto);
    }
    cabecera = D_8006CFF0;
    i = -1;
    if (cabecera != 0) {
        off = -0xF0;
        while (--D_8006CFE4 > 0) {
            if (i >= 0) {
                D_8006CF90(*(s32 *) (puerto + 0xC) + off);
            }
            r = func_8002643C(puerto, D_8006CF8C(puerto, 1) & 0xFF);
            if (r < 0) {
                return r;
            }
            func_8002908C(0x3C);
            i++;
            if (func_800266B4() == 0) {
                return -3;
            }
            off += 0xF0;
            if (i >= 4) {
                break;
            }
        }
    }
    p = 0;
    e = D_8006CFC4 == 0;
    if (D_8006CFE4 >= 2) {
        estado = &D_8006CFDC[e];
        base = e * 0xF0;
        do {
            if (*estado < 0) {
                break;
            }
            if (*estado > 0) {
                p = *(s32 *) (base + D_8006CFB8 + 0xC) + *estado * 0xF0 - 0xF0;
                D_8006CFA4(p);
            }
            switch (*estado) {
            case 3:
                D_8006CFA4(p - 0xF0);
                *estado = 1;
                break;
            case 0:
            case 1:
                p = D_8006CFB8 + base;
                D_8006CFA4(p);
                D_8006CFA8(p);
                *estado = -1;
                break;
            case 4:
                *estado = 3;
                break;
            }
            r = func_8002622C(puerto, D_8006CF8C(puerto, cabecera) & 0xFF);
            if (r < 0) {
                return r;
            }
            func_8002908C(0x3C);
            if (func_800266B4() == 0) {
                return -3;
            }
        } while (--D_8006CFE4 >= 2);
    }
    if (--D_8006CFE4 > 0) {
        do {
            r = func_8002622C(puerto, D_8006CF8C(puerto, cabecera) & 0xFF);
            if (r < 0) {
                return r;
            }
            if (*(u16 *) (D_8006CFE8 + 0xE) != 0x22) {
                func_8002908C(0x3C);
                if (func_800266B4() == 0) {
                    return -3;
                }
            }
        } while (--D_8006CFE4 > 0);
    }
    func_80026744();
    k = puerto[0x44];
    puerto[0x44] = k + 1;
    (*(u8 **) (puerto + 0x3C))[k] = D_8006CFE8[0];
    D_8006CF84(0);
    return 0;
}
