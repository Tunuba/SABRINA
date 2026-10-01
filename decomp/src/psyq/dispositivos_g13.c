#include "juego.h"

/* Tabla de dispositivos de la BIOS: en 0x150 su comienzo y en 0x154 su tamano, registros de 0x50 bytes
 * con el nombre en +0 y una funcion en +0x34. */

typedef s32 (*FuncDisp)(s32 *a, s32 b, s32 c);

extern FuncDisp D_80084B0C;
extern char D_80084B14[];            /* el nombre del dispositivo que se cambia */
extern s32 strcmp(const char *a, const char *b);

/* Pone en *a un 1 si estaba en 0, cambia la funcion +0x34 del dispositivo D_80084B14 por D_80084B0C y
 * llama a D_80084B0C con los mismos argumentos. */
s32 func_80014670(s32 *a, s32 b, s32 c) {
    u8 *p, *fin;
    FuncDisp f;

    if (*a == 0) {
        *a = 1;
    }
    p = *(u8 **)0x150;
    fin = p + (*(u32 *)0x154 / 0x50) * 0x50;
    f = D_80084B0C;
    for (; p < fin; p += 0x50) {
        if (*(char **)p != NULL && strcmp(*(char **)p, D_80084B14) == 0) {
            *(FuncDisp *)(p + 0x34) = f;
            break;
        }
    }
    return D_80084B0C(a, b, c);
}
