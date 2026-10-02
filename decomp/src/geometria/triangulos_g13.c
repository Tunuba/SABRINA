#include "gte.h"

/* Pasar una tira de triangulos con textura a primitivas de la GPU (POLY_GT3, 0x28 bytes). */

/* Un triangulo del modelo (0x1C bytes). */
typedef struct {
    s32 *v[3];                       /* 0x00, cada vertice: x, y (16 bits) y z; el color en +8 */
    u8 *textura;                     /* 0x0C: en +0xC y +0xE la pagina y la paleta, en +0x1C las banderas */
    s16 uv[3];                       /* 0x10 */
    u8 _16[6];
} TrianguloTex;

#define P8(p, d) (*(u8 *)((u8 *)(p) + (d)))
#define P16(p, d) (*(s16 *)((u8 *)(p) + (d)))
#define P32(p, d) (*(u32 *)((u8 *)(p) + (d)))

/* Para cada uno de los n triangulos: lo pasa a pantalla; si su area en pantalla es negativa (o la textura es de dos caras),
 * su z mas lejana esta entre 0x18 y 0x3FF y algun vertice cae en la pantalla, arma la primitiva en prim y
 * la pone en la tabla de orden ot por su z. Devuelve el siguiente lugar libre para primitivas. */
u8 *func_80020294(u8 *prim, TrianguloTex *t, u32 *ot, s32 n) {
    u32 z, z1, banderas;
    s32 a, b, c;
    u8 codigo;
    u32 *o;

    do {
        gte_poner_v0(t->v[0]);
        gte_poner_v1(t->v[1]);
        gte_poner_v2(t->v[2]);
        gte_rtpt();
        gte_leer_banderas(banderas);
        gte_nclip();
        gte_guardar_mac0(prim + 8);
        if ((s32)P32(prim, 8) < 0 || (t->textura[0x1C] & 4)) {
            __asm__ volatile("swc2 $17, 8(%0)" :: "r"(prim) : "memory");
            __asm__ volatile("swc2 $18, 0x14(%0)" :: "r"(prim) : "memory");
            __asm__ volatile("swc2 $19, 0x20(%0)" :: "r"(prim) : "memory");
            z = P32(prim, 8);
            z1 = P32(prim, 0x14);
            if (z < z1) {
                z = z1;
            }
            z1 = P32(prim, 0x20);
            if (z < z1) {
                z = z1;
            }
            z = (s32)z >> 4;
            if ((s32)z >= 0x18 && (s32)z < 0x400) {
                codigo = P8(prim, 7);
                __asm__ volatile("swc2 $12, 8(%0)" :: "r"(prim) : "memory");
                __asm__ volatile("swc2 $13, 0x14(%0)" :: "r"(prim) : "memory");
                __asm__ volatile("swc2 $14, 0x20(%0)" :: "r"(prim) : "memory");
                a = P16(prim, 8);
                b = P16(prim, 0x14);
                c = P16(prim, 0x20);
                if ((a >= 0 || b >= 0 || c > 0) && (a < 0x200 || b < 0x200 || c < 0x200)) {
                    a = P16(prim, 0xA);
                    b = P16(prim, 0x16);
                    c = P16(prim, 0x22);
                    if ((a >= 0 || b >= 0 || c > 0) && (a < 0xDC || b < 0xDC || c < 0xDC)) {
                        P32(prim, 4) = t->v[0][2];
                        P32(prim, 0x10) = t->v[1][2];
                        P32(prim, 0x1C) = t->v[2][2];
                        P8(prim, 7) = codigo;
                        P16(prim, 0xC) = t->uv[0];
                        P16(prim, 0x18) = t->uv[1];
                        P16(prim, 0x24) = t->uv[2];
                        P16(prim, 0x1A) = *(u16 *)(t->textura + 0xC);
                        P16(prim, 0xE) = *(u16 *)(t->textura + 0xE);
                        if (t->textura[0x1C] & 1) {
                            P8(prim, 7) |= 2;
                        }
                        o = ot + z;
                        P32(prim, 0) = (P32(prim, 0) & 0xFF000000) | (*o & 0xFFFFFF);
                        *o = (*o & 0xFF000000) | ((u32)prim & 0xFFFFFF);
                        prim += 0x28;
                    }
                }
            }
        }
        t++;
    } while (--n != 0);
    return prim;
}

/* SetGeomOffset: el centro de la pantalla para el GTE (OFX y OFY, en 16.16). */
void func_80017B5C(s32 x, s32 y) {
    __asm__ volatile("ctc2 %0, $24" :: "r"(x << 16));
    __asm__ volatile("ctc2 %0, $25" :: "r"(y << 16));
}

/* SetGeomScreen: la distancia a la pantalla (H). */
void func_80017B7C(s32 h) {
    __asm__ volatile("ctc2 %0, $26" :: "r"(h));
}
