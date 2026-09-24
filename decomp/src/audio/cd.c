#include "juego.h"

/* Volumen de la salida de audio del CD (CdlATV de libcd): izquierda->izquierda, izquierda->derecha,
 * derecha->derecha, derecha->izquierda. */
typedef struct {
    u8 val0;
    u8 val1;
    u8 val2;
    u8 val3;
} VolumenCd;

extern s32 CdMix(VolumenCd *vol);

/* Pone el volumen del audio del CD: cada canal a su propio lado, sin cruzar. */
void func_8003DD44(u8 volumen) {
    VolumenCd vol;

    vol.val0 = volumen;
    vol.val1 = 0;
    vol.val2 = volumen;
    vol.val3 = 0;
    CdMix(&vol);
}
