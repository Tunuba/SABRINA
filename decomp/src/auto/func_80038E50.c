#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80038E50(void *arg0) {
    if (!(M2C_FIELD(arg0, s16 *, 0x112) & 0x8000)) {
        func_800252A0(7, (s32) arg0, 0, -0x50000, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0);
    }
}
