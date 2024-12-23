#include<stdio.h>
int main()
{
    int i, j, bt[10], t, n, wt[10], tt[10], w1 = 0, t1 = 0;
    float aw, at;

    // Input the number of processes
    printf("Enter number of processes:\n");
    scanf("%d", &n);

    // Input burst times for the processes
    printf("Enter the burst time of processes:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &bt[i]);

    // Sort burst times in ascending order using bubble sort
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                t = bt[i];
                bt[i] = bt[j];
                bt[j] = t;
            }
        }
    }

    // Initialize waiting time and turnaround time for first process
    wt[0] = 0;
    tt[0] = bt[0];
    w1 = 0;
    t1 = tt[0];

    // Calculate waiting time and turnaround time for each process
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];  // Waiting time for process i
        tt[i] = wt[i] + bt[i];          // Turnaround time = waiting time + burst time
        w1 += wt[i];                    // Sum of waiting times
        t1 += tt[i];                    // Sum of turnaround times
    }

    // Calculate average waiting time and average turnaround time
    aw = (float)w1 / n;
    at = (float)t1 / n;

    // Print sorted burst times
    printf("\nSorted burst times: ");
    for (i = 0; i < n; i++)
        printf("%d ", bt[i]);

    // Print results
    printf("\n\nbt\twt\ttt\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\n", bt[i], wt[i], tt[i]);

    printf("Average Waiting Time = %.2f\n", aw);
    printf("Average Turnaround Time = %.2f\n", at);

    return 0;
}

