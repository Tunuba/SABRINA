/* MOD SABRINA KART: funciones del juego que en el disco del kart no corren nunca, vacias para que su cuerpo quede
 * libre para el C del kart (armar_c.py --huecos src/mods/kart_huecos.c).
 *
 * Son los "iniciar" de clases de objetos de los otros mundos (enemigos, cofres, cajas, rutas, marcas, el jefe...):
 * nadie las llama con jal, solo la tabla de clases (func_800252A0 / CrearObjetoMundo) al crear un objeto de ese tipo.
 * En el kart el HUB no tiene ningun objeto (nivel_fantasma sin_objetos) y a los otros niveles no se puede ir, asi que
 * ninguna se llega a llamar. La lista sale de notas/OBJETOS.md: las funciones de clase que no usan ni H1W ni FRW (el
 * menu) y que no tienen ninguna llamada en asm/800.s. No van func_8003821C (esta en la camara, ya en C) ni
 * func_8004A3B4 (tiene dos llamadas). */

void func_8002E21C(void) {}
void func_8003477C(void) {}
void func_8003CF60(void) {}
void func_8003D478(void) {}
void IniciarEnemigoTipo15(void) {}
void func_80045B60(void) {}
void func_800460CC(void) {}
void func_80049FCC(void) {}
void func_80052784(void) {}
void func_80053C74(void) {}
void func_800547EC(void) {}
void func_80054A58(void) {}
void func_80055998(void) {}
void func_800563C4(void) {}
void func_80057610(void) {}
void func_80057B38(void) {}
void func_8005A1EC(void) {}
void func_8005B008(void) {}
void func_8005EAD4(void) {}

/* Y lo que esos objetos hacen en cada paso (su "actualizar", la primera palabra de la cabecera de su clase): solo los
 * nombran las tablas de clases de los cinco mundos (por eso salen 5 veces en asm/data) y los iniciar de arriba. No
 * va func_800349F0, que tambien sale asi pero es la reaparicion de Sabrina. */
void func_80045278(void) {}
void func_8002E51C(void) {}
void func_80046428(void) {}
void func_8005A360(void) {}
void func_800528AC(void) {}
void func_8003D5F4(void) {}
void func_80045CF4(void) {}
void func_8004A140(void) {}
void func_80054894(void) {}
void func_80055A38(void) {}
void func_80057800(void) {}
void func_80057CA0(void) {}
void func_8005B150(void) {}
void func_8003D00C(void) {}
void func_80053ED8(void) {}
void func_8005655C(void) {}
