#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	pid_t pid;
	pid = fork();
	if (pid ==0)
	{
		exit(0);
	}
	else
	{
		sleep(5);
		wait(NULL);
	}	
}
