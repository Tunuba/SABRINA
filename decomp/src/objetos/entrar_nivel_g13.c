#include "juego.h"

/* Al entrar a un nivel: la musica, los contadores de la barra, las gemas del mundo y, si el nivel ya se
 * visito, marcar como tomados (estado 4) los recogibles que ya se juntaron. */

/* Un registro de WRLDDATA (0x9C bytes); solo lo que se usa. */
typedef struct {
    u8 _00[0x0C];
    s16 tipo;                        /* 0x0C */
    u8 _0E[0x0C];
    s16 estado;                      /* 0x1A, 4 = ya tomado */
    s32 numero;                      /* 0x1C, el numero del recogible en su tabla (desde 1) */
    u8 _20[0x7C];
} RegistroNivel;

/* Por nivel (0x141 bytes desde D_800C8586) la partida guarda, por tipo de recogible, cuantos hay y cual se
 * junto (una tabla de 0x48 bytes: el primero es la cuenta, los demas 1 si se tomo). */
extern u8 D_800C8586[], D_800C85CE[], D_800C8616[], D_800C865E[], D_800C86A6[], D_800C86B6[];
extern u8 D_800C86BE[];
extern u8 D_800C86B5[];              /* los huevos del nivel */
extern u8 D_800C86C6[];              /* 1 si el nivel se visito */
extern s8 D_800C8567, D_800C8568, D_800C8569, D_800C856A, D_800C856B, D_800C856C;
extern s8 D_800C856D, D_800C856E, D_800C856F, D_800C8570, D_800C8571, D_800C8572;
extern s8 D_800C857E, D_800C857F, D_800C8580, D_800C8581;
extern s16 D_800C8558, D_800C855A, D_800C855C, gemas;  /* las gemas de cada mundo */
extern s32 D_800C98A4;
extern s16 huevos, partida;
extern s16 D_8007C872;
extern s8 objetos_anacronicos;
extern s8 D_8007C88D, D_8007C88E, D_8007C88F;
extern s8 D_8007C890, D_8007C891, D_8007C892;  /* los tres hechizos del mundo */
extern u16 D_8007C8C4, D_8007C8C6;   /* volumenes */
extern s8 nivel_actual;
extern s8 D_8007CB20;
extern u8 D_8007CB28;                /* la cuenta de la barra */
extern s16 D_8007CB2A, D_8007CB2C, D_8007CB38;
extern u32 D_8007CB3C;               /* cuantos registros tiene el nivel */
extern RegistroNivel *D_8007CB40;
extern s32 D_8007CC70;

extern void func_8004BDA0(void);
extern void func_80056290(s32 nivel);
extern void func_8004C150(void);
extern void func_8003DD44(s32 volumen);
extern void func_8003DD74(s32 volumen);
extern void func_8004B318(void);
extern void func_8004C224(void);
extern void func_8004C22C(void);
extern void func_8004B14C(void);

/* Marca como tomados los registros del tipo dado cuyo numero figure como juntado en la tabla. */
__attribute__((noinline)) static void marcar(u8 *tablas, s32 tipo) {
    s32 i;
    u32 k;

    for (i = 0; i < (s8)tablas[D_800C98A4 * 0x141]; i++) {
        if (tablas[D_800C98A4 * 0x141 + i + 1] == 0) {
            continue;
        }
        for (k = 0; k < D_8007CB3C; k++) {
            if (D_8007CB40[k].tipo == tipo && i + 1 == D_8007CB40[k].numero) {
                D_8007CB40[k].estado = 4;
                D_8007CB28++;
                break;
            }
        }
    }
}

void func_8004B320(s32 nivel) {
    D_8007C872 = 0;
    D_8007CB20 = 0;
    D_8007CB38 = 0;
    func_8004BDA0();
    func_80056290(nivel);
    if (nivel_actual == 13) {
        func_8004C150();
    }
    func_8003DD44((D_8007C8C4 * 15) & 0xFF);
    func_8003DD74((D_8007C8C6 * 15) & 0xFF);
    func_8004B318();
    D_8007C890 = 0;
    D_8007C891 = 0;
    D_8007C892 = 0;
    D_8007C88D = D_800C857E;
    D_8007C88E = D_800C8581;
    D_8007C88F = D_800C857F;
    objetos_anacronicos = D_800C8580;
    huevos = 0;
    D_8007CC70 = 0;
    switch (nivel) {
    case 1: case 2: case 3:
        if (D_800C8567 != 0) {
            D_8007C890 = 1;
        }
        if (D_800C8568 != 0) {
            D_8007C891 = 1;
        }
        if (D_800C8569 != 0) {
            D_8007C892 = 1;
        }
        break;
    case 4: case 5: case 6:
        if (D_800C856A != 0) {
            D_8007C890 = 1;
        }
        if (D_800C856B != 0) {
            D_8007C891 = 1;
        }
        if (D_800C856C != 0) {
            D_8007C892 = 1;
        }
        break;
    case 7: case 8: case 9:
        if (D_800C856D != 0) {
            D_8007C890 = 1;
        }
        if (D_800C856E != 0) {
            D_8007C891 = 1;
        }
        if (D_800C856F != 0) {
            D_8007C892 = 1;
        }
        break;
    case 10: case 11: case 12:
        if (D_800C8570 != 0) {
            D_8007C890 = 1;
        }
        if (D_800C8571 != 0) {
            D_8007C891 = 1;
        }
        if (D_800C8572 != 0) {
            D_8007C892 = 1;
        }
        break;
    case 14:
        D_8007C872 = 1;
        break;
    }
    if (D_800C86C6[nivel * 0x141] != 0) {
        D_800C98A4 = nivel_actual;
        func_8004C224();
        marcar(D_800C8586, 4);
        marcar(D_800C85CE, 0x12);
        marcar(D_800C8616, 0x13);
        marcar(D_800C865E, 0x17);
        marcar(D_800C86B6, 0x28);
        marcar(D_800C86BE, 0x29);
        marcar(D_800C86A6, 0x2D);
    }
    func_8004C22C();
    func_8004B14C();
    switch (nivel_actual) {
    case 1: case 2: case 3:
        D_8007CB28 = gemas;
        break;
    case 4: case 5: case 6:
        D_8007CB28 = D_800C8558;
        break;
    case 7: case 8: case 9:
        D_8007CB28 = D_800C855A;
        break;
    case 10: case 11: case 12:
        D_8007CB28 = D_800C855C;
        break;
    }
    D_8007CB2A = D_8007CB28;
    D_8007CB2C = partida - 1;
    huevos = D_800C86B5[nivel_actual * 0x141];
}
