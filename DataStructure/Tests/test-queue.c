
#include "queue.h"


#define QUEUE_SIZE 16


void Queue_Print(queue q) {
    printf("Queue | ");
    if (q->front < q->rear) {
        for (int i = 0; i < q->size; i++)
            if (i < q->front)
                printf("* ");
            else if (i == q->front)
                printf("<%d ", q->body[i]);
            else if (i < q->rear)
                printf("%d ", q->body[i]);
            else if (i == q->rear)
                printf("%d> ", q->body[i]);
            else
                printf("* ");
        putchar('|');
    }
    else {
        for (int i = 0; i < q->size; i++)
            if (i < q->rear)
                printf("%d ", q->body[i]);
            else if (i == q->rear)
                printf("%d> ", q->body[i]);
            else if (i < q->front)
                printf("* ");
            else if (i == q->front)
                printf("<%d ", q->body[i]);
            else
                printf("%d ", q->body[i]);
        putchar('|');
    }
}


void test_queue_operations(void) {

    printf("Original queue:\n    ");
    queue q = Queue_FromArray(QUEUE_SIZE, (int [12]){2, 6, 4, 2, 5, 3, 7, 2, 8, 6, 5, 3}, 12);
    Queue_Print(q);

    printf("\nDequeue 4 elements:\n    ");
    for (int i = 0; i < 4; i++)
        Queue_Dequeue(q);
    Queue_Print(q);

    printf("\nEnqueue 3 elements:\n    ");
    for (int i = 0; i < 4; i++)
        Queue_Enqueue(q, i + 1);
    Queue_Print(q);

    printf("\nDequeue 3 elements:\n    ");
    for (int i = 0; i < 3; i++)
        Queue_Dequeue(q);
    Queue_Print(q);

    printf("\nEnqueue 2 elements:\n    ");
    for (int i = 0; i < 2; i++)
        Queue_Enqueue(q, i);


    Queue_Print(q);
}

