// Aplica notas\simbolos.tsv al programa: fija el registro gp en todo el codigo (asi las variables
// globales salen con su direccion real y no como iRamffffXXXX), renombra funciones (creandolas si
// hace falta) y pone etiquetas a los datos. Despues vuelve a analizar.
// Uso (headless): -process SLUS_012.08 -postScript AplicarSimbolos.java <ruta de simbolos.tsv>
//@category Sabrina
import java.io.File;
import java.math.BigInteger;
import java.nio.file.Files;
import java.util.List;

import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.plugin.core.analysis.AutoAnalysisManager;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.ProgramContext;
import ghidra.program.model.symbol.SourceType;

public class AplicarSimbolos extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String ruta = getScriptArgs()[0];
        List<String> lineas = Files.readAllLines(new File(ruta).toPath());

        Register gp = currentProgram.getRegister("gp");
        ProgramContext ctx = currentProgram.getProgramContext();
        ctx.setValue(gp, toAddr(0x80010000L), toAddr(0x80060800L), BigInteger.valueOf(0x80084754L));

        int funciones = 0, datos = 0;
        for (String l : lineas.subList(1, lineas.size())) {
            String[] c = l.split("\t");
            if (c.length < 3) continue;
            Address a = toAddr(Long.parseLong(c[0], 16));
            if (c[1].equals("funcion")) {
                Function f = getFunctionAt(a);
                if (f == null) {
                    new DisassembleCommand(new AddressSet(a), null, true).applyTo(currentProgram, monitor);
                    f = createFunction(a, c[2]);
                }
                if (f != null) {
                    f.setName(c[2], SourceType.USER_DEFINED);
                    if (c.length > 3) f.setComment(c[3]);
                    funciones++;
                }
            } else {
                createLabel(a, c[2], true, SourceType.USER_DEFINED);
                if (c.length > 3) setPlateComment(a, c[3]);
                datos++;
            }
        }
        AutoAnalysisManager m = AutoAnalysisManager.getAnalysisManager(currentProgram);
        m.reAnalyzeAll(null);
        m.startAnalysis(monitor);
        println("AplicarSimbolos: gp fijado, " + funciones + " funciones y " + datos + " datos con nombre");
    }
}
