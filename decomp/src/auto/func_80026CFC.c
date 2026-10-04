#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80026CFC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x46);
    switch (temp_v1) {                              /* irregular */
    case 2:
        M2C_FIELD(arg0, s8 *, 0x37) = 0x44;
        M2C_FIELD(arg0, void **, 0x2C) = (void *) (arg0 + 0x51);
        M2C_FIELD(arg0, u8 *, 0x36) = temp_v1;
        return;
    case 3:
        M2C_FIELD(arg0, s8 *, 0x37) = 0x4D;
        M2C_FIELD(arg0, void **, 0x2C) = (void *) (arg0 + 0x5D);
        M2C_FIELD(arg0, u8 *, 0x36) = 6U;
        return;
    }
}
