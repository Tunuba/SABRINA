#include "juego.h"

/* Herramienta de desarrollo: arma el .INO de un nivel en la PC (GRAPHICS\<nombre> con la extension cambiada a
 * .INO): la cuadricula, las texturas del grupo del nivel, los modelos, la fuente y la lista de modelos. */

extern char D_8007C784[];               /* "%s%s" */
extern char D_8007A1D0[];               /* "GRAPHICS\" */
extern char D_8007A3F0[];               /* el nombre de la fuente */

extern s32 sprintf(char *d, const char *f, ...);
extern char *func_80014FF0(char *s, s32 c);     /* strchr */
extern s32 func_800294F0(char *nombre, s32 a, s32 b);    /* PCcreat */
extern s32 func_80029518(s32 arch);                      /* PCclose */
extern void HerramientaArmarCuadricula(char *nombre, s32 arch);
extern void func_80024450(s32 grupo, s32 arch);
extern void HerramientaArmarModelos(s32 arch, s32 nivel);
extern void func_80018CB8(char *nombre, s32 arch);
extern void func_8001F524(s32 arch);

void func_800185A8(char *nombre, s32 nivel) {
    char ruta[0x80];
    char *p;
    s32 arch;

    sprintf(ruta, D_8007C784, D_8007A1D0, nombre);
    p = func_80014FF0(ruta, '.');
    p[1] = 'I';
    p[2] = 'N';
    p[3] = 'O';
    arch = func_800294F0(ruta, 0x200, 2);
    HerramientaArmarCuadricula(nombre, arch);
    func_80024450(nivel, arch);
    HerramientaArmarModelos(arch, nivel);
    func_80018CB8(D_8007A3F0, arch);
    func_8001F524(arch);
    func_80029518(arch);
}
