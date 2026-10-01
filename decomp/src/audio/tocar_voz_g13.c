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
    u8 _04[0x0A];
    u16 nota;                        /* 0x0E */
    s16 marca;                       /* 0x10 */
    s16 prog;                        /* 0x12 */
    s16 nprog;                       /* 0x14 */
    s16 tono;                        /* 0x16 */
    u16 vab;                         /* 0x18 */
    u8 _1A[3];
    u8 activa;                       /* 0x1D */
    u8 _1E[0x18];
    s16 vol;                         /* 0x36 */
} VozSnd;
EN(VozSnd, nota, 0x0E);
EN(VozSnd, vab, 0x18);
EN(VozSnd, activa, 0x1D);
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
