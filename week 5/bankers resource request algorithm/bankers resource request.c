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

    int p;

    int request[10];

    printf("\nEnter Process Number requesting resources: ");
    scanf("%d", &p);

    printf("\nEnter Request Vector:\n");

    for(int i = 0; i < m; i++) {

        scanf("%d", &request[i]);
    }

    // Check Request <= Need

    for(int i = 0; i < m; i++) {

        if(request[i] > need[p][i]) {

            printf("\nERROR: Process exceeded maximum claim!\n");

            return 0;
        }
    }

    // Check Request <= Available

    for(int i = 0; i < m; i++) {

        if(request[i] > avail[i]) {

            printf("\nResources not available. Process must wait.\n");

            return 0;
        }
    }

    // Temporary Allocation

    for(int i = 0; i < m; i++) {

        avail[i] -= request[i];

        alloc[p][i] += request[i];

        need[p][i] -= request[i];
    }

    // Safety Algorithm

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
    printf("\n RESOURCE REQUEST RESULT");
    printf("\n=================================\n");

    if(count == n) {

        printf("\nRequest can be GRANTED.\n");

        printf("\nSystem remains in SAFE STATE.\n");

        printf("\nSafe Sequence:\n");

        for(int i = 0; i < n; i++) {

            printf("P%d", safeSeq[i]);

            if(i != n - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else {

        printf("\nRequest CANNOT be granted.");

        printf("\nSystem will enter UNSAFE STATE.\n");
    }

    return 0;
}
