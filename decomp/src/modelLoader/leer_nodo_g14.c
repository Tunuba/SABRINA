#include "juego.h"

/* Lectura de un arbol de nodos de modelo desde un archivo abierto. */

extern char D_80068830[];            /* el nombre del archivo fuente */
extern char D_8007C7D8[];            /* aviso de nodo sin nombre */
extern void ArchivoLeer(s32 arch, void *dest, s32 n);
extern u8 *func_8001E164(u8 *padre); /* nodo nuevo en blanco, ultimo hijo de padre */
extern void func_8001E2DC(u8 *n, char *nombre);
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void Liberar(void *p);
extern void Afirmar(void *p, char *archivo, s32 linea);
extern u8 *TexturaPorIndice(s32 i);
extern s32 printf(char *fmt, ...);

#define CAMPO(tipo, n, desp) (*(tipo *)((u8 *)(n) + (desp)))

/* Lee nodos como hijos de padre: por cada uno la cantidad de puntos (negativa = fin de la lista), la de
 * triangulos, la de hijos, la matriz local, el nombre y, despues de los hijos (leidos por recursion), los
 * triangulos y los puntos. Los triangulos guardan indices de puntos que pasan a ser punteros, y su textura
 * por indice pasa a ser puntero sumandole a sus coordenadas el origen de la textura. Con varios != 0 sigue
 * leyendo hermanos hasta el fin de la lista. Devuelve el ultimo nodo leido (si no leyo ninguno, lo que
 * traia s1 el que llama, como el original). */
u8 *LeerNodoModelo(s32 arch, u8 *padre, s32 varios) {
    u8 *n;
    u8 *nombre;
    u8 *t;
    s16 hijos;
    s16 k;

    __asm__ volatile("move %0, $s1" : "=r"(n));
    for (;;) {
        ArchivoLeer(arch, &k, 2);
        if (k < 0) {
            return n;
        }
        n = func_8001E164(padre);
        Afirmar(n, D_80068830, 0x8F);
        CAMPO(s16, n, 0x5C) = k;
        ArchivoLeer(arch, n + 0x5E, 2);
        ArchivoLeer(arch, &hijos, 2);
        ArchivoLeer(arch, n + 0x14, 0x20);
        ArchivoLeer(arch, &k, 2);
        if (k != 0) {
            nombre = Reservar(k + 1, D_80068830, 0x99);
            ArchivoLeer(arch, nombre, k);
            nombre[k] = 0;
            func_8001E2DC(n, (char *)nombre);
            Liberar(nombre);
        } else {
            printf(D_8007C7D8);
        }
        while (hijos-- != 0) {
            LeerNodoModelo(arch, n, 0);
        }
        CAMPO(u8 *, n, 0x58) = Reservar(CAMPO(s16, n, 0x5E) * 0x1C, D_80068830, 0xA3);
        Afirmar(CAMPO(u8 *, n, 0x58), D_80068830, 0xA4);
        ArchivoLeer(arch, CAMPO(u8 *, n, 0x58), CAMPO(s16, n, 0x5E) * 0x1C);
        CAMPO(u8 *, n, 0x54) = Reservar(CAMPO(s16, n, 0x5C) * 0xC, D_80068830, 0xA7);
        Afirmar(CAMPO(u8 *, n, 0x54), D_80068830, 0xA8);
        ArchivoLeer(arch, CAMPO(u8 *, n, 0x54), CAMPO(s16, n, 0x5C) * 0xC);
        t = CAMPO(u8 *, n, 0x58);
        for (k = 0; k < CAMPO(s16, n, 0x5E); k++) {
            CAMPO(u8 *, t, 0) = CAMPO(u8 *, n, 0x54) + CAMPO(s32, t, 0) * 0xC;
            CAMPO(u8 *, t, 4) = CAMPO(u8 *, n, 0x54) + CAMPO(s32, t, 4) * 0xC;
            CAMPO(u8 *, t, 8) = CAMPO(u8 *, n, 0x54) + CAMPO(s32, t, 8) * 0xC;
            CAMPO(u8 *, t, 0xC) = TexturaPorIndice(CAMPO(s32, t, 0xC));
            t[0x10] += CAMPO(u8 *, t, 0xC)[0x10];
            t[0x11] += CAMPO(u8 *, t, 0xC)[0x11];
            t[0x12] += CAMPO(u8 *, t, 0xC)[0x10];
            t[0x13] += CAMPO(u8 *, t, 0xC)[0x11];
            t[0x14] += CAMPO(u8 *, t, 0xC)[0x10];
            t[0x15] += CAMPO(u8 *, t, 0xC)[0x11];
            t += 0x1C;
        }
        n[0x64] |= 8;
        if (varios == 0) {
            return n;
        }
    }
}
