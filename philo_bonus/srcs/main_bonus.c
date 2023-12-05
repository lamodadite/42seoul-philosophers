/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:04:07 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/05 23:23:42 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	make_philo(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = timestamp();
	while (++i < info->total_num)
	{
		info->pids[i] = fork();
		if (info->pids[i] == 0)
		{
			info->id = i;
			routine(info);
		}
	}
}

void	wait_philo(t_info *info)
{
	int	i;
	int	result;

	i = -1;
	result = waitpid(-1, NULL, 0);
	if (result > 0)
	{
		while (++i < info->total_num)
			kill(info->pids[i], SIGKILL);
	}
	while (result > 0)
		result = waitpid(-1, NULL, 0);
}

void	clear(t_info *info)
{
	sem_close(info->sem_forks);
	sem_close(info->sem_print);
	sem_close(info->sem_check);
	free(info->pids);
	free(info->time_to_die);
	free(info->eat_num);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (init_info(&info, ac, av) == 1)
		return (1);
	make_philo(&info);
	wait_philo(&info);
	clear(&info);
	return (0);
}
