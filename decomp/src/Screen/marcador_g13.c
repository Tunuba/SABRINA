#include "objeto.h"

/* Lo que muestra el marcador: que sprite va en cada lugar (punteros a la tabla de sprites de 32 bytes),
 * donde van los numeros y los digitos de los contadores. */

extern u8 *D_8007CB24;               /* la tabla de sprites del marcador, 32 bytes cada uno */
extern u8 *D_8006CE10, *D_8006CE14, *D_8006CE18, *D_8006CE1C, *D_8006CE20, *D_8006CE24, *D_8006CE28;
extern u16 D_8006CE36, D_8006CE38[2], D_8006CE3C;  /* x del cartel que entra y de sus tres digitos */
extern u16 D_8006CE46, D_8006CE48[2], D_8006CE4C;  /* y del mismo cartel y de sus digitos */
extern u8 D_8006CED0[];              /* brillo de cada pieza (0xFF tenida, 0x46 no) */
extern u8 D_8006CE70[], D_8006CE80[];  /* por nivel: sus sprites */
extern u8 D_8006CEF1, D_8006CEF2, D_8006CEF3, D_8006CEF4;
extern u8 D_8006CEF9, D_8006CEFA, D_8006CEFB, D_8006CEFC, D_8006CEFE, D_8006CEFF;  /* digitos (0x11 = '0') */
extern u8 hechizos[];
extern u8 D_8007CB1C;                /* el hechizo elegido */
extern u8 D_8007CB28;                /* recogibles tomados */
extern u16 D_8007CB2A, D_8007CB2C;   /* lo que se mostro la ultima vez */
extern s16 D_8007CB2E;               /* cuadros que el cartel queda quieto */
extern s16 partida;                  /* vidas (el primer campo de la partida) */
extern s16 huevos;
extern s8 nivel_actual;
extern u8 objetos_anacronicos[4];
extern u8 D_8007C890[3];
extern u8 func_80022EF4(s32 a);

/* Pone al dia el marcador. Si cambiaron las vidas o los recogibles arma el cartel que lo muestra (fuera
 * de la pantalla a la derecha) y lo deja quieto 50 cuadros; despues lo va sacando de a 4 pixeles. */
void func_8002303C(void) {
    u8 *extra = (u8 *)p_sabrina + 0x74;
    u8 *base;
    u8 h, n, i;
    s32 p, c;

    if (hechizos[D_8007CB1C] == 0) {
        extra[0x24] = func_80022EF4(1);
    }
    h = hechizos[D_8007CB1C];
    if (h != 0) {
        D_8006CE10 = D_8007CB24 + D_8007CB1C * 32;
        D_8006CE14 = D_8007CB24 + (h + 9) * 32;
    } else {
        D_8006CE10 = D_8007CB24 + 0x100;
        D_8006CE14 = D_8007CB24 + 0x120;
    }
    base = D_8007CB24;
    D_8006CE18 = base + 0x1E0;
    n = D_8007CB28;
    if (n != D_8007CB2A || partida != D_8007CB2C) {
        if (partida != D_8007CB2C) {
            p = partida;
            D_8006CE36 = 0x400;
            D_8006CE38[0] = 0x19E;
            D_8006CE38[1] = 0x1AE;
            D_8006CE3C = 0x18C;
            D_8006CE46 = 0xF0;
            D_8006CE48[0] = 0xA5;
            D_8006CE48[1] = 0xA5;
            D_8006CE4C = 0x93;
            D_8006CE20 = base + (p / 10 + 0x11) * 32;
            D_8006CE24 = base + (p - (p / 10) * 10 + 0x11) * 32;
            D_8006CE28 = base + 0x640;
            D_8007CB2C = p;
            D_8007CB2E = 0x32;
        } else if (nivel_actual != 13) {
            D_8006CE36 = 0x196;
            D_8006CE38[0] = 0x1A6;
            D_8006CE38[1] = 0x1B6;
            D_8006CE3C = 0x18C;
            D_8006CE46 = 0xA5;
            D_8006CE48[0] = 0xA5;
            D_8006CE48[1] = 0xA5;
            D_8006CE4C = 0x93;
            c = n / 100;
            D_8006CE1C = base + (c + 0x11) * 32;
            D_8006CE20 = base + ((n - c * 100) / 10 + 0x11) * 32;
            D_8006CE24 = base + (n - (n / 10) * 10 + 0x11) * 32;
            D_8006CE28 = base + 0x360;
            D_8007CB2A = n;
            D_8007CB2E = 0x32;
        } else {
            D_8007CB2A = n;
        }
    } else {
        if (D_8007CB2E-- < 0 && D_8006CE38[0] < 0x28A) {
            D_8006CE36 += 4;
            D_8006CE38[0] += 4;
            D_8006CE38[1] += 4;
            D_8006CE3C += 4;
            D_8006CE46 += 4;
            D_8006CE48[0] += 4;
            D_8006CE48[1] += 4;
            D_8006CE4C += 4;
        }
    }
    for (i = 0; i != 4; i++) {
        D_8006CED0[5 + i] = objetos_anacronicos[i] ? 0xFF : 0x46;
    }
    for (i = 0; i != 3; i++) {
        D_8006CED0[2 + i] = D_8007C890[i] ? 0xFF : 0x46;
    }
    D_8006CEF1 = D_8006CE70[nivel_actual];
    D_8006CEF2 = D_8006CE80[nivel_actual];
    D_8006CEF3 = D_8006CEF2 + 1;
    D_8006CEF4 = D_8006CEF2 + 2;
    c = n / 100;
    D_8006CEF9 = (n - c * 100) / 10 + 0x11;
    D_8006CEFA = n - (n / 10) * 10 + 0x11;
    D_8006CEFB = c + 0x11;
    D_8006CEFC = huevos + 0x11;
    p = partida;
    D_8006CEFE = p / 10 + 0x11;
    D_8006CEFF = p - (p / 10) * 10 + 0x11;
}
