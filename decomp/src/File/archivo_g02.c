#include "juego.h"

int printf(const char *formato, ...);
void Liberar(void *p);
void func_80017CE4(void *p);            /* suelta la memoria del propio archivo */

extern char D_80065474[];               /* "Deleting file %s...\n" */
extern char D_8006548C[];               /* "WARNING: file %s data not deleted\n \n" */

/* Lo que se sabe del archivo abierto. */
typedef struct {
    void *datos;                        /* 0x00, lo leido */
    u8 _04[0x10];
    u8 borrado;                         /* 0x14, si los datos se soltaron */
    char nombre[1];                     /* 0x15 */
} Archivo;
EN(Archivo, borrado, 0x14);
EN(Archivo, nombre, 0x15);

/* Suelta los datos del archivo y, si liberar > 0, tambien el archivo. Devuelve el mismo puntero. */
Archivo *ArchivoCerrar(Archivo *a, s32 liberar) {
    if (a != NULL) {
        if (a->datos != NULL) {
            Liberar(a->datos);
            a->datos = NULL;
        }
        if (a->borrado) {
            printf(D_80065474, a->nombre);
        } else {
            printf(D_8006548C, a->nombre);
        }
        if (liberar > 0) {
            func_80017CE4(a);
        }
    }
    return a;
}
