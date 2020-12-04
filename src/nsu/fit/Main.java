package nsu.fit;

import org.graalvm.polyglot.Context;
import org.graalvm.polyglot.Source;
import org.graalvm.polyglot.Value;

import java.io.File;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        Source llvm = Source.newBuilder("llvm", new File("src/nsu/fit/cppmod.bc")).build();
        Context context = Context.newBuilder().allowAllAccess(true).build();

        Value llvmLib = context.eval(llvm);

        Value cpuInfoMethod = llvmLib.getMember("cpuInfo");
        Value cpuInfo = cpuInfoMethod.execute();

        int procNum = cpuInfo.getMember("cpu_cores").asInt();
        Value modelValue = cpuInfo.getMember("cpu_model");
        long modelArraySize = modelValue.getArraySize();
        byte[] modelBufferCpy = new byte[(int) modelArraySize];
        for (int i = 0; i < (int) modelArraySize; i++) {
            modelBufferCpy[i] = modelValue.getArrayElement(i).asByte();
        }
        String procModel = new String(modelBufferCpy).trim();
        System.out.println("Number of cores: " + procNum);
        System.out.println("Processor model: " + procModel);
    }
}
