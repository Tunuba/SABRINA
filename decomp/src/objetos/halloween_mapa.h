/* Generado por scripts/mapa_halloween.py: no editar a mano. El castillo de Halloween (niveles/halloween.json).
 * Por zona: la salida (x, z, rumbo), cuantas calabazas, y las posiciones (x, y, z; y hacia abajo) de las
 * calabazas, las manzanas, los fantasmas, los murcielagos y las calabazas saltarinas; el portal; el jefe. */
#define HW_ZONAS 4
#define HW_MAX_CALABAZAS 6
#define HW_MAX_MANZANAS 3
#define HW_MAX_FANTASMAS 3
#define HW_MAX_MURCIELAGOS 4
#define HW_MAX_SALTARINAS 2
static const s16 hw_salida[HW_ZONAS][3] = {{128, -896, 2048}, {6693, -971, 1024}, {14373, -2507, 1024}, {6693, 6197, 1024}};
static const u8 hw_n_calabazas[HW_ZONAS] = {6, 6, 5, 0};
static const u8 hw_n_manzanas[HW_ZONAS] = {2, 2, 1, 3};
static const u8 hw_n_fantasmas[HW_ZONAS] = {3, 2, 0, 0};
static const u8 hw_n_murcielagos[HW_ZONAS] = {0, 2, 4, 0};
static const u8 hw_n_saltarinas[HW_ZONAS] = {0, 2, 0, 0};
static const s16 hw_calabazas[HW_ZONAS][6][3] = {
    {{-1536, 0, -3200}, {2048, -720, -2944}, {-1152, 0, 768}, {1792, 0, 1024}, {-512, 0, -1792}, {2432, 0, -1792}},
    {{8704, -500, -3328}, {6656, -500, 1280}, {10496, -500, 1280}, {8704, 0, -512}, {11008, -260, -1024}, {7424, 0, 512}},
    {{15040, -500, -3264}, {15040, -1000, -1856}, {13632, -1500, -1856}, {13632, -2000, -3264}, {15040, -2500, -3264}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
};
static const s16 hw_manzanas[HW_ZONAS][3][3] = {
    {{512, 0, 1024}, {-1792, 0, -768}, {0, 0, 0}},
    {{9216, 0, 0}, {8192, -500, -3328}, {0, 0, 0}},
    {{13632, -1500, -1856}, {0, 0, 0}, {0, 0, 0}},
    {{7168, 0, 7680}, {9216, 0, 4608}, {9216, 0, 7680}},
};
static const s16 hw_fantasmas[HW_ZONAS][3][3] = {
    {{-1408, 0, -2048}, {2304, 0, -1024}, {-1024, 0, 1280}},
    {{8704, 0, -1536}, {9728, 0, 512}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
};
static const s16 hw_murcielagos[HW_ZONAS][4][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{7680, -700, -1024}, {9728, -700, -1024}, {0, 0, 0}, {0, 0, 0}},
    {{14336, -900, -2560}, {14336, -1700, -2560}, {14336, -2500, -2560}, {13824, -1300, -3072}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
};
static const s16 hw_saltarinas[HW_ZONAS][2][3] = {
    {{0, 0, 0}, {0, 0, 0}},
    {{8192, 0, 0}, {9984, 0, -2304}},
    {{0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}},
};
static const s16 hw_portal[HW_ZONAS][3] = {{512, 0, -3200}, {8704, 0, -1024}, {14336, -3000, -2560}, {0, 0, 0}};
#define HW_JEFE_X 8192
#define HW_JEFE_Z 6144
