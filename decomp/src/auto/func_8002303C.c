#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 huevos;
extern s16 partida;
extern s32 D_8006CE10;
extern s32 D_8006CE14;
extern s32 D_8006CE18;
extern s32 D_8006CE1C;
extern s32 D_8006CE20;
extern s32 D_8006CE24;
extern s32 D_8006CE28;
extern u16 D_8006CE36;
extern u8 D_8006CE38[];
extern u16 D_8006CE3C[];
extern u16 D_8006CE46;
extern u8 D_8006CE48[];
extern u16 D_8006CE4C[];
extern u8 D_8006CE70[];
extern u8 D_8006CE80[];
extern u8 D_8006CED0[];
extern u8 D_8006CEF1;
extern u8 D_8006CEF2;
extern s8 D_8006CEF3;
extern s8 D_8006CEF4[];
extern s8 D_8006CEF9;
extern s8 D_8006CEFA;
extern s8 D_8006CEFB;
extern s8 D_8006CEFC[];
extern s8 D_8006CEFE;
extern s8 D_8006CEFF;
extern u8 objetos_anacronicos[];
extern u8 D_8007C890[];
extern u8 hechizos[];
extern s8 nivel_actual;
extern u8 D_8007CB1C;
extern s32 D_8007CB24;
extern u8 D_8007CB28;
extern u16 D_8007CB2A;
extern u16 D_8007CB2C;
extern s16 D_8007CB2E;


void func_8002303C(void) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3_2;
    s32 temp_a3_3;
    s32 temp_v0_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    u16 temp_a3;
    u32 temp_a3_4;
    u32 temp_v1;
    u8 temp_v0;
    u8 temp_v1_2;
    u8 var_a1;
    u8 var_a1_2;

    if (hechizos[D_8007CB1C] == 0) {
        M2C_FIELD(M2C_ERROR(/* Read from unset register $t0 */), s8 *, 0x24) = func_80022EF4(1);
    }
    temp_v0 = hechizos[D_8007CB1C];
    if (temp_v0 != 0) {
        D_8006CE10 = D_8007CB24 + (D_8007CB1C << 5);
        var_v0 = D_8007CB24 + ((temp_v0 + 9) << 5);
    } else {
        D_8006CE10 = D_8007CB24 + 0x100;
        var_v0 = D_8007CB24 + 0x120;
    }
    D_8006CE14 = var_v0;
    D_8006CE18 = D_8007CB24 + 0x1E0;
    if ((D_8007CB28 != D_8007CB2A) || (partida != D_8007CB2C)) {
        if (partida != D_8007CB2C) {
            D_8006CE36 = 0x400;
            M2C_FIELD(D_8006CE38, u16 *, 0) = 0x19EU;
            M2C_FIELD(D_8006CE38, u16 *, 2) = 0x1AEU;
            *D_8006CE3C = 0x18C;
            D_8006CE46 = 0xF0;
            M2C_FIELD(D_8006CE48, u16 *, 0) = 0xA5U;
            M2C_FIELD(D_8006CE48, u16 *, 2) = 0xA5U;
            *D_8006CE4C = 0x93;
            temp_a2 = (partida / 10) + ((u32) partida >> 0x1F);
            D_8006CE20 = D_8007CB24 + ((temp_a2 + 0x11) << 5);
            D_8006CE24 = D_8007CB24 + (((partida - (temp_a2 * 0xA)) + 0x11) << 5);
            D_8006CE28 = D_8007CB24 + 0x640;
            D_8007CB2C = (u16) partida;
            D_8007CB2E = 0x32;
        } else if (nivel_actual != 0xD) {
            temp_a3 = D_8007CB28 & 0xFFFF;
            D_8006CE36 = 0x196;
            M2C_FIELD(D_8006CE38, u16 *, 0) = 0x1A6U;
            M2C_FIELD(D_8006CE38, u16 *, 2) = 0x1B6U;
            *D_8006CE3C = 0x18C;
            D_8006CE46 = 0xA5;
            M2C_FIELD(D_8006CE48, u16 *, 0) = 0xA5U;
            M2C_FIELD(D_8006CE48, u16 *, 2) = 0xA5U;
            *D_8006CE4C = 0x93;
            temp_v1 = temp_a3 >> 0x1F;
            temp_a3_2 = ((D_8007CB28 & 0xFFFF) / 100) + temp_v1;
            D_8006CE1C = D_8007CB24 + ((temp_a3_2 + 0x11) << 5);
            temp_a3_3 = temp_a3_2 * 0x64;
            D_8006CE20 = D_8007CB24 + ((((temp_a3 - temp_a3_3) / 10) + ((u32) (temp_a3 - temp_a3_3) >> 0x1F) + 0x11) << 5);
            D_8006CE24 = D_8007CB24 + (((temp_a3 - ((((D_8007CB28 & 0xFFFF) / 10) + temp_v1) * 0xA)) + 0x11) << 5);
            D_8006CE28 = D_8007CB24 + 0x360;
            D_8007CB2A = temp_a3;
            D_8007CB2E = 0x32;
        } else {
            D_8007CB2A = (u16) D_8007CB28;
        }
    } else {
        D_8007CB2E -= 1;
        if ((D_8007CB2E < 0) && ((u16) M2C_FIELD(D_8006CE38, u16 *, 0) < 0x28AU)) {
            D_8006CE36 += 4;
            M2C_FIELD(D_8006CE38, u16 *, 0) = (u16) (M2C_FIELD(D_8006CE38, u16 *, 0) + 4);
            M2C_FIELD(D_8006CE38, u16 *, 2) = (u16) (M2C_FIELD(D_8006CE38, u16 *, 2) + 4);
            *D_8006CE3C += 4;
            D_8006CE46 += 4;
            M2C_FIELD(D_8006CE48, u16 *, 0) = (u16) (M2C_FIELD(D_8006CE48, u16 *, 0) + 4);
            M2C_FIELD(D_8006CE48, u16 *, 2) = (u16) (M2C_FIELD(D_8006CE48, u16 *, 2) + 4);
            *D_8006CE4C += 4;
        }
    }
    var_v1 = 0;
    var_a2 = 5;
loop_20:
    if (var_v1 != 4) {
        if (objetos_anacronicos[var_v1] != 0) {
            var_a1 = 0xFF;
        } else {
            var_a1 = 0x46;
        }
        D_8006CED0[var_a2] = var_a1;
        var_v1 = (var_v1 + 1) & 0xFF;
        var_a2 += 1;
        goto loop_20;
    }
    var_v1_2 = 0;
    var_a2_2 = 2;
loop_26:
    if (var_v1_2 != 3) {
        if (D_8007C890[var_v1_2] != 0) {
            var_a1_2 = 0xFF;
        } else {
            var_a1_2 = 0x46;
        }
        D_8006CED0[var_a2_2] = var_a1_2;
        var_v1_2 = (var_v1_2 + 1) & 0xFF;
        var_a2_2 += 1;
        goto loop_26;
    }
    D_8006CEF1 = D_8006CE70[nivel_actual];
    temp_v1_2 = D_8006CE80[nivel_actual];
    D_8006CEF2 = temp_v1_2;
    D_8006CEF3 = temp_v1_2 + 1;
    *D_8006CEF4 = temp_v1_2 + 2;
    temp_a3_4 = (u8) D_8007CB28 >> 0x1F;
    temp_a1 = (D_8007CB28 / 100) + temp_a3_4;
    temp_a0 = temp_a1 * 0x64;
    D_8006CEF9 = ((D_8007CB28 - temp_a0) / 10) + ((u32) (D_8007CB28 - temp_a0) >> 0x1F) + 0x11;
    D_8006CEFA = (D_8007CB28 - (((D_8007CB28 / 10) + temp_a3_4) * 0xA)) + 0x11;
    D_8006CEFB = temp_a1 + 0x11;
    *D_8006CEFC = huevos + 0x11;
    temp_v0_2 = (partida / 10) + ((u32) partida >> 0x1F);
    D_8006CEFE = temp_v0_2 + 0x11;
    D_8006CEFF = (partida - (temp_v0_2 * 0xA)) + 0x11;
}
