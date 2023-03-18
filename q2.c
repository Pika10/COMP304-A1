#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#define READ_END 0
#define WRITE_END 1


int main(int argc, char* argv[])
{	

	int n = atoi(argv[1]);
	int childNumber = 0;
	char* cmd = argv[2];
	char* arg = argv[3];
	int fd[n][2];
	int cN[n][2];
	pid_t pid;
	
	for (int i = 0; i<n; i++)
	{
		pipe(fd[i]);
		pipe(cN[i]);
		childNumber +=1;
		pid = fork();
		if (pid == 0)
		{
			
			struct timeval startTime;
			struct timeval endTime;
			
			freopen("/dev/null", "w", stdout);
			freopen("/dev/null", "w", stderr);
			
			gettimeofday(&startTime, NULL);
			
			pid_t pid2;
			pid2 = fork();
			if (pid2 == 0)
			{
				if (arg != NULL)
				{
					execlp(cmd,cmd,arg,NULL);
				}
				else
				{
					execlp(cmd,cmd,arg,NULL);
				}
				exit(0);
			}

			wait(NULL);
			gettimeofday(&endTime, NULL);
			
			double diff = (endTime.tv_sec - startTime.tv_sec) * 1000.0 + ((endTime.tv_usec - startTime.tv_usec) / 1000.0);
			close(cN[i][READ_END]);
			write(cN[i][WRITE_END], &childNumber, sizeof(childNumber));
			close(cN[i][WRITE_END]);
			close(fd[i][READ_END]);
			write(fd[i][WRITE_END], &diff, sizeof(diff));
			close(fd[i][WRITE_END]);
			exit(0);
		}
	
	}
	
	double min;
	double max;
	double avarage;
	for (int i = 0; i<n; i++)
	{
		wait(NULL);
		double value;
		int childNMBR;
		read(fd[i][READ_END], &value, sizeof(value));
		read(cN[i][READ_END], &childNMBR,sizeof(childNMBR));
		printf("Child %d Executed in %f millis\n",childNMBR,value);
		if (i == 0)
		{
			min = value;
			max = value;
		}
		else
		{
			if (value < min)
			{
				min = value;
			}
			if (value > max)
			{
				max = value;	
			}
		}
		avarage += value;
	}
	avarage = avarage / (double)n;
	printf("Max: %f millis\nMin: %f millis\nAvarage %f millis\n",max,min,avarage);
	
	
	return 0;
	


}
