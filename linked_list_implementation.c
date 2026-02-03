#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// PART 1: SINGLY LINKED LIST IMPLEMENTATION
// ============================================================================

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* insertAtBeginning(Node* head, int data) {
    Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);

    if (head == NULL) return newNode;

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

Node* insertAtPosition(Node* head, int data, int pos) {
    if (pos < 1) {
        printf("Invalid position!\n");
        return head;
    }
    if (pos == 1) return insertAtBeginning(head, data);

    Node* newNode = createNode(data);
    Node* temp = head;

    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of bounds!\n");
        free(newNode);
        return head;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

Node* deleteAtBeginning(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    Node* temp = head;
    head = head->next;
    printf("Deleted: %d\n", temp->data);
    free(temp);
    return head;
}

Node* deleteAtEnd(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    if (head->next == NULL) {
        printf("Deleted: %d\n", head->data);
        free(head);
        return NULL;
    }

    Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    printf("Deleted: %d\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
    return head;
}

Node* deleteByValue(Node* head, int value) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        printf("Deleted: %d\n", temp->data);
        free(temp);
        return head;
    }

    Node* temp = head;
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next != NULL) {
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        printf("Deleted: %d\n", toDelete->data);
        free(toDelete);
    } else {
        printf("Value %d not found!\n", value);
    }
    return head;
}

Node* search(Node* head, int value) {
    Node* temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (temp->data == value) {
            printf("Found %d at position %d\n", value, pos);
            return temp;
        }
        temp = temp->next;
        pos++;
    }
    printf("%d not found in the list\n", value);
    return NULL;
}

int getLength(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void displaySingly(Node* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" → ");
        temp = temp->next;
    }
    printf(" → NULL\n");
}

void freeSinglyList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// ============================================================================
// PART 1: DOUBLY LINKED LIST IMPLEMENTATION
// ============================================================================

typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

DNode* createDNode(int data) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

DNode* insertDAtBeginning(DNode* head, int data) {
    DNode* newNode = createDNode(data);
    if (head != NULL) {
        head->prev = newNode;
    }
    newNode->next = head;
    return newNode;
}

DNode* insertDAtEnd(DNode* head, int data) {
    DNode* newNode = createDNode(data);
    if (head == NULL) return newNode;

    DNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

DNode* insertDAtPosition(DNode* head, int data, int pos) {
    if (pos < 1) {
        printf("Invalid position!\n");
        return head;
    }
    if (pos == 1) return insertDAtBeginning(head, data);

    DNode* newNode = createDNode(data);
    DNode* temp = head;

    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of bounds!\n");
        free(newNode);
        return head;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    return head;
}

DNode* deleteDAtBeginning(DNode* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    DNode* temp = head;
    head = head->next;
    if (head != NULL) head->prev = NULL;
    printf("Deleted: %d\n", temp->data);
    free(temp);
    return head;
}

DNode* deleteDAtEnd(DNode* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    if (head->next == NULL) {
        printf("Deleted: %d\n", head->data);
        free(head);
        return NULL;
    }

    DNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    printf("Deleted: %d\n", temp->data);
    free(temp);
    return head;
}

DNode* deleteDByValue(DNode* head, int value) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }

    DNode* temp = head;
    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value %d not found!\n", value);
        return head;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    printf("Deleted: %d\n", temp->data);
    free(temp);
    return head;
}

void displayDoubly(DNode* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    DNode* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" ⇔ ");
        temp = temp->next;
    }
    printf("\n");
}

void displayReverse(DNode* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    DNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    printf("Reverse: ");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->prev != NULL) printf(" ⇔ ");
        temp = temp->prev;
    }
    printf("\n");
}

void freeDoublyList(DNode* head) {
    DNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// ============================================================================
// PART 2: COUNT TRIPLETS SUMMING TO X
// ============================================================================

int countTripletsSumToX(Node* head, int X) {
    if (head == NULL || head->next == NULL || head->next->next == NULL) {
        return 0;
    }

    int arr[1000];
    int n = 0;
    Node* temp = head;
    while (temp != NULL && n < 1000) {
        arr[n++] = temp->data;
        temp = temp->next;
    }

    int isAscending = (arr[1] > arr[0]);
    int count = 0;

    printf("\nFinding triplets that sum to %d:\n", X);

    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];

            if (sum == X) {
                printf("  Found triplet: (%d, %d, %d)\n", arr[i], arr[left], arr[right]);
                count++;
                left++;
                right--;
            } else if (isAscending && sum < X) {
                left++;
            } else if (!isAscending && sum < X) {
                right--;
            } else if (isAscending && sum > X) {
                right--;
            } else {
                left++;
            }
        }
    }

    return count;
}

void Triplets() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 2: COUNT TRIPLETS SUMMING TO X\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    Node* list = NULL;
    list = insertAtEnd(list, 1);
    list = insertAtEnd(list, 2);
    list = insertAtEnd(list, 4);
    list = insertAtEnd(list, 5);
    list = insertAtEnd(list, 6);
    list = insertAtEnd(list, 8);
    list = insertAtEnd(list, 9);

    printf("\nLinked List: ");
    displaySingly(list);
    printf("Target Sum X = 17\n");

    int result = countTripletsSumToX(list, 17);
    printf("\nTotal triplets found: %d\n", result);

    printf("\nExplanation:");
    printf("\n  Triplet 1: (2, 6, 9) = 2 + 6 + 9 = 17 ✓");
    printf("\n  Triplet 2: (4, 5, 8) = 4 + 5 + 8 = 17 ✓\n");

    freeSinglyList(list);
}

// ============================================================================
// PART 3: MULTIPLY NUMBERS REPRESENTED AS LINKED LISTS
// ============================================================================

long long linkedListToNumber(Node* head) {
    if (head == NULL) return 0;

    long long num = 0;
    Node* temp = head;
    while (temp != NULL) {
        num = num * 10 + temp->data;
        temp = temp->next;
    }
    return num;
}

Node* numberToLinkedList(long long num) {
    if (num == 0) {
        Node* newNode = createNode(0);
        newNode->next = NULL;
        return newNode;
    }

    int digits[20];
    int count = 0;
    long long temp = num;

    while (temp > 0) {
        digits[count++] = temp % 10;
        temp = temp / 10;
    }

    Node* head = NULL;
    for (int i = count - 1; i >= 0; i--) {
        head = insertAtEnd(head, digits[i]);
    }

    return head;
}

Node* multiplyNumbers(Node* num1, Node* num2) {
    printf("\nMultiplication Steps:\n");
    long long n1 = linkedListToNumber(num1);
    long long n2 = linkedListToNumber(num2);
    long long product = n1 * n2;

    printf("  Extracted number 1: %lld\n", n1);
    printf("  Extracted number 2: %lld\n", n2);
    printf("  Product: %lld = %lld × %lld\n", product, n1, n2);

    return numberToLinkedList(product);
}

void Multiply() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 3: MULTIPLY NUMBERS AS LINKED LISTS\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    printf("\n=== Example 1 ===");
    Node* num1 = NULL;
    num1 = insertAtEnd(num1, 3);
    num1 = insertAtEnd(num1, 7);
    num1 = insertAtEnd(num1, 1);

    Node* num2 = NULL;
    num2 = insertAtEnd(num2, 1);
    num2 = insertAtEnd(num2, 5);

    printf("\nNumber 1: ");
    displaySingly(num1);
    printf("Number 2: ");
    displaySingly(num2);

    Node* result = multiplyNumbers(num1, num2);
    printf("Result:   ");
    displaySingly(result);

    printf("\nVerification: 371 × 15 = 5565 ✓\n");

    freeSinglyList(num1);
    freeSinglyList(num2);
    freeSinglyList(result);
}

// ============================================================================
// PART 4: MOVE NODES X AND Y BETWEEN SINGLY LINKED LISTS
// ============================================================================

void moveNodesBetweenLists(Node** L1, Node** L2, int X, int Y) {
    if (*L1 == NULL) {
        printf("List L1 is empty!\n");
        return;
    }

    Node *nodeX = NULL, *nodeY = NULL;
    Node *prevX = NULL, *prevY = NULL;
    Node *temp = *L1, *prev = NULL;

    while (temp != NULL) {
        if (temp->data == X && nodeX == NULL) {
            nodeX = temp;
            prevX = prev;
        }
        if (temp->data == Y && nodeY == NULL) {
            nodeY = temp;
            prevY = prev;
        }
        prev = temp;
        temp = temp->next;
    }

    if (nodeX == NULL || nodeY == NULL) {
        printf("One or both nodes not found in L1!\n");
        return;
    }

    printf("\n=== Moving Nodes Between Lists ===\n");
    printf("Original L1: ");
    displaySingly(*L1);
    printf("Original L2: ");
    displaySingly(*L2);
    printf("Moving X=%d to head of L2, Y=%d to end of L2\n", X, Y);

    if (prevX == NULL) {
        *L1 = nodeX->next;
    } else {
        prevX->next = nodeX->next;
    }
    printf("  Removed X=%d from L1\n", X);

    if (prevY == nodeX) {
        prevY = nodeX;
    } else if (prevY == NULL && nodeY == *L1) {
        *L1 = nodeY->next;
    } else if (prevY != NULL) {
        prevY->next = nodeY->next;
    } else {
        *L1 = nodeY->next;
    }
    printf("  Removed Y=%d from L1\n", Y);

    nodeX->next = *L2;
    *L2 = nodeX;
    printf("  Inserted X=%d at beginning of L2\n", X);

    nodeY->next = NULL;
    if (*L2 == NULL) {
        *L2 = nodeY;
    } else {
        Node* tail = *L2;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = nodeY;
    }
    printf("  Inserted Y=%d at end of L2\n", Y);

    printf("\nModified L1: ");
    displaySingly(*L1);
    printf("Modified L2: ");
    displaySingly(*L2);
}

void MoveNodes() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 4: MOVE NODES BETWEEN SINGLY LINKED LISTS\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    Node* L1 = NULL;
    L1 = insertAtEnd(L1, 9);
    L1 = insertAtEnd(L1, 10);
    L1 = insertAtEnd(L1, 11);
    L1 = insertAtEnd(L1, 12);
    L1 = insertAtEnd(L1, 13);
    L1 = insertAtEnd(L1, 14);

    Node* L2 = NULL;
    L2 = insertAtEnd(L2, 100);
    L2 = insertAtEnd(L2, 101);
    L2 = insertAtEnd(L2, 102);
    L2 = insertAtEnd(L2, 103);

    moveNodesBetweenLists(&L1, &L2, 11, 14);

    freeSinglyList(L1);
    freeSinglyList(L2);
}

// ============================================================================
// PART 5: MOVE SONGS BETWEEN PLAYLISTS (DOUBLY LINKED LIST)
// ============================================================================

void moveSongsBetweenPlaylists(DNode** L1, DNode** L2, int X, int Y) {
    if (*L1 == NULL) {
        printf("Playlist L1 is empty!\n");
        return;
    }

    DNode *songX = NULL, *songY = NULL;
    DNode *temp = *L1;

    while (temp != NULL) {
        if (temp->data == X && songX == NULL) {
            songX = temp;
        }
        if (temp->data == Y && songY == NULL) {
            songY = temp;
        }
        temp = temp->next;
    }

    if (songX == NULL || songY == NULL) {
        printf("One or both songs not found in L1!\n");
        return;
    }

    printf("\n=== Moving Songs Between Playlists ===\n");
    printf("Original L1: ");
    displayDoubly(*L1);
    printf("Original L2: ");
    displayDoubly(*L2);
    printf("Moving song %d to head of L2, song %d to end of L2\n", X, Y);

    if (songX->prev != NULL) {
        songX->prev->next = songX->next;
    } else {
        *L1 = songX->next;
    }
    if (songX->next != NULL) {
        songX->next->prev = songX->prev;
    }
    printf("  Removed song %d from L1\n", X);

    if (songY->prev != NULL) {
        songY->prev->next = songY->next;
    } else {
        *L1 = songY->next;
    }
    if (songY->next != NULL) {
        songY->next->prev = songY->prev;
    }
    printf("  Removed song %d from L1\n", Y);

    songX->prev = NULL;
    songX->next = *L2;
    if (*L2 != NULL) {
        (*L2)->prev = songX;
    }
    *L2 = songX;
    printf("  Inserted song %d at beginning of L2\n", X);

    DNode* tail = *L2;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = songY;
    songY->prev = tail;
    songY->next = NULL;
    printf("  Inserted song %d at end of L2\n", Y);

    printf("\nModified L1: ");
    displayDoubly(*L1);
    printf("Modified L2: ");
    displayDoubly(*L2);
}

void MoveSongs() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 5: MOVE SONGS BETWEEN PLAYLISTS (DOUBLY LINKED LIST)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    DNode* L1 = NULL;
    L1 = insertDAtEnd(L1, 201);
    L1 = insertDAtEnd(L1, 202);
    L1 = insertDAtEnd(L1, 203);
    L1 = insertDAtEnd(L1, 204);
    L1 = insertDAtEnd(L1, 205);
    L1 = insertDAtEnd(L1, 206);

    DNode* L2 = NULL;
    L2 = insertDAtEnd(L2, 301);
    L2 = insertDAtEnd(L2, 302);
    L2 = insertDAtEnd(L2, 303);
    L2 = insertDAtEnd(L2, 304);

    moveSongsBetweenPlaylists(&L1, &L2, 203, 206);

    freeDoublyList(L1);
    freeDoublyList(L2);
}

// ============================================================================
// DEMONSTRATION FUNCTIONS - SINGLY LINKED LIST
// ============================================================================

void SinglyLinkedList() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 1a: SINGLY LINKED LIST OPERATIONS\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

    Node* head = NULL;

    printf("=== Insert Operations ===\n");
    printf("Inserting at end: 10, 20, 30, 40, 50\n");
    head = insertAtEnd(head, 10);
    head = insertAtEnd(head, 20);
    head = insertAtEnd(head, 30);
    head = insertAtEnd(head, 40);
    head = insertAtEnd(head, 50);
    displaySingly(head);

    printf("\nInserting at beginning: 5\n");
    head = insertAtBeginning(head, 5);
    displaySingly(head);

    printf("\nInserting 25 at position 4\n");
    head = insertAtPosition(head, 25, 4);
    displaySingly(head);

    printf("\nList length: %d\n", getLength(head));

    printf("\n=== Search Operation ===\n");
    search(head, 25);
    search(head, 99);

    printf("\n=== Delete Operations ===\n");
    printf("Deleting by value: 30\n");
    head = deleteByValue(head, 30);
    displaySingly(head);

    printf("\nDeleting at beginning\n");
    head = deleteAtBeginning(head);
    displaySingly(head);

    printf("\nDeleting at end\n");
    head = deleteAtEnd(head);
    displaySingly(head);

    freeSinglyList(head);
}

// ============================================================================
// DEMONSTRATION FUNCTIONS - DOUBLY LINKED LIST
// ============================================================================

void DoublyLinkedList() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("PART 1b: DOUBLY LINKED LIST OPERATIONS\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

    DNode* head = NULL;

    printf("=== Insert Operations ===\n");
    printf("Inserting at end: 10, 20, 30, 40, 50\n");
    head = insertDAtEnd(head, 10);
    head = insertDAtEnd(head, 20);
    head = insertDAtEnd(head, 30);
    head = insertDAtEnd(head, 40);
    head = insertDAtEnd(head, 50);
    displayDoubly(head);
    displayReverse(head);

    printf("\nInserting at beginning: 5\n");
    head = insertDAtBeginning(head, 5);
    displayDoubly(head);

    printf("\nInserting 25 at position 4\n");
    head = insertDAtPosition(head, 25, 4);
    displayDoubly(head);

    printf("\n=== Delete Operations ===\n");
    printf("Deleting by value: 30\n");
    head = deleteDByValue(head, 30);
    displayDoubly(head);

    printf("\nDeleting at beginning\n");
    head = deleteDAtBeginning(head);
    displayDoubly(head);

    printf("\nDeleting at end\n");
    head = deleteDAtEnd(head);
    displayDoubly(head);

    freeDoublyList(head);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║     LAB EXPERIMENT 4: LINKED LIST IMPLEMENTATION            ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");

    SinglyLinkedList();
    DoublyLinkedList();

    Triplets();

    Multiply();

    MoveNodes();

    MoveSongs();

    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("END OF LAB EXPERIMENT 4\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    return 0;
}
