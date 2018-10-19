

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <ctype.h>
#include <string.h>


const int BUFF_SIZE = 20;
int main() 
{

/*void *readerThread(void *vargp)*/
/*{*/
	//Queue *q = (Queue*) vargp;
	int ch;
	char buff[BUFF_SIZE];
	char *line;
	int i = 0;
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
				//EnqueueString(q, line);
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
	//EnqueueString(q, NULL);
	//pthread_exit();
	return NULL;
}
