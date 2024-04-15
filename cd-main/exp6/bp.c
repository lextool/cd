#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 100

typedef enum { SHIFT, REDUCE, ACCEPT } ActionType;

typedef struct {
    ActionType type;
    int value;
} Action;

typedef struct {
    char symbol;
    int nextState;
} StateTransition;

typedef struct {
    char symbol;
    int productionLength;
    char production[MAX_STACK_SIZE];
} Production;

Action actionTable[MAX_STACK_SIZE][MAX_INPUT_SIZE];
StateTransition gotoTable[MAX_STACK_SIZE][MAX_INPUT_SIZE];

Production productions[] = {
    {'E', 3, {'E', '+', 'T'}},
    {'E', 3, {'E', '-', 'T'}},
    {'E', 1, {'T'}},
    {'T', 3, {'T', '*', 'F'}},
    {'T', 3, {'T', '/', 'F'}},
    {'T', 1, {'F'}},
    {'F', 3, {'(', 'E', ')'}},
    {'F', 1, {'i'}} // 'i' represents an identifier or a number in this grammar
};

int stack[MAX_STACK_SIZE];
int stackTop = -1;

void push(int state) {
    stack[++stackTop] = state;
}

int pop() {
    return stack[stackTop--];
}

ActionType getActionType(char actionChar) {
    switch (actionChar) {
        case 's':
            return SHIFT;
        case 'r':
            return REDUCE;
        case 'a':
            return ACCEPT;
        default:
            return -1;
    }
}

void initializeTables() {
    // Initialize action table
    actionTable[0][0].type = SHIFT;
    actionTable[0][0].value = 5;
    actionTable[0][3].type = SHIFT;
    actionTable[0][3].value = 4;
    actionTable[1][1].type = SHIFT;
    actionTable[1][1].value = 6;
    actionTable[1][2].type = REDUCE;
    actionTable[1][2].value = 2;
    actionTable[1][4].type = REDUCE;
    actionTable[1][4].value = 2;
    actionTable[1][5].type = REDUCE;
    actionTable[1][5].value = 2;
    actionTable[1][6].type = REDUCE;
    actionTable[1][6].value = 2;
    actionTable[2][0].type = ACCEPT;
    
    // Initialize goto table
    gotoTable[0][0].symbol = 'E';
    gotoTable[0][0].nextState = 1;
    gotoTable[0][3].symbol = 'E';
    gotoTable[0][3].nextState = 7;
    gotoTable[1][1].symbol = 'T';
    gotoTable[1][1].nextState = 2;
    gotoTable[1][5].symbol = 'T';
    gotoTable[1][5].nextState = 7;
    gotoTable[1][6].symbol = 'F';
    gotoTable[1][6].nextState = 8;
}

void reduce(int productionIndex) {
    Production p = productions[productionIndex];
    for (int i = 0; i < p.productionLength; ++i) {
        pop(); // Pop symbols from the stack according to the production length
    }
    push(gotoTable[stack[stackTop]][p.symbol - 'E'].nextState);
}

void shift(int state) {
    push(state);
}

void parseInput(const char *input) {
    initializeTables();
    int index = 0;
    char currentSymbol = input[index];
    push(0);
    while (1) {
        int currentState = stack[stackTop];
        Action currentAction = actionTable[currentState][currentSymbol - 'i'];
        switch (currentAction.type) {
            case SHIFT:
                shift(currentAction.value);
                index++;
                currentSymbol = input[index];
                break;
            case REDUCE:
                reduce(currentAction.value);
                break;
            case ACCEPT:
                printf("Parsing successful!\n");
                return;
            default:
                printf("Error: Invalid action type.\n");
                return;
        }
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    printf("Enter the input string (e.g., 'i+i*i' or 'i+i'):\n");
    fgets(input, MAX_INPUT_SIZE, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove trailing newline character
    parseInput(input);
    return 0;
}
