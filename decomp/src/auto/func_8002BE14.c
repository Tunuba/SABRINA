#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_8002BE14(s32 arg0, s32 arg1, s32 arg2) {
    M2C_UNK sp10;

    func_80029F18(arg1, (s32) &sp10);
    func_80029AB8(2, (s32) &sp10, 0);
    CdRead(arg0, arg2, 0x80);
    return CdReadSync(0, 0) == 0;
}
