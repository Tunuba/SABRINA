@echo off
rem Doble clic: Greendale con la camara libre (SELECT la prende y la apaga). Ver GUIA_EDITOR.md
set "PY=python"
where py >nul 2>nul && set "PY=py"
%PY% "%~dp0scripts\jugar.py" nivel "%~dp0niveles\greendale.json" --libre %*
if errorlevel 1 pause
