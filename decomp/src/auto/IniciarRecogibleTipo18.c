#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 tabla_valor_gemas[];


void IniciarRecogibleTipo18(void *arg0) {
    void *temp_a1;

    M2C_FIELD(arg0, s16 *, 0x32) = 0;
    M2C_FIELD(arg0, s16 *, 0x34) = 0;
    temp_a1 = arg0 + 0x74;
    M2C_FIELD(arg0, s16 *, 0x30) = 0;
    M2C_FIELD(temp_a1, s8 *, 4) = (s8) (M2C_FIELD(temp_a1, s8 *, 4) * 2);
    M2C_FIELD(temp_a1, s8 *, 5) = (s8) (tabla_valor_gemas[M2C_FIELD(temp_a1, s8 *, 4)] + 1);
    M2C_FIELD(temp_a1, s8 *, 4) = (s8) tabla_valor_gemas[M2C_FIELD(temp_a1, s8 *, 4)];
    M2C_FIELD(temp_a1, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
    RegistrarRecogible((s32) arg0);
}
