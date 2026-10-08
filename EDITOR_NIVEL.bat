@echo off
rem Doble clic: abre el editor de niveles de plataformas (los niveles se guardan en niveles\*.json).
python "%~dp0scripts\editor_nivel.py" %*
if errorlevel 1 pause
