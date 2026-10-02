#include "juego.h"

/* El arranque en pantalla: las pantallas legales y los videos (STR). */

typedef struct {
    s16 x, y, w, h;
} RectV;

extern RectV D_8007C9E0;             /* lo que se borra entre pantallas */
extern RectV D_8007C77C;             /* donde va cada pantalla legal en la VRAM */
extern s32 D_80065408[4];            /* cuadros que dura cada una */
extern char *D_8007C740[4];          /* sus nombres */
extern char D_8007C784[];            /* "%s%s" */
extern char D_8007A1D0[];            /* la carpeta */
extern char D_80065418[];            /* el aviso si falta una */
extern s32 D_8007CA58;               /* botones recien apretados */

extern s32 func_80012CDC(s32 mascara);  /* SetDispMask */
extern s32 func_80021120(RectV r);   /* borra la pantalla */
extern void func_80017158(s32 w, s32 h, s32 a, s32 b, s32 c);
extern void GsDefDispBuff(s32 x0, s32 y0, s32 x1, s32 y1);
extern void func_80021A94(s32 a, s32 b, s32 c, s32 d);
extern void func_80017B5C(s32 a, s32 b);
extern s32 func_80017B7C(s32 a);
extern s32 sprintf(char *d, const char *f, ...);
extern s32 printf(const char *f, ...);
extern void *CargarArchivoEntero(char *nombre, s32 a);
extern void func_8001D778(void);     /* espera una vuelta de la pantalla */
extern void func_800219C8(void);
extern void SubirAVRAM(RectV *r, void *datos);
extern void Liberar(void *p);
extern void HerramientaConvertirPIC(char *nombre);

/* Pasa un video: apaga la pantalla, la borra, arma la pantalla de 320x240 y lo reproduce; al final borra y
 * vuelve a la de 256. */
s32 ReproducirSTR(s32 video, s32 b) {
    func_80012CDC(0);
    func_80021120(D_8007C9E0);
    func_80017158(0x140, 0xF0, 4, 1, 0);
    GsDefDispBuff(0, 0, 0, 0x100);
    func_80012CDC(1);
    func_80021A94(video, 0, 0x28, b);
    func_80021120(D_8007C9E0);
    func_80012CDC(1);
    func_80017B5C(0x100, 0x6E);
    return func_80017B7C(0x190);
}

/* Las cuatro pantallas legales: carga cada imagen, la sube a la VRAM y espera sus cuadros (desde la
 * segunda, un boton la corta). Si falta una, convierte las imagenes de la herramienta, avisa y se queda. */
s32 PantallasLegales(void) {
    RectV r = D_8007C77C;
    char nombre[0x80];
    s32 espera[4];
    void *p;
    s32 n;
    u16 i;

    espera[0] = D_80065408[0];
    espera[1] = D_80065408[1];
    espera[2] = D_80065408[2];
    espera[3] = D_80065408[3];
    for (i = 0; i != 4; i++) {
        sprintf(nombre, D_8007C784, D_8007A1D0, D_8007C740[i]);
        p = CargarArchivoEntero(nombre, 0);
        if (p == NULL) {
            HerramientaConvertirPIC(D_8007C740[0]);
            HerramientaConvertirPIC(D_8007C740[1]);
            HerramientaConvertirPIC(D_8007C740[2]);
            HerramientaConvertirPIC(D_8007C740[3]);
            printf(D_80065418);
            for (;;) {
            }
        }
        func_8001D778();
        func_800219C8();
        SubirAVRAM(&r, p);
        Liberar(p);
        n = espera[i];
        if (i != 0) {
            while (D_8007CA58 == 0 && n != 0) {
                func_8001D778();
                n--;
            }
        } else {
            while (n != 0) {
                func_8001D778();
                n--;
            }
        }
    }
    return func_80021120(D_8007C9E0);
}

extern s32 func_80016970(s32 canal, s32 f);
extern void SsSetSerialVol(s32 s, s32 izq, s32 der);
extern s32 func_8005D9C0(u32 *p, s32 v);
extern s32 D_8007CC98, D_8007CC9C, D_8007CCA0, D_8007CCA4;

typedef struct {
    s16 left, right;
} VolumenV;

typedef struct {
    u32 mask;
    VolumenV mvol, mvolmode, mvolx;
    VolumenV cd_volume;
    s32 cd_reverb, cd_mix;
    VolumenV ext_volume;
    s32 ext_reverb, ext_mix;
} AtributosSpuV;

extern s32 SpuSetCommonAttr(AtributosSpuV *a);

/* Pone f en el canal 1 de interrupciones (el del video). */
s32 func_8005DDE8(s32 f) {
    return func_80016970(1, f);
}

/* Baja el volumen del video de a 8 (sin pasar de 0). Devuelve 2 cuando llega a 0. */
s32 func_8005D164(s16 *vol) {
    *vol -= 8;
    if (*vol < 0) {
        *vol = 0;
    }
    SsSetSerialVol(0, *vol, *vol);
    return *vol == 0 ? 2 : 0;
}

/* Prende o apaga los bits 0x08000000 (al reves, con flags & 1) y 0x02000000 (flags & 2) de la palabra y la
 * manda con func_8005D9C0. */
s32 func_8005DCD4(u32 *p, s32 flags) {
    if (flags & 1) {
        *p &= 0xF7FFFFFF;
    } else {
        *p |= 0x08000000;
    }
    if (flags & 2) {
        *p |= 0x02000000;
    } else {
        *p &= 0xFDFFFFFF;
    }
    return func_8005D9C0(p, *(u16 *)p);
}

/* El sonido del video: volumen general y del CD al maximo, mezcla del CD prendida, y las cuentas en 0. */
s32 func_8005D844(void) {
    AtributosSpuV c;

    c.mask = 0x2C3;
    c.mvol.left = 0x3FFF;
    c.mvol.right = 0x3FFF;
    c.cd_volume.left = 0x3FFF;
    c.cd_volume.right = 0x3FFF;
    D_8007CC9C = 0;
    D_8007CC98 = 0;
    D_8007CCA4 = 0;
    D_8007CCA0 = 0;
    c.cd_mix = 1;
    return SpuSetCommonAttr(&c);
}
