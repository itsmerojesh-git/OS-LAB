#include <stdio.h>
// Structure to store the maximum, allocated, need, before, and after values for each process
struct da {
    int max[10], al[10], need[10], before[10], after[10];
} p[10];

int main() {
    int i, j, k, l, r, n, tot[10], av[10], cn = 0, cz = 0, temp = 0, c = 0;

    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &r);

    // Input maximum and allocated resources for each process
    for (i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        for (j = 0; j < r; j++) {
            printf("Maximum value for resource %d: ", j + 1);
            scanf("%d", &p[i].max[j]);
        }
        for (j = 0; j < r; j++) {
            printf("Allocated from resource %d: ", j + 1);
            scanf("%d", &p[i].al[j]);
            p[i].need[j] = p[i].max[j] - p[i].al[j]; // Calculate need
        }
    }

    // Input total value of each resource
    for (i = 0; i < r; i++) {
        printf("Enter total value of resource %d: ", i + 1);
        scanf("%d", &tot[i]);
    }

    // Calculate available resources
    for (i = 0; i < r; i++) {
        for (j = 0; j < n; j++)
            temp += p[j].al[i]; // Sum of allocated resources for each resource
        av[i] = tot[i] - temp; // Available = Total - Allocated
        temp = 0;
    }

    // Display the max, allocated, needed, total, and available resources
    printf("\nProcess\tMax\t\tAllocated\tNeeded\t\tTotal\tAvailable\n");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t", i + 1);
        for (j = 0; j < r; j++)
            printf("%d ", p[i].max[j]);
        printf("\t");
        for (j = 0; j < r; j++)
            printf("%d ", p[i].al[j]);
        printf("\t");
        for (j = 0; j < r; j++)
            printf("%d ", p[i].need[j]);
        printf("\t");
        if (i == 0) {
            for (j = 0; j < r; j++)
                printf("%d ", tot[j]);
            printf("\t");
            for (j = 0; j < r; j++)
                printf("%d ", av[j]);
        }
    }

    // Check for safe sequence
    printf("\n\nAvailable Before\tAvailable After\n");
    for (l = 0; l < n; l++) {
        for (i = 0; i < n; i++) {
            cn = 0;
            cz = 0;
            for (j = 0; j < r; j++) {
                if (p[i].need[j] > av[j])
                    cn++; // Check if resources are insufficient
                if (p[i].max[j] == 0)
                    cz++; // Check if process is already completed
            }

            // If resources are available and the process is not completed
            if (cn == 0 && cz != r) {
                for (j = 0; j < r; j++) {
                    p[i].before[j] = av[j];             // Store available resources before allocation
                    p[i].after[j] = av[j] + p[i].al[j]; // Update available resources after allocation
                    av[j] = p[i].after[j];              // Update available resources
                    p[i].max[j] = 0;                    // Mark process as completed
                }

                // Display available resources before and after each process execution
                printf("\nP%d\t", i + 1);
                for (j = 0; j < r; j++)
                    printf("%d ", p[i].before[j]);
                printf("\t\t");
                for (j = 0; j < r; j++)
                    printf("%d ", p[i].after[j]);
                c++; // Increment counter for completed processes
                break; // Move to the next process
            }
        }
    }

    // If all processes are completed, it's a safe sequence; otherwise, deadlock occurred
    if (c == n)
        printf("\nThe above sequence is a safe sequence\n");
    else
        printf("\nDeadlock occurred\n");

    return 0;
}

