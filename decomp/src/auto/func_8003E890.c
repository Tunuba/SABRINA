#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_80074EC0;
extern s32 D_80074EC4;
extern s32 D_80074ED0;


void func_8003E890(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_80074EC4 == 0) {
        func_8003E610(2, D_80074EC0 << D_80074ED0, arg2, arg3);
        func_8003E610(1, M2C_ERROR(/* Read from unset register $a1 */), M2C_ERROR(/* Read from unset register $a2 */), M2C_ERROR(/* Read from unset register $a3 */));
        func_8003E610(3, arg0, arg1, M2C_ERROR(/* Read from unset register $a3 */));
        return;
    }
    func_8003E0C4(arg0, arg1);
}
