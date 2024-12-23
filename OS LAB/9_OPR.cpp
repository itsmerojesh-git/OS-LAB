#include <stdio.h>

int find_farthest(int pages[], int frame[], int num_frames, int num_pages, int current_index) {
    int i, j, farthest = -1, index = -1;

    for(i = 0; i < num_frames; i++) {
        int found = 0;
        for(j = current_index + 1; j < num_pages; j++) {
            if(frame[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    index = i;
                }
                found = 1;
                break;
            }
        }
        if(!found) {
            return i;
        }
    }
    return (index == -1) ? 0 : index;
}

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
            if(page_faults < num_frames) {
                frame[page_faults] = pages[i];
            } else {
                int replace_index = find_farthest(pages, frame, num_frames, num_pages, i);
                frame[replace_index] = pages[i];
            }
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

