#include "objeto.h"

/* El aviso de un objeto que desaparece al tocarlo Sabrina. */

/* Si quien lo toca es Sabrina, lo marca para borrar (bit 0x80 del byte 0x20). Devuelve (v0) el byte
 * marcado, o Sabrina si no era ella. */
s32 func_8003BFC4(Objeto *o, Objeto *quien) {
    if (quien != p_sabrina) {
        return (s32)p_sabrina;
    }
    *(u8 *)&o->_20 |= 0x80;
    return *(u8 *)&o->_20;
}
