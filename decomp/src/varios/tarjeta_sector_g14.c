#include "juego.h"

/* Escritura comprobada de un sector de la tarjeta de memoria. */

extern char D_8006246C[];            /* aviso: fallo la lectura */
extern void _new_card(void);
extern s32 _card_write(s32 canal, s32 sector, u8 *buf);
extern s32 _card_read(s32 canal, s32 sector, u8 *buf);
extern s32 _card_status(s32 puerto);
extern void bzero(void *p, s32 n);
extern s32 printf(char *fmt, ...);

/* Pone en buf[0x7F] el xor de los 127 bytes anteriores, escribe el sector y lo vuelve a leer para comparar
 * la suma. Hasta 8 intentos: 1 si quedo bien, 0 si no (o si la escritura no arranco). */
s32 func_80052434(s32 canal, s32 sector, u8 *buf) {
    u8 leido[0x80];
    s32 intento;
    s32 x;
    s32 k;
    u8 *p;

    x = 0;
    p = buf;
    for (k = 0x7E; k >= 0; k--) {
        x ^= *p++;
    }
    *p = x;
    for (intento = 0; intento < 8; intento++) {
        _new_card();
        if (_card_write(canal, sector, buf) != 1) {
            return 0;
        }
        while (!(_card_status(canal >> 4) & 1)) {
        }
        bzero(leido, 0x80);
        _new_card();
        if (_card_read(canal, sector, leido) != 1) {
            printf(D_8006246C);
        } else {
            while (!(_card_status(canal >> 4) & 1)) {
            }
        }
        x = 0;
        p = leido;
        for (k = 0x7E; k >= 0; k--) {
            x ^= *p++;
        }
        if (buf[0x7F] == (x & 0xFF)) {
            return 1;
        }
    }
    return 0;
}

extern u8 D_800D5600[0x80];          /* el sector que se escribe */
extern u8 D_800D53D0[15][0x20];      /* el directorio: una entrada por bloque */
extern s32 D_800D55B0[20];           /* la lista de sectores rotos */

static void copiar(u8 *a, u8 *de, s32 n) {
    while (n-- > 0) {
        *a++ = *de++;
    }
}

/* Formatea la tarjeta: los 15 bloques del directorio libres (0xA0, siguiente 0xFFFF), la lista de sectores
 * rotos vacia (-1) y la cabecera "MC" en el sector 0. 1 si todo se escribio bien. */
s32 func_80052578(s32 canal) {
    s32 i;

    for (i = 0; i < 15; i++) {
        bzero(D_800D5600, 0x80);
        bzero(D_800D53D0[i], 0x20);
        *(s32 *)&D_800D53D0[i][0] = 0xA0;
        *(s32 *)&D_800D53D0[i][4] = 0;
        *(u16 *)&D_800D53D0[i][8] = 0xFFFF;
        copiar(D_800D5600, D_800D53D0[i], 0x20);
        if (func_80052434(canal, i + 1, D_800D5600) != 1) {
            return 0;
        }
    }
    for (i = 0; i < 20; i++) {
        D_800D55B0[i] = -1;
        bzero(D_800D5600, 0x80);
        copiar(D_800D5600, (u8 *)&D_800D55B0[i], 4);
        if (func_80052434(canal, i + 0x10, D_800D5600) != 1) {
            return 0;
        }
    }
    bzero(D_800D5600, 0x80);
    D_800D5600[0] = 'M';
    D_800D5600[1] = 'C';
    return func_80052434(canal, 0, D_800D5600) == 1;
}
