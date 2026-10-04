#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8005DD70(s32 arg0) {
    if (arg0 == 0) {
        return func_8005DADC();
    }
    return (func_8005DC04() >> 0x1D) & 1;
}
