/*Extend a Binary Search Tree program to support deletion. The program should create a BST,
delete a user-specified node, correctly handle nodes with zero, one and two children, and display
inorder traversal before and after deletion. Test the program separately for all three deletion cases.*/


#include <stdio.h>

#define MAX 100

struct Node {
    int data;
    int left;
    int right;
};

struct Node tree[MAX];
int count = 0;
int root = -1;

int createNode(int value) {
    if (count >= MAX) {
        printf("Tree is full!\n");
        return -1;
    }

    tree[count].data = value;
    tree[count].left = -1;
    tree[count].right = -1;

    return count++;
}

int insert(int node, int value) {
    int newNode;

    if (node == -1) {
        return createNode(value);
    }

    if (value < tree[node].data) {
        tree[node].left = insert(tree[node].left, value);
    } else if (value > tree[node].data) {
        tree[node].right = insert(tree[node].right, value);
    } else {
        printf("Duplicate value %d ignored.\n", value);
    }

    return node;
}

void inorder(int node) {
    if (node != -1) {
        inorder(tree[node].left);
        printf("%d ", tree[node].data);
        inorder(tree[node].right);
    }
}

int findMin(int node) {
    while (tree[node].left != -1) {
        node = tree[node].left;
    }
    return node;
}

int deleteNode(int node, int key) {
    int temp;

    if (node == -1) {
        return -1;
    }

    if (key < tree[node].data) {
        tree[node].left = deleteNode(tree[node].left, key);
    } else if (key > tree[node].data) {
        tree[node].right = deleteNode(tree[node].right, key);
    } else {
        /* Case 1: No children */
        if (tree[node].left == -1 && tree[node].right == -1) {
            return -1;
        }

        /* Case 2: One child */
        if (tree[node].left == -1) {
            return tree[node].right;
        }

        if (tree[node].right == -1) {
            return tree[node].left;
        }

        /* Case 3: Two children */
        temp = findMin(tree[node].right);
        tree[node].data = tree[temp].data;
        tree[node].right =
            deleteNode(tree[node].right, tree[temp].data);
    }

    return node;
}

int main() {
    int n, value, key, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Enter a number between 1 and %d.\n", MAX);
        return 0;
    }

    printf("Enter unique integer values:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("\nInorder before deletion: ");
    inorder(root);

    printf("\nEnter value to delete: ");
    scanf("%d", &key);

    root = deleteNode(root, key);

    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}
