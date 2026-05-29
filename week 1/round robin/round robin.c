#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

int main() {
    int n, tq;
    int time = 0, completed = 0;

    float avgWT = 0, avgTAT = 0;

    struct Process p[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {

        p[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        p[i].rt = p[i].bt;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    while (completed < n) {

        int executed = 0;

        for (int i = 0; i < n; i++) {

            if (p[i].at <= time && p[i].rt > 0) {

                executed = 1;

                if (p[i].rt > tq) {

                    time += tq;
                    p[i].rt -= tq;
                }
                else {

                    time += p[i].rt;

                    p[i].rt = 0;

                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    avgWT += p[i].wt;
                    avgTAT += p[i].tat;

                    completed++;
                }
            }
        }

        if (executed == 0) {
            time++;
        }
    }

    printf("\n===== ROUND ROBIN SCHEDULING =====\n");

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", avgTAT / n);
    printf("\nAverage Waiting Time = %.2f\n", avgWT / n);

    return 0;
}
