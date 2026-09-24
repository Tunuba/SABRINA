#include "juego.h"

/* Funciones sueltas de las bibliotecas de Sony (libapi, libc, libetc) enlazadas en el juego. */

typedef s32 (*FuncCallback)(void);

extern FuncCallback *D_800649A0;  /* tabla de funciones del modulo de interrupciones de libetc */
extern volatile s32 D_800649EC;   /* cuantas vueltas de la pantalla van (VSync) */
extern char D_80061048[];         /* "VSync: timeout\n" */

s32 puts(const char *s);
void ChangeClearPAD(s32 modo);
void ChangeClearRCnt(s32 contador, s32 modo);

/* EnterCriticalSection (libapi): llamada al sistema 1, apaga las interrupciones. */
s32 func_800143E4(void) {
    register s32 a0 asm("a0") = 1;
    register s32 v0 asm("v0");

    asm volatile("syscall 0" : "=r"(v0) : "r"(a0) : "memory");
    return v0;
}

/* ExitCriticalSection (libapi): llamada al sistema 2, prende las interrupciones. */
s32 func_800143F4(void) {
    register s32 a0 asm("a0") = 2;
    register s32 v0 asm("v0");

    asm volatile("syscall 0" : "=r"(v0) : "r"(a0) : "memory");
    return v0;
}

/* strchr (libc): primer caracter c de la cadena (tambien el 0 final si c es 0); NULL si no esta o si la
 * cadena es NULL. Compara como char con signo. */
char *func_80014FF0(char *s, s32 c) {
    s8 buscado;
    s8 letra;

    if (s == NULL) {
        return NULL;
    }
    buscado = (s8)c;
    do {
        letra = *s;
        if (letra == buscado) {
            return s;
        }
        s++;
    } while (letra != 0);
    return NULL;
}

/* strlen (libc): largo de la cadena; 0 si es NULL. */
s32 func_800150F0(char *s) {
    s32 n = 0;

    if (s == NULL) {
        return 0;
    }
    while (*s++ != 0) {
        n++;
    }
    return n;
}

/* v_wait de VSync (libetc): espera hasta que el contador de vueltas pase de cuenta. Si se da mas de
 * tiempo * 0x8000 vueltas de espera, avisa "VSync: timeout" y reinicia los manejadores del control y del
 * contador 3. */
void func_800161D4(s32 cuenta, s32 tiempo) {
    volatile s32 limite = tiempo << 15;

    while (D_800649EC < cuenta) {
        if (--limite == -1) {
            puts(D_80061048);
            ChangeClearPAD(0);
            ChangeClearRCnt(3, 0);
            return;
        }
    }
}

/* Llama a la funcion 1 de la tabla del modulo de interrupciones de libetc (+0x04). */
s32 func_80016970(void) {
    return D_800649A0[1]();
}
