#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80026E48(s32 arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x46);
    switch (temp_v1) {                              /* irregular */
    case 2:
        func_80026DB0(arg0);
        return;
    case 3:
        func_80026DC4(arg0, (s32) M2C_FIELD(arg0, u8 *, 0xE4));
        return;
    case 4:
        func_80026E04(arg0, (s32) M2C_FIELD(arg0, u8 *, 0x47));
        return;
    }
}
