# Para usar con "source" desde los scripts de Git Bash que llaman a WSL. Sirve igual en cualquier PC:
#   SABRINA_WSL   la distro de WSL: la variable si esta puesta; si no, Ubuntu o Ubuntu-24.04 (la que exista)
#   ruta_wsl DIR  la ruta de una carpeta de Windows vista desde WSL (C:\Proyectos -> /mnt/c/Proyectos)
if [ -z "${SABRINA_WSL:-}" ]; then
  _distros=$(wsl.exe -l -q 2>/dev/null | tr -d '\0\r')
  if grep -qx Ubuntu <<<"$_distros"; then SABRINA_WSL=Ubuntu
  elif grep -qx Ubuntu-24.04 <<<"$_distros"; then SABRINA_WSL=Ubuntu-24.04
  else SABRINA_WSL=Ubuntu; fi
fi
ruta_wsl() { (cd "$1" && pwd -W) | sed -E 's#^([A-Za-z]):#/mnt/\L\1#'; }
