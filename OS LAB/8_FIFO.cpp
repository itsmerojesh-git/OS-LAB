#include<stdio.h>

int main() {
    int num_pages, num_frames, pages[50], frame[10], i, j, avail, page_faults = 0, page_hits = 0;

    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter the page reference string: ");
    for(i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    for(i = 0; i < num_frames; i++) {
        frame[i] = -1;
    }

    printf("\nPage Reference\tFrames\t\tStatus\n");

    for(i = 0; i < num_pages; i++) {
        printf("%d\t\t", pages[i]);
        avail = 0;

        for(j = 0; j < num_frames; j++) {
            if(frame[j] == pages[i]) {
                avail = 1;
                page_hits++;
                break;
            }
        }

        if(avail == 0) {
            frame[page_faults % num_frames] = pages[i];
            page_faults++;
            for(j = 0; j < num_frames; j++) {
                if(frame[j] == -1) {
                    printf("-\t");
                } else {
                    printf("%d\t", frame[j]);
                }
            }
            printf("Page Fault\n");
        } else {
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

    printf("\nTotal Page Faults: %d\n", page_faults);
    printf("Total Page Hits: %d\n", page_hits);

    return 0;
}

