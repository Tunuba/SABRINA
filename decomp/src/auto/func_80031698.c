#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C8566;
extern s16 partida;
extern void * D_8007CAFC;
extern s32 D_8007CB00;
extern s32 D_8007CB04;
extern s32 D_8007CB08;
extern s16 D_8007CB0C;
extern u8 D_8007CB1C;
extern s8 vida_barra;
extern s16 D_8007CB38;
extern s16 D_8007CB70;
extern s32 D_8007CB78;
extern s32 D_8007CB80;
extern s8 D_8007CB88;
extern void * D_8007CB8C;
extern s32 D_8007CB90;
extern s32 D_8007CB94;
extern s32 D_8007CB98;
extern s32 D_8007CB9C;
extern s32 D_8007CBA0;
extern u16 D_8007CBC0;
extern u16 D_8007CBD4;
extern s16 D_8007CBF0;
extern u8 D_8007CC14;
extern s32 D_8007CC60;


void func_80031698(void *arg0) {
    void *temp_s1;
    void *temp_v1;

    temp_s1 = arg0 + 0x74;
    D_8007CB88 = 0;
    if (D_8007CAFC != NULL) {
        M2C_FIELD(D_8007CAFC, s16 *, 0x70) = 0;
    }
    D_8007CBF0 = 1;
    D_8007CB80 = 0;
    D_8007CC60 = 0;
    func_80031494();
    func_8003DC08();
    if (partida > 0) {
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) D_8007CB00;
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) D_8007CB04;
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) D_8007CB08;
        M2C_FIELD(arg0, s8 *, 0x118) = 0x14;
    }
    M2C_FIELD(arg0, s16 *, 0x30) = 0;
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) D_8007CB0C;
    M2C_FIELD(arg0, s16 *, 0x34) = 0;
    M2C_FIELD(arg0, s32 *, 0x74) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    M2C_FIELD(temp_s1, s16 *, 0x10) = 0;
    M2C_FIELD(temp_s1, s16 *, 0xE) = 0;
    M2C_FIELD(temp_s1, s8 *, 0x1F) = 0;
    M2C_FIELD(temp_s1, s8 *, 0x20) = 0;
    M2C_FIELD(temp_s1, s16 *, 0x12) = 0;
    M2C_FIELD(temp_s1, u8 *, 0x24) = (u8) D_8007CB1C;
    M2C_FIELD(temp_s1, s8 *, 0x22) = 8;
    M2C_FIELD(temp_s1, s16 *, 0x14) = 0x1E;
    M2C_FIELD(arg0, s32 *, 0x54) = 0xA;
    M2C_FIELD(arg0, s32 *, 0x58) = 0xA;
    M2C_FIELD(arg0, s32 *, 0x5C) = 0xA;
    M2C_FIELD(arg0, s16 *, 0x70) = 4;
    M2C_FIELD(temp_s1, s8 *, 0x1D) = 0;
    M2C_FIELD(temp_s1, s8 *, 0x1E) = 0;
    temp_v1 = M2C_FIELD(D_8007CB8C, void **, 0x1C);
    M2C_FIELD(temp_v1, s16 *, 0x4E) = 0x1000;
    M2C_FIELD(temp_v1, s8 *, 0x51) = (s8) *M2C_FIELD(D_8007CB8C, u16 **, 0x64);
    M2C_FIELD(temp_v1, s8 *, 0x50) = 0;
    D_8007CB70 = 0;
    if (D_8007CC14 == 1) {
        D_8007CC14 = 0;
    }
    switch (D_800C8566) {
    case 0:
        func_80030F18(2);
        break;
    case 1:
        func_80030F18(4);
        break;
    case 2:
        func_80030F18(8);
        break;
    case 3:
        func_80030F18(0xA);
        break;
    case 4:
        func_80030F18(6);
        break;
    }
    D_8007CB90 = 0;
    D_8007CB94 = 0;
    D_8007CB98 = 0;
    D_8007CB9C = 0;
    D_8007CBA0 = 0;
    D_8007CB78 = 0;
    vida_barra = p_sabrina->vida;
    D_8007CB38 = 0;
    ActualizarBarraVida();
    func_8004CAB8();
    func_800350A4((s32) (arg0 + 0x24));
    func_80037278((s32) D_8007CAFC, (s32) arg0);
    func_8003019C();
    func_80030E64();
    D_8007CBD4 = D_8007CBC0;
}
