#include "juego.h"

/* libgpu: la fuente de depuracion (FntOpen). */

typedef struct {
    s16 x, y, w, h;
} RectF;

/* Un flujo de texto de depuracion (0x30 bytes; hay 8 desde D_80063518 - 0x10). */
typedef struct {
    u32 tag;                         /* 0x00, el fondo (TILE) */
    u8 r, g, b, code;                /* 0x04 */
    s16 x, y, w, h;                  /* 0x08 */
    u32 modo[3];                     /* 0x10, DR_MODE */
    s32 n;                           /* 0x1C, cuantas letras caben */
    u8 *letras;                      /* 0x20, sus SPRT_8 (0x10 bytes cada uno) */
    char *texto;                     /* 0x24 */
    s32 largo;                       /* 0x28 */
    s32 sin_fondo;                   /* 0x2C */
} FlujoTexto;

extern s32 D_80062AF8;               /* cuantos flujos hay */
extern s32 D_80063500;               /* letras ya repartidas */
extern u8 D_80063518[];              /* el modo del primer flujo */
extern char D_8007ED9C[];            /* el texto de todos (0x400) */
extern u8 D_8007F19C[];              /* las letras de todos */
extern u16 D_8008319C;               /* la pagina de la fuente */
extern u16 D_800831A0;               /* su paleta */

extern void SetDrawMode(void *p, s32 dfe, s32 dtd, s32 tpage, RectF *tw);
extern void func_800141AC(void *p);  /* SetTile */
extern void func_800140DC(void *p, s32 semi);  /* SetSemiTrans */
extern void func_8001416C(void *p);  /* SetSprt8 */

#define FLUJOS ((FlujoTexto *)(D_80063518 - 0x10))

/* Abre un flujo en (x, y) de w por h con hasta n letras (las que queden de 0x400). Con fondo != 0 lleva
 * un rectangulo negro (semitransparente si es 2). Devuelve el numero del flujo, o -1 si ya hay 8. */
s32 func_80010920(s32 x, s32 y, s32 w, s32 h, s32 fondo, s32 n) {
    RectF tw;
    u8 *s;
    s32 i, k;

    if (D_80062AF8 >= 8) {
        return -1;
    }
    if (D_80062AF8 == 0) {
        D_80063500 = 0;
    }
    FLUJOS[D_80062AF8].sin_fondo = w == 0;
    if (D_80063500 + n > 0x400) {
        n = 0x400 - D_80063500;
    }
    tw.w = 0x100;
    tw.h = 0x100;
    tw.x = 0;
    tw.y = 0;
    SetDrawMode(FLUJOS[D_80062AF8].modo, 0, 0, D_8008319C, &tw);
    if (fondo != 0) {
        func_800141AC(&FLUJOS[D_80062AF8]);
        FLUJOS[D_80062AF8].r = 0;
        FLUJOS[D_80062AF8].g = 0;
        FLUJOS[D_80062AF8].b = 0;
        func_800140DC(&FLUJOS[D_80062AF8], fondo == 2);
    }
    k = D_80062AF8;
    i = D_80063500;
    FLUJOS[k].x = x;
    FLUJOS[k].y = y;
    FLUJOS[k].w = w;
    FLUJOS[k].h = h;
    FLUJOS[k].n = n;
    FLUJOS[k].largo = 0;
    FLUJOS[k].texto = &D_8007ED9C[i];
    FLUJOS[k].letras = &D_8007F19C[i * 0x10];
    FLUJOS[k].texto[0] = 0;
    s = FLUJOS[D_80062AF8].letras;
    for (i = 0; i < n; i++) {
        func_8001416C(s);
        *(u16 *)(s + 0xE) = D_800831A0;
        s += 0x10;
    }
    /* se relee: con el flujo -1 el largo de arriba cae justo en D_80063500 */
    D_80063500 = *(volatile s32 *)&D_80063500 + n;
    return D_80062AF8++;
}

extern s32 D_80062AFC;               /* el flujo por omision */
extern char *D_80063504;             /* "0123456789ABCDEF" */
extern s32 func_800150F0(char *s);   /* strlen */

/* Pone una letra al final del texto del flujo; 1 si se paso de las que caben. */
static s32 poner(FlujoTexto *f, s32 c) {
    f->texto[f->largo] = c;
    f->largo++;
    return f->n < f->largo;
}

/* El cuerpo de FntPrint. m es el sp del marco que arma ImprimirDepuracion igual que el juego (0x238
 * bytes): en m + 0x210 va el puntero a los argumentos y debajo se arman los numeros; en m + 0x238 empiezan
 * los argumentos. k es lo que traia a1: con una letra de formato que no entiende, el juego copia k letras
 * desde m + 0x210 (lo que haya en su marco), y por eso el marco tiene que ser el mismo. */
__attribute__((noinline, used)) static s32 imprimir(u8 *m, s32 k) {
    char **ap = (char **)(m + 0x210);
    FlujoTexto *f;
    char *fmt, *p;
    s32 id = *(s32 *)(m + 0x238);
    s32 c, ancho, cero, signo;
    u32 v;

    *ap = (char *)(m + 0x23C);
    if (id < 0 || id >= D_80062AF8) {
        fmt = (char *)id;
        id = D_80062AFC;
        *(s32 *)(m + 0x238) = id;
        if (FLUJOS[id].texto == NULL) {
            return -1;
        }
    } else {
        fmt = *(char **)(m + 0x23C);
        *ap = (char *)(m + 0x240);
    }
    f = &FLUJOS[*(s32 *)(m + 0x238)];
    if (f->n < f->largo) {
        return -1;
    }
    for (c = *fmt; c != 0; c = *++fmt) {
        if (c != '%' || (c = *++fmt) == '%') {
            if (poner(f, c)) {
                return -1;
            }
            continue;
        }
        ancho = 0;
        cero = c == '0';
        while ((u32)(c - '0') < 10) {
            ancho = ancho * 10 - '0' + c;
            c = *++fmt;
        }
        if (ancho <= 0) {
            ancho = 1;
        }
        p = (char *)ap;
        switch (c) {
        case 'd': {
            s32 n = *(s32 *)*ap;

            *ap += 4;
            if (n < 0) {
                n = -n;
                signo = '-';
            } else {
                signo = 0;
            }
            v = n;
            k = 0;
            do {
                *--p = v % 10 + '0';
                k++;
                v /= 10;
            } while (v != 0);
            if (signo != 0) {
                *--p = signo;
                k++;
            }
            break;
        }
        case 'x':
        case 'X':
            k = 0;
            v = *(u32 *)*ap;
            *ap += 4;
            do {
                *--p = D_80063504[v & 0xF];
                v >>= 4;
                k++;
            } while (v != 0);
            if (cero) {
                while (k < ancho) {
                    *--p = '0';
                    k++;
                }
            }
            break;
        case 'c':
            *--p = *(u8 *)*ap;
            *ap += 4;
            k = 1;
            break;
        case 's':
            p = *(char **)*ap;
            *ap += 4;
            k = func_800150F0(p);
            break;
        }
        for (; k < ancho; ancho--) {
            if (poner(f, ' ')) {
                return -1;
            }
        }
        for (k--; k != -1; k--) {
            if (poner(f, *p++)) {
                return -1;
            }
        }
    }
    f->texto[f->largo] = 0;
    return f->largo;
}

/* FntPrint: escribe con formato en el flujo id (si id no es un flujo abierto, es el formato y va al flujo
 * por omision). Entiende %d, %x, %X, %c, %s y %%, con ancho (rellena con espacios; con '0' delante, los
 * %x rellenan con ceros). Devuelve el largo del texto, o -1 si no cabe o el flujo no tiene texto. El marco
 * va a mano, igual al del juego (ver imprimir). */
__attribute__((naked)) s32 ImprimirDepuracion(s32 id, ...) {
    __asm__(".set noreorder\n"
            "\tsw $4, 0x0($sp)\n"
            "\tsw $5, 0x4($sp)\n"
            "\tsw $6, 0x8($sp)\n"
            "\tsw $7, 0xC($sp)\n"
            "\taddiu $sp, $sp, -0x238\n"
            "\tsw $31, 0x230($sp)\n"
            "\tsw $21, 0x22C($sp)\n"
            "\tsw $20, 0x228($sp)\n"
            "\tsw $19, 0x224($sp)\n"
            "\tsw $18, 0x220($sp)\n"
            "\tsw $17, 0x21C($sp)\n"
            "\tsw $16, 0x218($sp)\n"
            "\tjal imprimir\n"
            "\tmove $4, $sp\n"
            "\tlw $31, 0x230($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x238\n"
            ".set reorder");
}
