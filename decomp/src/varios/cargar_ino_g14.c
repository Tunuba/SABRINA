#include "juego.h"

/* Carga un .INO (los graficos de un nivel): la cuadricula, los sprites, los modelos, la letra y las
 * particulas, en ese orden, del mismo archivo. */

extern char D_8007C784[];            /* "%s%s" */
extern char D_8007A1D0[];            /* la carpeta de los graficos */

extern void ArchivoIniciar(void *archivo);
extern void ArchivoAbrir(void *archivo, char *ruta, s32 modo);
extern void ArchivoCerrar(void *archivo, s32 liberar);
extern s32 sprintf(char *destino, const char *formato, ...);
extern char *func_80014FF0(char *s, s32 c);                /* strrchr */
extern void LeerCuadriculaINO(void *archivo);
extern void LeerSpritesINO(void *archivo);
extern void LeerModelosINO(void *archivo, s32 a);
extern void LeerLetraINO(void *archivo);
extern void LeerParticulasINO(void *archivo);

/* nombre trae cualquier extension (se cambia por INO, de 3 letras, despues del ultimo punto). */
void CargarINO(char *nombre, s32 a) {
    char ruta[0x80];
    u8 archivo[0xA0];
    char *punto;

    ArchivoIniciar(archivo);
    sprintf(ruta, D_8007C784, D_8007A1D0, nombre);
    punto = func_80014FF0(ruta, '.');
    punto[1] = 'I';
    punto[2] = 'N';
    punto[3] = 'O';
    ArchivoAbrir(archivo, ruta, 1);
    LeerCuadriculaINO(archivo);
    LeerSpritesINO(archivo);
    LeerModelosINO(archivo, a);
    LeerLetraINO(archivo);
    LeerParticulasINO(archivo);
    ArchivoCerrar(archivo, -1);
}
