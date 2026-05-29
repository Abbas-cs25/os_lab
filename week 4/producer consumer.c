#include <stdio.h>

int mutex = 1;
int full = 0;
int empty = 5;

int x = 0;

void wait(int *s) {
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void producer() {

    wait(&empty);
    wait(&mutex);

    x++;

    printf("\nProducer produces item %d", x);

    signal(&mutex);
    signal(&full);
}

void consumer() {

    wait(&full);
    wait(&mutex);

    printf("\nConsumer consumes item %d", x);

    x--;

    signal(&mutex);
    signal(&empty);
}

int main() {

    int operations[] = {1,1,1,2,1,2,2,1,2};

    int n = sizeof(operations) / sizeof(operations[0]);

    printf("=================================");
    printf("\n PRODUCER CONSUMER USING SEMAPHORE");
    printf("\n=================================\n");

    printf("\nBuffer Size = 5\n");

    for(int i = 0; i < n; i++) {

        if(operations[i] == 1) {

            if((mutex == 1) && (empty != 0)) {

                producer();
            }
            else {

                printf("\nBuffer is Full!");
            }
        }

        else if(operations[i] == 2) {

            if((mutex == 1) && (full != 0)) {

                consumer();
            }
            else {

                printf("\nBuffer is Empty!");
            }
        }

        printf("\nBuffer Status --> Full = %d , Empty = %d\n",
               full,
               empty);
    }

    return 0;
}
