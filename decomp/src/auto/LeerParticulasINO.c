#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006886C[];
extern s32 D_8007CA88;
extern u8 D_8007CAE8;


void LeerParticulasINO(s32 arg0) {
    u16 sp1E;

    sp1E = 0;
    ArchivoLeer(arg0, (s32) &sp1E, 2);
    D_8007CA88 = Reservar(sp1E << 5, (s32) "Particle.c");
    ArchivoLeer(arg0, D_8007CA88, sp1E << 5);
    D_8007CAE8 += 1;
}
