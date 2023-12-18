/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:04:17 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/07 17:02:34 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	malloc_args(t_info *info)
{
	info->philos = (t_philo *)malloc(info->total_num * sizeof(t_philo));
	if (info->philos == NULL)
		return (print_error(MALLOC_ERROR_MSG));
	info->forks = (t_fork *)malloc(info->total_num * sizeof(t_fork));
	if (info->forks == NULL)
	{
		free(info->philos);
		return (print_error(MALLOC_ERROR_MSG));
	}
	return (0);
}

int	init_info(t_info *info, int ac, char **av)
{
	info->total_num = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	info->state = 0;
	info->max_eat = 0;
	if (info->total_num < 0 || info->die_time < 0
		|| info->eat_time < 0 || info->sleep_time < 0)
		return (print_error(INVALID_ARG_ERROR_MSG));
	if (ac == 6)
		info->max_eat = ft_atoi(av[5]);
	if (info->max_eat < 0)
		return (print_error(INVALID_ARG_ERROR_MSG));
	if (malloc_args(info) == 1)
		return (1);
	pthread_mutex_init(&info->m_check, NULL);
	pthread_mutex_init(&info->m_print, NULL);
	pthread_mutex_init(&info->m_state, NULL);
	return (0);
}

void	init_forks(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->total_num)
	{
		pthread_mutex_init(&(info->forks[i].m_fork), NULL);
		info->forks[i].fork_state = 0;
	}
}

int	init_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->total_num)
	{
		info->philos[i].id = i + 1;
		info->philos[i].info = info;
		info->philos[i].eat_num = 0;
		info->philos[i].l_fork = &info->forks[i];
		info->philos[i].r_fork = &info->forks[(i + 1) % info->total_num];
	}
	return (0);
}

int	init(t_info *info, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (print_error(INVALID_ARG_ERROR_MSG));
	if (init_info(info, ac, av) == 1)
		return (1);
	init_forks(info);
	if (init_philo(info) == 1)
		return (1);
	return (0);
}
