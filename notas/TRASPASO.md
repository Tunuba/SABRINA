# Traspaso, para seguir en otro chat

Estado al 2026-09-15. Leer primero este archivo, luego `README.md`, `notas\FORMATOS.md` y
`notas\DESCOMPILACION.md`.

## Donde esta cada cosa

- Proyecto: `C:\Proyectos\SABRINA`, repositorio publico github.com/Tunuba/SABRINA (rama main). En el
  repositorio solo van scripts, notas y parches; nada del juego (ver `.gitignore`).
- Juego: `disco\` (imagen Redump USA, pista 1 SHA1 7EA984FB4292E2E96C58EB436EC60539D56F490A) y
  `extraido\` (archivos del disco, `sabrina.xml` con el sector de cada uno).
- Herramientas: `herramientas\` (PCSX-Redux, Ghidra 12.1.3, JDK 21, mkpsxiso, jPSXdec, Nugget) y, en WSL
  `Ubuntu-24.04`, `~/decomp-herramientas` (splat, m2c, maspsx, asm-differ, unicorn, GCC viejos). Todo se
  reinstala con `.\arrancar.ps1 -Taller` y los `scripts\decomp_*.sh`.
- Estados del emulador en `estados\`: `titulo`, `saltar` (HUB jugando), `nivel_S3`, `final_hub`.
- Ghidra: proyecto en `ghidra\`, exportado a `notas\ghidra\` (funciones.tsv, textos.tsv, decompilado.c).

## Jugar

Doble clic en `Sabrina.lnk` (escritorio o raiz) o `ARRANCAR.bat`. Disco con mods:
`disco\sabrina_todo.cue` (espanol, invencible, pantalon azul). Parche `mods\sabrina_todo.ppf`.

## Lo hecho

- Mods: pantalla de carga y 62 textos en espanol, invencibilidad (5 instrucciones), pantalon azul.
- Formatos descifrados, todos comprobados contra el juego: .PIC, .TEX, .INO completo (cuadricula de
  colision, zonas, sprites, texturas, modelos, letra, particulas; triangulo de 28 bytes entero),
  .ANI (229 animaciones con nombre), WRLDDATA (objetos, tipos, rutas de patrulla, parametros de
  enemigos), VAB a WAV, STR a AVI. Selector de niveles y posicion de Sabrina.
- Exportadores: modelos a OBJ con texturas (`ino_obj.py`), niveles completos (`nivel_completo.py`), GIF de
  cualquier animacion (`animar.py`), sprites (`sprites.py`), letra (`letra.py`), sonidos (`vab.py`).
- Descompilacion: ejecutable reconstruido identico desde el desensamblado de splat; el juego se compilo
  con CodeWarrior (no hay compilador para igualar bytes), asi que se hace descompilacion funcional
  verificada con capturas reales y Unicorn. Ver `notas\DESCOMPILACION.md`.

## Donde quedo la descompilacion (2026-09-15)

Lote de `auto.py` sobre las 1033 funciones del juego (ver `decomp\progreso.tsv`):

- IGUAL 130 automaticas mas 3 a mano (RecogibleNoTomado, CeldaDePosicion, BitDeZona): 133 funciones,
  unos 20.5 KB de los 293 KB de codigo del juego (7 %).
- DISTINTO 236, NO_COMPILA 72, GTE 13 (Unicorn no emula el coprocesador geometrico), M2C_FALLA 2,
  ERROR 3, SIN_CAPTURAS 577 (no se ejecutaron en la ronda de cobertura).
- Ojo con las IGUAL automaticas: pasaron con las capturas que hay. Una rama que ninguna captura recorre no
  queda probada (le paso a BitDeZona con capturas solo del HUB). Para las importantes, capturar en otro
  nivel y probar un mutante en una rama.

## Como retomar la descompilacion

```
cd C:\Proyectos\SABRINA
wsl -d Ubuntu-24.04 -- bash -lc "cd /mnt/c/Proyectos/SABRINA/decomp && . ~/decomp-herramientas/venv/bin/activate && python3 auto.py --procesos 6"
```

Con 6 procesos, no mas: con mas, Windows se queda sin memoria y mata el lote. Tarda un par de horas.
Deja `decomp\progreso.tsv`. Para una funcion: `bash decomp/ver_funcion.sh Nombre` (ensamblador),
borrador en `decomp\src\auto\Nombre.c`, se corrige a mano y se pasa a `decomp\src\<modulo>\*.c`, y
`python3 verificar.py src/<modulo>/archivo.c Nombre` hasta IGUAL. auto.py no toca las que ya estan a mano
y con `--solo A,B` rehace solo esas, dejando el resto de progreso.tsv como estaba.
Para funciones sin capturas: `python scripts\capturar.py <estado> "<pasos>" Nombre:3` (con `ir:N` para
cargar un nivel antes) o `python scripts\capturar_mas.py` para una ronda entera.

Antes de creerle a un IGUAL:

```
python3 mutantes.py src/<modulo>/archivo.c Funcion     # mete errores a proposito; deben morir todos
python3 cobertura.py --solo Funcion                    # cuanto del codigo recorren las capturas
```

Si `aridad.py` o los tipos cambian, `python3 aridad.py` rehace `include\prototipos.h` para m2c.

## Siguiente

1. Pasar a mano las funciones de `progreso.tsv` que salieron DISTINTO o NO_COMPILA, empezando por las
   chicas; anotar los tipos que se van entendiendo (estructura del objeto, de la camara, del jugador) en
   `decomp\include\juego.h` para que m2c los use.
2. Mas cobertura: menus, tarjeta de memoria, hechizos, jefes, el HUB con dialogos (capturar_todo solo
   ejecuto 459 de 1037 funciones).
3. Armado "movible": reemplazar en `armar.sh` las funciones ya en C por su version compilada para tener un
   ejecutable jugable hecho desde C (hoy el C solo se verifica; el ejecutable se arma del ensamblador).
4. Las 13 funciones GTE (11.8 KB, el 4 % del codigo) no se pueden verificar porque Unicorn no emula el
   coprocesador geometrico. Idea: interceptar las instrucciones cop2 en Unicorn y emularlas en Python. No
   hace falta que el GTE sea perfecto para comparar: si las dos versiones ven el mismo GTE, la comparacion
   sigue valiendo; lo unico que cambia es que los caminos que tomen sean los de verdad.
5. Pendientes del juego: parametros de objetos que no son enemigos, formato de la partida guardada
   (bloque de 0x13AC en 0x800C8518).
