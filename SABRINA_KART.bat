@echo off
rem Doble clic: SABRINA KART, la Copa del Tiempo (niveles\kart.json + el modo carrera en C). Ver GUIA_EDITOR.md
set "PY=python"
where py >nul 2>nul && set "PY=py"
%PY% "%~dp0scripts\kart.py" %*
if errorlevel 1 pause
