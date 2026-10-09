# Editor de niveles de Sabrina

Un editor para armar tus propios mapas de *Sabrina the Teenage Witch: A Twitch in Time!* (PS1) y jugarlos de
verdad en el emulador: suelos, paredes con las que se choca, rampas, techos, texturas del juego y cielo propio.
Dibujas en una vista desde arriba, ves el resultado en 3D en la misma ventana y con un boton arma el disco y
abre el juego con tu mapa.

El mapa de ejemplo es `niveles\castillo.json`: un patio amurallado con estanque, una puerta, un camino, una
fortaleza con salon de columnas y habitaciones, y una muralla con rampas hasta una torre.

El segundo mapa es `niveles\greendale.json`: **Greendale entero, el pueblo de Sabrina, bajo una niebla cerrada al
estilo Silent Hill**. Sabrina aparece en el jardin de la casa Spellman (la funeraria, con su torreon y su porche) y
detras esta el cementerio con la cripta. Main Street tiene faroles, la libreria Cerberus, el diner del doctor
Cerberus, el cine Paramount con su marquesina, la farmacia y el ayuntamiento con la torre del reloj; enfrente,
Baxter High con su portico de columnas y su asta. La calle Kinkle cruza el pueblo hacia la Academia de Artes
Ocultas (dos torres) y la Iglesia de la Noche, cuyo campanario se sube por diez peldanos que flotan alrededor de
la torre hasta la campana dorada: esa es la meta. Al sur esta el bosque de Greendale con arboles muertos, el rio
Sweetwater (se cae y se sale saltando) con su puente de tablones y, al otro lado, la boca oxidada de las minas
Kinkle contra la colina. Lo genera `scripts\mapa_greendale.py` (91 bloques, el 97 % del espacio).

> Solo es **arquitectura y cielo**: no hay enemigos, gemas ni objetos. Cada mapa reemplaza el nivel del HUB
> (`H1W.INO`) dentro de una copia del disco; tu disco original no se toca.

## Que necesitas

- Windows 10 u 11 (usa PowerShell y el emulador PCSX-Redux para Windows).
- **Tu propia copia del juego**, version USA (SLUS-01208) en formato Redump: un `.cue` con 97 pistas `.bin`, o
  el `.7z` que las trae. El juego no viene en este repositorio.
- Internet la primera vez (se baja Python si no lo tienes, el emulador y una herramienta de 3 MB).

## Instalar (una sola vez)

1. Descarga o clona este repositorio.
2. Deja tu copia del juego en la carpeta `disco\` (el `.7z`, o el `.cue` con sus `.bin`), o en tu carpeta
   de Descargas.
3. En PowerShell, dentro de esta carpeta:

   ```
   .\arrancar.ps1 -Editor -SoloInstalar
   ```

   Instala Python (si falta) con Pillow y NumPy, baja el emulador PCSX-Redux (con OpenBIOS, no hace falta la
   BIOS de Sony), comprueba tu copia del juego y saca sus archivos a `extraido\`. Tarda unos minutos. Se puede
   repetir sin problema: lo que ya esta hecho no se repite. (`-Taller` en vez de `-Editor` instala ademas Java y
   Ghidra, unos 800 MB, solo para investigar el juego.)

Si algo falla, el propio script dice que hacer. Los discos que se generan (`disco\sabrina_*.cue`) y
`extraido\` no van al repositorio.

## Jugar y editar: los atajos (doble clic)

| Archivo | Que hace |
|---|---|
| `EDITOR_NIVEL.bat` | Abre el editor (con `niveles\plataformas.json`). Puedes pasarle otro: `EDITOR_NIVEL.bat niveles\castillo.json` |
| `MAPA_CASTILLO.bat` | Abre el juego directamente en el mapa del castillo |
| `MAPA_CASTILLO_CAMARA_LIBRE.bat` | Lo mismo, con la camara libre (SELECT la prende y la apaga) |
| `MAPA_GREENDALE.bat` | Abre el juego en Greendale, el pueblo de Sabrina bajo la niebla |
| `MAPA_GREENDALE_CAMARA_LIBRE.bat` | Greendale con la camara libre |
| `NIVEL_PLATAFORMAS.bat` | Un nivel de saltos entre plataformas |
| `CAMARA_LIBRE.bat` | El juego normal con la camara libre |
| `ARRANCAR.bat` | El juego con los mods de siempre (menus en espanol, etc.) |

El juego tarda unos **40 segundos** en pasar la intro y quedar listo para jugar (lo hace solo). La ventana del
emulador **tiene que estar visible**: si la minimizas mientras arranca, no responde. Se cierra cerrando su ventana.

Teclado en el emulador: flechas para moverse, X = X, D = circulo, Z = cuadrado, S = triangulo, Enter = START.
Un mando tambien sirve.

### Camara libre

SELECT la prende y la apaga. Prendida, el mando no mueve a Sabrina y la camara vuela: flechas arriba/abajo
avanzan y retroceden, izquierda/derecha giran, triangulo/equis miran arriba/abajo, L2/R2 van de lado, L1/R1
suben y bajan, y cuadrado la hace 4 veces mas rapida. Sirve para ver cualquier rincon del mapa. El parche es
`mods\camara_libre.ppf` (solo cambia 12 KB del ejecutable): el disco con camara se arma solo la primera vez que
hace falta.

## El editor

Abre `EDITOR_NIVEL.bat`. Arriba, la **vista desde arriba**; abajo, la **vista 3D** con el cielo del nivel de
fondo; a la derecha, el panel.

**Vista desde arriba** (derecha = +X, abajo = +Z; en el juego "arriba" avanza hacia abajo-derecha):

| Accion | Efecto |
|---|---|
| Arrastrar en vacio | Crea un bloque del tipo elegido en "Al crear" (se ajusta a una rejilla de 128) |
| **Mayus + arrastrar** | Lo mismo pero encima de otro bloque (paredes sobre un suelo, rampas sobre un piso...) |
| Clic / arrastrar un bloque | Lo selecciona / lo mueve |
| Arrastrar una esquina | Cambia su tamano |
| Ctrl + clic | Elige el bloque de debajo cuando hay varios apilados |
| Rueda / boton derecho o central | Zoom / desplazar la vista |
| Supr, Ctrl+D, Ctrl+S, flechas | Borrar, duplicar, guardar, mover 128 |

**Vista 3D:** arrastrar gira, la rueda hace zoom, doble clic la reinicia, clic selecciona un bloque. Los colores
salen de la textura de cada bloque por su color.

**Tipos de bloque** (radio "Al crear"): *Plataforma* (plana, a la altura del seleccionado), *Pared* (alta y
maciza, para salas y pasillos) y *Rampa* (sube 256).

**Campos de cada bloque:**

- X/Z desde-hasta: el rectangulo. Altura: de la tapa (positiva = arriba). **Grosor**: cuanto baja desde la
  tapa (vacio = automatico). Cuando un muro se apoya en un suelo, su grosor tiene que llegar hasta el.
- **Rampa**: altura final y eje (`x` o `z`) a lo largo del cual sube. No puede pasar de ~35 grados o Sabrina resbala.
- **Cuadro tapa / lados**: tamano de los triangulos (256 o 512). Mas pequeno = mas detalle de textura y menos
  distorsion, pero mas triangulos (ver "Limites").
- **Con techo**: el bloque tambien tiene cara inferior (para salas cubiertas). **Es pared**: no da aviso de
  "no se alcanza".
- **Color** (128 = el color de la textura tal cual) y **textura de tapa y de lado**: un clic abre una galeria
  con 33 texturas del juego (piedra, marmol, ladrillo, tejas, tablones, madera, motivos egipcios...).
- **Cielo**: tres colores (cenit, horizonte, nadir) en degradado.

**Botones:** *Probar en el juego* (valida, arma el disco, cierra el juego anterior y abre el nuevo; la casilla
"con camara libre" lo abre con SELECT), *Ir a la seleccionada* (teletransporta a Sabrina al bloque en el juego
abierto), *Cerrar el juego*, *Medir el tamano del nivel* y Guardar/Abrir.

El panel de estado avisa en vivo: **errores** (no se puede probar, por ejemplo dos bloques que se pisan a la misma
altura o la salida sin suelo) y **avisos** (un bloque que no se alcanza saltando; los bordes rojos en el editor).

La **salida** (cruz amarilla) esta fija en (128, -896): ahi aparece Sabrina y reaparece si se cae. Tiene que haber
un bloque plano a altura 0 debajo de ella.

## Los niveles: formato

Cada nivel es un JSON en `niveles\` (un bloque por linea):

```json
{"cielo": {"cenit": [50,60,150], "horizonte": [255,200,140], "nadir": [40,50,110]},
 "plataformas": [
  {"nombre": "patio", "x0": -2048, "z0": -3072, "x1": 512, "z1": 1024, "h": 0, "color": [190,180,170],
   "tex_tapa": 67, "tex_lado": 1, "prof": 600, "paso": 512},
  {"nombre": "muro", "x0": 6400, "z0": -3072, "x1": 6656, "z1": -512, "h": -1000, "color": [215,205,195],
   "tex_tapa": 16, "tex_lado": 88, "prof": 1000, "pared": true, "paso_lado": 384}
]}
```

`h` es la altura de la tapa con **-Y hacia arriba** (un muro de 1000 de alto sobre el suelo tiene `h: -1000`).
Opcionales: `prof`, `tex_tapa`, `tex_lado`, `h2` + `eje` (rampa), `techo`, `paso`, `paso_lado`, `pared`.
`scripts\mapa_castillo.py` genera el castillo con funciones de ayuda (`suelo`, `muro`, `rampa`): es un buen punto
de partida para hacer mapas por codigo. `scripts\mapa_greendale.py` genera el pueblo con otras (`edificio`,
`tejado`, `escalon`, `arbol`, `farol`) y al final dice cuanto ocupa del .INO. Tambien por linea de comandos:

```
python scripts\nivel_plataformas.py disco niveles\castillo.json     arma el disco
python scripts\nivel_plataformas.py ver niveles\castillo.json       comprueba en el juego que cada bloque se pisa a su altura
python scripts\jugar.py nivel niveles\castillo.json [--libre]       lo abre para jugar
```

## Limites (lo que conviene saber)

- **Tamano fijo.** El `H1W.INO` del disco no puede crecer (313.628 bytes): caben unos **3.800 triangulos**. El
  castillo usa el 98%. "Medir el tamano" dice cuanto llevas; si no cabe, usa cuadros mas grandes (512), menos
  bloques o menos techos.
- **Maximo ~2000 triangulos dibujados por cuadro** (el motor del juego) y los que miran de espaldas se descartan.
- **Sin enemigos, gemas, puertas ni objetos**: se quitan todos los del HUB. Solo geometria.
- **Dos bloques en el mismo cuadro de planta** (uno sobre otro) valen si sus tapas difieren al menos 64; con
  menos de ~370 de separacion y sin pared entre los dos, Sabrina "sube sola" al de arriba (como un escalon). Con mas
  de ~380 se pisan los dos, y se sube de uno a otro saltando hasta unos 700 de separacion.
- **El salto de Sabrina**: ~380 de alto y, a toda carrera, ~400 de largo (de casi parada, solo ~50-150). Los
  avisos de "no se alcanza" usan huecos de 256 y subidas de 250.
- Cuadros de pared grandes y cercanos a la camara se ven algo deformados (es asi en todo el juego, la PS1 no corrige la
  perspectiva de las texturas).

## Si algo no va

- **"el emulador no respondio en 30 s"**: la ventana del emulador debe estar visible (no minimizada), y el puerto
  no debe estar ocupado por otro programa. Cierra emuladores viejos y reintenta.
- **"No cabe" / "se paso del tamano original"**: ver Limites; el mensaje dice cuantos bytes sobran.
- **Falta `extraido\...` o `sabrina.xml`**: corre de nuevo `.\arrancar.ps1 -Editor -SoloInstalar`.
- **La primera prueba se cuelga o tarda**: espera los ~40 s; si el juego se queda en negro, cierra y vuelve a probar
  (arma el disco de cero cada vez).
- **Mensaje de Windows al abrir un `.bat`**: es la proteccion normal de SmartScreen; "mas informacion > ejecutar".

## Como funciona (para curiosos)

El editor no toca el ejecutable del juego: reescribe el archivo del nivel del HUB (`GRAPHICS\HUB\H1W.INO`) con tu
geometria y lo parcha dentro de una copia de la pista de datos del disco (recalculando sus sumas de control).
Lo que se descubrio por el camino, en resumen:

- Cada triangulo del `.INO` lleva su textura (una de 139 "ventanas" del archivo de texturas), seis UV, y una
  cola con tipo, normal (en bytes, x126) y ejes de prueba. El suelo ignora los triangulos de normal horizontal;
  el choque de lado los usa de frente.
- El mundo se **dibuja y choca por celdas** de 1024: el rango de cada celda (primer triangulo, cuantos) manda el
  dibujo (un triangulo fuera de todo rango no se dibuja nunca), y la lista de colision de cada celda manda el
  choque. La colision lee la fila "derecha" y los rangos la "invertida". Las paredes van en todas las celdas
  cercanas porque el choque de lado solo mira la celda donde empieza el segmento.
- El juego elige como suelo el triangulo **mas cercano por debajo de un punto ~360 sobre los pies** de Sabrina.
- El cielo del HUB (un tunel de engranajes) se sustituye por una esfera propia con degradado de color por vertice.
- Documentacion tecnica del resto del proyecto: `notas\FORMATOS.md`, `notas\DESCOMPILACION.md`, `README.md`.
