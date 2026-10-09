/* PCdrv y un trozo del mando (08-10). En la biblioteca son asm de tres a diez instrucciones.
 *
 * PCdrv: las herramientas de desarrollo escriben archivos en la PC conectada con una instruccion "break" cuyo
 * codigo dice la operacion (0x102 crear, 0x104 cerrar, 0x106 escribir). El argumento va en a1 (y a2, a3), la
 * respuesta vuelve en v0 (0 si salio bien) y v1 (el manejador o lo escrito). En C la llamada es el mismo break
 * con variables de registro.
 *
 * No incluye juego.h: prototipos.h los declara con otros argumentos (los que adivino m2c). */

typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;

/* PCcreat(nombre): el manejador del archivo nuevo, o -1 si la PC dijo que no. */
s32 func_800294F0(s32 nombre) {
    register s32 a1 asm("$5") = nombre;
    register s32 a2 asm("$6") = 0;
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");

    __asm__ volatile("break 0, 258" : "=r"(v0), "=r"(v1) : "r"(a1), "r"(a2) : "memory");
    if (v0 != 0) {
        v1 = -1;
    }
    return v1;
}

/* PCclose(manejador). */
void func_80029518(s32 manejador) {
    register s32 a1 asm("$5") = manejador;
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");

    __asm__ volatile("break 0, 260" : "=r"(v0), "=r"(v1) : "r"(a1) : "memory");
    __asm__ volatile("" : : "r"(v0), "r"(v1));
}

/* PCwrite(manejador, datos, largo): lo que se escribio. */
s32 func_80029530(s32 manejador, s32 datos, s32 largo) {
    register s32 a1 asm("$5") = manejador;
    register s32 a2 asm("$6") = largo;
    register s32 a3 asm("$7") = datos;
    register s32 v0 asm("$2");
    register s32 v1 asm("$3");

    __asm__ volatile("break 0, 262" : "=r"(v0), "=r"(v1) : "r"(a1), "r"(a2), "r"(a3) : "memory");
    __asm__ volatile("" : : "r"(v0));
    return v1;
}

/* Trozo de la rutina del mando: no es una funcion con argumentos, el que llega deja en v1 la base de los
 * registros del puerto (0x1F801040) y en v0 los bits a prender. Prende esos bits y 0x12 en el registro de
 * control (+0xA) y espera 0x28 vueltas para que el puerto los tome. */
void func_80052114(void) {
    register volatile u16 *puerto asm("$3");
    register u32 bits asm("$2");
    register s32 i asm("$8");

    __asm__ volatile("" : "=r"(puerto), "=r"(bits));
    puerto[5] = puerto[5] | bits | 0x12;
    for (i = 0x28; ; ) {
        i--;
        __asm__ volatile("" : "+r"(i));
        if (i == 0) {
            break;
        }
    }
}
