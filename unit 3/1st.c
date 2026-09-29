#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int roll;
    struct Node *next;
};

struct Node *head = NULL;

void display()
{
    struct Node *temp = head;

    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    printf("List: ");

    while (temp != NULL)
    {
        printf("%d -> ", temp->roll);
        temp = temp->next;
    }

    printf("NULL\n");
}

void insertBeginning(int roll)
{
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->roll = roll;
    newNode->next = head;
    head = newNode;

    printf("%d inserted at beginning\n", roll);
    display();
}

void insertEnd(int roll)
{
    struct Node *newNode, *temp;

    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->roll = roll;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    printf("%d inserted at end\n", roll);
    display();
}

void search(int roll)
{
    struct Node *temp = head;

    while (temp != NULL)
    {
        if (temp->roll == roll)
        {
            printf("Roll number %d found\n", roll);
            return;
        }

        temp = temp->next;
    }

    printf("Roll number %d not found\n", roll);
}

void deleteNode(int roll)
{
    struct Node *temp = head;
    struct Node *prev = NULL;

    while (temp != NULL && temp->roll != roll)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Roll number %d not found\n", roll);
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    printf("Roll number %d deleted\n", roll);
    display();
}

int main()
{
    int n, roll, i, choice;

    printf("Enter number of students: ");
    scanf("%d", &n);

    printf("Enter roll numbers:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &roll);
        insertEnd(roll);
    }

    while (1)
    {
        printf("\n1. Insert at Beginning");
        printf("\n2. Insert at End");
        printf("\n3. Search");
        printf("\n4. Delete");
        printf("\n5. Display");
        printf("\n6. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter roll number: ");
                scanf("%d", &roll);
                insertBeginning(roll);
                break;

            case 2:
                printf("Enter roll number: ");
                scanf("%d", &roll);
                insertEnd(roll);
                break;

            case 3:
                printf("Enter roll number to search: ");
                scanf("%d", &roll);
                search(roll);
                break;

            case 4:
                printf("Enter roll number to delete: ");
                scanf("%d", &roll);
                deleteNode(roll);
                break;

            case 5:
                display();
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}