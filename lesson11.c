#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main(void)
{
	pid_t pid;
	
	if ((pid = fork()) < 0)
	{
		perror ("fork");
	}
	if (pid == 0)
	{
		printf ("%d", getpid());
		exit(0);
	}
	printf("%d", pid);
	exit(0);
}