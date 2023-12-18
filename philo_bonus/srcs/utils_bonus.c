/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:04:10 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/19 08:02:05 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	philo_says(t_info *info, char *msg)
{
	sem_wait(info->sem_print);
	printf(msg, timestamp() - info->start_time, info->id);
	sem_post(info->sem_print);
	return (0);
}

int	ft_usleep(int time)
{
	long long	target;

	target = (long long) time + timestamp();
	while (target > timestamp())
		usleep(100);
	return (0);
}

long long	timestamp(void)
{
	struct timeval	te;

	gettimeofday(&te, NULL);
	return ((te.tv_sec * 1000) + (te.tv_usec / 1000));
}

int	print_error(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	if (result > INT32_MAX || result < 0)
		return (-1);
	return (result * sign);
}
