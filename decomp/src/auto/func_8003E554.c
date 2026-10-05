#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80074EAC;
extern void * D_80074EBC;

extern M2C_UNK (*D_80074EE0)(M2C_UNK);

void func_8003E554(void) {
    u32 var_v1;

    if (D_80074EAC == 0) {
        func_8003EA90();
    }
    M2C_FIELD(D_80074EBC, u16 *, 0x1AA) = (u16) (M2C_FIELD(D_80074EBC, u16 *, 0x1AA) & 0xFFCF);
    if (M2C_FIELD(D_80074EBC, u16 *, 0x1AA) & 0x30) {
        var_v1 = 1;
loop_4:
        if (var_v1 < 0xF01U) {
            var_v1 += 1;
            if (M2C_FIELD(D_80074EBC, u16 *, 0x1AA) & 0x30) {
                goto loop_4;
            }
        }
    }
    if (D_80074EE0 != NULL) {
        D_80074EE0(0xF0000000);
        return;
    }
    DeliverEvent();
}
