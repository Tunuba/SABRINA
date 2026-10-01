#include "objeto.h"

/* Volver a empezar despues de perder una vida (o al entrar al nivel). */

extern s8 D_800C8566;                /* la ultima bandera de func_80030F18 */
extern s16 partida;                  /* vidas */
extern Objeto *D_8007CAFC;           /* la camara */
extern s32 D_8007CB00, D_8007CB04, D_8007CB08;  /* donde reaparece */
extern s16 D_8007CB0C;               /* hacia donde mira al reaparecer */
extern u8 D_8007CB1C;                /* el hechizo elegido */
extern s8 vida_barra;
extern s16 D_8007CB38, D_8007CB70;
extern s32 D_8007CB78, D_8007CB80;
extern s8 D_8007CB88;
extern Objeto *D_8007CB8C;           /* el companero */
extern s32 D_8007CB90, D_8007CB94, D_8007CB98, D_8007CB9C, D_8007CBA0;
extern u16 D_8007CBC0, D_8007CBD4;
extern s16 D_8007CBF0;
extern u8 D_8007CC14;
extern s32 D_8007CC60;

extern void func_80031494(void);
extern void func_8003DC08(void);
extern void func_80030F18(s32 n);
extern void ActualizarBarraVida(void);
extern void func_8004CAB8(void);
extern void func_800350A4(s32 *p);
extern void func_80037278(Objeto *camara, Objeto *a);
extern void func_8003019C(void);
extern void func_80030E64(void);

/* Pone a Sabrina (o) en el punto de reaparicion (si le quedan vidas, con 20 de vida), con todo en cero,
 * escala 10 creciendo (estado 4), el companero en su primera animacion, la camara acomodada detras y el
 * estado normal. Devuelve (v0) el D_8007CBD4 que restaura. */
s32 func_80031698(Objeto *o) {
    u8 *e = (u8 *)&o->extra;
    EstadoAnim *ca;

    D_8007CB88 = 0;
    if (D_8007CAFC != NULL) {
        D_8007CAFC->estado = 0;
    }
    D_8007CBF0 = 1;
    D_8007CB80 = 0;
    D_8007CC60 = 0;
    /* func_80031494 recorre los objetos desde lo que trae en v1: el original le deja ahi D_8007CAFC */
    __asm__ volatile(".set noreorder\n\tmove $3, %0\n\tjal func_80031494\n\tnop\n\t.set reorder"
                     :
                     : "r"(D_8007CAFC)
                     : "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14",
                       "$15", "$24", "$25", "$31", "hi", "lo", "memory");
    func_8003DC08();
    if (partida > 0) {
        o->x = D_8007CB00;
        o->y = D_8007CB04;
        o->z = D_8007CB08;
        o->vida = 20;
    }
    o->rot[0] = 0;
    o->rot[1] = D_8007CB0C;
    o->rot[2] = 0;
    *(s32 *)e = 0;
    o->empuje_x = 0;
    o->vel_y = 0;
    o->empuje_z = 0;
    *(s16 *)(e + 0x10) = 0;
    *(s16 *)(e + 0x0E) = 0;
    e[0x1F] = 0;
    e[0x20] = 0;
    *(s16 *)(e + 0x12) = 0;
    e[0x24] = D_8007CB1C;
    e[0x22] = 8;
    *(s16 *)(e + 0x14) = 30;
    o->escala[0] = 10;
    o->escala[1] = 10;
    o->escala[2] = 10;
    o->estado = 4;
    e[0x1D] = 0;
    e[0x1E] = 0;
    ca = D_8007CB8C->anim;
    ca->_4E = 0x1000;
    ca->animacion = *D_8007CB8C->animaciones;
    ca->_50 = 0;
    D_8007CB70 = 0;
    if (D_8007CC14 == 1) {
        D_8007CC14 = 0;
    }
    switch (D_800C8566) {
    case 0:
        func_80030F18(2);
        break;
    case 1:
        func_80030F18(4);
        break;
    case 2:
        func_80030F18(8);
        break;
    case 3:
        func_80030F18(10);
        break;
    case 4:
        func_80030F18(6);
        break;
    }
    D_8007CB90 = 0;
    D_8007CB94 = 0;
    D_8007CB98 = 0;
    D_8007CB9C = 0;
    D_8007CBA0 = 0;
    D_8007CB78 = 0;
    vida_barra = p_sabrina->vida;
    D_8007CB38 = 0;
    ActualizarBarraVida();
    func_8004CAB8();
    func_800350A4(&o->x);
    func_80037278(D_8007CAFC, o);
    func_8003019C();
    func_80030E64();
    D_8007CBD4 = D_8007CBC0;
    return D_8007CBC0;
}
