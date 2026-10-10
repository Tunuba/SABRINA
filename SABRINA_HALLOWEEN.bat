@echo off
rem Doble clic: SABRINA, NOCHE DE BRUJAS EN EL CASTILLO (el especial de Halloween). Ver GUIA_EDITOR.md
set "PY=python"
where py >nul 2>nul && set "PY=py"
%PY% "%~dp0scripts\halloween.py" %*
if errorlevel 1 pause
