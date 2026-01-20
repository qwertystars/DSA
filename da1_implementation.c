#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100
#define MAX_STR_LEN 256

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

int stackSize(Stack *s) {
    return s->top + 1;
}

void printStack(Stack *s, const char *label) {
    printf("%s (Top to Bottom): [", label);
    for (int i = s->top; i >= 0; i--) {
        printf("%d", s->items[i]);
        if (i > 0) printf(", ");
    }
    printf("]\n");
}

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
    int size;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isQueueEmpty(Queue *q) {
    return q->size == 0;
}

int isQueueFull(Queue *q) {
    return q->size == MAX_SIZE;
}

void enqueue(Queue *q, int value) {
    if (isQueueFull(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->items[q->rear] = value;
    q->size++;
}

int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    int value = q->items[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return value;
}

int front(Queue *q) {
    if (isQueueEmpty(q)) {
        return -1;
    }
    return q->items[q->front];
}

int queueSize(Queue *q) {
    return q->size;
}

void printQueue(Queue *q, const char *label) {
    printf("%s: [", label);
    int count = 0;
    int idx = q->front;
    while (count < q->size) {
        printf("%d", q->items[idx]);
        if (count < q->size - 1) printf(", ");
        idx = (idx + 1) % MAX_SIZE;
        count++;
    }
    printf("]\n");
}

typedef struct {
    char name[20];
    int time;
} Passenger;

typedef struct {
    Passenger items[MAX_SIZE];
    int front;
    int rear;
    int size;
} PassengerQueue;

void initPassengerQueue(PassengerQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isPassengerQueueEmpty(PassengerQueue *q) {
    return q->size == 0;
}

void enqueuePassenger(PassengerQueue *q, Passenger p) {
    if (q->size == MAX_SIZE) {
        printf("Passenger Queue Overflow!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->items[q->rear] = p;
    q->size++;
}

Passenger dequeuePassenger(PassengerQueue *q) {
    Passenger empty = {"", 0};
    if (isPassengerQueueEmpty(q)) {
        printf("Passenger Queue Underflow!\n");
        return empty;
    }
    Passenger p = q->items[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return p;
}

Passenger frontPassenger(PassengerQueue *q) {
    Passenger empty = {"", 0};
    if (isPassengerQueueEmpty(q)) {
        return empty;
    }
    return q->items[q->front];
}

int passengerQueueSize(PassengerQueue *q) {
    return q->size;
}

void timeToString(int time, char *str) {
    int hours = time / 60;
    int minutes = time % 60;
    sprintf(str, "%02d:%02d", hours, minutes);
}

void printPassengerQueue(PassengerQueue *q, const char *label) {
    printf("%s: [", label);
    int count = 0;
    int idx = q->front;
    while (count < q->size) {
        char timeStr[10];
        timeToString(q->items[idx].time, timeStr);
        printf("(%s, %s)", q->items[idx].name, timeStr);
        if (count < q->size - 1) printf(", ");
        idx = (idx + 1) % MAX_SIZE;
        count++;
    }
    printf("]\n");
}

int expandAroundCenter(char *s, int left, int right) {
    int n = strlen(s);
    while (left >= 0 && right < n && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

void longestPalindromicSubstring(char *s, char *result) {
    int n = strlen(s);
    if (n == 0) {
        result[0] = '\0';
        return;
    }
    
    int start = 0, maxLen = 1;
    
    for (int i = 0; i < n; i++) {
        int len1 = expandAroundCenter(s, i, i);
        int len2 = expandAroundCenter(s, i, i + 1);
        
        int len = (len1 > len2) ? len1 : len2;
        
        if (len > maxLen) {
            maxLen = len;
            start = i - (len - 1) / 2;
        }
    }
    
    strncpy(result, s + start, maxLen);
    result[maxLen] = '\0';
}

void testLongestPalindrome() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PROBLEM 3: LONGEST PALINDROMIC SUBSTRING\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    char *testCases[] = {"aaaabbaa", "babad", "cbbd", "forgeeksskeegfor", "a", "ac"};
    int numTests = 6;
    
    for (int i = 0; i < numTests; i++) {
        char result[MAX_STR_LEN];
        longestPalindromicSubstring(testCases[i], result);
        printf("Test Case %d:\n", i + 1);
        printf("  Input:  \"%s\"\n", testCases[i]);
        printf("  Output: \"%s\"\n", result);
        printf("  Length: %lu\n\n", strlen(result));
    }
    
    printf("Time Complexity: O(n^2)\n");
    printf("Space Complexity: O(1)\n");
}

void rearrangeMaxMin(int arr[], int n) {
    int steps = n - 1;
    
    while (steps > 0) {
        for (int i = 0; i < steps; i++) {
            int pos = n - 1 - i;
            int temp = arr[pos];
            arr[pos] = arr[pos - 1];
            arr[pos - 1] = temp;
        }
        steps -= 2;
    }
}

void printArray(int arr[], int n, const char *label) {
    printf("%s: [", label);
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

void testRearrangeMaxMin() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PROBLEM 4: ARRAY REARRANGEMENT (MAX-MIN PATTERN)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    int arr1[] = {1, 2, 3, 4, 5, 6};
    int n1 = 6;
    printf("Test Case 1:\n");
    printArray(arr1, n1, "  Input");
    rearrangeMaxMin(arr1, n1);
    printArray(arr1, n1, "  Output");
    printf("  Explanation: max=6, min=1, 2nd_max=5, 2nd_min=2, 3rd_max=4, 3rd_min=3\n\n");
    
    int arr2[] = {1, 2, 3, 4, 5, 6, 7};
    int n2 = 7;
    printf("Test Case 2:\n");
    printArray(arr2, n2, "  Input");
    rearrangeMaxMin(arr2, n2);
    printArray(arr2, n2, "  Output");
    printf("\n");
    
    int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n3 = 10;
    printf("Test Case 3:\n");
    printArray(arr3, n3, "  Input");
    rearrangeMaxMin(arr3, n3);
    printArray(arr3, n3, "  Output");
    printf("\n");
    
    printf("Time Complexity: O(n^2)\n");
    printf("Space Complexity: O(1) - In-place modification\n");
}

void reverseFirstK(Queue *q, int k) {
    if (k <= 0 || k > queueSize(q)) {
        printf("Invalid k value!\n");
        return;
    }
    
    Stack s;
    initStack(&s);
    
    int n = queueSize(q);
    
    printf("\nStep 1: Push first %d elements to stack\n", k);
    for (int i = 0; i < k; i++) {
        int element = dequeue(q);
        push(&s, element);
    }
    printStack(&s, "  Stack");
    printQueue(q, "  Queue");
    
    printf("\nStep 2: Pop from stack and enqueue\n");
    while (!isStackEmpty(&s)) {
        enqueue(q, pop(&s));
    }
    printQueue(q, "  Queue");
    
    printf("\nStep 3: Move remaining %d elements to back\n", n - k);
    for (int i = 0; i < n - k; i++) {
        enqueue(q, dequeue(q));
    }
    printQueue(q, "  Queue");
}

void testReverseFirstK() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PROBLEM 5: REVERSE FIRST K ELEMENTS OF QUEUE\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    Queue q;
    initQueue(&q);
    
    for (int i = 1; i <= 10; i++) {
        enqueue(&q, i * 10);
    }
    
    int k = 5;
    printQueue(&q, "Initial Queue");
    printf("k = %d\n", k);
    
    reverseFirstK(&q, k);
    
    printf("\nFinal Queue: [50, 40, 30, 20, 10, 60, 70, 80, 90, 100]\n");
    printf("\nTime Complexity: O(n)\n");
    printf("Space Complexity: O(k)\n");
}

int isPrime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

void movePrimesToBottom(Stack *s) {
    Stack tempStack, primeStack, compositeStack;
    initStack(&tempStack);
    initStack(&primeStack);
    initStack(&compositeStack);
    
    printf("\nStep 1: Separate primes and composites\n");
    while (!isStackEmpty(s)) {
        int element = pop(s);
        if (isPrime(element)) {
            push(&primeStack, element);
        } else {
            push(&compositeStack, element);
        }
    }
    printStack(&primeStack, "  Primes (reversed)");
    printStack(&compositeStack, "  Composites (reversed)");
    
    printf("\nStep 2-3: Restore original order within groups\n");
    while (!isStackEmpty(&primeStack)) {
        push(&tempStack, pop(&primeStack));
    }
    while (!isStackEmpty(&tempStack)) {
        push(&primeStack, pop(&tempStack));
    }
    
    while (!isStackEmpty(&compositeStack)) {
        push(&tempStack, pop(&compositeStack));
    }
    while (!isStackEmpty(&tempStack)) {
        push(&compositeStack, pop(&tempStack));
    }
    
    printStack(&primeStack, "  Primes (original order)");
    printStack(&compositeStack, "  Composites (original order)");
    
    printf("\nStep 4: Build final stack\n");
    while (!isStackEmpty(&primeStack)) {
        push(s, pop(&primeStack));
    }
    
    while (!isStackEmpty(&compositeStack)) {
        push(s, pop(&compositeStack));
    }
    
    while (!isStackEmpty(s)) {
        push(&tempStack, pop(s));
    }
    while (!isStackEmpty(&tempStack)) {
        push(s, pop(&tempStack));
    }
}

void testMovePrimesToBottom() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PROBLEM 6: MOVE PRIMES TO BOTTOM OF STACK\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    Stack s;
    initStack(&s);
    
    int elements[] = {11, 9, 3, 15, 2, 10, 7, 4};
    int n = 8;
    
    for (int i = 0; i < n; i++) {
        push(&s, elements[i]);
    }
    
    printStack(&s, "Initial Stack");
    
    printf("\nPrime numbers: ");
    for (int i = 0; i < n; i++) {
        if (isPrime(elements[i])) printf("%d ", elements[i]);
    }
    printf("\nComposite numbers: ");
    for (int i = 0; i < n; i++) {
        if (!isPrime(elements[i])) printf("%d ", elements[i]);
    }
    printf("\n");
    
    movePrimesToBottom(&s);
    
    printStack(&s, "\nFinal Stack");
    printf("  Top Section (Composites): 4, 10, 15, 9\n");
    printf("  Bottom Section (Primes): 7, 2, 3, 11\n");
    
    printf("\nTime Complexity: O(n * sqrt(max_element))\n");
    printf("Space Complexity: O(n)\n");
}

void mergeQueuesInsertionSort(PassengerQueue *q1, PassengerQueue *q2, PassengerQueue *result) {
    Passenger passengers[MAX_SIZE];
    int n = 0;
    
    while (!isPassengerQueueEmpty(q1)) {
        passengers[n++] = dequeuePassenger(q1);
    }
    while (!isPassengerQueueEmpty(q2)) {
        passengers[n++] = dequeuePassenger(q2);
    }
    
    printf("  Combined array before sort: [");
    for (int i = 0; i < n; i++) {
        printf("%s", passengers[i].name);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
    
    printf("  Sorting by boarding time...\n");
    for (int i = 1; i < n; i++) {
        Passenger key = passengers[i];
        int j = i - 1;
        
        while (j >= 0 && passengers[j].time > key.time) {
            passengers[j + 1] = passengers[j];
            j--;
        }
        passengers[j + 1] = key;
    }
    
    initPassengerQueue(result);
    for (int i = 0; i < n; i++) {
        enqueuePassenger(result, passengers[i]);
    }
}

void mergeQueuesMergeSort(PassengerQueue *q1, PassengerQueue *q2, PassengerQueue *result) {
    initPassengerQueue(result);
    
    printf("  Merging pre-sorted queues...\n");
    
    while (!isPassengerQueueEmpty(q1) && !isPassengerQueueEmpty(q2)) {
        Passenger p1 = frontPassenger(q1);
        Passenger p2 = frontPassenger(q2);
        
        char time1[10], time2[10];
        timeToString(p1.time, time1);
        timeToString(p2.time, time2);
        
        if (p1.time <= p2.time) {
            printf("    Compare %s(%s) vs %s(%s) -> %s wins\n", 
                   p1.name, time1, p2.name, time2, p1.name);
            enqueuePassenger(result, dequeuePassenger(q1));
        } else {
            printf("    Compare %s(%s) vs %s(%s) -> %s wins\n", 
                   p1.name, time1, p2.name, time2, p2.name);
            enqueuePassenger(result, dequeuePassenger(q2));
        }
    }
    
    while (!isPassengerQueueEmpty(q1)) {
        Passenger p = dequeuePassenger(q1);
        printf("    Remaining: %s\n", p.name);
        enqueuePassenger(result, p);
    }
    
    while (!isPassengerQueueEmpty(q2)) {
        Passenger p = dequeuePassenger(q2);
        printf("    Remaining: %s\n", p.name);
        enqueuePassenger(result, p);
    }
}

void testQueueMerge() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PROBLEM 7: QUEUE MERGE WITH SORTING ALGORITHMS\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    PassengerQueue q1, q1_copy;
    initPassengerQueue(&q1);
    initPassengerQueue(&q1_copy);
    
    Passenger p1 = {"P1", 8 * 60 + 0};
    Passenger p2 = {"P2", 8 * 60 + 10};
    Passenger p3 = {"P3", 8 * 60 + 25};
    
    enqueuePassenger(&q1, p1);
    enqueuePassenger(&q1, p2);
    enqueuePassenger(&q1, p3);
    
    enqueuePassenger(&q1_copy, p1);
    enqueuePassenger(&q1_copy, p2);
    enqueuePassenger(&q1_copy, p3);
    
    PassengerQueue q2, q2_copy;
    initPassengerQueue(&q2);
    initPassengerQueue(&q2_copy);
    
    Passenger p4 = {"P4", 8 * 60 + 5};
    Passenger p5 = {"P5", 8 * 60 + 15};
    
    enqueuePassenger(&q2, p4);
    enqueuePassenger(&q2, p5);
    
    enqueuePassenger(&q2_copy, p4);
    enqueuePassenger(&q2_copy, p5);
    
    printf("Input Queues:\n");
    printPassengerQueue(&q1, "  Q1");
    printPassengerQueue(&q2, "  Q2");
    printf("\n");
    
    printf("=== APPROACH 1: INSERTION SORT ===\n");
    PassengerQueue result1;
    mergeQueuesInsertionSort(&q1, &q2, &result1);
    printPassengerQueue(&result1, "  Result Queue");
    printf("  Time Complexity: O((n+m)^2)\n\n");
    
    printf("=== APPROACH 2: MERGE SORT (Two-way merge) ===\n");
    PassengerQueue result2;
    mergeQueuesMergeSort(&q1_copy, &q2_copy, &result2);
    printPassengerQueue(&result2, "  Result Queue");
    printf("  Time Complexity: O(n+m) for pre-sorted queues\n");
}

void printComplexitySummary() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("COMPLEXITY SUMMARY\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    printf("| %-20s | %-25s | %-15s | %-15s |\n", 
           "Problem", "Algorithm", "Time", "Space");
    printf("|%-22s|%-27s|%-17s|%-17s|\n", 
           "----------------------", "---------------------------", 
           "-----------------", "-----------------");
    printf("| %-20s | %-25s | %-15s | %-15s |\n", 
           "3. Palindrome", "Expand Around Center", "O(n^2)", "O(1)");
    printf("| %-20s | %-25s | %-15s | %-15s |\n", 
           "4. Max-Min Rearrange", "Bubble Swap", "O(n^2)", "O(1)");
    printf("| %-20s | %-25s | %-15s | %-15s |\n", 
           "5. Reverse K Elements", "Stack-based", "O(n)", "O(k)");
    printf("| %-20s | %-25s | %-15s | %-15s |\n", 
           "6. Primes to Bottom", "Multi-stack", "O(n)", "O(n)");
    printf("| %-20s | %-25s | %-15s | %-15s |\n", 
           "7a. Queue Merge", "Insertion Sort", "O((n+m)^2)", "O(n+m)");
    printf("| %-20s | %-25s | %-15s | %-15s |\n", 
           "7b. Queue Merge", "Merge Sort", "O(n+m)", "O(n+m)");
}

int main() {
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║          LAB EXPERIMENT DA1: ALGORITHMS, STRINGS, ARRAYS & ADTs              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
    
    testLongestPalindrome();
    testRearrangeMaxMin();
    testReverseFirstK();
    testMovePrimesToBottom();
    testQueueMerge();
    printComplexitySummary();
    
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("END OF LAB EXPERIMENT DA1\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    return 0;
}
