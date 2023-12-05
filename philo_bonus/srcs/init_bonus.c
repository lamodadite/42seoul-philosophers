/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:33:46 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/05 21:52:56 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	open_sems(t_info *info)
{
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("check");
	info->sem_forks = sem_open("fork", O_CREAT, 0644, info->total_num);
	info->sem_print = sem_open("print", O_CREAT, 0644, 1);
	info->sem_check = sem_open("check", O_CREAT, 0644, 1);
}

int	malloc_args(t_info *info)
{
	info->pids = (pid_t *)malloc(info->total_num * sizeof(pid_t));
	if (info->pids == NULL)
		return (print_error(MALLOC_ERROR_MSG));
	info->eat_num = (int *)malloc(sizeof(int));
	if (info->eat_num == NULL)
	{
		free(info->pids);
		return (print_error(MALLOC_ERROR_MSG));
	}
	info->time_to_die = (long long *)malloc(sizeof(long long));
	if (info->time_to_die == NULL)
	{
		free(info->pids);
		free(info->eat_num);
		return (print_error(MALLOC_ERROR_MSG));
	}
	*info->eat_num = 0;
	*info->time_to_die = 0;
	return (0);
}

int	init_info(t_info *info, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (print_error(INVALID_ARG_ERROR_MSG));
	info->total_num = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	info->max_eat = 0;
	if (info->total_num < 0 || info->die_time < 0
		|| info->eat_time < 0 || info->sleep_time < 0)
		return (print_error(INVALID_ARG_ERROR_MSG));
	if (ac == 6)
		info->max_eat = ft_atoi(av[5]);
	if (info->max_eat < 0)
		return (print_error(INVALID_ARG_ERROR_MSG));
	malloc_args(info);
	open_sems(info);
	return (0);
}
