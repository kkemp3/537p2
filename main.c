
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <ctype.h>
#include <strings.h>
#include "queue.h"

void *readerThread(void *vargp)
{
	Queue *q = (Queue*) vargp;
	int ch; // keep track of current char
	char buff[BUFF_SIZE];
	char *line; // string to be enqueued
	int i = 0; // index
	while ((ch = getchar()) != EOF)
	{
		
		if (ch != '\n')
		{
			buff[i] = ch;
		
		}
		else 
		{
			if (i < BUFF_SIZE)
			{
				line = (char*)malloc(BUFF_SIZE * sizeof(char));
				line[strlen(line)-1] = '\0';
				strcpy(line,buff);
				printf("%s", line);
				memset(buff, 0, sizeof(buff));
				i = 0;
				EnqueueString(q, line);
			}
			else if (buff[BUFF_SIZE - 1] != '\0')
			{
				fprintf(stderr, "Line is too long\n");
				memset(buff, 0, sizeof(buff));
				i = 0;
			}
		}
		i++;
	}
	EnqueueString(q, NULL); // enqueue null to be last element of queue
	pthread_exit();
	return NULL;
}


void *writerThread(void *vargp)
{
	Queue *q = (Queue*) vargp;
  	char *line = Dequeue(q);
    	while (line != NULL) 
	{	
		srtcat(line, "\n");
		printf("%s", line);		
    		line = Dequeue(q);
	}
	
	pthread_exit();
    return NULL;
}

void *Munch1( void *vargp)
{

	Two_Queues *inAndOut = (Two_Queues*) vargp; 	// struct that points to 2
							// queues
	char *temp = DequeueString(inAndOut->q1); // current string
	
	while (temp != NULL)
	{
		char *qString = malloc(BUFF_SIZE * sizeof(char));
		for (int i = 0; i < strlen(temp); i++)
		{
			if (temp[i] == ' ')
			{
				qString[i] = '*':
			}
			else 
			{
				qString[i] = temp[i];
			}
		}
		Enqueue(inAndOut->q2, qString);
		temp = DequeueString(inAndOut->q1);

	}
	Enqueue(inAndOut->q2, NULL); // enqueue null value as last element
	pthread_exit();

  return NULL;

}

void *Munch2( void *vargp)
{

	Two_Queues *lowToUp = (Two_Queues*) vargp;
	char *temp = DequeueString(lowToUp->q1);

	while (temp != NULL)
	{
		char *qString = malloc(BUFF_SIZE * sizeof(char));
		for (int i = 0; i < strlen(temp); i++)
		{
			if (islower(temp[i]))
			{
				qString[i] = toupper(temp[i]);
			}
			else
			{
				qString[i] = temp[i];
			}
		}
		EnqueueString(lowToUp->q2, qString);
		temp = DequeueString(lowToUP->q1);
	}
	Enqueue(lowToUp->q2, NULL);
	pthread_exit();

return NULL;

}


//-------------------------------------------------------------------//

int main(int argc, char* argv[]){

  int argcCounter;

  if (argc == 1) {

      printf("No argument passed except program name\n ");

  }

  if (argc >= 2){

      printf("\n----Following Are The Command Line Arguments Passed----");
          for(argcCounter = 0; argcCounter < argc; argcCounter++)
              printf("\nargv[%d]: %s",argcCounter,argv[argcCounter]);
              printf("\n \n \n \n");


  }

  Queue queues[3];

  for (int i = 0; i < 3; i++) 
  {
  	queues[i] = CreateStringQueue(QUEUE_SIZE);
  }

	Two_Queues *m1 = CreateTwoQueues(queues[0], queues[1]);
	Two_Queues *m2 = CreateTwoQueues(queues[1], queues[2]);


    // This is where the thread is created and called.
    pthread_t thread_id_reader;
    pthread_t thread_id_Munch1;
    pthread_t thread_id_Munch2;
    pthread_t thread_id_writer;

    int t1 =  pthread_create(&thread_id_reader, NULL, readerThread , &queues[0]);
    int t2 = pthread_create(&thread_id_Munch1, NULL, Munch1, &m1);
    int t3 = pthread_create(&thread_id_Munch2, NULL, Munch2, &m2);
    int t4 = pthread_create(&thread_id_writer, NULL, writerThread , &queues[2]);
    
    pthread_join(thread_id_reader, NULL);
    pthread_join(thread_id_Munch1, NULL);
    pthread_join(thread_id_Munch2, NULL);
    pthread_join(thread_id_writer, NULL);
	
	fprintf(stderr, "%s", "Stats for Queue1: ");
	PrintQueueStats(queues[0]);
	fprintf(stderr, "%s", "Stats for Queue2: ");
	PrintQueueStats(queues[1]);
	fprintf(stderr, "%s", "Stats for Queue3: ");
	PrintQueueStats(queues[2]);

  printf("\n");
  return 0;

}
