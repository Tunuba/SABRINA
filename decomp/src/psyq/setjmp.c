#include "juego.h"

/* setjmp de PsyQ (08-10): guarda en jmp la vuelta, la pila, fp, s0-s7 y gp, y devuelve 0. En la biblioteca es
 * asm. En C ra, sp y los registros conservados van como variables de registro GLOBALES (en su propio archivo): asi GCC
 * no los da por usados ni los salva en un marco, y la funcion queda sin marco, con sp tal como entro. Con
 * variables de registro locales GCC armaba un marco de 40 bytes y el sp guardado quedaba corrido. */

register u32 r_s0 asm("$16");
register u32 r_s1 asm("$17");
register u32 r_s2 asm("$18");
register u32 r_s3 asm("$19");
register u32 r_s4 asm("$20");
register u32 r_s5 asm("$21");
register u32 r_s6 asm("$22");
register u32 r_s7 asm("$23");
register u32 r_gp asm("$28");
register u32 r_sp asm("$29");
register u32 r_ra asm("$31");
register u32 r_fp asm("$30");

s32 func_80016170(u32 *jmp) {
    jmp[0] = r_ra;
    jmp[11] = r_gp;
    jmp[1] = r_sp;
    jmp[2] = r_fp;
    jmp[3] = r_s0;
    jmp[4] = r_s1;
    jmp[5] = r_s2;
    jmp[6] = r_s3;
    jmp[7] = r_s4;
    jmp[8] = r_s5;
    jmp[9] = r_s6;
    jmp[10] = r_s7;
    return 0;
}
