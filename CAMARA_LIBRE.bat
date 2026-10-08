@echo off
rem Doble clic: abre el juego con la camara libre (SELECT la prende y la apaga).
python "%~dp0scripts\jugar.py" camara %*
if errorlevel 1 pause
