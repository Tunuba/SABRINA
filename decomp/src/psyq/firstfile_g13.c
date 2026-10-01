#include "juego.h"

/* firstfile con el arreglo de dispositivos (en su propio archivo para que func_80014670 sea la del juego).
 * Tabla de dispositivos de la BIOS: en 0x150 su comienzo y en 0x154 su tamano, registros de 0x50 bytes
 * con el nombre en +0 y una funcion en +0x34. */

typedef s32 (*FuncDisp)(s32 *a, s32 b, s32 c);

extern FuncDisp D_80084B0C;
extern char D_80084B14[];            /* el nombre del dispositivo que se cambia */
extern s32 strcmp(const char *a, const char *b);
extern s32 func_80014670(s32 *a, s32 b, s32 c);

extern s32 firstfile2(char *nombre, void *archivo);

/* firstfile con un arreglo: copia el nombre del dispositivo (lo que hay antes del primer caracter menor que
 * ';', como los ':' de "cdrom:") a D_80084B14 y, si existe, guarda su funcion +0x34 en D_80084B0C y pone
 * func_80014670 en su lugar antes de llamar a firstfile2. Si no existe devuelve 0. */
s32 func_80014774(char *nombre, void *archivo) {
    char *s = nombre;
    char *d = D_80084B14;
    u8 *p, *fin;
    s32 hallado;

    while (*s >= 0x3B) {
        *d++ = *s++;
    }
    *d = 0;
    hallado = 0;
    p = *(u8 **)0x150;
    fin = p + (*(u32 *)0x154 / 0x50) * 0x50;
    for (; p < fin; p += 0x50) {
        if (*(char **)p != NULL && strcmp(*(char **)p, D_80084B14) == 0) {
            D_80084B0C = *(FuncDisp *)(p + 0x34);
            hallado = 1;
            break;
        }
    }
    if (!hallado) {
        return 0;
    }
    p = *(u8 **)0x150;
    fin = p + (*(u32 *)0x154 / 0x50) * 0x50;
    for (; p < fin; p += 0x50) {
        if (*(char **)p != NULL && strcmp(*(char **)p, D_80084B14) == 0) {
            *(FuncDisp *)(p + 0x34) = (FuncDisp)func_80014670;
            break;
        }
    }
    return firstfile2(nombre, archivo);
}
