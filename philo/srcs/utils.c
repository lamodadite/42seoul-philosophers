/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:04:10 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/04 21:16:29 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	philo_says(t_philo *philo, char *msg, int flag)
{
	pthread_mutex_lock(&philo->info->m_print);
	pthread_mutex_lock(&philo->info->m_state);
	if (philo->info->state == 1)
	{
		pthread_mutex_unlock(&philo->info->m_state);
		pthread_mutex_unlock(&philo->info->m_print);
		if (flag == 1 || flag == 2)
			pthread_mutex_unlock(&philo->l_fork->m_fork);
		if (flag == 2)
			pthread_mutex_unlock(&philo->r_fork->m_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->m_state);
	printf(msg, timestamp() - philo->info->start_time, philo->id);
	pthread_mutex_unlock(&philo->info->m_print);
	return (0);
}

int	ft_usleep(int time)
{
	long long	target;

	target = (long long) time + timestamp();
	while (target >= timestamp())
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
