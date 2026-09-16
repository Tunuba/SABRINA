# Descompilacion

Todo esta en `decomp\`. El desensamblado, lo compilado, las capturas de memoria y el C sacado del juego
no van al repositorio (ver `.gitignore`); los scripts y la configuracion si.

## Herramientas (en WSL Ubuntu-24.04, todas libres)

- `scripts\decomp_instalar.sh`: venv en `~/decomp-herramientas` con splat 0.50, m2c, asm-differ, maspsx y
  unicorn 2.1.4. Paquetes de apt: python3-venv, binutils-mipsel-linux-gnu, gcc-mipsel-linux-gnu.
- `scripts\decomp_compiladores.sh`: GCC para PS1 2.6.3, 2.7.2, 2.8.0, 2.8.1, 2.91.66 y 2.95.2 de
  decompals/old-gcc, en `~/decomp-herramientas/gcc/`.
- `scripts\decomp_configurar.sh`: crea `decomp\` con la configuracion de splat.

## Ejecutable identico desde el desensamblado

`decomp\slus_012.08.yaml` (splat, gp 0x80084754) y `decomp\symbol_addrs.txt` (las 1331 funciones que
conoce Ghidra, con los nombres de `notas\simbolos.tsv`). Pasos:

```
wsl -d Ubuntu-24.04 -- bash -lc "cd /mnt/c/Proyectos/SABRINA/decomp && . ~/decomp-herramientas/venv/bin/activate && python -m splat split slus_012.08.yaml"
wsl -d Ubuntu-24.04 -- bash /mnt/c/Proyectos/SABRINA/decomp/armar.sh
```

`armar.sh` ensambla, enlaza y compara: da IGUAL, SHA1 b6328aa3a5366577e59a9de1ce8dab67bd64d822, 448512
bytes, el mismo que el original.

## Con que compilador se hizo el juego

No con el GCC de Sony. En el codigo del juego el 12 % de las sumas y restas son add, addi y sub (2102
contra 15691 addu, addiu y subu); GCC nunca las genera, y en las bibliotecas de Sony son el 3.5 %
(`decomp\estilo_compilador.py`). Las sumas de enteros con signo usan add o addi y las de direcciones addu.
Ademas el marco de pila es otro: `FisicaObjeto` guarda ra abajo (marco 0xC0, ra en 0x38) y todos los
registros de corrido; `CdRead`, de Sony, lo guarda arriba (marco 0x28, ra en 0x24), como GCC. Con eso el
juego parece compilado con Metrowerks CodeWarrior for PlayStation, como Digimon World (decomp jype0/dw_decomp),
y enlazado con las bibliotecas normales de Sony. Una descompilacion byte a byte necesitaria ese compilador
(propietario, cc_mips.dll); no se bajo.

## Descompilacion funcional verificada

En lugar de igualar los bytes, cada funcion se reescribe en C y se demuestra que hace lo mismo:

- `scripts\capturar.py` y `scripts\capturar_todo.py`: con el emulador, la ruta `capturar` de
  `control.lua` guarda registros, RAM (2 MB) y scratchpad al entrar a una funcion, en
  `decomp\capturas\<funcion>\NN.*`. La ronda de capturar_todo (HUB y los niveles 3, 4, 7, 10 y 14) ejecuto
  459 de las 1037 funciones del juego.
- `scripts\capturar_mas.py`: segunda ronda, que suma capturas a las que ya hay (`inicio=` en control.lua) y
  las toma espaciadas (`geo=1`: las llamadas 1, 4, 16, 64...), en otros niveles y chocando contra paredes,
  cayendo, atacando y en los menus. Las primeras llamadas de una funcion casi siempre son la carga del
  nivel y se parecen entre si. Cada captura ocupa 2 MB, tope de 12 por funcion.
- `decomp\verificar.py src\X.c Funcion`: compila el C con el GCC moderno para MIPS I y lo enlaza en
  0x80400000 con los simbolos reales; en Unicorn corre la original y la version en C desde cada captura y
  compara v0, v1, la RAM entera (menos la pila local), el scratchpad y lo escrito en hardware. Ademas
  prueba variantes de los argumentos: primero, una por una, las constantes que compara la propia funcion en
  cada argumento (asi se toman las ramas de `if (i == -1)`, que al azar casi nunca salen), y despues
  valores al azar, potencias de dos, sumas y restas. Y variantes de la memoria: cambia uno a tres de los
  valores que la funcion lee antes de escribirlos (contadores, banderas, tablas), casi siempre de los que
  lee su propio codigo. Sin eso, una funcion sin argumentos solo se probaba con una situacion.

  Reglas que costaron un dia de falsos DISTINTO:
  - El C no puede definir los datos del juego (`s32 D_8007CA88 = 0;` seria una copia nueva, no la memoria
    del juego). El verificador lo rechaza.
  - Si el C declara la funcion void, v0 no se compara **si** ningun llamador lo lee al volver. Eso se mira
    en el ensamblador siguiendo los saltos y, cuando el valor sale tal cual de la funcion, a sus llamadores.
    Si solo se llega por punteros no se sabe: queda `IGUAL_V0` (todo igual menos v0).
  - No se comparan los 16 bytes de sp a sp+16: son de la funcion llamada para guardar a0-a3, y una llamada
    al final (compilada como salto) los usa para la siguiente.
  - Una funcion del juego que el C define conserva su nombre apuntando a la original, y la version en C
    queda como `c__Nombre`. Asi un puntero a funcion vale lo mismo que en el original.
  - Se compila con `-mno-check-zero-division`: el div del juego no revisa el cero y el de GCC pone un teq.
  - Los ganchos de lectura de Unicorn cambian la ejecucion en algunas funciones (`func_80044C40` salta a 0
    solo con ellos): el rastreo de lecturas va en una corrida aparte que no se compara.
- `decomp\mutantes.py src\X.c Funcion`: hace copias del C con un cambio chico (un numero mas uno, una
  comparacion al reves, && por ||, una linea borrada) y verifica cada una. Un mutante que pasa es una parte
  que las capturas no prueban. Ejemplo real: `func_8003AE84` da IGUAL pero sobreviven tres mutantes, porque
  en las capturas la consulta de colision nunca acierta.
- `decomp\aridad.py`: mira el ensamblador y escribe `include\prototipos.h` con cuantos argumentos recibe
  cada funcion (a0-a3 leidos antes de escribirse, recorriendo los caminos; una llamada lee los argumentos
  de la llamada) y si lo que devuelve lo usa alguien. Sin eso m2c se come argumentos: escribia
  `strncmp(12)` y `memset(D, 0)`.
- Probado con mutantes: `CeldaDePosicion` con 0x800001 en vez de 0x800000 pasa las 5 capturas reales
  pero falla en 13 de 294 variantes; la buena pasa las 294.
- Unicorn traduce 0x80xxxxxx a la direccion fisica 0x0xxxxxxx: hay que mapear y leer la memoria fisica.
  La primera version comparaba una copia que nadie escribia.
- Las instrucciones del GTE (cop2) no las emula Unicorn: las emula `decomp\gte.py`, que engancha cada
  direccion cop2 y hace la cuenta en Python. Estan las cinco ordenes que usa el juego (mvmva, op, rtps,
  rtpt y nclip), la division por la z con su tabla igual que el hardware (se aparta de la cuenta exacta
  como mucho en 2, que es lo que se aparta la consola) y el registro de banderas (control 31), que el
  juego lee con `cfc2 $31` para saber si un triangulo se le salio de la pantalla. Una orden que no este
  hecha para la corrida: dejarla pasar en silencio haria que las dos versiones se equivocaran igual y el
  verificador aprobaria sin mirar nada.
- Ojo con lo que el GTE deja demostrado: las dos versiones ven el mismo coprocesador, asi que un error en
  gte.py no rompe la comparacion, pero haria que los caminos que toma el codigo no sean los del juego de
  verdad. Por eso conviene mirar la cobertura de las funciones que dibujan.

- Las capturas tienen que venir de lugares distintos. `BitDeZona` paso todo con capturas del HUB, que no
  tiene zonas, y un mutante (zona 3 devuelve 5 en vez de 4) tambien paso: esa rama nunca corria. Con 4
  capturas mas en Stone 3 (8 zonas) y variantes con indices chicos, el mutante cae y la buena pasa 9 de 9
  capturas y 349 de 349 variantes. Antes de dar por buena una funcion con ramas, probar un mutante en una
  rama.

Escritas a mano, en `decomp\src\` (el C de m2c queda en `src\auto\` y no se toca):

- `WobjCode\recogibles.c` RecogibleNoTomado; `modelLoader\cuadricula.c` CeldaDePosicion;
  `SceneProcessing\zonas.c` BitDeZona.
- `loadtga\texturas.c` TexturaPorIndice (lista enlazada de texturas).
- `colision\suelo.c` func_8003AF48, func_800223E8 y func_8003AE84: consulta de suelo de 0x4C bytes
  (posicion, punto de contacto, normal) contra los triangulos de la celda de la cuadricula.
- `objetos\forma.c` las formas de colision de los objetos (tipos 1, 2 y 3; el radio se guarda al cuadrado).
- `sabrina\estados.c` func_80030E64 y func_8003019C: cambiar el estado de Sabrina es cambiar su funcion de
  cada paso, elegir la animacion de su tabla y poner velocidad 0x1000.
- `varios\azar.c` (numero al azar en punto fijo con una tabla), `varios\matematicas.c` (raiz cuadrada por
  Heron), `varios\bloques.c` (tamano redondeado a bloques), `varios\sonidos_reiniciar.c`, `audio\cd.c`.
- `geometria\vectores.c`, `geometria\angulos.c`, `geometria\arbol.c` y `geometria\camara.c`: lo que usa el
  coprocesador. `arbol.c` tiene el recorrido del arbol de piezas de un modelo en sus dos versiones, la que
  llama a func_80020294 y su gemela func_8001FD50, que lleva el dibujo de los triangulos adentro;
  `camara.c`, la matriz de la camara, que recibe tres vectores por valor.
- `objetos\particulas.c` func_8001F6C8: cada particula es un cuadrado suelto que siempre mira a la camara.
  Pasa IGUAL pero sus capturas solo recorren 40 de 221 instrucciones: no hay ninguna particula viva en
  ellas. Hace falta capturarla jugando donde salten chispas.
- `include\dibujo.h` (CuadroTex y TriTex, los POLY_FT4 y POLY_GT3 de Sony), `include\modelo.h` (Vertice,
  Triangulo de 28 bytes, Textura) y `include\nodo.h` (Matriz y Nodo; el campo 0x5E no era un orden, es
  cuantos triangulos tiene el dibujo).
- `include\objeto.h`: lo que se sabe del objeto del mundo (funcion de estado en +0, animacion en +0x1C,
  posicion en +0x24, tabla de animaciones en +0x64, forma de colision en +0xF4, vida en +0x118). Cada campo
  lleva una comprobacion en compilacion de que cae donde debe.

## Lote automatico

`decomp\auto.py`: para cada funcion con capturas, borrador con m2c en dos pasadas (la primera para que
infiera el ancho de cada dato, la segunda con esos tipos), con los prototipos de `aridad.py` y los datos
como extern; si falla, otra vez con --no-switches. Compila y verifica. Resultado en `decomp\progreso.tsv` y
borradores en `decomp\src\auto\`. Para m2c se usan copias del codigo y los datos donde las tablas de
saltos apuntan a etiquetas (splat las deja como numeros): `build\codigo_m2c.s` y `build\datos_m2c.s`.
Con `--solo A,B` se rehacen esas funciones y el resto de `progreso.tsv` queda como estaba.

Arreglos del lote que valian muchas funciones:
- Los datos que m2c define con su valor (`s32 D_8007CA88 = 0;`) se quitan y van como extern. Eran 245
  borradores compilando contra copias vacias en vez de la memoria del juego.
- La limpieza borraba toda linea `return funcion(...);` creyendo que era un prototipo inventado. Solo se
  borran fuera de una funcion.
- Una llamada al final (`j Funcion` y su hueco de retardo) se le pasa a m2c como `jal Funcion` + `jr $ra`:
  tal cual, m2c no ve lo que escribe el hueco y se come argumentos.
- Un parametro s8/u8/s16/u16 entra como s32 y se recorta al empezar la funcion: el juego lo recorta el
  mismo y GCC da por hecho que ya viene recortado.
- Las funciones que se usan como valor (punteros a funcion) se declaran sin prototipo; sin eso no compila.

Los borradores automaticos casi nunca salen iguales de una: m2c escribe aritmetica de punteros en bytes
sobre punteros tipados, declara estructuras que no existen, llama con menos argumentos. El trabajo es
revisar cada funcion con m2c como punto de partida y verificar.py como juez.

## Otras piezas

- `decomp\ver_funcion.sh Nombre`: el ensamblador original de una funcion.
- `decomp\m2c.sh Nombre`: borrador de m2c.
- `decomp\funciones_juego.py`: lista de funciones del juego sin las de Sony (`funciones_juego.tsv`).
- `scripts\modulos.py`: mapa de modulos (`notas\modulos.tsv`). El enlazador puso el motor en orden
  alfabetico: BasicTools, File, Font, GraphicTools, loadtga, modelLoader, Object, Particle,
  SceneProcessing, Screen, StratTools, TexAnima, WobjCode; despues btrigger, membank, trigger; Movie al
  final.
- Ghidra: `AplicarSimbolos.java` fija gp y pone los nombres de `notas\simbolos.tsv`; `FuncionesPorPunteros.java`
  crea las funciones a las que solo se llega por tablas (de 1193 a 1455); `ExportarTodo.java` exporta.
