#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

struct Node* buildBST(int arr[], int n) {
    struct Node* root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);
    return root;
}

void freeTree(struct Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int isBSTUtil(struct Node* node, int min, int max) {
    if (node == NULL) return 1;
    if (node->data <= min || node->data >= max) return 0;
    return isBSTUtil(node->left, min, node->data) &&
           isBSTUtil(node->right, node->data, max);
}

int isBST(struct Node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

void testQ1() {
    printf("========== Q1: Check if Binary Tree is a Valid BST ==========\n");

    int arr1[] = {40, 20, 60, 10, 30, 50, 70};
    struct Node* tree1 = buildBST(arr1, 7);
    printf("Tree (level order): 40 20 60 10 30 50 70\n");
    printf("Result: The given tree is %sa valid Binary Search Tree\n\n",
           isBST(tree1) ? "" : "NOT ");

    struct Node* tree2 = createNode(40);
    tree2->left = createNode(20);
    tree2->right = createNode(60);
    tree2->left->left = createNode(10);
    tree2->left->right = createNode(100);
    printf("Tree with node 100 as right child of 20 (under 40):\n");
    printf("Result: The given tree is %sa valid Binary Search Tree\n\n",
           isBST(tree2) ? "" : "NOT ");

    freeTree(tree1);
    freeTree(tree2);
}

int kthSmallestUtil(struct Node* root, int* k) {
    if (root == NULL) return -1;
    int left = kthSmallestUtil(root->left, k);
    if (left != -1) return left;
    (*k)--;
    if (*k == 0) return root->data;
    return kthSmallestUtil(root->right, k);
}

int kthSmallest(struct Node* root, int k) {
    return kthSmallestUtil(root, &k);
}

void testQ2() {
    printf("========== Q2: Kth Smallest Element in BST ==========\n");
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    struct Node* root = buildBST(arr, 7);

    int k = 3;
    printf("BST elements: 50 30 70 20 40 60 80\n");
    printf("k = %d\n", k);
    printf("The %d%s smallest element is %d\n\n", k,
           k == 1 ? "st" : k == 2 ? "nd" : k == 3 ? "rd" : "th",
           kthSmallest(root, k));

    freeTree(root);
}

struct Node* lca(struct Node* root, int n1, int n2) {
    if (root == NULL) return NULL;
    if (root->data > n1 && root->data > n2)
        return lca(root->left, n1, n2);
    if (root->data < n1 && root->data < n2)
        return lca(root->right, n1, n2);
    return root;
}

void testQ3() {
    printf("========== Q3: Lowest Common Ancestor in BST ==========\n");
    int arr[] = {40, 20, 60, 10, 30, 50, 70};
    struct Node* root = buildBST(arr, 7);

    int n1 = 10, n2 = 30;
    struct Node* ancestor = lca(root, n1, n2);
    printf("BST elements: 40 20 60 10 30 50 70\n");
    printf("node1 = %d, node2 = %d\n", n1, n2);
    printf("Lowest Common Ancestor: %d\n\n", ancestor->data);

    freeTree(root);
}

void bstToDLL(struct Node* root, struct Node** head, struct Node** prev) {
    if (root == NULL) return;
    bstToDLL(root->left, head, prev);
    if (*prev == NULL)
        *head = root;
    else {
        root->left = *prev;
        (*prev)->right = root;
    }
    *prev = root;
    bstToDLL(root->right, head, prev);
}

void printDLL(struct Node* head) {
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d", curr->data);
        if (curr->right != NULL) printf(" <-> ");
        curr = curr->right;
    }
    printf("\n");
}

void freeDLL(struct Node* head) {
    while (head) {
        struct Node* temp = head;
        head = head->right;
        free(temp);
    }
}

void testQ4() {
    printf("========== Q4: BST to Sorted Doubly Linked List ==========\n");
    int arr[] = {50, 30, 70, 20, 40, 60};
    struct Node* root = buildBST(arr, 6);

    struct Node* head = NULL;
    struct Node* prev = NULL;
    bstToDLL(root, &head, &prev);

    printf("BST elements: 50 30 70 20 40 60\n");
    printf("Doubly Linked List:\n");
    printDLL(head);
    printf("\n");

    freeDLL(head);
}

int countInRange(struct Node* root, int L, int R) {
    if (root == NULL) return 0;
    if (root->data >= L && root->data <= R)
        return 1 + countInRange(root->left, L, R) + countInRange(root->right, L, R);
    else if (root->data < L)
        return countInRange(root->right, L, R);
    else
        return countInRange(root->left, L, R);
}

void testQ5() {
    printf("========== Q5: Count Nodes in Range [L, R] ==========\n");
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    struct Node* root = buildBST(arr, 7);

    int L = 25, R = 65;
    printf("BST elements: 50 30 70 20 40 60 80\n");
    printf("Range: [%d, %d]\n", L, R);
    printf("Number of nodes in range [%d, %d]: %d\n\n", L, R, countInRange(root, L, R));

    freeTree(root);
}
int isIdentical(struct Node* r1, struct Node* r2) {
    if (r1 == NULL && r2 == NULL) return 1;
    if (r1 == NULL || r2 == NULL) return 0;
    return (r1->data == r2->data) &&
           isIdentical(r1->left, r2->left) &&
           isIdentical(r1->right, r2->right);
}

void testQ6() {
    printf("========== Q6: Check if Two BSTs are Identical ==========\n");

    int arr1[] = {40, 20, 60, 10, 30};
    int arr2[] = {40, 20, 60, 10, 30};
    struct Node* bst1 = buildBST(arr1, 5);
    struct Node* bst2 = buildBST(arr2, 5);

    printf("BST1 elements: 40 20 60 10 30\n");
    printf("BST2 elements: 40 20 60 10 30\n");
    printf("Result: Both BSTs are %s\n\n",
           isIdentical(bst1, bst2) ? "identical" : "NOT identical");

    int arr3[] = {40, 20, 60, 10, 35};
    struct Node* bst3 = buildBST(arr3, 5);
    printf("BST1 elements: 40 20 60 10 30\n");
    printf("BST3 elements: 40 20 60 10 35\n");
    printf("Result: Both BSTs are %s\n\n",
           isIdentical(bst1, bst3) ? "identical" : "NOT identical");

    freeTree(bst1);
    freeTree(bst2);
    freeTree(bst3);
}

struct Node* inorderSuccessor(struct Node* root, int key) {
    struct Node* successor = NULL;
    while (root != NULL) {
        if (key < root->data) {
            successor = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return successor;
}

void testQ7() {
    printf("========== Q7: Inorder Successor in BST ==========\n");
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    struct Node* root = buildBST(arr, 7);

    int key = 40;
    struct Node* succ = inorderSuccessor(root, key);
    printf("BST elements: 50 30 70 20 40 60 80\n");
    printf("Key: %d\n", key);
    if (succ)
        printf("Inorder Successor of %d is %d\n\n", key, succ->data);
    else
        printf("No inorder successor found for %d\n\n", key);

    freeTree(root);
}

int main() {
    printf("===============================================\n");
    printf("       LAB EXPERIMENT 5 - BST Problems        \n");
    printf("===============================================\n\n");

    testQ1();
    testQ2();
    testQ3();
    testQ4();
    testQ5();
    testQ6();
    testQ7();

    printf("===============================================\n");
    printf("          All tests completed.                 \n");
    printf("===============================================\n");

    return 0;
}
