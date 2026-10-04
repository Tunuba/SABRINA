#include "juego.h"

/* Un valor de la tabla de D_80074EBC; si b no es -1, corrido D_80074ED0 bits (sin recortar a 16 bits). */

extern u16 *D_80074EBC;
extern s32 D_80074ED0;

s32 func_8003E9FC(s32 i, s32 b) {
    u32 v = D_80074EBC[i];

    if (b != -1) {
        return v << D_80074ED0;
    }
    return v;
}
