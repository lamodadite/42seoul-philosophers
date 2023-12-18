/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:15:48 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/19 07:34:22 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h> // pthread 관련 함수
# include <stdio.h> // printf
# include <string.h> // memset
# include <unistd.h> // write, usleep
# include <stdlib.h> // free, malloc
# include <sys/time.h> // gettimeofday

// philo says
# define TAKE_FORK_MSG "%lld %d has taken a fork\n"
# define EAT_MSG "%lld %d is eating\n"
# define SLEEP_MSG "%lld %d is sleeping\n"
# define THINK_MSG "%lld %d is thinking\n"
# define DIE_MSG "%lld %d is died\n"

// error
# define MALLOC_ERROR_MSG "malloc failed\n"
# define INVALID_ARG_ERROR_MSG "invalid argument\n"

typedef struct s_info
{
	struct s_philo	*philos;
	struct s_fork	*forks;
	int				total_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				max_eat;
	int				state;
	long long		start_time;
	pthread_mutex_t	m_check;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_state;
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
	int			eat_num;
	long long	time_to_die;
	t_fork		*l_fork;
	t_fork		*r_fork;
}	t_philo;

/* utils */
long long	timestamp(void);
int			ft_atoi(const char *str);
int			print_error(char *msg);
int			ft_usleep(int time);
int			philo_says(t_philo *philo, char *msg, int flag);
int			check_death(t_philo *philo);

/* init */
int			init(t_info *info, int ac, char **av);
int			init_philo(t_info *info);
int			init_info(t_info *info, int ac, char **av);
int			malloc_args(t_info *info);
void		init_forks(t_info *info);

/* thread */
int			one_case(t_philo *philo);
int			take_forks(t_philo *philo);
int			eat_delicious_spagetti(t_philo *philo);
void		drop_forks(t_philo *philo);
void		*routine(void *arg);

/* monitor */
void		monitoring(t_info *info);
int			check_death(t_philo *philo);

#endif