#include "juego.h"

/* CdSync y CdReady de la libcd de PsyQ: esperan a que el lector de CD termine la orden (o tenga datos),
 * atendiendo a mano sus interrupciones cuando estan cortadas, con un tope de tiempo. */

extern s32 D_80091460;                 /* hasta cuando esperar (en cuadros) */
extern s32 D_80091464;                 /* vueltas de la espera */
extern char *D_80091468;               /* el nombre de la funcion que espera, para el aviso */
extern u8 D_80091448[8];               /* el ultimo estado de fin de orden */
extern u8 D_80091450[8];               /* el ultimo estado de datos listos */
extern u8 D_80091458[8];
extern char D_80061380[], D_80061390[], D_80061408[], D_80061410[];
extern char *D_8006D328[];             /* nombres de las ordenes */
extern char *D_8006D3A8[];             /* nombres de los estados */
extern u8 D_8006D321;                  /* la ultima orden */
extern u8 D_8006D2C8[3];               /* fin de orden, datos listos, listo para leer */
extern volatile u8 *D_8006D2B0;        /* el registro de indice del lector */
extern void (*D_8006D304)(s32 estado, u8 *res);   /* aviso de fin de orden */
extern void (*D_8006D308)(s32 estado, u8 *res);   /* aviso de datos listos */
extern s32 func_8001626C(s32);         /* VSync */
extern s32 func_80016A04(void);        /* las interrupciones estan cortadas */
extern s32 func_8002A09C(void);        /* atender la interrupcion del lector */
extern void func_8002B0AC(void);       /* reiniciar el lector */
extern s32 puts(char *s);
extern s32 printf(char *fmt, ...);

static inline s32 se_paso(void) {
    if (D_80091460 < func_8001626C(-1) || D_80091464++ > 0x3C0000) {
        puts(D_80061380);
        printf(D_80061390, D_80091468, D_8006D328[D_8006D321], D_8006D3A8[D_8006D2C8[0]],
               D_8006D3A8[D_8006D2C8[1]]);
        func_8002B0AC();
        return -1;
    }
    return 0;
}

static inline void atender(void) {
    u8 i;
    s32 r;
    if (func_80016A04() != 0) {
        i = *D_8006D2B0 & 3;
        while ((r = func_8002A09C()) != 0) {
            if ((r & 4) && D_8006D308 != 0) {
                D_8006D308(D_8006D2C8[1], D_80091450);
            }
            if ((r & 2) && D_8006D304 != 0) {
                D_8006D304(D_8006D2C8[0], D_80091448);
            }
        }
        *D_8006D2B0 = i;
    }
}

/* CdSync(modo, res): con modo 0 espera a que termine la orden; si no, solo mira. Devuelve el estado
 * (2 completa, 5 error) y copia el resultado en res, 0 si sigue en curso o -1 si se paso el tiempo. */
s32 func_8002A6D0(s32 modo, u8 *res) {
    s32 e;
    s32 k;
    u8 *de;

    D_80091460 = func_8001626C(-1) + 0x3C0;
    D_80091464 = 0;
    D_80091468 = D_80061408;
    for (;;) {
        if (se_paso() != 0) {
            return -1;
        }
        atender();
        e = D_8006D2C8[0];
        if (e == 2 || e == 5) {
            D_8006D2C8[0] = 2;
            de = D_80091448;
            if (res != 0) {
                for (k = 7; k != -1; k--) {
                    *res++ = *de++;
                }
            }
            return e;
        }
        if (modo != 0) {
            return 0;
        }
    }
}

/* CdReady(modo, res): igual, pero espera datos listos para leer. */
s32 func_8002A950(s32 modo, u8 *res) {
    s32 e;
    s32 k;
    u8 *de;

    D_80091460 = func_8001626C(-1) + 0x3C0;
    D_80091464 = 0;
    D_80091468 = D_80061410;
    for (;;) {
        if (se_paso() != 0) {
            return -1;
        }
        atender();
        e = D_8006D2C8[2];
        if (e != 0) {
            D_8006D2C8[2] = 0;
            de = D_80091458;
        } else {
            e = D_8006D2C8[1];
            if (e == 0) {
                if (modo != 0) {
                    return 0;
                }
                continue;
            }
            D_8006D2C8[1] = 0;
            de = D_80091450;
        }
        if (res != 0) {
            for (k = 7; k != -1; k--) {
                *res++ = *de++;
            }
        }
        return e;
    }
}
