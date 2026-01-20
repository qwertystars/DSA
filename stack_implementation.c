#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_SIZE 100
#define MAX_STR_LEN 20

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isStackEmpty(Stack *s) {
    return s->top == -1;
}

int isStackFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, int value) {
    if (isStackFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->items[++s->top] = value;
}

int pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return s->items[s->top--];
}

int peek(Stack *s) {
    if (isStackEmpty(s)) {
        return -1;
    }
    return s->items[s->top];
}

typedef struct {
    char items[MAX_SIZE];
    int top;
} CStack;

void initCStack(CStack *s) {
    s->top = -1;
}

int isCStackEmpty(CStack *s) {
    return s->top == -1;
}

int isCStackFull(CStack *s) {
    return s->top == MAX_SIZE - 1;
}

void pushC(CStack *s, char c) {
    if (isCStackFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->items[++s->top] = c;
}

char popC(CStack *s) {
    if (isCStackEmpty(s)) {
        return '\0';
    }
    return s->items[s->top--];
}

char peekC(CStack *s) {
    if (isCStackEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void infixToPostfix(char *infix, char *postfix) {
    CStack s;
    initCStack(&s);
    int i = 0, j = 0;
    
    while (infix[i] != '\0') {
        char c = infix[i];
        
        if (isalnum(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            pushC(&s, c);
        } else if (c == ')') {
            while (!isCStackEmpty(&s) && peekC(&s) != '(') {
                postfix[j++] = popC(&s);
            }
            popC(&s);
        } else if (isOperator(c)) {
            while (!isCStackEmpty(&s) && peekC(&s) != '(' &&
                   precedence(peekC(&s)) >= precedence(c)) {
                postfix[j++] = popC(&s);
            }
            pushC(&s, c);
        }
        i++;
    }
    
    while (!isCStackEmpty(&s)) {
        postfix[j++] = popC(&s);
    }
    postfix[j] = '\0';
}

void reverseString(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
}

void swapParentheses(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') str[i] = ')';
        else if (str[i] == ')') str[i] = '(';
    }
}

void infixToPrefix(char *infix, char *prefix) {
    char temp[MAX_SIZE];
    strcpy(temp, infix);
    
    reverseString(temp);
    swapParentheses(temp);
    
    char postfix[MAX_SIZE];
    infixToPostfix(temp, postfix);
    
    strcpy(prefix, postfix);
    reverseString(prefix);
}

int applyOperator(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0;
        case '^': {
            int result = 1;
            for (int i = 0; i < b; i++) result *= a;
            return result;
        }
        default: return 0;
    }
}

int evaluatePostfix(char *postfix) {
    Stack s;
    initStack(&s);
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        
        if (isdigit(c)) {
            push(&s, c - '0');
        } else if (isOperator(c)) {
            int b = pop(&s);
            int a = pop(&s);
            int result = applyOperator(a, b, c);
            push(&s, result);
        }
    }
    
    return pop(&s);
}

int evaluatePrefix(char *prefix) {
    Stack s;
    initStack(&s);
    int n = strlen(prefix);
    
    for (int i = n - 1; i >= 0; i--) {
        char c = prefix[i];
        
        if (isdigit(c)) {
            push(&s, c - '0');
        } else if (isOperator(c)) {
            int a = pop(&s);
            int b = pop(&s);
            int result = applyOperator(a, b, c);
            push(&s, result);
        }
    }
    
    return pop(&s);
}

int areSymbolsBalanced(char *expr) {
    CStack s;
    initCStack(&s);
    
    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        
        if (c == '(' || c == '{' || c == '[') {
            pushC(&s, c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (isCStackEmpty(&s)) {
                return 0;
            }
            
            char top = popC(&s);
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return 0;
            }
        }
    }
    
    return isCStackEmpty(&s);
}

typedef struct {
    char items[MAX_SIZE][MAX_STR_LEN];
    int top;
} StringStack;

void initStringStack(StringStack *s) {
    s->top = -1;
}

int isStringStackEmpty(StringStack *s) {
    return s->top == -1;
}

void pushString(StringStack *s, char *str) {
    if (s->top >= MAX_SIZE - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    strcpy(s->items[++s->top], str);
}

char* popString(StringStack *s) {
    if (isStringStackEmpty(s)) {
        return NULL;
    }
    return s->items[s->top--];
}

char* peekString(StringStack *s) {
    if (isStringStackEmpty(s)) {
        return NULL;
    }
    return s->items[s->top];
}

void displayStringStack(StringStack *s) {
    printf("\nStack (Top to Bottom):\n");
    printf("----------------------\n");
    for (int i = s->top; i >= 0; i--) {
        printf("| %-12s |\n", s->items[i]);
    }
    printf("----------------------\n");
}

void processDockingSystem(StringStack *stack) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    
    int n = stack->top + 1;
    int seen[MAX_SIZE] = {0};
    char tempItems[MAX_SIZE][MAX_STR_LEN];
    
    for (int i = 0; i < n; i++) {
        strcpy(tempItems[i], stack->items[i]);
    }
    
    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        
        for (int j = i + 1; j < n; j++) {
            if (strcmp(tempItems[i], tempItems[j]) == 0) {
                strcpy(stack->items[j], "ERR-@DOCK");
                seen[j] = 1;
            }
        }
    }
    
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\n=== Algorithm Time Complexity Analysis ===\n");
    printf("Number of elements (n): %d\n", n);
    printf("Time Complexity: O(n^2) = O(%d^2) = O(%d)\n", n, n * n);
    printf("Space Complexity: O(n) = O(%d)\n", n);
    printf("Actual CPU Time: %.6f seconds\n", cpu_time_used);
}

typedef struct {
    Stack stack;
    char name[20];
} Rod;

void initRod(Rod *rod, char *name) {
    initStack(&rod->stack);
    strcpy(rod->name, name);
}

void movePlate(Rod *source, Rod *dest, int *moveCount) {
    if (isStackEmpty(&source->stack)) {
        int plate = pop(&dest->stack);
        push(&source->stack, plate);
        (*moveCount)++;
        printf("Move plate %d from %s to %s\n", plate, dest->name, source->name);
    } else if (isStackEmpty(&dest->stack)) {
        int plate = pop(&source->stack);
        push(&dest->stack, plate);
        (*moveCount)++;
        printf("Move plate %d from %s to %s\n", plate, source->name, dest->name);
    } else {
        int srcTop = peek(&source->stack);
        int destTop = peek(&dest->stack);
        
        if (srcTop < destTop) {
            int plate = pop(&source->stack);
            push(&dest->stack, plate);
            (*moveCount)++;
            printf("Move plate %d from %s to %s\n", plate, source->name, dest->name);
        } else {
            int plate = pop(&dest->stack);
            push(&source->stack, plate);
            (*moveCount)++;
            printf("Move plate %d from %s to %s\n", plate, dest->name, source->name);
        }
    }
}

void towersOfHanoiIterative(int n) {
    Rod source, auxiliary, destination;
    initRod(&source, "Source");
    initRod(&auxiliary, "Auxiliary");
    initRod(&destination, "Destination");
    
    int totalMoves = 0;
    
    for (int i = n; i >= 1; i--) {
        push(&source.stack, i);
    }
    
    printf("\nInitial Setup: %d plates on Source Rod\n", n);
    printf("Goal: Move all plates to Destination Rod\n");
    printf("\n--- Movement Sequence ---\n");
    
    Rod *rod1 = &source;
    Rod *rod2, *rod3;
    
    if (n % 2 == 0) {
        rod2 = &auxiliary;
        rod3 = &destination;
    } else {
        rod2 = &destination;
        rod3 = &auxiliary;
    }
    
    int numMoves = (1 << n) - 1;
    
    for (int i = 1; i <= numMoves; i++) {
        if (i % 3 == 1) {
            movePlate(rod1, rod2, &totalMoves);
        } else if (i % 3 == 2) {
            movePlate(rod1, rod3, &totalMoves);
        } else {
            movePlate(rod2, rod3, &totalMoves);
        }
    }
    
    printf("\n--- Summary ---\n");
    printf("Total Moves: %d\n", totalMoves);
    printf("Minimum moves for %d plates: %d (2^n - 1)\n", n, (1 << n) - 1);
}

int main() {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║     LAB EXPERIMENT 2: STACK IMPLEMENTATION & APPLICATIONS    ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");

    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 1: BASIC STACK OPERATIONS (LIFO)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    Stack basicStack;
    initStack(&basicStack);
    
    printf("\nPushing elements: 10, 20, 30, 40, 50\n");
    push(&basicStack, 10);
    push(&basicStack, 20);
    push(&basicStack, 30);
    push(&basicStack, 40);
    push(&basicStack, 50);
    
    printf("Top element (peek): %d\n", peek(&basicStack));
    printf("Popped: %d\n", pop(&basicStack));
    printf("Popped: %d\n", pop(&basicStack));
    printf("Top element after pops: %d\n", peek(&basicStack));
    printf("Is stack empty? %s\n", isStackEmpty(&basicStack) ? "Yes" : "No");

    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 2a: INFIX TO POSTFIX AND PREFIX CONVERSION\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    char infix1[] = "A+B*C-D";
    char infix2[] = "(A+B)*(C-D)";
    char infix3[] = "A+B*C^D-E";
    char postfix[MAX_SIZE], prefix[MAX_SIZE];
    
    printf("\nExpression 1: %s\n", infix1);
    infixToPostfix(infix1, postfix);
    infixToPrefix(infix1, prefix);
    printf("  Postfix: %s\n", postfix);
    printf("  Prefix:  %s\n", prefix);
    
    printf("\nExpression 2: %s\n", infix2);
    infixToPostfix(infix2, postfix);
    infixToPrefix(infix2, prefix);
    printf("  Postfix: %s\n", postfix);
    printf("  Prefix:  %s\n", prefix);
    
    printf("\nExpression 3: %s\n", infix3);
    infixToPostfix(infix3, postfix);
    infixToPrefix(infix3, prefix);
    printf("  Postfix: %s\n", postfix);
    printf("  Prefix:  %s\n", prefix);

    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 2b: EXPRESSION EVALUATION\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    printf("\n=== POSTFIX EVALUATION ===\n");
    
    char postfixExpr1[] = "23*54*+9-";
    char postfixExpr2[] = "92-3*";
    
    printf("\nPostfix Expression: %s\n", postfixExpr1);
    printf("  Evaluated Result: %d\n", evaluatePostfix(postfixExpr1));
    printf("  Explanation: (2*3) + (5*4) - 9 = 6 + 20 - 9 = 17\n");
    
    printf("\nPostfix Expression: %s\n", postfixExpr2);
    printf("  Evaluated Result: %d\n", evaluatePostfix(postfixExpr2));
    printf("  Explanation: (9-2) * 3 = 21\n");
    
    printf("\n=== PREFIX EVALUATION ===\n");
    
    char prefixExpr1[] = "-+*234*56";
    char prefixExpr2[] = "+*23*45";
    
    printf("\nPrefix Expression: %s\n", prefixExpr1);
    printf("  Evaluated Result: %d\n", evaluatePrefix(prefixExpr1));
    printf("  Explanation: ((2*3)+4) - (5*6) = 10 - 30 = -20\n");
    
    printf("\nPrefix Expression: %s\n", prefixExpr2);
    printf("  Evaluated Result: %d\n", evaluatePrefix(prefixExpr2));
    printf("  Explanation: (2*3) + (4*5) = 6 + 20 = 26\n");

    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 2c: BALANCING SYMBOLS\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    char *exprs[] = {
        "{[()]}",
        "((a+b)*(c-d))",
        "{[(])}",
        "((())",
        "[{()}][]",
        NULL
    };
    
    printf("\nChecking symbol balance:\n");
    for (int i = 0; exprs[i] != NULL; i++) {
        printf("  Expression: %-20s -> %s\n", 
               exprs[i], 
               areSymbolsBalanced(exprs[i]) ? "BALANCED" : "NOT BALANCED");
    }

    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 3: SPACE STATION DOCKING SYSTEM\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    StringStack dockingStack;
    initStringStack(&dockingStack);
    
    pushString(&dockingStack, "ZX12");
    pushString(&dockingStack, "AB34");
    pushString(&dockingStack, "CD56");
    pushString(&dockingStack, "AB34");
    pushString(&dockingStack, "EF78");
    pushString(&dockingStack, "ZX12");
    pushString(&dockingStack, "GH90");
    
    printf("\n=== BEFORE Processing ===");
    displayStringStack(&dockingStack);
    
    processDockingSystem(&dockingStack);
    
    printf("\n=== AFTER Processing (Duplicates Replaced) ===");
    displayStringStack(&dockingStack);

    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 4: TOWERS OF HANOI (ITERATIVE USING STACKS)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    int numPlates = 3;
    printf("\nInput: Number of plates = %d\n", numPlates);
    towersOfHanoiIterative(numPlates);
    
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("END OF LAB EXPERIMENT 2\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    return 0;
}
