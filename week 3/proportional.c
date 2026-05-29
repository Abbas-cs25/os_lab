#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process {

    int pid;
    int burstTime;
    int tickets;
    int executed;
    int completionTime;
};

int main() {

    int n, totalTickets = 0;
    int time = 0;

    struct Process p[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {

        p[i].pid = i + 1;

        printf("\nProcess P%d\n", i + 1);

        printf("Burst Time: ");
        scanf("%d", &p[i].burstTime);

        printf("Number of Tickets: ");
        scanf("%d", &p[i].tickets);

        p[i].executed = 0;

        totalTickets += p[i].tickets;
    }



    printf("\n==================================");
    printf("\n PROPORTIONAL SHARE SCHEDULING");
    printf("\n==================================\n");

    printf("\nProcess Table:\n");

    printf("\nPID\tBurst Time\tTickets\n");

    for(int i = 0; i < n; i++) {

        printf("P%d\t%d\t\t%d\n",
               p[i].pid,
               p[i].burstTime,
               p[i].tickets);
    }

    printf("\nGantt Chart:\n\n");

    while(1) {

        int completed = 1;

        for(int i = 0; i < n; i++) {

            if(p[i].executed < p[i].burstTime) {

                completed = 0;
                break;
            }
        }

        if(completed)
            break;

        int winningTicket = (rand() % totalTickets) + 1;

        int ticketSum = 0;
        int selected = -1;

        for(int i = 0; i < n; i++) {

            ticketSum += p[i].tickets;

            if(winningTicket <= ticketSum) {

                if(p[i].executed < p[i].burstTime) {

                    selected = i;
                    break;
                }
            }
        }

        if(selected != -1) {

            printf("| P%d ", p[selected].pid);

            p[selected].executed++;

            time++;

            if(p[selected].executed == p[selected].burstTime) {

                p[selected].completionTime = time;
            }
        }
    }

    printf("|\n");

    for(int i = 0; i <= time; i++) {

        printf("%-5d", i);
    }

    printf("\n");

    printf("\nResult Table:\n");

    printf("\nPID\tBT\tTickets\tCT\tTAT\tWT\n");

    float avgWT = 0;
    float avgTAT = 0;

    for(int i = 0; i < n; i++) {

        int tat = p[i].completionTime;

        int wt = tat - p[i].burstTime;

        avgWT += wt;

        avgTAT += tat;

        printf("P%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].burstTime,
               p[i].tickets,
               p[i].completionTime,
               tat,
               wt);
    }

    printf("\nAverage Turnaround Time = %.2f",
           avgTAT / n);

    printf("\nAverage Waiting Time = %.2f\n",
           avgWT / n);

    return 0;
}
