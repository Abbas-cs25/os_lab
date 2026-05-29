#include <stdio.h>

void FIFO(int pages[], int n, int f) {

    int frames[10];

    int index = 0;

    int faults = 0;

    for(int i = 0; i < f; i++) {

        frames[i] = -1;
    }

    printf("\n=================================");
    printf("\n FIFO PAGE REPLACEMENT");
    printf("\n=================================\n");

    printf("\nPage\tFrames\n");

    for(int i = 0; i < n; i++) {

        int found = 0;

        for(int j = 0; j < f; j++) {

            if(frames[j] == pages[i]) {

                found = 1;
                break;
            }
        }

        if(!found) {

            frames[index] = pages[i];

            index = (index + 1) % f;

            faults++;
        }

        printf("%d\t", pages[i]);

        for(int j = 0; j < f; j++) {

            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }

        if(!found)
            printf("PF");

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

void LRU(int pages[], int n, int f) {

    int frames[10];

    int time[10];

    int faults = 0;

    for(int i = 0; i < f; i++) {

        frames[i] = -1;
    }

    printf("\n=================================");
    printf("\n LRU PAGE REPLACEMENT");
    printf("\n=================================\n");

    printf("\nPage\tFrames\n");

    for(int i = 0; i < n; i++) {

        int found = 0;

        for(int j = 0; j < f; j++) {

            if(frames[j] == pages[i]) {

                found = 1;

                time[j] = i;

                break;
            }
        }

        if(!found) {

            int pos = -1;

            for(int j = 0; j < f; j++) {

                if(frames[j] == -1) {

                    pos = j;
                    break;
                }
            }

            if(pos == -1) {

                int least = time[0];

                pos = 0;

                for(int j = 1; j < f; j++) {

                    if(time[j] < least) {

                        least = time[j];

                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];

            time[pos] = i;

            faults++;
        }

        printf("%d\t", pages[i]);

        for(int j = 0; j < f; j++) {

            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }

        if(!found)
            printf("PF");

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

void Optimal(int pages[], int n, int f) {

    int frames[10];

    int faults = 0;

    for(int i = 0; i < f; i++) {

        frames[i] = -1;
    }

    printf("\n=================================");
    printf("\n OPTIMAL PAGE REPLACEMENT");
    printf("\n=================================\n");

    printf("\nPage\tFrames\n");

    for(int i = 0; i < n; i++) {

        int found = 0;

        for(int j = 0; j < f; j++) {

            if(frames[j] == pages[i]) {

                found = 1;
                break;
            }
        }

        if(!found) {

            int pos = -1;

            for(int j = 0; j < f; j++) {

                if(frames[j] == -1) {

                    pos = j;
                    break;
                }
            }

            if(pos == -1) {

                int farthest = i;

                pos = 0;

                for(int j = 0; j < f; j++) {

                    int k;

                    for(k = i + 1; k < n; k++) {

                        if(frames[j] == pages[k]) {

                            if(k > farthest) {

                                farthest = k;

                                pos = j;
                            }

                            break;
                        }
                    }

                    if(k == n) {

                        pos = j;
                        break;
                    }
                }
            }

            frames[pos] = pages[i];

            faults++;
        }

        printf("%d\t", pages[i]);

        for(int j = 0; j < f; j++) {

            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }

        if(!found)
            printf("PF");

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

int main() {

    int n, f;

    int pages[50];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("\nEnter page reference string:\n");

    for(int i = 0; i < n; i++) {

        scanf("%d", &pages[i]);
    }

    printf("\nEnter number of frames: ");
    scanf("%d", &f);

    FIFO(pages, n, f);

    LRU(pages, n, f);

    Optimal(pages, n, f);

    return 0;
}
