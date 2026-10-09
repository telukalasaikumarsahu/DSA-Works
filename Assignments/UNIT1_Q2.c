#include <stdio.h>

void displayArray(const int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int insertionSort(int arr[], int n) {
    int shifts = 0;

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            shifts++;
        }

        arr[j + 1] = key;

        printf("Pass %d: ", i);
        displayArray(arr, n);
    }

    return shifts;
}

int main(void) {
    int n;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    int marks[n];

    printf("Enter the marks of %d students:\n", n);

    for (int i = 0; i < n; i++) {
        printf("Student %d: ", i + 1);
        scanf("%d", &marks[i]);
    }

    printf("\n--- Insertion Sort Process ---\n");

    int shifts = insertionSort(marks, n);

    printf("\n--- Final Result ---\n");
    printf("Sorted marks: ");
    displayArray(marks, n);
    printf("Total number of shifts: %d\n", shifts);

    return 0;
}