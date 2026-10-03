# verificacion con el GPU modelado como desocupado (SABRINA_GPU_LISTA=1); resultados APARTE (anotar.py --gpu)
export SABRINA_GPU_LISTA=1
cd /mnt/c/Proyectos/SABRINA/decomp/verif
TOPE=3000 bash vvarias.sh src/TexAnima/paletas_g06.c func_80022D4C
TOPE=3000 bash vvarias.sh src/libgpu/gpu_g01.c func_8001315C
TOPE=3000 bash vvarias.sh src/libgpu/cola_g13.c func_800123E0
TOPE=3000 bash vvarias.sh src/Screen/pantalla_g05.c func_80010880
for f in func_80012130 func_8005D26C func_80011D9C func_80011B60 func_8005C964; do TOPE=3000 bash vvarias.sh src/auto/$f.c $f; done
TOPE=3000 bash vvarias.sh --sint src/libgpu/imagen_g14.c func_8001390C func_800139F8 func_80013C28 func_80013AE4
echo FIN
