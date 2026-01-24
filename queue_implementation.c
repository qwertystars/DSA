#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// ============================================================================
// PART 1: LINEAR QUEUE IMPLEMENTATION
// ============================================================================

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return q->rear == MAX_SIZE - 1;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow!\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[++q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

int front(Queue *q) {
    if (isEmpty(q)) {
        return -1;
    }
    return q->items[q->front];
}

int rear(Queue *q) {
    if (isEmpty(q)) {
        return -1;
    }
    return q->items[q->rear];
}

int size(Queue *q) {
    if (isEmpty(q)) return 0;
    return q->rear - q->front + 1;
}

void displayQueueInline(Queue *q) {
    if (isEmpty(q)) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d", q->items[i]);
        if (i < q->rear) printf(", ");
    }
    printf("]\n");
}

void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue: ");
    displayQueueInline(q);
    printf("Front: %d, Rear: %d\n", q->items[q->front], q->items[q->rear]);
}

// ============================================================================
// PART 2a: CIRCULAR QUEUE IMPLEMENTATION
// ============================================================================

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
    int capacity;
} CircularQueue;

void initCircularQueue(CircularQueue *cq, int capacity) {
    cq->front = -1;
    cq->rear = -1;
    cq->capacity = capacity;
}

int isCircularQueueEmpty(CircularQueue *cq) {
    return cq->front == -1;
}

int isCircularQueueFull(CircularQueue *cq) {
    return (cq->rear + 1) % cq->capacity == cq->front;
}

void enqueueCircular(CircularQueue *cq, int value) {
    if (isCircularQueueFull(cq)) {
        printf("Circular Queue Overflow!\n");
        return;
    }
    if (cq->front == -1) {
        cq->front = 0;
    }
    cq->rear = (cq->rear + 1) % cq->capacity;
    cq->items[cq->rear] = value;
    printf("Enqueued %d at position %d\n", value, cq->rear);
}

int dequeueCircular(CircularQueue *cq) {
    if (isCircularQueueEmpty(cq)) {
        printf("Circular Queue Underflow!\n");
        return -1;
    }
    int item = cq->items[cq->front];
    printf("Dequeued %d from position %d\n", item, cq->front);
    
    if (cq->front == cq->rear) {
        cq->front = -1;
        cq->rear = -1;
    } else {
        cq->front = (cq->front + 1) % cq->capacity;
    }
    return item;
}

int circularQueueSize(CircularQueue *cq) {
    if (isCircularQueueEmpty(cq)) return 0;
    if (cq->rear >= cq->front) {
        return cq->rear - cq->front + 1;
    }
    return cq->capacity - cq->front + cq->rear + 1;
}

void displayCircularQueue(CircularQueue *cq) {
    if (isCircularQueueEmpty(cq)) {
        printf("Circular Queue is empty!\n");
        return;
    }
    printf("Circular Queue: [");
    int i = cq->front;
    while (1) {
        printf("%d", cq->items[i]);
        if (i == cq->rear) break;
        printf(", ");
        i = (i + 1) % cq->capacity;
    }
    printf("]\n");
    printf("Front Index: %d, Rear Index: %d\n", cq->front, cq->rear);
}

// ============================================================================
// PART 2b: DOUBLE-ENDED QUEUE (DEQUE) IMPLEMENTATION
// ============================================================================

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
    int capacity;
} Deque;

void initDeque(Deque *dq, int capacity) {
    dq->front = -1;
    dq->rear = -1;
    dq->capacity = capacity;
}

int isDequeEmpty(Deque *dq) {
    return dq->front == -1;
}

int isDequeFull(Deque *dq) {
    return (dq->front == 0 && dq->rear == dq->capacity - 1) ||
           (dq->front == dq->rear + 1);
}

void insertFront(Deque *dq, int value) {
    if (isDequeFull(dq)) {
        printf("Deque Overflow!\n");
        return;
    }
    
    if (dq->front == -1) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = dq->capacity - 1;
    } else {
        dq->front--;
    }
    
    dq->items[dq->front] = value;
    printf("Inserted %d at front (index %d)\n", value, dq->front);
}

void insertRear(Deque *dq, int value) {
    if (isDequeFull(dq)) {
        printf("Deque Overflow!\n");
        return;
    }
    
    if (dq->front == -1) {
        dq->front = 0;
        dq->rear = 0;
    } else if (dq->rear == dq->capacity - 1) {
        dq->rear = 0;
    } else {
        dq->rear++;
    }
    
    dq->items[dq->rear] = value;
    printf("Inserted %d at rear (index %d)\n", value, dq->rear);
}

int deleteFront(Deque *dq) {
    if (isDequeEmpty(dq)) {
        printf("Deque Underflow!\n");
        return -1;
    }
    
    int item = dq->items[dq->front];
    printf("Deleted %d from front (index %d)\n", item, dq->front);
    
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->front == dq->capacity - 1) {
        dq->front = 0;
    } else {
        dq->front++;
    }
    
    return item;
}

int deleteRear(Deque *dq) {
    if (isDequeEmpty(dq)) {
        printf("Deque Underflow!\n");
        return -1;
    }
    
    int item = dq->items[dq->rear];
    printf("Deleted %d from rear (index %d)\n", item, dq->rear);
    
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    } else if (dq->rear == 0) {
        dq->rear = dq->capacity - 1;
    } else {
        dq->rear--;
    }
    
    return item;
}

int getFront(Deque *dq) {
    if (isDequeEmpty(dq)) {
        return -1;
    }
    return dq->items[dq->front];
}

int getRear(Deque *dq) {
    if (isDequeEmpty(dq)) {
        return -1;
    }
    return dq->items[dq->rear];
}

void displayDeque(Deque *dq) {
    if (isDequeEmpty(dq)) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deque: [");
    int i = dq->front;
    while (1) {
        printf("%d", dq->items[i]);
        if (i == dq->rear) break;
        printf(", ");
        i = (i + 1) % dq->capacity;
    }
    printf("]\n");
    printf("Front: %d (index %d), Rear: %d (index %d)\n", 
           dq->items[dq->front], dq->front, 
           dq->items[dq->rear], dq->rear);
}

// ============================================================================
// PART 3: QUEUE INTERLEAVING
// ============================================================================

void interleaveQueue(Queue *q) {
    int n = size(q);
    if (n == 0 || n % 2 != 0) {
        printf("Queue must have even number of elements!\n");
        return;
    }
    
    int half = n / 2;
    Queue tempQ;
    initQueue(&tempQ);
    
    printf("\nOriginal Queue: ");
    displayQueueInline(q);
    
    printf("\nStep 1: Moving first half to temporary queue\n");
    for (int i = 0; i < half; i++) {
        int elem = dequeue(q);
        enqueue(&tempQ, elem);
        printf("  Moved %d to tempQ\n", elem);
    }
    
    printf("  tempQ (first half): ");
    displayQueueInline(&tempQ);
    printf("  Main Queue (second half): ");
    displayQueueInline(q);
    
    printf("\nStep 2: Interleaving\n");
    while (!isEmpty(&tempQ)) {
        int first = dequeue(&tempQ);
        int second = dequeue(q);
        enqueue(q, first);
        enqueue(q, second);
        printf("  Enqueued %d (first half), then %d (second half)\n", first, second);
    }
    
    printf("\nInterleaved Queue: ");
    displayQueueInline(q);
}

// ============================================================================
// PART 4: REVERSE FIRST K ELEMENTS
// ============================================================================

int getSize(Queue *q) {
    if (isEmpty(q)) return 0;
    return q->rear - q->front + 1;
}

void reverseFirstK(Queue *q, int k) {
    int n = getSize(q);
    
    if (k <= 0 || k > n) {
        printf("Invalid k value! (k must be between 1 and %d)\n", n);
        return;
    }
    
    printf("\n=== Reversing First %d Elements ===\n", k);
    printf("Original Queue: ");
    displayQueueInline(q);
    
    Queue auxQ;
    initQueue(&auxQ);
    
    printf("\nStep 1: Extract first %d elements\n", k);
    for (int i = 0; i < k; i++) {
        int elem = dequeue(q);
        enqueue(&auxQ, elem);
        printf("  Extracted: %d\n", elem);
    }
    
    printf("  auxQ: ");
    displayQueueInline(&auxQ);
    printf("  Remaining in Q: ");
    displayQueueInline(q);
    
    Queue reverseQ;
    initQueue(&reverseQ);
    
    printf("\nStep 2: Reverse extracted elements using queue operations\n");
    
    while (!isEmpty(&auxQ)) {
        int cycles = getSize(&auxQ) - 1;
        for (int i = 0; i < cycles; i++) {
            int temp = dequeue(&auxQ);
            enqueue(&auxQ, temp);
        }

        int lastElem = dequeue(&auxQ);
        enqueue(&reverseQ, lastElem);
        printf("  Moved %d to reverseQ (was last in auxQ)\n", lastElem);
    }
    
    printf("  reverseQ (reversed first k): ");
    displayQueueInline(&reverseQ);
    
    printf("\nStep 3: Enqueue reversed elements to main queue\n");
    while (!isEmpty(&reverseQ)) {
        int elem = dequeue(&reverseQ);
        enqueue(q, elem);
        printf("  Enqueued: %d\n", elem);
    }

    int remaining = n - k;
    printf("\nStep 4: Move remaining %d elements to end\n", remaining);
    for (int i = 0; i < remaining; i++) {
        int elem = dequeue(q);
        enqueue(q, elem);
        printf("  Cycled: %d\n", elem);
    }
    
    printf("\nFinal Queue: ");
    displayQueueInline(q);
}

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

void demonstrateLinearQueue() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 1: LINEAR QUEUE OPERATIONS (FIFO)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    Queue q;
    initQueue(&q);
    
    printf("Enqueueing elements: 10, 20, 30, 40, 50\n");
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);
    
    displayQueue(&q);
    
    printf("\nDequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    
    printf("Queue after dequeues: ");
    displayQueueInline(&q);
    printf("Front element: %d\n", front(&q));
    printf("Rear element: %d\n", rear(&q));
    printf("Is queue empty? %s\n", isEmpty(&q) ? "Yes" : "No");
    printf("Queue size: %d\n", size(&q));
}

void demonstrateCircularQueue() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 2a: CIRCULAR QUEUE\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    CircularQueue cq;
    initCircularQueue(&cq, 5);
    
    printf("Initializing Circular Queue with capacity 5\n\n");
    
    enqueueCircular(&cq, 10);
    enqueueCircular(&cq, 20);
    enqueueCircular(&cq, 30);
    displayCircularQueue(&cq);
    
    printf("\n");
    dequeueCircular(&cq);
    dequeueCircular(&cq);
    displayCircularQueue(&cq);
    
    printf("\n");
    enqueueCircular(&cq, 40);
    enqueueCircular(&cq, 50);
    enqueueCircular(&cq, 60);
    displayCircularQueue(&cq);
    
    printf("\nDemonstrating circular nature:\n");
    printf("Queue size: %d\n", circularQueueSize(&cq));
    printf("Front element: %d, Rear element: %d\n", 
           cq.items[cq.front], cq.items[cq.rear]);
}

void demonstrateDeque() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 2b: DOUBLE-ENDED QUEUE (DEQUE)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    Deque dq;
    initDeque(&dq, 6);
    
    printf("Initializing Deque with capacity 6\n\n");
    
    insertRear(&dq, 10);
    insertRear(&dq, 20);
    insertFront(&dq, 5);
    insertRear(&dq, 30);
    displayDeque(&dq);
    
    printf("\n");
    deleteFront(&dq);
    deleteRear(&dq);
    displayDeque(&dq);
    
    printf("\n");
    insertFront(&dq, 1);
    insertRear(&dq, 40);
    displayDeque(&dq);
}

void demonstrateInterleaving() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 3: QUEUE INTERLEAVING\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    printf("\n=== Test Case 1 ===");
    Queue q1;
    initQueue(&q1);
    enqueue(&q1, 2);
    enqueue(&q1, 4);
    enqueue(&q1, 3);
    enqueue(&q1, 1);
    interleaveQueue(&q1);
    
    printf("\n=== Test Case 2 ===");
    Queue q2;
    initQueue(&q2);
    enqueue(&q2, 1);
    enqueue(&q2, 2);
    enqueue(&q2, 3);
    enqueue(&q2, 4);
    enqueue(&q2, 5);
    enqueue(&q2, 6);
    interleaveQueue(&q2);
}

void demonstrateReverseK() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 4: REVERSE FIRST K ELEMENTS\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    Queue q;
    initQueue(&q);
    
    for (int i = 1; i <= 10; i++) {
        enqueue(&q, i * 10);
    }
    
    reverseFirstK(&q, 5);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║     LAB EXPERIMENT 3: QUEUE IMPLEMENTATION & APPLICATIONS    ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    
    demonstrateLinearQueue();
    demonstrateCircularQueue();
    demonstrateDeque();
    demonstrateInterleaving();
    demonstrateReverseK();
    
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("END OF LAB EXPERIMENT 3\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    return 0;
}
