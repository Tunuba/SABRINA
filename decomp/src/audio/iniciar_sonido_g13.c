#include "juego.h"

/* Iniciar el sonido: el reloj de la musica, la reverberacion, el volumen general y las voces. */

typedef struct {
    s16 left, right;
} VolumenSpu;

typedef struct {
    u32 mask;
    VolumenSpu mvol, mvolmode, mvolx;
    VolumenSpu cd_volume;
    s32 cd_reverb, cd_mix;
    VolumenSpu ext_volume;
    s32 ext_reverb, ext_mix;
} AtributosSpu;

typedef struct {
    u32 voice;
    u32 mask;
    VolumenSpu volume, volmode, volumex;
    u16 pitch, note, sample_note;
    s16 envx;
    u32 addr, loop_addr;
    s32 a_mode, s_mode, r_mode;
    u16 ar, dr, sr, rr, sl;
    u16 adsr1, adsr2;
} AtributosVoz;

extern s16 D_800C65E0[];
extern s16 D_8007CBE6;
extern void func_80041C48(void);
extern void SsSetTickMode(s32 modo);
extern void SsUtReverbOn(void);
extern void SpuSetCommonAttr(AtributosSpu *a);
extern void SpuSetVoiceAttr(AtributosVoz *a);
extern s32 SsSetMVol(s32 izq, s32 der);

s32 func_8003DC48(void) {
    AtributosSpu c;
    AtributosVoz v;
    u8 i;
    s32 r;

    func_80041C48();
    SsSetTickMode(5);
    SsUtReverbOn();
    for (i = 20; i != 0; i--) {
        D_800C65E0[i] = 0;
    }
    c.mask = 0x2C3;
    c.mvol.left = 0x3FFF;
    c.mvol.right = 0x3FFF;
    c.cd_mix = 1;
    c.cd_volume.left = 0x2FFF;
    c.cd_volume.right = 0x2FFF;
    SpuSetCommonAttr(&c);
    v.mask = 0xFF93;
    v.voice = 0xFFFFFF;
    v.volume.left = 0x3FFF;
    v.volume.right = 0x3FFF;
    v.pitch = 0x800;
    v.a_mode = 1;
    v.s_mode = 1;
    v.r_mode = 3;
    v.ar = 0;
    v.dr = 0;
    v.sr = 0;
    v.rr = 0;
    v.sl = 0xF;
    SpuSetVoiceAttr(&v);
    r = SsSetMVol(0x7F, 0x7F);
    D_8007CBE6 = 0;
    return r;
}
