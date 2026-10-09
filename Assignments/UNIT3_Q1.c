#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int rollNo;
    struct Node *next;
} Node;

Node *head = NULL;

void displayList(void);

Node *createNode(int rollNo) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newNode->rollNo = rollNo;
    newNode->next = NULL;

    return newNode;
}

void createList(int n) {
    Node *tail = NULL;

    for (int i = 0; i < n; i++) {
        int rollNo;

        printf("Enter roll number %d: ", i + 1);
        scanf("%d", &rollNo);

        Node *newNode = createNode(rollNo);

        if (head == NULL)
            head = newNode;
        else
            tail->next = newNode;

        tail = newNode;
    }

    printf("\nList after creation: ");
    displayList();
}

void insertBeginning(int rollNo) {
    Node *newNode = createNode(rollNo);

    newNode->next = head;
    head = newNode;

    printf("Roll number %d inserted at the beginning.\n", rollNo);
    printf("Updated list: ");
    displayList();
}

void insertEnd(int rollNo) {
    Node *newNode = createNode(rollNo);

    if (head == NULL) {
        head = newNode;
    } else {
        Node *temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    printf("Roll number %d inserted at the end.\n", rollNo);
    printf("Updated list: ");
    displayList();
}

void searchRollNo(int rollNo) {
    Node *temp = head;

    while (temp != NULL) {
        if (temp->rollNo == rollNo) {
            printf("Roll number %d found in the list.\n", rollNo);
            printf("Current list: ");
            displayList();
            return;
        }

        temp = temp->next;
    }

    printf("Roll number %d is not available in the list.\n", rollNo);
    printf("Current list: ");
    displayList();
}

void deleteRollNo(int rollNo) {
    Node *temp = head;
    Node *prev = NULL;

    while (temp != NULL && temp->rollNo != rollNo) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Roll number %d is not available. Nothing deleted.\n", rollNo);
        printf("Current list: ");
        displayList();
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    printf("Roll number %d deleted successfully.\n", rollNo);
    printf("Updated list: ");
    displayList();
}

void displayList(void) {
    Node *temp = head;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    while (temp != NULL) {
        printf("%d", temp->rollNo);

        if (temp->next != NULL)
            printf(" -> ");

        temp = temp->next;
    }

    printf("\n");
}

void freeList(void) {
    Node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    int choice, n, rollNo;

    printf("Student Roll Number Management System\n");
    printf("Enter the number of students: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    if (n > 0)
        createList(n);
    else {
        printf("Initial list is empty.\n");
        displayList();
    }

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Search Roll Number\n");
        printf("4. Delete Roll Number\n");
        printf("5. Display List\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter roll number: ");
                scanf("%d", &rollNo);
                insertBeginning(rollNo);
                break;

            case 2:
                printf("Enter roll number: ");
                scanf("%d", &rollNo);
                insertEnd(rollNo);
                break;

            case 3:
                printf("Enter roll number to search: ");
                scanf("%d", &rollNo);
                searchRollNo(rollNo);
                break;

            case 4:
                printf("Enter roll number to delete: ");
                scanf("%d", &rollNo);
                deleteRollNo(rollNo);
                break;

            case 5:
                printf("Current student list: ");
                displayList();
                break;

            case 6:
                freeList();
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}