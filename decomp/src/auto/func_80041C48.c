#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80041C48(void) {
    func_80016910();
    SsUtReverbOff();
    SpuClearReverbWorkArea(7);
    _SsInit();
}
