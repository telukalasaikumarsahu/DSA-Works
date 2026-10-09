#include <stdio.h>

int binarySearch(const int arr[], int n, int key, int *comparisons) {
    int low = 0, high = n - 1;

    *comparisons = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        (*comparisons)++;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main(void) {
    int n, key, comparisons, position;

    printf("Enter the number of employee IDs: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of employee IDs.\n");
        return 1;
    }

    int employeeID[n];

    printf("Enter %d employee IDs in ascending order:\n", n);

    for (int i = 0; i < n; i++) {
        printf("Employee ID %d: ", i + 1);
        scanf("%d", &employeeID[i]);
    }

    printf("Enter the employee ID to search: ");
    scanf("%d", &key);

    position = binarySearch(employeeID, n, key, &comparisons);

    printf("\n--- Search Result ---\n");

    if (position != -1)
        printf("Employee ID %d found at position %d.\n", key, position + 1);
    else
        printf("Employee ID %d was not found.\n", key);

    printf("Number of comparisons: %d\n", comparisons);

    return 0;
}