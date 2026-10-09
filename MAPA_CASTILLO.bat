@echo off
rem Doble clic: abre el mapa del castillo (niveles\castillo.json) con sonido, listo para jugar. Ver GUIA_EDITOR.md
set "PY=python"
where py >nul 2>nul && set "PY=py"
%PY% "%~dp0scripts\jugar.py" nivel "%~dp0niveles\castillo.json" %*
if errorlevel 1 pause
