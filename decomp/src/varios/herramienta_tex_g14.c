#include "juego.h"

/* Herramienta de desarrollo: convierte un grupo de texturas y lo guarda en un archivo. */

extern char **D_8006CDD4[];          /* por grupo, la lista de nombres de textura (termina en 0) */
extern char D_8007C86C[];            /* el formato del nombre completo */
extern char D_8007C9D4[];            /* la carpeta */
extern s32 sprintf(char *dest, char *fmt, ...);
extern void *func_8001B0C8(char *nombre);              /* lee y convierte una textura */
extern s32 func_80029530(s32 arch, void *datos, s32 n); /* escribir */

/* Un lugar del marco del original: el cuerpo corre con el mismo sp (ver func_80024450 abajo). */
#define PILA(off) ({ u8 *_p; __asm__ volatile("addiu %0, $sp, " #off : "=r"(_p)); _p; })
#define N (*(s32 *) PILA(0x20))            /* cuantas lleva */
#define TEX ((void **) PILA(0x24))         /* hasta 100 */
#define NOMBRE ((char *) PILA(0x1B4))
#define DESDE (*(s32 *) PILA(0x234))       /* el recorrido del final, en bytes */
#define DIR(x) ({ void *_d; __asm__ volatile("la %0, " #x : "=r"(_d)); _d; })  /* sin guardarla en un registro */

/* Convierte las texturas del grupo (arma cada nombre aunque la lista este vacia, como el original) y escribe
 * en arch la cantidad (2 bytes) y despues 32 bytes de cada una. */
__attribute__((noinline, used)) static void convertir_grupo(s32 grupo, s32 arch) {
    char **lista = D_8006CDD4[grupo];
    s32 k;

    N = 0;
    do {
        sprintf(NOMBRE, DIR(D_8007C86C), DIR(D_8007C9D4), lista[N]);
        if (lista[N] != 0) {
            void *t = func_8001B0C8(NOMBRE);
            k = N;
            N = k + 1;
            TEX[k] = t;
        }
    } while (lista[N] != 0);
    func_80029530(arch, &N, 2);
    DESDE = 0;
    for (k = 0; k != N; k++) {
        func_80029530(arch, *(void **) ((u8 *) TEX + DESDE), 0x20);
        DESDE += 4;
    }
}

/* func_8001B0C8 usa el s4 del que llama y la pila de abajo: el cuerpo corre con el sp del original (0x238 =
 * 0x218 de este marco + 0x20 del cuerpo) y solo con s0 y s1, como el original. ra va en sp-0x10 (sp+0x10
 * del cuerpo, que GCC deja libre: guarda s0, s1 y ra en 0x14-0x1C). */
__attribute__((naked))
void func_80024450(s32 grupo, s32 arch) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x218\n"
            "\tsw $31, -0x10($sp)\n"
            "\tjal convertir_grupo\n"
            "\tnop\n"
            "\tlw $31, -0x10($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x218\n"
            ".set reorder");
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
