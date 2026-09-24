#include "juego.h"

/* Lectura de las secciones del .INO del nivel (modelLoader.c): la cuadricula del mundo (seccion 1) y los
 * modelos (seccion 3). Cada seccion leida suma uno a D_8007CAE8. El formato esta en notas\FORMATOS.md. */

/* Una lista de colision de 8 bytes: en el archivo trae en +4 el inicio en la tabla de indices, que al
 * cargar se cambia por el puntero. */
typedef struct {
    s16 n;
    s16 _02;
    s16 *indices;
} ListaColision;

/* Cabecera de 12 bytes de la cuadricula. */
typedef struct {
    s16 celdas;                      /* 0x00, celdas de 12 bytes */
    s16 listas;                      /* 0x02, listas de colision de 8 bytes */
    s16 _04;
    s16 lado;                        /* 0x06, celdas por lado */
    s32 indices;                     /* 0x08, indices de triangulo (s16) */
} CabCuadricula;

extern void ArchivoLeer(void *archivo, void *destino, s32 tam);
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern char D_80068830[];            /* "modelLoader.c" */

extern void *D_8007CA48;             /* celdas (12 bytes cada una) */
extern ListaColision *D_8007CBCC;    /* listas de colision */
extern s32 D_8007CBC4;               /* cuantas listas */
extern s16 D_8007CA4C;
extern s16 D_8007CBC8;               /* celdas por lado */
extern s16 *D_8007CBD0;              /* tabla de indices */
extern u8 D_8007CAE8;                /* secciones del .INO leidas */

/* Seccion 1: la cuadricula del mundo. Reserva y lee celdas, listas e indices y pasa el inicio de cada lista
 * a puntero dentro de la tabla de indices. */
void LeerCuadriculaINO(void *archivo) {
    CabCuadricula cab;
    s32 i;

    ArchivoLeer(archivo, &cab, sizeof(cab));
    D_8007CA48 = Reservar(cab.celdas * 12, D_80068830, 0x1AA);
    D_8007CBCC = Reservar(cab.listas * 8, D_80068830, 0x1AB);
    D_8007CBC4 = cab.listas;
    D_8007CA4C = cab._04;
    D_8007CBC8 = cab.lado;
    D_8007CBD0 = Reservar(cab.indices * 2, D_80068830, 0x1B1);
    ArchivoLeer(archivo, D_8007CA48, cab.celdas * 12);
    ArchivoLeer(archivo, D_8007CBCC, cab.listas * 8);
    ArchivoLeer(archivo, D_8007CBD0, cab.indices * 2);
    for (i = 0; i < D_8007CBC4; i++) {
        ListaColision *l = &D_8007CBCC[i];
        l->indices = (s16 *)((u8 *)D_8007CBD0 + ((s32)l->indices << 1));
    }
    D_8007CAE8++;
}

extern s32 *tabla_modelos_niveles[]; /* por nivel, lista de modelos terminada en 0 */
extern void *modelos_cargados[];     /* desde el indice 1 */

extern void RegistrarTextura(void *textura);
extern void func_80022614(void *textura);
extern void func_80022918(void *textura);
extern void *func_8001E164(s32 a);
extern void LeerNodoModelo(void *archivo, void *modelo, s32 a);
extern void func_8001B494(void);

/* Seccion 3: las texturas (una cuenta u16 y 0x20 bytes cada una), 0xDC bytes que no se usan y un arbol de
 * nodos por cada modelo de la lista del nivel, que van a modelos_cargados[1..]. */
void LeerModelosINO(void *archivo, s32 nivel) {
    s32 *lista = tabla_modelos_niveles[nivel];
    u16 i = 0;
    u16 n;
    u8 descarte[0xDC];
    s32 k;

    ArchivoLeer(archivo, &n, 2);
    while (n-- != 0) {
        u8 *t = Reservar(0x20, D_80068830, 0x139);
        ArchivoLeer(archivo, t, 0x20);
        RegistrarTextura(t);
        if (t[0x1C] & 2) {
            func_80022614(t);
        }
        if (t[0x1C] & 8) {
            func_80022918(t);
        }
    }
    ArchivoLeer(archivo, descarte, 0xDC);
    k = 0;
    do {
        if (lista[k] != 0) {
            modelos_cargados[k + 1] = func_8001E164(0);
            LeerNodoModelo(archivo, modelos_cargados[k + 1], 1);
        }
        k++;
    } while (lista[i++] != 0);
    func_8001B494();
    D_8007CAE8++;
}
