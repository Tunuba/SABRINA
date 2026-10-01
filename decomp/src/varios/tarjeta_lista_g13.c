#include "juego.h"

/* La pantalla de la tarjeta de memoria: leer el directorio y los iconos de las partidas. */

typedef struct {
    s16 x, y, w, h;
} RectT;

/* Una entrada del directorio de la tarjeta (0x28 bytes). */
typedef struct {
    u8 _00[0x18];
    s32 tam;                         /* 0x18, en bytes (de a 0x2000 por bloque) */
    u8 _1C[0x0C];
} EntradaTarjeta;

/* Donde va el icono de cada partida (0x20 bytes, en D_800D50B0). */
typedef struct {
    u8 _00[8];
    s16 w, h;                        /* 0x08 */
    u8 _0C[6];
    s16 x, y;                        /* 0x12 */
    u16 clut_x, clut_y;              /* 0x16 */
    u8 _1A[6];
} LugarIcono;

extern RectT D_8007C8E4;
extern char D_8007C8EC[];            /* "*" */
extern s16 D_8007CA20;
extern s32 D_8007CC40;
extern u16 D_8007CC56, D_8007CC58, D_8007CC5A;
extern s32 D_800D15E4[];             /* por puerto: cuantas entradas */
extern EntradaTarjeta D_800D1810[][15];
extern u8 D_800D2AD0[][0x40];        /* la paleta de cada icono */
extern u8 D_800D2E90[], D_800D2E94[], D_800D2EF0[], D_800D2F10[];  /* el encabezado leido */
extern u16 D_800D5090[];             /* 1 si la partida tiene icono propio */
extern LugarIcono D_800D50B0[];
extern u8 D_80075A04[], D_80075A84[];  /* el icono vacio y su paleta */

extern s32 func_80051024(s32 puerto, char *nombre, EntradaTarjeta *dir, s32 *n, s32 a, s32 max);
extern s32 func_80050AB8(s32 puerto, EntradaTarjeta *e, s32 a);
extern s32 func_80051298(s32 a, s32 b, s32 *c);
extern void func_80050C84(u8 *d, s32 a, s32 n);
extern void func_80050C40(void);
extern void SubirAVRAM(RectT *r, void *datos);
extern s32 func_80012D74(s32 modo);  /* DrawSync */
extern void LoadClut2(void *clut, s32 x, s32 y);
extern void *memcpy(void *d, const void *s, u32 n);

/* Pone en la VRAM el icono i (el de la partida o el vacio). */
static void icono(s32 i, void *datos, void *clut) {
    RectT r;

    r.x = D_800D50B0[i].x;
    r.y = D_800D50B0[i].y;
    r.w = D_800D50B0[i].w / 4;
    r.h = D_800D50B0[i].h;
    SubirAVRAM(&r, datos);
    func_80012D74(0);
    LoadClut2(clut, D_800D50B0[i].clut_x, D_800D50B0[i].clut_y);
}

/* Lee el directorio del puerto hasta que salga bien y, por cada una de las 15 entradas, carga su icono
 * (o el vacio si no ocupa bloques) y cuenta los bloques usados y libres. */
void func_8004EEF4(s32 puerto, s32 n) {
    s32 *cuantos;
    EntradaTarjeta *dir, *d;
    u16 i;
    s32 r;

    D_8007CA20 = 0xEC;
    if (D_8007CC56 != 2) {
        return;
    }
    cuantos = &D_800D15E4[n];
    dir = D_800D1810[n];
    do {
        D_8007CC40 = func_80051024(puerto, D_8007C8EC, dir, cuantos, 0, 0xF);
        if (D_8007CC40 != 0) {
            continue;
        }
        d = dir;
        D_8007CC58 = 0;
        for (i = 0; i != 0xF; i++, d++) {
            D_8007CC58 += (u16)(d->tam / 0x2000);
            if (d->tam / 0x2000 != 0) {
                r = func_80050AB8(puerto, d, 1);
                if (r == 0) {
                    func_80051298(0, 0, &r);
                    func_80050C84(D_800D2E90, 0, 0x200);
                    func_80051298(0, 0, &r);
                    func_80050C40();
                    icono(i, D_800D2F10, D_800D2EF0);
                    memcpy(D_800D2AD0[i], D_800D2E94, 0x40);
                    D_800D5090[i] = 1;
                } else {
                    D_8007CC58--;
                }
            } else {
                D_8007CC5A++;
                icono(i, D_80075A04, D_80075A84);
                D_800D5090[i] = 0;
            }
        }
        D_8007CA20 = 0;
    } while (D_8007CC40 != 0);
}
