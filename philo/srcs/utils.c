#include <philosophers.h>

int	check_death(t_philo *philo)
{
	if (timestamp() >= philo->time_to_die)
	{
		//printf("cur time = %lld\n", timestamp());
		//printf("philo[%d]->time_to_die = %lld\n", philo->id, philo->time_to_die);
		printf("[%d]timestamp() - philo->time_to_die = %lld\n", philo->id, timestamp() - philo->time_to_die);
		pthread_mutex_lock(&philo->info->m_state);
		printf("monitoring thread -> die because time\n");
		philo->info->state = 1;
		pthread_mutex_lock(&philo->info->m_print);
		printf(DIE_MSG, timestamp() - philo->info->start_time, philo->id);
		pthread_mutex_unlock(&philo->info->m_print);
		pthread_mutex_unlock(&philo->info->m_state);
		return (1);
	}
	if (philo->info->max_eat > 0 && philo->eat_num >= philo->info->max_eat)
	{
		printf("monitoring thread -> die because max_eat\n");
		pthread_mutex_lock(&philo->info->m_state);
		philo->info->state = 1;
		pthread_mutex_unlock(&philo->info->m_state);
		return (1);
	}
	return (0);
}

int	philo_says(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->info->m_print);
	pthread_mutex_lock(&philo->info->m_state);
	if (philo->info->state == 1)
	{
		pthread_mutex_unlock(&philo->info->m_state);
		pthread_mutex_unlock(&philo->info->m_print);
		//printf("[%d] in philo_says\n", philo->id);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->m_state);
	printf(msg, timestamp() - philo->info->start_time, philo->id);
	pthread_mutex_unlock(&philo->info->m_print);
	return (0);
}

int	ft_usleep(int time)
{
	long long	l_time;
	long long	start;

	l_time = (long long) time;
	start = timestamp();
	while (timestamp() - start < l_time)
		usleep((useconds_t) l_time * 100);
	return (0);
}

long long	timestamp(void)
{
	struct timeval te;

	gettimeofday(&te, NULL);
	return (te.tv_sec * 1000) + (te.tv_usec / 1000);
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
