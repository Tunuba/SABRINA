cd /mnt/c/Proyectos/SABRINA/decomp/verif
TOPE=3000 bash vvarias.sh src/psyq/cdsync_g14.c func_8002A6D0 func_8002A950 > ../build/v_cdsync.txt 2>&1
TOPE=3000 bash vvarias.sh --sint src/libgpu/espacio_vram_g14.c func_8001A228 > ../build/v_vram.txt 2>&1
TOPE=3000 bash vvarias.sh --sint src/Font/glifos_g14.c func_8001ADD8 > ../build/v_glifos.txt 2>&1
