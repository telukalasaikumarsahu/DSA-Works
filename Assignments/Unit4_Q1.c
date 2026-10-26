/*A system stores unique integer identification numbers using a Binary Search Tree. Write a C
program to insert n values, display inorder, preorder and postorder traversals, search for a
specified value, and report whether it exists. Use the output to explain why inorder traversal
produces sorted values.*/


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
    if (count == MAX) {
        printf("Tree is full!\n");
        return -1;
    }

    tree[count].data = value;
    tree[count].left = -1;
    tree[count].right = -1;

    return count++;
}

void insert(int value) {
    int current, newNode;

    if (root == -1) {
        root = createNode(value);
        return;
    }

    current = root;

    while (1) {
        if (value == tree[current].data) {
            printf("Duplicate value %d ignored.\n", value);
            return;
        }

        if (value < tree[current].data) {
            if (tree[current].left == -1) {
                newNode = createNode(value);
                if (newNode != -1)
                    tree[current].left = newNode;
                return;
            }
            current = tree[current].left;
        } else {
            if (tree[current].right == -1) {
                newNode = createNode(value);
                if (newNode != -1)
                    tree[current].right = newNode;
                return;
            }
            current = tree[current].right;
        }
    }
}

void inorder(int node) {
    if (node != -1) {
        inorder(tree[node].left);
        printf("%d ", tree[node].data);
        inorder(tree[node].right);
    }
}

void preorder(int node) {
    if (node != -1) {
        printf("%d ", tree[node].data);
        preorder(tree[node].left);
        preorder(tree[node].right);
    }
}

void postorder(int node) {
    if (node != -1) {
        postorder(tree[node].left);
        postorder(tree[node].right);
        printf("%d ", tree[node].data);
    }
}

int search(int value) {
    int current = root;

    while (current != -1) {
        if (tree[current].data == value)
            return 1;

        if (value < tree[current].data)
            current = tree[current].left;
        else
            current = tree[current].right;
    }

    return 0;
}

int main() {
    int n, value, i, key;

    printf("Enter number of values: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Enter a value between 1 and %d.\n", MAX);
        return 0;
    }

    printf("Enter %d unique integers:\n", n);

    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        insert(value);
    }

    printf("\nInorder Traversal: ");
    inorder(root);

    printf("\nPreorder Traversal: ");
    preorder(root);

    printf("\nPostorder Traversal: ");
    postorder(root);

    printf("\n\nEnter value to search: ");
    scanf("%d", &key);

    if (search(key))
        printf("%d exists in the BST.\n", key);
    else
        printf("%d does not exist in the BST.\n", key);

    return 0;
}
