#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_80052EA4(Objeto *arg0) {
    s16 temp_v0;
    u16 *temp_s1;
    void *temp_v1;

    temp_s1 = arg0->animaciones;
    temp_v0 = arg0->estado;
    temp_v1 = arg0 + 0x74;
    switch (temp_v0) {                              /* irregular */
    case 0:
        arg0->estado = 1;
        return;
    case 1:
        func_800484CC((s32) (arg0 + 0x24), (s32) &p_sabrina->x, 0x40000, (s32) (temp_v1 + 8));
        arg0->estado = 2;
        return;
    case 2:
        if (func_80021D44((s32) &arg0->rot[1], (s32) func_8002218C(arg0, M2C_FIELD(temp_v1, s32 *, 8), M2C_FIELD(temp_v1, s32 *, 0x10)), 0x96) == 0) {
            func_80022310((s32) arg0, (s32) arg0->rot[1], 0x3333, 0x1000, /* extra? */ (s32) M2C_FIELD(temp_s1, u16 *, 2));
        }
        return;
    }
}
