#include "juego.h"

/* Abrir, escribir y cerrar archivos de la tarjeta de memoria (libcard sobre las llamadas de archivo de la BIOS).
 * 05-10: los borradores de m2c (src/auto) llamaban a open(), close(), lseek() y write() sin argumentos, porque
 * prototipos.h las declara (void); pasaban como IGUAL / IGUAL_SINT hasta que verificar.py empezo a comparar las
 * llamadas a la BIOS. Aqui van con los argumentos que les pasa la original.
 *
 * D_800D52C0, el estado de la tarjeta:
 *   [0] evento abierto (1 o 2, <= 0 libre)  [1] resultado del paso (3 = sigue, 5 = error)  [2] listo
 *   [3] mascara de puertos usados  [4] puerto  [5] archivo abierto (-1 cerrado)  [6] desde  [7] n  [8] destino
 *   [9..] nombre del archivo ("bu00:..." armado por func_800508D4) */

#define TARJ_ARCHIVO 5
#define TARJ_DESDE   6
#define TARJ_N       7
#define TARJ_DESTINO 8

extern s32 D_800D52C0[];
extern s32 D_800D52B4;                  /* resultado que deja la rutina de la tarjeta */
extern s32 D_800D5318;                  /* estado de interrupciones guardado */
extern s32 D_80075B30;                  /* reintentos de la escritura */
extern s32 D_80075B34;
extern s32 D_80075B38;
extern char D_800622B8[];               /* "...already open" */
extern char D_800621BC[];               /* "Access Denied. : event multiple open" */
extern char D_80062360[];

extern s32 open(char *nombre, s32 modo);
extern s32 lseek(s32 archivo, s32 desde, s32 modo);
extern s32 write(s32 archivo, void *desde, s32 n);
extern s32 close(s32 archivo);
extern s32 printf(const char *formato, ...);
extern char *strcat(char *a, const char *b);
extern void UserFuncOpen(void *f);
extern void _card_clear(s32 puerto);
extern void func_800508D4(s32 puerto, char *nombre);
extern s32 func_80051284(s32 estado);
extern void func_80051298(s32 a, s32 b, s32 *resultado);
extern void func_80051D14(void);
extern s32 func_80051E1C(void);
extern void func_80051EF4(void);
extern s32 func_80051FCC(void);
extern s32 func_80052008(void);
extern s32 func_800507D4(s32 error);
extern s32 func_8004FD34();
extern s32 func_80050034();
extern s32 func_800502DC();
extern s32 func_80050418();

#define NOMBRE ((char *) &D_800D52C0[9])

/* Un paso de la escritura, como maquina de estados en *estado (la pareja de func_800502DC, que lee): en 0 pone
 * los reintentos en 0; en 10 se posiciona y lanza la escritura (y pasa a 30); en 30, si la tarjeta ya contesto,
 * con error reintenta desde 10 hasta 4 veces; al final guarda lo que da func_800507D4 en [1] y devuelve 1. */
s32 func_80050418(s32 *estado) {
    s32 error;

    switch (*estado) {
    case 0:
        D_80075B30 = 0;
        *estado = 10;
        return 0;
    case 10:
        while (lseek(D_800D52C0[TARJ_ARCHIVO], D_800D52C0[TARJ_DESDE], 0) != D_800D52C0[TARJ_DESDE]) {
        }
        func_80051D14();
        while (write(D_800D52C0[TARJ_ARCHIVO], (void *) D_800D52C0[TARJ_DESTINO], D_800D52C0[TARJ_N]) != 0) {
        }
        *estado = 30;
        return 0;
    case 30:
        if (func_80051FCC() == 0) {
            return 0;
        }
        error = func_80051E1C();
        if (error != 0) {
            if (++D_80075B30 < 4) {
                *estado = 10;
                return 0;
            }
        } else {
            error = 0;
        }
        D_800D52C0[1] = func_800507D4(error);
        return 1;
    }
    return 0;
}

/* Abrir el archivo del nombre ya armado y lanzar una lectura (func_800502DC) o una escritura (func_80050418) por
 * eventos; 20 la cierra o, si la tarjeta pide seguir (3), limpia el puerto y espera en 22 para volver a 11. */
static s32 abrir_y_pasar(u32 *estado, s32 *reintentos, void *paso) {
    s32 archivo;

    switch (*estado) {
    case 0:
        *reintentos = 0;
        UserFuncOpen(func_8004FD34);
        *estado = 10;
        return 0;
    case 10:
        if (D_800D52C0[1] != 0) {
            return 1;
        }
        archivo = open(NOMBRE, 0x8001);
        D_800D52C0[TARJ_ARCHIVO] = archivo;
        if (archivo < 0) {
            D_800D52C0[1] = 5;
            return 1;
        }
        /* sigue en 11 */
    case 11:
        *estado = 20;
        UserFuncOpen(paso);
        return 0;
    case 20:
        if (D_800D52C0[1] == 3) {
            func_80051D14();
            _card_clear(D_800D52C0[4]);
            *estado = 22;
            return 0;
        }
        close(D_800D52C0[TARJ_ARCHIVO]);
        D_800D52C0[TARJ_ARCHIVO] = -1;
        return 1;
    case 22:
        if (func_80052008() == 0) {
            return 0;
        }
        func_80051EF4();
        *estado = 11;
        return 0;
    }
    return 0;
}

s32 func_80050554(u32 *estado) {
    return abrir_y_pasar(estado, &D_80075B34, func_800502DC);
}

s32 func_80050694(u32 *estado) {
    return abrir_y_pasar(estado, &D_80075B38, func_80050418);
}

/* Abre bu<puerto>:<nombre> para escribir (modo | 0x8000) despues de comprobar que existe (abrir con 1 y cerrar).
 * Si no se puede abrir, pregunta a la tarjeta (evento 2, func_80050034) y reintenta: con 3 enseguida, con 2 hasta
 * 5 veces. Devuelve 0 si quedo abierto, -1 si ya habia uno abierto, o el codigo de la tarjeta (0 pasa a 5). */
s32 func_80050AB8(s32 puerto, char *nombre, s32 modo) {
    s32 resultado;
    s32 veces = 0;

    if (D_800D52C0[TARJ_ARCHIVO] >= 0) {
        printf(D_800622B8);
        return -1;
    }
    func_800508D4(puerto, NOMBRE);
    strcat(NOMBRE, nombre);
    D_800D52C0[4] = puerto;
    for (;;) {
        s32 archivo = open(NOMBRE, 1);

        if (archivo >= 0) {
            close(archivo);
            func_80051D14();
            D_800D52C0[TARJ_ARCHIVO] = open(NOMBRE, modo | 0x8000);
            return 0;
        }
        D_800D5318 = func_80051284(0);
        if (D_800D52C0[0] > 0) {
            printf(D_800621BC);
        } else {
            D_800D52C0[0] = 2;
            D_800D52C0[1] = 0;
            D_800D52C0[2] = 0;
            D_800D52C0[4] = puerto;
            UserFuncOpen(func_80050034);
        }
        func_80051298(0, 0, &resultado);
        func_80051284(D_800D5318);
        if (resultado == 3) {
            continue;
        }
        if (resultado != 2 || ++veces >= 5) {
            break;
        }
    }
    if (resultado == 0) {
        resultado = 5;
    }
    return resultado;
}

/* Cierra el archivo de la tarjeta si hay uno abierto. */
void func_80050C40(void) {
    if (D_800D52C0[TARJ_ARCHIVO] >= 0) {
        close(D_800D52C0[TARJ_ARCHIVO]);
        D_800D52C0[TARJ_ARCHIVO] = -1;
    }
}

/* Crea bu<puerto>:<nombre> con bloques en la parte alta del modo (bloques << 16 | 0x200). Devuelve 6 si ya
 * existe, 0 si se creo, -1 si habia un evento abierto, 7 si la tarjeta no contesto nada, y si no el codigo de la
 * tarjeta (reintenta con 3 enseguida y con 2 hasta 4 veces; 0 pasa a 5). */
s32 func_800513B4(s32 puerto, char *nombre, s32 bloques) {
    char ruta[32];
    s32 resultado;
    s32 veces = 0;
    s32 archivo;
    volatile s32 *tarjeta = D_800D52C0;

    if (D_800D52C0[0] != 0) {
        printf(D_80062360);
        return -1;
    }
    func_800508D4(puerto, ruta);
    strcat(ruta, nombre);
    D_800D52C0[3] |= 1 << D_800D52C0[4];
    archivo = open(ruta, 1);
    if (archivo >= 0) {
        close(archivo);
        return 6;
    }
    for (;;) {
        archivo = open(ruta, (bloques << 16) | 0x200);
        if (archivo >= 0) {
            close(archivo);
            return 0;
        }
        D_800D5318 = func_80051284(0);
        if (D_800D52C0[0] > 0) {
            printf(D_800621BC);
        } else {
            D_800D52C0[0] = 2;
            D_800D52C0[1] = 0;
            D_800D52C0[2] = 0;
            D_800D52C0[4] = puerto;
            UserFuncOpen(func_80050034);
        }
        if (tarjeta[0] != 0 || tarjeta[2] != 0) {
            (void) tarjeta[0];
            (void) tarjeta[1];
            if (tarjeta[2] == 0) {
                while (tarjeta[2] == 0) {
                }
            }
            resultado = D_800D52B4;
            tarjeta[2] = 0;
        }
        func_80051284(D_800D5318);
        if (resultado == 0) {
            return 7;
        }
        if (resultado == 3) {
            continue;
        }
        if (resultado != 2 || ++veces >= 4) {
            break;
        }
    }
    if (resultado == 0) {
        resultado = 5;
    }
    return resultado;
}
