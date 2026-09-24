@echo off
rem Doble clic en una PC nueva: deja la descompilacion de Sabrina andando (ver restaurar.ps1).
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0restaurar.ps1" %*
pause
