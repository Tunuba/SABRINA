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
