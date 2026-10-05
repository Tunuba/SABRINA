#include "juego.h"

/* Herramienta de desarrollo: copia un modelo .bud del archivo arch a la PC (pc), objeto por objeto. Cada objeto:
 * vertices, poligonos e hijos (2 bytes cada uno, -1 en vertices termina), 32 bytes, el largo del nombre (2) y el
 * nombre, los hijos (cada uno igual, de a uno), los poligonos (0x1C bytes; al byte bajo de la palabra de +0xC
 * le suma base, el primer numero de textura del modelo) y los vertices (0xC bytes). Con todos != 0 sigue con el
 * objeto siguiente hasta el -1; los hijos se leen de a uno. */

extern char D_80068830[];               /* el nombre del archivo fuente */

extern void ArchivoLeer(void *a, void *d, s32 n);
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void Liberar(void *p);
extern void Afirmar(void *cond, char *archivo, s32 linea);
extern s32 func_80029530(s32 arch, void *datos, s32 n);  /* PCwrite */

void func_8001CB4C(void *arch, s32 todos, s32 pc, s32 base) {
    u8 cabecera[0x20];
    s16 hijos;
    s16 poligonos;
    s16 vertices;
    s16 n;
    u8 *datos;
    u8 *p;

    do {
        ArchivoLeer(arch, &vertices, 2);
        func_80029530(pc, &vertices, 2);
        if (vertices < 0) {
            return;
        }
        ArchivoLeer(arch, &poligonos, 2);
        func_80029530(pc, &poligonos, 2);
        ArchivoLeer(arch, &hijos, 2);
        func_80029530(pc, &hijos, 2);
        ArchivoLeer(arch, cabecera, 0x20);
        func_80029530(pc, cabecera, 0x20);
        ArchivoLeer(arch, &n, 2);
        func_80029530(pc, &n, 2);
        if (n != 0) {
            datos = Reservar(n + 1, D_80068830, 0x10A);
            ArchivoLeer(arch, datos, n);
            func_80029530(pc, datos, n);
            Liberar(datos);
        }
        while (hijos-- != 0) {
            func_8001CB4C(arch, 0, pc, base);
        }
        datos = Reservar(poligonos * 0x1C, D_80068830, 0x112);
        Afirmar(datos, D_80068830, 0x113);
        ArchivoLeer(arch, datos, poligonos * 0x1C);
        p = datos;
        for (n = 0; n < poligonos; n++) {
            *(u32 *) (p + 0xC) = ((*(u32 *) (p + 0xC) & 0xFF) + (base & 0xFF)) & 0xFF;
            p += 0x1C;
        }
        func_80029530(pc, datos, poligonos * 0x1C);
        Liberar(datos);
        datos = Reservar(vertices * 0xC, D_80068830, 0x122);
        Afirmar(datos, D_80068830, 0x123);
        ArchivoLeer(arch, datos, vertices * 0xC);
        func_80029530(pc, datos, vertices * 0xC);
        Liberar(datos);
    } while (todos != 0);
}
