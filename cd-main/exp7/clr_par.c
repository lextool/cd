import java.util.*;

class CLRParser {
    private static final String[] terminals = {"i", "+", "*", "(", ")", "$"};
    private static final String[] nonTerminals = {"E", "T", "F"};
    private static final String[][] parsingTable = {
            {"s5", "", "", "s4", "", ""},
            {"", "s6", "", "", "", "acc"},
            {"", "r2", "s7", "", "r2", "r2"},
            {"", "r4", "r4", "", "r4", "r4"},
            {"s5", "", "", "s4", "", ""},
            {"", "r6", "r6", "", "r6", "r6"},
            {"s5", "", "", "s4", "", ""},
            {"s5", "", "", "s4", "", ""},
            {"", "s6", "", "", "s11", ""},
            {"", "r1", "s7", "", "r1", "r1"},
            {"", "r3", "r3", "", "r3", "r3"},
            {"", "r5", "r5", "", "r5", "r5"}
    };

    private static final int[][] gotoTable = {
            {1, 2, 3},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {8, 2, 3},
            {0, 0, 0},
            {0, 9, 3},
            {0, 0, 10},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
    };

    private static Stack<Integer> stateStack = new Stack<>();
    private static Stack<String> symbolStack = new Stack<>();

    private static int action(String terminal, int state) {
        for (int i = 0; i < terminals.length; i++) {
            if (terminals[i].equals(terminal)) {
                return Arrays.asList(parsingTable[state]).indexOf("s" + i);
            }
        }
        return -1;
    }

    private static int goTo(String nonTerminal, int state) {
        for (int i = 0; i < nonTerminals.length; i++) {
            if (nonTerminals[i].equals(nonTerminal)) {
                return gotoTable[state][i];
            }
        }
        return -1;
    }

    private static void reduce(int production) {
        String nonTerminal = nonTerminals[production];
        int length = nonTerminal.length();
        for (int i = 0; i < length; i++) {
            stateStack.pop();
            symbolStack.pop();
        }
        symbolStack.push(nonTerminal);
        stateStack.push(goTo(nonTerminal, stateStack.peek()));
    }

    public static boolean parse(String input) {
        input += "$";
        stateStack.push(0);
        int position = 0;
        while (position < input.length()) {
            String currentSymbol = Character.toString(input.charAt(position));
            int currentState = stateStack.peek();
            int actionIndex = action(currentSymbol, currentState);
            if (actionIndex != -1 && parsingTable[currentState][actionIndex].charAt(0) == 's') {
                stateStack.push(Integer.parseInt(parsingTable[currentState][actionIndex].substring(1)));
                symbolStack.push(currentSymbol);
                position++;
            } else if (actionIndex != -1 && parsingTable[currentState][actionIndex].charAt(0) == 'r') {
                int production = Integer.parseInt(parsingTable[currentState][actionIndex].substring(1));
                reduce(production);
            } else if (parsingTable[currentState][actionIndex].equals("acc")) {
                return true;
            } else {
                return false;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        String input = "i+i*i";
        if (parse(input)) {
            System.out.println("Parsing successful!");
        } else {
            System.out.println("Parsing failed!");
        }
    }
}
