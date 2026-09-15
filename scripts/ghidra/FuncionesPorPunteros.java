// Crea funciones en el codigo al que solo se llega por tablas de punteros (clases de objetos, maquinas
// de estados), que el analisis automatico de Ghidra no descubre.
// Recorre la zona de datos buscando palabras que apunten dentro del codigo, a una instruccion
// "addiu sp, sp, -N" (el comienzo tipico de una funcion MIPS), y crea la funcion ahi.
// Uso (headless, sobre el programa ya importado): -process SLUS_012.08 -postScript FuncionesPorPunteros.java
//@category Sabrina
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.mem.Memory;

public class FuncionesPorPunteros extends GhidraScript {
    @Override
    protected void run() throws Exception {
        Memory mem = currentProgram.getMemory();
        long codIni = 0x80010000L, codFin = 0x80060800L;     // codigo
        long datIni = 0x80060800L, datFin = 0x8007c9d8L;     // datos inicializados
        int creadas = 0, vistas = 0;
        for (long a = datIni; a < datFin; a += 4) {
            Address da = toAddr(a);
            int v;
            try { v = mem.getInt(da); } catch (Exception e) { continue; }
            long p = v & 0xffffffffL;
            if (p < codIni || p >= codFin || (p & 3) != 0) continue;
            int ins;
            try { ins = mem.getInt(toAddr(p)); } catch (Exception e) { continue; }
            // addiu sp, sp, imm negativo (0x27bd8000 .. 0x27bdffff), o una funcion hoja sin pila: justo
            // despues del "jr ra" (0x03e00008) y su hueco de retardo con que termina la anterior
            int antes = 0;
            try { antes = mem.getInt(toAddr(p - 8)); } catch (Exception e) { }
            if ((ins & 0xffff8000) != 0x27bd8000 && antes != 0x03e00008) continue;
            vistas++;
            Address fa = toAddr(p);
            if (getFunctionAt(fa) != null) continue;
            if (getFunctionContaining(fa) != null && !getFunctionContaining(fa).getEntryPoint().equals(fa)) {
                // cae dentro de otra funcion mal delimitada: se crea igual, Ghidra la parte
            }
            new DisassembleCommand(new AddressSet(fa), null, true).applyTo(currentProgram, monitor);
            if (createFunction(fa, null) != null) creadas++;
        }
        println("FuncionesPorPunteros: " + vistas + " punteros a comienzos de funcion, " + creadas + " funciones nuevas");
    }
}
