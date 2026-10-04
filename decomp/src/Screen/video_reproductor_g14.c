#include "juego.h"

/* El reproductor de video STR: abre el archivo, decodifica cuadro por cuadro con el MDEC y lo pasa a la
 * pantalla hasta que el video termina, se corta o el CD deja de responder. */

extern u8 D_800D5818[];              /* el estado del reproductor */
extern s16 D_800D5848;               /* el video llego al final */
extern s16 D_800D584E;               /* el bufer de entrada que toca */
extern s16 D_800D5850;               /* el bufer de salida que toca */
extern char D_8007C930[];            /* el nombre de este archivo, para Reservar */
extern s32 D_8007CC88;               /* bufer de los sectores (512 KB) */
extern s32 D_8007CC8C;               /* bufer de la imagen decodificada */
extern s32 D_8007CC94;               /* cuadros del fundido al cortar */

extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void Afirmar(s32 cond, char *archivo, s32 linea);
extern void Liberar(void *p);
extern void func_8005D844(void);
extern void CdMix(u8 *volumen);
extern s32 func_8002BE88(u8 *archivo, s32 nombre);         /* CdSearchFile */
extern void func_8005C964(void);
extern void func_8005C9D0(s32 *pedido);
extern s32 func_8005CD98(u8 *archivo);
extern void func_8005CE48(void);                           /* cerrar el video */
extern s32 func_8005CEBC(void);                            /* el siguiente cuadro del CD (0 si no hay) */
extern void func_8005D02C(s32 cuadro);
extern s32 func_8005D0D0(void);
extern s32 func_8005D0F4(void);
extern void func_8005DCD4(s32 datos, s32 n);
extern void func_8005DD50(s32 bufer, s32 ancho);
extern void SpuSetCommonMasterVolume(s32 izq, s32 der);
extern void func_8001D778(void);
extern s32 func_8005D164(s16 *fundido);
extern void func_8005D3F4(void);
extern void func_8005D1D0(void);
extern s32 func_80012D74(s32 modo);                        /* DrawSync */
extern s32 func_8001626C(s32 modo);                        /* VSync */
extern void GsSwapDispBuff(void);

#define V32(d) (*(s32 *)(D_800D5818 + (d)))

/* pedido: 0x00 el nombre del archivo y el resto lo lee func_8005C9D0. cada_cuadro se llama mientras no se
 * haya pedido cortar; si devuelve distinto de 0, corta con un fundido de D_8007CC94 cuadros.
 * Devuelve 0 si se corto sin fundido, 1 si el video termino, 3 si fallo o el CD dejo de mandar cuadros, o
 * lo que devuelva el fundido. */
s32 func_8005D50C(s32 *pedido, s32 (*cada_cuadro)(void)) {
    u8 archivo[0x18];
    u8 volumen[4];
    s16 fundido;
    s16 vacios;
    s16 r;
    s32 c;
    s32 n;

    vacios = 0;
    r = 0;
    fundido = 0;
    D_8007CC88 = (s32) Reservar(0x80000, D_8007C930, 0x157);
    Afirmar(D_8007CC88 != 0, D_8007C930, 0x158);
    D_8007CC8C = (s32) Reservar(0x11000, D_8007C930, 0x159);
    func_8005D844();
    volumen[0] = 0x80;
    volumen[1] = 0x80;
    volumen[2] = 0x80;
    volumen[3] = 0x80;
    CdMix(volumen);
    if (func_8002BE88(archivo, pedido[0]) == 0) {
        Liberar((void *) D_8007CC88);
        Liberar((void *) D_8007CC8C);
        return 3;
    }
    func_8005C964();
    func_8005C9D0(pedido);
    if (func_8005CD98(archivo) == 0) {
        func_8005CE48();
        Liberar((void *) D_8007CC88);
        Liberar((void *) D_8007CC8C);
        return 3;
    }
    while ((c = func_8005CEBC()) == 0) {
        vacios++;
        if (vacios == 5) {
            func_8005CE48();
            Liberar((void *) D_8007CC88);
            Liberar((void *) D_8007CC8C);
            return 3;
        }
    }
    vacios = 0;
    func_8005D02C(c);
    while (D_800D5848 == 0 && r == 0) {
        n = func_8005D0D0();
        func_8005DCD4(V32(0x3C + D_800D584E * 4), n);
        n = func_8005D0F4();
        func_8005DD50(V32(0x44 + D_800D5850 * 4), n);
        c = func_8005CEBC();
        if (c == 0) {
            vacios++;
            if (vacios == 5) {
                r = 3;
            }
        } else {
            vacios = 0;
        }
        func_8005D02C(c);
        SpuSetCommonMasterVolume(0x3FFF, 0x3FFF);
        func_8001D778();
        if (fundido == 0 && cada_cuadro() != 0) {
            if (D_8007CC94 > 0) {
                fundido = D_8007CC94;
            } else {
                fundido = 0;
            }
        }
        if (fundido != 0) {
            r = func_8005D164(&fundido);
        } else {
            func_8005D3F4();
        }
        func_8005D1D0();
        func_80012D74(0);
        func_8001626C(0);
        GsSwapDispBuff();
    }
    func_8005CE48();
    if (D_800D5848 != 0) {
        r = 1;
    }
    Liberar((void *) D_8007CC88);
    Liberar((void *) D_8007CC8C);
    return r;
}
