#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007CA1E;
extern u16 D_8007CA20;
extern s16 D_8007CA22;
extern u16 D_8007CA3A;


void func_80048094(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s16 *, 0x1A) = 2;
    if (D_8007CA20 != D_8007CA3A) {
        D_8007CA22 = func_80019234((s32) D_8007CA20);
    }
    D_8007CA3A = D_8007CA20;
    func_8001981C();
    func_80019288();
    func_80019374((s32) D_8007CA20, (s32) D_8007CA1E);
}
