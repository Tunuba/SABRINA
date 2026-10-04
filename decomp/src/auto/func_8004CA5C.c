#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 nivel_actual;
extern s8 D_8007CA01;
extern s16 D_8007CC16;
extern u8 D_8007CC18;


void func_8004CA5C(void *arg0) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    switch (temp_v0) {                              /* irregular */
    case 2:
    case 1:
        break;
    case 0:
        if (D_8007CC18 == 1) {
            D_8007CA01 = nivel_actual;
            nivel_actual = (s8) D_8007CC16;
            M2C_FIELD(arg0, s16 *, 0x70) = 2;
        }
        break;
    }
}
