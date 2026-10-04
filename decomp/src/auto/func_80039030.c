#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80039030(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x34) == 0) {
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + 0xFFFDD99A);
        M2C_FIELD(arg0, s16 *, 0x34) = 0x800;
    }
    func_80021D44((s32) (arg0 + 0x34), (s32) (s16) (func_80021CE4(0x64) + 0x79C), 0x28);
}
