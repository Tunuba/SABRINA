@echo off
rem Doble clic: el mapa del castillo con la camara libre (SELECT la prende y la apaga).
python "%~dp0scripts\jugar.py" nivel "%~dp0niveles\castillo.json" --libre %*
if errorlevel 1 pause
