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
 * dano. Pone extra+0 = 0x4CCC, extra+0x10 = 0, extra+0x18 = 0, extra+0x1A = 0x800 y extra+0x1C = 50. */
void func_8003795C(Objeto *o, s32 clase) {
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
