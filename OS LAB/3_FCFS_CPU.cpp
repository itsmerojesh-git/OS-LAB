#include<stdio.h>
int main()
{
    int i, j, bt[10], n, wt[10], tt[10], w1 = 0, t1 = 0;
    float aw, at;

    printf("Enter number of processes:\n");
    scanf("%d", &n);

    printf("Enter the burst time of processes:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &bt[i]);

    wt[0] = 0;

    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        w1 += wt[i];
    }

    for (i = 0; i < n; i++) {
        tt[i] = wt[i] + bt[i];
        t1 += tt[i];
    }

    aw = (float)w1 / n;
    at = (float)t1 / n;

    printf("\nProcess\tBT\tWT\tTT\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tt[i]);

    printf("Average Waiting Time = %.2f\n", aw);
    printf("Average Turnaround Time = %.2f\n", at);

    return 0;
}

