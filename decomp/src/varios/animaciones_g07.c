#include "juego.h"

/* Carga de animaciones (.ANI): un archivo con varias animaciones MAO seguidas. Cada una la lee LeerMAO
 * y la deja en el bloque de D_800C4E2C, avanzando D_8007CB64 (ver func_8002EC1C). */

extern u8 D_800C4E2C[];              /* bloque de animaciones */
extern u8 *D_8007CB64;               /* primer lugar libre del bloque */
extern char D_8006D5F8[];            /* "anims\%s" */

extern void ArchivoIniciar(void *archivo);
extern void ArchivoAbrir(void *archivo, char *ruta, s32 modo);
extern void ArchivoCerrar(void *archivo, s32 liberar);
extern s32 sprintf(char *destino, const char *formato, ...);
extern void LeerMAO(void *archivo);

/* Abre anims\<nombre> y lee n animaciones. En indices[i] deja donde empieza cada una dentro del bloque,
 * en palabras de 4 bytes. Devuelve 1. */
s32 CargarANI(s32 a0, s32 n, char *nombre, s16 *indices) {
    u8 archivo[0xA0];
    char ruta[0x80];
    s32 i;

    ArchivoIniciar(archivo);
    sprintf(ruta, D_8006D5F8, nombre);
    ArchivoAbrir(archivo, ruta, 1);
    for (i = 0; i < n; i++) {
        *indices++ = (s32)(D_8007CB64 - D_800C4E2C) / 4;
        LeerMAO(archivo);
    }
    ArchivoCerrar(archivo, -1);
    return 1;
}

/* Las 8 animaciones del caos (mao_chaos: 8 palabras que se copian a la pila y CargarANI no mira). */
extern s32 mao_chaos[8];
extern char D_8006EDB4[];            /* nombre del .ANI */
extern u16 D_80093CF4, D_80093CF6, D_80093CF8, D_80093CFA, D_80093CFC, D_80093CFE, D_80093D00, D_80093D02;

/* Carga las 8 animaciones y guarda donde empieza cada una; la cuarta y la quinta van cruzadas. */
void func_8002FE64(void) {
    s32 copia[8];
    s16 indices[8];
    s32 i;

    for (i = 0; i < 8; i++) {
        copia[i] = mao_chaos[i];
    }
    CargarANI((s32)copia, 8, D_8006EDB4, indices);
    D_80093CF4 = indices[0];
    D_80093CF6 = indices[1];
    D_80093CF8 = indices[2];
    D_80093CFC = indices[3];
    D_80093CFA = indices[4];
    D_80093CFE = indices[5];
    D_80093D00 = indices[6];
    D_80093D02 = indices[7];
}
