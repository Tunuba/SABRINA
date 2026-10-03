# uso: sint_lote2.sh log "opciones de candidatas"   (de a una, con tope de 10 min cada una)
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
log=$1; shift
L=$(python3 sint.py candidatas $@ --nuevas | cut -f2)
echo "candidatas: $(echo "$L" | wc -l)" > $log
for f in $L; do
  if timeout 600 python3 sint.py lote "$f" >> $log 2>&1; then :; else
    echo "$f TOPE_DE_TIEMPO" >> $log
    printf '%s\t0\tTOPE_DE_TIEMPO\t\n' "$f" >> progreso_sint.tsv
  fi
done
echo FIN >> $log
