#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h> // pthread 관련 함수
# include <stdio.h> // printf
# include <string.h> // memset
# include <unistd.h> // write, usleep
# include <stdlib.h> // free, malloc
# include <sys/time.h> // gettimeofday 

# define TAKE_FORK_MSG "%ld %d has taken a fork\n"
# define EAT_MSG "%ld %d is eating\n"
# define SLEEP_MSG "%ld %d is sleeping\n"
# define THINK_MSG "%ld %d is thinking\n"
# define DIE_MASG "%ld %d is died\n"

// error
# define MALLOC_ERROR_MSG "malloc failed\n"
# define INVALID_ARG_ERROR_MSG "invalid argument\n"

#define PHILO_DEATH 1

typedef struct s_info
{
	struct s_philo	*philos;
	struct s_fork	*forks;
	int				total_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				max_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	state;
}	t_info;

typedef struct s_fork
{
	pthread_mutex_t	m_fork;
	int				fork_state;
}	t_fork;

typedef struct s_philo
{
	pthread_t	tid;
	t_info		*info;
	int			id;
	int			state;
	int			lastes_eat_time;
	t_fork		l_fork;
	t_fork		r_fork;
}	t_philo;

/* utils */
int	ft_atoi(const char *str);
int	print_error(char *msg);

/* init */
int	init(t_info *info, t_philo *philo, int ac, char **av);
int	init_philo(t_info *info);
void	init_forks(t_info *info);
int	init_info(t_info *info, t_philo *philo, int ac, char **av);

/* run */



#endif