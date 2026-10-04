#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D52B0[];
extern u8 D_800D52C0[];

void func_80050828(void) {
    if (UserFuncComplete() == 0) {
        UserFuncExecute();
        if (UserFuncComplete() != 0) {
            M2C_FIELD(D_800D52C0, s32 *, 8) = 1;
            M2C_FIELD(D_800D52B0, s32 *, 0) = (s32) M2C_FIELD(D_800D52C0, s32 *, 0);
            M2C_FIELD(D_800D52B0, s32 *, 4) = (s32) M2C_FIELD(D_800D52C0, s32 *, 4);
            M2C_FIELD(D_800D52C0, s32 *, 0) = 0;
            M2C_FIELD(D_800D52C0, s32 *, 4) = 0;
            if (M2C_FIELD(D_800D52C0, M2C_UNK (**)(s32, s32, M2C_UNK), 0x44) != NULL) {
                M2C_FIELD(D_800D52C0, M2C_UNK (**)(s32, s32, M2C_UNK), 0x44)(M2C_FIELD(D_800D52B0, s32 *, 0), M2C_FIELD(D_800D52B0, s32 *, 4), M2C_FIELD(D_800D52C0, M2C_UNK (**)(s32, s32, M2C_UNK), 0x44));
            }
        }
    }
    M2C_FIELD(D_800D52C0, s32 *, 0x50) = (s32) (M2C_FIELD(D_800D52C0, s32 *, 0x50) + 1);
    M2C_FIELD(D_800D52C0, s32 *, 0x54) = (s32) (M2C_FIELD(D_800D52C0, s32 *, 0x54) + 1);
}
