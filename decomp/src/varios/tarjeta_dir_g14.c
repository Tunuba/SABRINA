#include "juego.h"

/* La tarjeta de memoria: leer el directorio (los archivos que coinciden con un patron). */

typedef struct {
    s32 evento;                      /* 0x00 ocupada si no es 0 */
    s32 dato;                        /* 0x04 */
    s32 hay;                         /* 0x08 */
    s32 puertos;                     /* 0x0C los puertos en uso (bits) */
    s32 puerto;                      /* 0x10 */
} EstadoTarjetaG14;

extern volatile EstadoTarjetaG14 D_800D52C0;
extern s32 D_800D52D0;               /* el puerto del ultimo error */
extern s32 D_800D5318;
extern char D_80062360[];            /* aviso de tarjeta ocupada */
extern char D_800621BC[];            /* aviso de error sin manejar */

extern s32 printf(const char *f, ...);
extern char *strcat(char *d, const char *s);
extern void func_800508D4(s32 puerto, char *ruta);         /* "buXX:" */
extern void func_80051D14(void);
extern s32 func_80014774(char *ruta, void *entrada);       /* firstfile */
extern s32 nextfile(void *entrada);
extern s32 func_80051EF4(void);
extern s32 func_800507D4(s32 error);
extern s32 func_80051284(s32 modo);
extern s32 func_80051298(s32 modo, s32 *evento, s32 *dato);
extern void UserFuncOpen(void (*f)(void));
extern void func_80050034(void);

/* Busca en la tarjeta del puerto los archivos del patron. Se saltea los primeros `saltar` y copia los
 * `cuantos` siguientes (0x28 bytes cada uno, el DIRENTRY de la BIOS) a destino, si no es NULL; en *n deja
 * cuantos copio. Si la primera busqueda falla 4 veces con un error de la tarjeta, avisa (o arma el
 * manejador del error) y devuelve el error. -1 si la tarjeta estaba ocupada. */
s32 func_80051024(s32 puerto, char *patron, u8 *destino, s32 *n, s32 saltar, s32 cuantos) {
    char ruta[0x20];
    s32 entrada[10];
    s32 error;
    s32 reintentos;
    s32 hay;
    s32 copiados;
    s32 desde;
    s32 i;
    s32 k;

    if (D_800D52C0.evento != 0) {
        printf(D_80062360);
        return -1;
    }
    func_800508D4(puerto, ruta);
    strcat(ruta, patron);
    reintentos = 0;
    i = 0;
    error = 0;
    D_800D52C0.puertos |= 1 << D_800D52C0.puerto;
    copiados = 0;
    desde = 0;
    while (i < saltar + cuantos) {
        if (i == 0) {
            for (;;) {
                func_80051D14();
                hay = func_80014774(ruta, entrada);
                if (hay != 0) {
                    break;
                }
                error = func_800507D4(func_80051EF4());
                if (error == 0) {
                    break;
                }
                reintentos++;
                if (reintentos >= 4) {
                    D_800D5318 = func_80051284(0);
                    if (D_800D52C0.evento > 0) {
                        printf(D_800621BC);
                    } else {
                        D_800D52C0.evento = 2;
                        D_800D52C0.dato = 0;
                        D_800D52C0.hay = 0;
                        D_800D52D0 = puerto;
                        UserFuncOpen(func_80050034);
                    }
                    func_80051298(0, 0, &error);
                    func_80051284(D_800D5318);
                    return error;
                }
            }
        } else {
            hay = nextfile(entrada);
        }
        if (hay == 0) {
            break;
        }
        if (i >= saltar && destino != 0) {
            for (k = 0; k < 10; k++) {
                ((s32 *) (destino + desde))[k] = entrada[k];
            }
            desde += 0x28;
            copiados++;
        }
        i++;
    }
    if (n != 0) {
        *n = copiados;
    }
    return 0;
}
