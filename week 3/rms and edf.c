#include <stdio.h>

struct Task {
    int id;
    int execution;
    int period;
    int deadline;
    int remaining;
    int nextArrival;
};

void resetTasks(struct Task t[], struct Task temp[], int n) {

    for(int i = 0; i < n; i++) {
        t[i] = temp[i];
    }
}

void RMS(struct Task t[], int n, int hyperperiod) {

    printf("\n===============================");
    printf("\n RATE MONOTONIC SCHEDULING");
    printf("\n===============================\n");

    printf("\nTask Table:\n");

    printf("\nTask\tExec\tPeriod\tDeadline\n");

    for(int i = 0; i < n; i++) {

        printf("T%d\t%d\t%d\t%d\n",
               t[i].id,
               t[i].execution,
               t[i].period,
               t[i].deadline);
    }

    printf("\nGantt Chart:\n\n");

    int executionTable[100];

    for(int time = 0; time < hyperperiod; time++) {

        for(int i = 0; i < n; i++) {

            if(time == t[i].nextArrival) {

                t[i].remaining = t[i].execution;

                t[i].nextArrival += t[i].period;
            }
        }

        int idx = -1;
        int minPeriod = 9999;

        for(int i = 0; i < n; i++) {

            if(t[i].remaining > 0) {

                if(t[i].period < minPeriod) {

                    minPeriod = t[i].period;
                    idx = i;
                }
            }
        }

        executionTable[time] = idx;

        if(idx != -1) {

            printf("| T%d ", t[idx].id);

            t[idx].remaining--;
        }
        else {

            printf("| IDLE ");
        }
    }

    printf("|\n");

    for(int i = 0; i <= hyperperiod; i++) {
        printf("%-6d", i);
    }

    printf("\n");

    printf("\nExecution Table:\n");

    printf("\nTime\tRunning Task\n");

    for(int i = 0; i < hyperperiod; i++) {

        if(executionTable[i] != -1)
            printf("%d-%d\tT%d\n",
                   i,
                   i + 1,
                   t[executionTable[i]].id);
        else
            printf("%d-%d\tIDLE\n", i, i + 1);
    }
}

void EDF(struct Task t[], int n, int hyperperiod) {

    printf("\n===============================");
    printf("\n EARLIEST DEADLINE FIRST");
    printf("\n===============================\n");

    printf("\nTask Table:\n");

    printf("\nTask\tExec\tPeriod\tDeadline\n");

    for(int i = 0; i < n; i++) {

        printf("T%d\t%d\t%d\t%d\n",
               t[i].id,
               t[i].execution,
               t[i].period,
               t[i].deadline);
    }

    printf("\nGantt Chart:\n\n");

    int currentDeadline[10];

    int executionTable[100];

    for(int i = 0; i < n; i++) {

        currentDeadline[i] = t[i].deadline;
    }

    for(int time = 0; time < hyperperiod; time++) {

        for(int i = 0; i < n; i++) {

            if(time == t[i].nextArrival) {

                t[i].remaining = t[i].execution;

                currentDeadline[i] = time + t[i].deadline;

                t[i].nextArrival += t[i].period;
            }
        }

        int idx = -1;

        int earliestDeadline = 9999;

        for(int i = 0; i < n; i++) {

            if(t[i].remaining > 0) {

                if(currentDeadline[i] < earliestDeadline) {

                    earliestDeadline = currentDeadline[i];

                    idx = i;
                }
            }
        }

        executionTable[time] = idx;

        if(idx != -1) {

            printf("| T%d ", t[idx].id);

            t[idx].remaining--;
        }
        else {

            printf("| IDLE ");
        }
    }

    printf("|\n");

    for(int i = 0; i <= hyperperiod; i++) {
        printf("%-6d", i);
    }

    printf("\n");

    printf("\nExecution Table:\n");

    printf("\nTime\tRunning Task\tDeadline\n");

    for(int i = 0; i < hyperperiod; i++) {

        if(executionTable[i] != -1) {

            printf("%d-%d\tT%d\t\t%d\n",
                   i,
                   i + 1,
                   t[executionTable[i]].id,
                   ((i / t[executionTable[i]].period) + 1)
                   * t[executionTable[i]].deadline);
        }
        else {

            printf("%d-%d\tIDLE\t\t-\n", i, i + 1);
        }
    }
}

int main() {

    int n, hyperperiod;

    struct Task t[10], temp[10];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {

        t[i].id = i + 1;

        printf("\nTask T%d\n", i + 1);

        printf("Execution Time: ");
        scanf("%d", &t[i].execution);

        printf("Period: ");
        scanf("%d", &t[i].period);

        printf("Deadline: ");
        scanf("%d", &t[i].deadline);

        t[i].remaining = 0;

        t[i].nextArrival = 0;

        temp[i] = t[i];
    }

    printf("\nEnter Hyperperiod (Simulation Time): ");
    scanf("%d", &hyperperiod);

    RMS(t, n, hyperperiod);

    resetTasks(t, temp, n);

    EDF(t, n, hyperperiod);

    return 0;
}
