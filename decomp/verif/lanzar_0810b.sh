#!/bin/bash
# 08-10: paso 2 del traspaso 07-10. El cambio de modelo_cd.py (saltar el audio XA) solo toca lo que lee los .STR:
# el disco tiene sectores XA solo en FMV (LBA 14140 a 40596; la musica va en pistas de CD-DA y los .WAV de AUDIO*
# apuntan a esas pistas). Reverifica las funciones del reproductor de video que ya estaban IGUAL.
# Espera el "TODO FIN" de build/cola_0810.txt (una cola a la vez por la RAM). Log: build/cola_0810b.txt
d=/mnt/c/Proyectos/SABRINA/decomp
cd $d
s=$d/build/cola_0810b.txt; rm -f $s
until grep -q "TODO FIN" $d/build/cola_0810.txt 2>/dev/null; do sleep 60; done
source ~/decomp-herramientas/venv/bin/activate
for par in Screen/video_g13.c:func_8005DDE8 Screen/video_g13.c:func_8005D164 Screen/video_g13.c:func_8005DCD4 \
           Screen/video_g13.c:func_8005D844 Screen/video_g13.c:func_8005D9C0 Screen/video_g13.c:func_8005D1D0 \
           Screen/video_g13.c:func_8005DA50 Screen/video_inicio_g14.c:func_8005C9D0 auto/func_8005CEBC.c:func_8005CEBC \
           Screen/video_cuadro_g14.c:func_8005D26C auto/func_8005D8D0.c:func_8005D8D0 auto/func_8005CD98.c:func_8005CD98 \
           auto/func_8005CE48.c:func_8005CE48 Screen/limpiar_g14.c:func_8005C964 auto/func_8005DCA0.c:func_8005DCA0; do
  echo "== ${par##*:} src/${par%%:*}" >> $s
  timeout 5400 bash $d/verif/vfull.sh src/${par%%:*} ${par##*:} >> $s 2>&1 < /dev/null
done
for par in varios/sueltas_g13.c:func_8005C940 auto/func_8005C8E0.c:func_8005C8E0; do
  echo "== ${par##*:} src/${par%%:*} (sint)" >> $s
  timeout 5400 bash $d/verif/vsint.sh src/${par%%:*} ${par##*:} >> $s 2>&1 < /dev/null
done
echo "TODO FIN $(date)" >> $s
