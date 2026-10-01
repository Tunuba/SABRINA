#include "juego.h"

/* libsnd: tocar una nota en una voz concreta (como SsUtKeyOnV de la biblioteca). */

/* Lo que libsnd arma para la nota que se va a tocar (_svm, en 0x800C76E4). */
typedef struct {
    u8 prog0;                        /* 0x00, byte 0 del programa */
    u8 _01;
    u8 nota;                         /* 0x02 */
    u8 fina;                         /* 0x03 */
    u8 vol;                          /* 0x04 */
    u8 pan;                          /* 0x05 */
    u8 _06;
    s8 prog;                         /* 0x07, lo deja _SsVmVSetUp */
    u8 _08[2];
    u8 prog1;                        /* 0x0A, byte 1 del programa */
    u8 prog4;                        /* 0x0B, byte 4 del programa */
    s8 tono;                         /* 0x0C */
    u8 b2, b3, b0, b4, b5, b1;       /* 0x0D, bytes 2, 3, 0, 4, 5 y 1 del tono */
    u8 _13;
    s16 marca;                       /* 0x14, 0x21 */
    u16 vag;                         /* 0x16, campo 0x16 del tono; 0 = no hay sonido */
    s16 voz;                         /* 0x18 */
} Svm;
EN(Svm, prog, 0x07);
EN(Svm, prog1, 0x0A);
EN(Svm, tono, 0x0C);
EN(Svm, b1, 0x12);
EN(Svm, marca, 0x14);
EN(Svm, vag, 0x16);
EN(Svm, voz, 0x18);

/* Estado de cada una de las 24 voces (0x38 bytes). */
typedef struct {
    u16 vag;                         /* 0x00 */
    s16 _02;                         /* 0x02 */
    u8 _04[2];
    u16 envolvente;                  /* 0x06, la escribe SpuGetVoiceEnvelope */
    u8 _08[6];
    u16 nota;                        /* 0x0E */
    s16 marca;                       /* 0x10 */
    s16 prog;                        /* 0x12 */
    s16 nprog;                       /* 0x14 */
    s16 tono;                        /* 0x16 */
    u16 vab;                         /* 0x18 */
    u8 _1A[3];
    u8 activa;                       /* 0x1D */
    s16 llamar1;                     /* 0x1E, distinto de 0: llamar a D_800C7508 */
    u8 _20[0x0A];
    s16 llamar2;                     /* 0x2A, distinto de 0: llamar a D_800C750C */
    u8 _2C[0x0A];
    s16 vol;                         /* 0x36 */
} VozSnd;
EN(VozSnd, nota, 0x0E);
EN(VozSnd, vab, 0x18);
EN(VozSnd, activa, 0x1D);
EN(VozSnd, envolvente, 0x06);
EN(VozSnd, llamar1, 0x1E);
EN(VozSnd, llamar2, 0x2A);
EN(VozSnd, vol, 0x36);

extern u8 D_800C76EE[];              /* el _svm empieza 0x0A bytes antes (0x800C76E4, sin simbolo) */
extern VozSnd D_800C6FC0[];
extern s32 D_800C6E60;               /* 1 mientras se esta tocando una (no se entra dos veces) */
extern u8 *D_800C7848;               /* atributos de los programas, 16 bytes cada uno */
extern u8 *D_800C784C;               /* atributos de los tonos, 32 bytes cada uno, 16 por programa */

extern s32 _SsVmVSetUp(s32 vab, s32 prog);
extern void _SsVmDoAllocate(s32 tono, void *m);  /* los argumentos son los que quedan en a0 y a1 */
extern void vmNoiseOn(s32 voz);
extern s32 func_80043358(s32 nota, s32 fina);  /* el tono de la nota para el SPU */
extern void _SsVmKeyOnNow(s32 a, s32 tono);

/* Toca nota/fina del tono del programa prog del banco vab en la voz pedida, con volumen izquierdo y
 * derecho. Devuelve la voz, o -1 si no se pudo. */
/* Los argumentos van como s32: el original recorta cada uno donde lo usa y no supone que vengan
 * recortados. */
s16 func_800425C8(s32 voz, s32 vab, s32 prog, s32 tono, s32 nota, s32 fina, s32 izq, s32 der) {
    Svm *m = (Svm *)(D_800C76EE - 0x0A);
    u8 *p, *t;
    VozSnd *v;

    if (D_800C6E60 == 1) {
        return -1;
    }
    D_800C6E60 = 1;
    if ((u16)voz >= 24 || _SsVmVSetUp((s16)vab, (s16)prog) != 0) {
        D_800C6E60 = 0;
        return -1;
    }
    m->marca = 0x21;
    m->nota = nota;
    m->fina = fina;
    m->tono = (s8)tono;
    if ((s16)izq == (s16)der) {
        m->pan = 0x40;
        m->vol = izq;
    } else if ((s16)der < (s16)izq) {
        m->pan = ((s16)der << 6) / (s16)izq;
        m->vol = izq;
    } else {
        m->vol = der;
        m->pan = 0x7F - ((s16)izq << 6) / (s16)der;
    }
    p = D_800C7848 + (s16)prog * 16;
    m->prog1 = p[1];
    m->prog4 = p[4];
    m->prog0 = p[0];
    t = D_800C784C + (s16)(m->tono + m->prog * 16) * 32;
    m->b0 = t[0];
    m->vag = *(u16 *)(t + 0x16);
    m->b2 = t[2];
    m->b3 = t[3];
    m->b4 = t[4];
    m->b5 = t[5];
    m->b1 = t[1];
    if (m->vag == 0) {
        D_800C6E60 = 0;
        return -1;
    }
    m->voz = (s16)voz;
    v = &D_800C6FC0[(s16)voz];
    v->marca = 0x21;
    v->vab = vab;
    v->nprog = prog;
    v->prog = m->prog;
    v->vag = m->vag;
    v->nota = nota;
    v->activa = 1;
    v->_02 = 0;
    v->tono = m->tono;
    v->vol = (s8)m->vol;
    _SsVmDoAllocate(m->tono, &m->marca);
    if ((s16)m->vag == 0xFF) {
        vmNoiseOn(voz & 0xFF);
    } else {
        _SsVmKeyOnNow(1, func_80043358((u16)nota, (u16)fina) & 0xFFFF);
    }
    D_800C6E60 = 0;
    return (s16)voz;
}

/* SpuVoiceAttr de la biblioteca: solo los campos que se usan aqui. */
typedef struct {
    s32 voz;                         /* 0x00, mascara de la voz */
    s32 mascara;                     /* 0x04, que campos tomar */
    s16 vol_izq, vol_der;            /* 0x08 */
    u8 _0C[8];
    u16 tono;                        /* 0x14 */
    u8 _16[6];
    u32 direccion;                   /* 0x1C */
    u8 _20[0x1A];
    u16 adsr1, adsr2;                /* 0x3A */
    u8 _3E[2];
} AtribVoz;
EN(AtribVoz, tono, 0x14);
EN(AtribVoz, direccion, 0x1C);
EN(AtribVoz, adsr1, 0x3A);

extern s32 D_800C6F7C;               /* cuadro actual de los ultimos 16 */
extern s32 D_800C6F80[16];           /* por cuadro: voces con la envolvente en cero */
extern s8 D_800C76DC;                /* cuantas voces usa libsnd */
extern s8 D_800C7700;                /* distinto de 0: no apagar las voces calladas */
extern u16 D_800C7500, D_800C7502, D_800C7504, D_800C7506;  /* voces a prender y apagar (0-15, 16-23) */
extern void (*D_800C7508)(s32 voz);
extern void (*D_800C750C)(s32 voz);
extern u8 D_800C7510[24];            /* por voz: que atributos cambiaron */
extern u16 D_800C7528[];             /* por voz, 8 u16: volumenes, tono, direccion y adsr */
extern u8 D_800C76A8;
extern u16 D_800C76AA;
extern u16 D_800C76AC;
extern u16 D_800C76AE;

extern void SpuGetVoiceEnvelope(s32 voz, u16 *env);
extern void SpuSetVoiceAttr(AtribVoz *a);
extern void SpuSetKey(s32 prender, u32 voces);
extern void func_8003F728(s32 a, s32 voces);
extern void func_8003F7A8(s32 a, s32 voces);

/* Lo de cada cuadro de libsnd: anota que voces tienen la envolvente en cero; las que estuvieron asi 15
 * cuadros seguidos se dan por terminadas; llama a los avisos de cada voz, pasa al SPU los atributos que
 * cambiaron y prende y apaga las voces pedidas. */
void func_80042B78(void) {
    AtribVoz a;
    s32 i, quietas;
    u16 *p;

    D_800C6F7C = (D_800C6F7C + 1) & 0xF;
    D_800C6F80[D_800C6F7C] = 0;
    for (i = 0; i < D_800C76DC; i++) {
        SpuGetVoiceEnvelope(i, &D_800C6FC0[i].envolvente);
        if (D_800C6FC0[i].envolvente == 0) {
            D_800C6F80[D_800C6F7C] |= 1 << i;
        }
    }
    if (D_800C7700 == 0) {
        quietas = -1;
        for (i = 0; i < 15; i++) {
            quietas &= D_800C6F80[i];
        }
        for (i = 0; i < D_800C76DC; i++) {
            if (quietas & (1 << i)) {
                if ((s8)D_800C6FC0[i].activa == 2) {
                    s32 bajo = 1 << i, alto = 0;
                    if (i >= 16) {
                        bajo = 0;
                        alto = 1 << (i - 16);
                    }
                    func_8003F728(0, ((alto & 0xFF) << 16) | (s16)bajo);
                }
                D_800C6FC0[i].activa = 0;
            }
        }
    }
    D_800C7502 &= ~D_800C7500;
    D_800C7506 &= ~D_800C7504;
    for (i = 0; i < 24; i++) {
        if (D_800C6FC0[i].llamar1 != 0) {
            D_800C7508(i);
        }
        if (D_800C6FC0[i].llamar2 != 0) {
            D_800C750C(i);
        }
    }
    for (i = 0; i < 24; i++) {
        p = &D_800C7528[i * 8];
        a.mascara = 0;
        a.voz = 1 << i;
        if (D_800C7510[i] & 1) {
            a.mascara = 3;
            a.vol_izq = p[0];
            a.vol_der = p[1];
        }
        if (D_800C7510[i] & 4) {
            a.mascara |= 0x10;
            a.tono = p[2];
        }
        if (D_800C7510[i] & 8) {
            a.mascara |= 0x80;
            a.direccion = p[3] << 3;
        }
        if (D_800C7510[i] & 0x10) {
            a.mascara |= 0x60000;
            a.adsr1 = p[4];
            a.adsr2 = p[5];
        }
        if (a.mascara != 0) {
            SpuSetVoiceAttr(&a);
        }
        D_800C7510[i] = 0;
    }
    SpuSetKey(0, ((u8)D_800C7504 << 16) | D_800C7500);
    SpuSetKey(1, ((u8)D_800C7506 << 16) | D_800C7502);
    func_8003F7A8(8, (D_800C76A8 << 16) | D_800C76AA);
    func_8003F728(8, ((u8)D_800C76AC << 16) | D_800C76AE);
    D_800C7500 = 0;
    D_800C7504 = 0;
    D_800C7502 = 0;
    D_800C7506 = 0;
    D_800C76AE = 0;
    D_800C76AC = 0;
}
