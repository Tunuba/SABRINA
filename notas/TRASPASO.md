# Traspaso, para seguir en otro chat

**2026-09-24: el proyecto esta en `D:\proyectos personales\Sabrina decomp\SABRINA` (PC nueva) y WSL es la
distro `Ubuntu`.** Lo primero: `notas\RESPALDO.md` (respaldo automatico cada 15 min y como migrar a otra
PC sin perder nada) y la bitacora por fases en `notas\fases\` (la mas nueva manda sobre lo que diga
este archivo).

Estado al 2026-09-16. Leer primero este archivo, luego `README.md`, `notas\FORMATOS.md` y
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

## Panel en vivo (`panel_color\`), y el proximo paso pendiente

`python panel_color\panel_color.py` abre un menu con paneles para tocar la RAM del HUB en vivo:
textura de Sabrina (con export a disco), saltos/movimiento, vida/objetos, camara (bloqueo real de
rotacion, encontrado por `GPU::Vsync`, ver el resto de este parrafo) y modelos 3D (escala por eje,
con vista previa en Python, y "piso bajo Sabrina" que de verdad mueve la colision, no solo lo
visual). Tecnicas nuevas que valen para seguir: instalar codigo Lua largo en pedazos (el endpoint
`eval` corta ~250 caracteres), y que solo un gancho de `GPU::Vsync` le gana la carrera al juego
para sostener un valor que se reescribe solo (los puntos de interrupcion y `nextTick` no sirvieron).

**Ya comprobado (2026-09-19), no era un bug**: moviendo la camara (con el panel) a una posicion
"imposible" el piso se veia duplicado infinitas veces. La sospecha de entonces (que la formula de
celda del mundo, `fila = (~((z >> 16) + 0x80) & 0xFF) >> 2`, envuelve con `& 0xFF` y por eso siempre
encuentra una celda real) resulto ser cierta para Z pero NO explica esto: `columna` no tiene esa
mascara (`((x >> 16) + 0x80) >> 2`, se sale de 0-63 sin envolver si x es muy grande), y ademas la
camara no toca la posicion de Sabrina -son sistemas separados, celda_de solo se usa para colision-.
Se probo en vivo teletransportando a Sabrina lejos por X y por Z (y los dos juntos): en los tres
casos se cae y muere por caida, identico, sin importar que el eje "envuelva" o no -la prueba fina de
colision (¿el punto cae DENTRO de un triangulo real?) descarta igual en los tres casos-. El piso
duplicado de la camara es otra cosa: trabando los valores de camara 4, 5 o 6 (`panel_camara.py`) a
un numero grande se reproduce el mismo patron -es la malla real del piso (349 triangulos) vista
desde un angulo que la camara normal del juego nunca usa, mostrando de golpe varias repeticiones de
su textura (el sello circular), no geometria fantasma ni una celda mal calculada.

## Recolor del traje default: mod_rosa.py y mod_bruja.py (2026-09-19)

Dos pruebas de recoloreo del traje default de Sabrina (piernas, cadera/cintura, brazo/manos,
pelo-cabeza), cambiando las paletas de la VRAM. `mod_bruja.py` es la version mas nueva y corrige las
etiquetas de `mod_rosa.py` (lo que creia "cadera" era el borde de la cintura, y "brazo" las manos),
leyendo los nodos del `.INO` en vez de tantear la RAM en vivo. `mods\sabrina_rosa.ppf` y
`mods\sabrina_bruja.ppf` ya estan armados (`python mod_bruja.py disco`). `crear_estado_saltar.py`
rehace `estados\saltar.estado` si hace falta.

## Nivel fantasma: armar un `.INO` propio desde cero (2026-09-19)

Se puede: `scripts\ino_escribir.py` es el escritor inverso de `ino.py` (verificado con viaje de ida
y vuelta byte a byte contra H1W.INO real) y `scripts\nivel_fantasma.py` arma un HUB alternativo
-el piso reemplazado por una malla propia, todo lo que no sea Sabrina/su sombra/el skybox real
(SkyDome1) vaciado (engranajes, ropero, FashionDiva, iconos)- que se parcha en
`disco\sabrina_fantasma.cue` con `disco.parchar()` (mismo mecanismo que usan los mods de textura,
solo que reemplazando un archivo mas grande: el `.INO` se rellena con ceros hasta medir igual que el
original, que es lo unico que pide `parchar()`). Panel nuevo en `panel_color\panel_fantasma.py`
("Nivel fantasma" en el menu) que lo arma y arranca en una ventana aparte (puerto 8092, no toca la
sesion principal); usa una `queue.Queue` para pasar mensajes del hilo de fondo al principal -llamar
`self.after()` directo desde el hilo de fondo tira `RuntimeError: main thread is not in main loop`
en una prueba automatizada, aunque el `mainloop()` real de la app quizas lo tolere-.

**El hallazgo real: un triangulo puede ser demasiado grande para el motor de dibujo del juego.** La
primera version del piso (un cuadrado de 2 triangulos de 32000 unidades de lado) cargaba perfecto en
RAM (comprobado leyendo el nodo real en vivo: `visible=4`, `banderas` sin bloquear -ver
`decomp\src\geometria\arbol.c func_8001FD50`, compartido por un amigo junto con el resto de
`decompilacion\`, integrar esa carpeta al `decomp\` propio en algun momento) pero quedaba
invisible, igual que el skybox real (SkyDome1) sin tocar. Esa funcion tiene una rama para
"triangulo demasiado grande en pantalla" que lo manda a partir (`D_80068878`/`func_800598DC`, las 7
funciones GTE que quedan pendientes en la descompilacion, ver "Siguiente" mas abajo) en vez de
dibujarlo directo. La mediana real de un triangulo de piso del HUB mide ~571 unidades (maximo real
~6969); el cuadrado gigante tenia ~45000 de diagonal, 80 veces mas grande que cualquier cosa que el
juego dibuje normalmente. Con una grilla de triangulos del tamano real (mediana ~571, `SPACING=700`
en `nivel_fantasma.py`) el piso se dibuja bien. El skybox real sigue sin verse -mismo problema,
sospecha sin confirmar: sus triangulos tambien deben ser grandes por naturaleza; para tener un cielo
de verdad habria que subdividirlo en triangulos chicos, como se hizo con el piso.

Cadena completa (la paso el amigo, por Ghidra y el desensamblado, sin verificar jugando): carga
`BuclePrincipal` (0x80010030) -> `CargarINO` (0x80018670) -> `LeerModelosINO` (0x8001CE0C) ->
`LeerNodoModelo` (0x8001C7D4, recursiva para los hijos, es la que ya se conocia como FUN_8001c7d4).
Dibujo: `func_80021A30` llama a `func_8001FD50` una vez por cuadro para dos nodos, `DAT_8007C9F0` y
`DAT_8007C9F4` (creados por `FUN_8001E164`); `func_80021B4C` tambien lo llama, y `func_8001FD50` se
llama a si misma para los hijos. Sin confirmar todavia si esos dos nodos son especificamente
mundo+cielo o alguna otra cosa; tampoco hay una funcion de piso separada para dibujar -el piso solo
se consulta para colision, con `func_8003AF48`, `func_800223E8` y `func_8003AE84` (`suelo.c`)-.

Dos bugs mas encontrados jugandolo de verdad (no solo con capturas automaticas), ya arreglados: el
piso con las 2 caras (por si el problema era la orientacion, cuando todavia no se sabia que era el
tamano) hacia parpadear -dos triangulos identicos compitiendo por los mismos pixeles-, ahora una
sola cara; y las 4096 celdas de colision viendo TODOS los triangulos del piso (en vez de solo las
cercanas) iba lento -ahora cada triangulo se reparte en su celda real, con la posicion pasada a la
escala de Sabrina (coordenada del modelo * 256, `CeldaDePosicion` trabaja en esa escala, confirmado
con `decomp\src\colision\suelo.c`), y la inmensa mayoria de celdas quedan vacias como en un nivel de
verdad. **Sin probar todavia**: si el parpadeo/lentitud se sintieron mejor jugandolo de verdad (solo
se midio tiempo real headless, 300 cuadros en 5.02s contra 5.00s ideales, sin atraso).

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
  verificada con capturas reales, Unicorn y el coprocesador geometrico emulado. Ver
  `notas\DESCOMPILACION.md`.

## Donde quedo la descompilacion (2026-09-16, madrugada)

Termino el lote de `auto.py` con las capturas nuevas (`decomp\progreso.tsv`):

- **247 funciones verificadas: 44156 de los 293812 bytes de codigo del juego, el 15.0 %.** Son 204 del lote
  automatico y 43 escritas a mano (las de `decomp\src\` sin contar la carpeta auto).
- DISTINTO 72, NO_COMPILA 120, IGUAL_V0 22 (todo igual menos el registro de retorno, que no se puede
  probar porque a esa funcion solo se llega por punteros), GTE 7, M2C_FALLA 2.
- NO_TERMINA 35: la original se queda dando vueltas en el emulador esperando al hardware (el CD, el
  sonido). No se pueden verificar asi; habria que simular esos registros.
- SIN_CAPTURAS 530, eran 575: la ronda de `capturar_mas.py` le dio capturas a 45. **Sigue siendo el
  siguiente paso y lo que mas rinde**: `python scripts\capturar_mas.py` (menus, tarjeta de memoria,
  hechizos, jefes, otros niveles) y despues el lote otra vez.
- Lo verificado ya no es solo lo que pasa el verificador: `mutantes.py` mide si el verificador cazaria un
  error y `cobertura.py`, cuanto del codigo recorren las capturas. `func_8001BE8C` (los angulos) mata sus
  10 mutantes; `func_8003AE84` deja vivos 3, porque en sus capturas la consulta de colision nunca acierta.

## El coprocesador geometrico, ya de verdad (2026-09-16)

`gte.py` emulaba solo dos ordenes (mvmva y op) y las otras tres que usa el juego las dejaba pasar en
silencio. Eso es peor que fallar: las dos versiones se equivocan igual, la comparacion pasa y el
verificador aprueba sin haber probado nada. Ahora:

- Estan las cinco ordenes del juego (mvmva, op, rtps, rtpt, nclip), la division por la z con la tabla del
  hardware (se aparta de la cuenta exacta como mucho en 2, que es lo que se aparta la consola) y el
  registro de banderas (control 31), que el juego lee con `cfc2 $31` para saber si un triangulo se le
  salio de la pantalla. Una orden que no este hecha para la corrida en vez de seguir callada.
- El gancho ya no adelanta el contador: escribe un `nop` encima de la instruccion y deja que Unicorn lo
  ejecute. Adelantarlo se comia los saltos, porque GCC puede poner un `swc2` en el hueco de retardo de una
  llamada (en el juego no pasa; en el C que genera GCC, si).
- Las macros de `include\gte.h` que tocan memoria llevan `: "memory"`. Sin eso GCC adelanta las lecturas
  del C a antes de que el `swc2` escriba y lee basura. Si se toca `gte.h` o `gte.py`, volver a verificar
  todo lo que los usa: `wsl ... "cd /mnt/c/Proyectos/SABRINA/decomp && ./reverificar_gte.sh"`.
- Escritas a mano y verificadas: `geometria\camara.c` func_8001FA3C (arma la matriz de la camara; recibe
  tres vectores por valor, que es lo que deja los nueve enteros corridos en la pila),
  `objetos\particulas.c` func_8001F6C8 (el cuadrado que siempre mira a la camara) y, en
  `geometria\arbol.c`, func_8001FD50, el gemelo de func_800204F0 con el dibujo de los triangulos adentro.
- Tipos nuevos: `include\dibujo.h` (CuadroTex y TriTex, los POLY_FT4 y POLY_GT3 de Sony) y
  `include\modelo.h` (Vertice, Triangulo de 28 bytes, Textura). El campo 0x5E del nodo no era un orden:
  es cuantos triangulos tiene el dibujo.
- La tabla `D_80068878` son los que parten un triangulo que sale demasiado grande en pantalla; el indice
  sale de sumar 1, 4 y 7 segun cual de los tres lados se paso de largo (entradas 1, 4, 5, 7, 8, 11 y 12).
  Las 7 funciones que quedan marcadas GTE son justo esas y func_800598DC, el que parte en cuatro.
- Ojo con la cobertura: `func_8001F6C8` pasa IGUAL tocando 40 de 221 instrucciones, porque en sus capturas
  no hay ninguna particula viva; `func_8001FD50` toca 220 de 337 y `func_8001FA3C`, las 136. Para la
  primera: `python scripts\capturar_mas.py 3 1,5 --solo func_8001F6C8` jugando donde salten chispas.
- Los mutantes de `func_8001FD50` (12 de los 16, a los otros los mato Windows por memoria): 6 muertos y 6
  vivos. Siguen vivos quitar `gte_poner_matriz(&camara);` (en esas capturas la matriz de la camara ya
  estaba puesta de antes), quitar el `codigo |= 2` de la mezcla, el tope 0x400 de la z, un `<` por `<=`,
  un `>=` por `>` y el 7 del reparto de lados. Esa funcion pasa, pero sus capturas no fijan esos numeros;
  con capturas de otros niveles deberian caer.

## Como retomar la descompilacion

```
cd C:\Proyectos\SABRINA
wsl -d Ubuntu-24.04 -- bash -lc "cd /mnt/c/Proyectos/SABRINA/decomp && . ~/decomp-herramientas/venv/bin/activate && python3 auto.py --procesos 5"
```

Con 5 o 6 procesos, no mas: con mas, Windows se queda sin memoria y mata el lote (y tampoco conviene
correr nada en paralelo mientras, que tambien lo mata). Tarda cerca de una hora. **No basta con
desprenderlo**: `setsid nohup` no lo salva si la maquina virtual de WSL se apaga sola al quedarse sin
ninguna sesion, que es como murio en 575 de 995. Se lanza con un proceso oculto de Windows que la
sostenga:

```
Start-Process -WindowStyle Hidden wsl.exe -ArgumentList '-d','Ubuntu-24.04','--','bash','-lc',
  'cd /mnt/c/Proyectos/SABRINA/decomp && ./lanzar_lote.sh 5'
```

`lanzar_lote.sh` retoma con `--seguir` lo que ya haya en `build\hechas.txt`, va guardando cada 25 y deja
el avance en `build\auto_log2.txt`. Si algo se murio, mirar `uptime` dentro de WSL: si dice pocos minutos,
se reinicio la maquina virtual.

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
2. **Lo que mas rinde: mas capturas.** 530 funciones (casi la mitad del codigo) nunca se ejecutaron.
   Correr `python scripts\capturar_mas.py` en los niveles que faltan, que suma capturas espaciadas, y
   despues el lote otra vez. Tambien sirve para las que pasan con poca cobertura, como las particulas.
3. Armado "movible": reemplazar en `armar.sh` las funciones ya en C por su version compilada para tener un
   ejecutable jugable hecho desde C (hoy el C solo se verifica; el ejecutable se arma del ensamblador).
4. Las 7 funciones GTE que quedan son las que parten y recortan un triangulo demasiado grande: las de la
   tabla `D_80068878` (func_80057F34, func_800582CC, func_8005865C, func_800589EC, func_80058EE4,
   func_800593E0) y func_800598DC, que parte en cuatro. Se verifican igual que las otras; solo falta
   pasarlas a mano. Las seis hechas estan en `decomp\src\geometria\` y `decomp\src\objetos\`.
5. Pendientes del juego: parametros de objetos que no son enemigos, formato de la partida guardada
   (bloque de 0x13AC en 0x800C8518).
6. Integrar `decompilacion\` (lo que paso un amigo: `decomp\src\geometria`, `colision`, `objetos` y
   notas actualizadas) al `decomp\` propio -por ahora quedo aparte, sin mezclar-.
7. Nivel fantasma (ver mas arriba): probarlo jugado de verdad para confirmar que el parpadeo/lentitud
   se arreglaron; si se quiere el skybox real (SkyDome1) visible, subdividirlo en triangulos chicos
   como se hizo con el piso -sospecha sin confirmar todavia de que es el mismo problema del tamano-.
   Las 7 funciones GTE del punto 4 (el que parte triangulos grandes) son sospechosas de tener algun
   caso no contemplado para triangulos muy por fuera del rango que usa el juego real; si alguna vez
   se pasan a mano, ojo con probarlas con algo mucho mas grande que lo normal.
