#include "juego.h"

/* CdPlay (libcd): tocar pistas de audio del CD en una lista. */

extern u8 D_8009387C[];              /* la tabla de contenido */
extern s32 D_80093A0C;               /* cuantas pistas tiene */
extern char D_800616E4[];            /* aviso de que no se pudo leer la tabla */
extern s32 D_8006D30C;               /* cuanto avisa libcd */
extern s32 D_8006D41C[100];          /* la lista de pistas (termina en 0) */
extern s32 D_8006D5AC;               /* el lugar de la lista que suena (-1 apagado) */
extern s32 D_8006D5B0;               /* ya empezo a sonar */
extern s32 D_8006D5B4;               /* repetir la lista */
extern s32 D_8006D5B8;               /* la pista que suena */

extern s32 printf(const char *f, ...);
extern s32 CdGetToc(void *toc);
extern s32 func_80029AB8(s32 orden, u8 *param, u8 *resultado);  /* CdControl */
extern s32 func_80029A50(s32 orden, u8 *resultado);             /* CdControlB */
extern s32 func_80029BF4(s32 orden, u8 *param);
extern void func_8002CEB4(void);     /* parar */
extern void func_8002CD3C(void);     /* tocar la pista que toca */

/* modo 0 para, 1 toca una vez la lista desde el lugar inicio, 2 la repite, 3 revisa (si la pista termino,
 * pasa a la siguiente). Devuelve el lugar de la lista que suena, o -1. */
s32 func_8002CF28(s32 modo, s32 *pistas, s32 inicio) {
    u8 param[8];
    u8 resultado[8];
    s32 n;

    if (modo == 3) {
        if (D_8006D5AC == -1) {
            return -1;
        }
        func_80029AB8(1, 0, 0);
        if (func_80029A50(1, resultado) != 0) {
            if (!(resultado[0] & 0xC0)) {
                D_8006D5B0 = 1;
            }
            if (D_8006D5B0 != 0 && !(resultado[0] & 0x10)) {
                func_8002CD3C();
            } else {
                func_80029BF4(1, 0);
            }
        }
        return D_8006D5AC;
    }
    if (modo == 0) {
        func_8002CEB4();
        return D_8006D5AC;
    }
    D_80093A0C = CdGetToc(D_8009387C);
    if (D_80093A0C == 0) {
        if (D_8006D30C >= 2) {
            printf(D_800616E4);
        }
        D_8006D5AC = -1;
        return -1;
    }
    D_8006D5B4 = modo != 1;
    for (n = 0; pistas[n] != 0; ) {
        D_8006D41C[n] = pistas[n];
        n++;
        if (n >= 0x63) {
            break;
        }
    }
    D_8006D41C[n] = 0;
    D_8006D5AC = inicio;
    if (inicio < 0) {
        n = 0;
    } else if (n >= inicio) {
        n = inicio;
    }
    D_8006D5AC = n;
    param[0] = 5;
    D_8006D5B8 = D_8006D41C[n];
    func_80029AB8(0xE, param, 0);
    func_8002CD3C();
    return D_8006D5AC;
}

extern char D_80061474[];            /* "CD_init:" */
extern char D_80061480[];            /* "addr=%08x" */
extern char D_8006D2CC[];
extern volatile u8 *D_8006D2B0;      /* registros del CD: indice */
extern volatile u8 *D_8006D2B8;
extern volatile u8 *D_8006D2BC;      /* interrupciones del CD */
extern volatile s32 *D_8006D2C0;     /* control de la memoria del CD */
extern u8 D_8006D2C8[];
extern s32 D_8006D304;
extern s32 D_8006D308;
extern s32 D_8006D310;
extern s32 D_8006D314;
extern s8 D_8006D320;
extern s8 D_8006D321;

extern s32 puts(const char *s);
extern void func_80016910();         /* ResetCallback */
extern void func_80016940(s32 n, void (*f)());   /* InterruptCallback */
extern void func_8002A5F8();         /* el manejador del CD */
extern s32 func_8002AC18(s32 orden, u8 *param, u8 *resultado, s32 c);   /* mandar una orden al CD */
extern s32 func_8002A6D0(s32 modo, u8 *resultado);   /* CdSync */

/* CD_init: borra el estado, engancha el manejador del CD, limpia sus interrupciones y lo reinicia
 * (Nop, Reset, Demute). Devuelve 0 si quedo listo, -1 si no. */
s32 func_8002B2BC(void) {
    puts(D_80061474);
    printf(D_80061480, D_8006D2CC);
    D_8006D321 = 0;
    D_8006D320 = 0;
    D_8006D308 = 0;
    D_8006D304 = 0;
    D_8006D314 = 0;
    D_8006D310 = 0;
    func_80016910();
    func_80016940(2, func_8002A5F8);
    *D_8006D2B0 = 1;
    while (*D_8006D2BC & 7) {
        *D_8006D2B0 = 1;
        *D_8006D2BC = 7;
        *D_8006D2B8 = 7;
    }
    D_8006D2C8[2] = 0;
    D_8006D2C8[1] = D_8006D2C8[2];
    D_8006D2C8[0] = 2;
    *D_8006D2B0 = 0;
    *D_8006D2BC = 0;
    *D_8006D2C0 = 0x1325;
    func_8002AC18(1, 0, 0, 0);
    if (D_8006D310 & 0x10) {
        func_8002AC18(1, 0, 0, 0);
    }
    if (func_8002AC18(0xA, 0, 0, 0) != 0) {
        return -1;
    }
    if (func_8002AC18(0xC, 0, 0, 0) != 0) {
        return -1;
    }
    if (func_8002A6D0(0, 0) != 2) {
        return -1;
    }
    return 0;
}
