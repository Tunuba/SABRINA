#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800754E8;
extern s32 SsSeqCalledTbyT();

extern s32 (*D_800754FC)();

void func_80041F54(void) {
    if (D_800754E8 == 0) {
        D_800754E8 = 1;
        return;
    }
    D_800754E8 = 0;
    D_800754FC();
}
