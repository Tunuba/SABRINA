#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800D5818;
extern u16 D_8007CC7C;
extern u16 D_8007CC7E;


void func_8005CE48(void) {
    func_8002D170();
    func_80029D28(9, 0, 0);
    func_8005DDE8(0);
    if (D_800D5818 != 0) {
        func_8005C964();
    }
    SsSetSerialVol(0, (s32) (s16) D_8007CC7C, (s32) (s16) D_8007CC7E);
}
