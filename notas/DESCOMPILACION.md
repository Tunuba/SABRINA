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
- `decomp\verificar.py src\X.c Funcion`: compila el C con el GCC moderno para MIPS I y lo enlaza en
  0x80400000 con los simbolos reales; en Unicorn corre la original y la version en C desde cada captura y
  compara v0, v1, la RAM entera (menos la pila local), el scratchpad y lo escrito en hardware. Ademas
  prueba variantes de los argumentos: constantes de la propia funcion y sus vecinos, potencias de dos,
  sumas y restas de ellos y valores al azar.
- Probado con mutantes: `CeldaDePosicion` con 0x800001 en vez de 0x800000 pasa las 5 capturas reales
  pero falla en 13 de 294 variantes; la buena pasa las 294.
- Unicorn traduce 0x80xxxxxx a la direccion fisica 0x0xxxxxxx: hay que mapear y leer la memoria fisica.
  La primera version comparaba una copia que nadie escribia.
- Las instrucciones del GTE (cop2) no las emula Unicorn; esas funciones no se pueden verificar asi.

- Las capturas tienen que venir de lugares distintos. `BitDeZona` paso todo con capturas del HUB, que no
  tiene zonas, y un mutante (zona 3 devuelve 5 en vez de 4) tambien paso: esa rama nunca corria. Con 4
  capturas mas en Stone 3 (8 zonas) y variantes con indices chicos, el mutante cae y la buena pasa 9 de 9
  capturas y 349 de 349 variantes. Antes de dar por buena una funcion con ramas, probar un mutante en una
  rama.

Verificadas a mano: `RecogibleNoTomado` (`decomp\src\WobjCode\recogibles.c`), `CeldaDePosicion`
(`decomp\src\modelLoader\cuadricula.c`) y `BitDeZona` (`decomp\src\SceneProcessing\zonas.c`).

## Lote automatico

`decomp\auto.py`: para cada funcion con capturas, borrador con m2c en dos pasadas (la primera para que
infiera el ancho de cada dato, la segunda con esos tipos), sin prototipos inventados y con los datos como
extern; si falla, otra vez con --no-switches. Compila y verifica. Resultado en `decomp\progreso.tsv` y
borradores en `decomp\src\auto\`. Para m2c se usan copias del codigo y los datos donde las tablas de
saltos apuntan a etiquetas (splat las deja como numeros): `build\codigo_m2c.s` y `build\datos_m2c.s`.

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
