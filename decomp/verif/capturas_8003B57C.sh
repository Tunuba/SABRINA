# capturas sinteticas a mano de func_8003B57C (los mutantes daban 2 de 8: a0 de la donante no era un objeto).
# Objeto falso en 0x80104580 (zona libre): funcion 0x08 = func_80024F6C, escala 0x800; enganchada: Sabrina.
cd /mnt/c/Proyectos/SABRINA/decomp && source ~/decomp-herramientas/venv/bin/activate
F=func_8003B57C
B=a0=0x80104580,m80104588=6C4F0280,m801045D4=00080000
python3 sint.py crear_con $F $B,m80104608=0100,m801045F4=F8B00880,m8010460C=1400,m80104610=0500
python3 sint.py crear_con $F $B,m80104608=0100,m801045F4=F8B00880,m8010460C=0100
python3 sint.py crear_con $F $B,m80104608=0200,m801045F4=F8B00880,m801045F8=F8B00880,m8010460A=0100,m8010460E=FFFF,m80104610=0300
python3 sint.py crear_con $F $B,m80104608=0200,m801045F8=F8B00880,m8010460C=0300
python3 sint.py crear_con $F a0=0x80104580,m80104588=6C4F0280,m801045D4=00010000
