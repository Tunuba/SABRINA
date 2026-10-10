/* Generado por scripts/mapa_kart.py: no editar a mano. La pista de SABRINA KART (niveles/kart.json). */
/* Puntos de control en el orden de la carrera (el 0 es la meta): x0, z0, x1, z1, x y z donde se
 * reaparece, y el rumbo del kart ahi. Turbos y cintas de hechizo: x0, z0, x1, z1. */
#define KART_NCP 6
#define KART_NTURBOS 4
#define KART_NCAJAS 2
#define KART_SALIDA_X 128
#define KART_SALIDA_Z -896
#define KART_SUELO_HIERBA 450
#define KART_FONDO 300
static const s16 kart_cp[KART_NCP][7] = {
    {768, -1664, 1280, -128, 1024, -896, 1024},
    {9472, 2560, 11008, 3072, 10240, 2816, 0},
    {7168, 6400, 7680, 7936, 7424, 7168, 3072},
    {3584, 2816, 4096, 4352, 3840, 3584, 3072},
    {-1024, 6400, -512, 7936, -768, 7168, 3072},
    {-3840, 2560, -2304, 3072, -3072, 2816, 2048},
};
static const s16 kart_turbos[KART_NTURBOS][4] = {
    {4096, -1152, 4608, -640},
    {9984, 512, 10496, 1024},
    {1792, 4864, 2304, 5376},
    {-3328, 4096, -2816, 4608},
};
static const s16 kart_cajas[KART_NCAJAS][4] = {
    {9472, 4608, 11008, 4864},
    {256, 6400, 512, 7936},
};
/* La linea del rival (ruta_rival en mapa_kart.py): cada tramo x, z, rumbo y direccion (ux, uz de largo
 * 4096); kart_ruta_d es la distancia al empezar cada tramo y KART_RUTA_LARGO la de una vuelta. */
#define KART_RUTA_N 17
#define KART_RUTA_LARGO 47112
static const s16 kart_ruta[KART_RUTA_N][5] = {
    {1024, -896, 1024, 4096, 0},
    {9640, -896, 512, 2896, 2896},
    {10240, -296, 0, 0, 4096},
    {10240, 6568, 3584, -2896, 2896},
    {9640, 7168, 3072, -4096, 0},
    {6744, 7168, 2560, -2896, -2896},
    {6144, 6568, 2048, 0, -4096},
    {6144, 4184, 2560, -2896, -2896},
    {5544, 3584, 3072, -4096, 0},
    {2648, 3584, 3584, -2896, 2896},
    {2048, 4184, 0, 0, 4096},
    {2048, 6568, 3584, -2896, 2896},
    {1448, 7168, 3072, -4096, 0},
    {-2472, 7168, 2560, -2896, -2896},
    {-3072, 6568, 2048, 0, -4096},
    {-3072, -296, 1536, 2896, -2896},
    {-2472, -896, 1024, 4096, 0},
};
static const s32 kart_ruta_d[KART_RUTA_N] = {0, 8616, 9465, 16329, 17178, 20074, 20923, 23307, 24156, 27052, 27901, 30285, 31134, 35054, 35903, 42767, 43616};
