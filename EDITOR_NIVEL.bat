@echo off
rem Doble clic: abre el editor de niveles (los niveles se guardan en niveles\*.json). Ver GUIA_EDITOR.md
set "PY=python"
where py >nul 2>nul && set "PY=py"
%PY% "%~dp0scripts\editor_nivel.py" %*
if errorlevel 1 pause
