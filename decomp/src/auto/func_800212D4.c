#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_8001B000();
extern s32 func_800211D4();

void func_800212D4(void) {
    func_80016910();
    func_8004EBD0();
    func_8001D554();
    func_80012B0C(0);
    func_80012CDC(0);
    func_80012C80(0);
    func_80016DEC(0);
    func_800177B4();
    func_80017B5C(0x100, 0x6E);
    func_80017B7C();
    func_800169A0((s32) func_800211D4);
    func_800299D4(2);
    func_8002988C();
    func_8003DC48();
    func_800213A0();
    func_8002153C();
    func_800190C0();
    func_80012CDC(1);
    func_80018218();
    func_800182A8();
    func_8001B5F8((s32) func_8001B000);
}
