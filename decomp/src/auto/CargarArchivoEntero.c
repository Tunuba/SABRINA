#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 CargarArchivoEntero(s32 arg0, s32 arg1) {
    s32 temp_v0;

    do {
        temp_v0 = func_80017D80(arg0);
    } while (temp_v0 == 0);
    return temp_v0;
}
