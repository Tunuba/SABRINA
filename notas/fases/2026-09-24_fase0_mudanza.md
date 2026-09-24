# Fase 0 (2026-09-24): mudanza a la PC nueva y puesta en marcha

PC nueva: Ryzen 7 4800H (16 hilos), 39 GB de RAM. El proyecto paso de `C:\Proyectos\SABRINA` a
`D:\proyectos personales\Sabrina decomp\SABRINA`.

## Que llego y que se perdio

- Llegaron el repositorio (scripts, notas, `progreso.tsv` del 2026-09-16), el juego y las herramientas de Windows.
- **No llegaron** las carpetas que ignora git: `decomp\asm`, `build`, `capturas` y `src`. `asm` se
  regenero. De `src` se recuperaron 20 funciones de la copia del amigo (`decompilacion\decomp\src`,
  identica al repo salvo los finales de linea). **Se perdieron 23 funciones escritas a mano**, que se rehacen
  en la fase 1. Por esto existe ahora el respaldo automatico: ver `notas\RESPALDO.md`.

## Instalado

- WSL: la distro se llama `Ubuntu` (24.04), no `Ubuntu-24.04`; se corrigieron los scripts. apt daba 403 con
  `http://archive.ubuntu.com`, asi que se usa `https://mirrors.edge.kernel.org/ubuntu`.
- `~/decomp-herramientas`: splat 0.50, m2c, asm-differ, maspsx, unicorn 2.1.4 y los GCC 2.6.3-2.95.2.
- El ejecutable rearmado desde splat da **IGUAL** (SHA1 b6328aa3...). El verificador da IGUAL en
  func_8001BE8C y func_8001FA3C.
- Todo esto en un paso para la proxima vez: `scripts\decomp_todo.sh`.

## Arreglos

- `emu.py`: el emulador sin ventana arranca **sin sonido** (`PCSX.settings.spu.Mute`). No cambia la
  configuracion del juego normal.
- **PCSX-Redux acepta ~896 puntos de interrupcion por sesion**: la primera ronda dejo 141 funciones sin
  captura, en silencio. `capturar_todo.py` y `capturar_mas.py` tienen ahora `--parte i/k --puerto P` para
  repartir las funciones entre varios emuladores a la vez, y avisan si alguna no se pudo poner.
- `lanzar_lote.sh` y `reverificar_gte.sh` usan rutas relativas.
- `scripts\vigilar_ram.sh` + `scripts\verificadores.sh`: con la RAM > 92 % detiene el verificador mas nuevo;
  con la CPU > 95 % por 30 s lo **pausa** (SIGSTOP) y lo reanuda cuando la CPU baja de 85 %. Solo toca
  procesos de Sabrina.

## Capturas

- Ronda 1 (HUB, 3, 4, 7, 10, 14): 457 funciones ejecutadas de 1037.
- Ronda 2 (0, 1, 2, 5, 6, 8, 9, 11, 12; 4 emuladores) y ronda 3 (3, 4, 7, 10, 13, 14 con el recorrido de
  capturar_mas; 8 emuladores): en curso, ver `notas\logs\ronda*.txt`.

## Trabajo lanzado (workflows de agentes)

- Fase 1: rehacer las 23 funciones a mano perdidas (8 grupos, cada uno con un auditor).
- Fase 2: las 7 funciones GTE que parten triangulos grandes (`src\geometria\partir_*.c`).
- Fase 3: ~100 funciones chicas DISTINTO/NO_COMPILA con capturas (13 grupos, archivos `*_gNN.c`).

Los resultados de cada fase quedan en `notas\fases\`.
