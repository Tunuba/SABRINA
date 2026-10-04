#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006D324;
extern s8 * D_8006D5C8;
extern s8 * D_8006D5CC;


void func_8002D170(void) {
    func_800143E4();
    if (D_8006D324 == 1) {
        func_8005C940(0);
        func_8005C92C(0);
    } else {
        func_80029ED4(0);
        func_80029AA4(0);
    }
    *D_8006D5C8 = 0;
    *D_8006D5CC = 0;
    func_800143F4();
}
