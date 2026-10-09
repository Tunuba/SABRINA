#include "objeto.h"

/* Grupo g08 (0x800350A4-0x80038318): una media de 32 valores, la camara que sigue a un punto (mueve el ojo
 * hacia el y gira para mirarlo), dos matrices de modelos que se ponen donde esta Sabrina y el arranque
 * de dos clases de objeto que sacan sus datos de una tabla de registros de 16 bytes. */

/* Campos crudos de un objeto (los que objeto.h todavia no nombra o nombra con otro tamano). */
#define CAMPO_S32(o, d) (*(s32 *)((u8 *)(o) + (d)))
#define CAMPO_S16(o, d) (*(s16 *)((u8 *)(o) + (d)))
#define CAMPO_S8(o, d) (*(s8 *)((u8 *)(o) + (d)))
#define CAMPO_U8(o, d) (*(u8 *)((u8 *)(o) + (d)))
#define CAMPO_PTR(o, d) (*(void **)((u8 *)(o) + (d)))

/* ---- Media de 32 valores ---- */

extern s32 D_800C6514[32];           /* los ultimos 32 valores, el mas viejo primero */
extern s32 D_8007CBB8;               /* la media que se va llevando */

/* Llena la tabla con el valor de p+4 y suma los 32 a la media (sin ponerla antes en cero) y la divide
 * entre 32. Lee p+4 en cada vuelta: la tabla podria pisarlo. */
void func_800350A4(s32 *p) {
    s32 i;

    for (i = 0; i < 32; i++) {
        D_800C6514[i] = p[1];
        D_8007CBB8 = D_8007CBB8 + p[1];
    }
    D_8007CBB8 = D_8007CBB8 >> 5;
}

/* Corre la tabla un lugar (se pierde el mas viejo), pone el valor nuevo al final y mezcla la media de los
 * 32 con la anterior: media = (media + suma / 32) / 2. Devuelve la media. */
s32 func_800350FC(s32 valor) {
    s32 suma = 0;
    s32 i;

    for (i = 0; i < 31; i++) {
        D_800C6514[i] = D_800C6514[i + 1];
        suma += D_800C6514[i];
    }
    suma += valor;
    D_800C6514[i] = valor;
    D_8007CBB8 = D_8007CBB8 + (suma >> 5);
    D_8007CBB8 = D_8007CBB8 >> 1;
    return D_8007CBB8;
}

/* ---- Modelos que siguen a Sabrina ---- */

extern Objeto *D_8007CAFC;           /* objeto con los nodos de modelo (en su parte extra +0x48 y +0x4C) */
extern s32 D_8007CC60;               /* altura para el segundo modelo */
extern s32 D_8006C444[3];            /* la camara: el ojo */
extern s32 D_8006C450[3];            /* la camara: hacia donde mira */

extern void MatrizDesdeAngulos(void *nodo, s32 *escala, s32 *pos, s32 *giro);
extern void func_80022104(s16 *ang_x, s16 *ang_y, s32 *v);  /* angulos de un vector */
extern void func_8001E7A8(void *nodo, s32 a, s32 b, s32 c);

/* Pone el nodo de extra+0x48 en x, z de Sabrina y a la altura de su +0x50. Lo aplasta en x y z segun
 * cuanto este Sabrina por debajo de esa altura (0x1000 - diferencia / 32), salvo que la escala de
 * Sabrina (x) sea menor que 1000: entonces usa la de Sabrina entera.
 * Ojo: sin esa escala el original no le da valor a la escala en y (su lugar de la pila, sp+0x2C, queda
 * con lo que habia); aqui se lee el mismo lugar: 0x14 bytes debajo de la pila del llamador. */
void func_80036250(void) {
    s32 pos[3];
    s32 escala[3];
    s32 giro[3];
    Objeto *s;
    s32 t;
    void *nodo;

    /* __builtin_dwarf_cfa es la pila al entrar (la del llamador); el original tiene 0x40 bytes de marco y
     * la escala en y en sp+0x2C. Se lee antes de guardar nada. */
    escala[1] = *(volatile s32 *)((u8 *)__builtin_dwarf_cfa() - 0x40 + 0x2C);
    __asm__ volatile("" ::: "memory");
    giro[0] = 0;
    giro[1] = 0;
    giro[2] = 0;
    nodo = CAMPO_PTR(D_8007CAFC, 0x74 + 0x48);
    s = p_sabrina;
    pos[0] = s->x;
    pos[1] = s->y;
    pos[2] = s->z;
    pos[1] = CAMPO_S32(s, 0x50);
    t = 0x1000 - ((pos[1] - s->y) >> 5);
    escala[0] = t;
    escala[2] = t;
    if (s->escala[0] < 1000) {
        escala[0] = s->escala[0];
        escala[1] = s->escala[1];
        escala[2] = s->escala[2];
    }
    MatrizDesdeAngulos(nodo, escala, pos, giro);
}

/* Pone el nodo de extra+0x4C en x, z de Sabrina y a la altura D_8007CC60, sin escala ni giro. Si ese nodo
 * tiene hijo y el hijo otro hijo, a este le pasa 0x1000 menos el angulo en y de hacia donde mira la
 * camara (x y z por 16). */
void func_8003630C(void) {
    s32 pos[3];
    s32 escala[3];
    s32 giro[3];
    s32 v[3];
    s16 ang[2];
    u8 *extra;
    void *nodo;
    void *hijo;

    giro[0] = 0;
    giro[1] = 0;
    extra = (u8 *)D_8007CAFC + 0x74;
    escala[0] = 0x1000;
    escala[1] = 0x1000;
    escala[2] = 0x1000;
    giro[2] = 0;
    pos[0] = p_sabrina->x;
    pos[1] = p_sabrina->y;
    pos[2] = p_sabrina->z;
    pos[1] = D_8007CC60;
    nodo = CAMPO_PTR(extra, 0x4C);
    if (nodo == NULL) {
        return;
    }
    MatrizDesdeAngulos(nodo, escala, pos, giro);
    hijo = CAMPO_PTR(CAMPO_PTR(extra, 0x4C), 4);
    if (hijo == NULL) {
        return;
    }
    hijo = CAMPO_PTR(hijo, 4);
    if (hijo == NULL) {
        return;
    }
    v[0] = D_8006C450[0] << 4;
    v[2] = D_8006C450[2] << 4;
    v[1] = 0;
    func_80022104(&ang[0], &ang[1], v);
    func_8001E7A8(hijo, 0, 0, 0x1000 - ang[1]);
}

/* ---- Camara que sigue un punto ---- */

extern s32 func_8001C004(s32 ax, s32 ay, s32 az, s32 bx, s32 by, s32 bz); /* distancia aproximada */
extern void func_8001C45C(s32 *v);
extern void func_80021E54(s16 *ang, s32 meta, s32 a, s32 b);          /* acerca un angulo a otro */
extern void func_8002205C(s32 *hacia, s32 ang_x, s32 ang_y);
extern s16 D_8007CAE2;
extern s16 D_8007CAE4;

/* Si el punto (x, y, z) esta a 0x200 o mas del objeto, guarda la diferencia en 0x38-0x40, acerca el
 * objeto la diferencia dividida entre 2^desp y pone el ojo de la camara en su posicion / 256. Los
 * argumentos 5 a 7 no se usan (el punto llega entero, desde a1, en la pila del llamador). */
void func_80036410(Objeto *o, s32 x, s32 y, s32 z, s32 a4, s32 a5, s32 a6, s32 desp) {
    s32 dx = x - o->x;
    s32 dy = y - o->y;
    s32 dz = z - o->z;

    if (func_8001C004(0, 0, 0, dx, dy, dz) < 0x200) {
        return;
    }
    o->empuje_x = dx;
    o->vel_y = dy;
    o->empuje_z = dz;
    o->x = o->x + (o->empuje_x >> desp);
    o->y = o->y + (o->vel_y >> desp);
    o->z = o->z + (o->empuje_z >> desp);
    D_8006C444[0] = o->x >> 8;
    D_8006C444[1] = o->y >> 8;
    D_8006C444[2] = o->z >> 8;
}

/* Gira el objeto para mirar al punto (x, y, z): saca los angulos de la diferencia, les acerca los giros
 * x e y del objeto (func_80021E54 con 2 y 3), pone hacia donde mira la camara con esos giros y los copia
 * en D_8007CAE4 (x) y D_8007CAE2 (y). */
void func_80036524(Objeto *o, s32 x, s32 y, s32 z) {
    s32 v[3];
    s16 ang[2];

    v[0] = x - o->x;
    v[1] = y - o->y;
    v[2] = z - o->z;
    func_8001C45C(v);
    func_80022104(&ang[0], &ang[1], v);
    func_80021E54(&o->rot[0], ang[0], 2, 3);
    func_80021E54(&o->rot[1], ang[1], 2, 3);
    func_8002205C(D_8006C450, o->rot[0], o->rot[1]);
    D_8007CAE2 = o->rot[1];
    D_8007CAE4 = o->rot[0];
}

/* Coloca la camara o respecto de a (la diferencia girada con el giro y de a, por 3 / 16, y 0x14CCC mas
 * arriba) y la deja 100 pasos acercandose y mirando a la posicion de a, para que llegue ya asentada. En
 * la parte extra de la camara quedan el punto que sigue (+0x28) y donde esta (+0x34). */
void func_80037278(Objeto *o, Objeto *a) {
    u8 *extra = (u8 *)o + 0x74;
    s32 v[3];
    s32 i;

    if (o == NULL) {
        return;
    }
    func_800350A4(&a->x);
    v[0] = (o->x - a->x) >> 8;
    v[1] = (o->y - a->y) >> 8;
    v[2] = (o->z - a->z) >> 8;
    func_8002205C(v, 0, a->rot[1]);
    v[0] = a->x - (v[0] >> 4) * 0x300;
    v[2] = a->z - (v[2] >> 4) * 0x300;
    v[1] = a->y - 0x14CCC;
    o->x = v[0];
    o->y = v[1];
    o->z = v[2];
    CAMPO_S32(extra, 0x34) = o->x;
    CAMPO_S32(extra, 0x38) = o->y;
    CAMPO_S32(extra, 0x3C) = o->z;
    CAMPO_S32(extra, 0x28) = a->x;
    CAMPO_S32(extra, 0x2C) = a->y;
    CAMPO_S32(extra, 0x30) = a->z;
    for (i = 0; i < 100; i++) {
        func_80036410(o, CAMPO_S32(extra, 0x34), CAMPO_S32(extra, 0x38), CAMPO_S32(extra, 0x3C),
                      CAMPO_S32(extra, 0x28), CAMPO_S32(extra, 0x2C), CAMPO_S32(extra, 0x30), 3);
        func_80036524(o, CAMPO_S32(extra, 0x28), CAMPO_S32(extra, 0x2C), CAMPO_S32(extra, 0x30));
        D_8007CAE2 = o->rot[1];
        D_8007CAE4 = o->rot[0];
        D_8006C444[0] = o->x >> 8;
        D_8006C444[1] = o->y >> 8;
        D_8006C444[2] = o->z >> 8;
    }
}

/* ---- Arranque de objetos con registro de 16 bytes ---- */

/* Registros de 16 bytes desde D_80074BC8: +0 s32, +4 s16, +6 modelo (indice de modelos_cargados), +7 un
 * byte que se copia a extra+1, +8 el dano. Antes, en D_80074BB8, un u16 por registro. */
extern u16 D_80074BB8[];
extern u8 D_80074BC8[];
extern void *modelos_cargados[];
extern void *D_8007C9F0;

extern void *func_8001E06C(void *modelo, void *padre);
extern void func_800206E0(Objeto *o);
extern void func_8001E588(Objeto *o);

#define REG(i) (D_80074BC8 + (i) * 16)

/* Guarda la clase en extra+0x1F y copia de su registro: extra+0x1E (byte del u16), extra+4, extra+8 y el
 * dano. Pone extra+0 = 0x4CCC, extra+0x10 = 0, extra+0x18 = 0, extra+0x1A = 0x800 y extra+0x1C = 50.
 * Se llega por puntero; al volver v0 queda con la direccion de la parte extra, y se devuelve igual. */
u8 *func_8003795C(Objeto *o, s32 clase) {
    u8 *e = (u8 *)o + 0x74;

    CAMPO_S8(e, 0x1F) = clase;
    CAMPO_S32(e, 0x10) = 0;
    CAMPO_U8(e, 0x1E) = D_80074BB8[CAMPO_S8(e, 0x1F)];
    CAMPO_S32(e, 4) = *(s16 *)(REG(CAMPO_S8(e, 0x1F)) + 4);
    CAMPO_S32(e, 8) = *(s32 *)(REG(CAMPO_S8(e, 0x1F)) + 0);
    o->dano = *(s8 *)(REG(CAMPO_S8(e, 0x1F)) + 8);
    CAMPO_S32(e, 0) = 0x4CCC;
    CAMPO_S16(e, 0x18) = 0;
    CAMPO_S16(e, 0x1A) = 0x800;
    CAMPO_S16(e, 0x1C) = 0x32;
    return e;
}

/* Si extra+0 es 0 le pone la clase. Si el modelo de su registro esta cargado, crea el nodo (hijo de
 * D_8007C9F0), escala 0x1000 y lo prepara. Giro x = z = 0, giro y = ((x + z) / 256) & 0xFFF, y extra+1
 * el byte +7 del registro. */
void func_8003821C(Objeto *o, s32 clase) {
    s8 *e = (s8 *)o + 0x74;
    void *m;

    if (e[0] == 0) {
        e[0] = clase;
    }
    m = modelos_cargados[*(s8 *)(REG(e[0]) + 6)];
    if (m != NULL) {
        o->modelo = func_8001E06C(m, D_8007C9F0);
        func_800206E0(o);
        o->escala[0] = 0x1000;
        o->escala[1] = 0x1000;
        o->escala[2] = 0x1000;
        func_8001E588(o);
    }
    o->rot[0] = 0;
    o->rot[2] = 0;
    o->rot[1] = ((o->x + o->z) >> 8) & 0xFFF;
    e[1] = *(s8 *)(REG(e[0]) + 7);
}

/* ---- Aviso de que algo toca a un objeto que se puede recoger ---- */

extern s8 nivel_actual;
extern u8 D_8007C8AC;                /* 1: recoger solo si lo mira o esta cerca */
extern s32 func_800221FC(s32 ax, s32 ay, s32 az, s32 bx, s32 by, s32 bz);  /* distancia */
extern s32 func_8001C33C(s32 *a, s32 *b);  /* producto escalar */
extern void func_80039BA0(Forma *f, s32 banderas);
extern void func_80037738(Objeto *o, Objeto *a);

/* a toca a o. Segun el tipo de a (la tabla de 53 tipos del juego) no pasa nada, o pasa siempre, o solo si
 * o tiene 8 o mas en extra+0x1F (algunos tipos, ademas, solo en los niveles 3, 6, 9 y 12). Con
 * D_8007C8AC en 1 lo toma si a esta a menos de 0x24000 (con 0x8000 de alto de mas) o si o lo mira de
 * frente; entonces guarda a y el producto en su parte extra, cambia su forma y pasa su aviso a
 * func_80037738. */
void func_80037468(Objeto *o, Objeto *a) {
    u8 *extra = (u8 *)o + 0x74;
    s32 fuerza = CAMPO_S8(extra, 0x1F);
    s32 v[3], mira[3];
    s32 cerca, d;
    u16 tipo;

    if (fuerza < 8 && (a->forma.banderas & 0x8000)) {
        return;
    }
    if (a->forma.banderas & 0x100) {
        return;
    }
    tipo = a->tipo;
    if (tipo < 0x35) {
        switch (tipo) {
        case 2: case 14: case 15: case 16: case 17: case 22: case 30: case 32:
        case 47: case 48: case 49: case 50: case 51:
            break;
        case 28:
            if (fuerza < 8) {
                return;
            }
            if (nivel_actual != 6 && nivel_actual != 12 && nivel_actual != 3 && nivel_actual != 9) {
                return;
            }
            break;
        case 40: case 41:
            if (fuerza < 8) {
                return;
            }
            break;
        default:
            return;
        }
    }
    v[0] = a->x - o->x;
    v[1] = a->y - o->y - 0x8000;
    v[2] = a->z - o->z;
    cerca = func_800221FC(0, 0, 0, v[0], v[1], v[2]) < 0x24000;
    if (D_8007C8AC != 1) {
        CAMPO_S32(extra, 0x04) = 0x80;
        CAMPO_S32(extra, 0x08) = 0x140000;
        o->aviso = func_80037738;
        return;
    }
    v[0] = a->x - o->x;
    v[1] = a->y - o->y - 0x8000;
    v[2] = a->z - o->z;
    func_8002205C(mira, o->rot[0], o->rot[1]);
    func_8001C45C(mira);
    func_8001C45C(v);
    v[0] >>= 4;
    v[1] >>= 4;
    v[2] >>= 4;
    mira[0] >>= 4;
    mira[1] >>= 4;
    mira[2] >>= 4;
    d = func_8001C33C(v, mira);
    if (d < 0xBE && !cerca) {
        return;
    }
    CAMPO_PTR(extra, 0x10) = a;
    CAMPO_S32(extra, 0x04) = d;
    func_80039BA0(&o->forma, 0xC000);
    CAMPO_S16(o, 0x114) = 0x26;
    o->forma.banderas = 0x3000;
    o->aviso = func_80037738;
}

extern s32 func_80021CE4(s32 n);     /* al azar, de 0 a n */
extern void *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                            s32 d, s32 e, s32 vida, s32 f, s32 g);
extern void func_80024F6C(Objeto *o, Objeto *a);
typedef struct {
    void (*al_recoger)(Objeto *a);
    u8 _04[0xC];
} Recompensa;
extern Recompensa D_80074BC4[];      /* por fuerza (extra+0x1F): que hacer con lo recogido */

/* El aviso que deja func_80037468: a toca a o, con el mismo filtro de tipos. Si a tiene el bit 0x100 lo
 * rebota (una sola vez por objeto: lo guarda en extra+0x14) girandolo un poco al azar. Si no, crea una
 * particula; si a tiene alguno de los bits 0-1, le aplica la recompensa de la fuerza de o y le avisa; y o
 * vuelve al aviso normal (func_80024F6C). */
void func_80037738(Objeto *o, Objeto *a) {
    u8 *extra = (u8 *)o + 0x74;
    void (*f)(Objeto *);

    if (a->forma.banderas & 0x100) {
        return;
    }
    if (a->tipo < 0x35) {
        switch (a->tipo) {
        case 2: case 14: case 15: case 16: case 17: case 22: case 30: case 32:
        case 47: case 48: case 49: case 50: case 51:
            break;
        case 28:
            if (CAMPO_S8(extra, 0x1F) < 8) {
                return;
            }
            if (nivel_actual != 6 && nivel_actual != 12 && nivel_actual != 3 && nivel_actual != 9) {
                return;
            }
            break;
        case 40: case 41:
            if (CAMPO_S8(extra, 0x1F) < 8) {
                return;
            }
            break;
        default:
            return;
        }
    }
    if (a->forma.banderas & 0x100) {
        if (CAMPO_PTR(extra, 0x14) == a) {
            return;
        }
        CAMPO_S32(extra, 0x10) = 0;
        o->forma.banderas = 0x3800;
        CAMPO_S16(o, 0x114) = 0x27;
        o->rot[1] = o->rot[1] + (s16)(func_80021CE4(200) + 0x79C);
        o->rot[0] = o->rot[0] + (s16)(func_80021CE4(200) - 100);
        CAMPO_S32(extra, 0x0C) = 0;
        CAMPO_PTR(extra, 0x14) = a;
        return;
    }
    CrearParticula(0x13, o, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x19, 0x202, 0);
    if (a->forma.banderas & 3) {
        f = D_80074BC4[CAMPO_S8(extra, 0x1F)].al_recoger;
        if (f != NULL) {
            f(a);
        }
        a->aviso(a, o);
    }
    o->aviso = func_80024F6C;
    CAMPO_S32(extra, 0x0C) = CAMPO_S32(extra, 0x08);
}

/* ---- Paredes a los lados de la camara ---- */

extern s32 D_800C6594[3];            /* comienzo del segmento que se prueba */
extern s32 D_800C65A0[3];            /* y su fin */
extern void func_8003B38C(s32 *c, s32 *desde, s32 *hasta);
extern s32 func_8003AE84(void);      /* si el segmento de D_800C6594 choca */

/* Prueba un segmento desde la camara (D_8007CAFC) hasta fin + lado: si choca devuelve 1. */
static s32 choca_desde_camara(s32 *cam, s32 fx, s32 fz) {
    D_800C6594[0] = cam[0];
    D_800C6594[1] = cam[1];
    D_800C6594[2] = cam[2];
    D_800C65A0[0] = fx;
    D_800C65A0[2] = fz;
    D_800C65A0[1] = cam[1];
    func_8003B38C(D_800C6594, D_800C6594, D_800C65A0);
    return func_8003AE84() != 0;
}

/* ¿Puede la camara moverse de lado (hacia donde apunta dir)? Toma la direccion de la camara a Sabrina en
 * el plano, su perpendicular, y prueba tres segmentos de la camara hacia ese lado (al frente, un poco a
 * cada costado). lado < 0 pide ir solo hacia un lado y lado > 0 solo hacia el otro. Devuelve 1 si choca o
 * si el lado no es el pedido. */
s32 func_80036880(s32 *dir, s32 lado) {
    s32 v[3], n[3], p[3], cam[3];
    s32 d, ax, az;

    v[0] = p_sabrina->x - D_8007CAFC->x;
    v[2] = p_sabrina->z - D_8007CAFC->z;
    v[1] = p_sabrina->y - D_8007CAFC->y;
    cam[0] = D_8007CAFC->x;
    cam[1] = D_8007CAFC->y;
    cam[2] = D_8007CAFC->z;
    v[1] = 0;
    v[0] = -v[0];
    func_8001C45C(v);
    n[0] = v[0];
    n[1] = v[1];
    n[2] = v[2];
    v[0] = (((v[0] >> 4) * 25) >> 8) << 8;
    v[2] = (((v[2] >> 4) * 25) >> 8) << 8;
    p[2] = n[0];
    p[0] = n[2];
    p[1] = 0;
    d = func_8001C33C(dir, p);
    n[0] = (((n[0] >> 4) * 192) >> 8) << 8;
    n[2] = (((n[2] >> 4) * 192) >> 8) << 8;
    if (d >= 0) {
        if (lado < 0) {
            return 1;
        }
        ax = cam[0] + n[2];
        az = cam[2] + n[0];
        if (choca_desde_camara(cam, ax, az) || choca_desde_camara(cam, v[0] + ax, v[2] + az) ||
            choca_desde_camara(cam, ax - v[0], az - v[2])) {
            return 1;
        }
    }
    if (d > 0) {
        return 0;
    }
    if (lado > 0) {
        return 1;
    }
    ax = cam[0] - n[2];
    az = cam[2] - n[0];
    if (choca_desde_camara(cam, ax, az) || choca_desde_camara(cam, v[0] + ax, v[2] + az) ||
        choca_desde_camara(cam, ax - v[0], az - v[2])) {
        return 1;
    }
    return 0;
}

extern s16 D_8007CBD4;               /* tipos de triangulo que no chocan */
extern s32 func_80021CE4(s32 n);     /* al azar, de 0 a n */
extern s32 func_800350FC(s32 valor);

/* Prueba un segmento que sale de Sabrina (corrido por d) a la altura y, hacia fin; devuelve 1 si choca. */
static s32 choca_desde_sabrina(s32 dx, s32 dz, s32 y) {
    D_800C6594[0] = p_sabrina->x;
    D_800C6594[1] = p_sabrina->y;
    D_800C6594[2] = p_sabrina->z;
    D_800C6594[0] += dx;
    D_800C6594[2] += dz;
    D_800C6594[1] = y;
    func_8003B38C(D_800C6594, D_800C6594, D_800C65A0);
    return func_8003AE84() != 0;
}

/* Pone la camara detras de Sabrina segun dir (x en dir[0], z en dir[2]) a la altura y: prueba un segmento
 * desde Sabrina hacia atras y otros tres con un poco de azar; si alguno choca devuelve 0 sin moverla. Si
 * ninguno choca, la deja 3 veces dir detras de Sabrina y a la altura media de Sabrina menos 0x13333.
 * Mientras, ningun tipo de triangulo se ignora (D_8007CBD4 en 0) y al terminar se ignoran casi todos. */
s32 func_80036D58(s32 dx, s32 a1, s32 dz, s32 y) {
    s32 tx = (((dx >> 4) * 0x300) >> 8) << 8;
    s32 tz = (((dz >> 4) * 0x300) >> 8) << 8;
    s32 cx = (((dx >> 4) * 0xCC) >> 8) << 8;
    s32 cz = (((dz >> 4) * 0xCC) >> 8) << 8;
    s32 i;

    D_8007CBD4 = 0;
    D_800C6594[0] = p_sabrina->x;
    D_800C6594[1] = p_sabrina->y;
    D_800C6594[2] = p_sabrina->z;
    D_800C6594[1] = y;
    D_800C65A0[0] = D_800C6594[0] - tx;
    D_800C65A0[2] = D_800C6594[2] - tz;
    D_800C65A0[1] = y;
    D_800C6594[0] += cx;
    D_800C6594[2] += cz;
    func_8003B38C(D_800C6594, D_800C6594, D_800C65A0);
    if (func_8003AE84() != 0) {
        D_8007CBD4 = -17;
        return 0;
    }
    for (i = 0; i < 3; i++) {
        D_800C65A0[0] = D_800C6594[0] - tx + (func_80021CE4(0x4000) - 0x2000);
        D_800C65A0[2] = D_800C6594[2] - tz + (func_80021CE4(0x4000) - 0x2000);
        D_800C65A0[1] = y;
        if (choca_desde_sabrina(cx, cz, y)) {
            D_8007CBD4 = -17;
            return 0;
        }
    }
    D_800C65A0[0] = D_800C6594[0] - tx;
    D_800C65A0[2] = D_800C6594[2] - tz;
    D_800C65A0[1] = func_800350FC(CAMPO_S32(p_sabrina, 0x50)) - 0x13333;
    D_8007CAFC->x = D_800C65A0[0];
    D_8007CAFC->y = D_800C65A0[1];
    D_8007CAFC->z = D_800C65A0[2];
    D_8007CBD4 = -17;
    return 1;
}

/* ---- Proyectil que persigue a un objeto ---- */

typedef struct {
    s32 rapidez;                     /* 0x00 */
    u8 _04[4];
    s32 alcance;                     /* 0x08, distancia maxima */
    s32 recorrido;                   /* 0x0C */
    Objeto *blanco;                  /* 0x10 */
    u8 _14[4];
    s16 giro1, giro2;                /* 0x18, angulos de las dos estelas */
    s16 estela;                      /* 0x1C, pasos que quedan con estela */
    s8 particula;                    /* 0x1E */
} ExtraProyectil;

extern s32 func_80021C3C(Objeto *o);           /* alto del objeto */
extern s32 func_800221A8(Objeto *o, s32 x, s32 y, s32 z);  /* angulo vertical hacia un punto */
extern s32 func_8002218C(Objeto *o, s32 x, s32 z);         /* angulo horizontal hacia un punto */
extern void func_80021D44(s16 *ang, s32 meta, s32 paso);   /* acerca un angulo a otro */

/* Un paso del proyectil: crece hasta escala 0x400, gira hacia el centro de su blanco (si tiene) y acelera
 * un poco, avanza segun sus giros, deja estelas y su particula, y se marca para borrar (bit 0x80 de
 * +0x20) al pasar su alcance. En v0 queda el alcance, o ese byte si se marco. */
s32 func_80037A18(Objeto *o) {
    ExtraProyectil *e = (ExtraProyectil *)&o->extra;
    Objeto *b = e->blanco;
    s32 esc = o->escala[0];
    s32 h, v[3], s, c, n;

    if (esc < 0x400) {
        o->escala[0] = esc + ((0x400 - esc) >> 2);
        if (o->escala[0] >= 0x400) {
            o->escala[0] = 0x400;
        }
        o->escala[1] = o->escala[0];
        o->escala[2] = o->escala[0];
    }
    if (b != NULL) {
        h = func_80021C3C(b) >> 1;
        func_80021D44(&o->rot[0], (s16)func_800221A8(o, b->x, b->y + h, b->z), 0x32);
        func_80021D44(&o->rot[1], (s16)func_8002218C(o, b->x, b->z), 0x32);
        e->rapidez += 0x28F;
        e->rapidez -= e->rapidez >> 8;
    }
    func_8002205C(v, o->rot[0], o->rot[1]);
    o->empuje_x = (v[0] * e->rapidez) >> 12;
    o->vel_y = (v[1] * e->rapidez) >> 12;
    o->empuje_z = (v[2] * e->rapidez) >> 12;
    o->x += o->empuje_x;
    o->y += o->vel_y;
    o->z += o->empuje_z;
    if (e->estela > 0) {
        s = (rsin(e->giro1) * 0xCCC) >> 12;
        c = (rcos(e->giro1) * 0xCCC) >> 12;
        n = e->estela;
        CrearParticula(0x12, o, 0, 0, 0, 0, c, s, 0, n, n, 0, 0xF, 2, 0);
        s = (rsin(e->giro2) * 0xCCC) >> 12;
        c = (rcos(e->giro2) * 0xCCC) >> 12;
        n = e->estela;
        CrearParticula(0x12, o, 0, 0, 0, 0, c, s, 0, n, n, 0, 0xF, 2, 0);
    }
    CrearParticula(e->particula, o, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x14, 2, e->giro1);
    e->giro1 = (e->giro1 + 0xF0) & 0xFFF;
    e->giro2 = (e->giro2 + 0xF0) & 0xFFF;
    e->estela--;
    e->recorrido += e->rapidez;
    if (e->alcance < e->recorrido) {
        *((u8 *)o + 0x20) |= 0x80;
        return *((u8 *)o + 0x20);
    }
    return e->alcance;
}

/* ---- La camara del juego ---- */

/* La parte extra del objeto camara. */
typedef struct {
    s32 *seguir;                     /* 0x00, un punto que se mira en el estado 1 */
    s32 guardada[3];                 /* 0x04, donde estaba antes de acercarse (estado 2) */
    s32 punto[3];                    /* 0x10, a donde va en el estado 3 */
    s32 lejos;                       /* 0x1C, cuanto se aparta en el estado 1 (hasta 0x1999) */
    u8 _20;
    s8 lado;                         /* 0x21 */
    u8 _22[2];
    s8 invertir;                     /* 0x24 */
    s8 espera;                       /* 0x25, pasos sin girar sola */
    u8 _26[2];
    s32 mira[3];                     /* 0x28 */
    s32 ojo[3];                      /* 0x34 */
    s16 giro;                        /* 0x40, cuanto girar alrededor de Sabrina */
    u8 _42[2];
    s32 _44;                         /* 0x44 */
    u8 _48[0x14];
    s8 cuenta;                       /* 0x5C */
} ExtraCamara;

extern s16 D_8007CBC0;               /* D_8007CBD4 guardado */
extern s32 D_8007CA50;               /* botones apretados: 1 y 2 giran la camara */
extern s32 D_8007CBBC;
extern Objeto *D_8007CBAC, *D_8007CBB0;
extern s16 D_8007C872;
extern s32 D_800C64FC[3], D_800C6508[3];  /* mira y ojo fijos (estados 5 y 6) */
extern void func_80047710(void);
extern s32 func_8001BF8C(s32 ax, s32 az, s32 bx, s32 bz);  /* distancia en el plano */
extern s32 func_8001BE8C(s32 ax, s32 az, s32 bx, s32 bz);  /* angulo en el plano */
extern s32 func_8001C2D0(s32 x, s32 y, s32 z, s32 ax, s32 ay, s32 az);
extern s32 func_8002225C(Objeto *o, s32 x, s32 y, s32 z);
extern void func_80034FD0(s32 *a, s32 *b);
extern s32 func_800365F0(s16 *giro, s16 *lado);
extern s32 func_800605C8(Objeto *o, void *a, void *b);
extern s32 func_80014AEC(s32 v);

/* Deja el ojo de la camara en D_8006C444 (su posicion / 256). */
static void ojo_camara(Objeto *o) {
    D_8006C444[0] = o->x >> 8;
    D_8006C444[1] = o->y >> 8;
    D_8006C444[2] = o->z >> 8;
}

/* Mira segun sus giros y los copia en D_8007CAE2/E4. */
static void mirar(Objeto *o) {
    func_8002205C(D_8006C450, o->rot[0], o->rot[1]);
    D_8007CAE2 = o->rot[1];
    D_8007CAE4 = o->rot[0];
}

#define MIRA_ARRIBA 0x6000 /* MOD: cuanto sube el punto de mira (16.16; 0x10000 = 1 unidad) */

extern s32 D_8007CA54, D_8007CA58;   /* botones de arriba / recien apretados */
extern void ActivarObjetosCercanos(void);
extern u8 D_8007CCBC[], D_8007CD18[]; /* entornos de dibujo de las dos paginas; +0x18 = borrar el fondo */

/* MOD: camara libre. SELECT la prende y la apaga (al apagarla vuelve a seguir a Sabrina). Prendida, el juego
 * borra el fondo en cada cuadro: sin cielo (camara fuera del mapa) los cuadros viejos se quedaban pegados. Mientras esta
 * prendida el mando no llega a Sabrina (solo START): flechas arriba/abajo avanzan y retroceden hacia donde
 * mira, izquierda/derecha giran, triangulo/equis miran arriba/abajo, L2/R2 van de lado, L1/R1 suben y
 * bajan y cuadrado va 4 veces mas rapido. */
static void __attribute__((noinline)) camara_libre(Objeto *o) {
    s32 b = D_8007CA50;
    s32 vel = (b & 0x80) ? 4 : 2;
    s32 d[3], l[3], av, la, p;

    o->rot[1] += (((b >> 13) & 1) - ((b >> 15) & 1)) * 24;
    p = o->rot[0] + (((b >> 6) & 1) - ((b >> 4) & 1)) * 20;
    if (p > -1000 && p < 1000) {
        o->rot[0] = p;
    }
    func_8002205C(d, o->rot[0], o->rot[1]);
    func_8002205C(l, 0, o->rot[1] + 0x400);
    av = ((b >> 12) & 1) - ((b >> 14) & 1);
    la = ((b >> 1) & 1) - (b & 1);
    o->x += (d[0] * av + l[0] * la) << vel;
    o->y += (d[1] * av + (((b >> 3) & 1) - ((b >> 2) & 1)) * 0x1000) << vel;
    o->z += (d[2] * av + l[2] * la) << vel;
    ojo_camara(o);
    mirar(o);
    D_8007CA50 &= 0x100;
    D_8007CA54 = 0;
    D_8007CA58 &= 0x800;
}

/* El paso de la camara. Mientras corre no ignora ningun tipo de triangulo. Estados: 0 sigue a Sabrina
 * desde atras (girando con los botones 1 y 2 o sola), 1 se aparta mirando a Sabrina, 2 se acerca a la
 * nuca de Sabrina, 3 vuelve atras, 4 y 5 una escena entre D_8007CBAC y D_8007CBB0, 6 y 8 se mueve hacia
 * un punto fijo. Devuelve (v0) el D_8007CBD4 que restaura. */
s32 func_80035314(Objeto *o) {
    ExtraCamara *e = (ExtraCamara *)&o->extra;
    u8 *ps;
    s32 v[3], w[3], a[3], b[3], d, r, uno, n;
    s16 g, h, ang;

    D_8007CBC0 = D_8007CBD4;
    D_8007CBD4 = -17;
    func_80047710();
    ((s16 *)o->datos)[13] = 2;
    if (p_sabrina == NULL) {
        D_8007CBD4 = D_8007CBC0;
        return (u16)D_8007CBC0;
    }
    /* func_80036250 lee una escala sin valor: lo que quedo 0x14 bytes debajo de la pila del llamador, que
     * en el original es el s1 que guardo func_80047710 (este objeto). Se deja ahi lo mismo. */
    ((Objeto *volatile *)__builtin_frame_address(0))[-5] = o;
    func_80036250();
    func_8003630C();
    ps = (u8 *)&p_sabrina->extra;
    v[0] = p_sabrina->x - o->x;
    v[1] = p_sabrina->y - o->y;
    v[2] = p_sabrina->z - o->z;
    d = func_8001BF8C(0, 0, v[0], v[2]);
    func_8001C45C(v);
    d = (d - 0x40000) >> 4;
    n = (D_8007CA50 >> 8) & 1;
    if (n && !e->_26[0]) {
        e->_20 ^= 1;
        if (!e->_20) {
            o->estado = 0;
        }
    }
    e->_26[0] = n;
    D_8007CCBC[0x18] = D_8007CD18[0x18] = e->_20;
    if (e->_20) {
        camara_libre(o);
        /* MOD: el juego solo crea los objetos de la zona de Sabrina alrededor de la camara. Con la camara libre
         * se crean ademas los de la zona de la camara (Sabrina "prestada" un momento a la camara) y los que
         * rodean a Sabrina (el ojo "prestado" a Sabrina), para que no se borre nada. */
        {
            s32 sx = p_sabrina->x, sz = p_sabrina->z, ox = D_8006C444[0], oz = D_8006C444[2];

            p_sabrina->x = o->x;
            p_sabrina->z = o->z;
            ActivarObjetosCercanos();
            p_sabrina->x = sx;
            p_sabrina->z = sz;
            D_8006C444[0] = sx >> 8;
            D_8006C444[2] = sz >> 8;
            ActivarObjetosCercanos();
            D_8006C444[0] = ox;
            D_8006C444[2] = oz;
        }
        goto fin;
    }
    switch ((u16)o->estado) {
    case 6:
        func_80036410(o, D_800C6508[0], D_800C6508[1], D_800C6508[2], D_800C64FC[0], D_800C64FC[1],
                      D_800C64FC[2], 3);
        func_80036524(o, D_800C64FC[0], D_800C64FC[1], D_800C64FC[2]);
        break;
    case 4:
        if (D_8007CBAC != NULL && D_8007CBB0 != NULL) {
            a[0] = D_8007CBB0->x;
            a[1] = D_8007CBB0->y;
            a[2] = D_8007CBB0->z;
            e->_44 = func_8002225C(D_8007CBAC, a[0], D_8007CBAC->y, a[2]);
            D_8007C872 = 1;
            func_80034FD0(&D_8007CBB0->x, &D_8007CBAC->x);
            o->estado = 5;
        }
        break;
    case 5:
        func_80036524(o, D_800C64FC[0], D_800C64FC[1], D_800C64FC[2]);
        func_80036410(o, D_800C6508[0], D_800C6508[1], D_800C6508[2], D_800C64FC[0], D_800C64FC[1],
                      D_800C64FC[2], 3);
        ojo_camara(o);
        break;
    case 0:
        if (e->espera >= 0) {
            e->espera--;
            if (e->espera < 0) {
                e->espera = 0;
            }
        }
        if (D_8007CA50 & 3) {
            if (D_8007CBBC == 0 && e->espera == 0) {
                e->cuenta = -50;
                if (D_8007CA50 & 2) {
                    e->giro = -300;
                }
                if (D_8007CA50 & 1) {
                    e->giro = 300;
                }
            }
        } else {
            uno = 0;
            if ((s8)ps[0x1D] == 0) {
                func_8002205C(a, 0, p_sabrina->rot[1]);
                func_8002205C(b, 0, o->rot[1]);
                a[0] >>= 4;
                a[1] >>= 4;
                a[2] >>= 4;
                b[0] >>= 4;
                b[1] >>= 4;
                b[2] >>= 4;
                func_8001C33C(a, b);
                uno = 1;
                e->cuenta = 0;
            } else {
                e->cuenta++;
                if (e->cuenta >= 3) {
                    e->cuenta = -126;
                    uno = 1;
                }
            }
            if (uno == 1 && e->espera == 0) {
                ang = o->rot[1];
                func_80021E54(&ang, p_sabrina->rot[1], 2, 3);
                e->giro = ang - o->rot[1];
            }
        }
        e->mira[0] = p_sabrina->x;
        e->mira[1] = func_800350FC(CAMPO_S32(p_sabrina, 0x50)) - 0x11999;
        e->mira[2] = p_sabrina->z;
        v[0] = -(e->mira[0] - o->x);
        v[1] = 0;
        v[2] = -(e->mira[2] - o->z);
        w[0] = v[0];
        w[1] = v[1];
        w[2] = v[2];
        if (func_800365F0(&g, &h) == 1) {
            if ((s8)ps[0x1D] == 0) {
                if (h == 0) {
                    h = -1;
                }
            } else {
                e->giro = g;
                h = 0;
            }
        }
        if (e->giro != 0) {
            n = func_8001BE8C(0, 0, v[0], v[2]) + e->giro;
            while (n < 0) {
                n += 0xFFF;
            }
            while (n >= 0x1001) {
                n -= 0xFFF;
            }
            func_8002205C(b, 0, (s16)n);
            if (func_80036880(b, h) == 0) {
                v[0] = b[0];
                v[1] = b[1];
                v[2] = b[2];
            } else {
                func_8001C45C(v);
            }
        } else {
            func_8001C45C(v);
        }
        v[0] >>= 4;
        v[2] >>= 4;
        e->ojo[0] = e->mira[0] + ((v[0] * 3) << 8);
        e->ojo[2] = e->mira[2] + ((v[2] * 3) << 8);
        e->ojo[1] = e->mira[1] + 0x11999 - 0x23333;
        w[0] = (e->mira[0] - e->ojo[0]) >> 8;
        w[1] = 0;
        w[2] = (e->mira[2] - e->ojo[2]) >> 8;
        r = func_8001C33C(w, w) - 0x900;
        if (r <= 0) {
            e->ojo[1] += r * 64;
        }
        /* MOD: la camara mira un poco por encima de Sabrina (la posicion del ojo ya esta calculada). */
        e->mira[1] -= MIRA_ARRIBA;
        func_80036410(o, e->ojo[0], e->ojo[1], e->ojo[2], e->mira[0], e->mira[1], e->mira[2], 3);
        func_80036524(o, e->mira[0], e->mira[1], e->mira[2]);
        if ((s8)ps[0x1D] == 13) {
            func_80022104(&o->rot[0], &o->rot[1], D_8006C450);
            e->guardada[0] = o->x;
            e->guardada[1] = o->y;
            e->guardada[2] = o->z;
            o->estado = 2;
            func_8002205C(w, 0, p_sabrina->rot[1]);
            w[0] <<= 5;
            w[2] <<= 5;
            o->x = p_sabrina->x - w[0];
            o->y = p_sabrina->y - 0x13333;
            o->z = p_sabrina->z - w[2];
            ojo_camara(o);
            mirar(o);
        }
        e->giro = 0;
        break;
    case 1:
        if (d >= 0x101 || d < -0x80) {
            e->lejos = func_80014AEC(d);
            if (e->lejos >= 0x199A) {
                e->lejos = 0x1999;
            }
            n = d > 0 ? 1 : -1;
            e->lado = e->invertir != 0 ? -n : n;
            if (e->seguir == NULL) {
                o->estado = 0;
            } else {
                v[0] = e->seguir[0] - o->x;
                v[1] = e->seguir[1] - o->y;
                v[2] = e->seguir[2] - o->z;
                func_8001C45C(v);
                if (func_80014AEC(func_8001C2D0(v[0], v[1], v[2], D_8006C450[0], D_8006C450[1],
                                                D_8006C450[2])) >= 0x801 &&
                    (s16)func_800605C8(o, &e->lejos, e) == 8) {
                    o->estado = 0;
                }
            }
        }
        ojo_camara(o);
        v[0] = p_sabrina->x - o->x;
        v[1] = p_sabrina->y - 0x11999 - o->y;
        v[2] = p_sabrina->z - o->z;
        func_8001C45C(v);
        func_80022104(&g, &h, v);
        func_80021E54(&o->rot[0], g, 3, 3);
        func_80021E54(&o->rot[1], h, 3, 3);
        mirar(o);
        if (p_sabrina->estado == 2) {
            o->estado = 0;
        }
        break;
    case 2:
        ps = (u8 *)&p_sabrina->extra;
        h = p_sabrina->rot[1] - (s8)ps[0x20] * 16;
        g = -((s8)ps[0x1F] * 16);
        a[0] = p_sabrina->x - ((((rsin(h) * rcos(g)) >> 12) << 17) >> 12);
        a[2] = p_sabrina->z - ((((rcos(h) * rcos(g)) >> 12) << 17) >> 12);
        a[1] = p_sabrina->y - ((rsin(g) << 17) >> 12);
        o->x += (a[0] - o->x) >> 3;
        o->y += (a[1] - 0x13333 - o->y) >> 3;
        o->z += (a[2] - o->z) >> 3;
        func_80021E54(&o->rot[0], g, 3, 3);
        func_80021E54(&o->rot[1], h, 3, 3);
        mirar(o);
        if ((s8)ps[0x1D] != 13) {
            h = p_sabrina->rot[1];
            e->punto[0] = p_sabrina->x - ((rsin(h) << 18) >> 12);
            e->punto[2] = p_sabrina->y - ((rcos(h) << 18) >> 12);
            e->punto[1] = p_sabrina->z - 0x38000;
            o->estado = 3;
        }
        ojo_camara(o);
        break;
    case 3:
        v[0] = (e->punto[0] - o->x) >> 4;
        v[1] = (e->punto[1] - o->y) >> 4;
        v[2] = (e->punto[2] - o->z) >> 4;
        e->ojo[0] = v[0] + o->x;
        e->ojo[1] = v[1] + o->y;
        e->ojo[2] = v[2] + o->z;
        if (p_sabrina->extra._1D == 13) {
            break;
        }
        o->estado = 0;
        func_8002205C(a, 0, p_sabrina->rot[1]);
        if (func_80036D58(a[0], a[1], a[2], p_sabrina->y - 0x23333) == 0) {
            o->x = e->guardada[0];
            o->y = e->guardada[1];
            o->z = e->guardada[2];
            ojo_camara(o);
        }
        break;
    case 8:
        func_80036410(o, e->ojo[0], e->ojo[1], e->ojo[2], e->mira[0], e->mira[1], e->mira[2], 3);
        func_80036524(o, e->mira[0], e->mira[1], e->mira[2]);
        D_8007CAE2 = o->rot[1];
        D_8007CAE4 = o->rot[0];
        ojo_camara(o);
        break;
    }
fin:
    D_8007CBD4 = D_8007CBC0;
    return (u16)D_8007CBC0;
}

/* ¿Hay pared a los lados entre Sabrina y la camara? Prueba un segmento de cada lado (de Sabrina, corrida
 * a un costado, hacia la camara corrida al mismo costado). Si choca el primero deja lado = 1 y giro =
 * -300; si choca el segundo, giro = 300 (lado queda en 0). Devuelve 1 si choco alguno. */
s32 func_800365F0(s16 *giro, s16 *lado) {
    s32 v[3];
    s32 az, bz, ax, bx, cx, cz;

    v[0] = D_8007CAFC->x - p_sabrina->x;
    v[1] = 0;
    v[2] = D_8007CAFC->z - p_sabrina->z;
    func_8001C45C(v);
    az = (((v[2] >> 4) * 0x33) >> 8) << 8;
    bz = (((v[2] >> 4) << 7) >> 8) << 8;
    ax = -(((v[0] >> 4) * 0x33) >> 8) << 8;
    bx = -(((v[0] >> 4) << 7) >> 8) << 8;
    cx = (((v[0] >> 4) << 7) >> 8) << 8;
    cz = (((v[2] >> 4) << 7) >> 8) << 8;
    D_800C6594[0] = p_sabrina->x + az - cx;
    D_800C6594[2] = p_sabrina->z + ax - cz;
    D_800C6594[1] = p_sabrina->y - 0x16666;
    D_800C65A0[0] = D_8007CAFC->x + bz;
    D_800C65A0[2] = D_8007CAFC->z + bx;
    D_800C65A0[1] = D_8007CAFC->y;
    func_8003B38C(D_800C6594, D_800C6594, D_800C65A0);
    if (func_8003AE84() != 0) {
        *lado = 1;
        *giro = -300;
        return 1;
    }
    *lado = 0;
    D_800C6594[0] = p_sabrina->x - az - cx;
    D_800C6594[2] = p_sabrina->z - ax - cz;
    D_800C6594[1] = p_sabrina->y - 0x16666;
    D_800C65A0[0] = D_8007CAFC->x - bz;
    D_800C65A0[2] = D_8007CAFC->z - bx;
    D_800C65A0[1] = D_8007CAFC->y;
    func_8003B38C(D_800C6594, D_800C6594, D_800C65A0);
    if (func_8003AE84() != 0) {
        *giro = 300;
        return 1;
    }
    return 0;
}
