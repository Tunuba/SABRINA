#include "objeto.h"

/* Estados de Sabrina. Cambiar de estado es poner su funcion de cada paso (Objeto.actualizar), elegir la
 * animacion de su tabla (Objeto.animaciones) con velocidad normal (0x1000), y lo mismo para el objeto
 * que la acompana en D_8007CB8C (se mueve y se anima a la par de ella, con su propia tabla). */

extern Objeto *D_8007CB8C;           /* el objeto que va con Sabrina */
extern s32 D_8007CB80;
extern s16 D_8007CB70;

void func_80030208();
void func_80055CA4();
void func_80025064();

/* Estado que solo marca el campo 0x1A del registro de WRLDDATA de Sabrina con 2. */
void func_8003018C(Objeto *o) {
    ((s16 *)o->datos)[0x1A / 2] = 2;
}

/* Pasa a Sabrina al estado func_8003018C con la animacion 21 de su tabla. */
void func_8003019C(void) {
    Objeto *s = p_sabrina;
    Objeto *c = D_8007CB8C;
    EstadoAnim *as = s->anim;
    EstadoAnim *ac = c->anim;
    u16 *tc = c->animaciones;

    s->extra._1D = 0;
    as->animacion = s->animaciones[21];
    as->velocidad = 0x1000;
    ac->animacion = tc[21];
    ac->velocidad = 0x1000;
    D_8007CB70 = 0;
    p_sabrina->actualizar = (FuncObjeto)func_8003018C;
    D_8007CB80 = 1;
    D_8007CB8C->actualizar = (FuncObjeto)func_80025064;
}

/* Pasa a Sabrina al estado func_80030208 con la primera animacion de su tabla. */
void func_80030E64(void) {
    Objeto *c = D_8007CB8C;
    Objeto *s = p_sabrina;
    EstadoAnim *ac = c->anim;
    u16 *tc = c->animaciones;
    EstadoAnim *as = s->anim;

    as->animacion = s->animaciones[0];
    as->velocidad = 0x1000;
    ac->animacion = tc[0];
    ac->velocidad = 0x1000;
    p_sabrina->actualizar = (FuncObjeto)func_80030208;
    D_8007CB80 = 0;
    D_8007CB8C->actualizar = (FuncObjeto)func_80055CA4;
}
