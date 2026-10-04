#include "juego.h"

/* Los sonidos del nivel: el banco de cabeceras (.VHD) y el de muestras (.VBD) de SOUND\, que se suben al SPU. */

extern s8 nivel_actual;
extern s16 D_80074C74[];             /* por nivel, el tamano del .VHD en KB */
extern s16 D_80074C94[];             /* por nivel, el tamano del .VBD en KB */
extern char D_80074CB4[];            /* "SOUND\%s" */
extern char D_80074CC0[];            /* el aviso de error del banco */
extern char D_8007C8B8[];            /* el nombre del archivo fuente */
extern u8 *D_8007CBDC;               /* el .VHD (queda) */
extern u8 *D_8007CBE0;               /* el .VBD (se libera al subirlo) */
extern s16 D_8007CBE4;               /* el banco abierto */

extern void ArchivoIniciar(void *archivo);
extern void ArchivoAbrir(void *archivo, char *ruta, s32 modo);
extern void ArchivoLeer(void *archivo, void *destino, s32 tam);
extern void ArchivoCerrar(void *archivo, s32 liberar);
extern s32 sprintf(char *destino, const char *formato, ...);
extern s32 printf(const char *formato, ...);
extern char *func_80014FF0(char *s, s32 c);                /* strrchr */
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern void Liberar(void *p);
extern void Afirmar(s32 cond, char *archivo, s32 linea);
extern void SpuSetTransferMode(s32 modo);
extern s32 func_80044C40(u8 *vhd, s32 id);                 /* SsVabOpenHead */
extern s32 SsVabTransBody(u8 *vbd, s32 id);
extern s32 SsVabTransCompleted(s32 modo);

void CargarSonidoNivel(char *nombre) {
    char ruta[0x80];
    u8 vhd[0xA0];
    u8 vbd[0xA0];
    char *punto;
    s32 tam;
    s16 id;

    ArchivoIniciar(vhd);
    ArchivoIniciar(vbd);
    sprintf(ruta, D_80074CB4, nombre);
    punto = func_80014FF0(ruta, '.');
    punto[1] = 'V';
    punto[2] = 'H';
    punto[3] = 'D';
    ArchivoAbrir(vhd, ruta, 1);
    tam = D_80074C74[nivel_actual] << 10;
    D_8007CBDC = Reservar(tam, D_8007C8B8, 0x6C);
    ArchivoLeer(vhd, D_8007CBDC, tam);
    punto[1] = 'V';
    punto[2] = 'B';
    punto[3] = 'D';
    ArchivoAbrir(vbd, ruta, 1);
    tam = D_80074C94[nivel_actual] << 10;
    D_8007CBE0 = Reservar(tam, D_8007C8B8, 0x77);
    ArchivoLeer(vbd, D_8007CBE0, tam);
    SpuSetTransferMode(0);
    D_8007CBE4 = func_80044C40(D_8007CBDC, -1);
    id = D_8007CBE4;
    if (id >= 0 && id == SsVabTransBody(D_8007CBE0, id)) {
        SsVabTransCompleted(1);
        Liberar(D_8007CBE0);
        ArchivoCerrar(vbd, -1);
        ArchivoCerrar(vhd, -1);
        return;
    }
    printf(D_80074CC0);
    Afirmar(0, D_8007C8B8, 0x86);
    ArchivoCerrar(vbd, -1);
    ArchivoCerrar(vhd, -1);
}
