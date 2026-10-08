@echo off
rem Doble clic: abre el nivel de plataformas (salida verde, meta dorada).
python "%~dp0scripts\jugar.py" nivel %*
if errorlevel 1 pause
