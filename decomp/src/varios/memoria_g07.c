#include "juego.h"

/* Bloques de memoria fijos del nivel que func_8002EC1C deja en cero y apunta desde sus punteros. */
extern u8 D_80093D04[];              /* 0x20F58 bytes */
extern u8 D_800B4C5C[];              /* 0x101D0 bytes */
extern u8 D_800C4E2C[];              /* 0xFA0 bytes */

/* 20 registros de 0x5C bytes; cada uno apunta en +0x48 al que le sigue. */
typedef struct Registro5C {
    u8 _00[0x48];
    struct Registro5C *siguiente;    /* 0x48 */
    u8 _4C[0x10];
} Registro5C;

extern Registro5C D_800C5DCC[];
extern s32 D_800C64E8;

extern u8 *D_8007CB5C;
extern u8 *D_8007CB60;
extern u8 *D_8007CB64;
extern s32 D_8007CB68;
extern Registro5C *D_8007CB6C;

extern void *memset(void *p, s32 c, u32 n);

/* Limpia los bloques y deja encadenados los 20 registros de D_800C5DCC. */
void func_8002EC1C(void) {
    s32 i;
    Registro5C *r;

    memset(D_80093D04, 0, 0x20F58);
    memset(D_800B4C5C, 0, 0x101D0);
    memset(D_800C4E2C, 0, 0xFA0);
    D_8007CB5C = D_80093D04;
    D_8007CB60 = D_800B4C5C;
    D_8007CB64 = D_800C4E2C;
    r = D_800C5DCC;
    for (i = 0; i < 20; i++) {
        memset(r, 0, sizeof(Registro5C));
        r->siguiente = r + 1;
        r++;
    }
    D_800C64E8 = 0;
    D_8007CB6C = D_800C5DCC;
    D_8007CB68 = 0;
}
