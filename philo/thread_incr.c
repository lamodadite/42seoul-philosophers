#include <pthread.h>
#include <stdio.h>

static int glob = 0;

static void *func(void *arg)
{
	int loops = *((int *) arg);
	//int loc;

	for (int i = 0; i < loops; i++)
	{
		//loc = glob;
		//loc++;
		//glob = loc;
		glob++;
	}
	return (NULL);
}

int main(void)
{
	pthread_t t1, t2;
	int loops, s;

	loops = 10000;
	s = pthread_create(&t1, NULL, func, &loops);
	if (s != 0)
		printf("error occured -> %d\n", s);
	s = pthread_create(&t2, NULL, func, &loops);
	if (s != 0)
		printf("error occured -> %d\n", s);
	
	s = pthread_join(t1, NULL);
	if (s != 0)
		printf("error occured -> %d\n", s);
	s = pthread_join(t2, NULL);
	if (s != 0)
		printf("error occured -> %d\n", s);
	
	printf("glob = %d\n", glob);
	return (0);
}