/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:04:07 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/07 18:24:38 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->total_num)
		pthread_mutex_destroy(&(info->philos[i].l_fork->m_fork));
	pthread_mutex_destroy(&(info->m_check));
	pthread_mutex_destroy(&(info->m_print));
	pthread_mutex_destroy(&(info->m_state));
	free(info->forks);
	free(info->philos);
}

void	wait_thread(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->total_num)
		pthread_join(info->philos[i].tid, NULL);
}

void	thread_run(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = timestamp();
	while (++i < info->total_num)
		pthread_create(&info->philos[i].tid, NULL, routine, &info->philos[i]);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (init(&info, ac, av) == 1)
		return (1);
	thread_run(&info);
	monitoring(&info);
	wait_thread(&info);
	clear(&info);
	return (0);
}
