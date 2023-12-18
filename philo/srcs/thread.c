/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:04:20 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/12 23:17:16 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_case(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->l_fork->m_fork));
	usleep(philo->info->die_time);
	return (1);
}

void	drop_forks(t_philo *philo)
{
	philo->l_fork->fork_state = 0;
	pthread_mutex_unlock(&(philo->l_fork->m_fork));
	philo->r_fork->fork_state = 0;
	pthread_mutex_unlock(&(philo->r_fork->m_fork));
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->l_fork->m_fork));
	if (philo_says(philo, TAKE_FORK_MSG, 1) == 1)
		return (1);
	if (philo->info->total_num == 1)
		return (one_case(philo));
	philo->l_fork->fork_state = 1;
	pthread_mutex_lock(&(philo->r_fork->m_fork));
	if (philo_says(philo, TAKE_FORK_MSG, 2) == 1)
		return (1);
	philo->r_fork->fork_state = 1;
	return (0);
}

int	eat_delicious_spagetti(t_philo *philo)
{
	if (take_forks(philo) == 1)
		return (1);
	pthread_mutex_lock(&(philo->info->m_check));
	philo->time_to_die = timestamp() + philo->info->die_time;
	pthread_mutex_unlock(&(philo->info->m_check));
	if (philo_says(philo, EAT_MSG, 2) == 1)
		return (1);
	ft_usleep(philo->info->eat_time);
	if (philo->info->max_eat > 0)
	{
		pthread_mutex_lock(&(philo->info->m_check));
		philo->eat_num++;
		pthread_mutex_unlock(&(philo->info->m_check));
	}
	drop_forks(philo);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->info->m_check));
	philo->time_to_die = timestamp() + philo->info->die_time;
	pthread_mutex_unlock(&(philo->info->m_check));
	if (philo->id % 2 == 1)
		ft_usleep(philo->info->eat_time / 2);
	while (1)
	{
		if (eat_delicious_spagetti(philo) == 1)
			return (NULL);
		if (philo_says(philo, SLEEP_MSG, 0) == 1)
			return (NULL);
		ft_usleep(philo->info->sleep_time);
		if (philo_says(philo, THINK_MSG, 0) == 1)
			return (NULL);
	}
	return (NULL);
}
