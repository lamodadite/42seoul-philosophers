#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h> // pthread 관련 함수
# include <stdio.h> // printf
# include <string.h> // memset
# include <unistd.h> // write, usleep
# include <stdlib.h> // free, malloc
# include <sys/time.h> // gettimeofday 

typedef struct s_philo
{
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	unsigned int	num_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_of_time_must_eat;
}	t_philo;

#endif