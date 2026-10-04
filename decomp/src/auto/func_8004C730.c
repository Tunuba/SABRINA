#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C86A6[];
extern u8 D_800C86B5[];
extern s16 huevos;
extern s8 nivel_actual;
extern s32 func_8004AB24();


void func_8004C730(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s8 *temp_a1;

    temp_v1 = nivel_actual * 0x141;
    temp_a1 = D_800C86A6 + temp_v1;
    *(arg0 + temp_a1) = 1;
    huevos += 1;
    *(D_800C86B5 + temp_v1) = (s8) huevos;
    if (huevos >= *temp_a1) {
        temp_v0 = func_800252A0(0x18, 0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 1);
        if (temp_v0 != 0) {
            *temp_v0 = func_8004AB24;
            func_8004AAE4(temp_v0);
        }
    }
}
