#include "juego.h"

/* Lectura del mando en cada paso. D_8007CA70 apunta al estado del mando que deja func_8001D8EC (o a
 * D_80086498 si no dejo ninguno); de su palabra en +0x20 salen los botones: los 16 bits de abajo en
 * D_8007CA50 y los de arriba en D_8007CA54. */

typedef struct {
    u8 _00[4];
    s32 estado;                      /* 0x04, 1 llama a func_8001DF6C; 0 limpia 0x38 */
    u8 _08[0x18];
    u16 botones;                     /* 0x20 */
    u8 _22[0x16];
    s32 _38;                         /* 0x38 */
} Mando;

extern Mando *D_8007CA70;
extern s32 D_8007CA74;               /* 1 si no hubo lectura */
extern s32 D_8007CA78;               /* palabra de botones del paso */
extern s32 D_8007C7F0;
extern s32 D_8007CA50;               /* botones apretados, 16 bits de abajo */
extern s32 D_8007CA54;               /* y de arriba */
extern s32 D_8007CA58;               /* recien apretados */
extern s32 D_8007CA5C;
extern s32 D_8007CA60;               /* los del paso anterior */
extern s32 D_8007CA64;
extern s32 D_8007CA68;               /* pasos sin nada apretado */
extern s32 D_8007CA6C;
extern u8 D_80086454[];
extern Mando D_80086498;

extern void func_8001D8EC(s32 a, void *b);
extern void func_8001DF6C(s32 estado);

void func_8001D778(void) {
    Mando *m;
    s32 e;

    D_8007CA70 = NULL;
    func_8001D8EC(0, D_80086454);
    if (D_8007CA70 == NULL) {
        D_8007CA70 = &D_80086498;
        D_8007C7F0 = D_8007C7F0 + 1;
        D_8007CA74 = 1;
    } else {
        if (D_8007C7F0 > 0x28) {
            D_8007C7F0 = 0;
        }
        D_8007CA74 = 0;
    }
    m = D_8007CA70;
    D_8007CA78 = m->botones;
    e = m->estado;
    if (e == 1) {
        func_8001DF6C(e);
    } else if (e == 0) {
        m->_38 = 0;
        D_8007C7F0 = D_8007C7F0 + 1;
    }
    D_8007CA60 = D_8007CA50;
    D_8007CA64 = D_8007CA54;
    D_8007CA50 = D_8007CA78 & 0xFFFF;
    D_8007CA54 = D_8007CA78 >> 16;
    D_8007CA68++;
    D_8007CA6C++;
    if (D_8007CA50 != 0) {
        D_8007CA68 = 0;
    }
    if (D_8007CA54 != 0) {
        D_8007CA6C = 0;
    }
    D_8007CA58 = ~D_8007CA60 & D_8007CA50;
    D_8007CA5C = ~D_8007CA64 & D_8007CA54;
}
