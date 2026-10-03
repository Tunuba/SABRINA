#include "juego.h"

/* Reducir una imagen de 16 bits a una paleta (para texturas de 4 u 8 bits). */

extern char D_8006561C[];            /* el nombre del archivo fuente */
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern s32 Liberar(void *p);
extern s32 func_80014AEC(s32 x);     /* valor absoluto */

#define ROJO(c) (((c) & 0x7C00) >> 10)
#define VERDE(c) (((c) & 0x3C0) >> 5)  /* asi en el original (0x3C0, no 0x3E0) */
#define AZUL(c) ((c) & 0x1F)

/* Saca de la lista pal[0..n) el color j, corriendo los de despues. */
static inline void sacar(u16 *pal, u32 j, u32 n) {
    u32 m;
    for (m = j; m < n - 1; m++) {
        pal[m] = pal[m + 1];
    }
}

/* img tiene n pixeles; la cabecera dice cuantos colores caben (0x1A) y si la textura es de 8 bits (0x1D).
 * Junta en pal los colores distintos; mientras sobren, une los que se parecen (con una tolerancia que va
 * subiendo de a uno; ojo, el original toma el valor absoluto del canal del primero y no de la diferencia);
 * despues le da a cada pixel el color mas cercano (hasta 10 por canal; si no hay, el de antes). Libera img y
 * devuelve los indices (8 bits) o empaquetados de a dos por byte (4 bits). */
u8 *func_8001A754(u8 *cab, u16 *img, u16 *pal, s32 n) {
    u8 *idx;
    u8 *paq;
    s32 i, k;
    u32 j, cant;
    s16 tol, dr, dg, db, mr, mg, mb;
    s32 hallado;
    u16 a, b;

    tol = 1;
    cant = 0;
    idx = Reservar(n, D_8006561C, 0x230);
    paq = Reservar(n / 2, D_8006561C, 0x231);
    for (i = 0; i != n; i++) {
        idx[i] = 0;
    }
    for (i = 0; i != n; i++) {
        if (idx[i] == 0) {
            pal[cant] = img[i];
            for (j = i; j < (u32)n; j++) {
                if (img[i] == img[j]) {
                    idx[j] = 1;
                }
            }
            cant++;
        }
    }
    while (*(u16 *)(cab + 0x1A) < cant) {
        for (i = 0, k = 1; (u32)i < cant && cant != *(u16 *)(cab + 0x1A); i++, k++) {
            for (j = k; j < cant && cant != *(u16 *)(cab + 0x1A); j++) {
                a = pal[i];
                b = pal[j];
                if (a == 0 || b == 0) {
                    if (a == b) {
                        sacar(pal, j, cant);
                        cant--;
                    }
                    continue;
                }
                dr = RESTA_TRAMPA(func_80014AEC(ROJO(a)), ROJO(pal[j]));
                dg = RESTA_TRAMPA(func_80014AEC(VERDE(pal[i])), VERDE(pal[j]));
                db = RESTA_TRAMPA(func_80014AEC(AZUL(pal[i])), AZUL(pal[j]));
                if (tol < dr || tol < dg || tol < db) {
                    continue;
                }
                sacar(pal, j, cant);
                cant--;
            }
        }
        tol = SUMA_TRAMPA(tol, 1);
    }
    for (i = 0; i != n; i++) {
        mr = mg = mb = 10;
        hallado = 0;
        for (j = 0; j != *(u16 *)(cab + 0x1A) && !hallado; j++) {
            dr = func_80014AEC(RESTA_TRAMPA(ROJO(img[i]), ROJO(pal[j])));
            dg = func_80014AEC(RESTA_TRAMPA(VERDE(img[i]), VERDE(pal[j])));
            db = func_80014AEC(RESTA_TRAMPA(AZUL(img[i]), AZUL(pal[j])));
            if (mr < dr || mg < dg || mb < db) {
                continue;
            }
            mr = dr;
            mg = dg;
            mb = db;
            if (SUMA_TRAMPA(db, SUMA_TRAMPA(dr, dg)) <= 0) {
                hallado = 1;
            }
            cant = j;
        }
        idx[i] = cant;
    }
    if (cab[0x1D] == 0) {
        for (i = 0, k = 0; (u32)i < (u32)n; i += 2, k++) {
            paq[k] = idx[i] | (idx[i + 1] << 4);
        }
        Liberar(idx);
        Liberar(img);
        return paq;
    }
    Liberar(paq);
    Liberar(img);
    return idx;
}
