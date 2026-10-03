#include "juego.h"

/* Herramienta de desarrollo: convierte un grupo de texturas y lo guarda en un archivo. */

extern char **D_8006CDD4[];          /* por grupo, la lista de nombres de textura (termina en 0) */
extern char D_8007C86C[];            /* el formato del nombre completo */
extern char D_8007C9D4[];            /* la carpeta */
extern s32 sprintf(char *dest, char *fmt, ...);
extern void *func_8001B0C8(char *nombre);              /* lee y convierte una textura */
extern s32 func_80029530(s32 arch, void *datos, s32 n); /* escribir */

/* Convierte las texturas del grupo (arma cada nombre aunque la lista este vacia, como el original) y escribe
 * en arch la cantidad (2 bytes) y despues 32 bytes de cada una. */
void func_80024450(s32 grupo, s32 arch) {
    char **lista = D_8006CDD4[grupo];
    s32 n = 0;
    void *tex[100];
    char nombre[0x80];
    s32 i;

    do {
        sprintf(nombre, D_8007C86C, D_8007C9D4, lista[n]);
        if (lista[n] != 0) {
            tex[n++] = func_8001B0C8(nombre);
        }
    } while (lista[n] != 0);
    func_80029530(arch, &n, 2);
    for (i = 0; i != n; i++) {
        func_80029530(arch, tex[i], 0x20);
    }
}
