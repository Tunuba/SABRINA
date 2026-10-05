#!/bin/bash
# 05-10: capturas sinteticas a mano para las de tarjeta_archivo_g16.c. Las de la donante casi no las recorrian
# (func_800513B4 con nombre NULL y un evento abierto salia en la primera linea: 0 de 8 mutantes; func_80050418
# leia el estado de la direccion 4). El estado de las maquinas va en S = 0x801F0000 (fuera de la pila local).
# D_800D52C0: [0] evento, [1] resultado, [4] puerto, [5] archivo, [9..] nombre. Banderas: D_800D5390 (las mira
# func_80051FCC y func_80051E1C) y D_800D53A0 (func_80052008 y func_80051EF4). Se corre desde WSL, una vez.
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
S=0x801F0000
M=m801F0000
NOMBRE=m800D52E4=627530303a4241534c55532d303132303853414249000000

F=func_80050418
python3 sint.py crear_con $F a0=$S,$M=00000000
python3 sint.py crear_con $F a0=$S,$M=1E000000
python3 sint.py crear_con $F a0=$S,$M=1E000000,m800D5390=01000000
python3 sint.py crear_con $F a0=$S,$M=1E000000,m800D5394=01000000
python3 sint.py crear_con $F a0=$S,$M=1E000000,m800D5394=01000000,m80075B30=03000000
python3 sint.py crear_con $F a0=$S,$M=14000000

for F in func_80050554 func_80050694; do
  python3 sint.py crear_con $F a0=$S,$M=00000000
  python3 sint.py crear_con $F a0=$S,$M=0A000000,m800D52C4=00000000,$NOMBRE
  python3 sint.py crear_con $F a0=$S,$M=0A000000,m800D52C4=03000000
  python3 sint.py crear_con $F a0=$S,$M=0B000000
  python3 sint.py crear_con $F a0=$S,$M=14000000,m800D52C4=03000000,m800D52D0=01000000
  python3 sint.py crear_con $F a0=$S,$M=14000000,m800D52C4=00000000,m800D52D4=05000000
  python3 sint.py crear_con $F a0=$S,$M=16000000
  python3 sint.py crear_con $F a0=$S,$M=16000000,m800D53A0=01000000
  python3 sint.py crear_con $F a0=$S,$M=07000000
done

F=func_800513B4
python3 sint.py crear_con $F a0=0,a1=0x80075938,a2=1,m800D52C0=00000000
python3 sint.py crear_con $F a0=0x10,a1=0x80075938,a2=3,m800D52C0=00000000,m800D52CC=05000000,m800D52D0=01000000

F=func_80050AB8
python3 sint.py crear_con $F a0=0,a1=0x80075938,a2=2,m800D52C0=00000000
python3 sint.py crear_con $F a0=0,a1=0x80075938,a2=2,m800D52C0=01000000
python3 sint.py crear_con $F a0=0,a1=0x80075938,a2=2,m800D52D4=03000000
