#include "juego.h"

/* WobjCode.c: cargar los objetos del mundo (WRLDDATA\<nivel>.BIN) y los puntos de las rutas. */

extern char D_8007C894[];            /* "%s%s" */
extern char D_8007A1DC[];            /* "WRLDDATA\" */
extern char D_8006CF3C[];            /* "WobjCode.c" */
extern s32 D_8007CB3C;               /* cuantos objetos */
extern u8 *D_8007CB40;               /* los objetos (0x9C bytes cada uno) */
extern s32 D_8007CCAC;               /* cuantos puntos de ruta */
extern u8 puntos_ruta[];             /* 0x18 bytes cada uno */

extern void ArchivoIniciar(void *archivo);
extern void ArchivoAbrir(void *archivo, char *ruta, s32 modo);
extern void ArchivoLeer(void *archivo, void *destino, s32 tam);
extern void ArchivoCerrar(void *archivo, s32 liberar);
extern s32 sprintf(char *destino, const char *formato, ...);
extern char *func_80014FF0(char *s, s32 c);                /* strrchr */
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void *memset(void *p, s32 c, u32 n);
extern void CrearObjetoMundo(u8 *objeto);

/* Lee la cantidad y los objetos, la cantidad y los puntos de ruta, y crea los dos primeros objetos. */
__attribute__((noinline, used)) static void cargar_wrlddata(char *nombre, char *ruta) {
    u8 *archivo = (u8 *) ruta + 0x80;
    char *punto;
    s32 tam;

    ArchivoIniciar(archivo);
    sprintf(ruta, D_8007C894, D_8007A1DC, nombre);
    punto = func_80014FF0(ruta, '.');
    punto[1] = 'B';
    punto[2] = 'I';
    punto[3] = 'N';
    ArchivoAbrir(archivo, ruta, 1);
    ArchivoLeer(archivo, &D_8007CB3C, 4);
    tam = D_8007CB3C * 0x9C;
    D_8007CB40 = Reservar(tam, D_8006CF3C, 0x3D);
    memset(D_8007CB40, 0, tam);
    ArchivoLeer(archivo, D_8007CB40, tam);
    ArchivoLeer(archivo, &D_8007CCAC, 4);
    if (D_8007CCAC != 0) {
        ArchivoLeer(archivo, puntos_ruta, D_8007CCAC * 0x18);
    }
    CrearObjetoMundo(D_8007CB40);
    CrearObjetoMundo(D_8007CB40 + 0x9C);
    ArchivoCerrar(archivo, -1);
}

/* La ruta y el archivo van en sp+0x18 y sp+0x98 de un marco de 0x138, como en el original (las funciones
 * del archivo leen bytes de ahi sin llenarlos). El marco va a mano. */
__attribute__((naked))
void CargarWRLDDATA(char *nombre) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x138\n"
            "\tsw $31, 0x14($sp)\n"
            "\tjal cargar_wrlddata\n"
            "\taddiu $5, $sp, 0x18\n"
            "\tlw $31, 0x14($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x138\n"
            ".set reorder");
}
