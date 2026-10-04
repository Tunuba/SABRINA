#include "juego.h"

/* Herramienta de desarrollo: arma el archivo de modelos de un nivel en la PC. Por cada modelo de la lista
 * del nivel lee GRAPHICS\<modelo>.TNF (los nombres de sus texturas) y convierte cada textura; escribe la
 * cantidad de texturas, 32 bytes de cada una, la tabla de cuantas texturas hay antes de cada modelo y despues
 * cada GRAPHICS\<modelo>.bud pasado por func_8001CB4C. */

extern char **tabla_modelos_niveles[];  /* por nivel, la lista de modelos (termina en 0) */
extern char D_80068830[];               /* el nombre del archivo fuente */
extern char D_8007C7E0[];               /* "%s%s" */
extern char D_8007A1D0[];               /* "GRAPHICS\" */

extern void ArchivoIniciar(void *a);
extern void ArchivoAbrir(void *a, char *ruta, s32 modo);
extern void ArchivoLeer(void *a, void *d, s32 n);
extern void ArchivoCerrar(void *a, s32 n);
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void Liberar(void *p);
extern s32 sprintf(char *d, const char *f, ...);
extern char *func_80014FF0(char *s, s32 c);     /* strchr */
extern void *func_8001B600(u8 *nombre);         /* la textura de ese nombre */
extern void func_8001CB4C(void *a, s32 todos, s32 arch, s32 base);
extern s32 func_80029530(s32 arch, void *datos, s32 n);  /* PCwrite */

/* Un lugar del marco del original: el cuerpo corre con el mismo sp (ver HerramientaArmarModelos abajo). */
#define PILA(off) ({ u8 *_p; __asm__ volatile("addiu %0, $sp, " #off : "=r"(_p)); _p; })
#define DIR(x) ({ void *_d; __asm__ volatile("la %0, " #x : "=r"(_d)); _d; })  /* sin guardarla en un registro */
#define LETRA(x) ({ s32 _k; __asm__ volatile("li %0, " #x : "=r"(_k)); _k; })  /* idem para una constante */
#define CUENTA ((u16 *) PILA(0x38))             /* cuantas texturas hay antes de cada modelo (110) */
#define TEX ((void **) PILA(0x114))             /* las texturas (256) */
#define RUTA ((char *) PILA(0x514))
#define ARCH_TNF PILA(0x594)
#define ARCH_BUD PILA(0x634)
#define DESDE (*(s32 *) PILA(0x6D4))            /* el recorrido de TEX, en bytes */
#define TOTAL (*(u16 *) PILA(0x6DA))
#define NOMBRES (*(u16 *) PILA(0x6DC))
#define TAM (*(u16 *) PILA(0x6DE))

__attribute__((noinline, used)) static void armar_modelos(s32 arch, s32 nivel) {
    char **lista = tabla_modelos_niveles[nivel];
    char *modelo;
    u8 *datos;
    u8 *p;
    u16 i;
    u16 k;
    s32 off;                            /* func_8001B0C8 lee el s4 del que llama: en el original es este */
    s32 m;

    TOTAL = 0;
    i = 0;
    CUENTA[0] = 0;
    off = 0;
    do {
        modelo = lista[i++];
        off += 2;
        if (modelo != 0) {
            ArchivoIniciar(ARCH_TNF);
            sprintf(RUTA, DIR(D_8007C7E0), DIR(D_8007A1D0), modelo);
            p = (u8 *) func_80014FF0(RUTA, '.');
            p[1] = LETRA(0x54);              /* .TNF */
            p[2] = LETRA(0x4E);
            p[3] = LETRA(0x46);
            ArchivoAbrir(ARCH_TNF, RUTA, 1);
            ArchivoLeer(ARCH_TNF, &NOMBRES, 2);
            ArchivoLeer(ARCH_TNF, &TAM, 2);
            datos = Reservar(TAM, DIR(D_80068830), 0x175);
            ArchivoLeer(ARCH_TNF, datos, TAM);
            p = datos;
            while (NOMBRES-- != 0) {
                u8 *nombre = p + 1;
                void *t;

                p = nombre + *p;
                /* t = func_8001B600(nombre), con off en s4 */
                __asm__ volatile("move $4, %1\n\tmove $20, %2\n\tjal func_8001B600\n\tmove %0, $2"
                                 : "=r"(t) : "r"(nombre), "r"(off)
                                 : "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12",
                                   "$13", "$14", "$15", "$20", "$24", "$25", "$31", "hi", "lo", "memory");
                k = TOTAL;
                TOTAL = k + 1;
                TEX[k] = t;
            }
            Liberar(datos);
            ArchivoCerrar(ARCH_TNF, -1);
        }
        *(u16 *) ((u8 *) CUENTA + off) = TOTAL;
    } while (modelo != 0);

    func_80029530(arch, &TOTAL, 2);
    k = 0;
    DESDE = 0;
    while (k != TOTAL) {
        func_80029530(arch, *(void **) ((u8 *) TEX + DESDE), 0x20);
        k++;
        DESDE += 4;
    }
    func_80029530(arch, CUENTA, 0xDC);

    i = 0;
    m = -1;
    do {
        modelo = lista[i++];
        m++;
        if (modelo != 0) {
            ArchivoIniciar(ARCH_BUD);
            sprintf(RUTA, DIR(D_8007C7E0), DIR(D_8007A1D0), modelo);
            ArchivoAbrir(ARCH_BUD, RUTA, 1);
            func_8001CB4C(ARCH_BUD, 1, arch, CUENTA[m]);
            ArchivoCerrar(ARCH_BUD, -1);
        }
    } while (modelo != 0);
}

/* El cuerpo corre con el sp del original: 0x6E0 = 0x6A8 de este marco + 0x38 del cuerpo (s0-s7 y ra en
 * 0x14-0x34). ra va en sp-0x28 (sp+0x10 del cuerpo, que GCC deja libre). */
__attribute__((naked))
void HerramientaArmarModelos(s32 arch, s32 nivel) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x6A8\n"
            "\tsw $31, -0x28($sp)\n"
            "\tjal armar_modelos\n"
            "\tnop\n"
            "\tlw $31, -0x28($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x6A8\n"
            ".set reorder");
}
