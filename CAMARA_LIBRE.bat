@echo off
rem Doble clic: abre el juego con la camara libre (SELECT la prende y la apaga). Ver GUIA_EDITOR.md
set "PY=python"
where py >nul 2>nul && set "PY=py"
%PY% "%~dp0scripts\jugar.py" camara %*
if errorlevel 1 pause
