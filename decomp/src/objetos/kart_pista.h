/* Generado por scripts/mapa_kart.py: no editar a mano. La pista de SABRINA KART (niveles/kart.json). */
/* Puntos de control en el orden de la carrera (el 0 es la meta): x0, z0, x1, z1, x y z donde se
 * reaparece, y el rumbo del kart ahi. Turbos y cajas de hechizo: x0, z0, x1, z1. */
#define KART_NCP 6
#define KART_NTURBOS 4
#define KART_NCAJAS 6
#define KART_SALIDA_X 128
#define KART_SALIDA_Z -896
#define KART_SUELO_HIERBA 96
#define KART_FONDO 496
static const s16 kart_cp[KART_NCP][7] = {
    {768, -1664, 1280, -128, 1024, -896, 1024},
    {9472, 2560, 11008, 3072, 10240, 2816, 0},
    {7168, 6400, 7680, 7936, 7424, 7168, 3072},
    {3584, 2816, 4096, 4352, 3840, 3584, 3072},
    {-1024, 6400, -512, 7936, -768, 7168, 3072},
    {-3840, 2560, -2304, 3072, -3072, 2816, 2048},
};
static const s16 kart_turbos[KART_NTURBOS][4] = {
    {4096, -1280, 4608, -512},
    {9984, 512, 10496, 1024},
    {1792, 4864, 2304, 5376},
    {-3328, 4096, -2816, 4608},
};
static const s16 kart_cajas[KART_NCAJAS][4] = {
    {9600, 4608, 9856, 4864},
    {10112, 4608, 10368, 4864},
    {10624, 4608, 10880, 4864},
    {256, 6528, 512, 6784},
    {256, 7040, 512, 7296},
    {256, 7552, 512, 7808},
};
