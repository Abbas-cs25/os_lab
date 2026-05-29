#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int priority;
    int ct;
    int tat;
    int wt;
    int completed;
};

void priorityNonPreemptive(struct Process p[], int n) {
    int time = 0, completed = 0;
    float avgWT = 0, avgTAT = 0;

    printf("\n===== PRIORITY NON-PREEMPTIVE =====\n");

    while (completed < n) {
        int idx = -1;
        int highestPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0) {

                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            time += p[idx].bt;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            avgWT += p[idx].wt;
            avgTAT += p[idx].tat;

            p[idx].completed = 1;
            completed++;
        }
        else {
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].priority,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", avgTAT / n);
    printf("\nAverage Waiting Time = %.2f\n", avgWT / n);
}

void priorityPreemptive(struct Process p[], int n) {
    int time = 0, completed = 0;
    float avgWT = 0, avgTAT = 0;

    printf("\n===== PRIORITY PREEMPTIVE =====\n");

    while (completed < n) {
        int idx = -1;
        int highestPriority = 9999;

        for (int i = 0; i < n; i++) {

            if (p[i].at <= time && p[i].rt > 0) {

                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].rt--;
            time++;

            if (p[idx].rt == 0) {

                completed++;

                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                avgWT += p[idx].wt;
                avgTAT += p[idx].tat;
            }
        }
        else {
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].priority,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", avgTAT / n);
    printf("\nAverage Waiting Time = %.2f\n", avgWT / n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p1[10], p2[10];

    for (int i = 0; i < n; i++) {

        printf("\nProcess %d\n", i + 1);

        p1[i].pid = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &p1[i].at);

        printf("Burst Time: ");
        scanf("%d", &p1[i].bt);

        printf("Priority: ");
        scanf("%d", &p1[i].priority);

        p1[i].rt = p1[i].bt;
        p1[i].completed = 0;

        // Copy for preemptive
        p2[i] = p1[i];
    }

    priorityNonPreemptive(p1, n);

    priorityPreemptive(p2, n);

    return 0;
}
