#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct two_queue 
{
	Queue* q1;
	Queue* q2;
} Two_Queues;

typedef struct q 
{
	char **strings;
	int capacity;
	int size;
	int front;
	int rear;
	int enqueueCount;
	int dequeueCount;
	int enqueueBlockCount;
	int dequeueBlockCount;
} Queue;

Queue *CreateStringQueue(int size) 
{
	Queue *q;
	q = (Queue *)malloc(sizeof(Queue));
	q->strings = malloc(sizeof(char*)*size);
	q->size = 0;
	q->capacity = size;
	q->front = 0;
	q->rear= -1;

	return q;
}

Two_Queues *CreateTwoQueues(Queue a, Queue b) 
{
	Two_Queues *qs = (Two_Queues*)malloc(sizeof(Two_Queues);
	qs->q1 = a;
	qs->q2 = b;
	return qs;
}

void EnqueueString(Queue *q, char *string)
{
	if (q->size == q->capacity)
	{
		printf("Error: Queue is full.\n");
	}
	else
	{
		q->size++;
		q->rear++;;

		if (q->rear == q-> capacity)
		{
			q->rear = 0;
		}

		q->strings[q->rear] = string;
		q->enqueueCount++;
	}
}

char * DequeueString(Queue *q) 
{
	if (q->size == 0)
	{
		printf("Error: Empty Queue\n");
	}
	else
	{
		q->size--;
		q->front++;
		q->dequeueCount++;

		if(q->front==q->capacity)
		{
			q->front=0;
		}
	}
}

void PrintQueueStats(Queue *q)
{ 
	fprintf(stderr, "%s %d", "Number of Enqueue operations: ", enqueueCount);
	fprintf(stderr, "%s %d", "Number of Dequeue operations: ", enqueueCount);
	fprintf(stderr, "%s %d", "Number of Enqueue blocks: ", enqueueBlockCount);
	fprintf(stderr, "%s %d", "Number of Dequeue blocks: ", dequeueBlockCount);

}
