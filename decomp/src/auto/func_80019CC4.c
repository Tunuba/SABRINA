#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 nivel_actual;


void func_80019CC4(void) {
    func_80019C04();
    func_80022528();
    func_800206F0();
    func_80025964();
    func_8001F23C();
    func_8001E9DC();
    func_8002FFB8((s32) nivel_actual);
}
