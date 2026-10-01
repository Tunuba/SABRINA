# Como retomar (actualizado 2026-09-24, antes de apagar la PC)

Todo lo escrito esta en `decomp\src` (y en GitHub).

**Hay dos PCs.** La del amigo: `D:\proyectos personales\Sabrina decomp\SABRINA`, distro WSL `Ubuntu`. La de Meme:
`C:\Proyectos\SABRINA`, distro `Ubuntu-24.04`. Los `.sh` de `scripts\` detectan solos la distro y la ruta
(`scripts\wsl.sh`); en los comandos de abajo cambia `-d Ubuntu` y la ruta `/mnt/d/...` por los de tu PC
(en la de Meme: `-d Ubuntu-24.04` y `/mnt/c/Proyectos/SABRINA`). Probado en la de Meme el 2026-09-24:
`decomp_todo.sh` da IGUAL y `verificar.py` da IGUAL en func_8001BE8C y func_8001FA3C.

Lo que estaba corriendo se paro a proposito y se retoma asi:

1. **Lote automatico** (m2c + verificador sobre todas las funciones con capturas). Retoma donde quedo
   (`decomp\build\hechas.txt`, 623 de ~1000 al pararlo). Desde PowerShell:
   ```
   Start-Process -WindowStyle Hidden wsl.exe -ArgumentList '-d','Ubuntu','--','bash','-lc','"cd ''/mnt/d/proyectos personales/Sabrina decomp/SABRINA/decomp'' && ./lanzar_lote.sh 6"'
   ```
   Avance en `decomp\build\auto_log2.txt`; resultado en `decomp\progreso.tsv`.

2. **Auditoria del C a mano**: `python3 auditar.py --procesos 12` (en WSL, carpeta decomp). Resultado por
   funcion en `notas\fases\auditoria.tsv`; el porcentaje total al final de `notas\logs\auditoria.txt`.
   **Lo que manda es auditoria.tsv**: una funcion escrita a mano solo cuenta si ahi dice IGUAL o IGUAL_V0.

3. **Los tres workflows de agentes** (se pararon a medias; el C que alcanzaron a escribir quedo en disco):
   - 23 funciones perdidas en la mudanza, run `wf_284f6b64-abc`
   - 7 funciones GTE que parten triangulos, run `wf_7ab69402-535` (`src\geometria\partir_*.c`)
   - oleada de ~100 funciones chicas, run `wf_cdde7b44-8fa` (archivos `*_gNN.c`)

   Para seguirlos no hace falta relanzarlos tal cual: mejor partir de `auditoria.tsv` y mandar agentes solo a
   las que quedaron DISTINTO / NO_COMPILA / TOPE_DE_TIEMPO.

4. **Si algo queda colgado en WSL**: `wsl -d Ubuntu -- bash "/mnt/d/proyectos personales/Sabrina decomp/SABRINA/scripts/parar_wsl.sh"`
   cierra el lote, los verificadores y los bucles que dejan los agentes (solo lo de Sabrina).

5. **Vigilante de RAM y CPU**: `bash scripts/vigilar_ram.sh 92 95` desde Git Bash (una sola copia; si ya hay
   una, sale sola). Pausa verificadores si la CPU pasa de 95 % y detiene uno si la RAM pasa de 92 %.

## Nivel fantasma (pendiente de probar jugando)

`scripts\nivel_fantasma.py` tenia dos fallos, ya arreglados en el script:
- **La traba**: cada una de las 4096 celdas declaraba el piso entero como suyo. Medido con
  `scripts\medir_fps.py`: **4.3 cuadros por segundo contra 31 del HUB original**. Ahora cada celda declara
  solo sus triangulos, igual que el HUB real.
- **La colision**: se leia la `y` del vertice en vez de la `z`, asi que todo el piso caia en una sola fila de
  la cuadricula. Ahora ocupa sus 100 celdas reales.
- **Nuevo: un cubo** (`CUBO` en el script: 1400 de lado, 700 de alto, en x = z = 2100), con la tapa y las 4
  paredes partidas en triangulos de tamano normal. Sin probar todavia: si se ve, si Sabrina se sube encima
  y si las paredes la frenan.

Para probarlo: `python scripts\nivel_fantasma.py disco` y despues `python scripts\medir_fps.py disco\sabrina_fantasma.cue`
(~5 min; tiene que dar cerca de 30 por segundo). Para jugarlo: `python scripts\nivel_fantasma.py probar`.

## 2026-09-30, PC de Meme: DISTINTO y NO_COMPILA a mano

Una sesion sola, sin agentes, con el lote `auto.py --procesos 3 --seguir` corriendo de fondo (no se toco).
`auditar.py` no tiene `--solo`, asi que no se corrio entero: cada funcion se verifico con `verificar.py` y
se anoto a mano en `notas/fases/auditoria.tsv`, como en la fase 4.

**A IGUAL (26, con Liberar)**: func_8003A46C (era la DISTINTO de la fase 4), ArchivoIniciar, func_80047710,
func_800425C8, TocarSonido, func_80042B78, func_8003A524, func_80037278, func_8002506C, func_8002EDC8,
func_8001E588, MatrizDesdeAngulos, func_80020818, func_80011930, func_8004F2D8, func_8004C82C,
func_80023B3C, RegistrarRecogible, func_8004BDA0, func_8001C45C, func_8002303C, func_80014670,
func_80014774, LeerMAO, PuntoEnTriangulo, Liberar. **A IGUAL_V0 (1)**: func_80037468 (v0 al salir antes es la
direccion de la tabla de saltos). Archivos nuevos `*_g13.c` en audio, colision, Screen, WobjCode, varios,
libgpu y psyq.

Trampas que aparecieron (sirven para las que faltan):
- **p[3] de PuntoEnTriangulo**: si el byte de ejes del triangulo vale 3 lee un cuarto valor del punto, que
  en el original es lo que sigue en la pila del llamador. func_8003A46C lo resuelve con
  `__builtin_dwarf_cfa()`; func_8003A524 poniendo normal, punto y vertice en un solo arreglo de 9.
- **Argumentos chicos**: con `s16`/`s8` en el prototipo GCC supone que vienen recortados y el original no
  (func_800425C8). Declararlos s32 y recortar donde el original recorta. Lo mismo con lo que devuelve una
  funcion real (SpuGetKeyStatus: declararla s32 y hacer `(s16)`).
- **Resta de punteros**: GCC divide "exacto" (por inverso multiplicativo); con un puntero parchado da otra
  cosa. Hacer la resta en bytes y dividir con signo (LeerMAO).
- **Direccion de una funcion propia**: si el C guarda `&func` y func esta en el mismo archivo, queda la
  direccion del C (0x804xxxxx). func_80014774 va en su propio archivo para que func_80014670 sea la real.
- Varias "void" pasan de IGUAL_V0 a IGUAL devolviendo lo que deja el original en v0 (func_8004F2D8,
  RegistrarRecogible).

**Escritas pero DISTINTO por variantes absurdas** (anotadas en auditoria.tsv con el motivo):
func_80023FD4 (con 0xAF43 casillas la tabla de sprites se lee hasta la pila de la propia funcion) y
func_800447E4 (una variante salta a un puntero de funcion al azar). **Liberar** (`src/varios/reservar_g13.c`) quedo IGUAL;
**Reservar** DISTINTO solo cuando D_8007C8E0 no es 0: llama a malloc de la BIOS (A0 0x33), que en el
emulador vuelve sin tocar v0, asi que el resultado es lo que hubiera en v0 (en el original, D_8007C8E0).
No es un error del C. Su verificacion tarda unas 2 horas.

**No intentadas**: DanoPorSuelo (1864 bytes, switch que m2c no lee) y las que leen el CD
(func_8002FF1C, func_80017D80, func_8002CF28: van a dar NO_TERMINA).

Mutantes: func_8003A46C 6/8 (los 2 vivos en comentarios), TocarSonido 6/8 (SpuGetKeyStatus no cambia en el
emulador), func_8002506C 7/8, func_8001C45C 4/8 (la rama de vectores muy grandes casi no se prueba),
PuntoEnTriangulo 8/8.

Lote de fondo al cerrar: 300 de 886 (empezo 19:07), sigue corriendo.
