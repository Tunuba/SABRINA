# capturas sinteticas a mano de func_8003C9DC, una por estado (los mutantes daban 4 de 8 con la de la donante)
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
F=func_8003C9DC
python3 sint.py crear_con $F a0=0x8008bb18,m8008BB88=0100,m8008BB9C=0000,m8008BB98=4000,m8008BB9A=2000
python3 sint.py crear_con $F a0=0x8008bb18,m8008BB88=0200,m8008BB98=0600,m8008BB78=80451080,m8008BB94=00200000
python3 sint.py crear_con $F a0=0x8008bb18,m8008BB88=0200,m8008BB98=8100,m8008BB78=80451080,m8008BB94=00200000,m8008BB90=00100000
python3 sint.py crear_con $F a0=0x8008bb18,m8008BB88=0300,m8008BB98=2002,m8008BB6C=00080000,m8008BB9E=0600
