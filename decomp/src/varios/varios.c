#include "objeto.h"

/* Lista de libres de los estados de animacion (EstadoAnim), enlazados por su campo sig. */
extern EstadoAnim *D_8007CB6C;

/* Le da al objeto un estado de animacion de la lista de libres; NULL si no queda ninguno. */
EstadoAnim *func_8002ECFC(Objeto *o) {
    EstadoAnim *a = D_8007CB6C;

    if (a == NULL) {
        return NULL;
    }
    D_8007CB6C = a->sig;
    o->anim = a;
    a->sig = NULL;
    return a;
}

/* Devuelve el estado de animacion del objeto a la lista de libres. */
void func_8002ED30(Objeto *o) {
    EstadoAnim *a = o->anim;

    o->anim = NULL;
    a->sig = D_8007CB6C;
    D_8007CB6C = a;
}
