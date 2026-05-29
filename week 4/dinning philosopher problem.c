#include <stdio.h>

#define N 5

int state[N];

enum {
    THINKING,
    HUNGRY,
    EATING
};

void test(int i) {

    if(state[i] == HUNGRY &&
       state[(i + 4) % N] != EATING &&
       state[(i + 1) % N] != EATING) {

        state[i] = EATING;

        printf("\nPhilosopher %d takes forks %d and %d",
               i + 1,
               (i + 4) % N + 1,
               i + 1);

        printf("\nPhilosopher %d is EATING\n", i + 1);
    }
}

void take_fork(int i) {

    state[i] = HUNGRY;

    printf("\nPhilosopher %d is HUNGRY", i + 1);

    test(i);

    if(state[i] != EATING) {

        printf("\nPhilosopher %d is WAITING\n", i + 1);
    }
}

void put_fork(int i) {

    state[i] = THINKING;

    printf("\nPhilosopher %d puts forks %d and %d down",
           i + 1,
           (i + 4) % N + 1,
           i + 1);

    printf("\nPhilosopher %d is THINKING\n", i + 1);

    test((i + 4) % N);

    test((i + 1) % N);
}

int main() {

    for(int i = 0; i < N; i++) {

        state[i] = THINKING;
    }

    printf("=================================");
    printf("\n DINING PHILOSOPHERS PROBLEM");
    printf("\n=================================\n");

    // Automatic Simulation

    take_fork(0);
    take_fork(1);
    put_fork(0);

    take_fork(2);
    put_fork(1);

    take_fork(3);
    put_fork(2);

    take_fork(4);
    put_fork(3);

    put_fork(4);

    return 0;
}
