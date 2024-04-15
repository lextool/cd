import java.util.*;

class IntermediateCodeGenerator {
    private List<String> intermediateCode;
    private int labelCount;

    IntermediateCodeGenerator() {
        intermediateCode = new ArrayList<>();
        labelCount = 0;
    }

    // Generate a new label
    private String newLabel() {
        return "L" + labelCount++;
    }

    // Generate intermediate code for an if statement
    public void generateIf(String condition, String trueLabel) {
        intermediateCode.add("if " + condition + " goto " + trueLabel);
    }

    // Generate intermediate code for a goto statement
    public void generateGoto(String label) {
        intermediateCode.add("goto " + label);
    }

    // Generate intermediate code for a label
    public void generateLabel(String label) {
        intermediateCode.add(label + ":");
    }

    // Generate intermediate code for a while statement
    public void generateWhile(String condition) {
        String loopLabel = newLabel();
        String endLabel = newLabel();

        generateLabel(loopLabel);
        generateIf(condition, endLabel);
        // Add code block here

        generateGoto(loopLabel);
        generateLabel(endLabel);
    }

    // Print the generated intermediate code
    public void printIntermediateCode() {
        for (String instruction : intermediateCode) {
            System.out.println(instruction);
        }
    }
}

public class Main {
    public static void main(String[] args) {
        IntermediateCodeGenerator generator = new IntermediateCodeGenerator();

        // Example of generating intermediate code for a while loop
        String condition = "i < 10";
        generator.generateWhile(condition);

        // Print the generated intermediate code
        generator.printIntermediateCode();
    }
}
