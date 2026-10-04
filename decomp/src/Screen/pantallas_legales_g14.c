#include "juego.h"

/* Las cuatro pantallas legales del arranque. Igual que la de video_g13.c, pero con el marco de pila del
 * original (0xB8): las funciones que llama (CargarArchivoEntero) copian bytes sin inicializar de su pila, y
 * con otro marco la basura cambia. Para que GCC guarde pocos registros, las direcciones de las globales se
 * arman dentro del bucle (DIR) en vez de quedar guardadas en registros. */

typedef struct {
    s16 x, y, w, h;
} RectL;

extern RectL D_8007C9E0;             /* lo que se borra entre pantallas */
extern RectL D_8007C77C;             /* donde va cada pantalla legal en la VRAM */
extern s32 D_80065408[4];            /* cuadros que dura cada una */
extern char *D_8007C740[4];          /* sus nombres */
extern char D_8007C784[];            /* "%s%s" */
extern char D_8007A1D0[];            /* la carpeta */
extern char D_80065418[];            /* el aviso si falta una */
extern s32 D_8007CA58;               /* botones recien apretados */

extern s32 func_80021120(RectL r);   /* borra la pantalla */
extern s32 sprintf(char *d, const char *f, ...);
extern s32 printf(const char *f, ...);
extern void *CargarArchivoEntero(char *nombre, s32 a);
extern void func_8001D778(void);     /* espera una vuelta de la pantalla */
extern void func_800219C8(void);
extern void SubirAVRAM(RectL *r, void *datos);
extern void Liberar(void *p);
extern void HerramientaConvertirPIC(char *nombre);

#define CUATRO() ({ u32 _k; __asm__ volatile("li %0, 4" : "=r"(_k)); _k; })
#define DIR(x) ({ void *_d; __asm__ volatile("la %0, " #x : "=r"(_d)); _d; })

s32 PantallasLegales(void) {
    RectL r = D_8007C77C;
    char nombre[0x80];
    s32 espera[4];
    void *p;
    s32 n;
    u32 i;

    espera[0] = D_80065408[0];
    espera[1] = D_80065408[1];
    espera[2] = D_80065408[2];
    espera[3] = D_80065408[3];
    for (i = 0; i != CUATRO(); i++) {
        sprintf(nombre, DIR(D_8007C784), DIR(D_8007A1D0), ((char **) DIR(D_8007C740))[i]);
        p = CargarArchivoEntero(nombre, 0);
        if (p == NULL) {
            HerramientaConvertirPIC(D_8007C740[0]);
            HerramientaConvertirPIC(D_8007C740[1]);
            HerramientaConvertirPIC(D_8007C740[2]);
            HerramientaConvertirPIC(D_8007C740[3]);
            printf(D_80065418);
            for (;;) {
            }
        }
        func_8001D778();
        func_800219C8();
        SubirAVRAM(&r, p);
        Liberar(p);
        n = espera[i];
        if (i != 0) {
            while (*(volatile s32 *) DIR(D_8007CA58) == 0 && n != 0) {
                func_8001D778();
                n--;
            }
        } else {
            while (n != 0) {
                func_8001D778();
                n--;
            }
        }
    }
    return func_80021120(D_8007C9E0);
}
