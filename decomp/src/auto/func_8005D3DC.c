#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CC90;
extern s32 D_8007CC94;


void func_8005D3DC(void) {
    D_8007CC90 = 0x7F;
    D_8007CC94 = -0xA;
    func_8005D3F4();
}
