/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:15:48 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/06 10:55:58 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h> // pthread 관련 함수
# include <semaphore.h> // semaphore 관련 함수
# include <stdio.h> // printf
# include <string.h> // memset
# include <unistd.h> // write, usleep
# include <stdlib.h> // free, malloc
# include <sys/time.h> // gettimeofday
# include <signal.h> // kill 

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
	pid_t		*pids;
	int			id;
	int			total_num;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			max_eat;
	int			*eat_num;
	long long	*time_to_die;
	long long	start_time;
	sem_t		*sem_forks;
	sem_t		*sem_print;
	sem_t		*sem_check;
}	t_info;

/* utils */
int			philo_says(t_info *info, char *msg);
int			ft_usleep(int time);
int			print_error(char *msg);
int			ft_atoi(const char *str);
long long	timestamp(void);

/* init */
int			malloc_args(t_info *info);
int			init_info(t_info *info, int ac, char **av);
void		open_sems(t_info *info);

/* process */
void		eat_delicious_spagetti(t_info *info);
void		*monitoring(void *args);
void		routine(t_info *info);

/* main */
void		clear(t_info *info);
void		wait_philo(t_info *info);
void		make_philo(t_info *info);

#endif