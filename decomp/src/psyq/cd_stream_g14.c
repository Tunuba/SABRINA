#include "juego.h"

/* La lectura de video por el CD (libcd, streaming): se llama cada vez que el CD tiene un sector listo.
 * Lee la cabecera del sector (0x20 bytes) al anillo, la revisa y, si es un sector de video que sigue,
 * pide por DMA el resto (0x1F8 palabras) al lugar del anillo que toca. Si el video viene de la memoria
 * (D_80091410), copia en vez de usar el DMA. D_8006D5F4 queda con el motivo de la salida. */

extern u8 *D_80091400;               /* el anillo: 0x20 bytes de cabecera por sector... */
extern s32 D_80091404;               /* ...para tantos sectores, y despues los datos (0x7E0 por sector) */
extern u8 *D_80091408;               /* adonde va el sector actual */
extern s32 D_8009140C;               /* velocidad doble */
extern s32 D_80091410;               /* el video esta en la memoria (no en el CD) */
extern s32 D_80091414;               /* sector leido de la memoria */
extern s32 D_80091418;               /* lugar del anillo que toca */
extern s32 D_8009141C;               /* primer lugar del cuadro actual */
extern s32 D_80091424;               /* esperando un cuadro */
extern u32 D_80091428;               /* el cuadro que se espera */
extern u32 D_8009142C;               /* el ultimo cuadro (0 sin limite) */
extern s32 D_80091430;               /* hay un cuadro completo */
extern u32 D_80091434;               /* el cuadro actual */
extern s16 D_80091438;               /* el sector que se espera dentro del cuadro */
extern s32 D_8009143C;
extern s32 D_80091440;
extern s32 D_80091444;               /* el canal que se lee */
extern s32 D_80091478;
extern u8 *D_80093A34;               /* la cabecera del sector actual */
extern void (*D_80093A30)();         /* aviso de fin del video */
extern volatile u8 *D_8006D5D0;      /* registros del CD */
extern volatile u8 *D_8006D5D4;
extern volatile u8 *D_8006D5D8;
extern volatile s32 *D_8006D5DC;     /* DMA del CD: control */
extern volatile s32 *D_8006D5E0;
extern volatile s32 *D_8006D5EC;
extern volatile s32 *D_8006D5F0;
extern s32 D_8006D5F4;

extern s32 func_80029A70(s32 n, u8 *resultado);
extern void func_8002D540(void *d, s32 s, s32 n, s32 ultimo);    /* copiar de la memoria */
extern void func_8002D56C(s32 canal, void *d, s32 a, s32 n, s32 control, s32 ultimo, s32 c);  /* DMA */
extern void init_ring_status(s32 desde, s32 n);
extern void data_ready_callback(void);

#define H16(d) (*(u16 *)(D_80093A34 + (d)))

/* Lugar del anillo que vuelve a empezar: deja el cuadro actual sin leer. */
static void reiniciar_cuadro(void) {
    D_80091434 = 0;
    D_80091438 = 0;
    init_ring_status(D_8009141C, D_80091418 - D_8009141C);
    D_80091418 = D_8009141C;
    H16(0) = 0;
}

/* El cuerpo; sub y cd viven en el marco de func_8002D714 (abajo), en los lugares del original. */
__attribute__((noinline, used)) static void lectura_sector(u8 *sub, u8 *cd) {
    u16 estado;
    s32 control;
    u32 i;

    if (D_80091430 == 1) {
        return;
    }
    if (D_8009140C != 0 && (*D_8006D5EC & 0x01000000)) {
        D_8009143C = 1;
        if (D_80091410 != 0) {
            D_80091414++;
        }
        D_8006D5F4 = 1;
        return;
    }
    if (func_80029A70(1, cd) == 5) {
        return;
    }
    estado = cd[0];
    if (estado & 4) {
        D_8006D5F4 = 3;
        return;
    }
    D_80093A34 = D_80091400 + (D_80091418 << 5);
    if (H16(0) != 0) {
        if (D_80091410 != 0) {
            D_80091414++;
        }
        D_8006D5F4 = 4;
        return;
    }
    *D_8006D5D0 = 0;
    *D_8006D5D8 = 0;
    *D_8006D5D0 = 0;
    *D_8006D5D8 = 0x80;
    *D_8006D5DC = 0x20943;
    *D_8006D5E0 = 0x1323;
    if (D_80091478 == 0) {
        for (i = 0; i < 4; i++) {
            sub[i] = *D_8006D5D4;
        }
        for (i = 0; i < 8; i++) {
            (void) *D_8006D5D4;
        }
    }
    if (D_80091410 != 0) {
        func_8002D540(D_80093A34, D_80091410 + (D_80091414 << 11), 8, 0);
    } else {
        func_8002D56C(3, D_80093A34, 0, 8, 0x11000000, 0, 0);
    }
    while (*D_8006D5F0 & 0x01000000) {
    }
    D_80093A34[0x1C] = sub[0];
    D_80093A34[0x1D] = sub[1];
    D_80093A34[0x1E] = sub[2];
    D_80093A34[0x1F] = sub[3];
    *D_8006D5DC = 0x20843;
    *D_8006D5E0 = 0x1325;
    if (D_80091424 == 1 && D_80091428 != 0) {
        if (D_80091428 != H16(8)) {
            H16(0) = 0;
            if (D_80091410 != 0) {
                D_80091414++;
            }
            return;
        }
        D_80091424 = 0;
    }
    if (H16(0) != 0x160 || ((H16(2) >> 10) & 0x1F) != D_80091444) {
        if (D_80091410 != 0) {
            D_80091414 = 0;
        }
        D_8006D5F4 = 5;
        H16(0) = 0;
        return;
    }
    if (D_80091438 != H16(4) || (D_80091434 != 0 && D_80091434 != H16(8))) {
        reiniciar_cuadro();
        if (D_80091410 != 0) {
            D_80091414++;
        }
        D_8006D5F4 = 6;
        return;
    }
    if (H16(4) == 0) {
        D_80091438 = 0;
        D_80091434 = H16(8);
        if (D_8009142C != 0 && D_80091434 >= D_8009142C) {
            reiniciar_cuadro();
            D_80091424 = 1;
            if (D_80093A30 != 0) {
                D_80093A30();
            }
            if (D_80091410 != 0) {
                D_80091414++;
            }
            D_8006D5F4 = 7;
            return;
        }
        if ((u32) (D_80091404 - D_80091418 - 1) < H16(6)) {
            /* el cuadro no entra en lo que queda del anillo: vuelve al principio */
            if (D_8009142C == 0) {
                H16(0) = 1;
                D_80091424 = 1;
                if (D_80093A30 != 0) {
                    D_80093A30(D_80093A34);
                }
                if (D_80091410 != 0) {
                    D_80091414++;
                }
                D_8006D5F4 = 8;
                return;
            }
            if (*(s16 *) D_80091400 != 0) {
                H16(0) = 0;
                if (D_80091410 != 0) {
                    D_80091414++;
                }
                D_8006D5F4 = 9;
                return;
            }
            H16(0) = 1;
            D_80091418 = 0;
            for (i = 0; i < 8; i++) {
                ((s32 *) D_80091400)[i] = ((s32 *) D_80093A34)[i];
            }
            D_80093A34 = D_80091400;
        }
        D_8009141C = D_80091418;
    }
    D_8006D5F4 = 0xA;
    D_80091438 = (u16) D_80091438 + 1;
    D_80091408 = D_80091400 + (D_80091404 << 5) + D_80091418 * 0x7E0;
    if (D_8009140C != 0) {
        control = 0x11000000;
        *D_8006D5DC = 0x20943;
        *D_8006D5E0 = 0x1323;
    } else {
        control = 0x11400100;
        *D_8006D5DC = 0x21020843;
    }
    if (H16(6) - 1 == H16(4)) {
        D_80091430 = 1;
        if (D_80091410 != 0) {
            func_8002D540(D_80091408, D_80091410 + (D_80091414 << 11) + 0x20, 0x1F8, 1);
            D_80091414++;
        } else {
            func_8002D56C(3, D_80091408, 0, 0x1F8, control, 1, 0);
        }
        D_80091438 = 0;
        D_80091434 = 0;
        D_80091444 = D_80091440;
    } else if (D_80091410 != 0) {
        func_8002D540(D_80091408, D_80091410 + (D_80091414 << 11) + 0x20, 0x1F8, 0);
        D_80091414++;
    } else {
        func_8002D56C(3, D_80091408, 0, 0x1F8, control, 0, 0);
    }
    *D_8006D5E0 = 0x1325;
    H16(0) = 3;
    D_80091418++;
    if (D_80091410 != 0 && D_80091430 != 0) {
        data_ready_callback();
    }
}

/* Si D_80091478 != 0 el original no llena sub y copia al sector los 4 bytes que habia en su pila
 * (sp+0x28 de un marco de 0x40, solo con ra guardado). GCC pone ahi registros guardados, asi que el
 * marco va a mano y el cuerpo usa esos mismos lugares. */
__attribute__((naked))
void func_8002D714(void) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x40\n"
            "\tsw $31, 0x38($sp)\n"
            "\taddiu $4, $sp, 0x28\n"
            "\tjal lectura_sector\n"
            "\taddiu $5, $sp, 0x30\n"
            "\tlw $31, 0x38($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x40\n"
            ".set reorder");
}

extern char D_80061774[];            /* aviso de DMA ocupado */
extern volatile s32 *D_8006D5E4;     /* DPCR */
extern volatile u8 *D_8006D5E8;      /* DICR */
extern s32 printf(const char *f, ...);

/* Arranca el DMA del canal: espera (con tope) a que el canal este libre, prende o apaga su interrupcion,
 * lo habilita, pone la direccion y el tamano, espera a que el CD tenga datos y da la orden. */
void func_8002D56C(s32 canal, void *madr, s32 bloques, s32 tam, s32 control, s32 aviso, s32 c) {
    volatile s32 *r = (volatile s32 *) (0x1F801080 + canal * 0x10);
    s32 n = 0;

    while (r[2] & 0x01000000) {
        if (n == 0x10000) {
            printf(D_80061774, r[2], 0x10000);
            break;
        }
        n++;
    }
    if ((u8) aviso == 1) {
        D_8006D5E8[2] |= 1 << canal;
    } else {
        D_8006D5E8[2] &= ~(1 << canal);
    }
    (void) *(volatile s32 *) D_8006D5E8;
    *D_8006D5E4 |= 1 << (canal * 4 + 3);
    r[0] = (s32) madr;
    r[1] = (bloques << 16) | tam;
    while (!(*D_8006D5D0 & 0x40)) {
    }
    r[2] = control;
    (void) r[2];
}
