#include "juego.h"

/* Reservar y Liberar: el malloc y el free del juego, con nombre de archivo (y linea, que no se usa).
 * Con D_8007CC24 en 1 anotan cada reserva en una tabla de 2000 registros para depurar. */

/* Un registro de la tabla de reservas (16 bytes). */
typedef struct {
    void *p;                         /* 0x00, lo reservado */
    char *archivo;                   /* 0x04, copia del nombre */
    s32 _08;                         /* 0x08, si no es 0 avisa */
    s32 tam;                         /* 0x0C */
} RegReserva;

/* El montón de memoria: una clase con su tabla de metodos en +8; el de reservar esta en +0x30 y el
 * de liberar en +0x38. */
typedef struct Monton Monton;
typedef struct {
    u8 _00[0x30];
    void *(*reservar)(Monton *m, s32 tam);
    u8 _34[4];
    void (*liberar)(Monton *m, void *p);
} MetodosMonton;
struct Monton {
    u8 _00[8];
    MetodosMonton *metodos;          /* 0x08 */
};

extern RegReserva D_800C98D4[2000];
extern u32 D_8007CC20;               /* cuantos registros hay */
extern u8 D_8007CC24;                /* 1: anotar las reservas */
extern s32 D_8007CC28;               /* cuanto se lleva reservado */
extern u8 D_8007C8E0;                /* distinto de 0: usar func_800161BC en vez del monton */
extern Monton *D_8007C9DC;
extern char D_80075844[];
extern char D_8007585C[];
extern char D_8007587C[];
extern char D_80075894[];

extern s32 printf(const char *formato, ...);
extern s32 func_800150F0(char *s);   /* strlen */
extern void *func_800161BC(s32 tam);
extern char *strcpy(char *d, const char *s);
extern void func_800161C8(void *p);

/* func_800161BC va al malloc de la BIOS, que en el emulador vuelve enseguida con el v0 que traia: se llama
 * con el v0 que deja el original en cada lugar. */
static void *malloc_bios(s32 tam, s32 v0) {
    void *p;

    __asm__ volatile(".set noreorder\n\tmove $2, %1\n\tjal func_800161BC\n\tmove $4, %2\n\t.set reorder\n\t"
                     "move %0, $2"
                     : "=&r"(p)
                     : "r"(v0), "r"(tam)
                     : "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13",
                       "$14", "$15", "$24", "$25", "$31", "hi", "lo", "memory");
    return p;
}

void *Reservar(s32 tam, char *archivo) {
    void *p;

    D_8007CC28 += tam;
    if (D_8007CC24 != 1) {
        if (D_8007C8E0 == 0) {
            return D_8007C9DC->metodos->reservar(D_8007C9DC, tam);
        }
        return malloc_bios(tam, D_8007C8E0);
    }
    if (D_800C98D4[D_8007CC20].archivo != NULL) {
        printf(D_80075844);
    }
    if (D_800C98D4[D_8007CC20]._08 != 0) {
        printf(D_80075844);
    }
    if (archivo != NULL) {
        if (D_8007C8E0 != 0) {
            p = func_800150F0(archivo);
            p = malloc_bios((s32)p + 1, (s32)p);
            D_800C98D4[D_8007CC20].archivo = p;
        }
        strcpy(D_800C98D4[D_8007CC20].archivo, archivo);
    } else {
        printf(D_8007585C);
    }
    D_800C98D4[D_8007CC20].tam = tam;
    if (D_8007C8E0 == 0) {
        p = D_8007C9DC->metodos->reservar(D_8007C9DC, tam);
    } else {
        p = malloc_bios(tam, D_8007C8E0);
    }
    D_800C98D4[D_8007CC20].p = p;
    D_8007CC20++;
    if (D_8007CC20 == 2000) {
        printf(D_8007587C);
        for (;;) {
        }
    }
    return D_800C98D4[D_8007CC20 - 1].p;
}

/* Suelta p. Con la tabla, quita su registro (corre los de atras un lugar; el que queda en su lugar ya no
 * se revisa) y suelta tambien la copia del nombre; si p no estaba en la tabla solo avisa. */
void Liberar(void *p) {
    RegReserva copia;
    u32 i, j, n;
    s32 hallado = 0;

    if (D_8007CC24 != 1) {
        if (D_8007C8E0 == 0) {
            D_8007C9DC->metodos->liberar(D_8007C9DC, p);
        } else {
            func_800161C8(p);
        }
        return;
    }
    for (i = 0; i < D_8007CC20; i++) {
        if (D_800C98D4[i].p != p) {
            continue;
        }
        D_8007CC28 -= D_800C98D4[i].tam;
        copia.p = D_800C98D4[i].p;
        copia.archivo = D_800C98D4[i].archivo;
        copia._08 = D_800C98D4[i]._08;
        copia.tam = D_800C98D4[i].tam;
        if (D_800C98D4[i].archivo != NULL && D_8007C8E0 != 0) {
            copia.archivo = func_800161BC(func_800150F0(D_800C98D4[i].archivo) + 1);
            strcpy(copia.archivo, D_800C98D4[i].archivo);
            func_800161C8(D_800C98D4[i].archivo);
        }
        if (D_8007C8E0 == 0) {
            D_8007C9DC->metodos->liberar(D_8007C9DC, p);
        } else {
            func_800161C8(p);
        }
        n = D_8007CC20;
        for (j = i + 1; j < n; j++) {
            D_800C98D4[j - 1].p = D_800C98D4[j].p;
            D_800C98D4[j - 1].archivo = D_800C98D4[j].archivo;
            D_800C98D4[j - 1]._08 = D_800C98D4[j]._08;
            D_800C98D4[j - 1].tam = D_800C98D4[j].tam;
        }
        D_8007CC20--;
        D_800C98D4[D_8007CC20].archivo = NULL;
        D_800C98D4[D_8007CC20]._08 = 0;
        D_800C98D4[D_8007CC20].p = NULL;
        hallado = 1;
    }
    if (!hallado) {
        printf(D_80075894);
        return;
    }
    if (copia.archivo != NULL && D_8007C8E0 != 0) {
        func_800161C8(copia.archivo);
    }
}
