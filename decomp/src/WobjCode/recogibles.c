#include "juego.h"

/* Registro de un objeto ya recogido (0x38 bytes); el primer campo lo identifica. */
typedef struct {
    s32 id;
    u8 _04[0x34];
} Recogido;

extern Recogido recogidos[];         /* 0x800C7990 */
extern s32 D_8007CC0C;               /* cuantos hay anotados */

/* 1 si id no esta entre los recogidos, 0 si ya se tomo. */
s32 RecogibleNoTomado(s32 id) {
    s32 i;

    for (i = 0; i < D_8007CC0C; i++) {
        if (recogidos[i].id == id) {
            return 0;
        }
    }
    return 1;
}
