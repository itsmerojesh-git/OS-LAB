#include <stdio.h>
#include <stdlib.h> // Include this header for the abs function

int main() {
    int num_requests, head, requests[50], i, seek_count = 0;

    // Input the number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);

    // Input the disk requests
    printf("Enter the disk requests: ");
    for(i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    // Input the initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    // Print the header for the output
    printf("\nDisk Request\tHead Position\tSeek Operations\n");

    // Process each disk request in the order they arrive (FCFS)
    for(i = 0; i < num_requests; i++) {
        printf("%d\t\t", requests[i]);
        
        // Calculate the seek operation (absolute distance between current head and request)
        seek_count += abs(requests[i] - head);
        head = requests[i];  // Move the head to the current request position

        // Print the current head position and the cumulative seek count
        printf("%d\t\t%d\n", head, seek_count);
    }

    // Print the total number of seek operations
    printf("\nTotal Seek Operations: %d\n", seek_count);

    return 0;
}

