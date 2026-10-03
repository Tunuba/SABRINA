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

extern char **D_8007C6BC[];          /* por nivel, la lista de nombres de modelo (termina en 0) */
extern char D_8006886C[];            /* el nombre del archivo fuente */
extern s8 nivel_actual;
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern s32 Liberar(void *p);
extern void Afirmar(s32 cond, char *archivo, s32 linea);
extern void *func_8001B698(char *nombre);              /* lee y convierte un modelo */

/* Convierte los modelos del nivel actual (como mucho 50) y escribe en arch la cantidad (2 bytes) y 32
 * bytes de cada uno, liberandolos. */
void func_8001F524(s32 arch) {
    char **lista = D_8007C6BC[nivel_actual];
    s32 n = 0;
    void **m;
    s32 i;

    while (lista[n] != 0) {
        n++;
    }
    m = Reservar((n + 1) * 4, D_8006886C, 0x21A);
    n = 0;
    do {
        if (lista[n] != 0) {
            m[n] = func_8001B698(lista[n]);
        }
        n++;
        if ((u32)n >= 0x32) {
            Afirmar(0, D_8006886C, 0x220);
        }
    } while (lista[n] != 0);
    func_80029530(arch, &n, 2);
    for (i = 0; i != n; i++) {
        func_80029530(arch, m[i], 0x20);
        Liberar(m[i]);
    }
    Liberar(m);
}
