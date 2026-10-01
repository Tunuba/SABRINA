#include "juego.h"

/* La tarjeta de memoria: armar y desarmar los manejadores de sus eventos. */

/* Eventos de la tarjeta que dejan los manejadores de interrupcion. */
typedef struct {
    s32 evento;                      /* 0x00 */
    s32 dato;                        /* 0x04 */
    s32 hay;                         /* 0x08 */
    s32 _0C, _10;
    s32 ultimo;                      /* 0x14 */
    u8 _18[0x2C];
    s32 _44, _48, _4C, _50, _54;     /* 0x44 */
} EventosTarjetaG13;

extern volatile EventosTarjetaG13 D_800D52C0;

extern void UserFuncInit(void);
extern void func_80051A84(void);
extern s32 func_800169D4(s32 canal, void (*f)(void));  /* InterruptCallback */
extern void func_80050828(void);     /* el manejador de la tarjeta */
extern s32 func_80051C60(void);

/* Pone todo en cero, arma los manejadores y engancha el de la tarjeta a la interrupcion 7. */
s32 func_80050938(void) {
    D_800D52C0._0C = 0;
    D_800D52C0._44 = 0;
    UserFuncInit();
    D_800D52C0.evento = 0;
    D_800D52C0.dato = 0;
    D_800D52C0.hay = 0;
    D_800D52C0._54 = 0;
    D_800D52C0.ultimo = -1;
    D_800D52C0._4C = 1;
    D_800D52C0._48 = 1;
    D_800D52C0._50 = D_800D52C0._54;
    func_80051A84();
    return func_800169D4(7, func_80050828);
}

/* Espera a que no quede un evento pendiente, suelta la interrupcion 7 y desarma lo demas. */
s32 func_800509A8(void) {
    while (D_800D52C0.evento != 0) {
    }
    func_800169D4(7, NULL);
    return func_80051C60();
}
