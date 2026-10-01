#include "banco.h"

/* El banco de memoria (membank.cpp): reservar. */

/* Afirmar(cond, archivo, linea): si cond es 0 avisa del fallo. */
extern s32 Afirmar(s32 cond, const char *archivo, s32 linea);
extern char D_800758EC[];            /* "membank.cpp" */

/* De donde saca memoria nueva el banco cuando no le alcanza (un objeto con su tabla de funciones). */
typedef struct Proveedor {
    struct ProveedorTabla *t;
} Proveedor;
typedef struct ProveedorTabla {
    void *_00[3];
    Bloque *(*pedir)(Proveedor *p, u32 tam);  /* 0x0C */
} ProveedorTabla;

extern s32 func_8004E2A4(u32 tam);   /* la clase de un tamano */
extern Bloque *func_8004E774(Banco *b, s32 clase);
extern void func_8004E7FC(Banco *b, Bloque *bl, u32 tam);
extern void func_8004E86C(Banco *b, Bloque *bl, s32 clase);
extern Bloque *func_80017CBC(u32 tam);  /* memoria del sistema (malloc de la BIOS) */

typedef struct {
    s32 v;
} __attribute__((packed)) PalabraSueltaG13;

/* La copia del tamano al final del bloque (la cabecera lleva el bit de ocupado: por eso el -5). */
#define PONER_PIE(bl) (((PalabraSueltaG13 *)((u8 *)(bl) + (bl)->cab - 5))->v = (bl)->cab)

/* Reserva tam bytes (redondeado a 4 con la cabecera, minimo 0x10). Busca en la clase siguiente; si no hay
 * y el banco lo permite (byte 0x100) revisa los de su misma clase que alcancen; si tampoco, pide al menos
 * 0x20000 bytes nuevos (al proveedor o al sistema) y los pega al final del monton. Devuelve el espacio
 * del usuario (detras de la cabecera) o NULL. */
void *func_8004E32C(Banco *b, u32 tam) {
    Bloque *bl, *chicos, *sig, *f;
    Proveedor *pv;
    s32 clase;
    u32 t, n;
    u8 *p;

    t = (tam + 0xB) & ~3;
    if (t < 0x10) {
        t = 0x10;
    }
    clase = func_8004E2A4(t);
    if (clase >= 0x38) {
        return NULL;
    }
    bl = func_8004E774(b, clase + 1);
    if (bl != NULL) {
        func_8004E7FC(b, bl, t);
    } else {
        if (((u8 *)b)[0x100] != 0) {
            chicos = NULL;
            while ((bl = func_8004E774(b, clase)) != NULL && (u32)bl->cab < t) {
                bl->sig = chicos;
                chicos = bl;
            }
            while (chicos != NULL) {
                sig = chicos->sig;
                func_8004E86C(b, chicos, clase);
                chicos = sig;
            }
            if (bl != NULL) {
                func_8004E7FC(b, bl, t);
            }
        }
        if (bl == NULL) {
            n = t + 8;
            if (n < 0x20000) {
                n = 0x20000;
            }
            pv = *(Proveedor **)b;
            if (pv != NULL) {
                bl = pv->t->pedir(pv, n);
            } else {
                /* func_80017CBC pasa a la BIOS (malloc), que en el emulador vuelve enseguida con el v0 que
                 * traia: el original llega con v0 = pv (NULL), asi que se llama igual */
                __asm__ volatile(".set noreorder\n\tmove $2, %1\n\tjal func_80017CBC\n\tmove $4, %2\n\t"
                                 ".set reorder\n\tmove %0, $2"
                                 : "=&r"(bl)
                                 : "r"(pv), "r"(n)
                                 : "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12",
                                   "$13", "$14", "$15", "$24", "$25", "$31", "hi", "lo", "memory");
            }
            if (bl != NULL) {
                Afirmar(((u32)bl & 3) == 0, D_800758EC, 0xC7);
                f = (Bloque *)b->fin;
                if (f != NULL && (u8 *)bl != (u8 *)f + 4) {
                    f->cab = ((u8 *)bl - (u8 *)f) + 5;
                    PONER_PIE(f);
                    bl = (Bloque *)((u8 *)bl + 4);
                    bl->cab = n - 7;
                } else if (f != NULL) {
                    bl = f;
                    f->cab = n + 1;
                } else {
                    bl = (Bloque *)((u8 *)bl + 4);
                    bl->cab = n - 7;
                }
                PONER_PIE(bl);
                b->fin = (u8 *)bl + bl->cab - 1;
                if (b->ini == NULL) {
                    b->ini = (u8 *)bl;
                }
                func_8004E7FC(b, bl, t);
            }
        }
    }
    if (bl != NULL) {
        p = (u8 *)bl + 4;
        b->usado += bl->cab;
    } else {
        p = NULL;
    }
    Afirmar(((u32)p & 3) == 0, D_800758EC, 0x10A);
    return p;
}
