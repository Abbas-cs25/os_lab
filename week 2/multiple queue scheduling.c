
#include <stdio.h>

struct Process {
    int pid;
    int bt;
    int ct;
    int tat;
    int wt;
};

int main() {

    int n1, n2;

    struct Process sys[10], user[10];

    int time = 0;

    printf("Enter number of System Processes: ");
    scanf("%d", &n1);

    for(int i = 0; i < n1; i++) {

        sys[i].pid = i + 1;

        printf("\nSystem Process P%d Burst Time: ", sys[i].pid);
        scanf("%d", &sys[i].bt);
    }

    printf("\nEnter number of User Processes: ");
    scanf("%d", &n2);

    for(int i = 0; i < n2; i++) {

        user[i].pid = i + 1;

        printf("\nUser Process P%d Burst Time: ", user[i].pid);
        scanf("%d", &user[i].bt);
    }

    printf("\n===== GANTT CHART =====\n\n");

    // System Queue using FCFS
    for(int i = 0; i < n1; i++) {

        printf("|  S%d  ", sys[i].pid);

        time += sys[i].bt;

        sys[i].ct = time;
        sys[i].tat = sys[i].ct;
        sys[i].wt = sys[i].tat - sys[i].bt;
    }

    // User Queue using FCFS
    for(int i = 0; i < n2; i++) {

        printf("|  U%d  ", user[i].pid);

        time += user[i].bt;

        user[i].ct = time;
        user[i].tat = user[i].ct;
        user[i].wt = user[i].tat - user[i].bt;
    }

    printf("|\n");

    // Time values
    time = 0;

    printf("0");

    for(int i = 0; i < n1; i++) {

        time += sys[i].bt;
        printf("     %d", time);
    }

    for(int i = 0; i < n2; i++) {

        time += user[i].bt;
        printf("     %d", time);
    }

    printf("\n");

    printf("\n===== SYSTEM QUEUE =====\n");

    printf("\nPID\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n1; i++) {

        printf("S%d\t%d\t%d\t%d\t%d\n",
               sys[i].pid,
               sys[i].bt,
               sys[i].ct,
               sys[i].tat,
               sys[i].wt);
    }

    printf("\n===== USER QUEUE =====\n");

    printf("\nPID\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n2; i++) {

        printf("U%d\t%d\t%d\t%d\t%d\n",
               user[i].pid,
               user[i].bt,
               user[i].ct,
               user[i].tat,
               user[i].wt);
    }

    return 0;
}
