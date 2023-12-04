/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:16:43 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/04 21:20:04 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *philo)
{
	if (timestamp() >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->info->m_state);
		philo->info->state = 1;
		pthread_mutex_lock(&philo->info->m_print);
		printf(DIE_MSG, timestamp() - philo->info->start_time, philo->id);
		pthread_mutex_unlock(&philo->info->m_print);
		pthread_mutex_unlock(&philo->info->m_state);
		return (1);
	}
	if (philo->info->max_eat > 0 && philo->eat_num >= philo->info->max_eat)
	{
		pthread_mutex_lock(&philo->info->m_state);
		philo->info->state = 1;
		pthread_mutex_unlock(&philo->info->m_state);
		return (1);
	}
	return (0);
}

void	monitoring(t_info *info)
{
	int	i;

	i = 0;
	usleep(100);
	while (check_death(&info->philos[i]) == 0)
	{
		i++;
		if (i == info->total_num)
			i = 0;
	}
}
