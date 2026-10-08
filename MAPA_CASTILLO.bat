@echo off
rem Doble clic: abre el mapa del castillo (niveles\castillo.json) con sonido, listo para jugar.
python "%~dp0scripts\jugar.py" nivel "%~dp0niveles\castillo.json" %*
if errorlevel 1 pause
