#include "juego.h"

/* Piezas del manejo de la tarjeta de memoria (pantalla de guardar/cargar): el sondeo periodico de la
 * tarjeta, el paso de la pantalla, el nombre del puerto ("buXY:") y la lectura de los eventos. */

/* Eventos de la tarjeta que dejan los manejadores de interrupcion. */
typedef struct {
    s32 evento;                      /* 0x00, ultimo evento de software */
    s32 dato;                        /* 0x04 */
    s32 hay;                         /* 0x08, distinto de 0 si llego un evento de hardware sin leer */
} EventosTarjeta;

extern volatile EventosTarjeta D_800D52C0;
extern volatile s32 D_800D52B0;      /* evento de hardware */
extern volatile s32 D_800D52B4;      /* su dato */

extern u16 D_8007CC56;               /* cuenta hasta el proximo sondeo */
extern s32 D_8007CC44;               /* modo de la pantalla (2: no se sondea) */
extern s32 D_8007CC40;               /* estado de la tarjeta (paso de la pantalla) */
extern s16 D_8007CC4A;
extern u16 D_8007CC52;
extern u16 D_8007CC54;
extern void *D_8007C8F0[];           /* un objeto por jugador/pantalla */

typedef void (*PasoTarjeta)(void *obj, s32 n, u32 x);
extern PasoTarjeta *D_80075B1C[];    /* por modo, la tabla de pasos por estado */

extern char D_80062440[];            /* "bu00:" */

extern void func_800509E8(s32 a);  /* recibe el mismo a0 */
extern void func_80050A50(s32 a);
extern void func_8004FA54(void *obj, s32 n, u32 x);
extern void func_80019288(void);
extern void func_80019374(u32 a, u32 b);

s32 func_80051298(s32 modo, s32 *evento, s32 *dato);

/* Cada 11 llamadas (cuando la cuenta pasa por 0 vuelve a 10) sondea la tarjeta, salvo en el modo 2.
 * El estado queda en D_8007CC40, pero si ya era 4 solo cambia a un valor distinto de 0; si sale 3 pide
 * otra cosa a la tarjeta (func_80050A50) y vuelve a leer: un 4 se anota.
 * Ojo: si func_80051298 no tiene nada que contar (devuelve -1) no escribe la variable, y el juego usa lo
 * que habia en esa posicion de la pila (sp de entrada - 4). Para hacer lo mismo se lee esa palabra al
 * entrar (func_8004EE24 no arma marco: salta a sondear con ella como argumento). */
static void sondear(s32 a, s32 basura);

void func_8004EE24(s32 a) {
    register u8 *sp __asm__("$sp");

    sondear(a, *(s32 *)(sp - 4));
}

static __attribute__((noinline)) void sondear(s32 a, s32 basura) {
    s32 estado = basura;
    u16 cuenta = D_8007CC56;

    D_8007CC56 = cuenta - 1;
    if (cuenta != 0) {
        return;
    }
    D_8007CC56 = 10;
    if (D_8007CC44 == 2) {
        return;
    }
    func_800509E8(a);
    func_80051298(0, NULL, &estado);
    if (D_8007CC40 == 4) {
        if (estado != 0) {
            D_8007CC40 = estado;
        }
    } else {
        D_8007CC40 = estado;
    }
    if (estado == 3) {
        func_80050A50(a);
        func_80051298(0, NULL, &estado);
        if (estado == 4) {
            D_8007CC40 = 4;
        }
    }
}

/* Un cuadro de la pantalla de la tarjeta para el objeto n: lo comun antes, el paso que toca segun modo
 * y estado, lo comun despues y el dibujo. */
void func_8004FC4C(s32 n) {
    void *obj = D_8007C8F0[n];

    func_8004EE24((s32)obj);
    D_80075B1C[D_8007CC44][D_8007CC40](obj, n, (u16)D_8007CC4A);
    func_8004FA54(obj, n, (u16)D_8007CC4A);
    func_80019288();
    func_80019374(D_8007CC54, D_8007CC52);
}

/* Nombre del dispositivo de la tarjeta: copia "bu00:" y pone los dos digitos del puerto (n / 16 y
 * n % 16, con la division con signo del juego). */
void func_800508D4(s32 n, char *dst) {
    s32 i;

    for (i = 0; i < 6; i++) {
        dst[i] = D_80062440[i];
    }
    dst[2] = n / 16 + '0';
    dst[3] = n % 16 + '0';
}

/* Lee los eventos de la tarjeta. Sin ninguno pendiente da -1 y no escribe nada.
 * modo 0: espera (sin limite) el evento de hardware, lo copia y lo da por leido: 1.
 * otro modo: si hay evento de hardware lo copia y lo da por leido (1); si no, copia el de software (0). */
s32 func_80051298(s32 modo, s32 *evento, s32 *dato) {
    volatile EventosTarjeta *e = &D_800D52C0;
    s32 ev;
    s32 dt;

    if (e->evento == 0 && e->hay == 0) {
        return -1;
    }
    ev = e->evento;
    dt = e->dato;
    if (modo == 0) {
        if (e->hay == 0) {
            while (e->hay == 0) {
            }
        }
    } else if (e->hay == 0) {
        if (dato != NULL) {
            *dato = dt;
        }
        if (evento != NULL) {
            *evento = ev;
        }
        return 0;
    }
    if (dato != NULL) {
        *dato = D_800D52B4;
    }
    if (evento != NULL) {
        *evento = D_800D52B0;
    }
    e->hay = 0;
    return 1;
}
