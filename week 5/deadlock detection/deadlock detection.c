#include <stdio.h>

int main() {

    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[10][10];
    int request[10][10];
    int avail[10];

    printf("\nEnter Allocation Matrix:\n");

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");

    for(int i = 0; i < m; i++) {

        scanf("%d", &avail[i]);
    }

    int finish[10] = {0};

    int work[10];

    for(int i = 0; i < m; i++) {

        work[i] = avail[i];
    }

    int sequence[10];

    int count = 0;

    while(count < n) {

        int found = 0;

        for(int i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(int j = 0; j < m; j++) {

                    if(request[i][j] > work[j]) {

                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    for(int j = 0; j < m; j++) {

                        work[j] += alloc[i][j];
                    }

                    finish[i] = 1;

                    sequence[count] = i;

                    count++;

                    found = 1;
                }
            }
        }

        if(found == 0) {

            break;
        }
    }

    printf("\n=================================");
    printf("\n DEADLOCK DETECTION RESULT");
    printf("\n=================================\n");

    if(count == n) {

        printf("\nNo Deadlock Detected.\n");

        printf("\nSafe Execution Sequence:\n");

        for(int i = 0; i < n; i++) {

            printf("P%d", sequence[i]);

            if(i != n - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else {

        printf("\nDeadlock Detected!\n");

        printf("\nProcesses in Deadlock:\n");

        for(int i = 0; i < n; i++) {

            if(finish[i] == 0) {

                printf("P%d ", i);
            }
        }

        printf("\n");
    }

    return 0;
}
