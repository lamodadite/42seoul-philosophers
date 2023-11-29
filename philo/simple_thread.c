#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static void *func(void *arg)
{
	char *s = (char *) arg;
	printf("[%d] -> %s", pthread_self(), s);
	int i = 0;
	while (s[i] != '\0')
		i++;
	return ((void *) i);
}

int main(int ac, char **av)
{
	pthread_t t1;
	void	*res;
	int	s;

	for (int i = 0; i < 100; i++)
	{
		s = pthread_create(&t1, NULL, func, "Hello world\n");
		if (s != 0)
			printf("error occured!! %d\n", s);
		pthread_detach(t1);
		printf("message from main()\n");
		//s = pthread_join(t1, &res);
		//if (s != 0)
		//	printf("error occured!! %d\n", s);
	}
	
	printf("thread return %d\n", (int) res);
	exit(0);
}
