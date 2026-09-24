#include "gte.h"
#include "nodo.h"
#include "objeto.h"

extern s32 D_8007CAC0;               /* donde va escribiendo la lista de dibujo */
extern Matriz D_8008AB58;            /* la matriz de la camara */

extern void MulMatrix0(Matriz *a, Matriz *b, Matriz *fuera);
extern void CompMatrix(Matriz *a, Matriz *b, Matriz *fuera);
extern s32 func_80020294(s32 lista, void *dibujo, s32 fin, s32 orden);

/* Recorre los hijos del nodo: a cada uno le compone la matriz de mundo con la del padre (si hace falta) y
 * lo manda a dibujar; luego sigue con sus hijos. Si el padre no se movio y el hijo ya tenia su matriz al
 * dia, se la salta. */
void func_800204F0(Nodo *padre, s32 fin, s32 padre_al_dia) {
    Nodo *n = padre->hijo;
    Matriz *matriz_padre = &padre->mundo;
    s32 al_dia = 0;

    while (n != NULL) {
        if (padre_al_dia != 0) {
            al_dia = (n->banderas & 2) != 0;
        }
        if (!al_dia) {
            gte_poner_matriz(matriz_padre);
            gte_poner_traslacion(matriz_padre->t);
            gte_poner_v0_xy(((u16 *) n->local.t)[0] | (((u16 *) n->local.t)[2] << 16));
            gte_cargar_v0_z(&n->local.t[2]);
            gte_mvmva_v0();
            gte_guardar_ir(n->mundo.t);
            MulMatrix0(matriz_padre, &n->local, &n->mundo);
            n->banderas |= 2;
        }
        if (!(n->banderas & 1)) {
            if (n->visible != 0) {
                Matriz camara;

                CompMatrix(&D_8008AB58, &n->mundo, &camara);
                gte_poner_matriz(&camara);
                gte_poner_traslacion(camara.t);
                D_8007CAC0 = func_80020294(D_8007CAC0, n->dibujo, fin - (n->capa << 2), n->triangulos & 0xFFFF);
            }
            if (n->hijo != NULL) {
                func_800204F0(n, fin, al_dia);
            }
        }
        n = n->sig;
    }
}

extern void func_80022104(s16 *giro_x, s16 *giro_y, s32 *direccion);
extern void func_8001E588(Objeto *o);

/* Pone al objeto mirando a donde apunta su modelo: gira el vector (0, 0, 0x1000) con la matriz del modelo
 * (sin la traslacion, que se guarda y se repone) y saca de ahi los dos angulos. */
void func_80024A48(Objeto *o) {
    Nodo *n = o->modelo;
    s32 tx = n->local.t[0];
    s32 ty = n->local.t[1];
    s32 tz = n->local.t[2];
    s32 v[3];

    n->local.t[0] = 0;
    n->local.t[1] = 0;
    n->local.t[2] = 0;
    v[0] = 0;
    v[1] = 0;
    v[2] = 0x1000;
    gte_poner_matriz(&n->local);
    gte_poner_traslacion(n->local.t);
    gte_poner_v0_xy(((u16 *) v)[0] | (((u16 *) v)[2] << 16));
    gte_cargar_v0_z(&v[2]);
    gte_mvmva_v0();
    gte_guardar_ir(v);
    func_80022104(&o->rot[0], &o->rot[1], v);
    o->rot[2] = 0;
    n->local.t[0] = tx;
    n->local.t[1] = ty;
    n->local.t[2] = tz;
    func_8001E588(o);
}

#include "dibujo.h"
#include "modelo.h"

extern u16 D_8007CA9C;               /* triangulos ya puestos en la lista de este cuadro */
extern u16 D_8007CA9E;               /* triangulos mirados, se dibujen o no */

extern s32 func_80014AEC(s32 v);                        /* valor absoluto */
extern s32 func_8001FC5C(TriTex *pieza);                /* 1 si el triangulo se salio de la pantalla */
extern void func_8001FD28(s32 pieza, Triangulo *t);     /* le pone la textura y las esquinas */
extern void func_8001FCF4(s32 pieza, Triangulo *t);     /* le pone el color de cada vertice */
extern void func_800598DC(Triangulo *t, s32 fin, s32 z);         /* el que recorta contra la pantalla */
extern void (*D_80068878[])(Triangulo *t, s32 fin, s32 z);       /* los que parten un triangulo grande */

/* El gemelo de func_800204F0, con el dibujo de los triangulos adentro en vez de llamar a func_80020294.
 * Por cada triangulo del modelo: lo pasa a pantalla de una sola orden, lo descarta si se ve por detras
 * (salvo que la textura se vea de los dos lados), lo situa en la lista por la z mas lejana de sus tres
 * vertices, y si el coprocesador marco que algo se salio de rango lo manda a recortar. Un triangulo que
 * sale muy grande en pantalla se parte antes de dibujarlo: cual de los tres lados es el largo decide a
 * cual de los partidores le toca. */
void func_8001FD50(Nodo *padre, s32 fin, u8 padre_al_dia) {
    Nodo *n = padre->hijo;
    Matriz *matriz_padre = &padre->mundo;
    u8 al_dia = 0;

    while (n != NULL) {
        if (padre_al_dia != 0) {
            al_dia = (n->banderas & 2) != 0;
        }
        if (!al_dia) {
            gte_poner_matriz(matriz_padre);
            gte_poner_traslacion(matriz_padre->t);
            gte_poner_v0_xy(((u16 *) n->local.t)[0] | (((u16 *) n->local.t)[2] << 16));
            gte_cargar_v0_z(&n->local.t[2]);
            gte_mvmva_v0();
            gte_guardar_ir(n->mundo.t);
            MulMatrix0(matriz_padre, &n->local, &n->mundo);
            n->banderas |= 2;
        }
        if (!(n->banderas & 1)) {
            if (n->visible != 0) {
                Matriz camara;
                Triangulo *t;
                TriTex *pieza;
                u32 cuenta;
                u32 sz[3];
                s32 lista, area, marcas, z;
                u16 corte;
                u8 codigo;

                CompMatrix(&D_8008AB58, &n->mundo, &camara);
                gte_poner_matriz(&camara);
                gte_poner_traslacion(camara.t);
                cuenta = n->triangulos & 0xFFFF;
                t = n->dibujo;
                lista = fin - (n->capa << 2);
                for (; cuenta-- != 0; D_8007CA9E++, t++) {
                    gte_poner_v0(t->v[0]);
                    gte_poner_v1(t->v[1]);
                    gte_poner_v2(t->v[2]);
                    gte_rtpt();
                    gte_leer_banderas(marcas);
                    gte_nclip();
                    gte_guardar_mac0(&area);
                    if (area >= 0 && !(t->textura->banderas & 4)) {
                        continue;                        /* se ve por detras */
                    }
                    gte_guardar_sz(sz);
                    z = sz[0];
                    if ((u32) z < sz[1]) {
                        z = sz[1];
                    }
                    if ((u32) z < sz[2]) {
                        z = sz[2];
                    }
                    z >>= 4;
                    if (z < 0xB || z >= 0x400 || D_8007CA9C >= 0x7D0) {
                        continue;
                    }
                    pieza = (TriTex *) D_8007CAC0;
                    codigo = pieza->codigo;
                    gte_guardar_sxy0(&pieza->x0);
                    gte_guardar_sxy1(&pieza->x1);
                    gte_guardar_sxy2(&pieza->x2);
                    if (func_8001FC5C(pieza) != 0) {
                        continue;
                    }
                    func_8001FD28(D_8007CAC0, t);
                    ((TriTex *) D_8007CAC0)->codigo = codigo;
                    if (marcas < 0) {
                        func_800598DC(t, fin, z);
                        continue;
                    }
                    pieza = (TriTex *) D_8007CAC0;
                    corte = 0;
                    if (z < 0x2BC) {
                        if (func_80014AEC(pieza->x0 - pieza->x1) >= 0x119 ||
                            func_80014AEC(pieza->y0 - pieza->y1) >= 0x3D) {
                            corte += 1;
                        }
                        if (func_80014AEC(pieza->x1 - pieza->x2) >= 0x119 ||
                            func_80014AEC(pieza->y1 - pieza->y2) >= 0x3D) {
                            corte += 4;
                        }
                        if (func_80014AEC(pieza->x0 - pieza->x2) >= 0x119 ||
                            func_80014AEC(pieza->y0 - pieza->y2) >= 0x3D) {
                            corte += 7;
                        }
                    }
                    if (corte != 0) {
                        D_80068878[corte](t, fin, z);
                        continue;
                    }
                    func_8001FCF4(D_8007CAC0, t);
                    if (t->textura->banderas & 1) {
                        ((TriTex *) D_8007CAC0)->codigo |= 2;
                    }
                    pieza = (TriTex *) D_8007CAC0;
                    D_8007CAC0 += 0x28;
                    AddPrim((u32 *) (lista + (z << 2)), pieza);
                    D_8007CA9C++;
                }
            }
            if (n->hijo != NULL) {
                func_8001FD50(n, fin, al_dia);
            }
        }
        n = n->sig;
    }
}
