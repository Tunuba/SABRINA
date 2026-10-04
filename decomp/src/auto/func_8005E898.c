#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 nivel_actual;
extern s32 func_80024F6C();
extern s32 func_80024F74();


void func_8005E898(void *arg0) {
    s8 temp_v0;
    void *temp_s1;
    void *temp_s2;

    temp_s1 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s2 = M2C_FIELD(arg0, void **, 0x64);
    if (M2C_FIELD(arg0, s16 *, 0x70) == 1) {
        switch (nivel_actual) {                     /* irregular */
        case 3:
            TocarSonido(0x39, 0, 0x2A, 0x7F);
            break;
        case 6:
            TocarSonido(0x38, 0, 0x2A, 0x7F);
            break;
        case 9:
            TocarSonido(0x38, 0, 0x2A, 0x7F);
            break;
        case 12:
            TocarSonido(0x3A, 0, 0x2A, 0x7F);
            break;
        }
        M2C_FIELD(arg0, s16 *, 0x70) = 0x11;
        M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) M2C_FIELD(temp_s2, u16 *, 0xC);
        M2C_FIELD(temp_s1, s8 *, 0x50) = 0;
        M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
        M2C_FIELD(arg0, s8 *, 0x118) = (s8) (M2C_FIELD(arg0, s8 *, 0x118) - 1);
        temp_v0 = M2C_FIELD(arg0, s8 *, 0x118);
        if (temp_v0 <= 0) {
            M2C_FIELD(arg0, s32 (**)(), 0xC) = func_80024F74;
            M2C_FIELD(arg0, s32 (**)(), 8) = func_80024F6C;
            M2C_FIELD(temp_s1, s8 *, 0x51) = (s8) M2C_FIELD(temp_s2, u16 *, 2);
            M2C_FIELD(temp_s1, s8 *, 0x50) = 0;
            M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
            M2C_FIELD(arg0, s16 *, 0x70) = 0xA;
            func_80022FD8(0, 5);
            return;
        }
        func_80022FD8(temp_v0 & 0xFF, 5);
    }
}
