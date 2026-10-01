#include "juego.h"

/* Partida nueva: deja en cero la partida guardada y el estado del juego que va con ella. */

extern u8 partida[0x13AC];           /* empieza con un s16: 5 al empezar */
extern u8 D_800C8560;
extern u8 D_800C8561[5];
extern u8 D_800C8567[13];            /* uno por nivel */
extern u8 D_800C8574[4];
extern u8 D_800C857E[4];
extern s16 D_800C8538[4];
extern s32 D_800C98C4[4];
extern s32 D_800C98A4, D_800C98B0, D_800C98B4;
extern u8 objetos_anacronicos, D_8007C88D, D_8007C88E, D_8007C88F, D_8007C890, D_8007C891, D_8007C892;
extern u8 hechizos, D_8007C8B1, D_8007C8B2, D_8007C8B3, D_8007C8B4, D_8007C8B5;
extern u8 D_800C98BC, D_800C98BD, D_800C98BE, D_800C98BF, D_800C98C0, D_800C98C1;
extern s32 D_8007CBA4, D_8007CC6C;
extern s16 D_8007CB2A, D_8007CB2C;
extern u8 D_8007CB28;

extern void *memset(void *p, s32 c, u32 n);

void func_8004C82C(void) {
    s32 i;

    memset(partida, 0, 0x13AC);
    *(s16 *)partida = 5;
    D_800C8560 = 1;
    for (i = 0; i < 5; i++) {
        D_800C8561[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        D_800C8574[i] = 1;
        D_800C98C4[i] = 0;
        D_800C8538[i] = 0;
    }
    /* lo de cada nivel: 0x141 bytes desde partida + 0x6E */
    for (i = 0; i < 13; i++) {
        D_800C8567[i] = 0;
        memset(partida + i * 0x141 + 0x6E, 0, 0x141);
    }
    for (i = 0; i < 4; i++) {
        D_800C857E[i] = 0;
    }
    D_800C98A4 = -1;
    D_800C98B0 = 1;
    objetos_anacronicos = 0;
    D_8007C88D = 0;
    D_8007C88E = 0;
    D_8007C88F = 0;
    D_8007C890 = 0;
    D_8007C891 = 0;
    D_8007C892 = 0;
    hechizos = 0;
    D_800C98BC = 0;
    D_8007C8B1 = 0;
    D_800C98BD = 0;
    D_8007C8B2 = 0;
    D_800C98BE = 0;
    D_8007C8B3 = 0;
    D_800C98BF = 0;
    D_8007C8B4 = 0;
    D_800C98C0 = 0;
    D_8007C8B5 = 0;
    D_8007CBA4 = 1;
    D_800C98C1 = 0;
    D_8007CB2A = -1;
    D_8007CB28 = 0;
    D_8007CB2C = *(s16 *)partida;
    D_800C98B4 = 1;
    D_8007CC6C = 0;
}

extern s8 nivel_actual;
extern u8 D_800C86C6[];              /* partida + 0x46 + nivel * 0x141: 1 si el nivel se visito */
extern u8 D_8007CB3A;                /* recogibles del nivel (las cuatro primeras clases) */
extern u32 D_8007CB3C;               /* cuantos registros tiene WRLDDATA */
extern u8 *D_8007CB40;               /* los registros de WRLDDATA, 0x9C bytes cada uno */
extern s32 D_800757DC[7];            /* con que numero empieza cada clase */

/* Al entrar a un nivel: lo marca visitado, cuenta en la partida cuantos objetos hay de cada una de las
 * siete clases que se guardan (tipos 4, 0x12, 0x13, 0x17, 0x28, 0x29 y 0x2D) y a cada uno le da su numero
 * dentro de la clase (en +0x1C del registro). Deja en D_8007CB3A y en D_800C8538 la suma de las cuatro
 * primeras clases. */
void func_8004BDA0(void) {
    static const s16 tipos[7] = { 4, 0x12, 0x13, 0x17, 0x28, 0x29, 0x2D };
    static const s16 desp[7] = { 0x6E, 0xB6, 0xFE, 0x146, 0x19E, 0x1A6, 0x18E };
    s32 num[7];
    s8 *cuenta[7];
    u8 *base, *r;
    u32 i;
    s32 k;

    for (k = 0; k < 7; k++) {
        num[k] = D_800757DC[k];
    }
    D_800C98A4 = nivel_actual;
    D_8007CB3A = 0;
    D_8007CB28 = 0;
    D_800C86C6[nivel_actual * 0x141] = 1;
    base = partida + nivel_actual * 0x141;
    for (k = 0; k < 7; k++) {
        cuenta[k] = (s8 *)(base + desp[k]);
    }
    for (k = 0; k < 7; k++) {
        *cuenta[k] = 0;
    }
    for (i = 0; i < D_8007CB3C; i++) {
        for (k = 0; k < 7; k++) {
            r = D_8007CB40 + i * 0x9C;
            if (*(s16 *)(r + 0xC) == tipos[k]) {
                *(s32 *)(r + 0x1C) = num[k];
                num[k]++;
                (*cuenta[k])++;
            }
        }
    }
    D_8007CB3A = *cuenta[0];
    D_8007CB3A += (u8)*cuenta[1];
    D_8007CB3A += (u8)*cuenta[2];
    D_8007CB3A += (u8)*cuenta[3];
    D_800C8538[nivel_actual] = D_8007CB3A;
}
