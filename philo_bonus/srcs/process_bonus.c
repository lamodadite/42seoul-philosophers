/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:48:41 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/19 08:09:58 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	eat_delicious_spagetti(t_info *info)
{
	sem_wait(info->sem_forks);
	philo_says(info, TAKE_FORK_MSG);
	sem_wait(info->sem_forks);
	philo_says(info, TAKE_FORK_MSG);
	sem_wait(info->sem_check);
	*info->time_to_die = timestamp() + info->die_time;
	sem_post(info->sem_check);
	philo_says(info, EAT_MSG);
	ft_usleep(info->eat_time);
	sem_wait(info->sem_check);
	*info->eat_num += 1;
	if (info->max_eat > 0 && *info->eat_num >= info->max_eat)
		exit(0);
	sem_post(info->sem_check);
	sem_post(info->sem_forks);
	sem_post(info->sem_forks);
}

void	*monitoring(void *args)
{
	t_info	*info;

	info = (t_info *)args;
	usleep(100);
	while (1)
	{
		sem_wait(info->sem_check);
		if (timestamp() >= *info->time_to_die)
		{
			sem_wait(info->sem_print);
			printf(DIE_MSG, timestamp() - info->start_time, info->id);
			exit(1);
		}
		sem_post(info->sem_check);
		usleep(10);
	}
}

void	routine(t_info *info)
{
	pthread_t	tid;

	while (timestamp() <= info->start_time)
		usleep(10);
	if (info->id % 2 == 1)
		ft_usleep(info->eat_time / 2);
	sem_wait(info->sem_check);
	*info->time_to_die = timestamp() + info->die_time;
	sem_post(info->sem_check);
	pthread_create(&tid, NULL, monitoring, info);
	pthread_detach(tid);
	while (1)
	{
		eat_delicious_spagetti(info);
		philo_says(info, SLEEP_MSG);
		ft_usleep(info->sleep_time);
		philo_says(info, THINK_MSG);
	}
}
