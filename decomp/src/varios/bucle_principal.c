#include "juego.h"

/* El bucle principal del juego (08-10). Arma el monton, la camara de objetos y los avisos de las pantallas,
 * muestra las pantallas legales y despues, nivel tras nivel: carga el sonido, las dos texturas (si faltan,
 * en las carpetas de desarrollo las convierte y se queda ahi), el .INO y el WRLDDATA, juega hasta que
 * `jugando` baja, elige el nivel siguiente si se pidio y pasa los videos del final. Nunca vuelve en la
 * practica: el do-while vuelve a empezar mientras `jugando` siga en 0 al terminar el nivel. */

typedef struct {
    s16 x, y, w, h;
} Rect;

typedef s32 (*Metodo)(void *yo, s32 a);

extern Rect D_8007C754;                /* donde va la textura .PIC del nivel en la VRAM */
extern Rect D_8007C75C;                /* donde va la textura .TEX */
extern u32 D_80060A08;                 /* el fin del ejecutable cargado */
extern u32 D_800609F8;                 /* la pila, en KB */
extern u32 D_800609F0;                 /* el tope de la RAM */
extern u32 D_800609FC;                 /* el monton, en KB */
extern char D_8006296C[];              /* aviso del fin del ejecutable */
extern char D_80062978[];              /* aviso del monton */
extern char D_8006299C[];              /* "convertido el .TEX" */
extern char D_800629D4[];              /* "convertido el .PIC" */
extern char D_80062A10[];              /* el video del final malo */
extern char D_80062A24[];              /* el video del final bueno */
extern char D_8007C764[];              /* "%s%s" */
extern char D_8007A1D0[];              /* la carpeta de las texturas */
extern char D_8007C76C[];              /* el aviso de depuracion de cada vuelta */
extern u8 D_8007C9D8;
extern u8 D_80060A58[];                /* tabla de funciones de la clase base */
extern u8 D_80075900[];                /* tabla de funciones de la clase del juego */
extern u8 D_800758F8[];                /* sus metodos (los de +0x30 y +0x38) */
extern void *D_8007C9DC;               /* el objeto del juego (en la pila de esta funcion) */
extern s32 D_8007CC28;
extern s16 jugando;                    /* 0x8007C9FC: se juega el nivel */
/* jugando + 2: la carga del nivel sigue (lo baja una interrupcion) */
#define D_8007C9FE (((volatile u16 *)&jugando)[1])
extern s16 D_8007CA20;
extern s32 D_8007C9F0;
extern s32 D_8007C9F4;
extern s8 nivel_actual;
extern u8 D_8007CA01;
extern u8 D_8007CAE8;                  /* niveles cargados */
extern u8 D_8007CC14;                  /* se pidio otro nivel */
extern s32 D_800C98A4;                 /* el nivel pedido */
extern s32 D_8007CC04;                 /* el final: 1 malo, 2 bueno */
extern u8 *D_8007CC2C;
extern s32 D_8007CC30;
extern void *D_8007CC34;
extern void *D_8007CC38;
extern u8 partida[];
extern char *tabla_sonido_niveles[];
extern char *tabla_pic_niveles[];
extern char *tabla_tex_niveles[];

extern void InitHeap(u32 base, u32 tam);
extern s32 printf(const char *formato, ...);
extern s32 sprintf(char *destino, const char *formato, ...);
extern void func_800212D4(void);
extern void func_80021C48(s32 n);
extern void func_8004E72C(void *yo);
extern void func_8004DC78(void);
extern void func_8004ADB0(void);
extern void func_8004AEAC(void);
extern void func_8004EAE8(s32 a, s32 b, s32 c);
extern void func_8004C82C(void);
extern void PantallasLegales(void);
extern void func_8004E268(void);
extern s32 func_8001E164(s32 a);
extern void func_80019CC4(void);
extern void CargarSonidoNivel(char *nombre);
extern void *CargarArchivoEntero(char *ruta, s32 modo);
extern void func_800219C8(void);
extern void SubirAVRAM(Rect *r, void *datos);
extern void Liberar(void *p);
extern void HerramientaConvertirPIC(char *nombre);
extern void func_80021190(void);
extern void func_800185A8(char *nombre);
extern void HerramientaConvertirTEX(char *nombre);
extern void CargarINO(char *nombre);
extern void func_8001C794(void);
extern void CargarWRLDDATA(char *nombre);
extern void func_8004E194(void);
extern void func_8004BDA0(void);
extern void func_8005E2A0(void);
extern void func_8005E59C(void);
extern void func_8003DDFC(void);
extern void func_8004B320(s32 nivel);
extern void ImprimirDepuracion(char *texto);
extern void func_80019D80(void);
extern void func_80021B4C(void);
extern void thunk_FUN_8004aea4(void);
extern void func_80019D18(void);
extern void func_8004E238(void);
extern void ReproducirSTR(char *video, s32 cuadros);
extern void func_800219F8(void);
extern void func_8004E6C0(void *yo, s32 liberar);

/* El marco va a mano (stub en asm con el de la original: 0x1B8, s0/s1/ra en 0x10/0x14/0x18) y el cuerpo en C
 * recibe la direccion de ese marco: el objeto del juego vive en sp+0xB4 de la original y su direccion queda en
 * D_8007C9DC, asi que tiene que caer en el mismo lugar. La ruta va en sp+0x24 y las dos areas de VRAM en sp+0xA4
 * y sp+0xAC.
 * Lo primero (el monton y las dos llamadas de arranque) va aparte, en preparar, con solo base y libre vivos:
 * el setjmp del modulo de interrupciones (que corre adentro de func_800212D4) guarda s1-s7 en un global, y en la
 * original ahi estan libre (s1) y lo que traia el que llamo (s2-s7). En una sola funcion GCC ocupaba s2 con el
 * marco y s1 con base. */
/* la original solo usa s0 y s1: s2-s7 y fp quedan reservados en todo el archivo (GCC no los usa ni los salva) */
register u32 r_s2 asm("$18");
register u32 r_s3 asm("$19");
register u32 r_s4 asm("$20");
register u32 r_s5 asm("$21");
register u32 r_s6 asm("$22");
register u32 r_s7 asm("$23");
register u32 r_fp asm("$30");

__attribute__((noinline, used)) static s32 preparar(void) {
    u32 base;
    register s32 libre asm("$17");

    base = (D_80060A08 & ~0xF) + 0x10;
    libre = ((D_800609F0 - (D_800609F8 << 10)) & ~0xF) - base;
    InitHeap(base, D_800609FC << 10);
    printf(D_8006296C, D_80060A08);
    printf(D_80062978, base, D_800609FC << 10);
    __asm__ volatile("" : "+r"(libre));
    func_800212D4();
    func_80021C48(0x400);
    return libre;
}

__attribute__((noinline, used)) static s32 bucle_cuerpo(u8 *marco, s32 libre) {
    s32 v;
    void *datos;
#define RUTA ((char *)(marco + 0x24))
#define PIC ((Rect *)(marco + 0xA4))
#define TEX ((Rect *)(marco + 0xAC))
#define JUEGO ((void **)(marco + 0xB4))

    *PIC = D_8007C754;
    *TEX = D_8007C75C;

    /* el objeto del juego: primero con la tabla de la clase base y enseguida con la suya (constructor en linea) */
    JUEGO[0] = &D_8007C9D8;
    *(void * volatile *)&JUEGO[1] = D_80060A58;
    JUEGO[2] = D_800758F8;
    *(void * volatile *)&JUEGO[1] = D_80075900;
    func_8004E72C(JUEGO);
    D_8007C9DC = JUEGO;
    v = (*(Metodo *)(*(u8 **)((u8 *)D_8007C9DC + 8) + 0x30))(D_8007C9DC, libre - D_8007CC28 - 0x1400);
    (*(Metodo *)(*(u8 **)((u8 *)D_8007C9DC + 8) + 0x38))(D_8007C9DC, v);
    func_8004DC78();
    D_8007CC2C = partida;
    D_8007CC30 = 0x13AC;
    D_8007CC34 = func_8004ADB0;
    D_8007CC38 = func_8004AEAC;
    func_8004EAE8(0x2E, 0x30, 0x2F);
    func_8004C82C();
    PantallasLegales();

    do {
        func_8004E268();
        jugando = 1;
        D_8007CA20 = 0;
        D_8007C9F0 = func_8001E164(0);
        D_8007C9F4 = func_8001E164(0);
        func_80019CC4();
        CargarSonidoNivel(tabla_sonido_niveles[nivel_actual]);

        sprintf(RUTA, D_8007C764, D_8007A1D0, tabla_pic_niveles[nivel_actual]);
        datos = CargarArchivoEntero(RUTA, 0);
        if (datos == NULL) {
            HerramientaConvertirPIC(tabla_pic_niveles[nivel_actual]);
            printf(D_800629D4);
            for (;;) {
            }
        }
        func_800219C8();
        SubirAVRAM(PIC, datos);
        Liberar(datos);

        sprintf(RUTA, D_8007C764, D_8007A1D0, tabla_tex_niveles[nivel_actual]);
        datos = CargarArchivoEntero(RUTA, 0);
        if (datos == NULL) {
            func_80021190();
            func_800185A8(tabla_sonido_niveles[nivel_actual]);
            HerramientaConvertirTEX(tabla_tex_niveles[nivel_actual]);
            printf(D_8006299C);
            for (;;) {
            }
        }
        D_8007C9FE = 1;
        SubirAVRAM(TEX, datos);
        Liberar(datos);
        D_8007CAE8++;
        CargarINO(tabla_sonido_niveles[nivel_actual]);
        func_8001C794();

        CargarWRLDDATA(tabla_sonido_niveles[nivel_actual]);
        func_8004E194();
        func_8004BDA0();
        if (nivel_actual == 0) {
            func_8005E2A0();
        } else {
            func_8005E59C();
        }
        while (D_8007C9FE != 0) {
        }
        D_8007C9FE = 0;
        func_8003DDFC();
        func_8004B320(nivel_actual);
        while (jugando != 0) {
            ImprimirDepuracion(D_8007C76C);
            func_80019D80();
            func_80021B4C();
        }

        if (D_8007CC14 == 1) {
            s32 n;

            D_8007CC14 = 0;
            nivel_actual = D_800C98A4;
            n = nivel_actual;
            D_8007CA01 = n;
            /* el nivel siguiente: tras el 3, el 6, el 9 y el 12 (los jefes) se va al 13 */
            switch (n) {
            case 1: case 2: case 4: case 5: case 7: case 8: case 10: case 11:
                nivel_actual = n + 1;
                break;
            case 3: case 6: case 9: case 12:
                nivel_actual = 13;
                break;
            }
        }
        thunk_FUN_8004aea4();
        func_80019D18();
        func_8004E238();
        if (D_8007CC04 == 2) {
            ReproducirSTR(D_80062A24, 0x843);
        } else if (D_8007CC04 == 1) {
            ReproducirSTR(D_80062A10, 0x213);
        }
        func_800219F8();
        D_8007CC04 = 0;
    } while (jugando == 0);

    func_8004E6C0(JUEGO, -1);
    return 0;
}

__attribute__((naked))
s32 BuclePrincipal(void) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x1B8\n"
            "\tsw $31, 0x18($sp)\n"
            "\tsw $17, 0x14($sp)\n"
            "\tsw $16, 0x10($sp)\n"
            "\tjal preparar\n"
            "\tnop\n"
            "\taddu $5, $2, $0\n"
            "\tjal bucle_cuerpo\n"
            "\taddu $4, $sp, $0\n"
            "\tlw $31, 0x18($sp)\n"
            "\tlw $17, 0x14($sp)\n"
            "\tlw $16, 0x10($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x1B8\n"
            ".set reorder");
}

