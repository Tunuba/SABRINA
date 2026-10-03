#include "juego.h"

/* Lectura de un directorio del CD (libcd de PsyQ, para CdSearchFile). */

extern s32 D_8006D3C8;               /* el directorio que ya esta leido */
extern s32 D_8006D30C;               /* nivel de depuracion */
extern u8 D_80091A58[];              /* por directorio (0x2C bytes c/u): el sector donde esta */
extern u8 D_8009307C[0x800];         /* el sector leido */
extern u8 D_8009387C[];              /* su final */
extern u8 D_8009147C[64][0x18];      /* los archivos: posicion (4), tamano (4), nombre (16) */
extern u16 D_8006164C;               /* "." */
extern s16 D_80061650;               /* ".." */
extern s8 D_80061652;
extern char D_80061610[], D_80061630[], D_80061654[], D_80061670[];
extern s32 func_8002BE14(s32 n, s32 sector, u8 *buf);   /* leer sectores */
extern void func_80029F18(s32 lba, u8 *pos);            /* CdIntToPos */
extern void *memcpy(void *a, const void *de, s32 n);
extern s32 printf(char *fmt, ...);

static inline u32 leer32(u8 *p) {
    return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
}

/* Lee el sector del directorio dir (si no es el que ya estaba) y llena la tabla con sus archivos (hasta 64):
 * la posicion del primer sector, el tamano y el nombre (las dos primeras entradas son "." y ".."). Marca el
 * final de la tabla con un nombre vacio. 1 si fue bien, -1 si no se pudo leer. */
s32 func_8002BB78(s32 dir) {
    u8 *p;
    s32 i;
    u32 lba;
    u8 *e;

    if (dir == D_8006D3C8) {
        return 1;
    }
    p = D_8009307C;
    if (func_8002BE14(1, *(s32 *)(D_80091A58 + dir * 0x2C), p) != 1) {
        if (D_8006D30C > 0) {
            printf(D_80061610);
        }
        return -1;
    }
    if (D_8006D30C >= 2) {
        printf(D_80061630);
    }
    i = 0;
    if (p < p + 0x800) {
        do {
            if (*p == 0) {
                break;
            }
            e = D_8009147C[i];
            lba = leer32(p + 2);
            func_80029F18(lba, e);
            *(u32 *)(e + 4) = leer32(p + 0xA);
            if (i == 0) {
                *(u16 *)(e + 8) = D_8006164C;
            } else if (i == 1) {
                *(s16 *)(e + 8) = D_80061650;
                *(s8 *)(e + 10) = D_80061652;
            } else {
                memcpy(e + 8, p + 0x21, p[0x20]);
                e[8 + p[0x20]] = 0;
            }
            if (D_8006D30C >= 2) {
                printf(D_80061654, e[0], e[1], e[2], *(s32 *)(e + 4), e + 8);
            }
            i++;
            p += *p;
        } while (i < 0x40 && p < D_8009387C);
    }
    D_8006D3C8 = dir;
    if (i < 0x40) {
        D_8009147C[i][8] = 0;
    }
    if (D_8006D30C >= 2) {
        printf(D_80061670, i);
    }
    return 1;
}

extern s32 D_8006D3CC;               /* las veces que se abrio la tapa cuando se leyo la tabla de directorios */
extern s32 D_8006D318;               /* las veces que se abrio la tapa */
extern char D_800614A4[], D_800614C0[], D_800614D8[], D_800614F4[], D_80061514[], D_80061520[];
extern s32 func_8002B810(void);                  /* leer la tabla de directorios */
extern s32 func_8002BAD4(s32 padre, char *nombre); /* el directorio hijo con ese nombre, o -1 */
extern s32 func_8002B7F0(char *a, char *b);      /* los nombres son iguales */

/* CdSearchFile(fp, nombre): busca "\DIR\...\ARCHIVO;1" (hasta 8 niveles). Si lo encuentra copia su entrada
 * (posicion, tamano y nombre) en fp y la devuelve; si no, 0. */
u8 *func_8002BE88(u8 *fp, char *nombre) {
    char tok[0x20];
    char *s;
    char *d;
    s32 dir;
    s32 i;
    s32 k;
    u8 *e;

    if (D_8006D3CC != D_8006D318) {
        if (func_8002B810() == 0) {
            return 0;
        }
        D_8006D3CC = D_8006D318;
    }
    if (nombre[0] != 0x5C) {
        return 0;
    }
    tok[0] = 0;
    dir = 1;
    s = nombre;
    for (i = 0; i < 8; i++) {
        d = tok;
        while (*s != 0x5C) {
            if (*s == 0) {
                goto fin;
            }
            *d++ = *s++;
        }
        s++;
        *d = 0;
        dir = func_8002BAD4(dir, tok);
        if (dir == -1) {
            tok[0] = 0;
            break;
        }
    }
fin:
    if (i >= 8) {
        if (D_8006D30C > 0) {
            printf(D_800614A4, nombre, i);
        }
        return 0;
    }
    if (tok[0] == 0) {
        if (D_8006D30C > 0) {
            printf(D_800614C0, nombre);
        }
        return 0;
    }
    *d = 0;
    if (func_8002BB78(dir) == 0) {
        if (D_8006D30C > 0) {
            printf(D_800614D8);
        }
        return 0;
    }
    if (D_8006D30C >= 2) {
        printf(D_800614F4, tok);
    }
    for (i = 0; i < 0x40; i++) {
        e = D_8009147C[i];
        if ((s8)e[8] == 0) {
            break;
        }
        if (func_8002B7F0((char *)e + 8, tok) != 0) {
            if (D_8006D30C >= 2) {
                printf(D_80061514, tok);
            }
            for (k = 0; k < 6; k++) {
                ((u32 *)fp)[k] = ((u32 *)e)[k];
            }
            return e;
        }
    }
    if (D_8006D30C > 0) {
        printf(D_80061520, tok);
    }
    return 0;
}
