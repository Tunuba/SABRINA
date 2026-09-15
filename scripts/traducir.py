"""Traduce los textos de menus del ejecutable (SLUS_012.08) y arma el disco en espanol.

Cada texto se escribe en su mismo sitio. El espacio disponible es el largo original redondeado a
multiplo de 4 (los textos estan alineados a 4 bytes) menos el cero final; si una traduccion no cabe,
el script se detiene y dice cual. Asi no se mueve nada del ejecutable.

Signos: '=' es el icono del boton X en la letra del juego y '^' es un bloque de la barra de volumen.
En los textos de volumen se conserva el largo del prefijo, por si el juego cambia las '^' por posicion.
La letra del juego no tiene tildes ni signos de apertura.

Uso: python traducir.py      deja disco\\sabrina_es (Track 01).bin y disco\\sabrina_es.cue
"""
import os

import disco
from mod_carga import pantalla_carga

TEXTOS = {
    "New game": "Nuevo juego",
    "Load game": "Cargar",
    "Options": "Ajustes",
    "Credits": "Autores",
    "Continue": "Seguir",
    "Save game": "Guardar",
    "Continue game": "Seguir jugando",
    "Return to Cosmic Cog": "Volver al Engranaje",
    "Quit game": "Salir",
    "Screen position": "Mover pantalla",
    "Sound options": "Sonido",
    "Back to Main Menu": "Volver al menu",
    "SFX volume ^^^^^^^^": "Efectos:   ^^^^^^^^",
    "Music volume ^^^^^^^^": "Musica:      ^^^^^^^^",
    "Back to Options Menu": "Volver a ajustes",
    "Use directional button": "Usa la cruceta",
    "to adjust the screen": "para mover la imagen",
    "Press = button to set": "Pulsa = para fijar",
    "Are you sure?": "Seguro?",
    "No MEMORY CARD": "Sin MEMORY CARD",
    "Press = to continue": "Pulsa = para seguir",
    "MEMORY CARD in slot 1 is not formatted": "La MEMORY CARD 1 no tiene formato",
    "Do you wish to format the MEMORY CARD?": "Quieres darle formato?",
    "Creating game file": "Creando partida",
    "Please wait": "Espera",
    "Reading MEMORY CARD slot 1 directory": "Leyendo la MEMORY CARD 1",
    "Loading data from MEMORY CARD slot 1": "Cargando de la MEMORY CARD 1",
    "Please do not remove the card": "No saques la tarjeta",
    "Saving data to MEMORY CARD slot 1": "Guardando en la MEMORY CARD 1",
    "Formatting MEMORY CARD slot 1": "Formateando la MEMORY CARD 1",
    "Cannot perform load": "No se pudo cargar",
    "Press = button to continue": "Pulsa = para seguir",
    "MEMORY CARD in slot 1 is full": "La MEMORY CARD 1 esta llena",
    "Cannot perform save": "No se pudo guardar",
    "MEMORY CARD in slot 1": "La MEMORY CARD 1",
    "Contains no Sabrina game files": "No tiene partidas de Sabrina",
    "Read successful.": "Carga lista.",
    "Read failed": "Fallo carga",
    "Write successful": "Guardado listo",
    "Write failed": "Fallo guardado",
    "Load game data": "Cargar partida",
}

EXE = "SLUS_012.08"


def traducir_exe(datos, textos=TEXTOS):
    d = bytearray(datos)
    hechos = 0
    for viejo, nuevo in textos.items():
        v = viejo.encode("ascii")
        n = nuevo.encode("ascii")
        pos = 0
        vistos = 0
        while True:
            i = d.find(v + b"\0", pos)
            if i < 0:
                break
            pos = i + 1
            if i > 0 and d[i - 1] != 0:
                continue        # es la cola de otro texto, no un texto propio
            espacio = ((len(v) + 1 + 3) // 4) * 4 - 1
            if len(n) > espacio:
                raise ValueError(f'"{nuevo}" mide {len(n)} y en "{viejo}" caben {espacio}')
            d[i:i + espacio + 1] = n.ljust(espacio + 1, b"\0")
            vistos += 1
        if vistos == 0:
            raise ValueError(f'no encontre "{viejo}" en el ejecutable')
        hechos += vistos
    return bytes(d), hechos


if __name__ == "__main__":
    exe = open(os.path.join(disco.RAIZ, "extraido", EXE), "rb").read()
    nuevo, n = traducir_exe(exe)
    print(f"{n} textos cambiados en el ejecutable")
    pista = os.path.join(disco.DISCO, "sabrina_es (Track 01).bin")
    disco.parchar({EXE: nuevo, r"GRAPHICS\FRONT\FR.PIC": pantalla_carga()}, pista)
    disco.cue_mod(os.path.join(disco.DISCO, "sabrina_es.cue"), pista)
    print("disco en espanol:", pista)
