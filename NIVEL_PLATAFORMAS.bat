@echo off
rem Doble clic: abre el nivel de plataformas (salida verde, meta dorada). Ver GUIA_EDITOR.md
set "PY=python"
where py >nul 2>nul && set "PY=py"
%PY% "%~dp0scripts\jugar.py" nivel %*
if errorlevel 1 pause
