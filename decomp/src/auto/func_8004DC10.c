#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80075834[];
extern u8 D_8007CC25;
extern s8 D_8007CC26;


s32 func_8004DC10(M2C_UNK arg1) {
    if (D_8007CC26 == 0) {
        D_8007CC25 = 0;
        D_8007CC26 = 1;
    }
    if (D_8007CC25 == 0) {
        D_8007CC25 = 1;
        return func_800161BC();
    }
    printf((s32) "OUT OF MEMORY");
    return 0;
}
