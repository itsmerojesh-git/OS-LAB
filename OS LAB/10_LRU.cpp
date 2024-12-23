#include <stdio.h>

// Function to find the least recently used page
int find_lru(int time[], int num_frames) {
    int i, min = time[0], pos = 0;
    for(i = 1; i < num_frames; ++i) {
        if(time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int num_pages, num_frames, pages[50], frame[10], time[10], counter = 0;
    int i, j, avail, page_faults = 0, page_hits = 0;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);

    // Input the reference string (page numbers)
    printf("Enter the page reference string: ");
    for(i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    // Initialize frames to -1 (empty) and time for tracking usage
    for(i = 0; i < num_frames; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("\nPage Reference\tFrames\t\tStatus\n");

    // Process each page in the reference string
    for(i = 0; i < num_pages; i++) {
        printf("%d\t\t", pages[i]);
        avail = 0;

        // Check if the page is already in one of the frames (Page Hit)
        for(j = 0; j < num_frames; j++) {
            if(frame[j] == pages[i]) {
                avail = 1;  // Page hit
                page_hits++;  // Increment page hit count
                counter++;
                time[j] = counter;  // Update the last used time
                break;
            }
        }

        // If it's a page fault
        if(avail == 0) {
            int pos;
            if(page_faults < num_frames) {
                pos = page_faults;  // Initially fill the frames
            } else {
                pos = find_lru(time, num_frames);  // Find LRU page to replace
            }
            frame[pos] = pages[i];  // Replace the LRU page
            counter++;
            time[pos] = counter;  // Update time for the inserted page
            page_faults++;  // Increment page fault count

            // Print the frame contents
            for(j = 0; j < num_frames; j++) {
                if(frame[j] == -1) {
                    printf("-\t");
                } else {
                    printf("%d\t", frame[j]);
                }
            }
            // Indicate it's a page fault
            printf("Page Fault\n");
        } else {
            // If it's a page hit, print the current frames and indicate it's a hit
            for(j = 0; j < num_frames; j++) {
                if(frame[j] == -1) {
                    printf("-\t");
                } else {
                    printf("%d\t", frame[j]);
                }
            }
            printf("Page Hit\n");
        }
    }

    // Print the total number of page faults and hits
    printf("\nTotal Page Faults: %d\n", page_faults);
    printf("Total Page Hits: %d\n", page_hits);

    return 0;
}

