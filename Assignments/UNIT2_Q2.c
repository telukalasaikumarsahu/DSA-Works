#include <stdio.h>

#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

int isFull(void) {
    return (front == 0 && rear == MAX - 1) || (rear + 1) % MAX == front;
}

int isEmpty(void) {
    return front == -1;
}

void insert(int value) {
    if (isFull()) {
        printf("Overflow: Request buffer is full.\n");
        return;
    }

    if (isEmpty())
        front = rear = 0;
    else
        rear = (rear + 1) % MAX;

    queue[rear] = value;
    printf("Request %d inserted successfully.\n", value);
}

void deleteRequest(void) {
    int value;

    if (isEmpty()) {
        printf("Underflow: Request buffer is empty.\n");
        return;
    }

    value = queue[front];

    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % MAX;

    printf("Request %d deleted successfully.\n", value);
}

void display(void) {
    int i;

    if (isEmpty()) {
        printf("Request buffer is empty.\n");
        return;
    }

    printf("Requests in buffer: ");

    i = front;
    while (1) {
        printf("%d ", queue[i]);

        if (i == rear)
            break;

        i = (i + 1) % MAX;
    }

    printf("\n");
}

int main(void) {
    int choice, value;

    printf("Circular Queue Request Buffer\n");
    printf("Buffer Capacity: %d\n", MAX);

    while (1) {
        printf("\n1. Insert Request\n");
        printf("2. Delete Request\n");
        printf("3. Display Buffer\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter request ID: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                deleteRequest();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}