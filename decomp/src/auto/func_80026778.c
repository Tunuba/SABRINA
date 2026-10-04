#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80026778(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x46);
    switch (temp_v1) {                              /* irregular */
    case 2:
        func_80026DC4((s32) arg0, (s32) M2C_FIELD(arg0, u8 *, 0x47));
        return;
    case 3:
        func_80026DE4((s32) arg0, (s32) M2C_FIELD(arg0, u8 *, 0x47));
        return;
    case 4:
        if (M2C_FIELD(arg0, u8 *, 0x48) == 0) {
            func_80026E04((s32) arg0, (s32) M2C_FIELD(arg0, u8 *, 0x47));
            return;
        }
        func_80026E24((s32) arg0);
        return;
    }
}
