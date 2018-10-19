#ifndef
#define QUEUE_H_

const int BUFF_SIZE = 1024;

const int QUEUE_SIZE = 10;

struct Queue;

struct Two_Queues;

Queue *CreateStringQueue(int size);

Two_Queues *CreateTwoQueues(Queue qa, Queue qb);

void EnqueueString(Queue *q, char *string);

char *DequeueString(Queue *q);

void PrintQueue(Queue *q);

#endif
