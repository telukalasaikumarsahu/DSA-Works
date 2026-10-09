#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100

typedef struct Node {
    char page[MAX_TITLE];
    struct Node *prev;
    struct Node *next;
} Node;

Node *head = NULL;
Node *tail = NULL;
Node *current = NULL;

Node *createNode(const char *page) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(newNode->page, page, MAX_TITLE - 1);
    newNode->page[MAX_TITLE - 1] = '\0';
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

void insertPage(const char *page) {
    Node *newNode = createNode(page);

    if (head == NULL) {
        head = tail = current = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        current = newNode;
    }

    printf("Page \"%s\" inserted successfully.\n", page);
}

void moveForward(void) {
    if (current == NULL) {
        printf("No pages available.\n");
    } else if (current->next == NULL) {
        printf("Already at the last page: \"%s\".\n", current->page);
    } else {
        current = current->next;
        printf("Moved forward to: \"%s\"\n", current->page);
    }
}

void moveBackward(void) {
    if (current == NULL) {
        printf("No pages available.\n");
    } else if (current->prev == NULL) {
        printf("Already at the first page: \"%s\".\n", current->page);
    } else {
        current = current->prev;
        printf("Moved backward to: \"%s\"\n", current->page);
    }
}

void deletePage(const char *page) {
    Node *temp = head;

    while (temp != NULL && strcmp(temp->page, page) != 0)
        temp = temp->next;

    if (temp == NULL) {
        printf("Page \"%s\" is not available.\n", page);
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    else
        tail = temp->prev;

    if (current == temp) {
        if (temp->next != NULL)
            current = temp->next;
        else
            current = temp->prev;
    }

    free(temp);

    printf("Page \"%s\" deleted successfully.\n", page);
}

void displayForward(void) {
    Node *temp = head;

    if (head == NULL) {
        printf("No pages in history.\n");
        return;
    }

    printf("Pages from first to last:\n");

    while (temp != NULL) {
        if (temp == current)
            printf("[ %s ]", temp->page);
        else
            printf("%s", temp->page);

        if (temp->next != NULL)
            printf(" <-> ");

        temp = temp->next;
    }

    printf("\n");
}

void displayBackward(void) {
    Node *temp = tail;

    if (tail == NULL) {
        printf("No pages in history.\n");
        return;
    }

    printf("Pages from last to first:\n");

    while (temp != NULL) {
        if (temp == current)
            printf("[ %s ]", temp->page);
        else
            printf("%s", temp->page);

        if (temp->prev != NULL)
            printf(" <-> ");

        temp = temp->prev;
    }

    printf("\n");
}

void displayCurrentPage(void) {
    if (current == NULL)
        printf("No current page.\n");
    else
        printf("Current page: \"%s\"\n", current->page);
}

void freeHistory(void) {
    Node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    tail = NULL;
    current = NULL;
}

int main(void) {
    int choice;
    char page[MAX_TITLE];

    printf("Web Page Navigation System\n");

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Insert New Page\n");
        printf("2. Move Forward\n");
        printf("3. Move Backward\n");
        printf("4. Delete Page\n");
        printf("5. Display First to Last\n");
        printf("6. Display Last to First\n");
        printf("7. Display Current Page\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter page name or URL: ");
                fgets(page, sizeof(page), stdin);
                page[strcspn(page, "\n")] = '\0';

                if (strlen(page) == 0) {
                    printf("Page name cannot be empty.\n");
                    break;
                }

                insertPage(page);
                break;

            case 2:
                moveForward();
                break;

            case 3:
                moveBackward();
                break;

            case 4:
                printf("Enter page name or URL to delete: ");
                fgets(page, sizeof(page), stdin);
                page[strcspn(page, "\n")] = '\0';

                deletePage(page);
                break;

            case 5:
                displayForward();
                break;

            case 6:
                displayBackward();
                break;

            case 7:
                displayCurrentPage();
                break;

            case 8:
                freeHistory();
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}