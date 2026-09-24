#include "juego.h"

extern s32 D_80074ECC;               /* si hay que redondear a bloques */
extern u32 D_80074ED4;               /* tamano del bloque */
extern u32 D_80074ED8;               /* mascara del bloque (tamano - 1) */
extern u32 D_80074ED0;               /* desplazamiento para pasar bytes a bloques */
extern u16 *D_80074EBC;              /* tabla de tamanos en bloques */

/* Redondea el tamano hacia arriba al siguiente bloque y lo pasa a bloques.
 * indice -2: devuelve el tamano redondeado; -1: devuelve el tamano en bloques;
 * otro: lo guarda en la tabla en esa posicion y devuelve el tamano redondeado. */
u32 func_8003E958(s32 indice, u32 tamano) {
    u32 bloques;

    if (D_80074ECC != 0 && tamano % D_80074ED4 != 0) {
        tamano = (tamano + D_80074ED4) & ~D_80074ED8;
    }
    bloques = tamano >> D_80074ED0;
    if (indice == -2) {
        return tamano;
    }
    if (indice == -1) {
        return bloques & 0xFFFF;
    }
    D_80074EBC[indice] = bloques;
    return tamano;
}
