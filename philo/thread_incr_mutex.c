#include <pthread.h>
#include <stdio.h>

static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *func(void *arg)
{
	int loops = *((int *) arg);
	int loc, s;

	for (int i = 0; i < loops; i++)
	{
		s = pthread_mutex_lock(&mtx);
		if (s != 0)
			printf("mtx lock error %d\n", s);
		loc = glob;
		loc++;
		glob = loc;
		s = pthread_mutex_unlock(&mtx);
		if (s != 0)
			printf("mtx lock error %d\n", s);
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