#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80055588(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
    M2C_FIELD((arg0 + 0x74), s32 *, 4) = CrearParticula((s32) (s8) M2C_FIELD(arg0, s32 *, 0x74), (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x3E80, /* extra? */ 0, /* extra? */ 0);
}
