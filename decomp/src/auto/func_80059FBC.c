#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 partida;
extern s8 vida_barra;


void func_80059FBC(void *arg0) {
    s16 temp_v0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s3;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    temp_s1 = M2C_FIELD(arg0, void **, 0x1C);
    temp_s3 = M2C_FIELD(arg0, void **, 0x64);
    temp_s2 = arg0 + 0x74;
    switch (temp_v0) {                              /* irregular */
    case 2:
        M2C_FIELD(arg0, s16 *, 0x70) = 4;
        M2C_FIELD(temp_s2, s16 *, 0x3C) = 5;
        p_sabrina->vida -= 4;
        vida_barra = p_sabrina->vida;
        TocarSonido(0x33, 0, 0x28, 2);
        TocarSonido(7, 0, 0x2A, 0x7F);
        ActualizarBarraVida();
        if ((vida_barra == 0) && (partida < 2)) {
            M2C_FIELD(arg0, s16 *, 0x70) = 0xE;
            return;
        }
        func_80031000();
        return;
    case 3:
        if (M2C_FIELD(temp_s1, u8 *, 0x51) != M2C_FIELD(temp_s3, u16 *, 8)) {
            TocarSonido(0x32, 0, 0x28, 2);
            M2C_FIELD(arg0, s16 *, 0x70) = 5;
            M2C_FIELD(temp_s2, s16 *, 0x3C) = 6;
            M2C_FIELD(arg0, s8 *, 0x118) = (s8) (M2C_FIELD(arg0, s8 *, 0x118) - 1);
            func_80022FD8(M2C_FIELD(arg0, s8 *, 0x118) & 0xFF, 5);
            if (M2C_FIELD(arg0, s8 *, 0x118) == 0) {
                M2C_FIELD(arg0, s16 *, 0x70) = 0x11;
                M2C_FIELD(temp_s1, u8 *, 0x51) = (u8) M2C_FIELD(temp_s3, u16 *, 0xC);
                M2C_FIELD(temp_s1, s8 *, 0x50) = 0;
                M2C_FIELD(temp_s1, s16 *, 0x4E) = 0x800;
                return;
            }
        }
        return;
    case 0:
        if (p_sabrina->extra.espera_golpe <= 0) {
            p_sabrina->extra.espera_golpe = 0x1E;
            p_sabrina->vida -= 4;
            vida_barra = p_sabrina->vida;
            TocarSonido(7, 0, 0x2A, 0x7F);
            ActualizarBarraVida();
            if ((vida_barra == 0) && (partida < 2)) {
                M2C_FIELD(arg0, s16 *, 0x70) = 0xE;
                return;
            }
            func_80031000();
        }
        break;
    }
}
