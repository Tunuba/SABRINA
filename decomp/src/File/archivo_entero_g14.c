#include "juego.h"

/* BasicTools.c: cargar un archivo entero del CD a un bloque nuevo. */

typedef struct {
    u8 pos[4];                          /* 0x00, CdlLOC */
    u32 tam;                            /* 0x04 */
    char nombre[16];                    /* 0x08 */
} CdArchivoG14;

extern char D_8007C774[];               /* "\%s;1" */
extern char D_800653F8[];               /* "BasicTools.c" */

extern void *memset(void *p, s32 c, u32 n);
extern s32 sprintf(char *d, const char *f, ...);
extern void func_80017D3C(char *nombre);
extern s32 func_8002BE88(CdArchivoG14 *a, char *nombre);   /* CdSearchFile */
extern s32 CdPosToInt(void *pos);
extern void func_80029F18(s32 sector, u8 *pos);             /* CdIntToPos */
extern s32 func_80029D28(s32 orden, u8 *param, u8 *resultado);  /* CdControl */
extern s32 CdRead(s32 sectores, void *destino, s32 modo);
extern s32 CdReadSync(s32 modo, u8 *resultado);
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void Liberar(void *p);

/* Busca el archivo (10 intentos), reserva su tamano, se pone en su primer sector (CdlSetloc, 10 intentos)
 * y lo lee (10 intentos). Devuelve el bloque, o 0 si fallo (lo libera). Lee un sector menos que los que
 * ocupa el archivo, como el original. */
void *func_80017D80(char *nombre) {
    CdArchivoG14 a;
    char ruta[0x80];
    u8 pos[4];
    void *datos;
    s32 primero;
    s32 ultimo;
    s32 listo;
    s8 i;

    i = 0;
    listo = 0;
    memset(&a, 0, 0x18);
    func_80017D3C(nombre);
    sprintf(ruta, D_8007C774, nombre);
    do {
        func_8002BE88(&a, ruta);
        i++;
    } while (a.tam == 0 && i < 10);
    primero = CdPosToInt(a.pos);
    ultimo = primero + ((a.tam + 0x7FF) >> 11) - 1;
    datos = Reservar(a.tam, D_800653F8, 0x6F);
    i = 0;
    if ((u32) ultimo < (u32) primero) {
        Liberar(datos);
        return 0;
    }
    func_80029F18(primero, pos);
    do {
        if (func_80029D28(0x15, pos, 0) != 0) {
            listo = 1;
        }
        i++;
    } while (listo == 0 && i < 10);
    if (listo == 0) {
        Liberar(datos);
        return 0;
    }
    i = 0;
    listo = 0;
    do {
        if (CdRead(ultimo - primero, datos, 0x80) != 0) {
            listo = 1;
        }
        i++;
    } while (listo == 0 && i < 10);
    if (listo == 0) {
        Liberar(datos);
        return 0;
    }
    while (CdReadSync(1, 0) > 0) {
    }
    return datos;
}
