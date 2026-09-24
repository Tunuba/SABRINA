#include "juego.h"

/* Texto de un cuadro de tres renglones. */

extern s8 ascii_a_letra[];           /* de ASCII al numero de letra de la fuente */
extern s8 *D_80079D48[];             /* renglones de pantalla; el cuadro usa del 0x3B al 0x3D */
extern char D_80076BA0[], D_80076BC0[];
extern char D_80076BE4[], D_80076C04[];
extern char D_80076C28[], D_80076C48[];

extern void func_800191D8(char *a, char *b);

/* Copia el texto a los tres renglones del cuadro, pasando cada caracter a su letra de la fuente. Un '#'
 * o el fin del texto cierra el renglon con 0x7F (el '#' se salta, el fin no: los renglones que quedan
 * salen vacios). Despues manda a dibujar los tres renglones. */
void func_80053F74(s8 *texto) {
    s8 *dst = D_80079D48[0x3B];
    s32 renglon = 0;
    s32 i = 0x3B;
    s8 c;

    while (renglon < 3) {
        c = *texto;
        if (c != 0 && c != '#') {
            *dst++ = ascii_a_letra[c];
            texto++;
        } else {
            *dst = 0x7F;
            if (*texto != 0) {
                texto++;
            }
            i++;
            renglon++;
            dst = D_80079D48[i];
        }
    }
    func_800191D8(D_80076BC0, D_80076BA0);
    func_800191D8(D_80076C04, D_80076BE4);
    func_800191D8(D_80076C48, D_80076C28);
}
