@echo off
rem Doble clic: abre Greendale, el pueblo de Sabrina bajo la niebla (niveles\greendale.json), listo para jugar. Ver GUIA_EDITOR.md
set "PY=python"
where py >nul 2>nul && set "PY=py"
%PY% "%~dp0scripts\jugar.py" nivel "%~dp0niveles\greendale.json" %*
if errorlevel 1 pause
