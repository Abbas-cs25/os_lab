#include <stdio.h>

int main() {

    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[10][10];
    int max[10][10];
    int need[10][10];
    int avail[10];

    printf("\nEnter Allocation Matrix:\n");

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Max Matrix:\n");

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");

    for(int i = 0; i < m; i++) {

        scanf("%d", &avail[i]);
    }

    // Calculate Need Matrix

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\n=================================");
    printf("\n NEED MATRIX");
    printf("\n=================================\n");

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    int finish[10] = {0};

    int safeSeq[10];

    int work[10];

    for(int i = 0; i < m; i++) {

        work[i] = avail[i];
    }

    int count = 0;

    while(count < n) {

        int found = 0;

        for(int i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(int j = 0; j < m; j++) {

                    if(need[i][j] > work[j]) {

                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    for(int j = 0; j < m; j++) {

                        work[j] += alloc[i][j];
                    }

                    safeSeq[count] = i;

                    count++;

                    finish[i] = 1;

                    found = 1;
                }
            }
        }

        if(found == 0) {

            break;
        }
    }

    printf("\n=================================");
    printf("\n SAFETY ALGORITHM RESULT");
    printf("\n=================================\n");

    if(count == n) {

        printf("\nSystem is in SAFE STATE\n");

        printf("\nSafe Sequence:\n");

        for(int i = 0; i < n; i++) {

            printf("P%d", safeSeq[i]);

            if(i != n - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else {

        printf("\nSystem is NOT in Safe State\n");
    }

    return 0;
}
