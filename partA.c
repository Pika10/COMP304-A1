#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char* argv[])
{
	pid_t pid;

	int num = atoi(argv[1]);
	int i;
	int level = 0;
	for (i = 0; i< num; i++)
	{
		pid = fork();
		if (pid ==0)
		{
			level +=1;
		}
		
	}
	if (level ==0)
	{
		printf("Main Process ID: %d, level: %d\n",getpid(),level);
	}
	else
	{
		printf("Process ID: %d, Parent ID: %d, level: %d\n",getpid(),getppid(), level);
	}
	for (i = 0;i<num;i++)
	{
	wait(NULL);
	}
	
	return 0;
}
