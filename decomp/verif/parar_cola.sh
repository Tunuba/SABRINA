# para todas las tandas de verificacion que corren sueltas en WSL (lanzar_*, cadena, vfull/vmano/vsint, mutantes)
for p in $(ps -eo pid,args | grep -E 'lanzar_|cadena\.sh|vfull\.sh|vmano\.sh|vsint\.sh|python3 -|sint\.py mutantes' | grep -v grep | awk '{print $1}'); do
  kill $p 2>/dev/null
done
sleep 2
ps -eo args | grep -E 'lanzar_|cadena\.sh|python3 -|mutantes' | grep -v grep | wc -l
