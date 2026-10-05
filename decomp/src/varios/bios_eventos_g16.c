#include "juego.h"

/* Eventos, interrupciones y tarjeta: funciones que llaman a la BIOS (DeliverEvent, OpenEvent, TestEvent,
 * SysEnqIntRP...). 05-10: los borradores de m2c (src/auto) las llamaban sin argumentos, porque prototipos.h las
 * declara (void), y pasaban como IGUAL porque el modelo de la BIOS no hace nada con ellos; ahora verificar.py
 * compara los argumentos (ARGS_BIOS). Aqui van con los de la original. */

extern void DeliverEvent(u32 clase, s32 especificador);
extern s32 OpenEvent(u32 clase, s32 especificador, s32 modo, void *funcion);
extern s32 CloseEvent(s32 evento);
extern s32 TestEvent(s32 evento);
extern s32 EnableEvent(s32 evento);
extern s32 SysEnqIntRP(s32 prioridad, void *entrada);
extern s32 SysDeqIntRP(s32 prioridad, void *entrada);
extern void HookEntryInt(void *punto);
extern s32 erase(char *nombre);
extern void ChangeClearPAD(s32 valor);
extern void StartCARD2(void);
extern s32 func_800143E4(void);
extern s32 func_800143F4(void);
extern s32 printf(const char *formato, ...);
extern char *strcat(char *a, const char *b);
extern void UserFuncOpen(void *f);
extern void func_800508D4(s32 puerto, char *nombre);
extern s32 func_80051284(s32 estado);
extern void func_8003EA90(void);
extern s32 func_80050034();
extern s32 func_800149C0();
extern s32 func_80014A28();
extern s32 func_800519E4();
extern s32 func_800519F8();
extern s32 func_80051A0C();
extern s32 func_80051A20();
extern s32 func_80051A34();
extern s32 func_80051A48();
extern s32 func_80051A5C();
extern s32 func_80051A70();
void func_80051D14(void);

/* --- interrupciones de los contadores (libetc) --- */

/* La entrada de interrupcion de prioridad 1 (D_80084B3C): siguiente, funcion, verificacion, y un dato. */
extern s32 D_80084B3C[4];

/* Pone func_800149C0/func_80014A28 en la entrada y la vuelve a encolar en la prioridad 1. */
s32 func_80014910(void) {
    func_800143E4();
    D_80084B3C[1] = (s32) func_800149C0;
    D_80084B3C[2] = (s32) func_80014A28;
    D_80084B3C[0] = 0;
    D_80084B3C[3] = 0;
    SysDeqIntRP(1, D_80084B3C);
    SysEnqIntRP(1, D_80084B3C);
    func_800143F4();
    return 1;
}

/* Saca la entrada de la prioridad 1. */
s32 func_80014988(void) {
    func_800143E4();
    SysDeqIntRP(1, D_80084B3C);
    func_800143F4();
    return 1;
}

/* --- modulo de interrupciones (libetc), D_80063918 --- */

extern u8 D_80063918[];
extern u16 *D_800649A8;
extern s32 *D_800649AC;

/* Vuelve a enganchar el punto de vuelta guardado (+0x38) si el modulo estaba apagado, y repone las mascaras.
 * Devuelve el estado, o NULL si ya estaba prendido. */
u8 *func_80016874(void) {
    if (*(u16 *) D_80063918 != 0) {
        return NULL;
    }
    HookEntryInt(D_80063918 + 0x38);
    *(u16 *) D_80063918 = 1;
    *D_800649A8 = *(u16 *) (D_80063918 + 0x32);
    *D_800649AC = *(s32 *) (D_80063918 + 0x34);
    func_800143F4();
    return D_80063918;
}

/* --- eventos del CD (libcd): DeliverEvent(HwCdRom 0xF0000003, ...) --- */

void func_80029808(void) {
    DeliverEvent(0xF0000003, 0x20);
}

void func_80029830(void) {
    DeliverEvent(0xF0000003, 0x40);
}

void func_80029858(void) {
    DeliverEvent(0xF0000003, 0x40);
}

/* --- sonido (libspu) --- */

extern s32 D_80074EAC;
extern u16 *D_80074EBC;                  /* registros del SPU */
extern void (*D_80074EE0)(u32);

/* Apaga los bits 4-5 del control del SPU (0x1AA), espera hasta 0xF00 vueltas a que se apaguen, y avisa el fin
 * de la transferencia: con la funcion del usuario si hay, o con DeliverEvent(HwSPU 0xF0000009, 0x20). */
void func_8003E554(void) {
    u32 i;

    if (D_80074EAC == 0) {
        func_8003EA90();
    }
    D_80074EBC[0x1AA / 2] &= 0xFFCF;
    if (D_80074EBC[0x1AA / 2] & 0x30) {
        for (i = 1; i < 0xF01; i++) {
            if (!(D_80074EBC[0x1AA / 2] & 0x30)) {
                break;
            }
        }
    }
    if (D_80074EE0 != NULL) {
        D_80074EE0(0xF0000000);
        return;
    }
    DeliverEvent(0xF0000009, 0x20);
}

/* --- tarjeta de memoria (libcard) --- */

extern s32 D_800D52C0[];
extern s32 D_800D52B4;
extern s32 D_800D5318;
extern char D_800621BC[];
extern char D_80062360[];

/* Borra bu<puerto>:<nombre>. Devuelve 0 si se borro, -1 si habia un evento abierto, o el codigo de la tarjeta
 * (reintenta con 3 enseguida y con 2 hasta 4 veces; 0 pasa a 5). */
/* El cuerpo de func_800515B0. ruta en el marco del stub (sp+0x10 de la original) y resultado en ruta+32, como la
 * original (guarda ahi lo que devuelve erase en cada vuelta): un nombre de mas de 32 letras desborda ruta igual. */
__attribute__((noinline, used)) static s32 borrar_cuerpo(s32 puerto, char *nombre, char *ruta) {
    volatile s32 *resultado = (volatile s32 *) (ruta + 32);
    s32 veces = 0;
    volatile s32 *tarjeta = D_800D52C0;

    if (D_800D52C0[0] != 0) {
        printf(D_80062360);
        return -1;
    }
    func_800508D4(puerto, ruta);
    strcat(ruta, nombre);
    D_800D52C0[3] |= 1 << D_800D52C0[4];
    for (;;) {
        *resultado = erase(ruta);
        if (*resultado != 0) {
            return 0;
        }
        D_800D5318 = func_80051284(0);
        if (D_800D52C0[0] > 0) {
            printf(D_800621BC);
        } else {
            D_800D52C0[0] = 2;
            D_800D52C0[1] = 0;
            D_800D52C0[2] = 0;
            D_800D52C0[4] = puerto;
            UserFuncOpen(func_80050034);
        }
        if (tarjeta[0] != 0 || tarjeta[2] != 0) {
            (void) tarjeta[0];
            (void) tarjeta[1];
            if (tarjeta[2] == 0) {
                while (tarjeta[2] == 0) {
                }
            }
            *resultado = D_800D52B4;
            tarjeta[2] = 0;
        }
        func_80051284(D_800D5318);
        if (*resultado == 3) {
            continue;
        }
        if (*resultado != 2 || ++veces >= 4) {
            break;
        }
    }
    if (*resultado == 0) {
        *resultado = 5;
    }
    return *resultado;
}

/* Stub con el marco de la original (0x50): s0-s3 en 0x38-0x44, ra en 0x48, ruta en 0x10. */
__attribute__((naked))
s32 func_800515B0(s32 puerto, char *nombre) {
    __asm__(".set noreorder\n"
            "\taddiu $sp, $sp, -0x50\n"
            "\tsw $16, 0x38($sp)\n"
            "\tsw $17, 0x3C($sp)\n"
            "\tsw $18, 0x40($sp)\n"
            "\tsw $19, 0x44($sp)\n"
            "\tsw $31, 0x48($sp)\n"
            "\tjal borrar_cuerpo\n"
            "\taddiu $6, $sp, 0x10\n"
            "\tlw $31, 0x48($sp)\n"
            "\tlw $19, 0x44($sp)\n"
            "\tlw $18, 0x40($sp)\n"
            "\tlw $17, 0x3C($sp)\n"
            "\tlw $16, 0x38($sp)\n"
            "\tjr $31\n"
            "\taddiu $sp, $sp, 0x50\n"
            ".set reorder");
}

/* Los 8 eventos de la tarjeta: 4 de la BIOS (SwCARD 0xF4000001) y 4 del hardware (HwCARD 0xF0000011), uno por
 * cada resultado (listo 0x4, error 0x8000, nueva 0x100, tiempo 0x2000), modo 0x1000 (con funcion). */
extern s32 D_800D5370[8];
extern s32 D_800D5390[4];               /* banderas de los eventos del hardware (4-7) */
extern s32 D_800D53A0[4];               /* banderas de los eventos de la BIOS (0-3) */

void func_80051A84(void) {
    s32 antes = func_800143E4();

    D_800D5370[0] = OpenEvent(0xF4000001, 0x4, 0x1000, func_800519E4);
    D_800D5370[1] = OpenEvent(0xF4000001, 0x8000, 0x1000, func_800519F8);
    D_800D5370[2] = OpenEvent(0xF4000001, 0x100, 0x1000, func_80051A0C);
    D_800D5370[3] = OpenEvent(0xF4000001, 0x2000, 0x1000, func_80051A20);
    D_800D5370[4] = OpenEvent(0xF0000011, 0x4, 0x1000, func_80051A34);
    D_800D5370[5] = OpenEvent(0xF0000011, 0x8000, 0x1000, func_80051A48);
    D_800D5370[6] = OpenEvent(0xF0000011, 0x100, 0x1000, func_80051A5C);
    D_800D5370[7] = OpenEvent(0xF0000011, 0x2000, 0x1000, func_80051A70);
    EnableEvent(D_800D5370[0]);
    EnableEvent(D_800D5370[1]);
    EnableEvent(D_800D5370[2]);
    EnableEvent(D_800D5370[3]);
    EnableEvent(D_800D5370[4]);
    EnableEvent(D_800D5370[5]);
    EnableEvent(D_800D5370[6]);
    EnableEvent(D_800D5370[7]);
    func_80051D14();
    if (antes == 1) {
        func_800143F4();
    }
}

void func_80051C60(void) {
    s32 antes = func_800143E4();

    CloseEvent(D_800D5370[0]);
    CloseEvent(D_800D5370[1]);
    CloseEvent(D_800D5370[2]);
    CloseEvent(D_800D5370[3]);
    CloseEvent(D_800D5370[4]);
    CloseEvent(D_800D5370[5]);
    CloseEvent(D_800D5370[6]);
    CloseEvent(D_800D5370[7]);
    if (antes == 1) {
        func_800143F4();
    }
}

/* Limpia los 8 eventos (TestEvent los baja) y las banderas. */
void func_80051D14(void) {
    volatile s32 *b = D_800D5390;
    volatile s32 *h = D_800D53A0;

    TestEvent(D_800D5370[0]);
    TestEvent(D_800D5370[1]);
    TestEvent(D_800D5370[2]);
    TestEvent(D_800D5370[3]);
    TestEvent(D_800D5370[4]);
    TestEvent(D_800D5370[5]);
    TestEvent(D_800D5370[6]);
    TestEvent(D_800D5370[7]);
    b[3] = 0;
    b[2] = b[3];
    b[1] = b[2];
    b[0] = b[1];
    h[3] = 0;
    h[2] = h[3];
    h[1] = h[2];
    h[0] = h[1];
}

/* Espera a que llegue un evento del hardware (banderas de D_800D5390, como bits 0-3), limpia los suyos y
 * devuelve el bit >> 1 (0 listo, 1 error, 2 nueva, 4 tiempo). */
s32 func_80051E1C(void) {
    volatile s32 *b = D_800D5390;
    s32 bits;

    do {
        bits = b[0] + b[1] * 2 + b[2] * 4 + b[3] * 8;
    } while (bits == 0);
    TestEvent(D_800D5370[4]);
    TestEvent(D_800D5370[5]);
    TestEvent(D_800D5370[6]);
    TestEvent(D_800D5370[7]);
    b[3] = 0;
    b[2] = b[3];
    b[1] = b[2];
    b[0] = b[1];
    return bits >> 1;
}

/* Lo mismo con los eventos de la BIOS (D_800D53A0). */
s32 func_80051EF4(void) {
    volatile s32 *h = D_800D53A0;
    s32 bits;

    do {
        bits = h[0] + h[1] * 2 + h[2] * 4 + h[3] * 8;
    } while (bits == 0);
    TestEvent(D_800D5370[0]);
    TestEvent(D_800D5370[1]);
    TestEvent(D_800D5370[2]);
    TestEvent(D_800D5370[3]);
    h[3] = 0;
    h[2] = h[3];
    h[1] = h[2];
    h[0] = h[1];
    return bits >> 1;
}

/* Arranca la tarjeta y deja de limpiar las interrupciones del mando. */
void func_80052350(void) {
    func_800143E4();
    StartCARD2();
    ChangeClearPAD(0);
    func_800143F4();
}
