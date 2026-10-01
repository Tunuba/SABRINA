#include "objeto.h"

/* El jefe de los mundos (niveles 3, 6, 9 y 12): mira a Sabrina, dispara segun su vida, recibe golpes y,
 * al perder, suena su musica, crece y se va. */

extern u16 D_8007C872;               /* distinto de 0: se termina la pelea */
extern u16 D_8007C8C4, D_8007C8C6;   /* volumenes */
extern s8 nivel_actual;
extern Objeto *D_8007CAFC;           /* la camara */
extern u16 D_8007CB58, D_8007CB5A;
extern u16 D_8007CBD4;
extern s8 D_8007CCA8;                /* la vida de Sabrina al disparar */
extern s8 D_800C8582, D_800C8583, D_800C8584, D_800C8585;  /* el jefe de cada mundo vencido */

extern s32 func_8003019C(void);
extern void func_80030E64(void);
extern void func_8003DDA0(s32 pista, s32 a);
extern void func_8003DD44(s32 volumen);
extern s32 func_8003DDFC(void);
extern s32 func_8003E060(void);
extern void func_80035098(void);
extern s32 func_8002EFD0(Objeto *o);
extern s32 func_8002218C(Objeto *o, s32 x, s32 z);
extern s32 func_80021D44(s16 *ang, s32 meta, s32 paso);
extern void func_8002205C(s32 *hacia, s32 ang_x, s32 ang_y);
extern void func_80034FD0(s32 *v, s32 *p);
extern void func_8005E9FC(Objeto *o, s32 a, s32 b, s32 c);
extern void func_80048228(Objeto *o, s32 *p);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern Objeto *func_800252A0(s32 clase, Objeto *padre, s32 x, s32 y, s32 z, s32 vx, s32 vy, s32 vz, s32 rx,
                             s32 ry, s32 rz, s32 a, s32 b);
extern void func_800249CC(Objeto *o, s32 n);
extern void func_8005B394(Objeto *o, s32 *desde, s32 *hasta, s32 rapidez);
extern void func_8005B46C(Objeto *o, s32 a, s32 b, s32 c, s32 d);
extern void func_8005B52C(void), func_8005B780(void), func_8005B794(void);
extern void func_80024DEC(void), func_80024DF4(void), func_80024F6C(void), func_80024F8C(void);
extern void thunk_FUN_8001e588(void), thunk_FUN_8004866c(void);

#define ANIMAR(a, n) ((a)->animacion = (n), (a)->_50 = 0, (a)->_4E = 0x800)
#define E8(e, d) (*(s8 *)((e) + (d)))
#define E16(e, d) (*(s16 *)((e) + (d)))
#define E32(e, d) (*(s32 *)((e) + (d)))
#define O32(o, d) (*(s32 *)((u8 *)(o) + (d)))

/* Gira hacia Sabrina; el resultado queda en el lugar de la pila del juego (m + 0x54). */
static void mirar(Objeto *o, u8 *m) {
    *(s32 *)(m + 0x54) = func_8002218C(o, p_sabrina->x, p_sabrina->z);
    *(s32 *)(m + 0x54) = func_80021D44(&o->rot[1], (s16)*(s32 *)(m + 0x54), 0x96);
}

/* El disparo: sus funciones de cada paso (la primera cambia). */
static void funciones(Objeto *d, void *primera, void *tercera, void *sexta) {
    void **f = (void **)d;

    f[0] = primera;
    f[1] = func_80024DF4;
    f[2] = tercera;
    f[3] = func_80024DEC;
    f[4] = func_80024F6C;
    f[5] = sexta;
    f[6] = thunk_FUN_8004866c;
}

/* m es el sp del marco que arma func_8005ED8C como el juego (0x70 bytes); s0 es lo que traia s0 (el juego
 * lo usa como disparo en un nivel que no es de jefe). */
__attribute__((noinline, used)) static s32 jefe(Objeto *o, u8 *m, Objeto *s0) {
    EstadoAnim *a = o->anim;
    u16 *t = o->animaciones;
    u8 *e = (u8 *)&o->extra;
    s32 *v = (s32 *)(m + 0x58);
    s32 *p = (s32 *)(m + 0x64);
    Objeto *d;
    s32 r, k;

    if (p_sabrina->estado == 2) {
        switch (o->estado) {
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 13: case 15: case 16: case 17: case 19: case 20:
            if (D_8007C872 != 0) {
                func_8003019C();
                o->estado = 0x12;
            }
            break;
        }
    }
    r = 0;
    switch (o->estado) {
    case 0x16:
        D_8007C872 = 0;
        return 0x16;
    case 0x15:
        func_80030E64();
        p_sabrina->estado = 2;
        o->estado = 0x16;
        return func_8003DDFC();
    case 0xB:
        mirar(o, m);
        if (func_8002EFD0(o)) {
            func_80030E64();
            o->estado = 0x15;
            ANIMAR(a, t[1]);
            r = 0x800;
        }
        break;
    case 0xC:
        mirar(o, m);
        if (func_8002EFD0(o)) {
            switch (nivel_actual) {
            case 12:
                TocarSonido(0x3C, 0, 0x2A, 0x7F);
                break;
            case 9:
            case 6:
                TocarSonido(0x3A, 0, 0x2A, 0x7F);
                break;
            case 3:
                TocarSonido(0x3B, 0, 0x2A, 0x7F);
                break;
            }
            o->estado = 0xB;
            ANIMAR(a, t[8]);
            r = 0x800;
        }
        break;
    case 0x12:
        switch (nivel_actual) {
        case 12:
            TocarSonido(0x3E, 0, 0x2A, 0x7F);
            break;
        case 9:
        case 6:
            TocarSonido(0x3C, 0, 0x2A, 0x7F);
            break;
        case 3:
            TocarSonido(0x3D, 0, 0x2A, 0x7F);
            break;
        }
        o->estado = 0xC;
        ANIMAR(a, t[10]);
        r = 0x800;
        break;
    case 0xE:
        func_80048228(o, (s32 *)(m + 0x54));
        if (*(u8 *)&o->_20 & 0x80) {
            D_8007CBD4 |= 0x40;
            r = 1;
            switch (nivel_actual) {
            case 12:
                D_800C8585 = 1;
                break;
            case 9:
                D_800C8584 = 1;
                break;
            case 6:
                D_800C8583 = 1;
                break;
            case 3:
                D_800C8582 = 1;
                break;
            default:
                r = nivel_actual;
                break;
            }
        }
        break;
    case 0xA:
        if (func_8002EFD0(o)) {
            switch (nivel_actual) {
            case 12:
                TocarSonido(0x3D, 0, 0x2A, 0x7F);
                break;
            case 9:
            case 6:
                TocarSonido(0x3B, 0, 0x2A, 0x7F);
                break;
            case 3:
                TocarSonido(0x3C, 0, 0x2A, 0x7F);
                break;
            }
            o->estado = 0xE;
            ANIMAR(a, t[7]);
            r = 0x800;
        }
        break;
    case 9:
        mirar(o, m);
        if (func_8002EFD0(o)) {
            o->estado = 0x14;
            ANIMAR(a, t[5]);
            r = 0x800;
        }
        break;
    case 0x14:
        mirar(o, m);
        if (func_8002EFD0(o)) {
            o->estado = 5;
            ANIMAR(a, t[2]);
            r = 0x800;
        }
        break;
    case 0x13:
        mirar(o, m);
        if (func_8002EFD0(o)) {
            o->estado = 9;
            ANIMAR(a, t[4]);
            r = 0x800;
        }
        break;
    case 1:
        mirar(o, m);
        if (func_8002EFD0(o) || D_8007CCA8 != p_sabrina->vida) {
            o->estado = 0x13;
            ANIMAR(a, t[3]);
            r = 0x800;
        } else {
            r = p_sabrina->vida;
        }
        break;
    case 5:
        mirar(o, m);
        if ((s32)a->_50 >= E8(e, 0x27) && E16(e, 0x3E) != 0) {
            E16(e, 0x3E) = 0;
            D_8007CCA8 = p_sabrina->vida;
            d = s0;
            switch (nivel_actual) {
            case 3:
                d = func_800252A0(0xC, o, 0x8000, -0x3333, 0x4CCC, 0, 0, 0, 0, 0, 0, E8(e, 0x26), 1);
                func_800249CC(d, 0x2F);
                funciones(d, func_8005B794, func_8005B780, thunk_FUN_8001e588);
                switch (o->vida) {
                case 0:
                    k = 0x51EB;
                    break;
                case 1:
                    k = 0x4CCC;
                    break;
                case 2:
                    k = 0x47AE;
                    break;
                case 3:
                    k = 0x428F;
                    break;
                case 4:
                    k = 0x3D70;
                    break;
                case 5:
                    k = 0x3851;
                    break;
                default:
                    k = -1;
                    break;
                }
                if (k != -1) {
                    func_8005B394(d, &d->x, &p_sabrina->x, k);
                }
                O32(d, 0xF8) = 0xB333;
                O32(d, 0xFC) = 0xB333;
                O32(d, 0x100) = 0x7D70;
                d->escala[0] = 0x2000;
                d->escala[1] = 0x2000;
                d->escala[2] = 0x2000;
                break;
            case 6:
                d = func_800252A0(0xC, o, 0, 0, 0xB333, 0, 0, 0, 0, 0, 0, E8(e, 0x26), 1);
                func_800249CC(d, 0x28);
                funciones(d, func_8005B52C, func_80024F6C, func_80024F8C);
                switch (o->vida) {
                case 0:
                    func_8005B46C(d, 0, D_8007CB5A, 0xE6, 0xCCC);
                    break;
                case 1:
                    func_8005B46C(d, 0, D_8007CB5A, 0x96, 0xE14);
                    break;
                case 2:
                    func_8005B46C(d, 0, D_8007CB5A, 0x78, 0xF5C);
                    break;
                case 3:
                    func_8005B46C(d, 0, D_8007CB5A, 0x5A, 0x11EB);
                    break;
                case 4:
                    func_8005B46C(d, 0, D_8007CB5A, 0x46, 0x147A);
                    break;
                case 5:
                    func_8005B46C(d, 0, D_8007CB5A, 0x46, 0x147A);
                    break;
                }
                O32(d, 0xF8) = 0x8000;
                O32(d, 0xFC) = 0x8000;
                O32(d, 0x100) = 0x4000;
                d->escala[0] = 0x1000;
                d->escala[1] = 0x1000;
                d->escala[2] = 0x1000;
                break;
            case 9:
                d = func_800252A0(0xC, o, E32(e, 0xC), E32(e, 0x10), E32(e, 0x14), 0, 0, 0, 0, 0, 0, E8(e, 0x26),
                                  1);
                func_800249CC(d, 0x22);
                funciones(d, func_8005B52C, func_80024F6C, func_80024F8C);
                switch (o->vida) {
                case 0:
                    func_8005B46C(d, 0, D_8007CB5A, 0xE6, 0xCCC);
                    break;
                case 1:
                    func_8005B46C(d, 0, D_8007CB5A, 0xB4, 0xE14);
                    break;
                case 2:
                    func_8005B46C(d, 0, D_8007CB5A, 0x96, 0x10A3);
                    break;
                case 3:
                    func_8005B46C(d, 0, D_8007CB5A, 0x82, 0x11EB);
                    break;
                case 4:
                    func_8005B46C(d, 0, D_8007CB5A, 0x64, 0x147A);
                    break;
                case 5:
                    func_8005B46C(d, 0, D_8007CB5A, 0x64, 0x147A);
                    break;
                }
                O32(d, 0xF8) = 0x18000;
                O32(d, 0xFC) = 0xD999;
                O32(d, 0x100) = 0xB8F5;
                d->escala[0] = 0x1000;
                d->escala[1] = 0x1000;
                d->escala[2] = 0x1000;
                break;
            case 12:
                d = func_800252A0(0xC, o, 0xE666, 0, 0x9999, 0, 0, 0, 0, 0, 0, E8(e, 0x26), 1);
                func_800249CC(d, 0x33);
                funciones(d, func_8005B52C, func_80024F6C, func_80024F8C);
                switch (o->vida) {
                case 0:
                    func_8005B46C(d, 0, D_8007CB58, 0xE6, 0xCCC);
                    break;
                case 1:
                    func_8005B46C(d, 0, D_8007CB58, 0x96, 0xE14);
                    break;
                case 2:
                    func_8005B46C(d, 0, D_8007CB58, 0x78, 0x10A3);
                    break;
                case 3:
                    func_8005B46C(d, 0, D_8007CB58, 0x5A, 0x11EB);
                    break;
                case 4:
                    func_8005B46C(d, 0, D_8007CB58, 0x46, 0x147A);
                    break;
                case 5:
                    func_8005B46C(d, 0, D_8007CB58, 0x46, 0x147A);
                    break;
                }
                O32(d, 0xF8) = 0x18000;
                O32(d, 0xFC) = 0xD999;
                O32(d, 0x100) = 0xB8F5;
                d->escala[0] = 0x4000;
                d->escala[1] = 0x4000;
                d->escala[2] = 0x4000;
                break;
            }
            *(s16 *)((u8 *)d + 0x110) = 2;
            d->dano = 1;
        }
        if (!func_8002EFD0(o)) {
            return 0;
        }
        {
            o->estado = 1;
            ANIMAR(a, t[1]);
            r = 0x800;
            E16(e, 0x3E) = 1;
            r = p_sabrina->vida;
            if (D_8007CCA8 != p_sabrina->vida) {
                o->estado = 0x13;
                ANIMAR(a, t[3]);
                r = t[3];
            }
        }
        break;
    case 0x11:
        mirar(o, m);
        if (func_8002EFD0(o)) {
            o->estado = 5;
            ANIMAR(a, t[2]);
            r = 0x800;
        }
        break;
    case 0x17:
        if (nivel_actual == 6 || nivel_actual == 12 || nivel_actual == 9 || nivel_actual == 3) {
            if (o->escala[0] < 0x1800) {
                o->escala[0] += 0x60;
                o->escala[1] = o->escala[0];
                o->escala[2] = o->escala[0];
                func_8005E9FC(o, 0x14CCC, -0x1999, 0x400);
                func_8005E9FC(o, 0x14CCC, -0x1999, 0x400);
                func_8005E9FC(o, 0x14CCC, -0x2666, 0x400);
            }
        }
        r = func_8003E060();
        *(s32 *)(m + 0x54) = r;
        switch (nivel_actual) {
        case 12:
            if (r != 0x56) {
                r = -1;
            }
            break;
        case 9:
            if (r != 0x55) {
                r = -1;
            }
            break;
        case 6:
            if (r != 0x54) {
                r = -1;
            }
            break;
        case 3:
            if (r != 0x53) {
                r = -1;
            }
            break;
        }
        *(s32 *)(m + 0x54) = r;
        if (r == -1) {
            switch (nivel_actual) {
            case 12:
                func_8003DDA0(0x14, 1);
                break;
            case 9:
                func_8003DDA0(0x10, 1);
                break;
            case 6:
                func_8003DDA0(0xC, 1);
                break;
            case 3:
                func_8003DDA0(8, 1);
                break;
            }
            func_8003DD44((D_8007C8C4 * 15) & 0xFF);
            func_80035098();
            D_8007CAFC->estado = 4;
            func_80030E64();
            if (o->escala[0] < 0x1800) {
                o->escala[0] = 0x1800;
                o->escala[1] = 0x1800;
                o->escala[2] = 0x1800;
            }
            o->estado = 0x13;
            ANIMAR(a, t[3]);
            r = 0x800;
        }
        break;
    case 8:
        E16(e, 0x3E) = 1;
        r = D_8007CAFC->estado;
        if (r == 5 || r == 4) {
            switch (nivel_actual) {
            case 12:
                func_8003DDA0(0x56, 0);
                break;
            case 9:
                func_8003DDA0(0x55, 0);
                break;
            case 6:
                func_8003DDA0(0x54, 0);
                break;
            case 3:
                func_8003DDA0(0x53, 0);
                break;
            }
            func_8003DD44((D_8007C8C6 * 15) & 0xFF);
            o->estado = 0x17;
            ANIMAR(a, t[1]);
            r = 0x800;
            func_8002205C(v, 0, o->rot[1]);
            v[0] = (((v[0] >> 4) * 0x600) >> 8) << 8;
            v[1] = (((v[1] >> 4) * 0x600) >> 8) << 8;
            v[2] = (((v[2] >> 4) * 0x600) >> 8) << 8;
            v[1] = v[1] - 0x48000;
            p[0] = o->x;
            p[1] = o->y;
            p[2] = o->z;
            p[1] = p[1] - 0x4CCD - 0x7FFF;
            v[0] += o->x;
            v[1] += o->y;
            v[2] += o->z;
            func_80034FD0(v, p);
            r = func_8003019C();
        }
        break;
    default:
        return o->estado;
    }
    return r;
}

/* El marco va a mano, igual al del juego (0x70 bytes): en el estado 0xE pasa a func_80048228 la direccion
 * de un lugar de su pila que en ese camino no llena, y en el 5, fuera de los niveles de jefe, usa lo que
 * traia s0. */
__attribute__((naked)) s32 func_8005ED8C(Objeto *o) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x70\n"
            "\tsw $31, 0x4C($sp)\n"
            "\tsw $20, 0x48($sp)\n"
            "\tsw $19, 0x44($sp)\n"
            "\tsw $18, 0x40($sp)\n"
            "\tsw $17, 0x3C($sp)\n"
            "\tsw $16, 0x38($sp)\n"
            "\tmove $5, $sp\n"
            "\tjal jefe\n"
            "\tmove $6, $16\n"
            "\tlw $31, 0x4C($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x70\n"
            ".set reorder");
}
