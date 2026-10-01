#include "juego.h"

/* Elegir una voz libre del SPU para un efecto de sonido. */

extern u16 D_800C65E0[];             /* prioridad del sonido de cada voz */
extern u16 D_800C6608[];             /* nota del sonido de cada voz */
extern u8 D_800C6630[];              /* 1 si la voz esta tomada */
extern s16 D_8007CBE4;               /* banco de sonidos */
extern u16 D_8007C8C0;               /* volumen izquierdo de los efectos */
extern u16 D_8007C8C2;               /* volumen derecho */

extern s32 SpuGetKeyStatus(s32 voces);
extern s16 func_800425C8(s32 voz, s32 vab, s32 prog, s32 tono, s32 nota, s32 fina, s32 izq, s32 der);

/* Busca, de la voz 19 a la 1, una que este callada y libre. Si no hay, toma la de menor prioridad
 * (empezando con 10) siempre que sea menor que la del sonido nuevo; si tampoco, devuelve -1. Toca el
 * tono del programa en esa voz y devuelve la voz. */
s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad) {
    s16 voz;
    s16 menor = 10;
    s16 voz_menor = 10;
    s16 estado;

    for (voz = 19; voz != 0; voz--) {
        estado = (s16)SpuGetKeyStatus(1 << voz);
        if ((s32)D_800C65E0[voz] < menor) {
            menor = D_800C65E0[voz];
            voz_menor = voz;
        }
        if ((estado == 0 || estado == 3) && D_800C6630[voz] == 0) {
            break;
        }
    }
    if (voz == 0) {
        if (menor < prioridad) {
            voz = voz_menor;
        } else {
            return -1;
        }
    }
    D_800C6630[voz] = 1;
    D_800C65E0[voz] = prioridad;
    D_800C6608[voz] = nota;
    func_800425C8(voz, D_8007CBE4, prog, tono, nota, 0, (s16)D_8007C8C0, (s16)D_8007C8C2);
    return voz;
}
