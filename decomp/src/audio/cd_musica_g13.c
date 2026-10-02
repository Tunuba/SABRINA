#include "juego.h"

/* La musica del CD (CdPlay de libcd): el aviso de cada respuesta del lector mientras suena una lista de
   pistas. */

extern u8 D_80093A14[8];        /* la ultima respuesta del lector */
extern u8 D_80093A15;           /* su segundo byte: la pista en BCD */
extern s32 D_8006D5B8;          /* la pista que suena */
extern s32 D_8006D5AC;          /* el indice en la lista */
extern s32 D_8006D41C[];        /* la lista de pistas */
extern s32 D_8006D30C;          /* nivel de mensajes */
extern s32 D_8006D5B0;          /* hubo error */
extern char D_8006170C[];       /* "cbdataready: CdlDataEnd (track=%d,time=%d)\n" */
extern char D_80061738[];       /* "CdPlay Error:%s:%02x,%02x\n" */
extern s32 printf(const char *f, ...);
extern void func_80029AA4(s32 x);
extern s32 func_8001626C(s32 x);
extern char *func_80029A1C(s32 n);
extern s32 func_8002CD3C(void);

/* st: 1 dato listo (si la pista ya paso a la siguiente, cuenta como fin), 4 fin de pista (pasa a la
   siguiente de la lista), 5 error. Devuelve lo que queda en v0. */
s32 func_8002CBB0(s32 st, u8 *res) {
    u32 s = st & 0xFF;
    s32 i, v;
    if (s == 1) {
        for (i = 0; i < 8; i++) {
            D_80093A14[i] = res[i];
        }
        if (D_8006D5B8 < (D_80093A15 >> 4) * 10 + (D_80093A15 & 0xF)) {
            s = 4;
        }
    }
    if (s == 4) {
        func_80029AA4(0);
        if (D_8006D30C >= 2) {
            i = func_8001626C(-1);
            printf(D_8006170C, D_8006D5AC, i);
        }
        i = D_8006D5AC + 1;
        D_8006D5AC = i;
        D_8006D5B8 = D_8006D41C[i];
        return func_8002CD3C();
    }
    if (s != 5) {
        return 5;
    }
    v = res[0] & 1;
    if (v != 0) {
        return v;
    }
    D_8006D5B0 = 1;
    if (D_8006D30C >= 2) {
        printf(D_80061738, func_80029A1C(5), res[0], res[1]);
    }
    v = res[0] & 0x11;
    if (v != 0) {
        return v;
    }
    return func_8002CD3C();
}
