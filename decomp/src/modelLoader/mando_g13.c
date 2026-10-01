#include "juego.h"

/* Lectura de los mandos (con libpad): un registro de 0x40 bytes por mando en D_80086498, el 0 a 3 del
 * puerto 1 (con multitap) y el 4 a 7 del puerto 2. */

typedef struct {
    s32 activo;                      /* 0x00, 1 normal, 2 sin analogo; 0 no hay */
    s32 analogo;                     /* 0x04, 1 si esta en modo analogo */
    s32 estado;                      /* 0x08, 6 = ya configurado */
    u8 vibra[2];                     /* 0x0C, si hay vibracion pedida (cuestan 10 y 20) */
    u8 _0E[2];
    s32 _10;                         /* 0x10 */
    u8 _14[4];
    s32 espera;                      /* 0x18, intentos antes de configurarlo */
    s32 puerto;                      /* 0x1C, para libpad */
    u16 botones;                     /* 0x20, 1 = apretado */
    u8 ejes[4];                      /* 0x22, los ejes analogos (del buffer van a 2, 3, 0, 1) */
    u8 centro[4];                    /* 0x26, los ejes en reposo */
    u8 _2A[0x12];
    s32 _3C;                         /* 0x3C */
} EstadoMando;
EN(EstadoMando, espera, 0x18);
EN(EstadoMando, botones, 0x20);
EN(EstadoMando, centro, 0x26);
EN(EstadoMando, _3C, 0x3C);

extern EstadoMando D_80086498[8];
extern EstadoMando *D_8007CA70;      /* el primer mando con datos de este paso */
extern s32 D_8007C7F4[2];            /* por puerto: 1 si tiene multitap, -1 si no respondio */
extern s32 D_8007CA7C;               /* lo que gasta la vibracion */
extern u8 D_8007C7E8[];              /* la tabla de actuadores */

extern void func_8001D5C0(s32 puerto);
extern s32 func_800279B8(s32 puerto);
extern u8 func_80027A04(s32 puerto);
extern s32 func_80027AD0(s32 puerto, s32 que, s32 n);
extern s32 func_80027D44(s32 puerto, u8 *tabla);

/* Copia los ejes: sin modo analogo quedan los de reposo. */
static void ejes_en_reposo(EstadoMando *m) {
    m->ejes[2] = m->centro[0];
    m->ejes[3] = m->centro[1];
    m->ejes[0] = m->centro[2];
    m->ejes[1] = m->centro[3];
}

/* Lee los mandos del puerto n del buffer de libpad buf (8 bytes por mando, 2 de cabecera con multitap) y
 * avanza la configuracion de cada uno (analogo, vibracion). Si el puerto no respondio (buf[0] distinto de
 * 0) lo marca con -1 y devuelve 0; si no, 1. */
s32 func_8001D8EC(s32 n, u8 *buf) {
    s32 base, cuantos, desp, i, k, r;
    EstadoMando *m;

    if (buf[0] != 0) {
        D_8007C7F4[n] = -1;
        func_8001D5C0(n);
        return 0;
    }
    if (n == 0) {
        base = 0;
        D_8007C7F4[n] = func_800279B8(0);
    } else {
        base = 4;
        D_8007C7F4[n] = func_800279B8(0x10);
    }
    if (D_8007C7F4[n] == 1) {
        cuantos = 4;
        desp = 2;
    } else {
        cuantos = 1;
        desp = 0;
    }
    cuantos += base;
    for (i = base; i < cuantos; i++) {
        m = &D_80086498[i];
        switch (func_80027A04(m->puerto)) {
        case 0:
        case 4:
            continue;
        case 1:
            m->estado = 1;
            if (m->activo != 0) {
                m->activo = 0;
                m->estado = 0;
                m->analogo = 0;
                m->espera = 6;
                if (m->vibra[0] != 0) {
                    m->vibra[0] = 0;
                    D_8007CA7C -= 10;
                }
                if (m->vibra[1] != 0) {
                    m->vibra[1] = 0;
                    D_8007CA7C -= 20;
                }
            }
            continue;
        case 2:
            if (m->estado != 6) {
                m->estado = 6;
                m->_3C = func_80027AD0(m->puerto, 1, 0);
                continue;
            }
            m->activo = 1;
            break;
        case 6:
            if (m->estado == 6) {
                break;
            }
            if (func_80027AD0(m->puerto, 4, 1) == 7) {
                if (m->espera != 6) {
                    m->espera++;
                    continue;
                }
                if (func_80027D44(m->puerto, D_8007C7E8) == 0) {
                    m->espera = 0;
                    continue;
                }
                r = func_80027AD0(m->puerto, 2, 0);
                m->activo = 1;
                if (r == 4) {
                    m->analogo = 0;
                } else if (r == 7) {
                    m->analogo = 1;
                }
            }
            m->estado = 6;
            m->_10 = 0;
            m->vibra[0] = 0;
            m->vibra[1] = 0;
            continue;
        default:
            break;
        }
        /* 3, 5, 7 o mas, o los que vienen de arriba: leer los botones */
        k = desp + (i - base) * 8;
        if (m->activo == 1) {
            m->botones = ~((buf[k + 2] << 8) | buf[k + 3]);
            if (m->analogo == 0) {
                ejes_en_reposo(m);
            } else if (m->analogo == 1) {
                m->ejes[2] = buf[k + 4];
                m->ejes[3] = buf[k + 5];
                m->ejes[0] = buf[k + 6];
                m->ejes[1] = buf[k + 7];
            }
            if (D_8007CA70 == NULL) {
                D_8007CA70 = m;
            }
        } else if (m->activo == 2) {
            m->botones = ~((buf[k + 2] << 8) | buf[k + 3]);
            ejes_en_reposo(m);
            D_8007CA70 = m;
        }
    }
    return 1;
}
