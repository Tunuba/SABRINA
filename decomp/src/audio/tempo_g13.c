#include "juego.h"

/* libsnd: el reloj de la secuencia de musica (SsSetTickMode y compania). */

extern s8 D_80075504[3];             /* [0] usar la vuelta de la pantalla, [1] cuenta, [2] canal */
extern s32 D_800754F8;               /* distinto de 0: no tocar el reloj */
#define MODO (*(s32 *)((u8 *)D_80075504 - 0x10))       /* el modo, o el tempo pedido (0x800754F4) */
#define PROPIA (*(s32 *)((u8 *)D_80075504 - 8))       /* la funcion propia de cada vuelta */
#define VIEJA (*(s32 *)((u8 *)D_80075504 - 4))        /* la funcion de vuelta que habia */

extern void func_800143E4(void);     /* EnterCriticalSection */
extern s32 func_800143F4(void);      /* ExitCriticalSection */
extern s32 func_80014598(s32 canal);
extern s32 func_800144C4(s32 canal, s32 valor, s32 banderas);
extern s32 func_800169A0(s32 f);
extern s32 func_80016940(s32 canal, s32 f);
extern void func_80041F08(void), func_80041F54(void);

/* Pone el reloj de la musica segun el modo: con la pantalla o con un contador del sistema (a 60 o 120
 * golpes, o al tempo pedido). Devuelve lo que devuelve la ultima llamada. */
s32 func_80041CD8(s32 propio) {
    volatile s32 espera;
    u32 canal = 0xF2000002;
    s32 valor = 0x44E8;

    for (espera = 0x3E6; espera >= 0; espera--) {
    }
    D_80075504[2] = 6;
    D_80075504[0] = 0;
    D_80075504[1] = 0;
    VIEJA = 0;
    switch (MODO) {
    case 2:
        break;
    case 0:
        D_80075504[2] = 0x7F;
        return 0x7F;
    case 3:
        valor = 0x89D0;
        break;
    case 5:
        D_80075504[2] = 0;
        if (propio == 0) {
            D_80075504[0] = 1;
        } else {
            canal = 0xF2000003;
            valor = 1;
        }
        break;
    default:
        if (D_800754F8 != 0) {
            return D_800754F8;
        }
        if (MODO < 0x46) {
            valor = 0x204CC0 / MODO;
            D_80075504[1]++;
        } else {
            valor = 0x409980 / MODO;
        }
        break;
    }
    if (D_80075504[0] != 0) {
        func_800143E4();
        func_800169A0(PROPIA);
    } else {
        func_800143E4();
        func_80014598(canal);
        func_800144C4(canal, valor & 0xFFFF, 0x1000);
        if (D_80075504[2] == 0) {
            VIEJA = func_80016940(0, 0);
            func_80016940(D_80075504[2], (s32)func_80041F08);
        } else {
            func_80016940(D_80075504[2], D_80075504[1] != 0 ? (s32)func_80041F54 : PROPIA);
        }
    }
    return func_800143F4();
}

extern s32 func_80016970(s32 canal, s32 f);

/* Pone f en el canal 4 de interrupciones. */
s32 func_8003EAF8(s32 f) {
    return func_80016970(4, f);
}

extern u8 *D_80074EBC;               /* los registros de la SPU */
extern s32 D_80074ED0;               /* corrimiento de las direcciones */

/* Escribe un registro de la SPU (n en medias palabras); con convertir, el valor es una direccion. */
s32 func_8003E914(s32 n, u32 valor, s32 convertir) {
    if (convertir == 0) {
        *(u16 *)(D_80074EBC + n * 2) = valor;
    } else {
        *(u16 *)(D_80074EBC + n * 2) = valor >> D_80074ED0;
    }
    return (s32)(D_80074EBC + n * 2);
}

extern u16 D_80074EC0;               /* la direccion de destino en la RAM de sonido (/8) */
extern char D_80061D10[];            /* "SPU:T/O [%s]\n" */
extern char D_80061D30[], D_80061D44[];  /* "wait (wrdy H -> L)", "wait (dmaf clear/W)" */
extern void func_8003EA90(void);     /* una espera corta */
extern s32 printf(const char *f, ...);

#define SPU16(d) (*(volatile u16 *)(D_80074EBC + (d)))

/* Escribe n bytes en la RAM de sonido por el FIFO de la SPU, de a 64 (sin DMA), esperando a la SPU entre
 * tandas y al final; si tarda demasiado, avisa. Devuelve lo que quedo en v0 en el original. */
s32 func_8003E0C4(u16 *datos, u32 n) {
    u32 estado, tanda, i;
    s32 j;

    SPU16(0x1A6) = D_80074EC0;
    estado = SPU16(0x1AE) & 0x7FF;
    func_8003EA90();
    while (n != 0) {
        tanda = n < 0x41 ? n : 0x40;
        for (j = 0; j < (s32)tanda; j += 2) {
            SPU16(0x1A8) = *datos++;
        }
        SPU16(0x1AA) = (SPU16(0x1AA) & 0xFFCF) | 0x10;
        func_8003EA90();
        if (SPU16(0x1AE) & 0x400) {
            for (i = 1;; i++) {
                if (i >= 0xF01) {
                    printf(D_80061D10, D_80061D30);
                    break;
                }
                if (!(SPU16(0x1AE) & 0x400)) {
                    break;
                }
            }
        }
        n -= tanda;
        func_8003EA90();
        func_8003EA90();
    }
    SPU16(0x1AA) &= 0xFFCF;
    if ((SPU16(0x1AE) & 0x7FF) == (estado & 0xFFFF)) {
        return estado & 0xFFFF;
    }
    for (i = 1;; i++) {
        if (i >= 0xF01) {
            return printf(D_80061D10, D_80061D44);
        }
        if ((SPU16(0x1AE) & 0x7FF) == (estado & 0xFFFF)) {
            return estado & 0xFFFF;
        }
    }
}
