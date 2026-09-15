@echo off
rem Doble clic: instala lo que falte, aplica los mods y abre Sabrina.
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0arrancar.ps1" %*
if errorlevel 1 pause
