#include "juego.h"

/* libpad: intercambiar un byte con el mando por el puerto serie. */

extern volatile u8 *D_8006CF70;      /* el puerto serie del mando (0x1F801040) */
extern volatile s32 *D_8006CF6C;     /* I_STAT (0x1F801070): el bit 7 es el ACK del mando */
extern u32 D_800913F8;               /* la espera que se pidio (func_8002908C) */
extern u32 D_800913FC;               /* el contador 2 al pedirla */
extern s32 D_8006CFC8;

extern void func_8002908C(s32 n);    /* empezar una espera */
extern s32 func_800290AC(void);      /* paso la espera */

#define SIO16(d) (*(volatile u16 *) (D_8006CF70 + (d)))
#define CONTADOR2 (*(volatile u16 *) 0x1F801120)
#define MODO2 (*(volatile u16 *) 0x1F801124)
#define OBJETIVO2 (*(volatile u16 *) 0x1F801128)

/* Espera a poder mandar, lee el byte que llego, ajusta la velocidad, espera el ACK del mando (con tiempo)
 * y manda el byte b. Anota lo recibido en el bufer del puerto (0x3C, en el lugar 0x44). Devuelve el byte
 * recibido, o -2 si el mando no respondio a tiempo. */
s32 func_8002643C(u8 *puerto, s32 b) {
    s16 velocidad;
    u32 recibido;
    u32 desde;
    u32 espera;
    u32 t;

    velocidad = 0x88;
    if ((**(u8 **) (puerto + 0x3C) >> 4) == 8 && puerto[0x44] >= 9) {
        velocidad = 0x22;
    }
    while (!(SIO16(4) & 2)) {
    }
    func_8002908C(0x190);
    recibido = D_8006CF70[0];
    if (puerto[0x44] == 0 && (recibido >> 4) == 8) {
        SIO16(0xE) = 0x22;
    } else {
        SIO16(0xE) = velocidad;
    }
    if (!(*D_8006CF6C & 0x80)) {
        desde = D_800913FC;
        espera = D_800913F8;
        do {
            t = CONTADOR2;
            if (t < desde) {
                if (OBJETIVO2 != 0) {
                    t += OBJETIVO2;
                } else {
                    t += 0x10000;
                }
            }
            if (MODO2 & 0x200) {
                if (t - desde >= espera) {
                    return -2;
                }
            } else if ((t - desde) >> 3 >= espera) {
                return -2;
            }
        } while (!(*D_8006CF6C & 0x80));
    }
    if (puerto[0xE8] != 8 && D_8006CFC8 == 2) {
        func_8002908C(0x3C);
        while (func_800290AC() == 0) {
        }
    }
    D_8006CF70[0] = b;
    if (D_8006CFC8 == 3 && recibido == 0x80) {
        *D_8006CF6C = -0x81;
        SIO16(0xA) |= 0x10;
    }
    puerto[0x45]++;
    if (puerto[0x44] != 0xFF) {
        (*(u8 **) (puerto + 0x3C))[puerto[0x44]] = recibido;
    }
    puerto[0x44]++;
    return recibido;
}
