#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>





int main(int argc, char* argv[])
{
	int status;
	int n = atoi(argv[2]);
	int targetNumber = atoi(argv[1]);
	const int SIZE = 4000;
	const char* name = "NUMBERS";
	int perChild = 1000 / n;
	int remainder = 1000 % n;
	int lastProcessCount;
	if (remainder != 0)
	{
		lastProcessCount = remainder + perChild;
	}
	else
	{
		lastProcessCount = perChild;
	}

	int childrenPids[n];
	pid_t pid;
	
	int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	void *ptr;
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	for (int i = 0; i<1000; i++)
	{
		int number;
		scanf("%d", &number);
		*((int *)ptr) = number; 
		//printf("%d\n", *((int *)ptr));
		ptr += sizeof(number);
	}
	ptr -= 1000 * sizeof(int);
	
	for (int i = 0 ; i < n; i++)
	{
		pid = fork();
		if (pid == 0)
		{	
			ptr += i * sizeof(int)* perChild;
			if (i == n-1)
			{
				perChild = lastProcessCount;
			}
			for (int j = 0; j< perChild; j ++)
			{
				int theNumber = *((int *)ptr);
				if ( theNumber == targetNumber)
				{
					printf("Number has been found: %d\n Index is: %d\n",theNumber,(i * perChild + j));
					exit(0);
				}
				ptr += sizeof(int);
			}
			exit(1);
		}
		else
		{
			childrenPids[i] = pid;
		}
		
	}
	int founderChild = -1;
	for (int i = 0; i<n; i++)
	{
		waitpid(childrenPids[i], &status, 0);
		if (status == 0)
		{
			founderChild = i;
			break;
		}
	}
	
	if (founderChild != -1)
	{
		for (int i = 0; i<n; i++)
		{
			if (i != founderChild)
			{
				kill(childrenPids[i]);
			}
		}
	}
	
	return 0;
	
	
}


