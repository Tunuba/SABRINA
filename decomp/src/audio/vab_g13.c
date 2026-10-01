#include "juego.h"

/* libsnd: abrir la cabecera de un banco de sonidos VAB (como _SsVabOpenHeadWithMode de la biblioteca). */

/* Cabecera del VAB ("pBAV"). */
typedef struct {
    u32 magia;                       /* 0x00, "VABp" al reves: 0x564142 arriba y 'p' abajo */
    s32 version;                     /* 0x04 */
    u8 _08[0x0A];
    u16 programas;                   /* 0x12 */
    u16 _14;
    u8 vags;                         /* 0x16, cuantos sonidos (el byte bajo) */
    u8 _17[9];
} CabVab;
EN(CabVab, programas, 0x12);
EN(CabVab, vags, 0x16);

/* Atributos de un programa (16 bytes); en lo que la biblioteca deja libre se guardan cosas. */
typedef struct {
    u8 tonos;                        /* 0x00 */
    u8 _01[7];
    s32 primer_tono;                 /* 0x08, cuantos tonos hay en los programas anteriores */
    u16 dir_par;                     /* 0x0C, direccion en el SPU / 8 de un sonido de numero par */
    u16 dir_impar;                   /* 0x0E, y la del siguiente */
} AtribProg;
EN(AtribProg, primer_tono, 0x08);
EN(AtribProg, dir_impar, 0x0E);

extern u8 D_800C76CC[16];            /* por banco: 0 libre, 1 abriendose, 2 abierto */
extern u16 D_800C76DE;               /* cuantos bancos hay abiertos */
extern s16 D_800C76E0;               /* programas que caben en la cabecera */
extern s32 D_800C76B4;
extern CabVab *D_800C7704[16];
extern AtribProg *D_800C7744[16];
extern u8 *D_800C7784[16];           /* los atributos de los tonos */
extern s32 D_800C77C4[16];           /* donde quedan los sonidos en el SPU */
extern s32 D_800C7804[16];           /* cuanto ocupan */

extern s32 func_8003FD90(void);
extern void func_8003FD68(s32 a);

typedef s32 (*Reservador)(s32 tam, s32 dato, s32 banco, void *a3);

/* Abre la cabecera vab en el banco id (-1: el primero libre). reservar da el lugar en el SPU para todos
 * los sonidos; con eso anota donde queda cada uno. Devuelve el banco o -1. */
s16 func_800447E4(CabVab *vab, s32 id, Reservador reservar, s32 dato) {
    s32 tam[256];
    s32 banco = 16;
    s32 i, n, suma, total, dir, ultimo;
    AtribProg *prog;
    u8 *tonos;
    u16 *tabla;

    if (func_8003FD90() == 1) {
        return -1;
    }
    func_8003FD68(1);
    if ((s16)id >= 16) {
        func_8003FD68(0);
        return -1;
    }
    if ((s16)id == -1) {
        for (i = 0; i < 16; i++) {
            if (D_800C76CC[i] == 0) {
                D_800C76CC[i] = 1;
                banco = i;
                D_800C76DE++;
                break;
            }
        }
    } else if (D_800C76CC[(s16)id] == 0) {
        D_800C76CC[(s16)id] = 1;
        banco = id;
        D_800C76DE++;
    }
    if ((s16)banco >= 16) {
        func_8003FD68(0);
        return -1;
    }
    D_800C7704[(s16)banco] = vab;
    D_800C76B4 = 0;
    if ((vab->magia >> 8) != 0x564142) {
        D_800C76CC[(s16)banco] = 0;
        goto falla;
    }
    n = 0x40;
    if ((vab->magia & 0xFF) == 0x70 && vab->version >= 5) {
        n = 0x80;
    }
    D_800C76E0 = n;
    if (D_800C76E0 < vab->programas) {
        D_800C76CC[(s16)banco] = 0;
        goto falla;
    }
    prog = (AtribProg *)(vab + 1);
    D_800C7744[(s16)banco] = prog;
    tonos = (u8 *)prog + D_800C76E0 * 16;
    suma = 0;
    for (i = 0; i < D_800C76E0; i++) {
        prog[i].primer_tono = suma;
        if (prog[i].tonos != 0) {
            suma++;
        }
    }
    D_800C7784[(s16)banco] = tonos;
    ultimo = vab->vags;
    tabla = (u16 *)(tonos + (vab->programas << 9));
    suma = 0;
    for (i = 0; i < 256; i++, tabla++) {
        if (ultimo >= i) {
            tam[i] = vab->version >= 5 ? *tabla * 8 : *tabla * 4;
            suma += tam[i];
        }
    }
    total = (suma + 0x3F) & ~0x3F;
    dir = reservar(total, dato, (s16)banco, tabla);
    if (dir == -1) {
        return -1;
    }
    if ((u32)(dir + total) > 0x80000) {
        D_800C76CC[(s16)banco] = 0;
        goto falla;
    }
    D_800C77C4[(s16)banco] = dir;
    suma = 0;
    for (i = 0; i <= ultimo; i++) {
        suma += tam[i];
        if (!(i & 1)) {
            prog[i / 2].dir_par = (u32)(dir + suma) >> 3;
        } else {
            prog[i / 2].dir_impar = (u32)(dir + suma) >> 3;
        }
    }
    D_800C7804[(s16)banco] = suma;
    D_800C76CC[(s16)banco] = 2;
    return banco;

falla:
    func_8003FD68(0);
    D_800C76DE--;
    return -1;
}
